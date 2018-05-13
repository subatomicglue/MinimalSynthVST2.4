//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4		$Date: 2006/11/13 09:08:27 $
//
// Category     : VST 2.x SDK Samples
// Filename     : surrounddelay.cpp
// Created by   : Steinberg Media Technologies
// Description  : Simple Surround Delay plugin with Editor using VSTGUI
//
// © 2006, Steinberg Media Technologies, All Rights Reserved
//-------------------------------------------------------------------------------------------------------

#ifndef __surrounddelay__
#include "surrounddelay.h"
#endif

#ifndef __sdeditor__
#include "editor/sdeditor.h"
#endif

#include <string.h>
#include <stdio.h>

//-------------------------------------------------------------------------------------------------------
AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new SurroundDelay (audioMaster);
}

//-----------------------------------------------------------------------------
SurroundDelay::SurroundDelay (audioMasterCallback audioMaster)
: ADelay (audioMaster)
, plugInput (0)
, plugOutput (0)
{
	
	// The first buffer is allocated in ADelay's constructor
	for (int i = 1; i < MAX_CHANNELS; i++)
	{
		sBuffers[i] = new float[size];
	}
	
	setNumInputs (MAX_CHANNELS);
	setNumOutputs (MAX_CHANNELS);

	// We initialize the arrangements to default values.
	// Nevertheless, the host should modify them via
	// appropriate calls to setSpeakerArrangement.
	allocateArrangement (&plugInput, MAX_CHANNELS);
	plugInput->type = kSpeakerArr51;

	allocateArrangement (&plugOutput, MAX_CHANNELS);
	plugOutput->type = kSpeakerArr51;

	setUniqueID ('SDlE');	// this should be unique, use the Steinberg web page for plugin Id registration

	// create the editor
	editor = new SDEditor (this);

	resume ();
}

//-----------------------------------------------------------------------------
SurroundDelay::~SurroundDelay ()
{
	sBuffers[0] = 0;
	// We let ~ADelay delete "buffer"...
	for (int i = 1; i < MAX_CHANNELS; i++)
	{
		if (sBuffers[i])
		{
			delete[] sBuffers[i];
		}
		sBuffers[i] = 0;
	}
	
	deallocateArrangement (&plugInput);
	deallocateArrangement (&plugOutput);
}

//------------------------------------------------------------------------
void SurroundDelay::resume ()
{
	memset (buffer, 0, size * sizeof (float));
	sBuffers[0] = buffer;

	for (int i = 1; i < MAX_CHANNELS; i++)
	{
		memset (sBuffers[i], 0, size * sizeof (float));
	}
}

//------------------------------------------------------------------------
bool SurroundDelay::getSpeakerArrangement (VstSpeakerArrangement** pluginInput, VstSpeakerArrangement** pluginOutput)
{
	*pluginInput  = plugInput;
	*pluginOutput = plugOutput;
	return true;
}

//------------------------------------------------------------------------
bool SurroundDelay::setSpeakerArrangement (VstSpeakerArrangement* pluginInput,
									 VstSpeakerArrangement* pluginOutput)
{
	if (!pluginOutput || !pluginInput)
		return false;

	bool result = true;
	
	// This plug-in can act on any speaker arrangement,
	// provided that there are the same number of inputs/outputs.
	if (pluginInput->numChannels > MAX_CHANNELS)
	{
		// This plug-in can't have so many channels. So we answer
		// false, and we set the input arrangement with the maximum
		// number of channels possible
		result = false;
		allocateArrangement (&plugInput, MAX_CHANNELS);
		plugInput->type = kSpeakerArr51;
	}
	else
	{
		matchArrangement (&plugInput, pluginInput);
	}
	
	if (pluginOutput->numChannels != plugInput->numChannels)
	{
		// This plug-in only deals with symetric IO configurations...
		result = false;
		matchArrangement (&plugOutput, plugInput);
	}
	else
	{
		matchArrangement (&plugOutput, pluginOutput);
	}

	return result;
}

#include "../../../../../MantisSynth/src/syn/Math.h"

syn::PeakFollower peaks[2];

//------------------------------------------------------------------------
void SurroundDelay::processReplacing (float** inputs, float** outputs, VstInt32 sampleframes)
{
	//switch (plugInput->numChannels)
	//{
	//case 2:
		{
			float* in1 = inputs[0];
			float* in2 = inputs[1];
			float* out1 = outputs[0];
			float* out2 = outputs[1];
            float vol = fGain * 3.0f;
            float power = 1.0f + 30.0f * fPower;
			while (--sampleframes >= 0)
			{
                float y1 = syn::Math::clamp( *in1++ * vol, -1.0f, 1.0f );
				//peaks[0].peakFollower( y1, 44100 );
				float yout1;
                if (fabsf( y1 ) <= fKnob)
                {
                    yout1 = y1;
                }
                else
                {
                    if (0.0f <= y1)
                    {
                        yout1 = y1;
                        float scale = (1.0f - fKnob);
				        yout1 -= fKnob;
                        yout1 /= scale;
				        yout1 = syn::Math::smoothExpPowT( yout1, power );
                        yout1 *= scale * fKnob;
                        yout1 += fKnob;
                    }
                    else
                    {
                        yout1 = y1;
                        float scale = (1.0f - fKnob);
				        yout1 += fKnob;
                        yout1 /= scale;
				        yout1 = -syn::Math::smoothExpPowT( -yout1, power );
                        yout1 *= scale * fKnob;
				        yout1 -= fKnob;
                    }
                    
                }
				*out1++ = syn::Math::lerp( fWetDry, y1, yout1 );

				float y2 = syn::Math::clamp( *in2++ * vol, -1.0f, 1.0f );
				//peaks[1].peakFollower( y2, 44100 );
				float yout2;
				if (0.0f <= y2)
					yout2 = syn::Math::smoothExpPowT( y2, power );
				else
					yout2 = -syn::Math::smoothExpPowT( -y2, power );
				
				*out2++ = syn::Math::lerp( fWetDry, y2, yout2 );
			}
		}
	//	break;

	//default:
		/*
		// copy 1:1 input to output...
		{
			for (int i = 0; i < plugInput->numChannels; i++)
			{
				float* in1 = inputs[i];
				float* out1 = outputs[i];
				VstInt32 frames = sampleframes;
				while (--frames >= 0)
				{
					float y1 = *in1++;
					*out1++ = y1 * fGain;
				}
			}
		}
		*/
	//	break;
	//}


	buffer = sBuffers[0];
}

//-----------------------------------------------------------------------------
void SurroundDelay::setParameter (VstInt32 index, float value)
{
	ADelay::setParameter (index, value);

	if (editor)
		((AEffGUIEditor*)editor)->setParameter (index, value);
}
