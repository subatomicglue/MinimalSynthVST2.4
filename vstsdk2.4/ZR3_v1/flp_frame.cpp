#include "Globals.h"
#include "flp.h"
#include "Editor.h"
#include <stdio.h>

#if WIN32
	#include <wtypes.h>
#endif

void flp::initall()
{
	int x;
	mono_before=0;
	samplecount=0;
	mono=mono1=mono2=l_before=r_before=0;
	
	viblfo=0;
	vmix1=vmix2=0;

	dist=fuzz=odmix=0;
	spread=spread2=cross1=0;
	lslow=lfast=uslow=ufast=ubelt_up=ubelt_down=lbelt_up=lbelt_down=lspeed=uspeed=0;
	er_r=er_l=0;
	lp=right=left=lright=lleft=upper=lower=0;
	llfo_out=llfo_nout=llfo_d_out=llfo_d_nout=0;
	lfo_out=lfo_nout=lfo_d_out=lfo_d_nout=0;
	last_out1=last_out2=0;

	VCA=1;
	compare=false;
	waitforsplit=false;
	splitpoint=0;

	odmix=0;
	vmix1=0;
	vmix2=0;

	for(x=0;x<WAVETABLESIZE*12+1;x++)
		wavetable[x]=0;

	for(x=0;x<kNumParams;x++)
		last_value[x]=-99;

	for(x=0;x<EVTBUFSIZE;x++)
	{
		this->delta[x]=-10;
		this->events[x]=evt_none;
	}
	event_pos=event_read_pos=0;
	has_events=false;

	if(samplerate<8000)
		samplerate=44100;
}

flp::flp (audioMasterCallback audioMaster) : AudioEffectX (audioMaster, kNumPrograms, kNumParams)
{
	mute=true;
	if (audioMaster)
	{
		setNumInputs (0);
		setNumOutputs (kNumOutputs);
		canProcessReplacing ();
//		hasVu (false);
//		hasClip (false);
		isSynth (true);
		noTail(false);
		setUniqueID (MY_ID);
	}

	initall();

	n1 = new notemaster(NUMOFVOICES);
	vdelay1 = new delay(441,true);
	vdelay2 = new delay(441,true);
	wand_r=new delay(4410,false);
	wand_l=new delay(4410,false);
	delay1 = new delay(4410,true);
	delay2 = new delay(4410,true);
	delay3 = new delay(4410,true);
	delay4 = new delay(4410,true);

	delay1->flood(0);
	delay2->flood(0);
	delay3->flood(0);
	delay4->flood(0);
	vdelay1->flood(0);
	vdelay2->flood(0);
	wand_r->flood(0);
	wand_l->flood(0);

	my_p=virtual_my_p=programs[0].p;
	setProgramDelayCount=0;
	setSampleRate((float)updateSampleRate());
	setFactorySounds();
	actual_curProgram=-1;
	setProgram (0);

	make_waveforms(W_SINE);

	editor=NULL;
	editor=new Editor(this);

	suspend();
	resume();
}

flp::~flp ()
{
	if(n1!=NULL)
		n1->~notemaster();
	n1=NULL;
	if(wand_r!=NULL)
		wand_r->~delay();
	wand_r=NULL;
	if(wand_l!=NULL)
		wand_l->~delay();
	wand_l=NULL;
	if(vdelay1!=NULL)
		vdelay1->~delay();
	vdelay1=NULL;
	if(vdelay2!=NULL)
		vdelay2->~delay();
	vdelay2=NULL;
	if(delay1!=NULL)
		delay1->~delay();
	delay1=NULL;
	if(delay2!=NULL)
		delay2->~delay();
	delay2=NULL;
	if(delay3!=NULL)
		delay3->~delay();
	delay3=NULL;
	if(delay4!=NULL)
		delay4->~delay();
	delay4=NULL;
	if (editor!=NULL)
		editor->~AEffEditor();
	editor=NULL;
}

void flp::setSampleRate (float sampleRate)
{
	AudioEffectX::setSampleRate (sampleRate);
	samplerate=sampleRate;
	
//	warmth.setparam(4500,1.0f,sampleRate);
	warmth.setparam(2700,1.2f,sampleRate);

	if(n1!=NULL)
		n1->set_samplerate(samplerate);
	if(vdelay1!=NULL)
		vdelay1->set_samplerate(samplerate);
	if(vdelay2!=NULL)
		vdelay2->set_samplerate(samplerate);
	vlfo.set_samplerate(samplerate);
	vlfo.set_rate(35,0);
	fuzz_filt.setparam(300,1,samplerate);
//	split.setparam(800,.5f,samplerate);
	split.setparam(400,1.3f,samplerate);
//	horn_filt.setparam(4000,.5f,samplerate);
	horn_filt.setparam(1700,1.0f,samplerate);
	if(wand_r!=NULL)
	{
		wand_r->set_samplerate(samplerate);
		wand_r->set_delay(40);
	}
	if(wand_r!=NULL)
	{
		wand_l->set_samplerate(samplerate);
		wand_l->set_delay(35);
	}
	if(delay1!=NULL)
		delay1->set_samplerate(samplerate);
	if(delay2!=NULL)
		delay2->set_samplerate(samplerate);
	if(delay3!=NULL)
		delay3->set_samplerate(samplerate);
	if(delay4!=NULL)
		delay4->set_samplerate(samplerate);
	lfo1.set_samplerate(samplerate);
	lfo2.set_samplerate(samplerate);
	lfo3.set_samplerate(samplerate);
	lfo4.set_samplerate(samplerate);
}
