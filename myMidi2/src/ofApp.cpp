#include "ofApp.h"
#include <stdio.h>
//#define quarter
//#define debug_motivation
/*
#define measure 10
#define zoom    8
#define note    120
#define disap   2000
#define hoola   1200
*/
int measure = 10, zoom = 8, note = 120, disap = 2000, hoola = 1200;
//===========================================================================
//The setup() function is called once when the application is first launched.
//This initialises all the applications variables and objects and sets its
//initial state.
int timer = 0;
long long int last_note_timestamp = 0;
long long int quant_melody = 50;
int rasuto_noto = 0;
bool flag_melody_line = false;

int chord_type9[3][9] = {{0,4,7,11,14,12,16,19,23}, //big      9 chord
                         {0,3,7,10,14,12,15,19,22}, //small    9 chord
                         {0,4,7,10,14,12,16,19,22}};//dominant 9 chord
int chord_type7[3][7] = {{0,4,7,11,12,16,19},       //big      7 chord
                         {0,3,7,10,12,15,19},       //small    7 chord
                         {0,4,7,10,12,15,19}};      //dominant 7 chord
int chord_type3[2][5] = {{0,4,7,12,16},             //big      3 chord
                         {0,3,7,12,15}};            //small    3 chord

bool record = false;
bool peek = false;
double alikeness = 0.0;

struct opedvol{
    bool keyup = false;
    int id = 0;
    int op = 0;
    int ed = 0;
    int vol = 0;
};

struct Nset{
    int direct = 5;         //undecided up1 down1 up2 down2
    int st_note = 0;
    int ed_note = 0;
    int life = 0;
    vector<int> notes;
};

struct img{
    string path = "";
    int posx = 0;
    int posy = 0;
    int size = 0;
    int birth = 0;
    int id = 0;
};

vector <opedvol> lines[90];
vector <Nset> order;
vector <img> imgvec;

void ofApp::test_palindrome(int i){
    if(order[i].st_note == order[i].ed_note){
        unsigned long ss = order[i].notes.size();
        if(ss < 4)
            return;
        for(int j = 0; j < ss; j++){
            if(order[i].notes[j] != order[i].notes[ss - j - 1])
                return;
        }
        unsigned long svec = imgvec.size();
        int newid = 2000 + order[i].notes.size() * 100 + order[i].st_note;
        for(int j = 0; j < svec; j++){
            if(imgvec[j].id == newid && imgvec[j].birth >= lines[order[i].st_note].back().op){
                return;
            }
        }
        img myimg;
        myimg.birth = timer;
        myimg.path = imgpalin;
        myimg.posx = random() % ofGetHeight();
        myimg.posy = random() % ofGetWidth();
        myimg.size = order[i].notes.size() * 25;
        myimg.id = newid;
        imgvec.push_back(myimg);
    }
}

void ofApp::test_motivation(){
    for(int i = 0; i < MAX_NUM_OF_NOTES - motivation.size(); i++){
        if(noteData[i].note_num == 0)
            continue;
        alikeness = 0.0;
        
        for(int j = 0; j < motivation.size(); j++){
            //printf("%d\n",noteData[i+j].note_num);
            int difference = noteData[i].note_num - motivation[0].note_num;
            if(abs(noteData[i+j].note_num  - motivation[j].note_num - difference) <= 1 && noteData[i+j].time_counter > 200){
                alikeness += 1/(double)motivation.size();
            }
            if(alikeness >= 0.9){
                ofImage maple;
                maple.load("images/motivations/pic1.bmp");
                ofSetColor(255, 255, 255, noteData[i].time_counter);
                maple.draw(ofGetWidth() - ((noteData[i].note_num - 20) * ofGetWidth() / 90),ofGetHeight() - ((noteData[i].note_num - 20) * ofGetHeight() / 90),noteData[i].note_vel*1.3,noteData[i].note_vel*1.3);
            }
        }
    }
}


void ofApp::test_chord(){
    bool kdown[150] = {0};
    for(int i = 0; i < 88; i++){
        if(lines[i].size() == 0)
            continue;
        if(lines[i].back().keyup == false)
            kdown[i] = 1;
    }
    int downcount = 0;
    int dcnt = 0;
    for(int i = 0; i < 88; i++){
        if(kdown[i] == 1){
            downcount += 1;
            dcnt = i;
            // 9 chord test
            for(int j = 0; j < 3; j++){
                int cnt = 0;
                for(int k = 0; k < 5; k++){ // 9 chord test / trans
                    cnt = 0;
                    int endpt = 0;
                    for(int l = 0; l < 5; l++){ //note in chord
                        if(kdown[i + chord_type9[j][k+l] - chord_type9[j][k]] == 1){
                            cnt += 1;
                            if(cnt >= 5){
                                endpt = l;
                                break;
                            }
                        }
                        else{
                            cnt = 0;
                        }
                    }
                    
                    if(cnt >= 5){
                        unsigned long ss = imgvec.size();
                        int newid = 90000 + (k * 1000) + (j * 100) + i;
                        for(int m = 0; m < ss; m++){
                            if(imgvec[m].id == newid && imgvec[m].birth >= lines[i].back().op){
                                return;
                            }
                        }
                        img myimg;
                        switch(j){
                            case 0:
                                myimg.path = img9big;
                                break;
                            case 1:
                                myimg.path = img9small;
                                break;
                            case 2:
                                myimg.path = img9dom;
                                break;
                            default:
                                fprintf(stderr,"No such type, but why?\n");
                                break;
                        }
                        myimg.birth = timer;
                        myimg.id = newid;
                        myimg.size = lines[i + chord_type9[j][k+endpt] - chord_type9[j][k]].back().vol;
                        myimg.posx = rand() % ofGetHeight();
                        myimg.posy = rand() % ofGetWidth();
                        imgvec.push_back(myimg);
                        return;
                    }
                }
            }
            // 7 chord test
            for(int j = 0; j < 3; j++){
                int cnt = 0;
                int maxcnt = 0;
                for(int k = 0; k < 4; k++){ // 7 chord test / trans
                    cnt = 0;
                    int endpt = 0;
                    for(int l = 0; l < 4; l++){// note in chord
                        if(kdown[i + chord_type7[j][k + l] - chord_type7[j][k]] == 1){
                            cnt += 1;
                            if(cnt >= 4){
                                endpt = l;
                                break;
                            }
                        }
                        else{
                            cnt = 0;
                        }
                    }
                    
                    if(cnt >= 4){
                        unsigned long ss = imgvec.size();
                        int newid = 70000 + (k * 1000) + (j * 100) + i;
                        for(int m = 0; m < ss; m++){
                            if(imgvec[m].id == newid && imgvec[m].birth >= lines[i].back().op){
                                return;
                            }
                        }
                        img myimg;
                        switch(j){
                            case 0:
                                myimg.path = img7big;
                                break;
                            case 1:
                                myimg.path = img7small;
                                break;
                            case 2:
                                myimg.path = img7dom;
                                break;
                            default:
                                fprintf(stderr,"No such type, but why?\n");
                                break;
                        }
                        myimg.birth = timer;
                        myimg.id = newid;
                        myimg.size = lines[i + chord_type7[j][k+endpt] - chord_type7[j][k]].back().vol;
                        myimg.posx = rand() % ofGetHeight();
                        myimg.posy = rand() % ofGetWidth();
                        imgvec.push_back(myimg);
                        return;
                        }
                }
            }
            // 3 chord test
            for(int j = 0; j < 2; j++){
                int cnt = 0;
                int maxcnt = 0;
                for(int k = 0; k < 3; k++){ // 3 chord test / trans
                    cnt = 0;
                    int endpt = 0;
                    for(int l = 0; l < 3; l++){// note in chord
                        if(kdown[i + chord_type3[j][k + l] - chord_type3[j][k]] == 1){
                            cnt += 1;
                            if(cnt >= 3){
                                endpt = l;
                                break;
                            }
                        }
                        else{
                            cnt = 0;
                        }
                    }
                    if(cnt >= 3){
                        unsigned long ss = imgvec.size();
                        int newid = 30000 + (k * 1000) + (j * 100) + i;
                        for(int m = 0; m < ss; m++){
                            if(imgvec[m].id == newid && imgvec[m].birth >= lines[i].back().op){
                                return;
                            }
                        }
                        img myimg;
                        switch(j){
                            case 0:
                                myimg.path = img3big;
                                break;
                            case 1:
                                myimg.path = img3small;
                                break;
                            default:
                                fprintf(stderr,"No such type, but why?\n");
                                break;
                        }
                        myimg.birth = timer;
                        myimg.id = newid;
                        myimg.size = lines[i + chord_type3[j][k+endpt] - chord_type3[j][k]].back().vol;
                        myimg.posx = rand() % ofGetHeight();
                        myimg.posy = rand() % ofGetWidth();
                        imgvec.push_back(myimg);
                        return;
                    }
                }
            }
        }
    }
    if(downcount >= 4){
        img myimg;
        myimg.path = imgdisaster;
        myimg.birth = timer;
        myimg.id = 3039751;
        myimg.size = 120;
        if(lines[dcnt].back().vol > 75){
            myimg.posx = (ofGetHeight() / 3) + (rand() % (ofGetHeight() / 3));
        }
        else if(lines[dcnt].back().vol > 50){
            myimg.posx = (2 * ofGetHeight() / 3) + (rand() % (ofGetHeight() / 3));
        }
        else{
            myimg.posx = (ofGetHeight() / 3) + (rand() % (ofGetHeight() / 3));
        }
        
        myimg.posy = rand() % ofGetWidth();
        imgvec.push_back(myimg);
    }
    /*for(int i = 0; i < 5; i++){
        if(ringing[i] && ringing[i+4] && ringing[i+7]){
            ofImage maple;
            maple.load("images/chords/3chord/pic1.bmp");
            ofSetColor(255, 255, 255, noteData[i].time_counter);
            maple.draw(ofGetWidth() - ((noteData[i].note_num - 20) * ofGetWidth() / 90),ofGetHeight() - ((noteData[i].note_num - 20) * ofGetHeight() / 90),noteData[i].note_vel*1.3,noteData[i].note_vel*1.3);
        }
    }*/
}

void ofApp::setup()
{
#ifdef TARGET_OSX
    // Get the absolute location of the executable file in the bundle.
    CFBundleRef appBundle     = CFBundleGetMainBundle();
    CFURLRef    executableURL = CFBundleCopyExecutableURL(appBundle);
    char execFile[4096];
    if (CFURLGetFileSystemRepresentation(executableURL, TRUE, (UInt8 *)execFile, 4096))
    {
        // Strip out the filename to just get the path
        string strExecFile = execFile;
        unsigned long found = strExecFile.find_last_of("/");
        string strPath = strExecFile.substr(0, found);
        
        // Change the working directory to that of the executable
        if(-1 == chdir(strPath.c_str())) {
            ofLog(OF_LOG_ERROR, "Unable to change working directory to executable's directory.");
        }
    }
    else {
        ofLog(OF_LOG_ERROR, "Unable to identify executable's directory.");
    }
    CFRelease(executableURL);
#endif
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
    
    for(int i = 0; i < 90; i++){
        lines[i].clear();
    }
    //read in configuration files
    FILE *fp;
    FILE *fp2;
    fp = fopen("config.txt", "r");
    if(fp == NULL){
        printf("No such file\n");
    }
    else{
        char srp[100];
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &measure);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &zoom);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &note);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &disap);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &hoola);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img9big);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img9small);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img9dom);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7big);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7small);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7dom);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img3big);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img3small);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", imgdisaster);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", imgpalin);
        printf("parse ended\n");
    }
    fclose(fp);
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
    if (msg.status == MIDI_NOTE_OFF){
        //printf("Note %d off\n", msg.pitch);
        int p = msg.pitch;
        unsigned long linsize = lines[p].size();
        if(linsize == 0)return;
        lines[p][linsize - 1].ed    = timer;
        lines[p][linsize - 1].keyup = true;
        
        //for palindrome
        unsigned long sorder = order.size();
        for (int i = 0; i < sorder; i++){
            //printf("order #%d last note: %d\n", i, order[i].ed_note);
            //printf("i = %d sorder = %lu\n", i, sorder);
            if(timer - order[i].life > hoola || order[i].ed_note == p){
                order.erase(order.begin() + i);
                i--;
                sorder--;
                continue;
            }
            if(abs(order[i].ed_note - p) <= 2){
                switch (order[i].direct){
                    case 1:
                        if(order[i].ed_note > p)
                            order[i].direct = 4;
                        else
                            order[i].direct = 1;
                        order[i].ed_note = p;
                        order[i].life = timer;
                        order[i].notes.push_back(p);
                        break;
                    case 2:
                        if(order[i].ed_note > p)
                            order[i].direct = 2;
                        else
                            order[i].direct = 3;
                        order[i].ed_note = p;
                        order[i].notes.push_back(p);
                        order[i].life = timer;
                        break;
                    case 3:
                        if(order[i].ed_note > p){
                            test_palindrome(i);
                            break;
                        }
                        else
                            order[i].direct = 3;
                        order[i].ed_note = p;
                        order[i].notes.push_back(p);
                        order[i].life = timer;
                        break;
                    case 4:
                        if(order[i].ed_note > p){
                            order[i].direct = 4;
                            order[i].ed_note = p;
                            order[i].notes.push_back(p);
                            order[i].life = timer;
                        }
                        else
                            test_palindrome(i);
                        break;
                    case 0:
                        if(order[i].ed_note > p)
                            order[i].direct = 2;
                        else
                            order[i].direct = 1;
                        order[i].ed_note = p;
                        order[i].notes.push_back(p);
                        order[i].life = timer;
                        break;
                    default:
                        printf("Not a valid direction\n");
                        break;
                }       /// switch
            }           /// if diff < 2
        }               ///for
        Nset mynset;
        mynset.direct = 0;
        mynset.st_note = p;
        mynset.ed_note = p;
        mynset.life = timer;
        mynset.notes.clear();
        mynset.notes.push_back(p);
        order.push_back(mynset);
    }
    if (msg.status == MIDI_NOTE_ON && msg.velocity >= 5)
    {
        //search through each member of the note data array
        unsigned long linsize = lines[msg.pitch].size();
        if(linsize == 0 || lines[msg.pitch][linsize - 1].keyup == true){    //add a new member
            opedvol myopedvol;
            myopedvol.id    = msg.pitch;
            myopedvol.op    = timer;
            myopedvol.ed    = timer;
            myopedvol.vol   = msg.velocity;
            myopedvol.keyup = false;       //just in case
            lines[msg.pitch].push_back(myopedvol);
            //printf("Note %d on\n", msg.pitch);
        }
        else{
            lines[msg.pitch][linsize - 1].ed = timer;
        }
        
        for (int i = 0; i < MAX_NUM_OF_NOTES; i++)                  //for new notes
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
                if (timer > 999999999)timer = 0;
                noteData[i].birth_time = timer;
                //records motivation
                if(record){
                    motivation.push_back(noteData[i]);
                }
                Notevec.push_back(noteData[i]);
                if(Notevec.size() > MAX_NUM_OF_NOTES){
                    Notevec.erase(Notevec.begin());
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
    timer += measure;
    unsigned long sorder = order.size();
    for(int i = 0; i < sorder; i++){
        if(timer - order[i].life >= hoola){
            order.erase(order.begin() + i);
            i--;
            sorder--;
            continue;
        }
        else if(timer - order[i].life >= hoola/2)
            test_palindrome(i);
    }
}

//===========================================================================
//The draw() function is called repetitively in an infinite loop along with the update()
//function above, and is designed for drawing to the screen. We use this function for
//three main things:
// 1. For using the stored note data to draw/update circles on the screen
// 2. For updating the background colour
// 3. For display the apps instructions

void ofApp::drawnote(int i, int alpha, int op, int ed, int vol){
    //set the transparency of the circle to be the current time value of the note
    
    //set the colour of the circle based on the notes note number
    switch(i % 12){
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
    ofPoint ppp;
    //draw a circle using the notes ofPoint value to determine the position,
    //and the notes velocity value to determine size of the circle.
    ppp.y = ofGetHeight() - ((i + 6) * ofGetHeight() / 100);
    //printf("from %d to %d\n", op, ed);
    for(int k = op; k < ed; k++){
        if(ed - op < note){
            ppp.x = (k / 10) % ofGetWidth();
            ofCircle(ppp,vol);
            break;
        }
        ppp.x = (k / 10) % ofGetWidth();
        ofCircle(ppp,vol);
    }
    //reduce the notes time value by 1 so that next time this function is called
    //it draws the notes circle with a greater transparency, giving the illusion
    //that the circle is fading out over time
}

void ofApp::draw()
{
    
    //=======================================
    //update the background of the app to be a gradient based on the last received MIDI CC 1 value
    ofBackgroundGradient(0, backgroundColour);
    //=======================================
    
    //draw/update all the notes circles...
    //search through each note/circle
    for (int i = 0; i < 88; i++)
    {
        //if the circle is currently visible
        unsigned long linsize = lines[i].size();
        if(linsize == 0)continue;
        for (int j = 0; j < linsize; j++)
        {
            int alpha;                                              //set transparency
            if(timer - lines[i][j].ed > disap){
                alpha = 0;
            }
            else{
                alpha = 255 - (255 * (timer - lines[i][j].ed) / disap);
            }
            
            if( j == linsize - 1 && lines[i][j].keyup == false)
                drawnote(i, alpha, lines[i][j].op, timer, lines[i][j].vol / zoom);
            else
                drawnote(i, alpha, lines[i][j].op, lines[i][j].ed, lines[i][j].vol / zoom);
        }
        if(timer - lines[i][0].ed > disap){
            lines[i].erase(lines[i].begin());
        }
    }
    if(peek){
        for (int i = 0; i < MAX_NUM_OF_NOTES; i++){
            printf("%d ",Notevec[i].note_num);
        }
        printf("\n");
        peek = false;
    }
    
    test_chord();
    if(!record)
        test_motivation();
    
    //draw image here
    unsigned long size_imgvec = imgvec.size();
    for(int i = 0; i < size_imgvec; i++){
        ofImage img;
        ofLoadImage(img, imgvec[i].path);
        img.update();
        ofSetColor(255, 255, 255);
        img.draw(imgvec[i].posx, imgvec[i].posy, imgvec[i].size, imgvec[i].size);
        if(i % 2){
            imgvec[i].size -= 2;
            imgvec[i].posx += 1;
            imgvec[i].posy += 1;
        }
        if(imgvec[i].size <= 0){
            imgvec.erase(imgvec.begin()+i);
            i--;
            size_imgvec--;
        }
    }
    
#ifdef debug_motivation
    for(int i = 0; i < motivation.size(); i++){
        printf("%d ",motivation[i].note_num);
    }
    printf("\n");
#endif
    
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
        ofDrawBitmapString("Press lowercase 'm' on the keyboard to record your motivation.", 10, last_line_pos + 140);
        
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
    else if(key == 'm'){
        if(!record){
            motivation.clear();
            printf("Start recording\n");
        }
        else{
            printf("End record\n");
            /*
            //erase leading blanks
            while(motivation[0].note_num == 0){
                motivation.erase(motivation.begin());
            }
            //erase rear blanks
            while(motivation.back().note_num == 0){
                motivation.pop_back();
            }*/
        }
        record = !record;
    }
    else if(key == 'p'){
        peek = true;
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
