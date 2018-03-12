# Architecture #

### Authors ###
    * Jarosław Szumega
    * Wojciech Juszczak
    * Adam Superczyński
    
### Project description ###
The aim of this project is creating an autonomus robot which will be able to scan surrounding and detect obstacles.

### Architecture diagram ###

![Architecture diagram](architecture_diagram.jpg "architecture diagram ")

### Use of RTOS ###
In the project FreeRTOS will be used for following purposes:

#### Tasks ####

System will consist of three tasks:
1. Scanning  + servo movements
2. Robot movements
3. Sending data to application

First task should be launched periodically and have higher priority than second task. After detecting obstacle close to robot it should be able to break second task. Third task should have the lower priority.

First task would also go with updating custom array-like structure - the map that robot will have in the internal memory. It will be designed to store one of currently planned three state, so the size of individual cell can be optimized. It does not have to use all bits of integer number.

#### Semaphores / Mutexes ####

Mutex for synchronising writing / reading from map.