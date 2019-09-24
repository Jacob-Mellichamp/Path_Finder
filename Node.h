/*------------------------------------------------------------------------
 *                                 Node.h
 * ------------------------------------------------------------------------
 */



 /*
 Node Class:
   - Given a 2D grid, a node is defined as a point in the graph which
	 a 90 turn occurs
   - Node class Will Contain:
		 node parent: The node that connected to it.
		 char directionOfParent: determines the direction the parent came from
		 double distanceFromParent: determines distance away from parent
		 double distanceFromFinish: determines distance from finish
 */
class node {
private:

	int x;
	int y;
	node *parent;


	char directionOfParent;
	double distanceFromFinish;
	int weight;
	std::vector<char> totalPath;

public:

	//Constructors
	node(int x, int y) :
		x(x), y(y), weight(INT_MAX) {};


	node() : parent(nullptr), directionOfParent(' '), distanceFromFinish(0),
		weight(INT_MAX) {};


	//Map of neighbor node's (childern)
	//key: direction
	//value: node in that direction in memory
	std::map<char, node*> childMap;


	//Getters
	char getDirection()					{ return directionOfParent; }
	double getDistanceFinish()			{ return distanceFromFinish; }
	int getWeight()						{ return weight; }
	int getX()							{ return x; }
	int getY()							{ return y; }
	node* getParent()					{ return parent; }
	std::vector<char> getTotalPath()	{ return totalPath; }


	//Setters
	void setParent(node* par)						{ parent = par; }
	void setDistanceFromFinish(double finish)		{ distanceFromFinish = finish; }
	void setWeight(double dist)						{ weight = dist; }
	void setX(int x)								{ this->x = x; }
	void setY(int y)								{ this->y = y; }
	void addToPath(char c)							{ totalPath.push_back(c); }
	void addPaths(std::vector<char> parentPath, std::vector<char> currentPath) {

		totalPath.clear();
		totalPath.reserve(parentPath.size() + currentPath.size());
		totalPath.insert(totalPath.end(), parentPath.begin(), parentPath.end());
		totalPath.insert(totalPath.end(), currentPath.begin(), currentPath.end());
	}


	//create a comparision operator
	bool operator < (const node &rhs) const {
		return weight > rhs.weight;
	}
};


//Comparator class to compare nodes in dijkstra 
//priority_queue
class Comparator {
public:
	bool operator()(node* a, node* b)
	{
		return (a->getWeight() > b->getWeight());
	}
};

