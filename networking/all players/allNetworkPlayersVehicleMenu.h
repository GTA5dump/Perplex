#pragma once
#include "menu/submenu.h"

class AllNetworkPlayersVehicleMenu : public Submenu {
public:
	static AllNetworkPlayersVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AllNetworkPlayersVehicleMenu() : Submenu() {}
	~AllNetworkPlayersVehicleMenu();
};

namespace AllNetworkPlayersVehicleMenuVars
{
	struct Vars {
		bool bInvincibleVehicle;
		bool bAutoRepairVehicle;
		bool bInvisibleVehicle;
		bool bPopTyres;
		bool bFreezeVehicle;
		bool bUnmovableVehicle;
		bool bLockVehicleDoors;
		bool bBoostVehicleOnHornPress;
		bool bSpinVehicles;
		bool bSlippyTyres;
		bool bSuperGrip;
		bool bRemoveGravityRules;
		bool bVehicleTrain;

		vector<Vehicle>vehicle_handles;
	};

	extern Vars vars;
}