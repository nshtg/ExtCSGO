#pragma once
#include "Maths\Vector.h"

namespace ExtCSGO::sdk
{	
	class Player
	{
		char m_Player[0x10000];
	public:
		int GetHealth() const;
		int GetTeamNum() const;
		int GetLifeState() const;
		int GetShotsFired() const;

		vec3 GetOrigin() const;
		vec3 GetVecView() const;
		vec3 GetEyePosition() const;
		vec3 GetVecPunch() const;
		uint32_t GetdwBoneMatrix() const;


		bool IsDormant() const;
		bool IsValid() const;

		void Reset()
		{
			for (int i = 0; i < 0x10000; i++)
				m_Player[i] = 0;
		}
	};
}