#include "stdafx.h"

namespace ReClass {
	CWorld* GetWorld() { 
		return *(CWorld**)pBackend.GetWorldPtr(); 
	}
	
	CNetworkPlayerManager* GetNetworkPlayerManager() { 
		return *(CNetworkPlayerManager**)pBackend.GetNetworkPlayerManagerPtr(); 
	}
	
	CPed* GetCPed() {
		auto world = GetWorld();
		if (world) {
			return world->LocalPed;
		}

		return nullptr;
	}
}