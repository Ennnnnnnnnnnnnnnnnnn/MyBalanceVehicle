# MyBalanceVehicle
Blance Vehicle Controled by BlueSerial
# STM32 Self-balancing Vehicle
A self-balancing robot based on STM32F103, iteratively developed from bottom-layer driver test to complete three-loop PID control with code optimization.

## Project Iterations
- **0 basic drive**: Module driver test code for the vehicle. Mainly used to verify the motor driver. During movement, vibration or falling may cause unstable encoder connections and occasional disconnection, so repeated verification is required at this driver layer.
- **1 pitch angle and complementary filtering**: MPU6050 data acquisition, conversion and pitch angle calculation. Pitch angle is the core parameter for balance control. Since the MPU6050 module cannot be mounted perfectly horizontal, a fixed installation offset needs to be calibrated and subtracted in the subsequent PID program.
  > Principle of complementary filter: The accelerometer can provide absolute tilt angle from ax/az, but the reading becomes inaccurate during motion. The gyroscope outputs angular velocity, which has no absolute reference but remains stable while moving. The final fused angle is dominated by gyroscope data with a small weight of accelerometer angle.
- **2 three-ring PID control**: Full control firmware of the balancing car. The three loops consist of cascaded angle loop + speed loop, plus an independent yaw steering loop.
  The angle loop alone can maintain upright posture and basic movement. However, the car cannot travel in a straight line and still drifts slightly when supposed to stay static. The speed loop and steering loop are added to solve these problems.
- **3 program optimization**: Optimization of the PID control algorithm, including derivative pre-processing on the angle loop, integral limiting for anti-windup, and output offset compensation. These improvements help the vehicle stop faster and reduce static jitter.

## Debugging Problems & Solutions
### 1. MPU6050 Noise
For this vehicle, fast response is prioritized over absolute measurement precision. The built-in hardware filter of MPU6050 was disabled in the driver. The serial curve showed more sharp spikes, but this noise level was acceptable for the control loop.

### 2. Hardware Soldering & Power Supply Faults
1. Poor soldering of PCB pads caused unstable MPU6050 connection. The IMU reading would freeze at a fixed value or return -1 randomly. Re-soldering and mechanical reinforcement were applied to stabilize the connection and fix the installation offset.
2. Loose power pads after vehicle fall caused accidental short-circuit on the board. The fuse overheated. After power-off inspection, both ST-Link and STM32 chip were damaged. The fuse was replaced, power traces re-soldered, and new STM32 & ST-Link were installed to recover the hardware.

### 3. PID Parameter Tuning & Encoder Failure
- Only angle loop: Easy to tune KP/KI/KD, but after pushing the car to generate speed, it cannot return to zero speed. The angle loop only keeps upright balance, with no control over translational speed.
- Add speed loop: Speed loop P=2. Larger P (3~4) brings faster response but introduces obvious oscillation, so P is set to 2. Speed loop I is used to eliminate steady-state drift. Ki must be kept very small, final value Ki=0.05. Larger Ki would amplify small swing.
- Add steering loop: After enabling the steering loop, unexpected spinning occurred at rest. Serial print of encoder data showed one wheel’s encoder reading stuck at 0, which suddenly increased the differential speed and triggered spinning, even though the motor itself rotated normally.
  Re-test with basic driver code confirmed encoder reading failure. Re-soldering and mechanical reinforcement fixed the encoder connection.
  Steering loop uses PI control. Final parameter: Kp=3, Ki=2. Larger parameters lead to excessive vibration.
- Additional protection: Integral limiting and integral separation were implemented to prevent integral accumulation when encoder signal is lost during collision or weak connection, and suppress low-speed jitter.

After hardware repair and parameter tuning, the vehicle can keep straight and turn stably.

## Hardware
PCB designed with **LCSC EasyEDA**.
Hardware files are located in `/hardware`.
- Schematic & PCB source file
- Schematic PDF and PCB preview image
- BOM list for component purchasing

## Build & Compile
1. Open `.uvprojx` project file in Keil MDK
2. Select target, compile and download
> Objects/ and Listings/ folders are generated after compilation and ignored by git.
