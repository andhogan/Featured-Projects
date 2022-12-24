// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <ctime>
#include <cmath>

// in order to access private members, we have to defeat the safety
// mechanisms. This is acceptable for unit testing, but not much
// else. It is also not portable because it is not supported by the
// C++ spec, and therefore might not work with all compilers.
#define private public
#include "../code/Graph.h"
#include "../code/Node.h"
#include "../code/Edge.h"

using namespace std;

class test_Graph : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
	}

};


// forward declaration of helpers. read and learn from them!
shared_ptr<Graph> buildGraphToClear();
shared_ptr<Graph> mkgraph();
shared_ptr<Node> find(shared_ptr<Graph> graph, string label);

// Unit Tests

//Graph Edge and Node Helper Tests
TEST_F(test_Graph, Graph_NodeDistanceHelpers){
  shared_ptr<Node> a(new Node("a"));
  shared_ptr<Node> b(new Node("b"));
  shared_ptr<Edge> ab(new Edge(a, b));
  a->distance = 0;
  ASSERT_EQ(a->distance, 0);
  b->setDistance(5);
  ASSERT_EQ(b->distance, 5); //testing the member var call
  ASSERT_EQ(b->getDistance(), 5); //testing the helper
  b->setPredecessor(a);
  ASSERT_EQ(b->getPredecessor(), a);
  b->clear();
  ASSERT_FALSE(b->getPredecessor());
}

TEST_F(test_Graph, Graph_EdgeWeightHelpers){
  shared_ptr<Node> a(new Node("a"));
  shared_ptr<Node> b(new Node("b"));
  shared_ptr<Edge> ab(new Edge(a, b));
  ab->weight = 3;
  ASSERT_EQ(ab->weight, 3);
  ab->setWeight(5);
  ASSERT_EQ(ab->weight, 5);
  ASSERT_EQ(ab->getWeight(), 5);
}

TEST_F(test_Graph, Node_ClearDistancePredecessor){
  shared_ptr<Node> n(new Node("some node"));
  shared_ptr<Node> p(new Node("some other node"));
  n->distance = 0;
  p->distance = 5;
  p->setPredecessor(n);
  ASSERT_EQ(n, p->getPredecessor());
  n->clear();
  p->clear();
  ASSERT_FALSE(n->getPredecessor());
  ASSERT_FALSE(p->getPredecessor());
  ASSERT_EQ(n->getDistance(), INFINITY);
  ASSERT_EQ(p->getDistance(), INFINITY);
}

TEST_F(test_Graph, Graph_ClearGraph_PlusClearDist){
  shared_ptr<Graph> g = buildGraphToClear();
  g->clear();
  ASSERT_EQ(g->clock, 0);

  for (auto it=g->nodes.begin(); it != g->nodes.end(); ++it) {
    shared_ptr<Node> n(*it);
    ASSERT_EQ(n->color, WHITE);
    ASSERT_EQ(n->discovery_time, -1);
    ASSERT_EQ(n->completion_time, -1);    
    ASSERT_EQ(n->rank, -1);
    //Now check for pred and distance resets
    ASSERT_FALSE(n->predecessor);
    ASSERT_EQ(n->distance, INFINITY);
  }
  for (auto it=g->edges.begin(); it != g->edges.end(); ++it) {
    shared_ptr<Edge> e(*it);
    ASSERT_EQ(e->type, UNDISCOVERED_EDGE);
  }
}

//Dijkstra's Tests

/**
 * Dijkstra's traverses a graph's nodes by iterating from the start node and 
 * moving to adjacent nodes depending on the shortest distance available, determined
 * by the weight of the edges connecting vertices.
 * When choosing between more than one node, the algorithm must have a means of
 * choosing to travel to the closest node -- 
 * i.e. the algorithm chooses to traverse the edge with the smallest weight.
 * A Min Priority Queue fits this implementation perfectly:
 * we eventually will meet each node in the graph iff each vertex is connected 
 * to at least one other by an edge. 
 * Thus, we can be confident that each node will appear in the queue, where
 * each node will queue based on the smallest distance from the start node.
 */

TEST_F(test_Graph, Dijkstra_PriorityQueue)
{//This PQ is taken and modified from assignment-6.
  shared_ptr<Node> a(new Node("a"));
  shared_ptr<Node> b(new Node("b"));
  shared_ptr<Node> c(new Node("c"));
  shared_ptr<Node> d(new Node("d"));

  a->distance = 0;
  b->distance = 2;
  c->distance = 6;
  d->distance = 4;

  PriorityQueue my_pq;
  
  my_pq.Insert(a);
  my_pq.Insert(b);
  my_pq.Insert(c);
  my_pq.Insert(d);

 /**
  * We can use a terminal output to determine that this works. 
  * In this example, a is the starting node with a distance of 0.
  * The queue's order should be a->b->d->c, with distances 0->2->4->6.
  */

  cout << "Expected PQ: a b d c\n";
  cout << "Order of PQ: ";
  cout << my_pq.PeekData() << " ";
  shared_ptr<Node> currNode = my_pq.Remove();
  cout << my_pq.PeekData() << " ";
  currNode = my_pq.Remove();
  cout << my_pq.PeekData() << " ";
  currNode = my_pq.Remove();
  cout << my_pq.PeekData() << " ";
  currNode = my_pq.Remove();
  cout << "\n";
}

/**
 * This tests the Dijkstra Algorithm itself. 
 * The test utilizes a graph implemented within the participation activity
 * located in the zyBook Ch 16.9.1 -- https://learn.zybooks.com/zybook/COLORADOCSPB2270C++Spring2022/chapter/16/section/9
 * The mkgraph() function located further below designs this graph.
 * Starting from A, we travel to the other 3 nodes in the graph,
 * documenting the distance from A to the other nodes and 
 * setting predecessors along the way as "breadcrumbs" for the trail.
 * Despite there being a direct edge from A->C, 
 * we find a shorter path from A->B->D->C
 */

TEST_F(test_Graph, Graph_DijkstraBasics)
{
  shared_ptr<Graph> g = mkgraph();
  g->clear();
  shared_ptr<Node> a = find(g, "a");
  ASSERT_TRUE(a);
  g->Dijkstra(a);
  cout << "\nResults: \n";
  for(auto it=g->nodes.begin(); it != g->nodes.end(); it++)
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
  cout <<"\033[1m\033[33mEND DijkstraBasics\033[37m\n";
}

/**
 * This variant of the Dijkstra's algorithm does not frontload all nodes into a queue.
 * The pseudocode in the zyBook implements nodes this way, but this is not necessary
 * for this particular implementation if we use a min priority queue.
 * Instead, this implementation will only queue nodes that we visit.
 * Thus, we would expect nodes that are not connected to any other vertex within the graph
 * to remain unvisited. As such, their distances would remain inf and predecessor would be NULL.
 */
TEST_F(test_Graph, Graph_Dijkstra_LonelyVertex)
{
  shared_ptr<Graph> g = mkgraph();
  //Initialize a node that will not be connected to any other nodes
  shared_ptr<Node> e(new Node("e")); 
  g->addNode(e);
  g->clear();
  shared_ptr<Node> a = find(g, "a");
  ASSERT_TRUE(a);
  g->Dijkstra(a);
  cout <<"\033[1m\033[33mEND LonelyVertex\033[37m\n";
}
/**
 * In a case where two nodes are equidistant from a node in the queue, 
 * the algorithm must make a choice regarding which to visit first.
 * The algorithm thus relies on the min priority queue implementation.
 * For this implementation, I prioritized a duplicate priority overtaking the lead.
 * For example, if a node "B" with a distance of 2 from "A" is already in the queue,
 * and a node "C" also has a distance of 2 from "A", "C" will take priority over "B"
 * and will be visited first.
 * 
 * In this graph, we equalize edge weights for AB and AC to 3.
 * We should expect the predecessors for C and B to be A now. 
 * D will still have predecessor B because it still costs less going from A->B->D
 * than from A->C->D.
 */
TEST_F(test_Graph, Graph_Dijkstra_SameDistanceChoice)
{
  shared_ptr<Graph> ret(new Graph());
  shared_ptr<Node> a(new Node("a"));
  shared_ptr<Node> b(new Node("b"));
  shared_ptr<Node> c(new Node("c"));
  shared_ptr<Node> d(new Node("d"));

  shared_ptr<Edge> ab(new Edge(a, b));
  shared_ptr<Edge> ac(new Edge(a, c));
  shared_ptr<Edge> bc(new Edge(b, c));
  shared_ptr<Edge> bd(new Edge(b, d));
  shared_ptr<Edge> cd(new Edge(c, d));
  shared_ptr<Edge> dc(new Edge(d, c));

  ret->addNode(a);
  ret->addNode(b);
  ret->addNode(c);
  ret->addNode(d);

  ret->addEdge(ab);
  ret->addEdge(ac);
  ret->addEdge(bc);
  ret->addEdge(bd);
  ret->addEdge(cd);
  ret->addEdge(dc);

  //ab and ac have the same edge weights, here
  ab->setWeight(3);
  ac->setWeight(3);
  bc->setWeight(5);
  bd->setWeight(1);
  cd->setWeight(9);
  dc->setWeight(2);

  ret->clear();

  ASSERT_TRUE(a);
  ret->Dijkstra(a);
  cout <<"\033[1m\033[33mEND SameDistanceChoice\033[37m\n";
}


/**
 * This test can be toyed with. 
 * Make your own graph, and see Dijkstra's Algorithm in action.
 */
TEST_F(test_Graph, Graph_Dijkstra_MakeYourOwnGraphtoRun)
{
  //Make a graph to any number of reasons
  shared_ptr<Graph> ret(new Graph());

  //Initialize nodes to insert
  shared_ptr<Node> a(new Node("a"));
  shared_ptr<Node> b(new Node("b"));

  //Initialize edges to connect nodes
  shared_ptr<Edge> ab(new Edge(a, b));
  shared_ptr<Edge> ba(new Edge(b, a));


  //Add nodes to the graph
  ret->addNode(a);
  ret->addNode(b);

  //Add edges to the graph
  ret->addEdge(ab);
  ret->addEdge(ba);

  //Set individual setting, particularly edge weights
  ab->setWeight(3);
  ba->setWeight(99);

  //This implementation does not rely on directedness. It's implied with the set of edges.
  ret->setDirected(true);


  //Clear the graph, then insert the start node into Dijkstra(shared_ptr<Node> start)
  ret->clear();
  ret->Dijkstra(a);
  cout <<"\033[1m\033[33mEND MakeYourOwnGraph\033[37m\n";
}

shared_ptr<Node> find(shared_ptr<Graph> graph, string label) {
  for (auto it=graph->nodes.begin(); it != graph->nodes.end(); ++it) {
    shared_ptr<Node> n = *it;
    if (n->data == label) {
      return n;
    }
  }
  return shared_ptr<Node>(NULL);
}

shared_ptr<Graph> mkgraph() 
{//mkgraph modeled from zyBook 16.9.1
  shared_ptr<Graph> ret(new Graph());
  shared_ptr<Node> a(new Node("a"));
  shared_ptr<Node> b(new Node("b"));
  shared_ptr<Node> c(new Node("c"));
  shared_ptr<Node> d(new Node("d"));

  shared_ptr<Edge> ab(new Edge(a, b));
  shared_ptr<Edge> ac(new Edge(a, c));
  shared_ptr<Edge> bc(new Edge(b, c));
  shared_ptr<Edge> bd(new Edge(b, d));
  shared_ptr<Edge> cd(new Edge(c, d));
  shared_ptr<Edge> dc(new Edge(d, c));

  ret->addNode(a);
  ret->addNode(b);
  ret->addNode(c);
  ret->addNode(d);

  ret->addEdge(ab);
  ret->addEdge(ac);
  ret->addEdge(bc);
  ret->addEdge(bd);
  ret->addEdge(cd);
  ret->addEdge(dc);

  ab->setWeight(3);
  ac->setWeight(7);
  bc->setWeight(5);
  bd->setWeight(1);
  cd->setWeight(9);
  dc->setWeight(2);

  ret->setDirected(true);

  return ret;
}

// ---------------------------------------------------------------- Helpers ---

shared_ptr<Graph> buildGraphToClear() {
  // make a Graph with wonky metadata. it is intended test clear().
  shared_ptr<Graph> g(new Graph());
  g->clock = 42;
  
  shared_ptr<Node> a(new Node("a"));
  a->color = GRAY;
  a->discovery_time = 1;
  a->completion_time = 4;
  a->rank = 0;
  shared_ptr<Node> b(new Node("b"));
  b->color = BLACK;
  b->discovery_time = 2;
  b->completion_time = 5;
  b->rank = 1;
  shared_ptr<Node> c(new Node("c"));
  c->color = WHITE;
  c->discovery_time = 3;
  c->completion_time = 6;
  c->rank=-1;

  shared_ptr<Edge> ab(new Edge(a, b));
  ab->type = TREE_EDGE;
  shared_ptr<Edge> bc(new Edge(b, c));
  bc->type = CROSS_EDGE;
  shared_ptr<Edge> ac(new Edge(a, c));
  bc->type = BACK_EDGE;

  a->predecessor = NULL;
  b->predecessor = a;
  c->predecessor = b;
  
  g->addNode(a);
  g->addNode(b);
  g->addNode(c);
  g->addEdge(ab);
  g->addEdge(bc);
  g->addEdge(ac);

  return g;
}

// shared_ptr<Graph> mkgraph_zyBook_16_9_1() 
//{
//   shared_ptr<Graph> ret(new Graph());
//   shared_ptr<Node> a(new Node("a"));
//   shared_ptr<Node> b(new Node("b"));
//   shared_ptr<Node> c(new Node("c"));
//   shared_ptr<Node> d(new Node("d"));

//   shared_ptr<Edge> ab(new Edge(a, b));
//   shared_ptr<Edge> ac(new Edge(a, c));
//   shared_ptr<Edge> bc(new Edge(b, c));
//   shared_ptr<Edge> bd(new Edge(b, d));
//   shared_ptr<Edge> cd(new Edge(c, d));
//   shared_ptr<Edge> dc(new Edge(d, c));

//   ret->addNode(a);
//   ret->addNode(b);
//   ret->addNode(c);
//   ret->addNode(d);

//   ret->addEdge(ab);
//   ret->addEdge(ac);
//   ret->addEdge(bc);
//   ret->addEdge(bd);
//   ret->addEdge(cd);
//   ret->addEdge(dc);

//   ab->setWeight(3);
//   ac->setWeight(7);
//   bc->setWeight(5);
//   bd->setWeight(1);
//   cd->setWeight(9);
//   dc->setWeight(2);

//   return ret;
// }


/*Legacy Tests
TEST_F(test_Graph, Graph_SetNodeColor){
  {
    shared_ptr<Node> n(new Node("some node"));
    n->color = BLACK;
    n->discovery_time = 10;
    n->completion_time = 11;
    n->setColor(WHITE, 18); // The 18 should be ignored
    ASSERT_EQ(n->color, WHITE);
    ASSERT_EQ(n->discovery_time, -1);
    ASSERT_EQ(n->completion_time, -1);
  }
  {
    shared_ptr<Node> n(new Node("some node"));
    n->color = WHITE;
    n->discovery_time = -1;
    n->completion_time = -1;
    n->setColor(GRAY, 18);
    ASSERT_EQ(n->color, GRAY);
    ASSERT_EQ(n->discovery_time, 18);
    ASSERT_EQ(n->completion_time, -1);
  }
  {
    shared_ptr<Node> n(new Node("some node"));
    n->color = GRAY;
    n->discovery_time = 10;
    n->completion_time = -1;
    n->setColor(BLACK, 18);
    ASSERT_EQ(n->color, BLACK);
    ASSERT_EQ(n->discovery_time, 10);
    ASSERT_EQ(n->completion_time, 18);
  }  
}

TEST_F(test_Graph, Graph_NodeGetDiscoInfo){
  shared_ptr<Node> n(new Node("some node"));
  n->color = GRAY;
  n->discovery_time = 10;
  n->completion_time = 18;
  n->rank = 4;
  int c, dt, ct, r;
  n->getDiscoveryInformation(c, dt, ct, r);
  ASSERT_EQ(c, GRAY);
  ASSERT_EQ(dt, 10);
  ASSERT_EQ(ct, 18);
  ASSERT_EQ(r, 4);
}

TEST_F(test_Graph, Graph_TestIfNodeIsSpanningTreeAncestor){
  shared_ptr<Node> a(new Node("a"));
  shared_ptr<Node> b(new Node("b"));  
  shared_ptr<Node> c(new Node("c"));
  shared_ptr<Node> e(new Node("e"));
  a->predecessor = shared_ptr<Node>(NULL);
  b->predecessor = a;
  c->predecessor = a;  
  e->predecessor = c;

  ASSERT_EQ(a->isAncestor(c), false);
  ASSERT_EQ(c->isAncestor(a), true);
  ASSERT_EQ(e->isAncestor(a), true);
  ASSERT_EQ(e->isAncestor(b), false);
}

TEST_F(test_Graph, Graph_SetSpanningTreePredecessor){
  shared_ptr<Node> a(new Node("a"));
  shared_ptr<Node> c(new Node("c"));
  shared_ptr<Node> e(new Node("e"));
  c->setPredecessor(a);
  e->setPredecessor(c);

  ASSERT_EQ(c->predecessor, a);
  ASSERT_EQ(e->predecessor, c);
}

TEST_F(test_Graph, Graph_DepthFirstSeartchNoTrarget){
  shared_ptr<Graph> g = mkgraph();
  g->clear();
  ASSERT_EQ(g->clock, 0);
  shared_ptr<Node> a = find(g, "a");
  ASSERT_TRUE(a); // sanity check my find function, "a" shouldn't be null
  g->dfs(a);
  ASSERT_GT(g->clock, 0); // clock should increment beyond zero
  ASSERT_EQ(a->color, BLACK); // start node should be fully explored
  ASSERT_EQ(a->discovery_time, 0); // start node discovered at t=0
  ASSERT_EQ(a->completion_time, 13); // should finish at exactly t=13
  int c, dt, ft, r;
  for (auto it=g->nodes.begin(); it != g->nodes.end(); ++it) {
    shared_ptr<Node> n(*it);
    ASSERT_TRUE(n);
    n->getDiscoveryInformation(c, dt, ft, r);
    ASSERT_EQ(c, BLACK); // all nodes should be fully explored
    ASSERT_GE(dt, 0); // discovered between 0 and 6 inclusive;
    ASSERT_LE(dt, 6);
    ASSERT_GE(ft, 7); // finish time between 7 and 13 inclusive
    ASSERT_LE(ft, 13); 
  }
  shared_ptr<Node> f = find(g, "f");
  shared_ptr<Node> d = find(g, "d");
  ASSERT_EQ(f->predecessor, d);
}

TEST_F(test_Graph, Graph_DepthFirstSeartchEdgeTypes){
  shared_ptr<Graph> g = mkgraph();
  g->clear();
  ASSERT_EQ(g->clock, 0);
  shared_ptr<Node> a = find(g, "a");
  ASSERT_TRUE(a); // sanity check my find function
  g->dfs(a); // run the DFS

  // declare vars to count number of each kind of edge
  int numFwd = 0;
  int numTree = 0;
  int numBack = 0;
  int numCross = 0;
  for (auto it=g->edges.begin(); it != g->edges.end(); ++it) {
    shared_ptr<Edge> e(*it);
    ASSERT_TRUE(e);
    if (e->getType() == FORWARD_EDGE) {
      numFwd++;
    } else if (e->getType() == TREE_EDGE) {
      numTree++;
    } else if (e->getType() == BACK_EDGE) {
      numBack++;
    } else if (e->getType() == CROSS_EDGE) {
      numCross++;
    }
  }

  // The classification of edges depends on traversal order & can't be
  // predicted at write-time, so test sums and inequalities instead.
  ASSERT_EQ(numTree + numFwd + numBack + numCross, 12);
  ASSERT_GE(numTree, 6);
  ASSERT_GT(numFwd, 0);  
  ASSERT_GT(numBack, 0); 
  ASSERT_EQ(numCross, 0);
}

TEST_F(test_Graph, Graph_BreadthFirstSearch){
  shared_ptr<Graph> graph = mkgraph();
  graph->clear();
  shared_ptr<Node> a = find(graph, "a");
  shared_ptr<Node> b = find(graph, "b");
  shared_ptr<Node> c = find(graph, "c");
  shared_ptr<Node> d = find(graph, "d");
  shared_ptr<Node> e = find(graph, "e");
  shared_ptr<Node> f = find(graph, "f");
  shared_ptr<Node> g = find(graph, "g");
  int color, dt, ft, rank;

  graph->bfs(a);
  a->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 0);
  b->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 1);
  c->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 1);
  e->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 1);
  d->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 2);
  g->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 2);
  f->getDiscoveryInformation(color, dt, ft, rank);
  ASSERT_EQ(rank, 3);
}

TEST_F(test_Graph, Graph_BreadthFirstSearchWithTarget){
  int color, dt, ft, rank;
  {
    shared_ptr<Graph> graph = mkgraph();
    graph->clear();
    shared_ptr<Node> c = find(graph, "c");
    shared_ptr<Node> f = find(graph, "f");
    graph->bfs(c, f);
    f->getDiscoveryInformation(color, dt, ft, rank);
    ASSERT_EQ(rank, 2);
  }
  {
    shared_ptr<Graph> graph = mkgraph();
    graph->clear();
    shared_ptr<Node> a = find(graph, "a");
    shared_ptr<Node> b = find(graph, "b");
    shared_ptr<Node> c = find(graph, "c");
    shared_ptr<Node> d = find(graph, "d");
    shared_ptr<Node> e = find(graph, "e");
    shared_ptr<Node> f = find(graph, "f");
    shared_ptr<Node> g = find(graph, "g");
    graph->bfs(c, b);
    b->getDiscoveryInformation(color, dt, ft, rank);
    ASSERT_EQ(rank, 3); // rank is 3 if graph is directed
  }
  {
    shared_ptr<Graph> graph = mkgraph();
    graph->setDirected(false);
    graph->clear();
    shared_ptr<Node> a = find(graph, "a");
    shared_ptr<Node> b = find(graph, "b");
    shared_ptr<Node> c = find(graph, "c");
    shared_ptr<Node> d = find(graph, "d");
    shared_ptr<Node> e = find(graph, "e");
    shared_ptr<Node> f = find(graph, "f");
    shared_ptr<Node> g = find(graph, "g");
    graph->bfs(c, b);
    b->getDiscoveryInformation(color, dt, ft, rank);
    ASSERT_EQ(rank, 1); // rank is 1 if graph is undirected
  }
  
}


*/