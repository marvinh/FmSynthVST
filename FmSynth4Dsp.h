//
//  FmSynth4Dsp.h
//  FmSynth4
//
//  Created by marvin h on 9/24/15.
//
//

#ifndef __FmSynth4__FmSynth4Dsp__
#define __FmSynth4__FmSynth4Dsp__

#include <stdio.h>
#include <math.h>
#include "ADSR.h"


inline float midi2CPS(float pitch)
{
    return 440. * pow(2., (pitch - 69.) / 12.);
}
inline float wrap(float x, float low = 0., float high = 1.)
{
    while (x >= high) x -= high;
    while (x < low)  x += high - low;
    
    return x;
}

inline float lerp(float phase, const float* buffer, unsigned long int mask)
{
    const int intPart = (int) phase;
    const float fracPart = phase-intPart;
    const float a = buffer[intPart & mask];
    const float b = buffer[(intPart+1) & mask];
    return a + (b - a) * fracPart;
}
struct CWTOscState
{
    float mPhase;        // float phase (goes between 0. and 1.)
    float mPhaseIncr;    // freq * mPhaseStep
    float mod[4];
    CWTOscState()
    {
        mPhase = 0.;
        mPhaseIncr = 0.;
    }
    
};

class CWTOsc
{
protected:
    const float* mLUT;           // pointer to waveform lookup table, const because the oscilator doesn't change the table data
    unsigned long int mLUTSize;   // wavetable size
    unsigned long int mLUTSizeM;  // wavetable Mask (size -1)
    float mLUTSizeF;             // float version
    
public:
    
    float modValue[4];
    float modAmp[4];
    CWTOsc(const float* LUT, unsigned long int LUTSize)
    {
        setLUT(LUT, LUTSize);
    }
    
    ~CWTOsc() {}
    
    void setLUT(const float* LUT, unsigned long int LUTSize)
    {
        mLUTSize = LUTSize;
        mLUTSizeM = LUTSize-1;
        mLUTSizeF = (float) LUTSize;
        mLUT = LUT;
    }
    
    float process(CWTOscState* pState)
    {
        for(int i = 0;i<4;i++){
                            //want to grow more exp.      //arbitray multiplier
            modValue[i] = ((modAmp[i]*modAmp[i]*modAmp[i])*2.75f*(pState->mod[i]));
        }
        float total = (modValue[0] + modValue[1] + modValue[2] + modValue[3])*mLUTSizeF;
        pState->mPhase = wrap(pState->mPhase, 0., 1.);
        const float output = lerp((pState->mPhase * mLUTSizeF)+total, mLUT, mLUTSizeM);
        pState->mPhase+=pState->mPhaseIncr;
        return output;
    }
    
};
class CParamSmooth
{
public:
    CParamSmooth() { a = 0.99; b = 1.0 - a; z = 0; };
    ~CParamSmooth(){};
    inline float Process(float in) { z = (in * b) + (z * a); return z; }
private:
    float a, b, z;
};

struct CVoiceState
{
    CWTOscState mOsc_ctx[4];
    CADSREnvLState mEnv_ctx[4];
    int mKey;
    int age;
    bool noteIsOn;
    CVoiceState()
    {
        mKey = -1;
        noteIsOn=false;
        age=0;
    }
     bool GetBusy()
     {
         if (mEnv_ctx[0].mStage==kIdle
             &&mEnv_ctx[1].mStage==kIdle
             &&mEnv_ctx[2].mStage==kIdle
             &&mEnv_ctx[3].mStage==kIdle){
             return false;
         }else{
             return true;
         }
     }
    

    
};
#endif /* defined(__FmSynth4__FmSynth4Dsp__) */
