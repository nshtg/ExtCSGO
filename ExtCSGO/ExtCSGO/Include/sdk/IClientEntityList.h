#pragma once


namespace ExtCSGO
{
	class Engine;
	class vec3;
}
namespace ExtCSGO::sdk
{
	class Player;
	class IClientEntityList
	{
		const Engine *m_Engine;
	public:
		IClientEntityList(const Engine *engine);
		~IClientEntityList();

		vec3 GetBonePosition(const int & Index, const Player& player) const;
		bool GetClientEntity(const int & Index, Player* Entity) const;
	};
}