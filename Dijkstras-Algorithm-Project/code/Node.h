#ifndef NODE_H__
#define NODE_H__

#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

// Node colors are described at the bottom of the file.
#define WHITE 1
#define GRAY 2
#define BLACK 3

class Node {
private:
  string data;
  int color;           // WHITE, GRAY, or BLACK.
  int discovery_time;  // clock value when the node was discovered by search.
  int completion_time; // clock value when node was completely finished.
  int rank;            
  /* Number of steps from source node in a BFS. 0 means it was the source node. */
  float distance; //set to infinity when Dijkstra's begins, and reassign when finding a shorter path

  shared_ptr<Node> predecessor; 
  shared_ptr<Node> next;
  shared_ptr<Node> prev;
  // The predecessor node in the spanning tree, also use for Dijkstra's
  
public:
  // Public Node members in this block are implemented for you.
  Node(string s);
  ~Node();
  string getData();
  void setData(string s);

  int getRank();
  void setRank(int rank);

  int getColor();
  void setColor(int search_color, int time);

  float getDistance();
  void setDistance(float length);

  // Public Node methods to implement are below here.

  // clear sets the color to WHITE, 
  // the discovery/completion time and rank to -1, 
  // and sets the predecessor to NULL.
  void clear();



  

  

  // Sets the predecessor node in the spanning tree. The predecessor
  // node was the node that we were exploring when we first discovered
  // a node (e.g. it was WHITE when we found it).
  shared_ptr<Node> getPredecessor();
  void setPredecessor(shared_ptr<Node> other);
  shared_ptr<Node> getNext();
  void setNext(shared_ptr<Node> other);
  shared_ptr<Node> getPrev();
  void setPrev(shared_ptr<Node> other);


  /*
  Have you ever wondered when you type ' cout << "hello world!" << endl; ' what << means? 
  how is it implemented? these are operator methods that you can define for your classes. 
  Below is an example on how you can define << operator for this class and here we choose 
  to define it as passing the data of current node in string format to the stream, 
  which could later be like:
  
  Node mynode;
  cout << mynode;
  
  and that would print the data of the node. 
  You can define similar operators like +,-,* for you classes and define 
  what it means to sum two of this class's objects.
*/
  friend std::ostream &operator<<(std::ostream &out, Node node);
  void getDiscoveryInformation(int &thecolor, int &disco_time, int &finish_time, int &bfs_rank);
  bool isAncestor(shared_ptr<Node> other);
};

#endif // NODE_H__

/*

  Node color tells us if we have discovered a node, if we're in the
  middle of finishing a node, or if we've finished a node. They are:

  WHITE: Node has not yet been reached by the search.

  GRAY: Node has been reached by the search but is not yet complete.

  BLACK: Node has been completely explored.
 */
