//
//  MainComponent.h
//  OnsetReal
//
//  Created by Minwei Gu on 8/27/13.
//
//

#ifndef __OnsetReal__MainComponent__
#define __OnsetReal__MainComponent__

#include <iostream>
#include "JuceHeader.h"
#include "Sokoban.h"
#include "MapComponent.h"


class MainComponent  : public Component, public ButtonListener, public Timer//, public KeyListener
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();
    
    //==============================================================================s]
    
    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void visibilityChanged();
    void timerCallback();
//    bool keyPressed(const KeyPress &key, Component *originatingComponent);
//    bool keyStateChanged (bool isKeyDown, Component *originatingComponent);
    
private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    File currentFile;
    String currentMap;
    Sokoban *sokoban;
    //ScopedPointer<MapParser> map;
    ScopedPointer<MapParser> planner;
    ScopedPointer<MapComponent> visualPlanner;
    //[/UserVariables]
    
    //==============================================================================
    //    Label* helloWorldLabel;
    Path internalPath1;
    ScopedPointer<Label> title;
    ScopedPointer<Label> console;
    ScopedPointer<Label> stepIndex;
    ScopedPointer<Label> movement;
    ScopedPointer<TextButton> loadButton;
    ScopedPointer<TextButton> quitButton;
    ScopedPointer<TextButton> solveButton;

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};



#endif /* defined(__OnsetReal__MainComponent__) */
