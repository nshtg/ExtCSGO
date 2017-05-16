#include "Update.h"

#include <iostream>
namespace ExtCSGO
{
	using namespace Features;
	Update::Update(char* argv[]):
		m_Engine(new Engine()),
		m_Aimbot(new Aimbot(std::atoi(argv[1]), std::atof(argv[2]), std::atoi(argv[3]), std::atof(argv[4]), m_Engine))
	{
	}

	Update::~Update()
	{
		delete m_Aimbot;
		delete m_Engine;
	}

	int Update::Run() const
	{
		bool Running = false;
		while (true)
		{
			if (Running == true)
			{
				if (m_Engine->IsValid())
				{
					m_Aimbot->Run();		
				}
				else
				{
					#ifdef _DEBUG
					#else
					Sleep(5000);
					#endif
					m_Engine->Update();
				}
			}
			if (GetAsyncKeyState(VK_INSERT) & 1)
			{
				Running = !Running;
			}
			Sleep(1);
		}
		return 0;
	}	
}