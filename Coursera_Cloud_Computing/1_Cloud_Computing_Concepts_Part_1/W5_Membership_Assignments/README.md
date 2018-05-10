
# Membership function Assignment

## Learning Objectives
- By completing this programming assignment, you will be able to:
	- Design, implement, and test your distributed failure detection protocol. (Related to objectives in Week 3)
	- Design, implement, and test your distributed membership protocol. (Related to objectives in Week 3)

## Overview

- All cloud computing systems need to run a membership protocol in order to detect process (node) failures, and to incorporate new and leaving nodes. This MP (Machine Programming assignment) is about implementing such a membership protocol, similar to one we discussed in class. Since it is infeasible to run a thousand cluster nodes (peers) over a real network, we are providing you with an implementation of an emulated network layer (EmulNet). Your membership protocol implementation will sit above EmulNet in a peer-to-peer (P2P) layer, but below an App layer. Think of this like a three layer protocol stack with Application, P2P, and EmulNet as the three layers (from top to bottom).

- We provide you template code for an emulation of a distributed system, along with some tests. Your goal is to write code (for the membership protocol) to make all these tests pass.

- C++ is required for this assignment. The template code is written in C++. It is one of the most commonly used languages in industry for writing systems code. For this, you will need at least C++11 (gcc version 4.7 and onwards).

## Directions
1. _Download the Assignment Materials_: Download [mp1_assignment.zip](https://spark-public.s3.amazonaws.com/cloudcomputing/assignments/mp1/mp1.zip). This zip file contains all the files you will need to complete this assignment, including the MP1 Specification Document (mp1_specifications.pdf) with step-by-step instructions for creating your membership protocol.
2. _Follow the MP1 Specification Document Instructions_: Unzip mp1_assignment.zip, locate the MP1 Specification Document instructions (mp1_specifications.pdf), and follow the instructions in that document to create the code for implementing a membership protocol..
3. _Test Your Program_: Test your programming assignment on your own machine by following the instructions in _Section 6 (How Do I Test My Code?)_ of the MP1 Specification Document.
4. _Submit Your Program for Grading_: When you are satisfied with your local test results, submit your assignment by following the instructions in _Section 6.4 (Submission Instructions)_ of the MP1 Specification Document. You will need to submit your programming assignment on the [Assignment: Gossip Protocol](https://www.coursera.org/learn/cloud-computing/programming/O4lWE/gossip-protocol) Submission Page.

## Evaluation
- This assignment is worth a total of 90 points. When you run the grader it tells you whether you passed all the tests (out of 90). See Section 6.2 of the MP1 Specification Document for additional information on grading.
