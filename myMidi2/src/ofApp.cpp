/*
 * Modified from:  2015 Liam Lacey
 * Author:  2017 Joseph Chen
 *
 */

#include "ofApp.h"
#include <stdio.h>
#define img_transparent
//#define quarter
//#define debug_motivation

int measure = 10, zoom = 8, note = 120, hoola = 1200;
int img_size = 25, shrink = 4;
int gap = 20, layer = 3, trio_gap = 200;

//===========================================================================
//The setup() function is called once when the application is first launched.
//This initialises all the applications variables and objects and sets its
//initial state.

int timer = 0;
int imgswap_timer = 5;
long long int last_note_timestamp = 0;
long long int quant_melody = 50;
int rasuto_noto = 0;
bool sweet = false;
int frames[30];
int trill[200];
int policy[30];
int imgsize[30];
int volsiz[30];
int disap[6];

int chord_type9[3][9] = {{0,4,7,11,14,12,16,19,23}, //maj      9 chord
                         {0,3,7,10,14,12,15,19,22}, //min      9 chord
                         {0,4,7,10,14,12,16,19,22}  //dominant 9 chord
};
int chord_type7[8][7] = {{0,4,7,11,12,16,19},       //maj      7 chord
                         {0,3,7,10,12,15,19},       //min      7 chord
                         {0,4,7,10,12,15,19},       //dominant 7 chord
                         {0,3,7,11,12,15,19},       //minmaj   7 chord
                         {0,3,6,10,12,15,18},       //halfdim  7 chord
                         {0,3,6, 9,12,15,18},       //dim      7 chord
                         {0,4,8,11,12,16,20},       //aug      7 chord
                         {0,4,8,10,12,16,18}        //augdom   7 chord
};
int chord_type3[4][5] = {{0,4,7,12,16},             //maj      3 chord
                         {0,3,7,12,15},             //min      3 chord
                         {0,4,8,12,16},             //aug      3 chord
                         {0,3,6,12,15}              //dim      3 chord
};


bool record = false;
double alikeness = 0.0;

enum{
    trio,
    maj9,min9,dom9,
    maj7,min7,dom7,
    mmj7,hdi7,dim7,aug7,ado7,
    maj3,min3,aug3,dim3,
    oth,pal,mot,can,
};

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
    int  live = 1;
    int  posx = 0;
    int  posy = 0;
    int  size = 0;
    int  birth = 0;
    int  id = 0;
    int  base_note = -1;
    int  imgswap_timer = 0;
    int  imgswap_id = 0;
    int  img_movement = 0;
};

vector <opedvol> lines[200];
vector <Nset> order;
vector <img> imgvec;

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
    
    for(int i = 0; i < 200; i++){
        lines[i].clear();
    }
    //read in configuration files
    FILE *fp;
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
        fscanf(fp, "%d", &disap[0]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &disap[1]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &disap[2]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &disap[3]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &disap[4]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &disap[5]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &hoola);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &img_size);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &shrink);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &gap);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &layer);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%d", &trio_gap);
        
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img9big);
        fscanf(fp, "%d%d%d%d", &frames[maj9], &policy[maj9], &imgsize[maj9], &volsiz[maj9]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img9small);
        fscanf(fp, "%d%d%d%d", &frames[min9], &policy[min9], &imgsize[min9], &volsiz[min9]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img9dom);
        fscanf(fp, "%d%d%d%d", &frames[dom9], &policy[dom9], &imgsize[dom9], &volsiz[dom9]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7big);
        fscanf(fp, "%d%d%d%d", &frames[maj7], &policy[maj7], &imgsize[maj7], &volsiz[maj7]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7small);
        fscanf(fp, "%d%d%d%d", &frames[min7], &policy[min7], &imgsize[min7], &volsiz[min7]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7dom);
        fscanf(fp, "%d%d%d%d", &frames[dom7], &policy[dom7], &imgsize[dom7], &volsiz[dom7]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7mmj);
        fscanf(fp, "%d%d%d%d", &frames[mmj7], &policy[mmj7], &imgsize[mmj7], &volsiz[mmj7]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7hdi);
        fscanf(fp, "%d%d%d%d", &frames[hdi7], &policy[hdi7], &imgsize[hdi7], &volsiz[hdi7]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7dim);
        fscanf(fp, "%d%d%d%d", &frames[dim7], &policy[dim7], &imgsize[dim7], &volsiz[dim7]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7aug);
        fscanf(fp, "%d%d%d%d", &frames[aug7], &policy[aug7], &imgsize[aug7], &volsiz[aug7]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img7ado);
        fscanf(fp, "%d%d%d%d", &frames[ado7], &policy[ado7], &imgsize[ado7], &volsiz[ado7]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img3big);
        fscanf(fp, "%d%d%d%d", &frames[maj3], &policy[maj3], &imgsize[maj3], &volsiz[maj3]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img3small);
        fscanf(fp, "%d%d%d%d", &frames[min3], &policy[min3], &imgsize[min3], &volsiz[min3]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img3dim);
        fscanf(fp, "%d%d%d%d", &frames[dim3], &policy[dim3], &imgsize[dim3], &volsiz[dim3]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", img3aug);
        fscanf(fp, "%d%d%d%d", &frames[aug3], &policy[aug3], &imgsize[aug3], &volsiz[aug3]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", imgdisaster);
        fscanf(fp, "%d%d%d%d", &frames[oth], &policy[oth], &imgsize[oth], &volsiz[oth]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", imgpalin);
        fscanf(fp, "%d%d%d%d", &frames[pal], &policy[pal], &imgsize[pal], &volsiz[pal]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", imgtrio);
        fscanf(fp, "%d%d%d%d", &frames[trio], &policy[trio], &imgsize[trio], &volsiz[trio]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", candy);
        fscanf(fp, "%d%d%d%d", &frames[can], &policy[can], &imgsize[can], &volsiz[can]);
        fscanf(fp, "%s", srp);
        fscanf(fp, "%s", background);
        printf("parse ended\n");
    }
    fclose(fp);
}

void clean(){
    for(int i = 0; i < 200; i++){
        lines[i].clear();
    }
    order.clear();
    imgvec.clear();
    timer = 0;
    last_note_timestamp = 0;
    rasuto_noto = 0;
    return;
}

// small 9chord priority > 7chord > 3chord big
bool check_collision(int base, int id){
    unsigned long ss = imgvec.size();
    for(int i = 0; i < ss; i++){
        //priority block
        if(imgvec[i].base_note == base && imgvec[i].birth > timer - 200 ){
            if(imgvec[i].id > id){
                imgvec.erase(imgvec.begin()+i);
                ss--;
                i--;
            }
            else{
                return true;
            }
        }
        //generated at the same time
        if(lines[base].back().op - imgvec[i].birth < 30){
            return true;
        }
    }
    return false;
}

void ofApp::test_palindrome(int i){
    //do re mi re do - like notes detection
    //needs later part exactly replicated
    
    if(order[i].st_note == order[i].ed_note){
        bool last = false;
        unsigned long ss = order[i].notes.size();
        
        if(ss <= 4)
            //returns short instances
            return;

        for(int j = 0; j < ss; j++){
            if(order[i].notes[j] != order[i].notes[ss - j - 1])
                return;
        }
        unsigned long svec = imgvec.size();
        for(int j = 0; j < svec; j++){
            if(imgvec[j].id == pal && imgvec[j].birth >= lines[order[i].st_note].back().op){
                if(imgvec[j].live == 0)
                    imgvec[j].live = 1;
                return;
            }
            else if((imgvec[j].base_note == i) && timer - imgvec[j].birth < hoola){
                last = true;
            }
        }
        if(last){
            return;
        }
        /*/smash
        if(lines[order[i].st_note][lines[order[i].st_note].size()-2].op >= lines[order[i].notes[(ss+1)/2]].back().op || lines[order[i].notes[(ss+1)/2]].back().op >= lines[order[i].ed_note].back().op){
            return;
        }*/
        //put image in to-print vector
        
        img myimg;
        myimg.live = 1;
        myimg.birth = timer;
        myimg.path = imgpalin;
        printf("%s\n",imgpalin);
        myimg.posx = (myimg.size / 2) + (rand() % (ofGetWidth() - myimg.size));
        myimg.posy = (myimg.size / 2) + (rand() % (ofGetHeight() - myimg.size));
        myimg.size  = imgsize[myimg.id];
        if(volsiz[pal] == 1)
            myimg.size = (int)order[i].notes.size() * 6 * myimg.size;
        myimg.id = pal;
        myimg.base_note = order[i].st_note;
        if(check_collision(myimg.base_note, myimg.id) == false)
            imgvec.push_back(myimg);
    }
}

void ofApp::test_trio(){
    for(int i = 0; i < 200; i++){
        if(lines[i].size() > 0 && lines[i].back().keyup == false){
            unsigned long ss = imgvec.size();
            for(int j = 0; j < ss; j++){
                if(imgvec[j].id == trio && imgvec[j].base_note == i && imgvec[j].live == 1){
                    imgvec[j].birth = timer - 30;
                }
            }
        }
    }
    if(timer % 600 == 0){
        for(int i = 0; i < 198; i++){
            bool flag = false;
            if(trill[i] >= 3 && trill[i+1] >= 3){
                flag = true;
            }
            if(trill[i] >= 3 && trill[i+2] >= 3){
                flag = true;
            }
            if(flag){
                unsigned long ss = imgvec.size();
                bool flag2 = false;
                for(int j = 0; j < ss; j++){
                    if(imgvec[j].id == trio && imgvec[j].base_note == i && imgvec[j].live == 1){
                        flag2 = true;
                    }
                }
                if(flag2){
                    continue;
                }
                img myimg;
                myimg.base_note = i;
                myimg.birth = timer;
                myimg.id = trio;
                myimg.live = 1;
                myimg.path = imgtrio;
                myimg.posx = (myimg.size / 2) + (rand() % (ofGetWidth() - myimg.size));
                myimg.posy = (myimg.size / 2) + (rand() % (ofGetHeight() - myimg.size));
                myimg.posy /= layer;
                int imglayer = (layer * (myimg.base_note - 21) / 87);
                myimg.posy += imglayer * ofGetHeight() / layer;
                myimg.posy = ofGetHeight() - myimg.posy;
                myimg.size = imgsize[myimg.id];
                if(volsiz[myimg.id] == 1)
                    myimg.size = lines[myimg.base_note].back().vol * myimg.size;
                imgvec.push_back(myimg);
            }
        }
        for(int i = 0; i < 200; i++){
            trill[i] = 0;
        }
    }
}

void ofApp::test_motivation(){
    for(int i = 0; i < MAX_NUM_OF_NOTES - motivation.size(); i++){
        if(noteData[i].note_num == 0)
            continue;
        alikeness = 0.0;
        
        for(int j = 0; j < motivation.size(); j++){
            int difference = noteData[i].note_num - motivation[0].note_num;
            if(abs(noteData[i+j].note_num  - motivation[j].note_num - difference) <= 1 && noteData[i+j].time_counter > 200){
                alikeness += 1/(double)motivation.size();
            }
            if(alikeness >= 0.9){
                ofImage maple;
                maple.load("images/motivations/pic1.bmp");
                ofSetColor(255, 255, 255, noteData[i].time_counter);
                maple.draw(ofGetWidth() - ((noteData[i].note_num - 20) * ofGetWidth() / 120),ofGetHeight() - ((noteData[i].note_num - 20) * ofGetHeight() / 120),noteData[i].note_vel*1.3,noteData[i].note_vel*1.3);
            }
        }
    }
}

bool ofApp::chord9test(int i, bool* kdown){
    for(int j = 0; j < 3; j++){
        int cnt = 0;
        for(int k = 0; k < 5; k++){
            // 9 chord test / trans
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
                //find success
                img myimg;
                switch(j){
                    case 0:
                        myimg.path = img9big;
                        myimg.id = maj9;
                        break;
                    case 1:
                        myimg.path = img9small;
                        myimg.id = min9;
                        break;
                    case 2:
                        myimg.path = img9dom;
                        myimg.id = dom9;
                        break;
                    default:
                        fprintf(stderr,"No such type, but why?\n");
                        break;
                }
                //switch for different chords
                int newid = myimg.id;
                unsigned long ss = imgvec.size();
                //id for each image -- unique
                for(int m = 0; m < ss; m++){
                    //note line (====) [img]
                    if(imgvec[m].id == newid && imgvec[m].birth >= lines[i].back().op){
                        if(imgvec[j].live == 0)
                            imgvec[m].live = 1;
                        return true;
                    }
                    else if(imgvec[m].base_note == i && timer - imgvec[m].birth <= gap){
                        return true;
                    }
                }
                myimg.base_note = i;
                myimg.birth = timer;
                myimg.id    = newid;
                myimg.size  = imgsize[myimg.id];
                if(volsiz[myimg.id] == 1)
                    myimg.size  = lines[i + chord_type9[j][k+endpt] - chord_type9[j][k]].back().vol * myimg.size;
                myimg.posx  = (myimg.size / 2) + (rand() % (ofGetWidth() - myimg.size));
                myimg.posy  = (myimg.size / 2) + (rand() % (ofGetHeight() - myimg.size));
                myimg.posy /= layer;
                int imglayer = (layer * (myimg.base_note - 21) / 87);
                myimg.posy += imglayer * ofGetHeight() / layer;
                myimg.posy = ofGetHeight() - myimg.posy;
                if(check_collision(myimg.base_note, myimg.id) == false)
                    imgvec.push_back(myimg);
                return true;
            }
        }
    }
    return false;
}
bool ofApp::chord7test(int i, bool* kdown){
    for(int j = 0; j < 8; j++){
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
            img myimg;
            switch(j){
                case 0:
                    myimg.path = img7big;
                    myimg.id = maj7;
                    break;
                case 1:
                    myimg.path = img7small;
                    myimg.id = min7;
                    break;
                case 2:
                    myimg.path = img7dom;
                    myimg.id = dom7;
                    break;
                case 3:
                    myimg.path = img7mmj;
                    myimg.id = mmj7;
                    break;
                case 4:
                    myimg.path = img7hdi;
                    myimg.id = hdi7;
                    break;
                case 5:
                    myimg.path = img7dim;
                    myimg.id = dim7;
                    break;
                case 6:
                    myimg.path = img7aug;
                    myimg.id = aug7;
                    break;
                case 7:
                    myimg.path = img7ado;
                    myimg.id = ado7;
                    break;
                default:
                    fprintf(stderr,"No such type, but why?\n");
                    break;
            }
            if(cnt >= 4){
                unsigned long ss = imgvec.size();
                int newid = myimg.id;
                for(int m = 0; m < ss; m++){
                    if(imgvec[m].id == newid && imgvec[m].birth >= lines[i].back().op){
                        if(imgvec[j].live == 0)
                            imgvec[m].live = 1;
                        return true;
                    }
                    else if(imgvec[m].base_note == i && timer - imgvec[m].birth <= gap){
                        return true;
                    }
                }
                myimg.base_note = i;
                myimg.birth = timer;
                myimg.size  = imgsize[myimg.id];
                if(volsiz[myimg.id] == 1)
                    myimg.size = lines[i + chord_type7[j][k+endpt] - chord_type7[j][k]].back().vol * myimg.size;
                myimg.posx = (myimg.size / 2) + (rand() % (ofGetWidth() - myimg.size));
                myimg.posy = (myimg.size / 2) + (rand() % (ofGetHeight() - myimg.size));
                myimg.posy /= layer;
                int imglayer = (layer * (myimg.base_note - 21) / 87);
                myimg.posy += imglayer * ofGetHeight() / layer;
                myimg.posy = ofGetHeight() - myimg.posy;
                if(check_collision(myimg.base_note, myimg.id) == false)
                    imgvec.push_back(myimg);
                return true;
            }
        }
    }
    return false;
}
bool ofApp::chord3test(int i, bool* kdown){
    for(int j = 0; j < 4; j++){
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
            img myimg;
            switch(j){
                case 0:
                    myimg.path = img3big;
                    myimg.id = maj3;
                    break;
                case 1:
                    myimg.path = img3small;
                    myimg.id = min3;
                    break;
                case 2:
                    myimg.path = img3aug;
                    myimg.id = aug3;
                    break;
                case 3:
                    myimg.path = img3dim;
                    myimg.id = dim3;
                    break;
                default:
                    fprintf(stderr,"No such type, but why?\n");
                    break;
            }
            if(cnt >= 3){
                unsigned long ss = imgvec.size();
                int newid = myimg.id;
                for(int m = 0; m < ss; m++){
                    if(imgvec[m].id == newid && imgvec[m].birth >= lines[i].back().op){
                        if(imgvec[j].live == 0)
                            imgvec[m].live = 1;
                        return true;
                    }
                    else if(imgvec[m].base_note == i && timer - imgvec[m].birth <= gap){
                        return true;
                    }
                }
                
                myimg.base_note = i;
                myimg.birth = timer;
                myimg.size  = imgsize[myimg.id];
                if(volsiz[myimg.id] == 1)
                    myimg.size = lines[i + chord_type3[j][k+endpt] - chord_type3[j][k]].back().vol * myimg.size;
                myimg.posx = (myimg.size / 2) + (rand() % (ofGetWidth() - myimg.size));
                myimg.posy = (myimg.size / 2) + (rand() % (ofGetHeight() - myimg.size));
                myimg.posy /= layer;
                int imglayer = (layer * (myimg.base_note - 21) / 87);
                myimg.posy += imglayer * ofGetHeight() / layer;
                myimg.posy = ofGetHeight() - myimg.posy;
                if(check_collision(myimg.base_note, myimg.id) == false)
                    imgvec.push_back(myimg);
                return true;
            }
        }
    }
    return false;
}

void ofApp::test_chord(){
    //keyDown the keys pressed down
    bool kdown[200] = {0};
    
    // code for melody line
    for(int i = 0; i < 200; i++){
        if(lines[i].size() == 0)
            continue;
        if(lines[i].back().keyup == false)
            kdown[i] = 1;
    }
    
    int downcount = 0;
    int dcnt = 0;
    int dd = 0;
    
    //search through every base note
    for(int i = 0; i < 200; i++){
        if(kdown[i] == 1){
            if(dd == 0){
                dd = i;
            }
            downcount += 1;
            dcnt = i;
            if(downcount >= 6){
                break;
            }
        }
    }
    
    if(downcount >= 6){
        img myimg;
        myimg.path = imgdisaster;
        myimg.birth = timer;
        myimg.id = oth;
        myimg.base_note = dd;
        unsigned long ss = imgvec.size();
        for(int m = 0; m < ss; m++){
            if(dd == 0)
                break;
            if(imgvec[m].id == myimg.id && imgvec[m].birth >= lines[dd].back().op){
                return;
            }
            else if(imgvec[m].base_note == myimg.base_note && timer - imgvec[m].birth <= gap){
                return;
            }
        }
        myimg.size  = imgsize[myimg.id] * 40;
        myimg.posx = rand() % ofGetWidth();
        myimg.posy = rand() % ofGetHeight();
        if(check_collision(myimg.base_note, myimg.id) == false)
            imgvec.push_back(myimg);
    }
    else{
        for(int i = 0; i < 200; i++){
            if(kdown[i] == 1){
                // 9 chord test
                if(chord9test(i, kdown)){
                    continue;
                }
                // 7 chord test
                if(chord7test(i, kdown)){
                    continue;
                }
                // 3 chord test
                if(chord3test(i, kdown)){
                    continue;
                }
            }
        }
    }
}

//===========================================================================
//The newMidiMessage() function is called each time the application receives
//a new MIDI message. For this application we use this function to set the
//array of note data values, as well as for setting the apps background colour.
//Note that this function only sets values - the drawing of things based on these
//values is done within the draw() function below.

void ofApp::newMidiMessage (ofxMidiMessage& msg)
{
    //if we have received a note-off message
    if (msg.status == MIDI_NOTE_OFF){
        //printf("Note %d off\n", msg.pitch);
        int p = msg.pitch;
        unsigned long linsize = lines[p].size();
        if(linsize == 0)return;
        lines[p][linsize - 1].ed    = timer;
        lines[p][linsize - 1].keyup = true;
        trill[p] += 1;
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
    if (timer > 999999){
        clean();
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
            ofSetColor(255,  0,  0, alpha);
            break;
            
        case 1:
            ofSetColor(238,130,238, alpha);
            break;

        case 2:
            ofSetColor(255,255,  0, alpha);
            break;
            
        case 3:
            ofSetColor(255,160,122, alpha);
            break;
            
        case 4:
            ofSetColor(135,206,235, alpha);
            break;
            
        case 5:
            ofSetColor(139,  0,  0, alpha);
            break;
            
        case 6:
            ofSetColor( 66,192,251, alpha);
            break;
            
        case 7:
            ofSetColor(255,140,  0, alpha);
            break;
            
        case 8:
            ofSetColor(221,160,221, alpha);
            break;
            
        case 9:
            ofSetColor(  0,128,  0, alpha);
            break;
            
        case 10:
            ofSetColor(199, 21,133, alpha);
            break;
            
        case 11:
            ofSetColor(  0,  0,255, alpha);
            break;
            
        default:
            printf("No such note!\n");
            break;
    };
    ofPoint ppp;
    //draw a circle using the notes ofPoint value to determine the position,
    //and the notes velocity value to determine size of the circle.
    ppp.y = ofGetHeight() - ((i - 15) * ofGetHeight() / 115);
    for(int k = op; k < ed; k++){
        if(ed - op < note){
            ppp.x = (k / 10) % ofGetWidth();
            if(sweet){
                ofImage cdy;
                ofSetColor(255, 255, 255);
                ofLoadImage(cdy, candy);
                cdy.update();
                cdy.draw(ppp, vol * img_size/10, vol * img_size/10);
            }
            else{
                ofCircle(ppp,vol * img_size/30);
            }
            break;
        }
        ppp.x = (k / 10) % ofGetWidth();
        if(sweet){
            ofImage cdy;
            ofSetColor(255, 255, 255);
            ofLoadImage(cdy, candy);
            cdy.update();
            cdy.draw(ppp, vol * img_size/10, vol * img_size/10);
        }
        else{
            ofCircle(ppp,vol * img_size/30);
        }
    }
    //reduce the notes time value by 1 so that next time this function is called
    //it draws the notes circle with a greater transparency, giving the illusion
    //that the circle is fading out over time
}

inline int min(int a, int b){return a > b ? b : a;}

void drawimage(int i){
    if(timer - imgvec[i].birth < 30){
        return;
    }
    ofImage img;
    //modify between image names
    string s = imgvec[i].path;
    if(s == "NONE"){
        return;
    }
    s.insert(s.end()-4, '_');
    s.insert(s.end()-4,'1'+imgvec[i].imgswap_id);
    ofLoadImage(img, s.c_str());
    img.update();
    ofSetColor(255, 255, 255);
    #ifdef img_transparent
   
    int alpha0 = 2 * lines[imgvec[i].base_note].back().vol;
    int alpha2 = alpha0 - (alpha0 * min(disap[policy[imgvec[i].id]-1],timer-imgvec[i].birth) / (disap[policy[imgvec[i].id] - 1]));
    ofSetColor(255, 255, 255, alpha2);
    #endif
    img.draw(imgvec[i].posx, imgvec[i].posy - imgvec[i].size, imgvec[i].size, imgvec[i].size);
 
    if(frames[imgvec[i].id] != 1 && imgvec[i].imgswap_timer > imgswap_timer){
        imgvec[i].imgswap_timer = 0;
        imgvec[i].imgswap_id += 1;
        /* Loop gif image*/
        if(imgvec[i].imgswap_id >= frames[imgvec[i].id])
            imgvec[i].imgswap_id = 0;
    }
    else{
        imgvec[i].imgswap_timer++;
    }
}

unsigned long image_fade(int i, unsigned long size_imgvec){
    if(timer % shrink == 0){
        imgvec[i].size -= 2;
        imgvec[i].posx += 1;
        imgvec[i].posy += 1;
    }
    if(imgvec[i].size <= 0 || imgvec[i].posy > ofGetHeight() || imgvec[i].imgswap_id >= 4){
        imgvec.erase(imgvec.begin()+i);
        i--;
        size_imgvec--;
    }
    return size_imgvec;
}

unsigned long image_dissapear(int i, unsigned long size_imgvec){
    if(imgvec[i].id == 3039751){
        if(timer - imgvec[i].birth > disap[policy[imgvec[i].id] - 1]){
            imgvec[i].id = 3039752;
        }
        if(imgvec[i].live == 0)
            imgvec[i].live = 1;
    }
    if(imgvec[i].live == 0){
        if(timer - imgvec[i].birth > disap[policy[imgvec[i].id] - 1]){
            imgvec.erase(imgvec.begin()+i);
            i--;
            size_imgvec--;
        }
    }
    return size_imgvec;
}

unsigned long image_custom(int i, unsigned long size_imgvec){
    if(timer % shrink == 0){
        //    x0 x1
        // y0
        // y1
        if(imgvec[i].size != 0){
            imgvec[i].posx += ((ofGetWidth()/2 - imgvec[i].posx) * 2 / imgvec[i].size);
            imgvec[i].posy += ((ofGetHeight()/2 - imgvec[i].posy) * 2 / imgvec[i].size);
        }
        imgvec[i].size -= 2;
    }
    if(imgvec[i].size <= 0){
        imgvec.erase(imgvec.begin()+i);
        i--;
        size_imgvec--;
    }
    return size_imgvec;
}

unsigned long image_custom2(int i, unsigned long size_imgvec){
    //    x0 x1
    // y0
    // y1
    if(timer % 90 == 0)
        imgvec[i].posx += (random() % (6 * ofGetWidth() / disap[policy[imgvec[i].id] - 1])) - (3 * ofGetWidth() / disap[policy[imgvec[i].id] - 1]);
    if(imgvec[i].size != 0)
        imgvec[i].posy += ((ofGetHeight()/6 - imgvec[i].posy) * 2 / imgvec[i].size);
    imgvec[i].size -= 2;
    if(imgvec[i].size <= 0){
        imgvec.erase(imgvec.begin()+i);
        i--;
        size_imgvec--;
    }
    return size_imgvec;
}

unsigned long image_custom3(int i, unsigned long size_imgvec){
    //    x0 x1
    // y0
    // y1
    int delta = ofGetWidth() / disap[policy[imgvec[i].id] - 1];
    imgvec[i].posx += delta;
    if(imgvec[i].size <= 0 || imgvec[i].posx > ofGetWidth()){
        imgvec.erase(imgvec.begin()+i);
        i--;
        size_imgvec--;
    }
    return size_imgvec;
}

unsigned long image_custom4(int i, unsigned long size_imgvec){
    //    x0 x1
    // y0
    // y1
    int delta = ofGetWidth() / disap[policy[imgvec[i].id] - 1];
    imgvec[i].posx -= delta;
    if(imgvec[i].size <= 0 || imgvec[i].posx <= 0){
        imgvec.erase(imgvec.begin()+i);
        i--;
        size_imgvec--;
    }
    return size_imgvec;
}

unsigned long image_custom5(int i, unsigned long size_imgvec){
    //    x0 x1
    // y0
    // y1
    int delta = 10*ofGetHeight() / disap[policy[imgvec[i].id] - 1];
    if(imgvec[i].posy < ofGetHeight())
        imgvec[i].posy += delta;
    if(timer - imgvec[i].birth > disap[policy[imgvec[i].id] - 1]){
        imgvec.erase(imgvec.begin()+i);
        i--;
        size_imgvec--;
    }
    return size_imgvec;
}

void ofApp::draw()
{
    
    //=======================================
    //update the background of the app to be a gradient based on the last received MIDI CC 1 value
    ofBackgroundGradient(0, backgroundColour);
    //=======================================
    ofImage bkgd;
    if(strcmp(background,"NONE") != 0){
        ofLoadImage(bkgd,background);
        ofSetColor(255, 255, 255);
        bkgd.update();
        bkgd.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    //draw/update all the notes circles...
    //search through each note/circle
    for (int i = 0; i < 200; i++)
    {
        //if the circle is currently visible
        unsigned long linsize = lines[i].size();
        if(linsize == 0)continue;
        for (int j = 0; j < linsize; j++)
        {
            //set transparency
            int alpha;
            //Detect: not the same note
            if(timer - lines[i][j].ed > disap[0]){
                alpha = 0;
            }
            //Released note
            else if(lines[i][j].keyup == true){
                alpha = 255 - (255 * (timer - lines[i][j].ed) / disap[0]);
                unsigned long ss = imgvec.size();
                for(int k = 0; k < ss; k++){
                    if(imgvec[k].base_note == i && imgvec[k].id != trio){
                        imgvec[k].live = 0;
                    }
                }
            }
            
            //draw note
            if( j == linsize - 1 && lines[i][j].keyup == false)
                drawnote(i, 255, lines[i][j].op, timer, lines[i][j].vol / zoom);
            else
                drawnote(i, alpha, lines[i][j].op, lines[i][j].ed, lines[i][j].vol / zoom);
        }
        if(timer - lines[i][0].ed > disap[0] && lines[i][0].keyup == true){
            lines[i].erase(lines[i].begin());
        }
    }
    
    unsigned long ss = imgvec.size();
    for(int i = 0; i < ss; i++){
        if(imgvec[i].id == trio && (timer - imgvec[i].birth > trio_gap)){
            imgvec[i].live = 0;
        }
    }
    
    
    //test chord here
    test_chord();
    if(!record)
        test_motivation();
    //test trio here
    test_trio();
    
    //draw image here
    unsigned long size_imgvec = imgvec.size();
    for(int i = 0; i < size_imgvec; i++){
        drawimage(i);
        //image dissapear after key lift
        switch(policy[imgvec[i].id]){
            case 1:
                if(imgvec[i].live == 0)
                    size_imgvec = image_dissapear(i, size_imgvec);
                break;
            case 2:
                if(imgvec[i].live == 0)
                    size_imgvec = image_custom(i, size_imgvec);
                break;
            case 3:
                if(imgvec[i].live == 0)
                    size_imgvec = image_custom2(i, size_imgvec);
                break;
            case 4:
                if(imgvec[i].live == 0)
                    size_imgvec = image_custom3(i, size_imgvec);
                break;
            case 5:
                if(imgvec[i].live == 0)
                    size_imgvec = image_custom4(i, size_imgvec);
                break;
            default:
                if(imgvec[i].live == 0)
                    size_imgvec = image_custom5(i, size_imgvec);
                break;
        }
    }
    //print note number for motivation recording
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
        ofDrawBitmapString("Press lowercase 'p' on the keyboard to start.", 10, last_line_pos + 140);
        ofDrawBitmapString("Press lowercase 'b' on the keyboard to switch note image.", 10, last_line_pos + 160);
    } //if (showingInstructions)
}

//===========================================================================
//The keyPressed() function is called each time a key on the QWERTY keyboard
//is pressed. For this application we use this for toggling the instructions
//on and off as well as for setting the MIDI input we want to connect to.

void ofApp::keyPressed(int key)
{
    if (key == 'b'){
        sweet = !sweet;
    }
    else if( key == 'p'){
        clean();
    }
    //if key 's' has been pressed
    else if (key == 's')
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
        }
        record = !record;
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
