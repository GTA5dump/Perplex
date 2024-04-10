#include "stdafx.h"
#include "allNetworkPlayersVehicleMenu.h"
#include "allNetworkPlayersMenu.h"
#include "menu/submenus/main/networking/playerList/playerMenu/networkPlayerVehicle.h"

using namespace AllNetworkPlayersVehicleMenuVars;

namespace AllNetworkPlayersVehicleMenuVars {
	Vars vars;

	void DissembleVehicleTrain() {
		if (!vars.vehicle_handles.empty()) {
			for (auto vehicle : vars.vehicle_handles) {
				if (vehicle != NULL) {
					if (DoesEntityExist(vehicle)) {
						if (IsEntityAttached(vehicle)) {
							pEntityControl.SimpleRequestControl(vehicle);
							SetEntityAsMissionEntity(vehicle, true, true);
							DetachEntity(vehicle, true, true);
							SetVehicleDoorsLocked(vehicle, 0);
						}
					}
				}
			}
			vars.vehicle_handles.clear();
		}
	}

	void AssembleVehicleTrain(SPlayer& player) {
		Vector3 Min, Max;
		Vehicle attach_to, to_attach;
		if (player.Id != GetLocalPlayer().Id) {
			if (player.bIsInVehicle) {
				if (GetLocalPlayer().bIsInVehicle) {
					attach_to = (vars.vehicle_handles.empty() ? GetLocalPlayer().Vehicle_ : vars.vehicle_handles[vars.vehicle_handles.size() - 1]);
					if (DoesEntityExist(attach_to)) {
						to_attach = player.Vehicle_;
						pEntityControl.SimpleRequestControl(attach_to);
						pEntityControl.SimpleRequestControl(to_attach);
						GetModelDimensions(GetEntityModel(attach_to), &Min, &Max);
						SetEntityAsMissionEntity(to_attach, true, true);
						if (IsEntityAttached(to_attach))
							DetachEntity(to_attach, true, true);
						AttachEntityToEntity(to_attach, attach_to, 0x0, 0.0f, Min.y - 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, true, true, false, 1, true);
						SetVehicleDoorsLocked(to_attach, 4);
						vars.vehicle_handles.push_back(to_attach);
					}
				}
			}
		}
	}

}

void AllNetworkPlayersVehicleMenu::Init() {
	SetParentSubmenu<AllNetworkPlayersMenu>();
	SetName("Vehicle", true, false);

	addOption(ButtonOption("Fix Vehicles")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::FixVehicle(player);
			});
		}
	));

	addOption(ToggleOption("Invincible Vehicles")
		.addToggle(vars.bInvincibleVehicle).addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::SetVehicleInvincible(player, vars.bInvincibleVehicle);
			});
	}));
	
	addOption(ToggleOption("Auto Repair Vehicles")
		.addToggle(vars.bAutoRepairVehicle).addTranslation());

	addOption(ToggleOption("Invisible Vehicles")
		.addToggle(vars.bInvisibleVehicle).addTranslation());

	addOption(ButtonOption("Max Upgrade")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::MaxUpgradeVehicle(player);
			});
		})
	);

	addOption(ButtonOption("Kick From Vehicles")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::KickFromVehicle(player);
			});
		}
	));

	addOption(ButtonOption("Delete Vehicles")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::DeleteVehicle(player);
			});
		}
	));

	addOption(ButtonOption("Pop Tyres")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::PopTyres(player);
			});
		}
	));

	addOption(ButtonOption("Slingshot")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::SlingshotVehicle(player);
			});
		}
	));

	addOption(ToggleOption("Pop Tyres Loop")
		.addToggle(vars.bPopTyres).addTranslation());

	addOption(ToggleOption("Freeze Vehicles")
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::FreezeVehicle(player, vars.bFreezeVehicle);
			});
		})
		.addToggle(vars.bFreezeVehicle).addTranslation());

	addOption(ToggleOption("Unmovable Vehicles")
		.addToggle(vars.bUnmovableVehicle).addTranslation());

	addOption(ToggleOption("Lock Vehicles Doors")
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::SetVehicleDoorsLockStatus(player, vars.bLockVehicleDoors);
			});
		})
	.addToggle(vars.bLockVehicleDoors).addTranslation());

	addOption(ToggleOption("Boost Vehicles On Horn Press")
		.addToggle(vars.bBoostVehicleOnHornPress).addTranslation());

	addOption(ToggleOption("Spin Vehicles")
		.addToggle(vars.bSpinVehicles).addTranslation());

	addOption(ToggleOption("Spin Vehicle")
		.addToggle(GetSelectedPlayer().bSpinVehicle).addTranslation()
		.addOnUpdate([](ToggleOption* option) { option->addToggle(GetSelectedPlayer().bSpinVehicle); }));

	addOption(ToggleOption("Slippy Tyres")
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::SlippyTyres(player, vars.bSlippyTyres);
			});
		})
		.addToggle(vars.bSlippyTyres).addTranslation());

	addOption(ToggleOption("Super Grip")
		.addToggle(vars.bSuperGrip).addTranslation());

	addOption(ToggleOption("Remove Gravity Rules")
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::RemoveGravityRules(player, vars.bRemoveGravityRules);
			});
		})
		.addToggle(vars.bRemoveGravityRules).addTranslation());

	addOption(ButtonOption("Set Vehicles As Stolen")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerVehicleMenuVars::SetVehicleStolen(player);
			});
		}
	));

	addOption(ToggleOption("Vehicle Train")
		.addToggle(vars.bVehicleTrain).addTranslation()
		.addFunction([] {
			if (vars.bVehicleTrain) {
				if (GetLocalPlayer().bIsInVehicle) {
					pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
						if (player.bIsInVehicle && DoesEntityExist(player.Ped)) {
							AssembleVehicleTrain(player);
						} 
					});
					if (vars.vehicle_handles.empty()) {
						pRenderer.NotifyBottom("Oops we could not find any players vehicles to attach!");
						vars.bVehicleTrain = false;
					}
				} else {
					pRenderer.NotifyBottom("You must be inside a vehicle...");
					vars.bVehicleTrain = false;
				}
			} else if (!vars.vehicle_handles.empty()) {
				DissembleVehicleTrain();
			}
		}
	));
}

/*Update once when submenu is opened*/
void AllNetworkPlayersVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AllNetworkPlayersVehicleMenu::Update() {}

/*Background update*/
void AllNetworkPlayersVehicleMenu::FeatureUpdate() {
	pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
		if (vars.bInvincibleVehicle) 
			NetworkPlayerVehicleMenuVars::SetVehicleInvincible(player, true);

		if (vars.bAutoRepairVehicle) 
			NetworkPlayerVehicleMenuVars::AutoRepairVehicle(player);

		if (vars.bInvisibleVehicle) 
			NetworkPlayerVehicleMenuVars::SetVehicleInvisible(player, true);

		if (vars.bPopTyres) 
			NetworkPlayerVehicleMenuVars::PopTyres(player);

		if (vars.bFreezeVehicle)
			NetworkPlayerVehicleMenuVars::FreezeVehicle(player, true);

		if (vars.bUnmovableVehicle) 
			NetworkPlayerVehicleMenuVars::SetVehicleSpeed(player, 0.0f);

		if (vars.bLockVehicleDoors)
			NetworkPlayerVehicleMenuVars::SetVehicleDoorsLockStatus(player, true);

		if (vars.bBoostVehicleOnHornPress) 
			NetworkPlayerVehicleMenuVars::BoostVehicleOnHornPress(player);

		if (vars.bSpinVehicles) 
			NetworkPlayerVehicleMenuVars::SpinVehicle(player);

		if (vars.bSlippyTyres) 
			NetworkPlayerVehicleMenuVars::SlippyTyres(player, true);

		if (vars.bRemoveGravityRules)
			NetworkPlayerVehicleMenuVars::RemoveGravityRules(player, true);

	});
}

/*Singleton*/
AllNetworkPlayersVehicleMenu* _instance;
AllNetworkPlayersVehicleMenu* AllNetworkPlayersVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AllNetworkPlayersVehicleMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
AllNetworkPlayersVehicleMenu::~AllNetworkPlayersVehicleMenu() { delete _instance; }