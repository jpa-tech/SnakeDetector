/* Includes ---------------------------------------------------------------- */


/* Constant Defines -------------------------------------------------------- */
#define SENSOR_PIN A0       // Analog pin reading the geophone/vibration sensor
#define MOTOR_PIN 3         // PWM-capable digital pin for the vibration motor
#define THRESHOLD 0.80f     // 80% confidence threshold

// Allocate a buffer to hold 2 seconds of sensor data
float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

// Edge Impulse callback to pull data from our buffer
int raw_feature_get_data(size_t offset, size_t length, float *out_ptr) {
    memcpy(out_ptr, features + offset, length * sizeof(float));
    return 0;
}

void setup() {
    Serial.begin(115200);
    pinMode(SENSOR_PIN, INPUT);
    pinMode(MOTOR_PIN, OUTPUT);
    
    // Seed the random number generator using analog noise for true randomness
    randomSeed(analogRead(A1)); 
    
    Serial.println("Edge AI Seismic Deterrent System Initialized.");
}

void loop() {
    Serial.println("Listening to ground vibrations...");

    // ==================================================================
    // 1. DATA ACQUISITION (Targeting your 500 Hz sample rate)
    // 500 Hz = 1 sample every 2000 microseconds
    // ==================================================================
    for (int i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i++) {
        unsigned long start_time = micros();
        
        // Read the analog vibration data
        features[i] = (float)analogRead(SENSOR_PIN); 

        // Pad the loop with a delay to hit exactly 500 Hz
        while (micros() - start_time < 2000) {
            // Wait
        }
    }

    // ==================================================================
    // 2. EDGE AI INFERENCE
    // ==================================================================
    ei_impulse_result_t result = { 0 };
    signal_t features_signal;
    features_signal.total_length = sizeof(features) / sizeof(features[0]);
    features_signal.get_data = &raw_feature_get_data;

    // Run the classifier
    EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, false);
    if (res != EI_IMPULSE_OK) {
        Serial.printf("ERR: Failed to run classifier (%d)\n", res);
        return;
    }

    // ==================================================================
    // 3. DECISION LOGIC & STATE MACHINE
    // ==================================================================
    bool snake_detected = false;
    
    // Loop through the output classes to find "snake_data"
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        if (strcmp(result.classification[i].label, "snake_data") == 0) {
            if (result.classification[i].value >= THRESHOLD) {
                snake_detected = true;
            }
        }
    }

    // ==================================================================
    // 4. ACTUATION & BLANKING PERIOD
    // ==================================================================
    if (snake_detected) {
        Serial.println("THREAT DETECTED: 75 Hz signature verified. Firing deterrent!");
        
        triggerChaoticDeterrent(); // Fire the motor
        
        Serial.println("Entering Blanking Period...");
        delay(4000); // 4-second refractory period to let soil settle
        
    } else {
        Serial.println("Environment safe (Noise/Footsteps). Motor off.");
        analogWrite(MOTOR_PIN, 0); // Ensure motor remains off to save power
    }
}

// Function to generate the pseudo-random biological deterrent pulses
void triggerChaoticDeterrent() {
    // Run a sequence of 5 chaotic, unpredictable pulses
    for (int i = 0; i < 5; i++) {
        int motorSpeed = random(150, 255);      // Random PWM intensity (voltage)
        int pulseDuration = random(150, 500);   // Random ON duration (150ms to 500ms)
        int pauseDuration = random(50, 200);    // Random OFF duration (50ms to 200ms)

        analogWrite(MOTOR_PIN, motorSpeed);
        delay(pulseDuration);
        
        analogWrite(MOTOR_PIN, 0);
        delay(pauseDuration);
    }
}
