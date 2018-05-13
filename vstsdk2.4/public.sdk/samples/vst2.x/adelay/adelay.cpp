//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4		$Date: 2006/11/13 09:08:27 $
//
// Category     : VST 2.x SDK Samples
// Filename     : adelay.cpp
// Created by   : Steinberg Media Technologies
// Description  : Simple Delay plugin (Mono->Stereo)
//
// © 2006, Steinberg Media Technologies, All Rights Reserved
//-------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

#ifndef __adelay__
#include "adelay.h"
#endif

//----------------------------------------------------------------------------- 
ADelayProgram::ADelayProgram ()
{
	// default Program Values
	fPower = 0.2f;
	fWetDry = 1.0f;
	fGain = 1.0f / 3.0f;
    fKnob = 0.0f;
	
	strcpy (name, "Init");
}

//-----------------------------------------------------------------------------
ADelay::ADelay (audioMasterCallback audioMaster)
	: AudioEffectX (audioMaster, kNumPrograms, kNumParams)
{
	// init
	size = 44100;
	buffer = new float[size];
	
	programs = new ADelayProgram[numPrograms];
	fKnob = fPower = fWetDry = fGain = 0;

	if (programs)
		setProgram (0);

	setNumInputs (2);	// mono input
	setNumOutputs (2);	// stereo output

	setUniqueID ('ADly');	// this should be unique, use the Steinberg web page for plugin Id registration

	resume ();		// flush buffer
}

//------------------------------------------------------------------------
ADelay::~ADelay ()
{
	if (buffer)
		delete[] buffer;
	if (programs)
		delete[] programs;
}

//------------------------------------------------------------------------
void ADelay::setProgram (VstInt32 program)
{
	ADelayProgram* ap = &programs[program];

	curProgram = program;
	setParameter (kPower, ap->fPower);	
	setParameter (kMorph, ap->fWetDry);
	setParameter (kGain, ap->fGain);
    setParameter (kKnob, ap->fKnob);
}

//------------------------------------------------------------------------
void ADelay::setProgramName (char *name)
{
	strcpy (programs[curProgram].name, name);
}

//------------------------------------------------------------------------
void ADelay::getProgramName (char *name)
{
	if (!strcmp (programs[curProgram].name, "Init"))
		sprintf (name, "%s %d", programs[curProgram].name, curProgram + 1);
	else
		strcpy (name, programs[curProgram].name);
}

//-----------------------------------------------------------------------------------------
bool ADelay::getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text)
{
	if (index < kNumPrograms)
	{
		strcpy (text, programs[index].name);
		return true;
	}
	return false;
}

//------------------------------------------------------------------------
void ADelay::resume ()
{
	memset (buffer, 0, size * sizeof (float));
	AudioEffectX::resume ();
}

//------------------------------------------------------------------------
void ADelay::setParameter (VstInt32 index, float value)
{
	ADelayProgram* ap = &programs[curProgram];

	switch (index)
	{
		case kKnob :    fKnob = ap->fKnob = value;				break;
		case kPower :    fPower = ap->fPower = value;					break;
		case kMorph : fWetDry = ap->fWetDry = value; break;
		case kGain :      fGain = ap->fGain = value;			break;
	}
}

//------------------------------------------------------------------------
float ADelay::getParameter (VstInt32 index)
{
	float v = 0;

	switch (index)
	{
		case kKnob :    v = fKnob;	break;
		case kPower :    v = fPower;	break;
		case kMorph : v = fWetDry; break;
		case kGain :      v = fGain;		break;
	}
	return v;
}

//------------------------------------------------------------------------
void ADelay::getParameterName (VstInt32 index, char *label)
{
	switch (index)
	{
		case kKnob :   strcpy (label, "Knob");		break;
		case kPower :    strcpy (label, "Squash");		break;
		case kMorph : strcpy (label, "WetDry");	break;
		case kGain :      strcpy (label, "Gain");		break;
	}
}

//------------------------------------------------------------------------
void ADelay::getParameterDisplay (VstInt32 index, char *text)
{
	switch (index)
	{
		case kKnob :   int2string ((int)fKnob, text, kVstMaxParamStrLen);			break;
		case kPower :    int2string ((int)fPower, text, kVstMaxParamStrLen);			break;
		case kMorph : float2string (fWetDry, text, kVstMaxParamStrLen);	break;
		case kGain :      dB2string (fGain, text, kVstMaxParamStrLen);			break;
	}
}

//------------------------------------------------------------------------
void ADelay::getParameterLabel (VstInt32 index, char *label)
{
	switch (index)
	{
		case kKnob :    strcpy (label, "knob");	break;
		case kPower :    strcpy (label, "factor");	break;
		case kMorph : strcpy (label, "amount");	break;
		case kGain :      strcpy (label, "db");		break;
	}
}

//------------------------------------------------------------------------
bool ADelay::getEffectName (char* name)
{
	strcpy (name, "Delay");
#ifdef _DEBUG
	strcat (name, "(Debug)");
#endif
	return true;
}

//------------------------------------------------------------------------
bool ADelay::getProductString (char* text)
{
	strcpy (text, "Delay");
	return true;
}

//------------------------------------------------------------------------
bool ADelay::getVendorString (char* text)
{
	strcpy (text, "Steinberg Media Technologies");
	return true;
}

//---------------------------------------------------------------------------
void ADelay::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
	float* in1 = inputs[0];
	float* in2 = inputs[1];
	float* out1 = outputs[0];
	float* out2 = outputs[1];

	while (--sampleFrames >= 0)
	{
		float y1 = *in1++;
		//float y2 = *in2++;
		*out1++ = y1 * fGain;
		if (out2)
			*out2++ = y1 * fGain;
	}
	
/*
	while (--sampleFrames >= 0)
	{
		float x = *in1++;
		float y = buffer[cursor];
		buffer[cursor++] = x + y * fWetDry;
		if (cursor >= delay)
			cursor = 0;
		*out1++ = y * fGain;
		if (out2)
			*out2++ = y * fGain;
	}
	*/
}
