#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(){
    head = shared_ptr<Node>(NULL);
}

PriorityQueue::~PriorityQueue(){
    // You don't need to add anything here
}

// Implement this after defining struct in .h file
shared_ptr<Node> PriorityQueue::InitPriorityQueue(){
    shared_ptr<Node> new_pq(new Node(""));
    SetHead(new_pq);
    return new_pq;
}

// Implement this second
void PriorityQueue::Insert(shared_ptr<Node> queue_node){
    // Initialize pointer nodes
    shared_ptr<Node> currNode = head;
    shared_ptr<Node> prevNode(NULL);

    // Check to see if a head node is present
    if(!currNode)
    {// If the queue is empty (no head is present), make this the head node
        head = queue_node;
        return;
    }

    // If there is a head, check to see whether this new node has lower distance, 
    // and set a new head
    if(queue_node->getDistance() <= currNode->getDistance())
    {
        queue_node->setNext(head);
        head = queue_node;
        return;
    }
    
    //Already checked the head, move nodes ahead.
    prevNode = currNode;
    currNode = currNode->getNext();

    // Compare the new node with the rest in the list, planning on inserting in the middle
    while(currNode)
    {// Loop while there is a node being looked at that is not NULL
        if(queue_node->getDistance() <= currNode->getDistance())
        {
            queue_node->setNext(currNode);
            prevNode->setNext(queue_node);
            return;
        }
        prevNode = currNode;
        currNode = currNode->getNext();

    }

    //If reached the end of the queue (currNode is NULL again),
    //Insert queue_node at the end. Back of the line!
    if(!currNode)
    {
        prevNode->setNext(queue_node);
        queue_node->setNext(NULL);
        return;
    }

}

// Implement this third
shared_ptr<Node> PriorityQueue::Remove(){

    if(!head)
    {//If the queue is empty, return a blank string ""
        return NULL;
    }
    //If the queue is not empty, return head node and set a new head
    // Save head text result
    shared_ptr<Node> min = head;

    // Set new head, which is head->next
    head = head->getNext();

    return min;

}

// Implement this last
shared_ptr<Node> PriorityQueue::Peek(){
    return head;    // replace this line with your own code
}

string PriorityQueue::PeekData()
{
    return head->getData();
}

//Helper Functions


void PriorityQueue::SetHead(shared_ptr<Node> head){
    this->head = head;
}