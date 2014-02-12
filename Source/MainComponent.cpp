//
//  MainComponent.cpp
//  OnsetReal
//
//  Created by Minwei Gu on 8/27/13.
//
//

#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible (title = new Label (String::empty, "Sokoban Planner"));
    title->setFont (Font (30.00f, Font::bold));
    title->setJustificationType (Justification::topLeft);
    title->setEditable (false, false, false);
    title->setColour (TextEditor::textColourId, Colours::black);
    title->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible(loadButton = new TextButton(String::empty));
    loadButton->setButtonText("Load map");
    loadButton->addListener(this);
    loadButton->setColour (TextButton::buttonColourId, Colours::lightblue);
    loadButton->setColour (TextButton::textColourOnId, Colours::black);
    
    addAndMakeVisible(solveButton = new TextButton(String::empty));
    solveButton->setButtonText("solve it! ");
    solveButton->addListener(this);
    solveButton->setColour (TextButton::buttonColourId, Colours::lightblue);
    solveButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (console = new Label (String::empty, "choose a map"));
    console->setFont (Font (20.00f, Font::bold));
    console->setJustificationType (Justification::topLeft);
    console->setEditable (false, false, false);
    console->setColour (TextEditor::textColourId, Colours::white);
    console->setColour (TextEditor::backgroundColourId, Colours::black);
    
    addAndMakeVisible (quitButton = new TextButton (String::empty));
    quitButton->setButtonText ("Quit");
    quitButton->addListener (this);
    
    
    setSize(1024, 768);
    
    // audio stuff
    currentFile = File(String::empty);
    currentMap = String::empty;
}

MainComponent::~MainComponent()
{
    
    title = nullptr;
    quitButton = nullptr;
    loadButton = nullptr;
    sokoban = nullptr;
    solveButton = nullptr;
}

void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
    g.setColour(Colours::whitesmoke);
}

void MainComponent::resized()
{
    title->setBounds (getWidth()/3+50, 20, 400, 32);
    quitButton -> setBounds (getWidth()/2+250, 20, 120, 32);
    loadButton -> setBounds(getWidth()/3-300, 20, 120, 32);
    solveButton -> setBounds(getWidth()/3-170, 20, 120, 32);
    console -> setBounds (getWidth()/3-300,60, 600,96);
    
    internalPath1.clear();
    internalPath1.startNewSubPath (136.0f, 80.0f);
    internalPath1.quadraticTo (176.0f, 24.0f, 328.0f, 32.0f);
    internalPath1.quadraticTo (472.0f, 40.0f, 472.0f, 104.0f);
    internalPath1.quadraticTo (472.0f, 192.0f, 232.0f, 176.0f);
    internalPath1.lineTo (184.0f, 216.0f);
    internalPath1.lineTo (200.0f, 168.0f);
    internalPath1.quadraticTo (96.0f, 136.0f, 136.0f, 80.0f);
    internalPath1.closeSubPath();
    
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::buttonClicked(Button* buttonthatWasClicked)
{
    if (buttonthatWasClicked == quitButton)
    {
        JUCEApplication::quit();
    }
    
    if (buttonthatWasClicked == loadButton)
    {
        FileChooser chooser (("Choose .map file to open"),File::nonexistent,"*",true);
        chooser.browseForFileToOpen();
       // if (chooser.getResult().exists())
        currentFile = File(chooser.getResult());
        if (currentFile.exists())
        {
            // UI
            addAndMakeVisible(visualPlanner = new MapComponent(currentFile));
            int a = (visualPlanner->height)*BLOCKSIZE;
            int b = (visualPlanner->width)*BLOCKSIZE;
            visualPlanner->setBounds(getWidth()/2-b/2, getHeight()/2-a/2,b,a);
            
            //planner
            planner = new MapParser(currentMap.toStdString());
            currentMap = currentFile.loadFileAsString();
            sokoban = new Sokoban(currentMap.toStdString());
        }
        else
        {
            printf("no such file!");
        }
     }
    
    if (buttonthatWasClicked == solveButton)
    {
        console->setText("planning... ", dontSendNotification);
        sokoban->solve();
        if (sokoban->numSteps>0){
            String temp = "solved!\n" + String(sokoban->numSteps) + " steps total.\nRunning time: "+String(sokoban->time)+ " seconds. \n ";
            console->setText(temp, dontSendNotification);
            cout<<endl<<endl<< "number of steps : " << sokoban->numSteps <<endl;
            cout<<endl<<"time : "<<sokoban->time<<" sec"<<endl;
            cout<<endl<<sokoban->reverseplan<<endl<<endl<<"start plan :"<<endl<<endl;
            for(int i=0; i<sokoban->actions.size(); i++){
                cout<< sokoban->actions[i]<<endl;
            }
            cout<<endl<<"end plan"<<endl;
        }
        else
        {
            console->setText("no solution found", dontSendNotification);
            cout<<"no solution found"<<endl;
        }
        if (visualPlanner)
        {
            visualPlanner->getSolution(sokoban->reverseplan);
            visualPlanner->autoStart = 1;
        }
    }
}


void MainComponent::timerCallback()
{
    
}

void MainComponent::visibilityChanged()
{
    
}