#include "Graph.h"

#include <iostream>
#include <sstream>

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<shared_ptr<Node>> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<shared_ptr<Edge>> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  edges.push_back(e);
}
 
void Graph::removeNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  for (vector<shared_ptr<Node>>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}
 
void Graph::removeEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin();
       it != edges.end(); 
       it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

/*
Orders a set of edges into a vector, ordering edges 
according to their weights from min to max. 
Takes as input a set of adjacent edges 
(use with getAdjacentEdges())
*/
vector<shared_ptr<Edge>> Graph::sortLightestWeightEdges(set<shared_ptr<Edge>> edgeSet)
{
  vector<shared_ptr<Edge>> edgesMintoMax;
  while(edgeSet.size()>0)
  {
    float min_weight = INFINITY;
    shared_ptr<Edge> min_edge;
    set<shared_ptr<Edge>>::iterator eit = edgeSet.begin();
    for(; eit != edgeSet.end(); eit++)
    {
      shared_ptr<Edge> curr_edge = *eit;
      if (curr_edge->getWeight() < min_weight)
      {
        min_edge = curr_edge;
        min_weight = min_edge->getWeight();
      }
    }
    //Order return vector from min weight edge growing to max for the adjacent edges
    edgesMintoMax.push_back(min_edge);
    //Erase the edge from the set to prevent duplicates
    edgeSet.erase(min_edge);
  }
  return edgesMintoMax;
}

//Use with a Dijkstra's queue to sort unvisited vertices when a new distance is found. 
void Graph::sortShortestDistanceToStart(vector<shared_ptr<Node>> queue)
{}
//   vector<shared_ptr<Node>> nodesMintoMax;
//   while(queue.size()<0)
//   {
//     float min_distance = INFINITY;
//     shared_ptr<Node> minDisNode;
//     vector<shared_ptr<Node>>::iterator nit = queue.begin();
//     for(; nit != queue.end(); nit++)
//     {
//       shared_ptr<Node> curr_node = *nit;
//       if(curr_node->getDistance() < min_distance)
//       {
//         minDisNode = curr_node;
//         min_distance = minDisNode->getDistance();
//       }
//     }
//     //Order the new queue by the shortest distance from the current node to the next
//     //Shortest distance will be in the back, to prep for back() and pop_back() in Dijkstra's
//     queue.insert(queue.end(), minDisNode);

//     nit = std::find(queue.begin(), queue.end()-begin_count, minDisNode);
//     queue.erase(nit);

//     begin_count++;
//   }
// }

set<shared_ptr<Edge>> Graph::getAdjacentEdges(shared_ptr<Node> n) {
  // DONE FOR YOU
  set<shared_ptr<Edge>> ret;
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin(); it != edges.end(); it++) {
    shared_ptr<Edge> edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

/*Takes as input pointers to a starting node and a target node, 
and finds the lightest weight edge from start to target*/

void Graph::Test_Dij(shared_ptr<Node> start)
{
  clear();
  start->setDistance(0);
  PriorityQueue PQ;
  cout << "Unvisited Queue Before: \n\t";
  // for(auto it=unvisitedqueue.begin(); it != unvisitedqueue.end(); it++)
  // {
  //   shared_ptr<Node> n = *it;
  //   cout << n->getData() << " ";
  // }
  // cout << "\n";
  // sortShortestDistanceToStart(unvisitedqueue);
  // cout << "Unvisited Queue After: \n\t";
  // for(auto it=unvisitedqueue.begin(); it != unvisitedqueue.end(); it++)
  // {
  //   shared_ptr<Node> n = *it;
  //   cout << n->getData() << " ";
  // }

}
void Graph::Dijkstra(shared_ptr<Node> start)
{
  //First, clear the graph -- set all vertex distances to infinity and predecessors to null
  clear();

  //Set start node distance to 0
  start->setDistance(0);

  //Enqueue all vertices into a queue of unvisited vertices, 
  //sorting by least distance to the starting node in the back for back() and pop_back() functions.
  //Since the distance to the start node is 0, and everything else is INFINITY, 
  //we expect the start node to be at the "front" of the queue.
  PriorityQueue PQ;
  PQ.Insert(start);

  /* Debugging
  cout << "Priority Queue Beginning: \n" 
  << PQ.PeekData() 
  << ": " 
  << std::to_string(PQ.Peek()->getDistance())
  << "\n";
  */

  // while loop while items still remain in the unvisited queue
  while(PQ.Peek())
  {
    //Visit the node with the shortest distance, pop it from the queue. 
    shared_ptr<Node> curr_node = PQ.Peek();
    
    
    if(!PQ.Peek())
    {
      cout << "PQ Empty!\n";
      return;
    }
    else
    {
    cout << "Priority Queue Front: \n" 
    << PQ.PeekData() 
    << ": " 
    << std::to_string(PQ.Peek()->getDistance())
    << "\n";
    }
    curr_node->setColor(GRAY, 0);
    

    // //Define a vector of adjacent edges to the curr_node
    // //Iterate through the adjacent nodes
    set<shared_ptr<Edge>> adjEdges = getAdjacentEdges(curr_node);
    set<shared_ptr<Edge>>::iterator it = adjEdges.begin();
    cout << "Adjacent Edges to " << curr_node->getData() << ": \n";
    for(;it != adjEdges.end(); it++)
    {
      
      shared_ptr<Edge> curr_edge = *it;
      shared_ptr<Node> adj_node = curr_edge->getEnd();
      int edgeWeight = curr_edge->getWeight();
      int altPathDistance = curr_node->getDistance() + edgeWeight;
      cout << "\t" << adj_node->getData() << ": \n";
      cout << "\t  Distance: " << std::to_string(adj_node->getDistance()) << "\n";


      //If shorter path from start to adjacent is found,
      // update adjacent vertex's distance and predecessor:
      if(altPathDistance < adj_node->getDistance())
      {
        cout << "\tUpdating Distance of " << adj_node->getData() << "\n";
        adj_node->setDistance(altPathDistance);
        adj_node->setPredecessor(curr_node);
        cout << "\t  Distance: " << std::to_string(adj_node->getDistance()) << "\n";
        cout << "\t  Predecessor: " << adj_node->getPredecessor()->getData() << "\n";
      }
      if(adj_node->getColor() == WHITE)
      {
        adj_node->setColor(GRAY, 0);
        PQ.Insert(adj_node);
      }
    }
    //Done visiting this node, set to BLACK
     curr_node->setColor(BLACK, 0);
     shared_ptr<Node> removeNode = PQ.Remove();


  }
  cout << "\nResults: \n";
  for(auto it=nodes.begin(); it != nodes.end(); it++)
  {
    shared_ptr<Node> currNode = *it;
    shared_ptr<Node> predNode = currNode->getPredecessor();
    cout << currNode->getData()<< ": \n";
    cout << "  Distance: " << std::to_string(currNode->getDistance()) << "\n";
    if (currNode->getPredecessor())
    {
      cout << "  Predecessor: " << currNode->getPredecessor()->getData() << "\n";
    }
    else
    {
      cout << "  Predecessor: NULL\n";
    } 
  }
  return;
}

void Graph::clear() {
  clock = 0;
  // nodes is vector<Node*>
  // for (size_t i = 0; i < nodes.size(); i++) {
  // Node* n = nodes[i];
  // }
  vector<shared_ptr<Node>>::iterator it = nodes.begin();
  for (;it != nodes.end(); it++) {
    shared_ptr<Node> n = *it;
    n->clear();
  }
  vector<shared_ptr<Edge>>::iterator eit = edges.begin();
  for (;eit != edges.end(); eit++) {
    shared_ptr<Edge> e = *eit;
    e->setType(UNDISCOVERED_EDGE);
  }
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

void Graph::dfs(shared_ptr<Node> start) {
  //mark the node being started as GRAY
  start->setColor(GRAY, clock);

  //Create a set of adjacent edges to iterate through
  set<shared_ptr<Edge>> adjEdges = getAdjacentEdges(start);
  set<shared_ptr<Edge>>::iterator edgeit;

  //iterate through the set of edges
  for (edgeit = adjEdges.begin(); edgeit != adjEdges.end(); edgeit++)
  { //within each iteration, create a current edge from one of the edges in the set
      shared_ptr<Edge> curr_edge = *edgeit;
      if (start == curr_edge->getStart() && 
      (curr_edge->getEnd()->getColor() == GRAY || curr_edge->getEnd()->getColor() == BLACK))
      {//If statement adds typing to the edge
       //Checks: If the inserted start node is the same as the edge.start, come through here
       //Then check whether the end nodes have been encountered to set an appropriate typing for the edge.
          if (curr_edge->getStart()->isAncestor(curr_edge->getEnd()))
          { //If A is an ancestor of C, and C was fully explored,
            //then this is a forward edge from A to C
            curr_edge->setType(FORWARD_EDGE);
          }
          else 
          { //If A is not an ancestor of C, and C was fully explored,
            //then this is a cross edge.
            curr_edge->setType(BACK_EDGE);
          }
      }
      if (!directed && start == curr_edge->getEnd() && 
      (curr_edge->getStart()->getColor() == GRAY || curr_edge->getEnd()->getColor() == BLACK))
      { //If statement adds typing to the edge
        //Checks: If the graph is undirected, and inserted start node is the edge.end, come through here
        //Then check whether the start nodes have been encountered to set the typing.

          if (curr_edge->getEnd()->getRank() > curr_edge->getStart()->getRank())
          {//Rank is the level in a spanning tree that a node was found in
           //If the end rank is higher, this means A was discovered before C, and C was discovered while A is still GRAY
           //This is a back edge.
            curr_edge->setType(BACK_EDGE);
          }
          else 
          {//If an edge exists between A and C, and C was completely examined while A was still being searched,
           //This is a forward edge.
              curr_edge->setType(FORWARD_EDGE);
          }
      }
      if (start == curr_edge->getStart() && curr_edge->getEnd()->getColor() == WHITE)
      {//If at the starting vertex, and the end vertex is white, set normal tree edge, and recursively call on the end.
          curr_edge->setType(TREE_EDGE);
          curr_edge->getEnd()->setPredecessor(start);
          clock++;
          dfs(curr_edge->getEnd());
      }
      else if (!directed && start == curr_edge->getEnd() && curr_edge->getStart()->getColor() == WHITE)
      {//
          curr_edge->setType(CROSS_EDGE);
          curr_edge->getStart()->setPredecessor(start);
          clock++;
          dfs(curr_edge->getStart());
      }
  }
  clock++;
  start->setColor(BLACK, clock);
}

void Graph::bfs(shared_ptr<Node> start) {
  clear();
  vector<shared_ptr<Node>> queue;
  shared_ptr<Node> current = start;
  queue.insert(queue.begin() +0, start);
  start->setColor(GRAY, clock);
  start->setRank(0);
  set<shared_ptr<Edge>> ret;
  while (queue.size()>0)
  { //Iterate while nodes are still queued.
    current = queue.back();
    clock++;
    current->setColor(BLACK, clock);
    if (current->getPredecessor())
    {//If statement skipped on first iteration because we are at the starting node, and has no predecessor.
     //Each node after will have a pred and will set its rank based on the pred's rank.
        current->setRank(current->getPredecessor()->getRank() + 1);
    }
    queue.pop_back(); //pops current BLACK node from the stack, 
    //and proceeds to find another node from an adjacent edge. 
    ret = getAdjacentEdges(current);
    set<shared_ptr<Edge>>::iterator it;
    for (it = ret.begin(); it != ret.end(); it++)
    {//iterate through the set of current's adjacent edges
        shared_ptr<Edge> ter = *it; //select an edge from the set to analyze
        if (current == ter->getStart() && ter->getEnd()->getColor() == WHITE)
        {//If the node on the opposite end is WHITE, we have not visited it yet.
         //Insert it into the queue, mark it GRAY, and set its predecessor so that we can trace back.
         //If the node is GRAY or BLACK, we never enter these if statements: it would be redundant to do so. 
            queue.insert(queue.begin() + 0, ter->getEnd());
            clock++;
            ter->setType(TREE_EDGE);
            ter->getEnd()->setColor(GRAY, clock);
            ter->getEnd()->setPredecessor(current);
        }
        else if (directed && current == ter->getEnd() && ter->getStart()->getColor() == WHITE)
        {
            queue.insert(queue.begin() + 0, ter->getStart());
            clock++;
            ter->setType(TREE_EDGE);
            ter->getStart()->setColor(GRAY, clock);
            ter->getStart()->setPredecessor(current);
        }
        
    } 
    /*
    After all edges for the current node have been analyzed and marked GRAY, 
    we return to the beginning of while, pop another node from the stack and mark it BLACK, 
    look at its edges and mark unvisited nodes GRAY, add more nodes to the queue, 
    and continue until the queue is empty.
    */
  }
}

void Graph::bfs(shared_ptr<Node> start, shared_ptr<Node> finish) {
  clear();
  vector<shared_ptr<Node>> queue;
  shared_ptr<Node> current = start;
  queue.insert(queue.begin() +0, start);
  start->setColor(GRAY, clock);
  start->setRank(0);
  set<shared_ptr<Edge>> ret;
  while (queue.size()>0){
    current = queue.back();
    clock++;
    current->setColor(BLACK, clock);
    if (current->getPredecessor()){
        current->setRank(current->getPredecessor()->getRank() + 1);
    }
    queue.pop_back();
    if (current == finish)
    { //for this particular bfs, we're searching for a particular node. 
      //Once it has been found, we can return from the function.
        return;
    }
    ret = getAdjacentEdges(current);
    set<shared_ptr<Edge>>:: iterator it;
    for (it = ret.begin(); it != ret.end(); it++){
        shared_ptr<Edge> ter = *it;
        if (current == ter->getStart() && ter->getEnd()->getColor() == WHITE){
            queue.insert(queue.begin() + 0, ter->getEnd());
            clock++;
            ter->getEnd()->setColor(GRAY, clock);
            ter->getEnd()->setPredecessor(current);
        }
        else if (current == ter->getEnd() && ter->getStart()->getColor() == WHITE){
            queue.insert(queue.begin() + 0, ter->getStart());
            clock++;
            ter->getStart()->setColor(GRAY, clock);
            ter->getStart()->setPredecessor(current);
        }
    }
  }
}


// overloading operator << lets you put a Graph object into an output
// stream.
ostream &operator << (ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<shared_ptr<Node>>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
    shared_ptr<Node> n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<shared_ptr<Edge>>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++) {
    shared_ptr<Edge> e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness. 
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<shared_ptr<Node>> nodes = g->getNodes();
  vector<shared_ptr<Edge>> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it=nodes.begin(); it != nodes.end(); ++it) {
    shared_ptr<Node> n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\"" << textColor << "\" fillcolor=\"" << what(c) << "\"" << " ]" << endl;
  }
  
  string edgeColor = "black";
  for (auto it=edges.begin(); it != edges.end(); ++it) {
    shared_ptr<Edge> e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData() << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}

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