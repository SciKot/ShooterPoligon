// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ShooterPoligonTarget : TargetRules
{
	public ShooterPoligonTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShooterPoligon" } );
	}
}
