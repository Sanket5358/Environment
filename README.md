Industrial Machine Monitoring System
Overview
The Industrial Machine Monitoring System is a multi-process Linux application that simulates a real-time monitoring pipeline for environmental conditions in an industrial setup.
The system generates simulated sensor values such as **Temperature, Humidity, and Air Quality Index (AQI)**, processes the data, detects abnormal conditions, and logs system activity.
This project demonstrates several core Operating System concepts, including:

* Process creation and management
* Multithreading
* Inter-Process Communication (IPC)
* Signal handling
* File logging
* Modular software design
Architecture
The system follows a pipeline architecture:
Sensor → Processor → Display → Logger
System Workflow
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
```

Communication mechanism:

* Message Queue
* Shared Memory + Semaphore

---

### 3. Display Process

The Display process reads data from shared memory and shows real-time output.

It uses multithreading to continuously display data and check conditions.

Responsibilities:

* Display sensor values
* Generate alerts
* Send logs to logger via pipe

Example:

```id="ex3"
[Display] Temp=25 Hum=60 AQI=120
```

Alert rules:

* If temperature > 40 → High Temperature
* If AQI > 200 → Poor Air Quality

Example:

```id="ex4"
[Display ALERT] High Temperature!
[Display ALERT] Poor Air Quality!
```

Technologies used:

* POSIX Threads
* Shared Memory
* Semaphores

---

### 4. Logger Process

The Logger process records system output into a log file.

It receives data from the display process through a pipe and writes it to a file.

Log file:

* `environment_log.txt`

Example log output:

```id="ex5"
[Display] Temp=48 Hum=59 AQI=267
[ALERT] High Temperature
[ALERT] Poor Air Quality
```

Communication mechanism:

* Pipe

---

## 🧠 Technologies Used

| Component       | Technology                         |
| --------------- | ---------------------------------- |
| Language        | C                                  |
| Build System    | Makefile                           |
| Threading       | POSIX pthread                      |
| IPC             | Message Queue, Shared Memory, Pipe |
| Synchronization | POSIX Semaphores                   |
| Signal Handling | signal()                           |
| Logging         | File I/O                           |

---

## 🔧 System Calls / APIs Used

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

---

## 🚨 Signal Handling

The Supervisor process handles signals for system control.

| Signal | Purpose                      |
| ------ | ---------------------------- |
| SIGINT | Graceful shutdown (Ctrl + C) |

Example:

```id="ex6"
^C
[Supervisor] Shutdown
```

---

## 📁 Project Structure

```id="struct1"
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
```

---

## 🚀 Build Instructions

Compile the project:

```bash id="cmd1"
make
```

Run the system:

```bash id="cmd2"
make run
```

or

```bash id="cmd3"
./main_final
```

Clean build files:

```bash id="cmd4"
make clean
```

---

## 🧪 Testing Scenarios

### Normal Operation

* Temperature < 40
* AQI < 200

System runs normally without alerts.

---

### High Temperature

* Temperature > 40

Output:

```id="test1"
[Display ALERT] High Temperature!
```

---

### Poor Air Quality

* AQI > 200

Output:

```id="test2"
[Display ALERT] Poor Air Quality!
```

---

### Critical Condition

* Temperature > 40 AND AQI > 200

Output:

```id="test3"
[Display ALERT] High Temperature!
[Display ALERT] Poor Air Quality!
```

---

## 🎬 Demo Steps

1. Build the project

```bash id="demo1"
make
```

2. Run the system

```bash id="demo2"
./main_final
```

3. Observe output
   Sensor → Processor → Display

4. Check logs

```bash id="demo3"
cat environment_log.txt
```

5. Stop system
   CTRL + C

---

## 🧠 Reflection

### What Worked Well

* Modular architecture
* Smooth IPC communication
* Proper synchronization using semaphores

---

### Challenges Faced

* Synchronizing shared memory access
* Handling race conditions between processes
* Managing multiple IPC mechanisms

---

### What We Learned

* Linux process management
* Inter-process communication
* Thread synchronization
* Signal handling
* System-level programming in C

---

## 👨‍💻 Author

**Name:** Sanket Chavan
**Branch:** Electronics and Telecommunication Engineering
**Institute:** AISSMS IOIT Pune
**Project Type:** Embedded Linux / Operating Systems Project

---

