//
//  fms4.cpp
//  fms4
//
//  Created by marvin h on 9/27/15.
//  Copyright (c) 2015 marvin h. All rights reserved.
//

#include "fms4.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TABLE_SIZE 2048
AudioEffect *createEffectInstance(audioMasterCallback audioMaster)
{
    return new fms4(audioMaster);
}

fms4::fms4(audioMasterCallback audioMaster) : AudioEffectX(audioMaster, NPROGS, NPARAMS)
{
    mTable = new float[TABLE_SIZE];
    
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        mTable[i] = sin( i/float(TABLE_SIZE) * 2. * M_PI);
    }
    for (int v = 0; v<NVOICES; v++) {
        for(int i = 0; i < 4 ; i++){
            mVS[v].mEnv_ctx[i].mStage=kIdle;
            mVS[v].mEnv_ctx[i].mLevel=0.0f;
            mVS[v].mEnv_ctx[i].mEnvValue=0.0f;
            mVS[v].mEnv_ctx[i].mPrev=0.0f;
            mVS[v].mOsc_ctx[0].mod[i]=0.0f;
            mVS[v].mOsc_ctx[1].mod[i]=0.0f;
            mVS[v].mOsc_ctx[2].mod[i]=0.0f;
            mVS[v].mOsc_ctx[3].mod[i]=0.0f;
            mVS[v].mOsc_ctx[i].mPhase=0.0f;
            mVS[v].mOsc_ctx[i].mPhaseIncr=0.0f;
            OutPut[i]= 0.0f;
        }
        mVS[v].age=0;
    }
    
    
    for(int i = 0; i < 4 ; i++){
        mOsc[i] = new CWTOsc(mTable, TABLE_SIZE);
        mEnv[i] = new ADSR();
    }
    
    VstInt32 i=0;
    Fs = 44100.0f;
    voices=16;
    activevoices=0;
    programs = new fms4Program[NPROGS];
    for(int i =0;i<NPARAMS;i++){
        pPatch[i] = 0.0f;
        if(i==kSustain1){
            pPatch[i]=1.f;
        }
        else if(i==kPan1||i==kPan2||i==kPan3||i==kPan4){
            pPatch[i]=.5;
        }
        else if (i == kOutPut1){
            pPatch[i]=1.0f;
        }
    }
    if(programs){
        fillpatch(i++, "default",0, pPatch);
        fillpatch(i++, "init", 0,pPatch);
    }
    if(audioMaster)
    {
        setNumInputs(0);
        setNumOutputs(NOUTS);
        canProcessReplacing();
        isSynth();
        setUniqueID('semf');
    }
    
    for (int i=0; i<128; i++) {
        notes[i]=EVENTS_DONE;
    }
    
    setSampleRate(Fs);
    update();
    voiceUpdate();
    suspend();
    
    extern AEffGUIEditor* createEditor (AudioEffectX*);
    setEditor (createEditor(this));
    
}

void fms4::update()  //parameter change //if multitimbral would have to move all this...
{
    float * param = programs[curProgram].param;
    
    mEnv[0]->setStageTime(kStageAttack,param[kAttack1]);
    mEnv[0]->setStageTime(kStageDecay,param[kDecay1]);
    mEnv[0]->setSustainLevel(mPS[kSustain1].Process(param[kSustain1]));
    mEnv[0]->setStageTime(kStageRelease,param[kRelease1]);
    
    mEnv[1]->setStageTime(kStageAttack,param[kAttack2]);
    mEnv[1]->setStageTime(kStageDecay,param[kDecay2]);
    mEnv[1]->setSustainLevel(mPS[kSustain2].Process(param[kSustain2]));
    mEnv[1]->setStageTime(kStageRelease,param[kRelease2]);
    
    
    mEnv[2]->setStageTime(kStageAttack,param[kAttack3]);
    mEnv[2]->setStageTime(kStageDecay,param[kDecay3]);
    mEnv[2]->setSustainLevel(mPS[kSustain3].Process((param[kSustain3])));
    mEnv[2]->setStageTime(kStageRelease,param[kRelease3]);
    
    
    mEnv[3]->setStageTime(kStageAttack,param[kAttack4]);
    mEnv[3]->setStageTime(kStageDecay,param[kDecay4]);
    mEnv[3]->setSustainLevel(mPS[kSustain4].Process(param[kSustain4]));
    mEnv[3]->setStageTime(kStageRelease,param[kRelease4]);
    
    mOsc[0]->modAmp[0]= mPS[kMod1to1].Process(param[kMod1to1]);
    mOsc[0]->modAmp[1]= mPS[kMod2to1].Process(param[kMod2to1]);
    mOsc[0]->modAmp[2]= mPS[kMod3to1].Process(param[kMod3to1]);
    mOsc[0]->modAmp[3]= mPS[kMod4to1].Process(param[kMod4to1]);
    
    mOsc[1]->modAmp[0]= mPS[kMod1to2].Process(param[kMod1to2]);
    mOsc[1]->modAmp[1]= mPS[kMod2to2].Process(param[kMod2to2]);
    mOsc[1]->modAmp[2]= mPS[kMod3to2].Process(param[kMod3to2]);
    mOsc[1]->modAmp[3]= mPS[kMod4to2].Process(param[kMod4to2]);
    
    mOsc[2]->modAmp[0]= mPS[kMod1to3].Process(param[kMod1to3]);
    mOsc[2]->modAmp[1]= mPS[kMod2to3].Process(param[kMod2to3]);
    mOsc[2]->modAmp[2]= mPS[kMod3to3].Process(param[kMod3to3]);
    mOsc[2]->modAmp[3]= mPS[kMod4to3].Process(param[kMod4to3]);
    
    mOsc[3]->modAmp[0]= mPS[kMod1to4].Process(param[kMod1to4]);
    mOsc[3]->modAmp[1]= mPS[kMod2to4].Process(param[kMod2to4]);
    mOsc[3]->modAmp[2]= mPS[kMod3to4].Process(param[kMod3to4]);
    mOsc[3]->modAmp[3]= mPS[kMod4to4].Process(param[kMod4to4]);
    
    OutPut[0] = mPS[kOutPut1].Process(param[kOutPut1]);
    OutPut[1] = mPS[kOutPut2].Process(param[kOutPut2]);
    OutPut[2] = mPS[kOutPut3].Process(param[kOutPut3]);
    OutPut[3] = mPS[kOutPut4].Process(param[kOutPut4]);
    
    Pan[0] = mPS[kPan1].Process((param[kPan1]-1.f)+.5f);
    Pan[1] = mPS[kPan2].Process((param[kPan2]-1.f)+.5f);
    Pan[2] = mPS[kPan3].Process((param[kPan3]-1.f)+.5f);
    Pan[3] = mPS[kPan4].Process((param[kPan4]-1.f)+.5f);
}
void fms4::voiceUpdate(){
    float * param = programs[curProgram].param;
    for (int v = 0; v<NVOICES; v++) {
        for(int i = 0; i < 4 ; i++){
            mVS[v].mEnv_ctx[i].mStage=kIdle;
            mVS[v].mEnv_ctx[i].mLevel=0.0f;
            mVS[v].mEnv_ctx[i].mEnvValue=0.0f;
            mVS[v].mOsc_ctx[0].mod[i]=0.0f;
            mVS[v].mOsc_ctx[1].mod[i]=0.0f;
            mVS[v].mOsc_ctx[2].mod[i]=0.0f;
            mVS[v].mOsc_ctx[3].mod[i]=0.0f;
            mVS[v].mOsc_ctx[i].mPhase=0.0f;
            mVS[v].mOsc_ctx[i].mPhaseIncr=0.0f;
        }
        mVS[v].age=0;
    }
    voices=(param[kVoices]*15)+1;
}
void fms4::setParameter(VstInt32 index, float value)
{
    if (index < kNumParams)
    {
        programs[curProgram].param[index] = value;
        if (editor)
            ((AEffGUIEditor*)editor)->setParameter(index, value);
    }
    
    if(index==kVoices){
        voiceUpdate();
    }
}
void fms4::setSampleRate(float sampleRate)
{
    AudioEffectX::setSampleRate(sampleRate);
    Fs = sampleRate;
    for (int i = 0; i<4; i++) {
        mEnv[i]->setSampleRate(Fs);
    }
}

void fms4::resume()
{
    DECLARE_VST_DEPRECATED (wantEvents) ();
}

fms4::~fms4 ()  //destroy any buffers...
{
    for(int i=0; i <4 ; i++){
        delete  mOsc[i];
        delete  mEnv[i];
        
    }
    delete [] programs;
    delete mTable;
}

void fms4::setProgram(VstInt32 program)
{
    curProgram = program;
    update();
    voiceUpdate();
}

void fms4::fillpatch(VstInt32 p, char *name,int v,float patch[])
{
    strcpy(programs[p].name, name);
    programs[p].param[0] = 1;
    for (int i = 1; i < NPARAMS; i++) {
        programs[p].param[i] = patch[i];
    }
    
}

float fms4::getParameter(VstInt32 index)     { return programs[curProgram].param[index]; }
void  fms4::setProgramName(char *name)   { strcpy(programs[curProgram].name, name); }
void  fms4::getProgramName(char *name)   { strcpy(name, programs[curProgram].name); }
void  fms4::setBlockSize(VstInt32 blockSize) {	AudioEffectX::setBlockSize(blockSize); }
bool  fms4::getEffectName(char* name)    { strcpy(name, "fms4"); return true; }
bool  fms4::getVendorString(char* text)  {	strcpy(text, "marvinh"); return true; }
bool  fms4::getProductString(char* text) { strcpy(text, "fms4"); return true; }

bool fms4::getOutputProperties(VstInt32 index, VstPinProperties* properties)
{
    if(index<NOUTS)
    {
        sprintf(properties->label, "fms4");
        properties->flags = kVstPinIsActive;
        if(index<2) properties->flags |= kVstPinIsStereo; //make channel 1+2 stereo
        return true;
    }
    return false;
}


bool fms4::getProgramNameIndexed(VstInt32 category, VstInt32 index, char* text)
{
    if ((unsigned int)index < NPROGS)
    {
        strcpy(text, programs[index].name);
        return true;
    }
    return false;
}


bool fms4::copyProgram(VstInt32 destination)
{
    if(destination<NPROGS)
    {
        programs[destination] = programs[curProgram];
        return true;
    }
    return false;
}


VstInt32 fms4::canDo(char* text)
{
    if(strcmp(text, "receiveVstEvents") == 0) return 1;
    if(strcmp(text, "receiveVstMidiEvent") == 0) return 1;
    return -1;
}
void fms4::getParameterName(VstInt32 index, char *label)
{
    /*
     switch (index)
     {
     case 0: strcpy(label, "Voices  "); break;
     case  1: strcpy(label, "Attack  "); break;
     case  2: strcpy(label, "Decay   "); break;
     case  3: strcpy(label, "Sustain "); break;
     case  4: strcpy(label, "Release "); break;
     case  5: strcpy(label, "Mod "); break;
     }
     */
}
void fms4::getParameterDisplay(VstInt32 index, char *text)
{
    
    char string[16];
    float * param = programs[curProgram].param;
    
    switch(index)
    {
        default: sprintf(string, "%f",param[index]);
            break;
    }
    string[8] = 0;
    strcpy(text, (char *)string);
    
}


void fms4::getParameterLabel(VstInt32 index, char *label)
{
    /*
     switch(index)
     {
     case  1: strcpy(label, "ms"); break;
     case  2: strcpy(label, "ms"); break;
     case  3: strcpy(label, ""); break;
     case  4: strcpy(label, "ms"); break;
     case  5: strcpy(label, ""); break;
     default: strcpy(label, "");
     }
     */
}
void fms4::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames){
    float* out1 = outputs[0];
    float* out2 = outputs[1];
    VstInt32 event=0, frame=0, frames=0;
    float lo=0.f;
    float ro=0.f;
    CVoiceState* vs;
    float osc[4];
    if(activevoices>0||notes[event]<sampleFrames){
        while(frame<sampleFrames)
        {
            update();
            frames = notes[event++];
            if(frames>sampleFrames) frames = sampleFrames;
            frames -= frame;
            frame += frames;
            while(--frames>=0)
            {
                lo=0.0f;
                ro=0.0f;
                update();
                for(int v=0;v<voices;v++)// for each vs
                {
                    vs = &mVS[v];
                    if(  vs->mEnv_ctx[0].mStage!=kIdle
                       ||vs->mEnv_ctx[1].mStage!=kIdle
                       ||vs->mEnv_ctx[2].mStage!=kIdle
                       ||vs->mEnv_ctx[3].mStage!=kIdle)
                    {
                        for(int i=0; i<4;i++)
                        {
                            vs->mOsc_ctx[0].mod[i] = osc[i]=
                            mEnv[i]->process(&vs->mEnv_ctx[i])
                            *mOsc[i]->process(&vs->mOsc_ctx[i]);
                            vs->mOsc_ctx[1].mod[i] = osc[i];
                            vs->mOsc_ctx[2].mod[i] = osc[i];
                            vs->mOsc_ctx[3].mod[i] = osc[i];
                            
                            lo+= sqrt(.5f-Pan[i]) * (osc[i]*OutPut[i]);
                            ro+=  sqrt(.5f+Pan[i]) * (osc[i]*OutPut[i]);
                        }
                    }
                }
                lo*=0.125892541179417f;
                ro*=0.125892541179417f;
                *out1++ = lo;
                *out2++ = ro;
            }
            
            if(frame<sampleFrames) //next note on/off
            {
                VstInt32 note = notes[event++];
                VstInt32 vel  = notes[event++];
                noteOn(note, vel);
            }
            
        }
        activevoices = voices;
        for(int v=0; v<voices; v++)
        {
            if(mVS[v].mEnv_ctx[0].mStage==kIdle
               &&mVS[v].mEnv_ctx[1].mStage==kIdle
               &&mVS[v].mEnv_ctx[2].mStage==kIdle
               &&mVS[v].mEnv_ctx[3].mStage==kIdle)  //choke voices that have finished
            {
                activevoices--;
            }
        }
        
    }else{
        memset (out1, 0.0f, sampleFrames * sizeof (float));
        memset (out2, 0.0f, sampleFrames * sizeof (float));
    }
    notes[0] = EVENTS_DONE;  //mark events buffer as done
}

int fms4::FindFreeVoice(){
    for(int v=0;v<voices;v++){
        if(  mVS[v].mEnv_ctx[0].mStage==kIdle
           &&mVS[v].mEnv_ctx[1].mStage==kIdle
           &&mVS[v].mEnv_ctx[2].mStage==kIdle
           &&mVS[v].mEnv_ctx[3].mStage==kIdle){
            mVS[v].age=0;
            for(int i =0;i<4;i++)
                mVS[v].mOsc_ctx[i].mPhase=0.0f;
            return v;
        }else{
            mVS[v].age++;
        }
    }
    int currentIndex=1;
    int oldestIndex=0;
    
    while (currentIndex<voices) {
        if(mVS[currentIndex].age>mVS[oldestIndex].age){
            oldestIndex=currentIndex;
        }
        currentIndex++;
    }
    for(int i =0;i<4;i++)
        mVS[oldestIndex].mOsc_ctx[i].mPhase=0.0f;
    mVS[oldestIndex].age=0;
    return oldestIndex;
    
}
void fms4::noteOn(VstInt32 note, VstInt32 velocity)
{
    if(velocity>0)
    {
        int v=FindFreeVoice();
        mVS[v].mKey=note;
        mVS[v].noteIsOn=true;
        activevoices++;
        for(int i = 0; i<4 ; i++){
            mVS[v].mOsc_ctx[i].mPhaseIncr = 1.f/Fs * midi2CPS(note);
            //mVS[v].mOsc_ctx[i].mPhase=0.0f;//retrigger
            mVS[v].mEnv_ctx[i].mStage = kStageAttack;
            mVS[v].mEnv_ctx[i].mLevel = velocity*(1.f/127.f);
        }
    }
    else //note off
    {
        for (int v = 0; v < voices; v++)
        {
            if(mVS[v].mKey == note)
            {
                if(mVS[v].mEnv_ctx[0].mStage!=kIdle
                   ||mVS[v].mEnv_ctx[1].mStage!=kIdle
                   ||mVS[v].mEnv_ctx[2].mStage!=kIdle
                   ||mVS[v].mEnv_ctx[3].mStage!=kIdle){
                        for(int i =0;i<4;i++){
                            mVS[v].mEnv_ctx[i].mStage=kStageRelease;
                        }
                        mVS[v].mKey=-1;
                        mVS[v].noteIsOn=false;
                    return;
                }
            }
        }
        
    }
    
}

VstInt32 fms4::processEvents(VstEvents* ev)
{
    VstInt32 npos=0;
    
    for (VstInt32 i=0; i<ev->numEvents; i++)
    {
        if((ev->events[i])->type != kVstMidiType) continue;
        VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
        char* midiData = event->midiData;
        
        switch(midiData[0] & 0xf0) //status byte (all channels)
        {
            case 0x80: //note off
                notes[npos++] = event->deltaFrames; //delta
                notes[npos++] = midiData[1] & 0x7F; //note
                notes[npos++] = 0;                  //vel
                break;
                
            case 0x90: //note on
                notes[npos++] = event->deltaFrames; //delta
                notes[npos++] = midiData[1] & 0x7F; //note
                notes[npos++] = midiData[2] & 0x7F; //vel
                break;
                
            case 0xB0: //controller
                switch(midiData[1])
            {
                case 0x01:  //mod wheel
                    break;
                    
                case 0x07:  //volume
                    break;
                    
                case 0x40:  //sustain
                    sustain = midiData[2] & 0x40;
                    if(sustain==0)
                    {
                        notes[npos++] = event->deltaFrames;
                        notes[npos++] = SUSTAIN; //end all sustained notes
                        notes[npos++] = 0;
                    }
                    break;
                    
                default:  //all notes off
                    if(midiData[1]>0x7A)
                    {
                        sustain = 0;
                    }
                    break;
            }
            default: break;
        }
        
        if(npos>EVENTBUFFER) npos -= 3; //discard events if buffer full!!
        event++;
    }
    notes[npos] = EVENTS_DONE;
    return 1;
}















