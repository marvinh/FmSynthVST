#ifndef ADRS_h
#define ADRS_h

enum EADSREnvStage
{
    kIdle = 0,
    kStageAttack,
    kStageDecay,
    kStageSustain,
    kStageRelease,
};

struct CADSREnvLState
{
    float mEnvValue;          
    int mStage;
    float mLevel;
    float mPrev;
    
    CADSREnvLState()
    {
        mEnvValue = 0.f;
        mStage = kIdle;
        mLevel = 0.f;
        mPrev = 0.f;
    }
    
};
class ADSR {
public:
    ADSR(void);
    ~ADSR(void);
    float process(CADSREnvLState* pS);
    void setAttackRate(float rate);
    void setDecayRate(float rate);
    void setReleaseRate(float rate);
    void setSustainLevel(float level);
    void setStageTime(int stage, float rate);
    void setSampleRate(float sr);

    
    
    enum envState {
        env_idle = 0,
        env_attack,
        env_decay,
        env_sustain,
        env_release
    };
    
protected:
    float sampleRate;
    //inverse sample rate
    float iSR;
    float sustainLevel;
    float attack;
    float decay;
    float release;
};

float ADSR::process(CADSREnvLState* pS) {
    float result = 0.0;
    switch (pS->mStage) {
        case kIdle:
            break;
        case kStageAttack:
            pS->mEnvValue += attack;
            if (pS->mEnvValue  >= 1.0) {
                pS->mEnvValue  =  1.0;
                pS->mStage = kStageDecay;
            }
            result = pS->mEnvValue;
            break;
        case kStageDecay:
            pS->mEnvValue -= decay;
            if (pS->mEnvValue  <= sustainLevel) {
                pS->mEnvValue  = sustainLevel;
                pS->mStage = kStageSustain;
            }
            result = pS->mEnvValue;
            break;
        case kStageSustain:
            result = sustainLevel;
            break;
        case kStageRelease:
            pS->mEnvValue  -=release;
            if (pS->mEnvValue  < 0.00001f) {
                pS->mEnvValue  = 0.0;
                pS->mStage = kIdle;
            }
            result = pS->mEnvValue;
            break;
        default:
            result = pS->mEnvValue;
            break;
    }
    
    pS->mPrev=result;
    return (result*pS->mLevel);
    
}
ADSR::ADSR(void) {
    setAttackRate(0.);
    setDecayRate(0.);
    setReleaseRate(0.);
    setSustainLevel(0.);
    setSampleRate(44100.0);
}
ADSR::~ADSR(void) {
}
void ADSR::setSampleRate(float sr){
    sampleRate=sr;
    iSR = -(1./sr);
}
void ADSR::setAttackRate(float rate) {
    attack = 1.0f - (float)(exp(iSR * exp(5.0 - 8.0*rate)));
}

void ADSR::setDecayRate(float rate) {
    decay =  1.0f - (float)(exp(iSR * exp(5.0 - 8.0*rate)));
}

void ADSR::setReleaseRate(float rate) {
    release = 1.0f - (float)(exp(iSR * exp(5.0 - 8.0*rate)));
}

void ADSR::setSustainLevel(float level) {
    sustainLevel = level;
}
void ADSR::setStageTime(int stage, float rate){
    switch (stage) {
        case kStageAttack:
                setAttackRate(rate);
            break;
        case kStageDecay:
                setDecayRate(rate);
            break;
        case kStageRelease:
                setReleaseRate(rate);
            break;
        default:
            break;
    }
    
}
#endif
