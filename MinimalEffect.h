#ifndef __MinimalEffectINCLUDED__
#define __MinimalEffectINCLUDED__

#include "public.sdk/source/vst2.x/audioeffectx.h"

#include <vector>
#include <string>
#include <math.h>

class MinimalEffect : public AudioEffectX
{
public:
	MinimalEffect(audioMasterCallback audioMaster);
	virtual ~MinimalEffect();
	float getDefaultParameter(VstInt32 index);

	//---from AudioEffect-----------------------
	virtual void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) {
        static float position = 0.0f;
        for (int x = 0; x < sampleFrames; ++x) {
            position += 1.0f / 44100.0f;
            outputs[0][x] = 1.0f * sinf( 2.0f * float(M_PI) * 220.0f * position );
            outputs[1][x] = 1.0f * sinf( 2.0f * float(M_PI) * 400.0f * position );
        }
    }
   virtual void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames) {
        static double position = 0.0;
        for (int x = 0; x < sampleFrames; ++x) {
            position += 1.0 / 44100.0;
            outputs[0][x] = 1.0 * sin( 2.0f * float(M_PI) * 220.0 * position );
            outputs[1][x] = 1.0 * sin( 2.0f * float(M_PI) * 400.0 * position );
        }
   }

	virtual void setProgram (VstInt32 which);
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);
	virtual bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text);
	
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);

    virtual VstInt32 processEvents (VstEvents* ev) { return 1; }

    virtual VstInt32 canHostDo( char* text ) { return AudioEffectX::canHostDo(text); }
    virtual VstInt32 canDo( const char* text ) {
        if (0 == strcmp (text, "receiveVstEvents"))
            return 1;
        if (0 == strcmp (text, "receiveVstMidiEvent"))
            return 1;
        if (0 == strcmp (text, "midiProgramNames"))
            return 1;
        return -1; //AudioEffectX::canDo(text);
    }
	virtual void resume ();

    /// config
    virtual bool getEffectName (char* name);
    virtual bool getVendorString (char* text);
    virtual bool getProductString (char* text);
    virtual VstInt32 getVendorVersion() { return 3001; }
    virtual VstPlugCategory getPlugCategory() { return kPlugCategSynth; }
};

#endif
