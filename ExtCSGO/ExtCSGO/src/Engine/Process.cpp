#include "Engine\Process.h"
#include <iostream>

namespace ExtCSGO
{
	bool HandleIsValid(const HANDLE & ProcessHandle);

	bool WindowExists(const char * WindowName);

	void CloseProcess(const char * ProcessName, const HANDLE & hProcess);

	bool NewProcess(
		const char* ProcessPath,
		const char* ProcessName,
		const char* Arguments,
		PHANDLE		ProcessHandle);

	Process::Process(
		const char* ProcessPath,
		const char* ProcessName,
		const char* WindowName,
		const char* ProcessArguments) :
			m_ProcessPath(ProcessPath), m_ProcessName(ProcessName),
			m_WindowName(WindowName), m_ProcessArguments(ProcessArguments)
	{
		m_Process = nullptr;
	}

	Process::~Process()
	{
	}

	HANDLE Process::GetProcess() const
	{
		return m_Process;
	}

	bool Process::ReadMemory(LPCVOID Adr, LPVOID Buffer, SIZE_T Size) const
	{
		return (ReadProcessMemory(m_Process, Adr, Buffer, Size, 0) > FALSE);
	}

	bool Process::Init()
	{
		if (IsValid(PROCESS_WINDOW))
		{
			#ifdef _DEBUG 
			#else
			CloseProcess(m_ProcessName, m_Process);
			m_Process = nullptr;
			Sleep(5000);
			#endif
		}
		else
		{
			m_Process = nullptr;
		}
		return NewProcess(m_ProcessPath, m_ProcessName, m_ProcessArguments, &m_Process);
	}

	bool Process::IsValid(const int & PROCESS_FLAGS) const
	{
		bool status = false;
		switch (PROCESS_FLAGS)
		{
			case PROCESS_WINDOW:
			{
				status = WindowExists(m_WindowName);
				break;
			}

			case PROCESS_HANDLE:
			{
				status = HandleIsValid(m_Process);
				break;
			}
		}
		return status;
	}

	bool HandleIsValid(const HANDLE & ProcessHandle)
	{
		if (ProcessHandle == nullptr)
			return false;

		DWORD ExitCode;
		GetExitCodeProcess(ProcessHandle, &ExitCode);
		return (ExitCode == STILL_ACTIVE);
	}

	bool WindowExists(const char * WindowName)
	{
		return (FindWindowA(0, WindowName) > nullptr);
	}

	void CloseProcess(const char * ProcessName, const HANDLE & hProcess)
	{
		std::string CmdString = 
		(
			"Taskkill /IM" + std::string(" ") + 
			ProcessName	   + std::string(" ") + "/F"
		);

		system(CmdString.c_str());
		if (hProcess > nullptr)
		{
			CloseHandle(hProcess);
		}
	}

	bool NewProcess(
		const char* ProcessPath,
		const char * ProcessName,
		const char* Arguments,
		PHANDLE ProcessHandle)
	{
	#ifdef _DEBUG 
		DWORD pid = 0;	
		GetWindowThreadProcessId(FindWindowA("Valve001", nullptr), &pid);
		if (pid == 0)
		{
			return false;
		}

		*ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

		if (*ProcessHandle == nullptr)
		{
			return false;
		}
	#else
		PROCESS_INFORMATION		pi = { 0 };
		STARTUPINFOA			si = { 0 };
								si.cb = sizeof(STARTUPINFO);
								si.dwFlags = STARTF_USESHOWWINDOW;
								si.wShowWindow = SW_HIDE;

	
		std::string FullPath = std::string
		(
			ProcessPath + std::string("")	+
			ProcessName + std::string(" ")	+
			Arguments
		);

		if (!CreateProcessA(
			nullptr,
			(LPSTR)FullPath.c_str(),
			nullptr,
			nullptr,
			FALSE,
			FALSE,
			nullptr,
			nullptr,
			&si,
			&pi))
		{
			return false;
		}

		CloseHandle(pi.hThread);

		*ProcessHandle = pi.hProcess;
	#endif
		return true;
	}
}


