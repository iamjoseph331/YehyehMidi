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
#define MAX_NUM_OF_NOTES 5000
//Structure that stores information for a single note/circle

typedef struct
{
    ofPoint pos;
    int time_counter;
    int note_num;
    int note_vel;
    int birth_time;
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
    void test_palindrome(int i);
    void test_motivation();
    void draw();
    void drawnote(int i, int alpha, int op, int ed, int vol);
    void exit();
    void keyPressed(int key);
    
    //MIDI input callback function
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
private:
    
    //Array that stores information for each note/circle being displayed
    NoteData noteData[MAX_NUM_OF_NOTES];
    vector<NoteData> motivation;
    vector<NoteData> Notevec;
    
    //Variable for storing the apps background colour
    int backgroundColour;
    
    //Object that handles the MIDI input
    ofxMidiIn midiIn;
    
    //Flag that sets whether we're currently displaying the apps instructions
    bool showingInstructions;
    
    //path of images
    char img9big[20], img9small[20], img9dom[20], img7big[20], img7small[20], img7dom[20];
    char img3big[20], img3small[20], imgdisaster[20];
    char imgpalin[20];
    
};
