# Line Following Robot 🤖

An autonomous line-following robot built in C on Arduino that secured 
**1st place** at the UofT Robotics Competition with a record 
**12-second track time**.

> [!NOTE]
> Source code is not available for this project.

## Photos
<img width="434" height="575" alt="image" src="https://github.com/user-attachments/assets/f1ec8cfd-efa9-457e-9db3-a3d8f54e8072" />

<img width="431" height="571" alt="image" src="https://github.com/user-attachments/assets/2bc65aa7-66fc-4391-8c9a-ae17ecabd51b" />



## Results
- 🏆 **1st place** — UofT Robotics Competition
- ⏱️ **12-second track time** — fastest recorded run

## Tech Stack
- **Microcontroller:** Arduino
- **Language:** C
- **Communication:** UART debugging
- **Design:** Fusion360 (chassis)
- **Wireless:** Bluefruit LE

## How It Works
The robot uses an array of IR sensors along its underside to detect 
the line on the track. The control algorithm reads sensor values 
continuously and adjusts left and right motor speeds to keep the 
robot centered on the line.

The key challenge was tuning the control algorithm to be aggressive 
enough to handle sharp turns at high speed without overshooting — 
getting this balance right was what pushed the track time down to 
12 seconds.

## Key Engineering Challenges
- Optimized control algorithm in C to process IR sensor data with 
  minimal latency — critical at high speeds where reaction time 
  determines whether the robot stays on track
- Diagnosed and resolved UART communication failures between sensor 
  array and controller under competition pressure
- Iterated on motor speed curves to find the right balance between 
  cornering aggression and stability

## Competition
UofT Robotics Competition — competed against teams across the 
university, placing 1st with the fastest recorded track time
