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
#include <list>
#include <climits>
using namespace std;
// Main Execution
int minDistance(set<int> visited, int distance[]) { // finds min distance in the visited set
    int min = INT_MAX;
    int minIndex;

    set<int>::iterator it;
    for (it = visited.begin(); it != visited.end(); ++it) {
        if (distance[*it] < min) {
            min = distance[*it];
            minIndex = *it;
        }
    }

    return minIndex;
}

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

    //Start of Dijkstra's algorithm
    set<int> visited; //set of indices that have been visited by the algorithm
    int *distance = new int[1]; // distances from source for each index
    int *previous = new int[1]; // contains each index's previous 'hop' from source

    for (int i=0; i<map_size; i++) {
        visited.insert(i);
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    //since distances are measured from "leaving" a tile, the start tile must contain it's weight
    distance[start_index] = tiles.find(tile_map[start_index])->second;
    int current;

    while (!visited.empty()) {
        current = minDistance(visited, distance);
        if (current == end_index) break;
        visited.erase(current);

        set<int>::iterator it;
        //This loop will update all adjacent tiles with new distances if they are shorter
        for(it = visited.begin(); it!=visited.end(); ++it) {
            if (*it == current + map_cols || // checks for adjacency
                *it == current - map_cols ||
                (*it == current + 1 && *it / map_cols == current / map_cols) ||
                (*it == current - 1 && *it / map_cols == current / map_cols)) {
                    int alt = distance[current] + tiles.find(tile_map[*it])->second;

                    if (alt < distance[*it]) {
                        distance[*it] = alt;
                        previous[*it] = current;
                    }
                }
        }
    }

    list<int> sequence; // list of moves from source to target
    sequence.push_front(end_index); // had to be added here because of how I did cost calculation
    int cost = 0;
    current = previous[end_index]; // this might break it
    if (previous[current] != -1 || current == start_index) {
        // this loop traverses the "previous" array to find the path from source to target
        while (current != -1) {  
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

