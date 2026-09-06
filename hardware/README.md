# Hardware Logic: Edge AI Seismic Deterrent System

**Legal Notice:** ⚠️ Patent Pending - All Rights Reserved.

## System Overview (Physical Architecture)
This directory contains the hardware state machine for our TinyML seismic deterrent prototype. In its physical deployment, the system architecture utilizes:
* **Microcontroller:** ESP32
* **Sensor:** Analog Geophone (capturing 15-25 Hz ground vibrations)
* **AI Processing:** On-device Edge Impulse Neural Network (running FFT spectral feature extraction)
* **Actuator:** Eccentric Rotating Mass (ERM) Vibration Motor for chaotic PWM blanking

## 🛠️ Current Repository State: Evaluation & Simulation Mode
To allow hackathon judges and reviewers to easily evaluate our hardware logic without requiring physical geophones or compiling the full Edge Impulse C++ library, the `sketch.ino` file in this repository is currently configured for **Virtual Simulation (Wokwi)**.

### Simulation Pin Configuration & Wiring
In this simulation mode, the TinyML inference step is abstracted to a physical trigger:
* **GPIO 18 (OUTPUT):** Connected to an LED (simulating the ERM motor actuation).
* **GPIO 4 (INPUT_PULLUP):** Connected diagonally across a pushbutton to `GND` (simulating a verified 75 Hz AI detection).

## State Machine Architecture
Whether running the physical neural network or the virtual simulation, the C++ logic executes three strict operational states:
1. **Listening State:** The system loops continuously, sampling data.
2. **Actuation:** Upon a positive trigger, the system fires a 5-stage chaotic PWM sequence with randomized pulse durations (150-400ms) to prevent wildlife biological habituation.
3. **Hardware Blanking Period:** The system enters a strict 4000ms delay post-actuation. All sensor inputs are ignored during this refractory window to prevent the deterrent's own localized noise from creating a false-positive feedback loop.
