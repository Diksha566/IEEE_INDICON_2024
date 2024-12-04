# IEEE_INDICON_2024

# Real-Time Hazard Detection System for Construction Sites

This project uses **ESP32 microcontrollers** and the **Intel® Distribution of OpenVINO™ Toolkit** to build a real-time hazard detection system for construction sites. It integrates **AI-driven anomaly detection** and advanced sensors to monitor environmental and structural risks, enabling proactive hazard identification and mitigation.

---

## 🚧 Key Features
- **Real-Time Hazard Alerts**: Instantly sent to workers and supervisors via mobile devices, wearables, and NFC-enabled systems.
- **Comprehensive Monitoring**: Detects risks such as gas leaks, overheating, and structural instability.
- **Centralized Dashboard**: Provides real-time analytics for safety oversight.
- **AI Integration**: Optimized using Intel® OpenVINO™ for edge inference on ESP32.

---

## 🛠️ Technical Overview

### Architecture
- **Sensors**:
  - Gas Sensor (e.g., MQ-135): Monitors gas concentration in ppm.
  - Vibration Sensor (e.g., ADXL345): Tracks X, Y, Z-axis vibration data.
  - Temperature Sensor (e.g., DHT22): Reads environmental temperature in Celsius.
  
- **AI Models**:
  - Anomaly detection trained using TensorFlow.
  - Converted to TensorFlow Lite and optimized with Intel® OpenVINO™ Toolkit.
  
- **Communication**:
  - NFC-enabled PN532 module for instant alerts.

- **Programming Languages**:
  - Python: AI model training and development.
  - C++/Arduino: ESP32 programming.
  - JavaScript: Frontend for the dashboard.

### Workflow
1. **Data Collection**: ESP32 gathers sensor data in real-time.
2. **AI Processing**: AI model detects anomalies using sensor data.
3. **Alert Transmission**: NFC module sends formatted alerts to nearby devices.

### Intel Technologies Used
- **OpenVINO™ Toolkit**: Optimizes AI models for edge inference.
- **Intel® DevCloud**: For model training and testing.

---

## 🌟 Impact
- Enhances **worker safety** by proactively mitigating risks.
- Reduces **downtime** and **operational costs**.
- Prevents **environmental damage** caused by hazards like gas leaks.
- Scalable across various industries, including construction, manufacturing, and mining.

---

## 🚀 Future Potential
- Integration of additional sensors for broader risk coverage.
- Deployment in hazardous environments like oil refineries, chemical plants, and earthquake zones.
- Widespread adoption to improve global safety standards and sustainability.

---

![image](https://github.com/user-attachments/assets/02f3cadb-f0a9-4790-b13f-3326d3073920)


## 📂 Repository Structure

```plaintext
├── AI_Model/
│   ├── model_training.ipynb  # Training scripts and datasets
│   ├── tflite_model/         # Optimized TensorFlow Lite model
├── ESP32_Code/
│   ├── esp32_main.ino        # Main ESP32 code for data collection and NFC communication
├── Dashboard/
│   ├── index.html            # Dashboard frontend
│   ├── app.js                # JavaScript logic
├── Resources/
│   ├── architecture_diagram.png
│   ├── research_articles/
│       ├── IEEE_Article.pdf
│       ├── Pantech_Solutions.pdf
│   ├── datasets/
│       ├── gas_sensor_data.csv
│       ├── vibrational_data.csv
│       ├── temperature_data.csv
├── README.md                 # Project overview and setup instructions
