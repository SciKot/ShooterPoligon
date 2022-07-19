// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Sound/SPSoundFuncLib.h"

#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPSoundFuncLib, All, All);

void USPSoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	if (!SoundClass) return;

	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	UE_LOG(LogSPSoundFuncLib, Display, TEXT("Sound class volume was changed: %s = %f"), *SoundClass->GetName(),
		SoundClass->Properties.Volume);
}

void USPSoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if (!SoundClass) return;

	const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
	SetSoundClassVolume(SoundClass, NextVolume);
}
