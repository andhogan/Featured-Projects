# Dijkstra's Algorithm
CSPB2270 Final Project

by Andrew Hogan


<hr>

### What is the purpose of this project?
The purpose of this project is to extend our recent Graphs project by implementing Dijkstra's algorithm.

Dijkstra's algorithm is an algorithm used for finding the shortest path between nodes in a graph. These nodes can represent various kinds of networks, such as roadways, telecommunication traffic, social relationships, various uses in video games, and more. 

Dijkstra's algorithm begins with a source node and target node as inputs. Using edge weights between vertices in a graph, the algorithm seeks to find the shortest/lightest/least difficult path from the source node to the target. The weights in a graph indicate varying degrees of quality depending on the context. For example, for a graph of roadways, edge weights may indicate anything from distance from one node to another, or conversely the amount of time it would take to traverse from one to another. As an example of these, modern day GPS tracking usually provides common users with many of these "least path" decisions given current traffic conditions when a user inputs an address to travel to. A user could choose to travel the shortest distance, saving them gas, but perhaps not necessarily time, and vice versa. [1]

Dijkstra's algorithm  determines the shortest path between a given start node and the remaining nodes in the path. Many variants exist for the algorithm for different use cases, but my algorithm keeps to the basics and provides a visual terminal output of nodes and their predecessors, allowing us to visualize the shortest path from start to every other node. 

### How will the project be evaluated?

I plan on implementing unit tests detailing many cases that Dijkstra's algorithm could encounter and discussing what these tests indicate and why they matter for a particular implementation. Many of these tests seek to determine the behavior of the algorithm given cases where edge weights may be the same, or nodes are equal in distance from the starting node, and how the Priority Queue implemented to organize Dijkstra's queue determines priority and tiebreakers in these instances. I've used a mixture of assert statements along with terminal output to visualize (and debug) the algorithm. The unit tests utilize and modify the graph implemented in our semester's text [2].

Execution of the algorithm is very simple. For the sake of time, I have only modified .h and .cpp files for Node, Edge, Graph (assignment-9), and Priority Queue (assignment-6). After making these modifications, I've simply run a make file and execute ./run_tests to see the output of the unit tests, and reviewing code and test files to see how the implementation works. 

### Sources

[1] Dijkstra's algorithm - Wikipedia -- https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
* Broad grasp of information regarding the algorithm, including complexity time, use cases, some pseudocode, and variants.

[2] zyBook Chapter 16.9 -- https://learn.zybooks.com/zybook/COLORADOCSPB2270C++Spring2022/chapter/16/section/9
* Inspiration for primary pseudocode and test case functions. Implemented the graph detailed in 16.9.1 and modified it for various test cases.
