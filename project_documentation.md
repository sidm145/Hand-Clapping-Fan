# Clap-Activated Fan Project

## 📋 Total Component List

1. **Arduino Board** (Uno, Nano, or compatible) - 1x
2. **LM393 Sound Sensor Module** - 1x
3. **DC Motor** (with fan blade attached) - 1x
4. **2N2222 NPN Transistor** - 1x
5. **220Ω Resistor** (for the Transistor Base) - 1x
6. **LED** - 1x
7. **220Ω Resistor** (for the LED) - 1x
8. **Breadboard** - 1x
9. **Jumper Wires** - Assorted
10. **Power Supply** (USB cable to computer or external power bank)

---

## 🔌 Circuit Connections

### 1. LM393 Sound Sensor
*   **VCC:** Connect to Arduino **5V**
*   **GND:** Connect to Arduino **GND**
*   **OUT:** Connect to Arduino **Digital Pin 2**

### 2. Status LED
*   **Anode (Long Leg):** Connect to a **220Ω Resistor**, then to Arduino **Digital Pin 4**
*   **Cathode (Short Leg):** Connect to Arduino **GND**

### 3. Motor & Transistor Circuit
*   **Arduino Digital Pin 3:** Connect to the **220Ω Resistor**, then to the **Base** (middle pin) of the 2N2222 Transistor.
*   **Transistor Emitter** (typically the right pin, check datasheet): Connect to Arduino **GND**.
*   **Transistor Collector** (typically the left pin): Connect to the **Negative (-)** terminal of the Motor.
*   **Motor Positive (+) Terminal:** Connect to Arduino **5V**.

*(Note: If your motor requires more power than the Arduino's 5V pin can safely provide, connect the Motor Positive to an external battery's positive terminal, and ensure the battery's negative terminal is connected to the Arduino GND.)*

---

## ⚙️ Workflow / System Logic

1.  **Sound Detection:** The LM393 sensor continuously listens for sound. When you clap, the sound exceeds the set threshold (adjusted via the onboard potentiometer), and the sensor's `OUT` pin drops to a `LOW` logic state.
2.  **Signal Processing:** The Arduino constantly reads `Digital Pin 2`. When it detects this `LOW` signal, it recognizes a valid clap.
3.  **State Toggling:** The system uses a boolean variable (`fanIsOn`) to track the current state. Every valid clap flips this state (from OFF to ON, or ON to OFF).
4.  **Actuation (Turning ON):** 
    *   The Status LED turns ON.
    *   **The Pro Kickstart:** The Arduino sends a maximum PWM signal (`255`) to `Digital Pin 3` for a brief 100 milliseconds. This provides a surge of power, fully opening the transistor and allowing maximum current to overcome the inertia of the heavy fan blade.
    *   **Cruising Speed:** After the 100ms kickstart, the PWM signal drops to `150` (~60% power). The 220Ω base resistor ensures the transistor stays cool while maintaining a smooth, quiet fan speed.
5.  **Actuation (Turning OFF):**
    *   The Status LED turns OFF.
    *   The PWM signal drops to `0`, fully closing the transistor and stopping the motor.
6.  **Debounce Delay:** After any state change, the Arduino pauses for 500 milliseconds. This prevents a single, slightly echoing clap from accidentally triggering the system multiple times rapidly.
