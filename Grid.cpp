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


