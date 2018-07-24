# include<iostream>
# include <queue>
using namespace std;

class BitMatrixGraph                                // create graph class.
{
private:
	unsigned char** bitAdjacencyMatrix;				// bit representation matrix.
	int n;											// number of nodes in the graph.
	int size;										// number of bytes per row.
public:
	BitMatrixGraph();                                    // default constructor.
	BitMatrixGraph(int numNodes);                        // non-default constructor.
	BitMatrixGraph(const BitMatrixGraph& otherGraph);
	virtual ~BitMatrixGraph();                           // destructor.
	void addEdge(int u, int v);
	bool isAnEdge(int u, int v);
	friend ostream &operator << (ostream &output, BitMatrixGraph &bmg);
	void operator =(const BitMatrixGraph& otherGraph);
	void copy(const BitMatrixGraph& otherGraph);
	int BFS(int i);                                     // breadth first search.
	int DFS(int i);                                     // depth first search.
};

ostream & operator << (ostream &output, BitMatrixGraph &bmg)   // Define the ostream operator "<<" for the purpose of... 
															   // BitAjacencyMatrix output. 
{
	for (int i = 0; i < bmg.n; i++) {
		for (int j = 0; j < bmg.size; j++) {
			for (int k = 0; k < 8; k++) {
				if (bmg.bitAdjacencyMatrix[i][j]&(0x01 << (7 - k)))      // print bits.
					output << 1;
				else
					output << 0;
			}
			output << endl;
		}
	}
		return output;
}

void BitMatrixGraph::operator=(const BitMatrixGraph& otherGraph)    //overloaded "=" assignment operator. 
{
	copy(otherGraph);												//using copy() method.
}

void BitMatrixGraph::copy(const BitMatrixGraph& otherGraph)      //copy constructor.
{
	n = otherGraph.n;
	size = otherGraph.size;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < size; j++)
			bitAdjacencyMatrix[i][j] = otherGraph.bitAdjacencyMatrix[i][j];
	}
}

BitMatrixGraph::BitMatrixGraph(){}								// default constructor.

BitMatrixGraph::~BitMatrixGraph() {}							// destructor.

BitMatrixGraph::BitMatrixGraph(const BitMatrixGraph& otherGraph) {} // non-default constructor.

BitMatrixGraph::BitMatrixGraph(int numNodes)					// create a graph matrix with "numNodes" number of nodes.
{
	n = numNodes;
	if (numNodes % 8 == 0)
		size = numNodes / 8;
	else
		size = (int)(n / 8) + 1;

	unsigned char** bitAdjacencyMatrix;                        // create a bit representation matrix.
	bitAdjacencyMatrix = new unsigned char*[numNodes];
	for (int i = 0; i < n; i++) {
		bitAdjacencyMatrix[i] = new unsigned char[size];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < size; j++) 
		bitAdjacencyMatrix[i][j] = 0x00 << 8;                 // intialize all to be 0.
	}
}

void BitMatrixGraph::addEdge(int u, int v)                   // create an edge between vertex u and v.
{
	int index;
	int pos;
	    // set postion (u,v) to be 1;
	if (v % 8 == 0) {
		index = v / 8;
		pos = 7;
		bitAdjacencyMatrix[u][index] = 0x01 << pos;
	}
	else {
		index = (int)(v / 8) + 1;
		pos = 7-(v % 8);
		bitAdjacencyMatrix[u][index] = 0x01 << pos;
	}
	    // set postion (v,u) to be 1;
	if (u % 8 == 0) {
		index = u / 8;
		pos = 7;
		bitAdjacencyMatrix[v][index] = 0x01 << pos;
	}
	else {
		index = (int)(u / 8) + 1;
		pos = 7-(u % 8);
		bitAdjacencyMatrix[v][index] = 0x01 << pos;
	}
}

bool BitMatrixGraph::isAnEdge(int u, int v)             // check whether vertex u and v are connected or not.
{
	int index, pos;
	if (v % 8 == 0) {
		index = v / 8;
		pos = 7;
		if (bitAdjacencyMatrix[u][index]& (0x01 << pos))
			return true;
		else
			return false;
	}
	else {
		index = (int)(v / 8) + 1;
		pos = 7-(v % 8);
		if (bitAdjacencyMatrix[u][index]& (0x01 << pos))
			return true;
		else
			return false;
	}
}

int BitMatrixGraph::BFS(int i)			// create a breadth first search (BFS) function.
{
	std::vector<bool> visited(n, false); //initiate a boolean vector, set all false.
	std::queue<int> Q;
	std::vector<int> parentnodes(n); // create an integer vector to to store parent nodes. 
	visited[i] = true;
	parentnodes[i] = -1;             // set the i position euqal to -1 since it is the root, no parent node.
	Q.push(i);

	while (!Q.empty) {
		int top = Q.front(); Q.pop();   // take the top node in the queue to analyze and remove it off the queue.
		for (int j = 0; j < n; j++) {
			if (isAnEdge(top, j) && (!visited[j])) {
				Q.push(j);
				parentnodes[j] = top;   //set position j to number top, which is j's parent node.
				visited[j] = true;
			}
		}	
	}
	for (int k=0; k<n;k++)                
	cout << parentnodes[k] << endl;      // output the parent nodes in an array.
}

int BitMatrixGraph::DFS(int i)			  // create a depth first search (DFS) function.
{
	std::vector<bool> visited(n, false);  // initiate a boolean vector, set all false.
	std::queue<int> Q;
	std::vector<int> parentnodes(n);      // create an integer vector to to store parent nodes. 
	visited[i] = true;
	parentnodes[i] = -1;                 // set the i position euqal to -1 since it is the root, no parent node.
	Q.push(i);

	while (!Q.empty) {
		int top = Q.front(); Q.pop();     // take the top node in the queue to analyze and remove it off the queue.
		for (int j = 0; j < n; j++) {
			if (isAnEdge(top, j) && (!visited[j])) {
				Q.push(j);
				parentnodes[j] = top;    //set position j to number top, which is j's parent node.
				visited[j] = true;
			}
			break;                      // jump out of the loop.
		}
	}
	for (int k = 0; k<n; k++)           // output the parent nodes in an array.
		cout << parentnodes[k] << endl;
}

int main()
{	
		int numbernode, u, v, i=0;
		std::cin >> numbernode;       // Redirected input.
		cout << "Total number of nodes within the graph is: " << numbernode << endl;
		BitMatrixGraph* bmg;
		bmg = new BitMatrixGraph(numbernode);

		while (!cin.eof()) {         // read in edges from the second line in the file.
			if (i = 0) {			// skip the first line when adding edges.
				i++;
			}
			else {
				std::cin >> u >> v;  
				bmg->addEdge(u,v);   // set edge between vertice u and v.
			}
		}

		bmg->BFS(0);  // perform a breadth first search on the graph starting from node 0, and output parent nodes.
		bmg->DFS(0);  // perform a depth first search no the graph starting from node 0, and output parent nodes.

	return 0;
}