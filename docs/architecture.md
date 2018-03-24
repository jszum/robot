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
1. Obstacle scanning
2. Handling commands from queue - robots movements / surrounding scanning
3. Sending data to application

First task should be launched periodically with high frequency and has the highest prority. After detecting obstacle close to robot it should be able to break second task and robot should stop. Third task should have the lower priority.

Second task would also go with updating custom array-like structure - the map that robot will have in the internal memory. It will be designed to store one of currently planned three state, so the size of individual cell can be optimized. It does not have to use all bits of integer number.

#### Semaphores / Mutexes ####

Mutex will be used for synchronising writing / reading from map, because robot will be using map for deciding about next movement and it will be also updating the map during work.

#### Queue ####

Robot will have queue in which commands will be buffered. Following command will be implemented:

* Go forward by specified length (equal to length of one field of the map),
* Turn right / left by 90 degrees (without additional movements),
* Scan surrounding (robots stops and turns around by 360 degrees with scanner active)


### Pinout ###
To be decided...