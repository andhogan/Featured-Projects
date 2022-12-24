#ifndef GRAPH_H__
#define GRAPH_H__

#include <vector>
#include <set>
#include <string>
#include <memory>
#include <queue>
#include "Edge.h"
#include "Node.h"

using namespace std;

class Graph {
private:
  bool directed;
  vector<shared_ptr<Node>> nodes;
  vector<shared_ptr<Edge>> edges;
  // The next two vectors may be used in your search algorithms.
  vector<shared_ptr<Edge>> search_edges;
  vector<shared_ptr<Node>> search_nodes;
  // The clock is used to set discovery/finish times. Increment it by
  // one every time a Node color changes to GRAY or BLACK.
  int clock;
public:
  // The first block of public members are implemented for you.
  Graph();
  ~Graph();
  vector<shared_ptr<Node>> getNodes();
  vector<shared_ptr<Edge>> getEdges();
  int getClock();
  void addNode(shared_ptr<Node> n);
  void addEdge(shared_ptr<Edge> e);
  void removeNode(shared_ptr<Node> n);
  void removeEdge(shared_ptr<Edge> e);
  bool isDirected();
  void setDirected(bool val);
  vector<shared_ptr<Edge>> sortLightestWeightEdges(set<shared_ptr<Edge>> edgeSet);
  void sortShortestDistanceToStart(vector<shared_ptr<Node>> queue);
  set<shared_ptr<Edge>> getAdjacentEdges(shared_ptr<Node> n);
  friend std::ostream &operator << (std::ostream& out, Graph graph);
  
  void Test_Dij(shared_ptr<Node> start);
  void Dijkstra(shared_ptr<Node> start);


  // clear resets all nodes to have WHITE color, with -1 discovery and
  // finish times and rank. Resets all edges to type
  // UNDISCOVERED_EDGE. It resets the graph clock to 0.
  void clear();

  // tick is an OPTIONAL debugging method. Use this after every time
  // you increment the clock. You might pass in a string
  // to describe what just happened. If you are having trouble,
  // consider using this function as a place to track your algorithm's
  // progress. Print out your graph on each tick. If you want to get
  // very fancy, you can output your graph in 'dot' format. This is
  // the same format we used in the B-Tree assignment for debugging.
  //
  // This function is 100% optional, though.
  void tick(string message);

  // dfs(start) runs a depth-first search from the indicated start
  // node, and explores all reachable nodes. This ignores unreachable
  // nodes. When this function returns, all explored nodes are colored
  // BLACK, all unreachable nodes are WHITE. All explored nodes have
  // correct discovery/exit time information. All edges have correct
  // edge types (unfollowed edges should remain UNDISCOVERED).
  //
  // For a DFS, mark nodes GRAY when we first discover them, and BLACK
  // when we exit (finish) them.
  void dfs(shared_ptr<Node> start);

  // bfs(start) runs a breadth-first search starting from the given
  // node. It sets the 'rank' value on all nodes to something
  // appropriate: -1 for unreachable nodes, 0 for the start node, 1
  // for nodes that are one edge from the start node, and so forth.
  //
  // For a BFS, mark nodes GRAY when they are enqueued, and BLACK when
  // they are dequeued.
  void bfs(shared_ptr<Node> start);

  // bfs(start, target) has the same requirements as the other version
  // of `bfs`, except this one stops after the target node is
  // reached. If found, the target node should be marked BLACK, and
  // its rank should be correctly set on exit. If it is not found, the
  // target node should remain WHITE with a rank of -1.
  void bfs(shared_ptr<Node> start, shared_ptr<Node> target);


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

#endif  // GRAPH_H__