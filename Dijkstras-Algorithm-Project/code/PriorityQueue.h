#ifndef PRIORITYQUEUE_H__
#define PRIORITYQUEUE_H__

#include <memory>
#include <string>
#include <vector>
#include "Node.h"
#include "Graph.h"

using namespace std;

// Edit this to flesh out the pq structure as appropriate. You may
// also add the function prototypes for anything else, and implement
// them in pq.cpp.
struct pq {
    string text;
    float priority;
    shared_ptr<pq> next;
};
class PriorityQueue {
public:
    // constructor, you should set all values in array to zero
    PriorityQueue();

    //deconstructor, you don't need to add anything here since you are gonna use smart pointers
    ~PriorityQueue();

    // init_priority_queue allocates memory for a pq structure (which you
    // are responsble for defining above. It is
    // completely up to you how this should work.
    shared_ptr<Node> InitPriorityQueue();

    // insert adds the given text to the queue, using the specified
    // priority. If there is a tie, the given string should be placed at
    // the back of the group that it ties with, so all other strings with
    // this priority will be removed first.
    void Insert(shared_ptr<Node> queue_node);

    // remove will access the highest priority element in the queue,
    // remove it from the queue, and return it. if the queue is empty it
    // should return the empty string.
    shared_ptr<Node> Remove();

    // ppek will access the highest priority element in the queue and
    // return it without modifying the queue. if the queue is empty it
    // should return the empty string.
    shared_ptr<Node> Peek();  
    string PeekData(); 

    //Helper Functions

    //Set Head of Queue
    void SetHead(shared_ptr<Node> head);

private:
    shared_ptr<Node> head;
    // you can add add more private member variables and member functions here if you need
};

#endif  // PRIORITYQUEUE_H__
