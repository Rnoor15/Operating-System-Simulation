# Operating-System-Simulation
 
Scheduling: your program should use preemptive priority scheduling.
 
All I/O-queues are FCFS.
 
Memory: your program should simulate paging memory management. When the new process starts running, its page #0 is loaded into memory. Later pages are added only when needed (when corresponding m command is used). If page needs to be loaded into memory but there is no place for it, swap from the RAM the least recently used page (it can belong to any process).
 
At the start, your program asks the user three questions:
#### How much RAM memory is there on the simulated computer? Your program receives the number in bytes (no kilobytes or words). I can enter any number up to 4000000000 (4 billions).
#### What is the size of a page/frame.
#### How many hard disks the simulated computer has? Enumeration of hard disks starts with 0.
 
After these questions are answered, the simulation begins. You program constantly listens for the user inputs. The user inputs signal some system events. Your program simulates the corresponding system behavior. The possible inputs are:
 
### A priority    
‘A’ input means that a new process has been created. This process has the priority priority. For example, the input A 2 means that a new process has arrived. This process has the priority of 2.
When a new process arrives, your program should create its PCB and allocate memory for it’s first page.
Also, when a new process is created your program should send it to the ready-queue or allow it to use the CPU right away.
When choosing a PID for the new process start from 1 and go up. Do NOT reuse PIDs of the terminated processes.
 
### t        
The process that currently uses the CPU terminates. It leaves the system immediately. Make sure you release the memory used by this process.
 
### d number file_name     
The process that currently uses the CPU requests the hard disk #number. It wants to read or write file file_name.
 
### D number  
The hard disk #number has finished the work for one process.
 
### m address   
The process that currently uses the CPU requests a memory operation for the address address.
 
### S r    
Shows what process is currently using the CPU and what processes are waiting in the ready-queue.
 
### S i      
Shows what processes are currently using the hard disks and what processes are waiting to use them. For each busy hard disk show the process that uses it and show its I/O-queue. Make sure to display the filenames for each process.
 
### S m   
Shows the state of memory. For each used frame display the process number that occupies it and the page number stored in it.
