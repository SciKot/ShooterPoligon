// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "SPGameInstance.h"

#include "Sound/SPSoundFuncLib.h"

void USPGameInstance::ToggleVolume()
{
	USPSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}
