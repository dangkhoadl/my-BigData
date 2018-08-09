
# Membership Protocol Assignment

## Project description
### Learning Objectives
- By completing this programming assignment, you will be able to:
	- Design, implement, and test your distributed failure detection protocol. (Related to objectives in Week 3)
	- Design, implement, and test your distributed membership protocol. (Related to objectives in Week 3)

### Overview

- All cloud computing systems need to run a membership protocol in order to detect process (node) failures, and to incorporate new and leaving nodes. This MP (Machine Programming assignment) is about implementing such a membership protocol, similar to one we discussed in class. Since it is infeasible to run a thousand cluster nodes (peers) over a real network, we are providing you with an implementation of an emulated network layer (EmulNet). Your membership protocol implementation will sit above EmulNet in a peer-to-peer (P2P) layer, but below an App layer. Think of this like a three layer protocol stack with Application, P2P, and EmulNet as the three layers (from top to bottom).

- We provide you template code for an emulation of a distributed system, along with some tests. Your goal is to write code (for the membership protocol) to make all these tests pass.

- C++ is required for this assignment. The template code is written in C++. It is one of the most commonly used languages in industry for writing systems code. For this, you will need at least C++11 (gcc version 4.7 and onwards).

## Directions
1. _Download the Assignment Materials_: Download [mp1_assignment.zip](https://spark-public.s3.amazonaws.com/cloudcomputing/assignments/mp1/mp1.zip). This zip file contains all the files you will need to complete this assignment, including the MP1 Specification Document (mp1_specifications.pdf) with step-by-step instructions for creating your membership protocol.
2. _Follow the MP1 Specification Document Instructions_: Unzip mp1_assignment.zip, locate the MP1 Specification Document instructions (mp1_specifications.pdf), and follow the instructions in that document to create the code for implementing a membership protocol..
3. _Test Your Program_: Test your programming assignment on your own machine by following the instructions in _Section 6 (How Do I Test My Code?)_ of the MP1 Specification Document.
4. _Submit Your Program for Grading_: When you are satisfied with your local test results, submit your assignment by following the instructions in _Section 6.4 (Submission Instructions)_ of the MP1 Specification Document. You will need to submit your programming assignment on the [Assignment: Gossip Protocol](https://www.coursera.org/learn/cloud-computing/programming/O4lWE/gossip-protocol) Submission Page.

### Evaluation
- This assignment is worth a total of 90 points. When you run the grader it tells you whether you passed all the tests (out of 90). See Section 6.2 of the MP1 Specification Document for additional information on grading.

## Project implementation
### Overviews
- 3 layers: Applcation, P2P, EmulNet
- Requirements:
	1. _Completeness_: All non-faulty process must detect: `join/leave/failure` from other nodes
	2. _Accuracy_: Keep high, completeness is more imporetant
- Implementation:
	+ All-to-all heartbeating
	+ Gossip-style heartbeating
	+ SWIM heartbeating (recommended)
### 3 Layers of the project
#### EmulNet(Dont modify)
```cpp
// - Called once by each node 
// init its own address(myaddr)
void *ENinit(Address *myaddr, short port);
```
```cpp
// send/receive called by a peer
// On receiving:
// 	  Enqueue receiving message
int ENsend(Address *myaddr, struct address *addr, string data);
int ENrecv(Address *myaddr, int (* enqueue)(void *, char *, int), struct timeval
*t, int times, void *queue);
```
```cpp
// Clean up EmulNet implementation
int ENcleanup();
```

#### Application(Dont modify)
- Run in synchronous periods(global variable)
- During periods
	+ some peers maby __started up__ or __crash-stop__
	+ For each peer alive: nodeLoop()
- nodeLoop()
	+ Implement in P2P layer
	+ receive all messages
	+ Check whether application has new waiting requests
#### P2P(!!! Write code here)
- This is the layer responsible for implementing the membership protocol
- P2P layer can be extended to provide functionalities like `file insert, lookup, remove` etc
```
MP1Node.cpp
MP1Node.h
```

### Debug
1. the code prints out debugging messages into dbg.log (format is node address [globaltime] message)
2. turn debugging on or off by commenting out the `#DEFINE DEBUGLOG` in stdincludes.h

### Starting code
- Two message types are currently defined for the P2P layer
	+ JOINREQ
		+ received by the introducer
		+ introducer = the first peer to join the system
	+ JOINREP
- The best place to start the implementation is to have the introducer reply to a JOINREQ with a JOINREP message

### What should be implemented?
- _All the code will go into the P2P layer in file MP1Node.{cpp,h}_
- Implement `nodeLoopOps()` and `recvCallBack()` (Both functions are invoked by nodeLoop() to periodically perform protocol routines)
- The functionalities the implementation must have:
	+ _Introduction_: 
		- Each new peer contacts a well-known peer (the introducer) to join the group
		- implemented through JOINREQ and JOINREP messages
		- Currently, JOINREQ messages reach the introducer, but JOINREP messages are not implemented
		- JOINREP messages should specify the cluster member list
		- The introducer does not need to maintain a list of all peers currently in the system; a partial list of fixed size can be maintained
	+ _Membership_:
		- Satisfy completeness all the time (for joins and failures)
		- Satisfy accuracy when there are no message delays or losses (high accuracy when there are losses or delays)
- _Notes_:
	+ Some of the things that you will probably need to modify are the struct member and enum MsgTypes in `Mp1Node.h`
	+ You need to handle the new message types in separate Process functions similar to `JOINREQ/JOINREP` for this	

### Logging
- Log.{cpp,h} has a LOG() function that prints out node status into a file named dbg.log
- `logNodeAdd()` and `logNodeRemove()`
	+ Whenever a process adds or removes a member from its membership list, make sure you use logNodeAdd and logNodeRemove to log these respectively
- These functions take two address parameters 
	+ pass the address of the recording process as the first parameter
	+  the address of the process getting added/removed as the second parameter

### Other Files
- `Params.{cpp,h}` contains the setparams() function:
	- Initializes several parameters at the simulator start
	- including the number of peers in the system(EN_GPSZ), and the global time variable globaltime, etc.
- `Member.cpp,h`
	- list some necessary definitions and declarations
	- See descriptions in the files
	- Avoid modifying these files


## Testing and Submitting
### Testing
- To compile the code, run `make`
- To execute the program run `./Application testcases/<test_name>.conf`
- conf file contain information about the parameters used by your application
```
MAX_NNB: val
SINGLE_FAILURE: val DROP MSG: val
MSG_DROP_PROB: val
```
+ MAX_NNB: max number of neighbors
+ SINGLE_FAILURE: one bit 1/0 variable that sets single/multi failure scenarios
+ MSG_DROP_PROB: message drop probability(between 0 and 1)
+ MSG_DROP: one bit 1/0 variable that decides if messages will be dropped or not

### Grading
- grader script Grader.sh
	+ tests your implementation of membership protocol in 3 scenarios
		1. Single node failure
		2. Multiple node failure
		3. Single node failure under a lossy network
	+ grades each of them on 3 separate metrics
		1. whether all nodes joined the peer group correctly
		2. whether all nodes detected the failed node (completeness) 
		3. whether the correct failed node was detected (accuracy)
- How Do I Run the Grader on My Computer
```bash
chmod +x Grader.sh
./Grader.sh
```

### Submit to Coursera
```bash
python submit.py
```
