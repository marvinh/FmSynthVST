//-----------------------------------------------------------------------------
// VSTGUI: Graphical User Interface Framework for VST plugins
//
// Version 3.5
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2013, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this
//     software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#include "fms4Editor.h"

//------------------------------------------------------------------------------------
AEffGUIEditor* createEditor (AudioEffectX* effect)
{
    return new fms4Editor (effect);
}

//------------------------------------------------------------------------------------
fms4Editor::fms4Editor (void* ptr)
: AEffGUIEditor (ptr)
{
    //background = new CBitmap ("bg.png");
    rect.left   = 0;
    rect.top    = 0;
    rect.right  = 700;
    rect.bottom = 400;
}

//------------------------------------------------------------------------------------
bool fms4Editor::open (void* ptr)
{
  
    CRect frameSize (0, 0, 700,400);
    CRect knobFrame(0,0,40,40);
    CRect knobFrame2(0,0,40,40);
    CRect polyFrame(0,0,100,40);
    CRect textFrame(0,0,60,100);
    
    textFrame.offset(60,0);
    
    CFrame* newFrame = new CFrame (frameSize,this);
    CTextLabel* envlabel = new CTextLabel(textFrame,"Envelopes");
    envlabel->setFontColor(kWhiteCColor);
    textFrame.offset(380, 0);
    CTextLabel* matlabel = new CTextLabel(textFrame,"Matrix");

    CBitmap* animatedKnob = new CBitmap("knob.png");
    CBitmap* animatedKnob2 = new CBitmap("knob.png");
    CBitmap* animatedKnobPoly = new CBitmap("poly.png");

    newFrame->open(ptr);
    newFrame->setBackgroundColor (kBlackCColor);
    newFrame->addView(envlabel);
    newFrame->addView(matlabel);
    
    knobFrame2.offset(60,60);
    CKnob* a1 = new CAnimKnob(knobFrame2,this,kAttack1,animatedKnob2,CPoint(0,0));
    newFrame->addView (a1);
    knobFrame2.offset(40,0);
    CKnob* d1 = new CAnimKnob(knobFrame2,this,kDecay1,animatedKnob2,CPoint(0,0));
    newFrame->addView (d1);
    knobFrame2.offset(40,0);
    CKnob* s1 = new CAnimKnob(knobFrame2,this,kSustain1,animatedKnob2,CPoint(0,0));
    newFrame->addView (s1);
    knobFrame2.offset(40,0);
    CKnob* r1 = new CAnimKnob(knobFrame2,this,kRelease1,animatedKnob2,CPoint(0,0));
    newFrame->addView (r1);
    
    knobFrame2.offset(-120,40);
    CKnob* a2 = new CAnimKnob(knobFrame2,this,kAttack2,animatedKnob2,CPoint(0,0));
    newFrame->addView (a2);
    knobFrame2.offset(40,0);
    CKnob* d2 = new CAnimKnob(knobFrame2,this,kDecay2,animatedKnob2,CPoint(0,0));
    newFrame->addView (d2);
    knobFrame2.offset(40,0);
    CKnob* s2 = new CAnimKnob(knobFrame2,this,kSustain2,animatedKnob2,CPoint(0,0));
    newFrame->addView (s2);
    knobFrame2.offset(40,0);
    CKnob* r2 = new CAnimKnob(knobFrame2,this,kRelease2,animatedKnob2,CPoint(0,0));
    newFrame->addView (r2);

    knobFrame2.offset(-120,40);
    CKnob* a3 = new CAnimKnob(knobFrame2,this,kAttack3,animatedKnob2,CPoint(0,0));
    newFrame->addView (a3);
    knobFrame2.offset(40,0);
    CKnob* d3 = new CAnimKnob(knobFrame2,this,kDecay3,animatedKnob2,CPoint(0,0));
    newFrame->addView (d3);
    knobFrame2.offset(40,0);
    CKnob* s3 = new CAnimKnob(knobFrame2,this,kSustain3,animatedKnob2,CPoint(0,0));
    newFrame->addView (s3);
    knobFrame2.offset(40,0);
    CKnob* r3 = new CAnimKnob(knobFrame2,this,kRelease3,animatedKnob2,CPoint(0,0));
    newFrame->addView (r3);
    
    
    knobFrame2.offset(-120,40);
    CKnob* a4 = new CAnimKnob(knobFrame2,this,kAttack4,animatedKnob2,CPoint(0,0));
    newFrame->addView (a4);
    knobFrame2.offset(40,0);
    CKnob* d4 = new CAnimKnob(knobFrame2,this,kDecay4,animatedKnob2,CPoint(0,0));
    newFrame->addView (d4);
    knobFrame2.offset(40,0);
    CKnob* s4 = new CAnimKnob(knobFrame2,this,kSustain4,animatedKnob2,CPoint(0,0));
    newFrame->addView (s4);
    knobFrame2.offset(40,0);
    CKnob* r4 = new CAnimKnob(knobFrame2,this,kRelease4,animatedKnob2,CPoint(0,0));
    newFrame->addView (r4);
    
    
    polyFrame.offset(0,360);
    CKnob* knob1 = new CAnimKnob(polyFrame,this,kVoices,animatedKnobPoly,CPoint(0,0));
    newFrame->addView (knob1);
    
    knobFrame.offset(440,60);
    CKnob* km121 = new CAnimKnob(knobFrame,this,kMod1to1,animatedKnob,CPoint(0,0));
    newFrame->addView (km121);
    knobFrame.offset(0,40);
    CKnob* km221 = new CAnimKnob(knobFrame,this,kMod2to1,animatedKnob,CPoint(0,0));
    newFrame->addView (km221);
    knobFrame.offset(0,40);
    CKnob* km321 = new CAnimKnob(knobFrame,this,kMod3to1,animatedKnob,CPoint(0,0));
    newFrame->addView (km321);
    knobFrame.offset(0,40);
    CKnob* km421 = new CAnimKnob(knobFrame,this,kMod4to1,animatedKnob,CPoint(0,0));
    newFrame->addView (km421);
    knobFrame.offset(0,40);
    CKnob* p1 = new CAnimKnob(knobFrame,this,kPan1,animatedKnob,CPoint(0,0));
    newFrame->addView (p1);
    knobFrame.offset(0,40);
    CKnob* op1 = new CAnimKnob(knobFrame,this,kOutPut1,animatedKnob,CPoint(0,0));
    newFrame->addView (op1);

    
    
    knobFrame.offset(40,-200);
    CKnob* km122 = new CAnimKnob(knobFrame,this,kMod1to2,animatedKnob,CPoint(0,0));
    newFrame->addView (km122);
    knobFrame.offset(0,40);
    CKnob* km222 = new CAnimKnob(knobFrame,this,kMod2to2,animatedKnob,CPoint(0,0));
    newFrame->addView (km222);
    knobFrame.offset(0,40);
    CKnob* km322 = new CAnimKnob(knobFrame,this,kMod3to2,animatedKnob,CPoint(0,0));
    newFrame->addView (km322);
    knobFrame.offset(0,40);
    CKnob* km422 = new CAnimKnob(knobFrame,this,kMod4to2,animatedKnob,CPoint(0,0));
    newFrame->addView (km422);
    knobFrame.offset(0,40);
    CKnob* p2 = new CAnimKnob(knobFrame,this,kPan2,animatedKnob,CPoint(0,0));
    newFrame->addView (p2);
    knobFrame.offset(0,40);
    CKnob* op2 = new CAnimKnob(knobFrame,this,kOutPut2,animatedKnob,CPoint(0,0));
    newFrame->addView (op2);
    
    knobFrame.offset(40,-200);
    CKnob* km123 = new CAnimKnob(knobFrame,this,kMod1to3,animatedKnob,CPoint(0,0));
    newFrame->addView (km123);
    knobFrame.offset(0,40);
    CKnob* km223 = new CAnimKnob(knobFrame,this,kMod2to3,animatedKnob,CPoint(0,0));
    newFrame->addView (km223);
    knobFrame.offset(0,40);
    CKnob* km323 = new CAnimKnob(knobFrame,this,kMod3to3,animatedKnob,CPoint(0,0));
    newFrame->addView (km323);
    knobFrame.offset(0,40);
    CKnob* km423 = new CAnimKnob(knobFrame,this,kMod4to3,animatedKnob,CPoint(0,0));
    newFrame->addView (km423);
    knobFrame.offset(0,40);
    CKnob* p3 = new CAnimKnob(knobFrame,this,kPan3,animatedKnob,CPoint(0,0));
    newFrame->addView (p3);
    knobFrame.offset(0,40);
    CKnob* op3 = new CAnimKnob(knobFrame,this,kOutPut3,animatedKnob,CPoint(0,0));
    newFrame->addView (op3);

    
    knobFrame.offset(40,-200);
    CKnob* km124 = new CAnimKnob(knobFrame,this,kMod1to4,animatedKnob,CPoint(0,0));
    newFrame->addView (km124);
    knobFrame.offset(0,40);
    CKnob* km224 = new CAnimKnob(knobFrame,this,kMod2to4,animatedKnob,CPoint(0,0));
    newFrame->addView (km224);
    knobFrame.offset(0,40);
    CKnob* km324 = new CAnimKnob(knobFrame,this,kMod3to4,animatedKnob,CPoint(0,0));
    newFrame->addView (km324);
    knobFrame.offset(0,40);
    CKnob* km424 = new CAnimKnob(knobFrame,this,kMod4to4,animatedKnob,CPoint(0,0));
    newFrame->addView (km424);
    knobFrame.offset(0,40);
    CKnob* p4 = new CAnimKnob(knobFrame,this,kPan4,animatedKnob,CPoint(0,0));
    newFrame->addView (p4);
    knobFrame.offset(0,40);
    CKnob* op4 = new CAnimKnob(knobFrame,this,kOutPut4,animatedKnob,CPoint(0,0));
    newFrame->addView (op4);
    
    //animatedKnob->forget();
    animatedKnobPoly->forget();
    animatedKnob2->forget();
    
    //-- remember our controls so that we can sync them with the state of the effect
    controls[kVoices] = knob1;
    controls[kMod1to1] = km121;
    controls[kMod2to1] = km221;
    controls[kMod3to1] = km321;
    controls[kMod4to1] = km421;
    
    controls[kMod1to2] = km122;
    controls[kMod2to2] = km222;
    controls[kMod3to2] = km322;
    controls[kMod4to2] = km422;
    
    controls[kMod1to3] = km123;
    controls[kMod2to3] = km223;
    controls[kMod3to3] = km323;
    controls[kMod4to3] = km423;
    
    controls[kMod1to4] = km124;
    controls[kMod2to4] = km224;
    controls[kMod3to4] = km324;
    controls[kMod4to4] = km424;
    
    controls[kOutPut1] = op1;
    controls[kOutPut2] = op2;
    controls[kOutPut3] = op3;
    controls[kOutPut4] = op4;
    
    controls[kPan1] = p1;
    controls[kPan2] = p2;
    controls[kPan3] = p3;
    controls[kPan4] = p4;

    controls[kAttack1] = a1;
    controls[kDecay1] = d1;
    controls[kSustain1] = s1;
    controls[kRelease1] = r1;
    
    controls[kAttack2] = a2;
    controls[kDecay2] = d2;
    controls[kSustain2] = s2;
    controls[kRelease2] = r2;
    
    controls[kAttack3] = a3;
    controls[kDecay3] = d3;
    controls[kSustain3] = s3;
    controls[kRelease3] = r3;
    
    controls[kAttack4] = a4;
    controls[kDecay4] = d4;
    controls[kSustain4] = s4;
    controls[kRelease4] = r4;

    //-- set the member frame to the newly created frame
    //-- we do it this way because it is possible that the setParameter method is called
    //-- in between of constructing the frame and it's controls
    frame = newFrame;
    
    //-- sync parameters
    for (int i = 0; i < kNumParams; i++)
        setParameter (i, effect->getParameter (i));
    
    return true;
}

//------------------------------------------------------------------------------------
void fms4Editor::close ()
{
    //-- on close we need to delete the frame object.
    //-- once again we make sure that the member frame variable is set to zero before we delete it
    //-- so that calls to setParameter won't crash.
    //frame->close();
    CFrame* oldframe = frame;
    frame=0;
    oldframe->forget();
    
    
}

//------------------------------------------------------------------------------------
void fms4Editor::valueChanged (CControl* pControl)
{
    //-- valueChanged is called whenever the user changes one of the controls in the User Interface (UI)
    effect->setParameterAutomated (pControl->getTag (), pControl->getValue ());
}

//------------------------------------------------------------------------------------
void fms4Editor::setParameter (VstInt32 index, float value)
{
    //-- setParameter is called when the host automates one of the effects parameter.
    //-- The UI should reflect this state so we set the value of the control to the new value.
    //-- VSTGUI will automatically redraw changed controls in the next idle (as this call happens to be in the process thread).
    if (frame && index < kNumParams)
    {
        controls[index]->setValue (value);
    }
}

