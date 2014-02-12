//
//  Sokoban.h
//  JUCE_sokoban
//
//  Created by annie zhang on 9/21/13.
//
//

#ifndef __JUCE_sokoban__Sokoban__
#define __JUCE_sokoban__Sokoban__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <time.h>
#include <ctype.h>
#include "MapParser.h"

using namespace std;

typedef struct sokoStruct{
    Table t;
    string s;
    int px;
    int py;
}soko;

typedef struct dirStruct{
    int dx;
    int dy;
    char ld;
    char ud;
}direction;

class Sokoban{
    
public:
    Sokoban(string mapName);
    ~Sokoban();
    void look(Table &t);
    bool isSolved(Table &t, int x, int y);
    bool pullable(int x, int y, int dx, int dy, Table &t);
    bool movable(int x, int y, int dx, int dy, Table &t);
    string getAction(char c);
    void applyAction();
    void solve();
    
    clock_t init, final;
    double time = 0;
    MapParser *map;
    int* orient;
    string plan = "";
    string reverseplan = "";
    int numSteps = 0;
    vector<direction> dir;
    vector<string> actions;
};
#endif /* defined(__JUCE_sokoban__Sokoban__) */
