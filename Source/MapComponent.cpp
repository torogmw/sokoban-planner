//
//  MapComponent.cpp
//  JUCE_sokoban
//
//  Created by Minwei Gu on 9/21/13.
//
//

#include "MapComponent.h"
MapComponent::MapComponent(File mapFile)
{
    addKeyListener(this);
    autoStart = false;      //this is the flag for automatic playing
    mapFile.readLines(lines);
    height = lines.size();
    width = 0;
    for (int i = 0; i<height; i++)
    {
        if (width < lines[i].length())
        {
            width = lines[i].length();
        }
    }
    // draw the map in a static component
    block = ImageCache::getFromMemory(BinaryData::block_small_png, BinaryData::block_small_pngSize);
    wall_E = ImageCache::getFromMemory(BinaryData::mario_small_png, BinaryData::mario_small_pngSize);
    box = ImageCache::getFromMemory(BinaryData::box_small_png, BinaryData::box_small_pngSize);
    boxIndex = 0; //to track the box 
    target = ImageCache::getFromMemory(BinaryData::target_small_png, BinaryData::target_small_pngSize);
    victory = ImageCache::getFromMemory(BinaryData::victor_png, BinaryData::victor_pngSize);
    //emptySpace = ImageCache::getFromMemory(BinaryData::grayhound_jpg,     BinaryData::grayhound_jpgSize);
    for (int j = 0; j<height; j++)
    {
        for (int k=0; k<lines[j].length(); k++)             
        {   
            if (lines[j][k] == 'X')             // draw wall(block)
            {
                ImageButton* temp;
                addAndMakeVisible(temp = new ImageButton("block"));
                temp->setImages (true, false, true,
                                     block, 0.9f, Colours::transparentBlack,
                                     block, 1.0f, Colours::transparentBlack,
                                     block, 1.0f, Colours::transparentBlack,
                                     0.5f);
                temp->setSize(BLOCKSIZE,BLOCKSIZE);
                temp->setBounds(k*BLOCKSIZE, j*BLOCKSIZE,  BLOCKSIZE, BLOCKSIZE);
                blockDrawer.add(temp);
            }
            else if (lines[j][k] == '?')                    //draw targets
            {
                ImageButton* temp;
                addAndMakeVisible(temp = new ImageButton("target"));
                temp->setImages (true, false, true,
                                 target, 0.9f, Colours::transparentBlack,
                                 target, 1.0f, Colours::transparentBlack,
                                 target, 1.0f, Colours::transparentBlack,
                                 0.5f);
                temp->setSize(BLOCKSIZE,BLOCKSIZE);
                temp->setBounds(k*BLOCKSIZE, j*BLOCKSIZE,  BLOCKSIZE, BLOCKSIZE);
                temp->toBack();
                targetDrawer.add(temp);
            }
            else if (lines[j][k] == '@')        // draw the robot
            {
                personx = k;
                persony = j;
                addAndMakeVisible(robotDrawer = new ImageButton("wallE"));
                robotDrawer->setImages (true, false, true,
                                 wall_E, 0.9f, Colours::transparentBlack,
                                 wall_E, 1.0f, Colours::transparentBlack,
                                 wall_E, 1.0f, Colours::transparentBlack,
                                 0.5f);
                robotDrawer->setSize(BLOCKSIZE,BLOCKSIZE);
                robotDrawer->setBounds(k*BLOCKSIZE, j*BLOCKSIZE,  BLOCKSIZE, BLOCKSIZE);
                robotDrawer->toFront(false);
                //robotDrawer->setVisible(true);
            }
            else if ((lines[j][k] == '*'))          //draw boxes
            {
                ImageButton* temp;
                addAndMakeVisible(temp = new ImageButton("box"));
                temp->setImages (true, false, true,
                                 box, 0.9f, Colours::transparentBlack,
                                 box, 1.0f, Colours::transparentBlack,
                                 box, 1.0f, Colours::transparentBlack,
                                 0.5f);
                temp->setSize(BLOCKSIZE,BLOCKSIZE);
                temp->setBounds(k*BLOCKSIZE, j*BLOCKSIZE,  BLOCKSIZE, BLOCKSIZE);
                boxDrawer.add(temp);
                lines.set(j,lines[j].replaceSection(k, 1, String(boxIndex)));
                //std::cout<<"x: "<<k<<"y: "<<j<<"index: "<<lines[j][k]<<std::endl;
                boxIndex++;
            }
        }
    }
    startTimer(200);
    // for debug
    solution = String::empty;
    solutionIndex = 0;
}

MapComponent::~MapComponent()
{
    
}

void MapComponent::getSolution(std::string solution_)
{
    solution = String(solution_);
}

void MapComponent::animatePlan()
{
    char ch = solution[solutionIndex];
    if (solutionIndex<solution.length())
    {
        solutionIndex++;
    }
    else if (solutionIndex == solution.length())
    {
        robotDrawer->setImages (true, false, true,
                                victory, 0.9f, Colours::transparentBlack,
                                victory, 1.0f, Colours::transparentBlack,
                                victory, 1.0f, Colours::transparentBlack,
                                0.5f);
    }
    switch (ch)
    {
        case 'u':
        {
            movePlayer(0);
            break;
        }
        case 'd':
        {
            movePlayer(1);
            break;
        }
        case 'l':
        {
            movePlayer(2);
            break;
        }
        case 'r':
        {
            movePlayer(3);
            break;
        }
        case 'U':
        {
            pushBox(0);
            break;
        }
        case 'D':
        {
            pushBox(1);
            break;
        }
        case 'L':
        {
            pushBox(2);
            break;
        }
        case 'R':
        {
            pushBox(3);
            break;
        }
        default:
        {
            break;
        }
    }
}

void MapComponent::movePlayer(int direction)
{
    switch (direction)
    {
        case 0:
        {
            persony = persony - 1;
            break;
        }
        case 1:
        {
            persony = persony + 1;
            break;
        }
        case 2:
        {
            personx = personx - 1;
            break;
        }
        case 3:
        {
            personx = personx + 1;
            break;
        }
        default:
        {
            break;
        }
    }
    robotDrawer->setBounds(personx*BLOCKSIZE, persony*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
}

void MapComponent::pushBox(int direction)
{
    int boxx;
    int boxy;
    switch (direction)
    {
        case 0:
        {
            persony = persony - 1;
            boxx = personx;
            boxy = persony-1;
            break;
        }
        case 1:
        {
            persony = persony + 1;
            boxx = personx;
            boxy = persony+1;
            break;
        }
        case 2:
        {
            personx = personx - 1;
            boxx = personx-1;
            boxy = persony;
            break;
        }
        case 3:
        {
            personx = personx + 1;
            boxx = personx+1;
            boxy = persony;
            break;
        }
        default:
        {
            break;
        }
    }
    robotDrawer->setBounds(personx*BLOCKSIZE, persony*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
    // update the boxindex in maps and drawer
    int movingIndex = lines[persony][personx]- '0';
    boxDrawer[movingIndex]->setBounds(boxx*BLOCKSIZE, boxy*BLOCKSIZE, BLOCKSIZE,BLOCKSIZE);
    lines.set(persony,lines[persony].replaceSection(personx, 1, String(" ")));
    lines.set(boxy, lines[boxy].replaceSection(boxx, 1, String(movingIndex)));
    //std::cout<<"x: "<<boxx<<"y: "<<boxy<<"index: "<<lines[boxy][boxx]<<std::endl;
}
void MapComponent::timerCallback()
{
    if(autoStart && solution != String::empty)
    {
        animatePlan();
    }
    
}

bool MapComponent::keyPressed(const KeyPress &key, Component *originatingComponent)
{
    if(key == KeyPress::upKey)
    {
        personx-=1;
        robotDrawer->setBounds(persony*BLOCKSIZE, personx*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
    }
    if(key == KeyPress::downKey)
    {
        personx+=1;
        robotDrawer->setBounds(persony*BLOCKSIZE, personx*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
    }
    if(key == KeyPress::leftKey)
    {
        persony-=1;
        robotDrawer->setBounds(persony*BLOCKSIZE, personx*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
    }
    if(key == KeyPress::rightKey)
    {
        persony+=1;
        robotDrawer->setBounds(persony*BLOCKSIZE, personx*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE);
    }
    return 0;
}

bool MapComponent::keyStateChanged(bool isKeyDown, Component *originatingComponent)
{
    return 0;
}

void MapComponent::paint(Graphics &g)
{
    g.fillAll (Colours::darkgrey);
    g.setColour (Colours::lightgreen);
}

