#include "Features\Aimbot.h"
#include "Maths\Math.h"

namespace ExtCSGO::Features
{
	using namespace sdk;
	using namespace Maths;

	Aimbot::Aimbot(const int &AimKey, const double & AimFov, const DWORD & AimSmooth, const double & Sensitivity, const Engine* Engine) :
		m_AimKey(AimKey),
		m_AimFov(AimFov),
		m_AimSmooth(AimSmooth),
		m_Sensitivity(Sensitivity),
		m_Engine(Engine)
	{
	}

	Aimbot::~Aimbot()
	{
	}

	void Aimbot::Run()
	{
		if (GetAsyncKeyState(m_AimKey))
		{
			if (!m_Engine->GetIVEngine(&m_IVEngine))
				return;

			if (!m_Engine->GetClient(&m_EntList))
				return;

			vec3 AimAngles; float Fov;
			if (!GetTargetAngles(m_IVEngine->GetViewAngles(), &AimAngles, &Fov))
				return;

			if (Fov < (float)m_AimFov)
			{
				PixelMove(m_IVEngine->GetViewAngles(), AimAngles, (float)m_Sensitivity, m_AimSmooth);
			}
			
		}
	}

	bool Aimbot::GetTargetAngles (
		const vec3 &	ViewAngles,
		vec3*			BestAngles,
		float*			AimFov) const
	{
		static float	BestFov = 180.f;
		static Player	LocalPlayer, Enemy;
		int				BestIndex = -1;

		m_EntList->GetClientEntity(m_IVEngine->GetLocalPlayer(), &LocalPlayer);
		if (!LocalPlayer.IsValid())
		{
			return false;
		}

		for (auto i = 1; i < 32; i++)
		{
			if (!m_EntList->GetClientEntity(i, &Enemy))
				continue;

			if (!Enemy.IsValid())
				continue;
			
			if (Enemy.GetTeamNum() == LocalPlayer.GetTeamNum())
				continue;

			auto AimAngles = GetAimAngles(8, LocalPlayer, Enemy);

			
			auto Fov = GetFov(ViewAngles, AimAngles);

			if (Fov < BestFov)
			{
				BestFov = Fov;

				BestIndex = i;
				*BestAngles = AimAngles;
			}		
		}
		if (BestIndex == -1)
		{
			BestFov = 180.f;
			*BestAngles = 0.f;
			return false;
		}
		*AimFov = BestFov;


		return (BestFov < 180.f);
	}

	vec3 Aimbot::GetAimAngles(
		const int &		BoneId,
		const Player&	Local,
		const Player&	Entity) const
	{
		vec3 AimAngles, BoneCoords;
		BoneCoords = m_EntList->GetBonePosition(BoneId, Entity);
		BoneCoords -= Local.GetEyePosition();

		VectorNormalize(BoneCoords);
		VectorAngles(BoneCoords, AimAngles);

		if (Local.GetShotsFired() > 1)
		{
			AimAngles -= Local.GetVecPunch() * 2.0f;
		}
		ClampAngles(AimAngles);
		return AimAngles;
	}

	void Aimbot::PixelMove(
		const vec3 &	ViewAngles,
		const vec3 &	AimAngles,
		const float &	Sensitivity,
		const DWORD &	Smooth) const
	{
		vec3 PixelAngles = ConvertAngles(Sensitivity, AimAngles, ViewAngles);
		if (Smooth > 0)
		{
			vec3 Smoothed;
			if (Smoothed.x != PixelAngles.x && std::abs(PixelAngles.x) > std::abs(PixelAngles.y))
			{
				Smoothed.x = Smoothed.x < PixelAngles.x ? Smoothed.x += 2 : (Smoothed.x > PixelAngles.x ? Smoothed.x -= 2 : Smoothed.x = PixelAngles.x);
			}
			else if (Smoothed.y != PixelAngles.y)
			{
				Smoothed.y = Smoothed.y < PixelAngles.y ? Smoothed.y += 2 : (Smoothed.y > PixelAngles.y ? Smoothed.y -= 2 : Smoothed.y = PixelAngles.y);
			}
			static auto TickCount = GetTickCount();
			if (GetTickCount() - TickCount >= Smooth - 1)
			{
				TickCount = GetTickCount();
				mouse_event(MOUSEEVENTF_MOVE, (int)Smoothed.x, (int)Smoothed.y, 0, 0);
			}
			
		}
		else
		{
			static auto TickCount = GetTickCount();
			if (GetTickCount() - TickCount > 0)
			{
				TickCount = GetTickCount();
				mouse_event(MOUSEEVENTF_MOVE, (int)PixelAngles.x, (int)PixelAngles.y, 0, 0);
			}
		}
	}
}
