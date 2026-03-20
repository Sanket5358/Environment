Enviromental Monitoring System

[1]Overview
The Industrial Machine Monitoring System is a multi-process Linux application that simulates a real-time monitoring pipeline for environmental conditions in an industrial setup.
The system generates simulated sensor values such as **Temperature, Humidity, and Air Quality Index (AQI)**, processes the data, detects abnormal conditions, and logs system activity.
This project demonstrates several core Operating System concepts, including:
* Process creation and management
* Multithreading
* Inter-Process Communication (IPC)
* Signal handling
* File logging
* Modular software design

[2]Architecture
<img width="1024" height="1536" alt="image" src="https://github.com/user-attachments/assets/0ab2325a-44bf-477d-86c2-f06b2d40fe8a" />

    ↓
File → permanent storage
fork + exec → create processes  
Message Queue → sensor to processor  
Shared Memory → processor to display  
Semaphore → synchronization  
Pipe → display to logger  
Thread → display execution  
File I/O → logging  
Signal → shutdown

[3]System Workflow
1. Sensor Process
The Sensor process simulates environmental sensor inputs using random values.
Generated parameters:
* Temperature
* Humidity
* AQI
Each cycle, the sensor generates data and sends it to the processor.
Example:
[Sensor] Temp=25 Hum=60 AQI=120

2. Processor Process
The Processor receives sensor data and prepares it for further use.
Responsibilities:
* Receive data from Message Queue
* Store data into Shared Memory
* Synchronize using Semaphores
Example:
[Processor] Temp=25 Hum=60 AQI=120
Communication mechanism:
* Message Queue
* Shared Memory + Semaphore

3. Display Process
The Display process reads data from shared memory and shows real-time output.
It uses multithreading to continuously display data and check conditions.
Responsibilities:
* Display sensor values
* Generate alerts
* Send logs to logger via pipe
Example:
[Display] Temp=25 Hum=60 AQI=120
Alert rules:
* If temperature > 40 → High Temperature
* If AQI > 200 → Poor Air Quality
Example:
[Display ALERT] High Temperature!
[Display ALERT] Poor Air Quality!
Technologies used:
* POSIX Threads
* Shared Memory
* Semaphores

4. Logger Process
The Logger process records system output into a log file.
It receives data from the display process through a pipe and writes it to a file.
Log file:
* environment_log.txt`
Example log output:
[Display] Temp=48 Hum=59 AQI=267
[ALERT] High Temperature
[ALERT] Poor Air Quality
Communication mechanism:
* Pipe

[4]Technologies Used

| Component       | Technology                         |
| --------------- | ---------------------------------- |
| Language        | C                                  |
| Build System    | Makefile                           |
| Threading       | POSIX pthread                      |
| IPC             | Message Queue, Shared Memory, Pipe |
| Synchronization | POSIX Semaphores                   |
| Signal Handling | signal()                           |
| Logging         | File I/O                           |

[5]System Calls / APIs Used

| System Call      | Purpose                   |
| ---------------- | ------------------------- |
| fork()           | Create child processes    |
| execl()          | Execute programs          |
| wait()           | Process synchronization   |
| pthread_create() | Create threads            |
| mq_open()        | Create message queue      |
| mq_send()        | Send data                 |
| mq_receive()     | Receive data              |
| shm_open()       | Create shared memory      |
| mmap()           | Map shared memory         |
| sem_open()       | Create semaphore          |
| sem_wait()       | Lock resource             |
| sem_post()       | Unlock resource           |
| pipe()           | Create pipe communication |
| dup2()           | Redirect pipe streams     |
| signal()         | Handle signals            |
| open()           | Open file                 |
| write()          | Write logs                |
| lseek()          | File offset control       |


[6]Signal Handling
The Supervisor process handles signals for system control.
| Signal | Purpose                      |
| ------ | ---------------------------- |
| SIGINT | Graceful shutdown (Ctrl + C) |

Example:
^C
[Supervisor] Shutdown

[7]Project Structure
env_monitor
│
├── env_final.h
├── main_final.c
├── sensor_final.c
├── process_final.c
├── display_final.c
├── logger_final.c
├── Makefile
│
├── main_final
├── sensor_final
├── process_final
├── display_final
└── logger_final

[8]Build Instructions
Compile the project
Run the system:
make run
or
./main_final
Clean build files:
make clean

[9]Testing Scenarios
Normal Operation
* Temperature < 40
* AQI < 200

System runs normally without alerts.
High Temperature
* Temperature > 40
Output:
[Display ALERT] High Temperature!
Poor Air Quality
* AQI > 200
Output:
[Display ALERT] Poor Air Quality!
Critical Condition
* Temperature > 40 AND AQI > 200
Output:
[Display ALERT] High Temperature!
[Display ALERT] Poor Air Quality!

[10]Demo Steps

1. Build the project
make
2. Run the system
./main_final
3. Observe output
   Sensor → Processor → Display
4. Check logs
cat environment_log.txt
5. Stop system
   CTRL + C

[10]Reflection
What Worked Well
* Modular architecture
* Smooth IPC communication
* Proper synchronization using semaphores

Challenges Faced
* Synchronizing shared memory access
* Handling race conditions between processes
* Managing multiple IPC mechanisms

What We Learned
* Linux process management
* Inter-process communication
* Thread synchronization
* Signal handling
* System-level programming in C

[11]Author
Name:Sanket Chavan
Branch:Electronics and Telecommunication Engineering
Institute:AISSMS IOIT Pune
Project Type:Embedded Linux / Operating Systems Project

