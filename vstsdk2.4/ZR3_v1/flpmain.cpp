#include "audioeffect.h"
#include "Globals.h"
#include "flp.h"

//------------------------------------------------------------------------
AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new flp (audioMaster);
}
