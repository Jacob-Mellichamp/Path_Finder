
/*------------------------------------------------------------------------
 *                                 Grid.h
 * ------------------------------------------------------------------------
 */


 /*
   Grid Class:
   -  Given a 2D grid from an input file, make a map representation of the grid.
   Include:
	 - map<node, node> : map that will contain a list of all nodes and nodes that
	 connect to them.
	 - sourceNode : node to start with.
	 - stopNode : node to stop  at/ finish node.
 */

using namespace std;

class grid {

private:


	//holds all nodes
	//key: coordinate x, y
	//value: node associated
	map<pair<int, int>, node*> nodes;
	node* sourceNode;
	node* stopNode;


	//Graph
	vector<vector<char>> graph;


	//private functions to create graph.
	void determineIfNode(int, int);
	int ManhatDist(node*, node*);
	int calculateWeight(node*, int);
	void visitNode(node*, char);

public:


	grid(vector<vector<char>>&);


	//Creating grid

	void constructGraph(vector<vector<char>>&);


	//connect nodes to eachother
	void connectGraph();


	//preform dijkstra's algorithm on constructed graph.
	vector<char> dijkstra();


	//print graph
	void print();
};
