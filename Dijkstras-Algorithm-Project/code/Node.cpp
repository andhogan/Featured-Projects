#include "Node.h"

Node::Node(string s) {
  // DONE FOR YOU
  data = s;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() 
{
  // DONE FOR YOU
  return data;
}

void Node::setData(string s) {data = s;}

float Node::getDistance(){return distance;}

void Node::setDistance(float dis){distance = dis;}

shared_ptr<Node> Node::getPredecessor(){return predecessor;}

void Node::setPredecessor(shared_ptr<Node> other) {predecessor = other;}

shared_ptr<Node> Node::getNext(){return next;}

void Node::setNext(shared_ptr<Node> other){next = other;}

shared_ptr<Node> Node::getPrev(){return prev;}

void Node::setPrev(shared_ptr<Node> other){ prev = other;}








void Node::clear() {
  this->color = WHITE;
  this->discovery_time = -1;
  this->completion_time = -1;
  this->rank = -1;
  this->predecessor = NULL;
  this->distance = INFINITY;
}












/*
UNUSED FUNCTIONS MOVE HERE
*/

int Node::getColor() {return color;}

void Node::setColor(int search_color, int time) {
  this->color = search_color;
  if (this->color == BLACK)
  {
    this->completion_time = time;
  }
  else if (this->color == GRAY)
  {
    this->discovery_time = time;
  }
  else
  {
    this->clear();
  }
}

int Node::getRank() {
  return rank;
}
void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}


bool Node::isAncestor(shared_ptr<Node> other) {
  shared_ptr<Node> current = this->predecessor;
  while(current)
  {//Loop until we reach a NULL pointer. This indicates the ancestor wasn't found
    if(current == other) {return true;}
    current = current->predecessor;

  }
  return false;
}

void Node::getDiscoveryInformation(int& thecolor, int& disco_time, int& finish_time, int& bfs_rank) {
  thecolor = this->color;
  disco_time = this->discovery_time;
  finish_time = this->completion_time;
  bfs_rank = this->rank;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}
