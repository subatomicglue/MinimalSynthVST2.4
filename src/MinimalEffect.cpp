//#include <stdio.h>
#include <string>
#include <math.h>
#include "MinimalEffect.h"
#include "MinimalEditor.h"

AudioEffect* createEffectInstance( audioMasterCallback audioMaster )
{
    return new MinimalEffect( audioMaster );
}

MinimalEffect::MinimalEffect (audioMasterCallback audioMaster)
	: AudioEffectX (audioMaster, 1/*numprograms*/, 1/*numparams*/)
{
    curProgram = 0;
    setUniqueID( 'sUBm' );	// this should be unique, use the Steinberg web page for plugin Id registration
	setNumInputs(0);	// no input in this synth
	setNumOutputs(2);	// stereo output
    canProcessReplacing(true);// enable processReplacing() so that hosts can know to use it
    canDoubleReplacing(true); // enable processDoubleReplacing() so that hosts can know to use it
    isSynth( true ); // true for synth, false for effect
    editor = new MinimalEditor( this );
}

MinimalEffect::~MinimalEffect ()
{
    delete editor;
    editor = 0;
}

void MinimalEffect::setProgram( VstInt32 which )
{
    AudioEffect::setProgram( which ); // sets curProgram
}

void MinimalEffect::setProgramName (char *name)
{
	//strncpy( program, name, kVstMaxProgNameLen );
}

void MinimalEffect::getProgramName (char *name)
{
    strncpy( name, "prog", kVstMaxProgNameLen );
}

bool MinimalEffect::getProgramNameIndexed( VstInt32 category, VstInt32 index, char* text )
{
    strncpy( text, "prog", kVstMaxProgNameLen );
    return true;
}

void MinimalEffect::resume ()
{
	AudioEffectX::resume ();
}

void MinimalEffect::setParameter (VstInt32 index, float value)
{
    //snprintf( param[index], kVstMaxProgNameLen, "%f", value );
}

float MinimalEffect::getParameter( VstInt32 index )
{
    return 0.0f;
}

float MinimalEffect::getDefaultParameter (VstInt32 index)
{
    return 0.0f;
}

void MinimalEffect::getParameterName (VstInt32 index, char *label)
{
    strncpy( label, "Param", kVstMaxParamStrLen );
}

void MinimalEffect::getParameterDisplay (VstInt32 index, char *text)
{
    strncpy( text, "0.0", kVstMaxParamStrLen );
}

void MinimalEffect::getParameterLabel (VstInt32 index, char *label)
{
    strncpy( label, "Label", kVstMaxParamStrLen );
}

bool MinimalEffect::getEffectName (char* name)
{
    strncpy( name, "MinimalEffect", kVstMaxEffectNameLen );
	return true;
}

bool MinimalEffect::getProductString (char* text)
{
    strncpy( text, "Product", kVstMaxProductStrLen );
	return true;
}

bool MinimalEffect::getVendorString (char* text)
{
    strncpy( text, "vendor", kVstMaxVendorStrLen );
	return true;
}
