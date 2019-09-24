/*-------------------------------------------------------------------------
 *                                 dijkstra.cpp
 * ------------------------------------------------------------------------
 */


 //Preform dijkstra on the Grid.h 'graph' and return the shortest path via vector.

vector<char> grid::dijkstra() {


	//hold finalPath in vector finalPath, create queue of nodes
	vector<char> finalPath;
	priority_queue<node*, vector<node*>, Comparator> queue;


	queue.push(sourceNode);
	sourceNode->setWeight(0);

	//preform dijkstra
	while (!queue.empty()) {


		//pop first node in list.
		node* top = queue.top();
		queue.pop();


		//if top == stopNode then shortestPath has been reached.
		if (top == stopNode) {
			return stopNode->getTotalPath();
		}


		//Go to each child
		auto iterator = top->childMap.begin();
		while (iterator != top->childMap.end()) {

			
			//Don't add null childern to the queue
			if (iterator->second != nullptr) {

				int row = iterator->second->getY();
				int col = iterator->second->getX();

				//Calculate Weight
				int dist = ManhatDist(top, iterator->second);
				int totalWeight = calculateWeight(top, dist);

				//if the node is value 'b' add 20 to the totalWeight
				if (graph[row][col] == 'b') {
					totalWeight += 20;
				}

				//if the node is value 'g' subtract 3 from the totalWeight
				if (graph[row][col] == 'g') {
					totalWeight -=3;
					//set graph position to equal ' ' so no repeats
					graph[row][col] = ' ';
	
				}


		

				//Don't add yourself if your path is worse that previous
				if (totalWeight < iterator->second->getWeight()) {


					//Set Weight
					iterator->second->setWeight(totalWeight);


					//Set Parent of child to top
					iterator->second->setParent(top);


					//Calculate Path
					vector<char> localPath;
					for (int i = 0; i < dist; i++) {
						localPath.push_back(iterator->first);
					}
					iterator->second->addPaths(top->getTotalPath(), localPath);


					//add to queue
					queue.push(iterator->second);
				}




			}


			iterator++;

		}


	}


	return finalPath;
}
