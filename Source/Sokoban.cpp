//
//  Sokoban.cpp
//  JUCE_sokoban
//
//  Created by annie zhang on 9/21/13.
//
//

#include "Sokoban.h"

Sokoban::Sokoban(string mapName)
{
    map = new MapParser(mapName);
    
    for(int i=0; i<map->height; i++)
    {
        for (int j=0;j<map->width; j++)
            cout<<map->mapData[i][j];
        cout<<endl;
    }
    orient = new int[4];
    
    look(map->mapData_tryout);
    vector<int> myvector(5);

}

Sokoban::~Sokoban()
{
    delete map;
    delete orient;
}

void Sokoban::look(Table &t)
{
    int ax = 0;
    int ay = 0;
    int bx = 0;
    int by = 0;
    bool targetfound = false;
    bool boxfound = false;
    memset(orient, 0, 4*sizeof(int));
    dir.clear();
    
    for (int i=0; i<t.size(); i++){
        for (int j=0; j<t[i].size(); j++){
            if (!targetfound && t[i][j] == '?'){
                ax = i;
                ay = j;
                targetfound = true;
            }
            if (!boxfound && t[i][j] == '*'){
                bx = i;
                by = j;
                boxfound = true;
            }
            if (targetfound && boxfound)
                break;
        }
    }
    
    
    double tan = (by-ay)*1.0/(bx-ax);
    if (tan<1 && tan>-1){
        if(bx>ax){
            orient[0] = 3;
            orient[1] = 4;
            orient[2] = 1;
            orient[3] = 2;
        }
        else{
            orient[0] = 1;
            orient[1] = 2;
            orient[2] = 3;
            orient[3] = 4;
        }
    }
    else{
        if(by>ay){
            orient[0] = 2;
            orient[1] = 3;
            orient[2] = 4;
            orient[3] = 1;
        }
        else{
            orient[0] = 4;
            orient[1] = 1;
            orient[2] = 2;
            orient[3] = 3;
        }
    }
    
    for (int i=0; i<4; i++){
        if(orient[i] == 1){
            direction du;
            du.dx = -1;
            du.dy = 0;
            du.ld = 'u';
            du.ud = 'U';
            dir.push_back(du);
        }
        else if(orient[i] == 2){
            direction dr;
            dr.dx = 0;
            dr.dy = 1;
            dr.ld = 'r';
            dr.ud = 'R';
            dir.push_back(dr);
        }
        else if(orient[i] == 3){
            direction dd;
            dd.dx = 1;
            dd.dy = 0;
            dd.ld = 'd';
            dd.ud = 'D';
            dir.push_back(dd);
        }
        else if(orient[i] == 4){
            direction dl;
            dl.dx = 0;
            dl.dy = -1;
            dl.ld = 'l';
            dl.ud = 'L';
            dir.push_back(dl);
        }
    }
}

bool Sokoban::isSolved(Table &t, int x, int y)
{
    for (int i = 0; i<t.size(); ++i)
        for(int j=0; j<t[i].size(); ++j)
            if((map->mapData[i][j] == '*') ^ (t[i][j] == '?'))
                return false;
    if (map->px != x || map->py != y)
        return false;
    return true;
}

bool Sokoban::pullable(int x, int y, int dx, int dy, Table &t)
{
    if(t[x-dx][y-dy] == ' ')
        return true;
    return false;
}

bool Sokoban::movable(int x, int y, int dx, int dy, Table &t)
{
    if(map->mapData[x+dx][y+dy] == 'X')
        return false;
    if (t[x+dx][y+dy] == ' ' || t[x+dx][y+dy] == '*')
        return true;
    return false;
}

string Sokoban::getAction(char c)
{
    switch (c) {
        case 'u':
            return "move-player-up";
        case 'd':
            return "move-player-down";
        case 'l':
            return "move-player-left";
        case 'r':
            return "move-player-right";
        case 'U':
            return "push-box-up";
        case 'D':
            return "push-box-down";
        case 'L':
            return "push-box-left";
        case 'R':
            return "push-box-right";

        default:
            break;
    }
}

void Sokoban::applyAction()
{
    for (int i=plan.size()-1; i>=0; i--){
        char c = plan[i];
        if (plan[i] == 'u')
            c = 'd';
        else if (plan[i] == 'd')
            c = 'u';
        else if (plan[i] == 'l')
            c = 'r';
        else if (plan[i] == 'r')
            c = 'l';
        reverseplan = reverseplan + c;
        actions.push_back(getAction(c));
    }
    while(reverseplan.size()>0){
        if (islower(reverseplan[reverseplan.size()-1])){
            reverseplan.erase(reverseplan.size()-1);
            actions.pop_back();
        }
        else
            break;
    }
    numSteps = actions.size();
}

void Sokoban::solve()
{
    init=clock();
    
    set<Table> visited;
    queue<soko> q;
    
    soko initSoko;
    initSoko.t = map->mapData_tryout;
    initSoko.s = "";
    initSoko.px = map->px;
    initSoko.py = map->py;
    q.push(initSoko);
    visited.insert(map->mapData_tryout);
    
    while (q.size()>0){
        Table temp = q.front().t;
        Table cur = q.front().t;

        look(temp);
        
        string prepath = q.front().s;
        int x = q.front().px;
        int y = q.front().py;
        q.pop();
        
        
        for(int i=0; i<dir.size(); i++){
            temp = cur;
            int dx = dir[i].dx;
            int dy = dir[i].dy;
            
            if(temp[x+dx][y+dy] == '?'){
                if (pullable(x, y, dx, dy, temp)){
                    temp[x][y] = '?';
                    temp[x+dx][y+dy] = ' ';
                    temp[x-dx][y-dy] = '@';
                    if(visited.find(temp) == visited.end()){
                        if(isSolved(temp, x-dx, y-dy)){
                            final = clock() - init;
                            time = (double)final/((double)CLOCKS_PER_SEC);
                            plan = prepath + dir[i].ud;
                            numSteps = plan.size();
                            if(numSteps>0)
                                applyAction();
                            return;
                        }
                        soko newsoko;
                        newsoko.t = temp;
                        newsoko.s = prepath+dir[i].ud;
                        newsoko.px = x-dx;
                        newsoko.py = y-dy;
                        q.push(newsoko);
                        visited.insert(temp);
                    }
                }
            }
            else if(movable(x, y, dx, dy, temp)){
                temp[x][y] = ' ';
                temp[x+dx][y+dy] = '@';
                if(visited.find(temp) == visited.end()){
                    if(isSolved(temp, x+dx, y+dy)){
                        final = clock() - init;
                        time = (double)final/((double)CLOCKS_PER_SEC);
                        plan = prepath+dir[i].ld;
                        numSteps = plan.size();
                        if(numSteps>0)
                            applyAction();
                        return;
                    }
                    soko newsoko;
                    newsoko.t = temp;
                    newsoko.s = prepath+dir[i].ld;
                    newsoko.px = x+dx;
                    newsoko.py = y+dy;
                    q.push(newsoko);
                    visited.insert(temp);
                }
            }
        }
    }
    
}



