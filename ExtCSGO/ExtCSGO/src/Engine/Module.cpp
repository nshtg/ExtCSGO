#include "Engine\Module.h"
#include <Psapi.h>
#include <iostream>
namespace ExtCSGO
{
	bool ExGetModuleHandle(
		const HANDLE &  hProcess,
		const char*		ModuleName,
		int				LIST_MODULES,
		HMODULE*		hModule);


	Module::Module(const char* ModuleName, const int & LIST_MODULES) : 
		m_ModuleName(ModuleName),
		m_ListModules(LIST_MODULES)
	{
		m_BaseAddress = nullptr;
	}

	Module::~Module()
	{
	}

	HMODULE Module::GetBaseAddress() const
	{
		return m_BaseAddress;
	}

	DWORD Module::GetdwBaseAddress() const
	{
		return (DWORD)(DWORD64)m_BaseAddress;
	}

	void Module::Reset()
	{
		m_BaseAddress = nullptr;
	}

	bool Module::IsValid() const
	{
		return (m_BaseAddress > nullptr);
	}

	bool Module::Init(const HANDLE & hProcess)
	{
		return ExGetModuleHandle(hProcess, m_ModuleName, m_ListModules, &m_BaseAddress);
	}

	bool ExGetModuleHandle(
		const HANDLE &  hProcess,
		const char*		ModuleName,
		int				LIST_MODULES,
		HMODULE*		hModule)
	{
		DWORD				ModuleCount = 0;
		HMODULE				Modules[1024] = { 0 };
		CHAR				Name[MAX_PATH] = { 0 };

		if (!K32EnumProcessModulesEx(hProcess, Modules, 1024, &ModuleCount, LIST_MODULES))
			return false;

		for (DWORD i = 0; i < ModuleCount; i++)
		{
			if (!K32GetModuleBaseNameA(hProcess, Modules[i], Name, MAX_PATH))
				continue;

			if (!_stricmp(Name, ModuleName))
			{
				*hModule = Modules[i];
				break;
			}

		}

		if (*hModule == nullptr)
		{
			return false;
		}

		return true;
	}


}