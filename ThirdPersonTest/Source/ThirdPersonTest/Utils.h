
#pragma once

inline FString TransformRoleToFString(ENetRole role)
{
	switch (role)
	{
		case ROLE_None:
			return FString("ROLE_None");
		case ROLE_Authority:
			return FString("ROLE_Authority");
		case ROLE_AutonomousProxy:
			return FString("ROLE_AutonomousProxy");
		case ROLE_SimulatedProxy:
			return FString("ROLE_SimulatedProxy");
		default:
			return FString("default");
	}
}
