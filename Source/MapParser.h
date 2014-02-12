//
//  MapParser.h
//  JUCE_sokoban
//
//  Created by Minwei Gu on 9/21/13.
//
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector.h>
#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/unordered_set.hpp>


using namespace std;

typedef vector<char> TableRow;     // one line
typedef vector<TableRow> Table;    // all lines

class MapParser
{
public:
    MapParser(string map);
    ~MapParser();
    
    vector<string> data;  // the string we need to parse
    int px,py;            // the position of the person
    int width;
    int height;
    Table mapData;        // the map data that has 2d char value size of(width * height)
    Table mapData_tryout;
};

