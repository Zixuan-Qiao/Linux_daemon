# Linux Daemon Process
Two Linux daemons are designed and implemented in this project. 

## Process of Creating Daemon Process
1. create child process with fork(), terminate parent process with exit(); 
2. make the child process a session leader with setsid(); 
3. change the working directory to / with chdir(); 
4. set access permission with umask();
5. close inheritied files with close();

## Functionality
**daemon.c**: creates a daemon process that records system time in timelog.txt every 5 seconds. 

**auxiliary.c**: create a daemon process that keeps the previously mentioned daemon running. It checks the length of timelog.txt every 5 seconds, if it's not increased, system() is called to restart daemon.

**start.sh**: used to start daemon and auxiliary automatically at boot. sh PATH/start.sh is added to /etc/profile. 

**timelog.txt**: the result. 

## Language
C/C++

## Author
Zixuan (Alex) Qiao

