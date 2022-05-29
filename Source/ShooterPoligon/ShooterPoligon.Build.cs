// Shooter Poligon. Created in educational purposes by SciKot. All Rights Reserved.

using UnrealBuildTool;

public class ShooterPoligon : ModuleRules
{
    public ShooterPoligon(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "PhysicsCore" });

        PublicIncludePaths.AddRange(new string[]
        {
            "ShooterPoligon/Public/Player",
            "ShooterPoligon/Public/Components",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
