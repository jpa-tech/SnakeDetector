import numpy as np
import pandas as pd

# Set up the time environment
sample_rate = 500 
duration = 2.0 # 2 seconds per file
num_files = 30 # 30 files * 2s = 60 seconds of data per class

print("Generating files...")

for i in range(num_files):
    # Time array for 2 seconds
    time = np.linspace(0, duration, int(sample_rate * duration))
    base_noise = 0.1 * np.random.randn(len(time))

    # --- GENERATE SNAKE VIBRATION ---
    snake_wave = 0.5 * np.sin(2 * np.pi * 75 * time)
    snake_signal = base_noise + snake_wave

    # --- GENERATE HUMAN/MAMMAL DISTURBANCE ---
    heavy_rumble = 0.8 * np.sin(2 * np.pi * 15 * time) + 0.6 * np.sin(2 * np.pi * 25 * time)
    footstep_signal = base_noise + heavy_rumble

    # --- SAVE DATA TO CSV FILES ---
    pd.DataFrame({'timestamp': time * 1000, 'vibration_amplitude': snake_signal}).to_csv(f'snake_data_{i}.csv', index=False)
    pd.DataFrame({'timestamp': time * 1000, 'vibration_amplitude': footstep_signal}).to_csv(f'footstep_data_{i}.csv', index=False)

print("Bulletproof continuous frequency data generated as multiple segments!")
