// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HydrogenClientTarget : TargetRules
{
	public HydrogenClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;

		ExtraModuleNames.AddRange( new string[] { "Hydrogen" } );

		GlobalDefinitions.Add("UIPOOLING=1");
	}
}
