/*-------------------------------------------------------------------------
 *                                 pathfinder.cpp
 * ------------------------------------------------------------------------
 */


//finally, the master function. This function takes in a 2D char array and outputs the
//shortest path FINDING OPTIMIZIED GOLD and time it takes to run.
template<size_t rows, size_t cols>
vector<char> pathFinder(char(&input)[rows][cols]) {

	//time how long it takes to preform dijkstra's
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();


	//fill up 2D vector of char
	vector<vector<char>> tmp;
	tmp.resize(rows);

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			tmp[r].push_back(input[r][c]);
		}
	}

	//create testGrid
	grid master(tmp);

	//connect testGrid
	master.connectGraph();

	//preform dijkstra's algorithm on master
	vector<char> victory = master.dijkstra();

   


	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	master.print();
	cout << "shortest Path:";
	for (char i : victory) {
		cout << " " << i << ", ";
	}
	cout << endl;

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "It took me " << time_span.count() << " seconds." << endl;
	return victory;
}
