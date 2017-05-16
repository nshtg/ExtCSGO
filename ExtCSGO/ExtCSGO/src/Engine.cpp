#include "Engine.h"
#include "NetVars.h"

#define LIST_MODULES_32BIT 0x1
#define LIST_MODULES_64BIT 0x2
#define LIST_MODULES_ALL 0x3

namespace ExtCSGO
{
	using namespace sdk;
	Engine::Engine() :
		m_Process(new Process (
		"C:/Program Files (x86)/Steam/steamapps/common/Counter-Strike Global Offensive/",
		"csgo.exe",
		"Counter-Strike: Global Offensive",
		"-steam -freq 144 -novid") ),
		m_ClientDLL(new Module("client.dll", LIST_MODULES_32BIT)),
		m_EngineDLL(new Module("engine.dll", LIST_MODULES_32BIT)),
		m_IClientEntity(new IClientEntityList(this))
	{
	}

	Engine::~Engine()
	{
		delete m_EngineDLL;
		delete m_ClientDLL;
		delete m_Process;
	}

	Process * Engine::GetProcess() const
	{
		return m_Process;
	}

	Module * Engine::GetClientDLL() const
	{
		return m_ClientDLL;
	}

	Module * Engine::GetEngineDLL() const
	{
		return m_EngineDLL;
	}

	bool Engine::GetClient(IClientEntityList **EntityList) const
	{
		*EntityList = m_IClientEntity;
		return (m_IClientEntity > nullptr);
	}

	bool Engine::GetIVEngine(IVEngineClient **IVEngine) const
	{
		static DWORD Ptr = 0;
		if (!m_Process->ReadMemory
		(
			(PVOID)((DWORD64)m_EngineDLL->GetdwBaseAddress() + m_ClientState),
			&Ptr, sizeof(vec3)
		))
		{
			return false;
		}

		static IVEngineClient Engine;
		if (!m_Process->ReadMemory
		(
			(PVOID)(DWORD64)(Ptr),
			&Engine, sizeof(IVEngineClient)
		))
		{
			return false;
		}

		*IVEngine = &Engine;


		return (*IVEngine > nullptr);
	}

	void Engine::Update() const
	{
		if (!IsHandleValid())
		{
			GetClientDLL()->Reset();
			GetEngineDLL()->Reset();

			GetProcess()->Init();
		}
		else
		{
			GetClientDLL()->Init(GetProcess()->GetProcess());
			GetEngineDLL()->Init(GetProcess()->GetProcess());

			if (IsValid())
			{
				std::cout << "Process Found! Handle:" << m_Process->GetProcess() << std::endl;
			}
		}
	}

	bool Engine::IsValid() const
	{
		return (IsHandleValid() && IsModuleValid());
	}

	bool Engine::IsHandleValid() const
	{
		return GetProcess()->IsValid(PROCESS_HANDLE);
	}

	bool Engine::IsModuleValid() const
	{
		return GetClientDLL()->IsValid() &&
			   GetEngineDLL()->IsValid();
	}
}