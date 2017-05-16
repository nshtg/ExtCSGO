#pragma once
#include "Engine.h"
#include "sdk\Player.h"


namespace ExtCSGO::Features
{
	class Aimbot
	{
		int					m_AimKey;
		double				m_AimFov;
		DWORD				m_AimSmooth;
		double				m_Sensitivity;

		const Engine*		m_Engine;
sdk::	IClientEntityList*	m_EntList;
sdk::	IVEngineClient*		m_IVEngine;
	public:
		Aimbot(const int &AimKey, const double & AimFov, const DWORD & AimSmooth, const double & Sensitivity, const Engine* Engine);
		~Aimbot();

		void Run();
	private:
		bool GetTargetAngles (
			const vec3 &		ViewAngles,
			vec3*				BestAngles,
			float*				AimFov) const;

		vec3 GetAimAngles (
			const int &			BoneId,
			const sdk::Player&	Local,
			const sdk::Player&	Entity) const;

		void PixelMove(
			const vec3 &		ViewAngles,
			const vec3 &		AimAngles,
			const float &       Sensitivity,
			const DWORD &       Smooth) const;
	};
}