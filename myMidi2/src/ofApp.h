/*
 * Modified from:  2015 Liam Lacey
 * Author:  2017 Joseph Chen
 *
 */

#pragma once

#include "ofMain.h"

//Include the ofxMidi library so that the application can have MIDI functionality

#include "ofxMidi.h"

//Set the max amount of notes/circles we can display at any time

#define MAX_NUM_OF_NOTES 1000

//Structure that stores information for a single note/circle

typedef struct

{
    
    ofPoint pos;
    int time_counter;
    int note_num;
    int note_vel;
    
} NoteData;



//===========================================================================

//The main openFrameworks class,

//configured to listen for incoming MIDI messages


class ofApp :   public ofBaseApp,
public ofxMidiListener

{
    
public:
    
    //Main openFrameworks functions
    void setup();
    void update();
    void test_chord();
    void test_motivation();
    void draw();
    void drawnote(int i);
    void exit();
    void keyPressed(int key);
    
    
    
    //MIDI input callback function
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
private:
    
    //Array that stores information for each note/circle being displayed
    NoteData noteData[MAX_NUM_OF_NOTES];
    vector<NoteData> motivation;
    
    //Variable for storing the apps background colour
    int backgroundColour;
    
    //Object that handles the MIDI input
    ofxMidiIn midiIn;
    
    //Flag that sets whether we're currently displaying the apps instructions
    bool showingInstructions;
    
};
