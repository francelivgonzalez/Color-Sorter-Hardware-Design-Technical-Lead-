#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/*
 * Color Sorting System
 * Arduino Uno R3
 *
 * Firmware - development version
 *
 * Hardware:
 * - Arduino Uno R3
 * - TCS3200 color sensor
 * - A4988 stepper driver
 * - NEMA 17 stepper motor
 * - PCA9685 servo driver
 * - Three servo channels
 * - Homing limit switch
 *
 * Features:
 * - RGB + clear-channel measurements
 * - Lighting-aware normalized color detection
 * - Confidence threshold for classification
 * - Stepper indexing
 * - Multi-servo actuation
 * - Homing with travel limits
 * - Manual Serial Monitor commands
 */

Adafruit_PWMServoDriver pwm(0x40);

// ---------- PIN ASSIGNMENTS ----------

// A4988
const byte STEP_PIN = 2;
const byte DIR_PIN = 3;
const byte ENABLE_PIN = 9;

// TCS3200
const byte S0_PIN = 4;
const byte S1_PIN = 5;
const byte S2_PIN = 6;
const byte S3_PIN = 7;
const byte SENSOR_OUT_PIN = 8;

// Homing switch
const byte HOME_PIN = 10;

// PCA9685 channels
const byte INTAKE_SERVO = 0;
const byte GATE_SERVO = 1;
const byte ROUTING_SERVO = 2;

// ---------- SERVO SETTINGS ----------

// PCA9685 pulse counts at 50 Hz
// Calibrate these values for the actual servos.
const int SERVO_MIN = 150;
const int SERVO_MAX = 600;

const int CLOSED_ANGLE = 20;
const int OPEN_ANGLE = 100;

// ---------- STEPPER SETTINGS ----------

const unsigned int STEP_DELAY_US = 1000;

// Provisional bin positions in full steps
const long RED_BIN = 0;
const long GREEN_BIN = 400;
const long BLUE_BIN = 800;

const long MAX_HOME_STEPS = 4000;
const long MAX_MOVE_STEPS = 2000;

const int HOME_BACKOFF_STEPS = 40;

// Adjust to match the actual homing direction.
const byte HOME_DIRECTION = LOW;

long currentPosition = 0;
bool isHomed = false;

// ---------- SENSOR SETTINGS ----------

const unsigned long SENSOR_TIMEOUT_US = 30000UL;
const unsigned long LOW_LIGHT_LIMIT_US = 20000UL;

// Provisional normalized color separation threshold.
// Must be tuned using measured samples.
const float COLOR_SEPARATION_THRESHOLD = 0.12f;

const int COLOR_SAMPLES = 5;

// ---------- COLORS ----------

enum Color {
  RED,
  GREEN,
  BLUE,
  UNKNOWN
};

// ---------- SERVO CONTROL ----------

void setServoAngle(byte channel, int angle) {
  angle = constrain(angle, 0, 180);

  int pulse = map(
    angle,
    0,
    180,
    SERVO_MIN,
    SERVO_MAX
  );

  pwm.setPWM(channel, 0, pulse);
}

void closeAllServos() {
  setServoAngle(INTAKE_SERVO, CLOSED_ANGLE);
  setServoAngle(GATE_SERVO, CLOSED_ANGLE);
  setServoAngle(ROUTING_SERVO, CLOSED_ANGLE);
}

void testServo(byte channel) {
  Serial.print("Testing servo channel ");
  Serial.println(channel);

  setServoAngle(channel, OPEN_ANGLE);
  delay(700);

  setServoAngle(channel, CLOSED_ANGLE);
  delay(400);

  Serial.println("Servo test complete.");
}

// ---------- STEPPER CONTROL ----------

void enableStepper(bool enabled) {
  // A4988 ENABLE is active LOW
  digitalWrite(ENABLE_PIN, enabled ? LOW : HIGH);
}

void singleStep() {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(STEP_DELAY_US);

  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(STEP_DELAY_US);
}

bool homeSorter() {
  Serial.println("Starting homing...");

  isHomed = false;
  enableStepper(true);

  // If the home switch is already pressed,
  // move away until it releases.
  if (digitalRead(HOME_PIN) == LOW) {
    digitalWrite(DIR_PIN, !HOME_DIRECTION);

    bool released = false;

    for (long i = 0; i < MAX_HOME_STEPS; i++) {
      if (digitalRead(HOME_PIN) == HIGH) {
        released = true;
        break;
      }

      singleStep();
    }

    if (!released) {
      enableStepper(false);
      Serial.println("ERROR: Home switch did not release.");
      return false;
    }
  }

  // Move toward the home switch.
  digitalWrite(DIR_PIN, HOME_DIRECTION);

  bool foundHome = false;

  for (long i = 0; i < MAX_HOME_STEPS; i++) {
    if (digitalRead(HOME_PIN) == LOW) {
      foundHome = true;
      break;
    }

    singleStep();
  }

  if (!foundHome) {
    enableStepper(false);
    Serial.println("ERROR: Home switch not found.");
    return false;
  }

  // Back away from the home switch.
  digitalWrite(DIR_PIN, !HOME_DIRECTION);

  for (int i = 0; i < HOME_BACKOFF_STEPS; i++) {
    singleStep();
  }

  if (digitalRead(HOME_PIN) == LOW) {
    enableStepper(false);
    Serial.println("ERROR: Home switch still pressed.");
    return false;
  }

  currentPosition = 0;
  isHomed = true;

  enableStepper(false);

  Serial.println("Homing complete.");
  return true;
}

bool moveToPosition(long target) {
  if (!isHomed) {
    Serial.println("ERROR: Home the sorter first.");
    return false;
  }

  long difference = target - currentPosition;
  long count = abs(difference);

  if (count > MAX_MOVE_STEPS) {
    Serial.println("ERROR: Movement limit exceeded.");
    return false;
  }

  if (count == 0) {
    return true;
  }

  digitalWrite(
    DIR_PIN,
    difference > 0 ? HIGH : LOW
  );

  enableStepper(true);

  for (long i = 0; i < count; i++) {
    singleStep();
  }

  currentPosition = target;
  enableStepper(false);

  Serial.print("Reached position: ");
  Serial.println(currentPosition);

  return true;
}

// ---------- TCS3200 SENSOR ----------

// Returns pulse duration in microseconds.
// Smaller duration generally indicates
// greater detected light intensity.

unsigned long readChannel(byte s2, byte s3) {
  digitalWrite(S2_PIN, s2);
  digitalWrite(S3_PIN, s3);

  delay(20);

  unsigned long total = 0;

  for (int i = 0; i < COLOR_SAMPLES; i++) {
    unsigned long pulse = pulseIn(
      SENSOR_OUT_PIN,
      LOW,
      SENSOR_TIMEOUT_US
    );

    if (pulse == 0) {
      return 0;
    }

    total += pulse;
  }

  return total / COLOR_SAMPLES;
}

// Read red, green, blue and clear channels.

bool readRGB(
  unsigned long &r,
  unsigned long &g,
  unsigned long &b,
  unsigned long &clearValue
) {
  // Red filter: S2 LOW, S3 LOW
  r = readChannel(LOW, LOW);

  // Green filter: S2 HIGH, S3 HIGH
  g = readChannel(HIGH, HIGH);

  // Blue filter: S2 LOW, S3 HIGH
  b = readChannel(LOW, HIGH);

  // Clear filter: S2 HIGH, S3 LOW
  clearValue = readChannel(HIGH, LOW);

  if (
    r == 0 ||
    g == 0 ||
    b == 0 ||
    clearValue == 0
  ) {
    Serial.println("ERROR: TCS3200 sensor timeout.");
    return false;
  }

  Serial.println("Raw sensor measurements:");

  Serial.print("R: ");
  Serial.print(r);

  Serial.print(" | G: ");
  Serial.print(g);

  Serial.print(" | B: ");
  Serial.print(b);

  Serial.print(" | Clear: ");
  Serial.println(clearValue);

  return true;
}

// ---------- COLOR CLASSIFICATION ----------

Color detectColor() {
  unsigned long r, g, b, clearValue;

  if (!readRGB(r, g, b, clearValue)) {
    return UNKNOWN;
  }

  // Reject extremely low illumination.
  // Threshold requires physical calibration.
  if (clearValue > LOW_LIGHT_LIMIT_US) {
    Serial.println("Insufficient lighting.");
    return UNKNOWN;
  }

  // Convert pulse durations to values
  // proportional to sensor frequency.
  float red = 1.0f / (float)r;
  float green = 1.0f / (float)g;
  float blue = 1.0f / (float)b;

  float total = red + green + blue;

  if (total <= 0.0f) {
    return UNKNOWN;
  }

  // Normalize to reduce the effect of
  // uniform brightness changes.
  float normR = red / total;
  float normG = green / total;
  float normB = blue / total;

  Serial.println("Normalized color values:");

  Serial.print("R: ");
  Serial.print(normR, 3);

  Serial.print(" | G: ");
  Serial.print(normG, 3);

  Serial.print(" | B: ");
  Serial.println(normB, 3);

  float highest = max(
    normR,
    max(normG, normB)
  );

  float lowest = min(
    normR,
    min(normG, normB)
  );

  float separation = highest - lowest;

  Serial.print("Color separation: ");
  Serial.println(separation, 3);

  // Reject weak or ambiguous classification.
  if (separation < COLOR_SEPARATION_THRESHOLD) {
    Serial.println("Color classification uncertain.");
    return UNKNOWN;
  }

  if (highest == normR) {
    return RED;
  }

  if (highest == normG) {
    return GREEN;
  }

  if (highest == normB) {
    return BLUE;
  }

  return UNKNOWN;
}

// ---------- SORTING LOGIC ----------

void sortObject() {
  if (!isHomed) {
    Serial.println("ERROR: Home sorter before sorting.");
    return;
  }

  Serial.println("Reading object color...");

  Color detected = detectColor();
  long target;

  switch (detected) {
    case RED:
      Serial.println("Detected: RED");
      target = RED_BIN;
      break;

    case GREEN:
      Serial.println("Detected: GREEN");
      target = GREEN_BIN;
      break;

    case BLUE:
      Serial.println("Detected: BLUE");
      target = BLUE_BIN;
      break;

    default:
      Serial.println(
        "Unknown color. Sorting cancelled."
      );
      return;
  }

  if (!moveToPosition(target)) {
    return;
  }

  // Open gate to release the object.
  setServoAngle(GATE_SERVO, OPEN_ANGLE);
  delay(700);

  // Close gate.
  setServoAngle(GATE_SERVO, CLOSED_ANGLE);
  delay(400);

  Serial.println("Sorting cycle complete.");
}

// ---------- SERIAL COMMANDS ----------

void printCommands() {
  Serial.println();
  Serial.println("Available commands:");
  Serial.println("r - Read RGB + clear sensor values");
  Serial.println("c - Classify the current color");
  Serial.println("h - Home the stepper");
  Serial.println("s - Run one sorting cycle");
  Serial.println("0 - Test intake servo");
  Serial.println("1 - Test gate servo");
  Serial.println("2 - Test routing servo");
  Serial.println("? - Show commands");
  Serial.println();
}

// ---------- SETUP ----------

void setup() {
  Serial.begin(9600);

  // A4988: configure disabled before use.
  digitalWrite(ENABLE_PIN, HIGH);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  // TCS3200
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(SENSOR_OUT_PIN, INPUT);

  // Home switch
  pinMode(HOME_PIN, INPUT_PULLUP);

  // TCS3200 output scaling: 20%
  digitalWrite(S0_PIN, HIGH);
  digitalWrite(S1_PIN, LOW);

  // PCA9685 servo driver
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(100);

  closeAllServos();

  Serial.println("Color Sorting System");
  Serial.println("Arduino Uno R3");
  Serial.println("Development firmware initialized.");

  printCommands();
}

// ---------- MAIN LOOP ----------

void loop() {
  if (!Serial.available()) {
    return;
  }

  char command = Serial.read();

  switch (command) {

    case 'r': {
      unsigned long r, g, b, clearValue;

      readRGB(r, g, b, clearValue);
      break;
    }

    case 'c': {
      Color color = detectColor();

      switch (color) {
        case RED:
          Serial.println("Result: RED");
          break;

        case GREEN:
          Serial.println("Result: GREEN");
          break;

        case BLUE:
          Serial.println("Result: BLUE");
          break;

        default:
          Serial.println("Result: UNKNOWN");
          break;
      }

      break;
    }

    case 'h':
      homeSorter();
      break;

    case 's':
      sortObject();
      break;

    case '0':
      testServo(INTAKE_SERVO);
      break;

    case '1':
      testServo(GATE_SERVO);
      break;

    case '2':
      testServo(ROUTING_SERVO);
      break;

    case '?':
      printCommands();
      break;

    default:
      break;
  }
}
