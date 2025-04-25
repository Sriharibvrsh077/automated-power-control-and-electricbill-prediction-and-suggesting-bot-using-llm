# Visitor Counter Using Ultrasonic Sensors, Servo Motor, and 7-Segment Display

This Arduino-based project is a simple automated visitor counter using two ultrasonic sensors, a servo motor as a gate, and a 7-segment display for visual count output. It detects entry and exit using HC-SR04 sensors and controls a gate using a servo based on occupancy.

## 🛠️ Hardware Used
- Arduino Mega 2560
- 2 × HC-SR04 Ultrasonic Sensors
- 1 × Servo Motor (e.g., SG90)
- 1 × 7-Segment Display (Common Cathode)
- 74HC595 Shift Register
- Breadboard and jumper wires

## ⚙️ How It Works
- **Sensor 1** detects entry.
- **Sensor 2** detects exit.
- **Visitor count** is incremented or decremented based on direction of motion.
- A **servo motor** simulates a gate: opens when someone enters, closes when empty.
- **7-segment display** shows the live visitor count using a shift register.

## 💻 Code Overview
- Includes servo control via `Servo.h`.
- Uses shift register with `shiftOut()` to drive 7-segment display.
- Monitors distance using `pulseIn()` from ultrasonic sensors.
- Prevents false positives by checking sensor sequences.

## 🔧 Wiring Guide (Pin Mapping)
| Component         | Arduino Mega Pin |
|------------------|------------------|
| Ultrasonic 1 Trig| 5                |
| Ultrasonic 1 Echo| 4                |
| Ultrasonic 2 Trig| 7                |
| Ultrasonic 2 Echo| 6                |
| Servo Motor      | 8                |
| Shift Register DS| 50               |
| Shift Register ST| 48               |
| Shift Register SH| 46               |

## 🧠 Logic Flow
1. Detect distance from both ultrasonic sensors.
2. If Sensor 1 is triggered first, wait for Sensor 2 – indicates **entry**.
3. If Sensor 2 is triggered first, wait for Sensor 1 – indicates **exit**.
4. Update the count and servo motor position.
5. Display count on 7-segment using shift register.

## 📂 Code File
You can find the code inside [`visitor_counter.ino`](visitor_counter.ino). It is well-commented and ready to upload to an Arduino Mega.

## 🪛 Future Improvements
- Add buzzer for unauthorized access
- Store count in EEPROM for power resilience
- Add an LCD or OLED screen for more information

## 🖼️ Screenshots / Demo (Optional)
*Add wiring diagram or real-time demo video links here if available.*

---

Feel free to fork and improve! 😊
# 🔌 Electricity Bill Predictions

This project provides a data-driven solution for predicting electricity bills based on historical consumption data. It uses machine learning models to forecast upcoming electricity charges and offers insights into energy usage patterns to help users save money.

## 📓 Project Contents

- `electricity-bill-prdictions.ipynb` — Main Jupyter Notebook containing:
  - Data cleaning & preprocessing
  - Feature engineering
  - Model training & evaluation
  - Bill prediction
  - Appliance-wise consumption visualization
  - Energy-saving suggestions

## 🚀 Features

- Predict future electricity bills using historical data
- Visualize consumption trends and patterns
- Appliance-wise energy usage breakdown
- Smart energy-saving suggestions
- Exportable results and insights

## 🛠️ Technologies Used

- Python
- Pandas, NumPy
- Scikit-learn
- Matplotlib, Seaborn
- Jupyter Notebook

## 📦 Setup Instructions

1. Clone the repository or download the notebook.
2. Install dependencies:
   ```bash
   pip install pandas numpy matplotlib seaborn scikit-learn
