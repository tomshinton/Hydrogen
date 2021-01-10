// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HydrogenTarget : TargetRules
{
	public HydrogenTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

        ExtraModuleNames.AddRange( new string[] { "Hydrogen" } );
    }
}
