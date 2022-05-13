// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ShooterPoligonEditorTarget : TargetRules
{
	public ShooterPoligonEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShooterPoligon" } );
	}
}
