//-----------------------------------------------------------------------------
// VSTGUI: Graphical User Interface Framework for VST plugins : 
//
// Version 3.5
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// © 2008, Steinberg Media Technologies, All Rights Reserved
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
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A  PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#ifndef __fms4Parameters__
#define __fms4Parameters__

enum Params{
    kVoices=0,
    
    kMod1to1,
    kMod2to1,
    kMod3to1,
    kMod4to1,

    
    kMod1to2,
    kMod2to2,
    kMod3to2,
    kMod4to2,
    
    kMod1to3,
    kMod2to3,
    kMod3to3,
    kMod4to3,

    kMod1to4,
    kMod2to4,
    kMod3to4,
    kMod4to4,
    
    kOutPut1,
    kOutPut2,
    kOutPut3,
    kOutPut4,
    
    kPan1,
    kPan2,
    kPan3,
    kPan4,
    
    
    kAttack1,
    kDecay1,
    kSustain1,
    kRelease1,
    
    kAttack2,
    kDecay2,
    kSustain2,
    kRelease2,
    
    kAttack3,
    kDecay3,
    kSustain3,
    kRelease3,
    
    kAttack4,
    kDecay4,
    kSustain4,
    kRelease4,
   
    kNumParams
};

#endif // __fms4Parameters__