#include "ofApp.h"



//===========================================================================

//The setup() function is called once when the application is first launched.

//This initialises all the applications variables and objects and sets its

//initial state.



long long int timer = 0;

long long int last_note_timestamp = 0;

long long int quant_melody = 50;

int rasuto_noto = 0;

bool flag_melody_line = true;

vector <ofPoint> lines;

bool chords[20] = {0};

int ringing[12] = {0};



void ofApp::test_chord(){
    
    if(ringing[0] && ringing[4] && ringing[7]){
        
        printf("C5!\n");
    }
}



void ofApp::setup()

{
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    
    //Open a connection to the first available MIDI input
    
    midiIn.openPort(0);
    
    
    
    //Set this class to listen for incoming MIDI messages
    
    midiIn.addListener(this);
    
    
    
    //initialise the note data array so that no circles will be drawn at startup
    
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
        
    {
        
        noteData[i].time_counter = 0;
        
    }
    
    
    
    //set the apps background to be black on startup
    
    backgroundColour = 0;
    
    
    
    //set the instructions to be displayed on startup
    
    showingInstructions = true;
    
}



//===========================================================================

//The newMidiMessage() function is called each time the application receives

//a new MIDI message. For this application we use this function to set the

//array of note data values, as well as for setting the apps background colour.

//Note that this function only sets values - the drawing of things based on these

//values is done within the draw() function below.



void ofApp::newMidiMessage (ofxMidiMessage& msg)

{
    
    //if we have received a note-on message
    
    if (msg.status == MIDI_NOTE_ON && msg.velocity != 0)
        
    {
        
        //search through each member of the note data array
        
        for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
            
        {
            
            //if found a member of noteData that is currently 'off'
            
            if (noteData[i].time_counter == 0)
                
            {
                
                //set this note to be 'on', resetting a time variable
                
                //that controls the transparency of the notes circle
                
                noteData[i].time_counter = 255;
                
                
                
                //store note number and velocity values of the note
                
                noteData[i].note_num = msg.pitch;
                
                noteData[i].note_vel = msg.velocity;
                
                
                
                if(noteData[i].note_num >= 90)
                    
                    noteData[i].pos.set (ofRandom (ofGetWidth()), ofRandom (ofGetHeight()/4));
                
                else if(noteData[i].note_num >= 60)
                    
                    noteData[i].pos.set (ofRandom (ofGetWidth()), ofGetHeight()/2 - ofRandom (ofGetHeight()/4));
                
                else if(noteData[i].note_num >= 30)
                    
                    noteData[i].pos.set (ofRandom (ofGetWidth()), ofGetHeight()/2 + ofRandom (ofGetHeight()/4));
                
                else
                    
                    noteData[i].pos.set (ofRandom (ofGetWidth()), ofGetHeight() - ofRandom (ofGetHeight()/4));
                
                
                
                //add to melody line
                
                if(timer - last_note_timestamp <= quant_melody){
                    
                    lines.push_back(ofPoint((lines.size() * 15) + (noteData[i].note_num * 30) + ofRandom(-20, 20), (ofGetHeight() - (noteData[i].note_num * ofGetHeight() / 60)) + 400));
                    
                }
                
                last_note_timestamp = timer;
                
                //leave the loop, as we have now stored this note in the array
                
                break;
                
                
                
            } //if (noteData[i].time_counter == 0)
            
            
            
        } //for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
        
        
        
    } //if (msg.status == MIDI_NOTE_ON)
    
    
    
    //if we have received a MIDI CC 1 (mod wheel) message
    
    else if (msg.status == MIDI_CONTROL_CHANGE && msg.control == 1)
        
    {
        
        //Set the background colour based on the CC value
        
        backgroundColour = msg.value;
        
    }
    
}



//===========================================================================

//The update() function is called repetitively in an infinite loop along with the draw()

//function below, and is designed to handle any backend (non GUI related) tasks

//that need triggering periodically. For this application there is nothing to do here.



void ofApp::update()

{
    
    timer += 1;
    
    if(timer - last_note_timestamp > quant_melody){
        
        lines.clear();
        
    }
    
}



//===========================================================================

//The draw() function is called repetitively in an infinite loop along with the update()

//function above, and is designed for drawing to the screen. We use this function for

//three main things:

// 1. For using the stored note data to draw/update circles on the screen

// 2. For updating the background colour

// 3. For display the apps instructions



void ofApp::drawnote(int i){
    
    //set the transparency of the circle to be the current time value of the note
    
    int alpha = noteData[i].time_counter;
    
    
    
    //set the colour of the circle based on the notes note number
    
    switch(noteData[i].note_num % 12){
            
        case 0:
            
            //printf("Do\n");
            
            ofSetColor(255,  0,  0, alpha);
            
            break;
            
        case 1:
            
            //printf("Do#\n");
            
            ofSetColor(238,130,238, alpha);
            
            break;
            
        case 2:
            
            //printf("Re\n");
            
            ofSetColor(255,255,  0, alpha);
            
            break;
            
        case 3:
            
            //printf("Re#\n");
            
            ofSetColor(255,160,122, alpha);
            
            break;
            
        case 4:
            
            //printf("Mi\n");
            
            ofSetColor(135,206,235, alpha);
            
            break;
            
        case 5:
            
            //printf("Fa\n");
            
            ofSetColor(139,  0,  0, alpha);
            
            break;
            
        case 6:
            
            //printf("Fa#\n");
            
            ofSetColor( 66,192,251, alpha);
            
            break;
            
        case 7:
            
            //printf("Sol\n");
            
            ofSetColor(255,140,  0, alpha);
            
            break;
            
        case 8:
            
            //printf("Sol#\n");
            
            ofSetColor(221,160,221, alpha);
            
            break;
            
        case 9:
            
            //printf("La\n");
            
            ofSetColor(  0,128,  0, alpha);
            
            break;
            
        case 10:
            
            //printf("La#\n");
            
            ofSetColor(199, 21,133, alpha);
            
            break;
            
        case 11:
            
            //printf("Ti\n");
            
            ofSetColor(  0,  0,255, alpha);
            
            break;
            
        default:
            
            printf("No such note!\n");
            
            break;
            
    };
    
    //draw a circle using the notes ofPoint value to determine the position,
    
    //and the notes velocity value to determine size of the circle.
    
    
    
    //ofImage maple;
    
    //maple.load("/Users/yehyeh/Desktop/leaf-png-23.png");
    
    ofCircle(noteData[i].pos, noteData[i].note_vel / 2);
    
    //maple.draw(noteData[i].pos.x,noteData[i].pos.y,20,20);
    
    
    
    //reduce the notes time value by 1 so that next time this function is called
    
    //it draws the notes circle with a greater transparency, giving the illusion
    
    //that the circle is fading out over time
    
    noteData[i].time_counter--;
    
}



void ofApp::draw()

{
    
    //=======================================
    
    //update the background of the app to be a gradient based on the last received MIDI CC 1 value
    
    ofBackgroundGradient(0, backgroundColour);
    
    
    
    //=======================================
    
    //draw/update all the notes circles...
    
    for(int i = 0; i < 12; i++) ringing[i] = false;
    
    //search through each note/circle
    
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
        
    {
        
        //if the circle is currently visible
        
        if (noteData[i].time_counter > 0)
            
        {
            
            drawnote(i);
            
            ringing[noteData[i].note_num % 12] = true;
            
        }
        
        
        
    }
    
    test_chord();
    
    if(flag_melody_line){
        
        ofPoint start;
        
        int shift = 0;
        
        if(!lines.empty()){
            
            start.y = lines[0].y;
            
            start.x = ofGetWidth()/3;
            
            shift = lines[0].x;
            
        }
        
        for(auto point : lines){
            
            point.x -= (shift - 5 - ofGetWidth()/3);
            
            ofDrawLine(start, point);
            
            start = point;
            
        }
        
    }
    
    
    
    //=======================================
    
    //Display the apps instructions
    
    
    
    //if we should be displaying the instructions
    
    if (showingInstructions)
        
    {
        
        //Draw a set of texts on the screen...
        
        
        
        //set the text colour to white
        
        ofSetColor(255);
        
        
        
        ofDrawBitmapString("MIDI inputs available:", 10, 24);
        
        
        
        //get a list of the available MIDI inputs
        
        vector<string> midi_port_strings = midiIn.getPortList();
        
        
        
        int last_line_pos = 44;
        
        
        
        //display each MIDI input name on a new line on the screen
        
        for (int i = 0; i < midi_port_strings.size(); i++)
            
        {
            
            ofDrawBitmapString(ofToString(i) + ": " + midi_port_strings[i], 10, 44 + (20 * i));
            
            
            
            last_line_pos = 44 + (20 * i);
            
        }
        
        
        
        ofDrawBitmapString("Currently connected to MIDI input:", 10, last_line_pos + 40);
        
        
        
        //if we are currently connected to a MIDI input, display its name on the screen
        
        if (midiIn.getPort() != -1)
            
            ofDrawBitmapString(midiIn.getName(), 10, last_line_pos + 60);
        
        //if we're not currently connected to a MIDI input, display that we're not connected to anything
        
        else
            
            ofDrawBitmapString("none/invalid", 10, last_line_pos + 60);
        
        
        
        ofDrawBitmapString("Press 0-9 on the keyboard to set the connected port number.", 10, last_line_pos + 100);
        
        ofDrawBitmapString("Press lowercase 's' on the keyboard to show/hide this text.", 10, last_line_pos + 120);
        
        
        
    } //if (showingInstructions)
    
}



//===========================================================================

//The keyPressed() function is called each time a key on the QWERTY keyboard

//is pressed. For this application we use this for toggling the instructions

//on and off as well as for setting the MIDI input we want to connect to.



void ofApp::keyPressed(int key)

{
    
    //if key 's' has been pressed
    
    if (key == 's')
        
    {
        
        //set instructions to show or hide (depending on their current state)
        
        //the next time that the draw() function is called.
        
        showingInstructions = !showingInstructions;
        
    }
    
    
    
    //if any of the number keys have been pressed
    
    else if (key >= '0' && key <= '9')
        
    {
        
        //convert the value of the number key to the related number
        
        int port_num = key - 48;
        
        
        
        //close the connection to the currently connected MIDI input
        
        midiIn.closePort();
        
        
        
        //open a connection to the chosen MIDI input
        
        midiIn.openPort(port_num);
        
    }
    
}



//===========================================================================

//The exit() function is called when the application is shut down



void ofApp::exit()

{
    
    //close the connection to the currently connected MIDI input
    
    midiIn.closePort();
    
    
    
    //stop listening for MIDI messages
    
    midiIn.removeListener(this);
    
}
