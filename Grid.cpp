
/*------------------------------------------------------------------------
 *                                 Grid.cpp
 * ------------------------------------------------------------------------
 */


grid::grid(vector<vector<char>>& input) {
	constructGraph(input);
}


//Create graph with input file

void grid::constructGraph(vector<vector<char>>& input) {


	graph = input;


	//create nodes in graph:
	int rowSize = graph.size();
	int colSize = graph[0].size();
	for (int row = 0; row < rowSize; row++) {

		for (int col = 0; col < colSize; col++) {

			//if empty determine if e is a node.
			if (graph[row][col] == 'e' || graph[row][col] == 's'
				|| graph[row][col] == 'f' || graph[row][col] == 'b' ||
				graph[row][col] == 'g') {

				determineIfNode(row, col);

			}
		}

	}


}


//Determine if graph[row][col] is a node, or just empty path.
void grid::determineIfNode(int row, int col) {
	int  rowSize = graph.size();
	int  colSize = graph[0].size();
	int  totalEdges = 0;
	vector<char> edgeDirection;


	//if else latter to collect edges.
	//Check boundaries.
	if (row == 0) {
		if (graph[row + 1][col] != 'w') {
			totalEdges++;
			edgeDirection.push_back('D');
		}
	}
	if (row == rowSize - 1) {
		if (graph[row - 1][col] != 'w') {
			totalEdges++;
			edgeDirection.push_back('U');
		}
	}
	if (col == 0) {
		if (graph[row][col + 1] != 'w') {
			totalEdges++;
			edgeDirection.push_back('R');
		}
	}
	if (col == colSize - 1) {
		if (graph[row][col - 1] != 'w') {
			totalEdges++;
			edgeDirection.push_back('L');
		}
	}

	//if in the middle of the middle of the column
	if (row != 0 && row != (rowSize - 1)) {

		if (graph[row + 1][col] != 'w') {
			totalEdges++;
			edgeDirection.push_back('D');
		}

		if (graph[row - 1][col] != 'w') {
			totalEdges++;
			edgeDirection.push_back('U');
		}
	}

	//if a middle column
	if (col != 0 && col != (colSize - 1)) {
		if (graph[row][col + 1] != 'w') {
			totalEdges++;
			edgeDirection.push_back('R');
		}
		if (graph[row][col - 1] != 'w') {
			totalEdges++;
			edgeDirection.push_back('L');
		}

	}




	//Determine what's in edgeDirection
	bool lat = false;
	bool vert = false;
	if (totalEdges >= 2) {



		for (int i = 0; i < edgeDirection.size(); i++) {
			if (edgeDirection.at(i) == 'R' || edgeDirection.at(i) == 'L') {
				lat = true;
			}

			if (edgeDirection.at(i) == 'U' || edgeDirection.at(i) == 'D') {
				vert = true;
			}
		}

	}




	//Determine type of node
	//start node
	if (graph[row][col] == 's') {


		sourceNode = new node(col, row);
		//sourceNode->setPaths(edgeDirection);
		pair<int, int> coordinates(col, row);
		nodes[coordinates] = sourceNode;

		//add edges to node
		for (char c : edgeDirection) {
			sourceNode->childMap[c];
		}




	}
	//stop node
	else if (graph[row][col] == 'f') {


		stopNode = new node(col, row);
		//stopNode->setPaths(edgeDirection);
		pair<int, int> coordinates(col, row);
		nodes[coordinates] = stopNode;

		//add edges to node
		for (char c : edgeDirection) {
			stopNode->childMap[c];
		}




	}
	//bomb node
	else if (graph[row][col] == 'b') {
		node* tmpNode;
		tmpNode = new node(col, row);
		

		pair<int, int> coordinates(col, row);

		//add edges to node
		for (char c : edgeDirection) {
			tmpNode->childMap[c];
		}


		nodes[coordinates] = tmpNode;

		graph[row][col] = 'b';
	}
	//gold node
	else if (graph[row][col] == 'g') {
		node* tmpNode;
		tmpNode = new node(col, row);


		pair<int, int> coordinates(col, row);

		//add edges to node
		for (char c : edgeDirection) {
			tmpNode->childMap[c];
		}


		nodes[coordinates] = tmpNode;

		graph[row][col] = 'g';
	}
	//regular node
	else if (lat && vert) {

		node* tmpNode;
		tmpNode = new node(col, row);
		

		pair<int, int> coordinates(col, row);

		//add edges to node
		for (char c : edgeDirection) {
			tmpNode->childMap[c];
		}


		nodes[coordinates] = tmpNode;

		graph[row][col] = 'n';



	}
}


//Print the graph to console
void grid::print() {
	for (int r = 0; r < graph.size(); r++) {
		cout << "|";
		for (int c = 0; c < graph[0].size(); c++) {
			cout << " " << graph[r][c] << "  |";
		}
		cout << endl;
	}
}


//Connect the nodes to Childern.
void grid::connectGraph() {

	//find directions for all nodes.
	auto iterator = nodes.begin();


	while (iterator != nodes.end()) {


		auto pathIterator = iterator->second->childMap.begin();


		while (pathIterator != iterator->second->childMap.end()) {
			visitNode((iterator->second), pathIterator->first);
			pathIterator++;
		}
		iterator++;
	}

}


//find next node
void grid::visitNode(node* currNode, char direction) {

	int x_search = currNode->getX();
	int y_search = currNode->getY();


	//If latter to decide which direction to look.
	if (direction == 'U') {

		//Conidition to know when to stop looking.
		while (y_search > 0 && graph[y_search][x_search] != 'w') {
			y_search--;


			pair <int, int> currPosition(x_search, y_search);
			//if the current position is a node, then add node as a child of parameterized node.
			if (nodes.find(currPosition) != nodes.end()) {

				currNode->childMap[direction] = nodes[currPosition];
				return;
			}
		}
	}

	if (direction == 'D') {
		//Conidition to know when to stop looking.
		while (y_search < (graph.size() - 1) && graph[y_search][x_search] != 'w') {
			y_search++;


			pair <int, int> currPosition(x_search, y_search);
			//if the current position is a node, then add node as a child of parameterized node.
			if (nodes.find(currPosition) != nodes.end()) {

				
				currNode->childMap[direction] = nodes[currPosition];

				return;
			}
		}

	}

	if (direction == 'R') {
		//Conidition to know when to stop looking.
		while (x_search < (graph[0].size() - 1) && graph[y_search][x_search] != 'w') {
			x_search++;


			pair <int, int> currPosition(x_search, y_search);
			//if the current position is a node, then add node as a child of parameterized node.
			if (nodes.find(currPosition) != nodes.end()) {

				
				currNode->childMap[direction] = nodes[currPosition];

				return;
			}
		}
	}

	if (direction == 'L') {
		//Conidition to know when to stop looking.
		while (x_search > 0 && graph[y_search][x_search] != 'w') {
			x_search--;


			pair <int, int> currPosition(x_search, y_search);
			//if the current position is a node, then add node as a child of parameterized node.
			if (nodes.find(currPosition) != nodes.end()) {
				//currNode->addChild(nodes[currPosition]);
				currNode->childMap[direction] = nodes[currPosition];
				return;
			}
		}

	}
}
//Return the Manhatten Distance between two nodes.
int grid::ManhatDist(node* parent, node* child) {
	int x = abs(parent->getX() - child->getX());
	int y = abs(parent->getY() - child->getY());

	return x + y;

}

//Compute the total weight of a node
int grid::calculateWeight(node* parent, int dist) {
	return parent->getWeight() + dist;
}

