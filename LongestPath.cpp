// A C++ program to find longest Distance for latency calculation 
// in a DAG, representing a circuit.
#include <iostream> 
#include <limits.h> 
#include <vector>
#include <list> 
#include <stack> 

#define NINF INT_MIN 
using namespace std; 

/******************************************************************************/

/*Graph is represented using adjacency list. Every node of adjacency list 
  contains vertex number of the vertex to which edge connects.*/
class AdjacencyListNode { 
	int v;
public: 
	AdjacencyListNode(int v1) { v = v1; } 

	int getVertex() { return v; } 
}; 

/******************************************************************************/

/* Class to represent a graph using adjacency list representation */ 
class Graph { 
	int V; // Number of vertices

	// Pointer to an array which contains adjacency lists 
	list<AdjacencyListNode>* adj; 

	// A function for topologically sorting the graph 
	void topologicalSort(stack<int>& Stack, int v, bool visited[]); 

public: 
	Graph(int V) // Constructor 
	{
		this->V = V; 
		adj = new list<AdjacencyListNode>[V]; 
	}

	// function to add a new edge to graph 
	void addnewEdge(int u, int v)
	{
		AdjacencyListNode node(v); 
		adj[u].push_back(node); // Add v to u's list 
	}

	// find longest Distance from given source 
	void longestPath(int s, int dest); 

}; 

/******************************************************************************/

/* A recursive function topological sorting used by longestPath */
void Graph::topologicalSort(stack<int>& Stack, int v, bool visited[]) 
{ 
	// Marks current node as visited 
	visited[v] = true; 

	// Recurse for all the vertices adjacent to current vertex 
	for (auto i = adj[v].begin(); i != adj[v].end(); ++i) { 
		AdjacencyListNode node = *i; 
		if (!visited[node.getVertex()]) 
			topologicalSort(Stack, node.getVertex(), visited); 
	} 

	// Push current vertex to stack which stores topological sort 
	Stack.push(v); 
} 


/******************************************************************************/
/* Function to find longest Distance from a given vertex to given destination.
   It uses recursive topologicalSort() to get topological_sorting. */
void Graph::longestPath(int s, int dest) 
{ 
	stack<int> Stack; 
	int Dist[V]; 

	// Marks all the vertices as unvisited 
	bool* visited = new bool[V]; 
	for (int i = 0; i < V; i++) 
		visited[i] = false; 

	/* Calls the recursive function to store Topological 
	   Sort starting from all vertices one by one */
	for (int i = 0; i < V; i++) 
		if (visited[i] == false) 
			topologicalSort(Stack, i, visited); 

	/* Initializes Distances to all vertices as infinite value and 
	   Distance to source as 0 */
	for (int i = 0; i < V; i++) 
		Dist[i] = NINF; 
	Dist[s] = 0; 

	// Processes vertices in topological_order 
	while (!Stack.empty()) { 

		// Get the new next vertex from topological order 
		int u = Stack.top(); 
		Stack.pop(); 

		// Update Distances of all adjacent vertices 
		if (Dist[u] != NINF) { 
			for (auto i = adj[u].begin(); i != adj[u].end(); ++i) 
				Dist[i->getVertex()] = max(Dist[i->getVertex()], Dist[u]+1); 
		} 
	} 

	// Now, print the calculated longest Distance to destination excluding 2 NOPs
	cout << Dist[dest] - 2 ;
} 




/*---------------------------- MAIN -------------------------*/ 

// Driver program to test above functions 
int main() 
{ 
	// Create a graph given in the above diagram. 
	Graph g(17); 
	g.addnewEdge(0, 1); 
	g.addnewEdge(0, 2); 
	g.addnewEdge(0, 3); 
	g.addnewEdge(0, 8);
        g.addnewEdge(0, 13); 
	g.addnewEdge(1, 4); 
	g.addnewEdge(2, 5); 
	g.addnewEdge(2, 7); 
	g.addnewEdge(3, 4); 
	g.addnewEdge(4, 6); 
    	g.addnewEdge(5, 10);
    	g.addnewEdge(5, 12);
    	g.addnewEdge(6, 5);
    	g.addnewEdge(6, 9);	
	g.addnewEdge(7, 6); 
    	g.addnewEdge(7, 12);
    	g.addnewEdge(8, 7);
    	g.addnewEdge(8, 11);
    	g.addnewEdge(9, 11);
    	g.addnewEdge(10, 14);
    	g.addnewEdge(10, 13);
    	g.addnewEdge(11, 16);
    	g.addnewEdge(12, 9);
    	g.addnewEdge(12, 10);
    	g.addnewEdge(13, 14);
    	g.addnewEdge(14, 15);
    	g.addnewEdge(15, 16);
    
	int s = 0 , dest = 16; 
	//cin >>s >>dest;
	cout << "Following are longest Distances from "
			"source to output vertex \n"; 
	g.longestPath(s, dest); 

	return 0; 
} 
