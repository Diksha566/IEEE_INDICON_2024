#include <Wire.h>
#include <Adafruit_PN532.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_ADXL345_U.h>
#include "anomaly_model.h" // Include TensorFlow Lite model
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

// NFC Module Pins
#define SDA_PIN 21
#define SCL_PIN 22

// DHT Sensor Pins and Type
#define DHT_PIN 14
#define DHT_TYPE DHT22

// MQ-135 Analog Pin
#define MQ135_PIN 36

// Initialize NFC module
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

// Initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Initialize ADXL345 accelerometer
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// TensorFlow Lite variables
const tflite::Model* model;
tflite::MicroInterpreter* interpreter;
uint8_t tensor_arena[2 * 1024]; // Adjust based on model size

// TensorFlow Lite setup
void setupAI() {
  model = tflite::GetModel(anomaly_model);
  static tflite::AllOpsResolver resolver;
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, sizeof(tensor_arena));
  interpreter = &static_interpreter;

  if (interpreter->AllocateTensors() != kTfLiteOk) {
    Serial.println("Tensor allocation failed!");
    while (1);
  }
}

// Run inference using TensorFlow Lite
float runInference(float input_data[]) {
  float* input = interpreter->input(0)->data.f;
  for (int i = 0; i < interpreter->input(0)->bytes / sizeof(float); i++) {
    input[i] = input_data[i];
  }

  if (interpreter->Invoke() != kTfLiteOk) {
    Serial.println("Inference failed!");
    return -1;
  }

  return interpreter->output(0)->data.f[0]; // Return anomaly score
}

// Function to send NFC alert
void sendNFCAlert(String message) {
  uint8_t ndefMessage[128];
  size_t messageLength = message.length();
  memcpy(ndefMessage, message.c_str(), messageLength);

  bool success = nfc.writeNDEFURI(ndefMessage);
  if (success) {
    Serial.println("NFC alert sent: " + message);
  } else {
    Serial.println("Failed to send NFC alert.");
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize NFC module
  nfc.begin();
  if (!nfc.getFirmwareVersion()) {
    Serial.println("NFC module not found!");
    while (1);
  }
  nfc.SAMConfig();
  Serial.println("NFC module initialized.");

  // Initialize sensors
  dht.begin();
  if (!accel.begin()) {
    Serial.println("ADXL345 not found!");
    while (1);
  }

  // Initialize TensorFlow Lite
  setupAI();
}

void loop() {
  // Read sensors
  float gas = analogRead(MQ135_PIN);          // MQ-135 gas concentration
  float temperature = dht.readTemperature(); // DHT22 temperature
  float vibrationX, vibrationY, vibrationZ;
  sensors_event_t event;
  accel.getEvent(&event);
  vibrationX = event.acceleration.x;
  vibrationY = event.acceleration.y;
  vibrationZ = event.acceleration.z;

  // Check if sensor readings are valid
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Log sensor data
  Serial.print("Gas: "); Serial.print(gas);
  Serial.print(", Temp: "); Serial.print(temperature);
  Serial.print(", VibrationX: "); Serial.print(vibrationX);
  Serial.print(", VibrationY: "); Serial.print(vibrationY);
  Serial.print(", VibrationZ: "); Serial.println(vibrationZ);

  // Prepare input data for the AI model
  float input_data[4] = {gas, vibrationX, vibrationY, temperature};

  // Run anomaly detection
  float anomaly_score = runInference(input_data);
  Serial.print("Anomaly Score: "); Serial.println(anomaly_score);

  // Check for anomalies
  if (anomaly_score > 0.5) { // Threshold can be adjusted based on the model
    String alertMessage = "Anomaly detected! Gas: " + String(gas) +
                          ", Temp: " + String(temperature) +
                          ", VibrationX: " + String(vibrationX) +
                          ", VibrationY: " + String(vibrationY);
    sendNFCAlert(alertMessage);
  }

  // Delay before next cycle
  delay(2000); // 2 seconds
}