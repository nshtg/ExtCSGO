#pragma once
#include "Engine.h"
#include "Features\Aimbot.h"

namespace ExtCSGO
{
	class Update
	{
		Engine* m_Engine;

		Features::
		Aimbot* m_Aimbot;
	public:
		Update(char* argv[]);
		~Update();
		int Run() const;
	};
}