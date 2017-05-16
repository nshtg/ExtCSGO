#include "sdk\IClientEntityList.h"
#include "Netvars.h"
#include "Engine.h"

namespace ExtCSGO::sdk
{

	IClientEntityList::IClientEntityList(const Engine *engine):
		m_Engine(engine)
	{

	}

	IClientEntityList::~IClientEntityList()
	{
	}

	vec3 IClientEntityList::GetBonePosition(const int & Index, const Player & player) const
	{
		static matrix3x4_t Matrix;
		if (!m_Engine->GetProcess()->ReadMemory
		(
			(PVOID)((DWORD64)player.GetdwBoneMatrix() + Index * 0x30),
			&Matrix, sizeof(matrix3x4_t)
		))
		{
			return vec3(0.f, 0.f, 0.f);
		}
		return vec3(Matrix[0][3], Matrix[1][3], Matrix[2][3]);
	}

	bool IClientEntityList::GetClientEntity(const int & Index, Player* Entity) const
	{
		static DWORD Ptr = 0;
		if (!m_Engine->GetProcess()->ReadMemory
		(
			(PVOID)((DWORD64)m_Engine->GetClientDLL()->GetdwBaseAddress() + m_EntityList + Index * 0x10),
			&Ptr, sizeof(DWORD)
		))
		{
			return false;
		}

		Player Ent;
		if (!m_Engine->GetProcess()->ReadMemory
		(
			(PVOID)((DWORD64)Ptr),
			&Ent, sizeof(Player)
		))
		{
			return false;
		}
		*Entity = Ent;

		return (Entity > nullptr);
	}
	
}