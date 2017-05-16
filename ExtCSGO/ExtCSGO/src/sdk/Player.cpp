#include "sdk\Player.h"
#include "Netvars.h"
namespace ExtCSGO::sdk
{
	int Player::GetHealth() const 
	{
		static int result = -1;
		GetArrayData(m_Player, m_iHealth, &result);
		return result;
	}

	int Player::GetTeamNum() const
	{
		static int result = -1;
		GetArrayData(m_Player, m_iTeamNum, &result);
		return result;
	}

	int Player::GetLifeState() const
	{
		static int result = -1;
		GetArrayData(m_Player, m_LifeState, &result);
		return result;
	}

	int Player::GetShotsFired() const
	{
		static int result = -1;
		GetArrayData(m_Player, m_iShotsFired, &result);
		return result;
	}

	vec3 Player::GetOrigin() const
	{
		static vec3 result;
		GetArrayData(m_Player, m_VecOrigin, &result);
		return result;
	}

	vec3 Player::GetVecView() const
	{
		static vec3 result;
		GetArrayData(m_Player, m_VecView + 0x4, &result);
		return vec3(0.f, 0.f, result.y);
	}

	vec3 Player::GetEyePosition() const
	{
		return vec3(GetOrigin() + GetVecView());
	}

	vec3 Player::GetVecPunch() const
	{
		static vec3 result;
		GetArrayData(m_Player, m_aimPunchAngle, &result);
		return result;
	}

	uint32_t Player::GetdwBoneMatrix() const
	{
		static uint32_t result = 0;
		GetArrayData(m_Player, m_BoneMatrix, &result);
		return result;
	}

	bool Player::IsDormant() const
	{
		static bool result = false;
		GetArrayData(m_Player, m_Dormant, &result);
		return result;
	}

	bool Player::IsValid() const
	{
		if (this->GetHealth() < 1 && this->GetHealth() > 1337)
			return false;

		if (this->IsDormant())
			return false;

		if (this->GetLifeState() != 0)
			return false;

		return true;
	}


}