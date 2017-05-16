#pragma once
#include "Vector.h"


namespace ExtCSGO::Maths
{
	void ClampAngles(vec3& v);
	void VectorNormalize(vec3& vec);
	void VectorAngles(vec3 & forward, vec3 & angles);
	void AngleVectors(const vec3 & angles, vec3 * forward);

	float AngleDistance(
		const vec3 & ViewAngles,
		const vec3 & TargetAngles,
		const vec3 & MyPos,
		const vec3 & TargetPos);

	float Distance2d(vec3 v1, vec3 v2);

	vec3 ConvertAngles(
		const float Sensitivity,
		const vec3 &AimAngle,
		const vec3 &ViewAngle);

	float GetFov(const vec3& viewAngle, const vec3& aimAngle);


	int PxAngleDistance(const vec3& PxAimAngle);
}