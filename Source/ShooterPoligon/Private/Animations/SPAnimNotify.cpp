// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

#include "Animations/SPAnimNotify.h"

void USPAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	// warning C4996: 'UAnimNotify::Notify': Please use the other Notify function instead Please update your code to the new API
	// before upgrading to the next release, otherwise your project will no longer compile.
	Super::Notify(MeshComp, Animation);
}
