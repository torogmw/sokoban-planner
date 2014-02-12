//
//  MapParser.cpp
//  JUCE_sokoban
//
//  Created by Minwei Gu on 9/21/13.
//
//

#include "MapParser.h"

MapParser::MapParser(string map)
{
    boost::split(data,map,boost::is_any_of("\n"));      // split the map into different lines
    // start parsing the map
    // first get the height and the width
    height = data.size();
    width = 0;
    for (int i=0; i<height; i++)
    {
        if (width < data[i].size())
            width = data[i].size();
    }
    // use the height and width to parse the other data
    for (int i=0; i<height; i++)
    {
        TableRow temp;
        TableRow temp2;
        for (int j=0; j<width; j++)
        {
            char ch = data[i][j];
            if (j<data[i].size())
            {
                temp.push_back(ch);
                temp2.push_back(ch);
            }
            else
            {
                temp.push_back(' ');
                temp2.push_back(' ');
            }
            if (data[i][j] == '@')      // if finding the player,record his position
            {
                px = i;
                py = j;
            }
        }
        mapData.push_back(temp);
        mapData_tryout.push_back(temp2);
    }
//    for(int i=0; i<height; i++)
//    {
//        for (int j=0;j<width; j++)
//            cout<<mapData[i][j];
//        cout<<endl;
//    }
//    cout<<"person at x: "<<px<<" y: "<<py<<endl;
    
}

MapParser::~MapParser()
{

}