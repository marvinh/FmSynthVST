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

#ifndef __fms4Editor__
#define __fms4Editor__

#include "vstgui/plugin-bindings/aeffguieditor.h"
#include "fms4Parameters.h"
class fms4Editor : public AEffGUIEditor, public IControlListener
{
public:
    fms4Editor (void*);
    // from AEffGUIEditor
    bool open (void* ptr);
    void close ();
    void setParameter (VstInt32 index, float value);
    virtual bool getRect(ERect** ppRect)
    {
        if (frame)
        {
            CRect rc;
            frame->getSize(rc);
            rect.left = (VstInt16)rc.left;
            rect.right = (VstInt16)rc.right;
            rect.top = (VstInt16)rc.top;
            rect.bottom = (VstInt16)rc.bottom;
        }
        return AEffGUIEditor::getRect(ppRect);
    };
    // from CControlListener
    void valueChanged (CControl* pControl);
    
protected:
    //CBitmap* background; //= new CBitmap ("bg.png");
    CControl* controls[kNumParams];
};

#endif // __fms4Editor__

