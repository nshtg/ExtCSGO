#include "sdk\IVEngineClient.h"
#include "Netvars.h"
namespace ExtCSGO::sdk
{
	int IVEngineClient::GetLocalPlayer() const
	{
		static int Angles;
		GetArrayData(m_IVEngine, m_GetLocalPlayer, &Angles);
		return Angles;
	}

	vec3 IVEngineClient::GetViewAngles() const
	{
		static vec3 Angles;
		GetArrayData(m_IVEngine, m_ViewAngles, &Angles);
		return Angles;
	}
}