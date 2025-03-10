# Traffic Light Control System Report

## System Overview

The traffic light control system simulates and manages traffic at a four-way intersection with traffic signals in North-South (NS), South-North (SN), West-East (WE), and East-West (EW) directions. The system is designed using SystemC for event-driven simulation with three main components:

1. **CarMonitor**: Generates car arrival data

2. **TrafficLightServer**: Controls traffic lights based on car data

3. **TrafficLightMonitor**: Logs traffic light status changes

   

## Component Functions

### 1. CarMonitor

**Purpose**: Generate car arrival data for all four directions of the intersection.

**Key Functions**:

- Produces car arrival events (0-3 cars per direction) either randomly or from input file
- Manages data generation at 1-second intervals
- Notifies the system when new cars arrive through an event mechanism
- Outputs car arrival information to console

**Implementation Details**:

- Uses either random number generation or file input based on configuration
- Writes car arrival counts to output signals
- Notifies other components via `car_comming_event` with delta cycle delay (SC_ZERO_TIME)(delay is necessary, ensure that TrafficLightServer could receive car comming data from CarMonitor.)

### 2. TrafficLightServer

**Purpose**: Control traffic light signals based on car arrivals and waiting times.

**Key Functions**:
- Tracks car counts and waiting times for each direction
- Implements traffic flow control algorithm
- Updates traffic light signals based on current conditions
- Prioritizes directions with more traffic or excessive waiting times

**Traffic Control Algorithm**:

- Alternates between NS-SN and WE-EW directions based on traffic volume
- Implements maximum waiting time threshold (5 seconds) to prevent excessive delay
- Forces direction changes when waiting time exceeds threshold, and it will keep open up to forced_passing_time.
- Ensures green lights only appear when cars are present

**Implementation Details**:

- Listens for car arrival events from CarMonitor
- Updates internal car counters and waiting times
- Uses a binary direction flag (`now_green_direction`) to track current flow
- Implements forced passing time (3 seconds) when switching due to wait time violations

### 3. TrafficLightMonitor

**Purpose**: Monitor and log traffic light status changes.

**Key Functions**:
- Detects changes in traffic light signals
- Formats and outputs status information to console
- Optionally logs status changes to output file

**Implementation Details**:
- Sensitive to changes in all four traffic light signals

- Provides human-readable output (GREEN/RED) for each direction

- Timestamps all status changes

- Supports both console and file output

  

## Synchronization Mechanism

The system uses SystemC's event-driven architecture for synchronization:

1. **Event Notification**:
   - `CarMonitor` generates car arrival data every second
   - Notifies `TrafficLightServer` via `car_comming_event` with SC_ZERO_TIME delay
   - This delta cycle delay ensures signals are fully updated before processing
2. **Signal-Based Communication**:
   - Car arrival data flows from `CarMonitor` to `TrafficLightServer` via integer signals
   - Traffic light status flows from `TrafficLightServer` to `TrafficLightMonitor` via boolean signals
3. **Process Sensitivity**:
   - `TrafficLightServer` is sensitive to `car_comming_event`
   - `TrafficLightMonitor` is sensitive to changes in traffic light signals



## System Configuration

The system supports flexible configuration through command-line parameters:
- Simulation duration (required)
- Input file for car arrival data (optional)
- Output file for traffic light status logs (optional)



## Conclusion

This traffic light control system demonstrates effective use of SystemC's event-driven architecture for simulating a real-time control system. The three-component design separates concerns between data generation, control logic, and monitoring. The synchronization mechanism ensures proper data flow and timing between components, creating a realistic simulation of traffic light control at an intersection.

[Github repository](https://github.com/1carusalwayswa/TDTS07/tree/main/lab1/traffic)

