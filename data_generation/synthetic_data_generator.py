import numpy as np
import pandas as pd

# Set up the time environment (1 second of data recording at 500 samples per second)
sample_rate = 500 
duration = 1.0 
time = np.linspace(0, duration, int(sample_rate * duration))

# --- GENERATE BACKGROUND NOISE ---
# This simulates the normal vibrations of the earth (wind, distant roads)
base_noise = 0.1 * np.random.randn(len(time))

# --- GENERATE SNAKE VIBRATION ---
# Snakes create a continuous, low-frequency wave. We will simulate a 75 Hz wave.
snake_freq = 75 
snake_wave = 0.5 * np.sin(2 * np.pi * snake_freq * time)
# Combine the snake wave with the background noise
snake_signal = base_noise + snake_wave

# --- GENERATE HUMAN FOOTSTEP VIBRATION ---
# A footstep is a sudden, heavy spike (transient event), not a continuous wave.
footstep_signal = base_noise.copy()
# Inject a heavy spike right in the middle of the recording (samples 200 to 250)
footstep_signal[200:250] += 5.0 

# --- SAVE DATA TO CSV FILES ---
# Edge Impulse requires data in columns. We will save these arrays as CSV files.
pd.DataFrame({'vibration_amplitude': snake_signal}).to_csv('snake_data.csv', index=False)
pd.DataFrame({'vibration_amplitude': footstep_signal}).to_csv('footstep_data.csv', index=False)

print("Synthetic data successfully generated and saved to CSV!")
