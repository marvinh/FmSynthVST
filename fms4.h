//
//  fms4.h
//  fms4
//
//  Created by marvin h on 9/27/15.
//  Copyright (c) 2015 marvin h. All rights reserved.
//

#ifndef __fms4__fms4__
#define __fms4__fms4__

#include <stdio.h>
#include <string.h>
#include "audioeffectx.h"
#include "FmSynth4Dsp.h"
#include "fms4Parameters.h"
#include "fms4Editor.h"




#define NPARAMS 50      //number of parameters
#define NPROGS  2       //number of programs
#define NOUTS    2       //number of outputs
#define NVOICES  16     //max polyphony
#define SILENCE 0.00003f  //voice choking

class fms4Program
{
    friend class fms4;
private:
    float param[NPARAMS];
    char  name[24];
};

class fms4 : public AudioEffectX
{
public:
    fms4(audioMasterCallback audioMaster);
    ~fms4();
    virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
    
    virtual VstInt32 processEvents(VstEvents* events);
    
    virtual void setProgram(VstInt32 program);
    virtual void setProgramName(char *name);
    virtual void getProgramName(char *name);
    virtual void setParameter(VstInt32 index, float value);
    virtual float getParameter(VstInt32 index);
    virtual void getParameterLabel(VstInt32 index, char *label);
    virtual void getParameterDisplay(VstInt32 index, char *text);
    virtual void getParameterName(VstInt32 index, char *text);
    virtual void setSampleRate(float sampleRate);
    virtual void setBlockSize(VstInt32 blockSize);
    virtual void resume();
    
    virtual bool getOutputProperties (VstInt32 index, VstPinProperties* properties);
    virtual bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text);
    virtual bool copyProgram (VstInt32 destination);
    virtual bool getEffectName (char* name);
    virtual bool getVendorString (char* text);
    virtual bool getProductString (char* text);
    virtual VstInt32 getVendorVersion () {return 1;}
    virtual VstInt32 canDo (char* text);
    
    virtual VstInt32 getNumMidiInputChannels ()  { return 1; }
    

    
private:
    void update();  //my parameter update
    void noteOn(VstInt32 note, VstInt32 velocity);
    void fillpatch(VstInt32 p, char *name,int v,float patch[]);
    
    fms4Program* programs;
    float Fs;
    
    void voiceUpdate();
    
#define EVENTBUFFER 120
#define EVENTS_DONE 99999999
    VstInt32 notes[EVENTBUFFER + 8];  //list of delta|note|velocity for current block
    
    ///global internal variables
    CVoiceState mVS[NVOICES];
    
    CWTOsc* mOsc[4];
    ADSR* mEnv[4];
    
    float Pan[4];
    float OutPut[4];
    float *mTable;
    CParamSmooth mPS[NPARAMS];
    int FindFreeVoice();
    int voices;
    int voiceMaintain;
    bool noteIsOn=true;
    float pPatch[NPARAMS];
    
    int parameterIndex;

#define SUSTAIN 128
    VstInt32 sustain, activevoices, K;
};
#endif /* defined(__fms4__fms4__) */
