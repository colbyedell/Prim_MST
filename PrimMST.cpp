#include <iostream>
#include <bits/stdc++.h>

class Graph {
  private:
    // V represents the number of vertices in the graph.
    int V;

    // Adjacency list representation: Pair of a neighbor vertex and a weight for every edge.
    std::list< std::pair<int, int> > *adj;

  public:
    // Parameterized constructor which allocates an adjacency list with the specified number of vertices.
    Graph(int V) {
      this->V = V;
      // This is an array of neighbor vertices and weights.
      adj = new std::list< std::pair<int, int> > [V];
    }

    // Function to add an edge to the graph.
    void addEdge(int sourceVertex, int destinationVertex, int edgeWeight) {
      // Insert an edge from the source vertex to the destination vertex with the given edge weight.
      adj[sourceVertex].push_back(std::make_pair(destinationVertex, edgeWeight));
      // Because this is an undirected graph, we should also insert an equivalent edge in the opposite direction.
      adj[destinationVertex].push_back(std::make_pair(sourceVertex, edgeWeight));
    }

    // Prints the minimum spanning tree using Prim's algorithm.
    void primMST() {
      // Create a priority queue (min-heap) that is essentially a list of vertices in the graph.
      // The pairs stored within this graph are in the form (timeToReach, vertexNumber).
      std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > vertices;

      // Create a vector to store traversal cost values for each vertex, initializing them all to INT_MAX (essentially infinity.)
      std::vector<int> values(V, INT_MAX);

      // Create a vector to store parent vertices for each vertex, initializing them all to -1 (indicating that they are null.)
      std::vector<int> parent(V, -1);

      // Create a vector to keep track of whether each vertex has been included in the minimum spanning tree, initializing them all to false.
      std::vector<bool> inMST(V, false);

      // Set the time to reach our source vertex to 0.
      values[0] = 0;

      // Declare an iterator which will iterate through every edge of the graph.
      std::list< std::pair<int, int> >::iterator adjIterator;
      
      // Push each vertex with its corresponding cost to the "vertices" priority queue. (Reminder: the syntax for the pairs in the queue is "costToReach, vertexNumber".)
      for(int i = 0; i < V; i++)
        vertices.push(std::make_pair(values[i], i));

      while(!vertices.empty()) {
        // Access the current minimum element in our "vertices" priority queue, which will be the top element, because we defined it as a min-heap.
        std::pair<int, int> v = vertices.top();
        // Pop the top element from our priority queue, which we've just stored in v.
        vertices.pop();

        // Iterate through every edge that starts at the vertex we're currently checking.
        for(int i = 0; i < adj[v.second].size(); i++) {
          // Initialize an iterator that will run through each edge from our adjacency list.
          adjIterator = adj[v.second].begin();
          // Advance the iterator to the appropriate edge.
          std::advance(adjIterator, i);
  
          // If the currently-stored cost to reach the destination vertex of the edge we're checking is greater than the weight of the current edge, and this destination vertex has not been previously explored, update the cost and parent of that vertex.
          if(values[adjIterator->first] > adjIterator->second && !inMST[adjIterator->first]) {
            values[adjIterator->first] = adjIterator->second;
            parent[adjIterator->first] = v.second;

            // Push the vertex we've just updated (with its updated cost) to the priority queue, essentially updating the cost to reach it.
            // We must do it in this way because the standard C++ priority queue does not have the ability to update priorities directly.
            // The original, infinite-cost vertices still remain in the priority queue, but they will simply skip over the contents of this if statement.
            vertices.push(std::make_pair(values[adjIterator->first], adjIterator->first));
          }

          // After checking each edge for the current vertex, set the current vertex's corresponding inMST value to true, indicating that the vertex has been explored.
          inMST[v.second] = true;
        }
      }

      // Print each vertex, and the corresponding parent in the MST used to reach it.
      for(int i = 0; i < V; i++) {
        if(parent[i] != -1) {
          // If the vertex has a valid parent, output the minimum spanning tree edge used to reach it.
          std::cout << parent[i] << " - " << i << std::endl;
        } 
      }
    }
};

int main() {
  
  // Graph from project specification document
  int V = 9;
  Graph g(V);

  g.addEdge(0, 1, 5);
  g.addEdge(0, 2, 9);
  g.addEdge(1, 4, 9);
  g.addEdge(1, 2, 12);
  g.addEdge(2, 3, 8);
  g.addEdge(2, 5, 2);
  g.addEdge(3, 4, 3);
  g.addEdge(3, 5, 7);
  g.addEdge(4, 7, 8);
  g.addEdge(4, 6, 5);
  g.addEdge(5, 6, 3);
  g.addEdge(6, 7, 15);
  g.addEdge(6, 8, 11);
  g.addEdge(7, 8, 10);
  g.primMST();
  
  
  /*
  // Graph from slide 17 of greedy-prime-priority-queue.pptx
  int V = 6;
  Graph g(V);

  g.addEdge(0, 1, 5);
  g.addEdge(0, 2, 6);
  g.addEdge(0, 3, 4);
  g.addEdge(1, 2, 1);
  g.addEdge(1, 3, 2);
  g.addEdge(2, 3, 2);
  g.addEdge(2, 4, 5);
  g.addEdge(2, 5, 3);
  g.addEdge(4, 5, 4);
  g.addEdge(3, 5, 4);
  g.primMST();
  */

  /*
  // Graph from https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/#
  int V = 9;
  Graph g(V);

  g.addEdge(0, 1, 4);
  g.addEdge(0, 7, 8);
  g.addEdge(1, 2, 8);
  g.addEdge(1, 7, 11);
  g.addEdge(2, 3, 7);
  g.addEdge(2, 5, 4);
  g.addEdge(2, 8, 2);
  g.addEdge(3, 4, 9);
  g.addEdge(3, 5, 14);
  g.addEdge(4, 5, 10);
  g.addEdge(5, 6, 2);
  g.addEdge(6, 7, 1);
  g.addEdge(6, 8, 6);
  g.addEdge(7, 8, 7);
  g.primMST();
  */
  
  return 0;
}