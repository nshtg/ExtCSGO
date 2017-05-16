#pragma once
#include "..\Maths\Math.h"
namespace ExtCSGO::sdk
{
	class IVEngineClient
	{
		char m_IVEngine[0x10000];
	public:
		int GetLocalPlayer() const;
		vec3 GetViewAngles() const;
	};
}