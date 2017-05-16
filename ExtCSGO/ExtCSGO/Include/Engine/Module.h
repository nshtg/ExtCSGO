#pragma once
#include <windows.h>
namespace ExtCSGO
{
	class Module
	{
		const char*		m_ModuleName;
		int				m_ListModules;
		HMODULE			m_BaseAddress;
	public:
		Module(const char* ModuleName, const int & LIST_MODULES);
		~Module();
		HMODULE		GetBaseAddress() const;
		DWORD		GetdwBaseAddress() const;

		void		Reset();

		bool		IsValid() const;
		bool		Init(const HANDLE & hProcess);
	};
}