Data Generation and Simulation Methodology

Acquiring real-world seismic data for snake movement is highly difficult due to the animal's low mass and the unpredictability of field encounters. To overcome this data scarcity and effectively train our TinyML classification model, we utilized a mathematical simulation approach.

Biological evidence suggests that snakes have their greatest sensitivity to sound and substrate vibration in low frequencies, typically between 0 and 150 Hz. Specific studies on species like royal pythons show peak sensitivity to substrate vibration at 80–160 Hz.

Because snakes generate continuous, low-amplitude seismic waves when slithering, our synthetic_data_generator.py script mathematically simulates waveforms strictly within this 50-150 Hz biological frequency footprint. We combine this simulated snake wave with random, high-amplitude transient spikes (representing environmental noise and human footsteps). This synthetic dataset allows us to train the Edge-AI model to accurately filter out heavy background noise and isolate the specific, low-frequency seismic signature of a snake.
