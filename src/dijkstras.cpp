/*************************************
 * John Turner Heath & Blake Milstead
 * COSC302 3/24/23
 * Dijkstras.cpp
 * Takes in a tilemap and applies
 * Dijkstra's algorithm to find the 
 * shortest path between a start and
 * target tile, and printing the cost
*************************************/
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <climits>
using namespace std;
// Main Execution

int main(int argc, char *argv[]) {
    int num_of_tiles, tile_weight, map_rows, map_cols;
    int start_row, start_col, end_row, end_col;
    char tile_name;
    map<char, int> tiles; //different tile types; key=name val=weight

    //Taking the different tile types from std input and adding to map
    cin >> num_of_tiles;
    for (int i=0; i<num_of_tiles; i++) {
        cin >> tile_name >> tile_weight;
        tiles.insert(pair<char,int>(tile_name,tile_weight));
    }

    //Taking in the map
    cin >> map_rows >> map_cols;
    int map_size = map_rows*map_cols;
    int *tile_map = new int[map_size];

    for (int i=0; i<map_size; i++) {
        cin >> tile_name;
        tile_map[i] = tile_name;
    }

    //Runner start and end positions
    cin >> start_row >> start_col >> end_row >> end_col;
    int start_index = (start_row * map_cols) + start_col;
    int end_index   = (end_row * map_cols) + end_col;

    //Start of dijkstras algorithm

    //This priority queue allows multiple insertions of the same index, but will only output
    //the insertion with minimum weight, this is useful in finding alt. paths to tiles
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq; 
    int *distance = new int[map_size];
    int *previous = new int[map_size];

    for (int i=0; i<map_size; i++) {
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    //start tile is initialized in distance and pushed into the pq
    distance[start_index] = tiles.find(tile_map[start_index])->second;
	pq.push(make_pair(distance[start_index], start_index));

    int current; // index of current tile being looked at by the loop
    while (!pq.empty()) {
        current = pq.top().second; //value in pq with smallest distance
        if (current == end_index) break; // we've found the end
        pq.pop();

        // These next if statements check the adjacent tiles for a quicker path
        // to the adjacent nodes through the current node
		if (current / map_cols != map_rows-1) { //bottom
			int alt = current + map_cols;
			int weight = distance[current] + tiles.find(tile_map[alt])->second;
            if (weight < distance[alt]) {
				distance[alt] = weight;
                previous[alt] = current;
				pq.push(make_pair(distance[alt], alt));
            }
		}

		if (current / map_cols != 0) { //Top
            int alt = current - map_cols;
            int weight = distance[current] + tiles.find(tile_map[alt])->second;
            if (weight < distance[alt]) {
                distance[alt] = weight;
                previous[alt] = current;
                pq.push(make_pair(distance[alt], alt));
            }
        }

		if (current / map_cols == (current+1) / map_cols && current != map_size-1) { //Right
            int alt = current + 1;
            int weight = distance[current] + tiles.find(tile_map[alt])->second;
            if (weight < distance[alt]) {
                distance[alt] = weight;
                previous[alt] = current;
                pq.push(make_pair(distance[alt], alt));
            }
        }

		if (current / map_cols == (current-1) / map_cols && current != 0) { //Left
            int alt = current - 1;
            int weight = distance[current] + tiles.find(tile_map[alt])->second;
            if (weight < distance[alt]) {
                distance[alt] = weight;
                previous[alt] = current;
                pq.push(make_pair(distance[alt], alt));
            }
        }
    }
    list<int> sequence; // final list containing path from start to end
    sequence.push_front(end_index);
    int cost = 0; // added weights of each tile
    current = previous[end_index];
    if (previous[current] != -1 || current == start_index) {
        while (current != -1) {
            //adds up cost, adds to list, goes to tile stored in previous[current] and repeats
            cost += tiles.find(tile_map[current])->second;
            sequence.push_front(current);
            current = previous[current];
        }
    }
    
    cout << cost << endl;
    for (list<int>::iterator it = sequence.begin(); it != sequence.end(); ++it) {
        cout << *it / map_cols << ' ' << *it % map_cols << endl;
    }

    delete[] tile_map;
    delete[] distance;
    delete[] previous;
    return 0;
}

