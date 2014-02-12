//
//  MapComponent.h
//  JUCE_sokoban
//
//  Created by Minwei Gu on 9/21/13.
//
//  using this class to add a subcomponent onto the main document view and read the map

#ifndef __JUCE_sokoban__MapComponent__
#define __JUCE_sokoban__MapComponent__

#include <iostream>
#include <JuceHeader.h>
#include "BinaryData.h"

#define BLOCKSIZE 40

class MapComponent : public Timer, public Component, public KeyListener
{
public:
    MapComponent(File mapFile);
    ~MapComponent();
    void timerCallback();
    void paint (Graphics& g);
    bool keyPressed(const KeyPress &key, Component *originatingComponent);
    bool keyStateChanged (bool isKeyDown, Component *originatingComponent);
    
    // 0: up, 1: down, 2: left, 3: right
    void animatePlan();
    void movePlayer(int direction);
    void pushBox(int direction);
    void getSolution(std::string solution);
    
    int height;
    int width;
    bool autoStart;
    
    
private:
    StringArray lines;
    String solution;
    int solutionIndex;
    int boxIndex;
    int personx;
    int persony;
    Image block; // the block image
    Image wall_E;
    Image box;
    Image target;
    Image emptySpace;
    Image victory;
    ScopedPointer<ImageButton> robotDrawer;
    OwnedArray<ImageButton> blockDrawer;
    OwnedArray<ImageButton> boxDrawer;
    OwnedArray<ImageButton> targetDrawer;
    //OwnedArray<ImageButton> emptyDrawer;
};
#endif /* defined(__JUCE_sokoban__MapComponent__) */
