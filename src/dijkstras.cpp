// dijsktras.cpp
#include <iostream>
#include <map>
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
    int *tile_map = new int[map_rows*map_cols];

    for (int i=0; i<(map_rows*map_cols); i++) {
        cin >> tile_name;
        tile_map[i] = tile_name;
    }

    //Runner start and end positions
    cin >> start_row >> start_col >> end_row >> end_col;

    //TODO: run dijkstras algorithm

    delete[] tile_map;
    return 0;
}

