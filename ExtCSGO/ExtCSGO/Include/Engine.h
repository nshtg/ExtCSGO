#pragma once
#include "Engine\Process.h"
#include "Engine\Module.h"

#include "sdk\Player.h"
#include "sdk\IVEngineClient.h"
#include "sdk\IClientEntityList.h"


namespace ExtCSGO
{
	class Engine
	{
		Process*           m_Process;
sdk::   IClientEntityList* m_IClientEntity;
		Module*            m_ClientDLL;
		Module*            m_EngineDLL;
	public:
		Engine();
		~Engine();

		Process*				GetProcess() const;
		Module*					GetClientDLL() const;
		Module*					GetEngineDLL() const;

		bool GetClient(sdk::IClientEntityList** EntityList) const;
		bool GetIVEngine(sdk::IVEngineClient** IVEngine) const;

		void		Update() const;
		bool		IsValid() const;
	private:
		bool		IsHandleValid() const;
		bool		IsModuleValid() const;
	};
}