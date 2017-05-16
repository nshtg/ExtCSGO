#pragma once
#include <windows.h>
namespace ExtCSGO
{
	enum PROCESS_FLAGS_CREATE
	{
		PROCESS_HANDLE =	( 1 << 0),
		PROCESS_WINDOW =		( 1 << 2 )
	};

	class Process
	{
		const char*		m_ProcessPath;
		const char*		m_ProcessName;
		const char*		m_WindowName;
		const char*		m_ProcessArguments;
		HANDLE			m_Process;
	public:
		Process(
			const char* ProcessPath,
			const char* ProcessName,
			const char* WindowName,
			const char* ProcessArguments);
		~Process();


		HANDLE GetProcess() const;

		bool   ReadMemory(LPCVOID Adr, LPVOID Buffer, SIZE_T Size) const;
		bool   Init();
		bool   IsValid(const int & PROCESS_FLAGS) const;
	};
}