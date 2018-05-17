

## MP1Node
- Message
```cpp
// Message Header
struct MessageHdr {
	// Message type
	enum MsgTypes msgType;
		// received by the introducer
		JOINREQ

		// introducer reply
	    JOINREP

	    // Heartbeat message
	    HEARTBEAT

	    // 
	    DUMMYLASTMSGTYPE
}

// Message Data
struct MessageData {
	int id;
	short port;
	long heartbeat;
}
```
- Node Data
```cpp
EmulNet *emulNet; 						// Emulation Net in EmulNet.{h,cpp}
	// EmulNet receive function
	int emulNet->ENrecv(Address *myaddr, int (* enq)(void *, char *, int), struct timeval *t, int times, void *queue);

	// EmulNet send function
	int emulNet->ENsend(Address *myaddr, Address *toaddr, char *data, int size);

Log *log; 								// Log 

Params *par;							// Parameters

Member *memberNode;						// all member nodes in Member.h
	// Status
		// indicating if this member is up
		bool memberNode->inited;

		// indicating if this member has failed
		bool memberNode->bFailed;

		// indicating if this member is in the group
		bool memberNode->inGroup;

	// Data
		// number of my neighbors
		int memberNode->nnb;

		// member's IP Address
		Address memberNode->addr;
			// Address in Member.h 
			class Address {
				// data struct: 
				//		addr[0-3]: IP
				//		addr[4-6]: Port
				char addr[6];

				// Constructors
				Address(string address);

				// return: to_string(id) + ":" + to_string(port)
				string getAddress();
			}

		// the node's own heartbeat
		long memberNode->heartbeat;

	// Counters
		// counter for next ping
		int memberNode->pingCounter;

		// counter for ping timeout
		int memberNode->timeOutCounter;

	// Data structure
		// Membership table
		vector<MemberListEntry> memberNode->memberList;
			// MemberListEntry in Member.h
			class MemberListEntry {
				// data struct
				int id;
				short port;
				long heartbeat;
				long timestamp;

				// function
				int getid();
				short getport();
				long getheartbeat();
				long gettimestamp();
				void setid(int id);
				void setport(short port);
				void setheartbeat(long hearbeat);
				void settimestamp(long timestamp);
			}
		// My position in the membership table
		vector<MemberListEntry>::iterator memberNode->myPos;

		// Queue for failure detection messages
		queue<q_elt> memberNode->mp1q;


char NULLADDR[6];						// NULL address(init = {0,0,0,0,0,0})
```

- Node Functions
```cpp
/**
 *   This function receives message from the network and pushes into the queue
 *   This function is called by a node to receive messages currently waiting for it
 */
int recvLoop();

/**
 *   Enqueue the message from Emulnet into the queue
 */
int enqueueWrapper(void *env, char *buff, int size);

/**
 *	 This function bootstraps the node
 * 	 All initializations routines for a member.
 * 	 Called by the application layer.
 */
void nodeStart(char *servaddrstr, short servport);

/**
 * 	 Find out who I am and start up
 */
int initThisNode(Address *joinaddr);

/**
 * 	 Join the distributed system
 */
int introduceSelfToGroup(Address *joinaddr);

/**
 *	 Wind up this node and clean up state
 *   
 *	 !!! Your code goes here !!!
 *
 */
int finishUpThisNode();

/**
 *   Executed periodically at each member
 * 	 Check your messages in queue and perform membership protocol duties
 */
void nodeLoop();

/**
 *   Check messages in the queue and call the respective message handler
 */
void checkMessages();

/**
 *   Message handler for different message types
 *   
 *	 !!! Your code goes here !!!
 *
 */
bool recvCallBack(void *env, char *data, int size);

/**
 *   Check if any node hasn't responded within a timeout period and then delete
 * 	    the nodes
 * 	 Propagate your membership list
 *   
 *	 !!! Your code goes here !!!
 *
 */
void nodeLoopOps();

/**
 *   Function checks if the address is NULL
 */
int isNullAddress(Address *addr);

/**
 * 	 Returns the Address of the coordinator
 */
Address getJoinAddress();

/**
 * 	 Initialize the membership list
 */
void initMemberListTable(Member *memberNode);

/**
 *   Print the Address
 */
void printAddress(Address *addr);


/*------------------------------------------------ My Implementations ------------------------------------------------*/
/**
 *  Check if address is the same as memberNode address
 */
bool isAddressTheSameAsMemberNodeAddress(Address *address);

/**
 * send JOINREP message. (reference: introduceSelfToGroup)
 */
void sendJoinRepMessage(Address *destinationAddr);

/**
 * 	send HeartBeat message. (reference: introduceSelfToGroup)
 */
void sendHeartBeatMessage(Address *destinationAddr);
```
