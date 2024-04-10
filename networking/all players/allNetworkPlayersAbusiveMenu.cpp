#include "stdafx.h"
#include "allNetworkPlayersAbusiveMenu.h"
#include "allNetworkPlayersMenu.h"
#include "menu/submenus/main/networking/playerList/playerMenu/networkPlayerAbusive.h"
#include "menu/submenus/main/networking/all players/Abusive/allNetworkPlayersAbusiveAttachmentsMenu.h"


using namespace AllNetworkPlayersAbusiveMenuVars;

namespace AllNetworkPlayersAbusiveMenuVars {
	Vars vars;

}

void AllNetworkPlayersAbusiveMenu::Init() {
	SetParentSubmenu<AllNetworkPlayersMenu>();
	SetName("Abusive", true, false);

	addOption(SubmenuOption("Attachments")
		.addSubmenu<AllNetworkPlayersAbusiveAttachmentsMenu>()
		.addTranslation());

	addOption(ButtonOption("Crash Session")
		.addTranslation()
		.addFunction([] {
			pBackend.iSessionCrashTimeout = GetGameTimer() + 10000;
			pNatives.SyncLobbyWeather(-1, -1, -1, 0);
			pRenderer.NotifyStack("Successfully crashed session!");
		}
	));

	addOption(ButtonOption("Non-Host Kick")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer& player) {
				NetworkPlayerAbusiveMenuVars::NonHostKick(player);
			});
		}
	));

	addOption(ButtonOption("Ram With Bus")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::RamPlayer(player);
			});
		}
	).addTooltip("Ram the players with a bus"));

	addOption(ButtonOption("Burn")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::BurnPlayer(player);
			});
		}
	));

	addOption(ButtonOption("Explode (Blame Yourself)")
		.addTranslation()
		.addFunction([] {
			NetworkPlayerAbusiveMenuVars::BlamePlayer(GetLocalPlayer());
		}
	));

	addOption(ButtonOption("Explode")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::ExplodePlayer(player);
			});
		}
	));

	addOption(ToggleOption("Explode Loop")
		.addToggle(vars.bExplode).addTranslation());

	addOption(ToggleOption("Explode Talking Players")
		.addToggle(vars.bExplodeTalking).addTranslation());

	addOption(ToggleOption("Forcefield")
		.addToggle(vars.bForceField).addTranslation());

	addOption(ToggleOption("Incapacitate")
		.addToggle(vars.bIncapacitate).addTranslation());

	addOption(ButtonOption("Clone")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::Clone(player);
			});
		}
	));

	addOption(ButtonOption("Trap In Cage")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::TrapPlayerInCage(player);
			});
		}
	));

	addOption(ButtonOption("Remove Weapons")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::RemovePlayerWeapons(player);
			});
		}
	));

	addOption(NumberOption<int>(SCROLLSELECT, "Give Stars")
		.addNumber(vars.iGiveStars, "%i", 1).addMin(1).addMax(5).addTranslation()
		.addFunction([]{
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::GivePlayerStars(player, vars.iGiveStars);
			});
		}
	));

	addOption(ToggleOption("Always Wanted")
		.addToggle(vars.bAlwaysWanted).addTranslation());

	addOption(ButtonOption("Ragdoll")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::Ragdoll(player);
			});
		}
	));

	addOption(ButtonOption("Shake Camera")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::ShakePlayerCamera(player);
			});
		}
	));

	addOption(ToggleOption("Shake Camera Loop")
		.addToggle(vars.bShakeCamera).addTranslation());

	addOption(ToggleOption("Troll Money Bags")
		.addToggle(vars.bTrollMoneyBags).addTranslation());

	addOption(ButtonOption("Glitch Players")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::GlitchPlayer(player);
			});
		}
	));

	addOption(ToggleOption("Glitch Players Loop")
		.addToggle(vars.bGlitchPlayersLoop).addTranslation());

	addOption(ButtonOption("Ban From Current CEO")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::BanFromCEO(player);
			});
		}
	));

	addOption(ButtonOption("Kick From Current CEO")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::KickFromCEO(player);
			});
		}
	));

	addOption(ButtonOption("Kick From Vehicle")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::KickPlayerFromVehicle(player);
			});
		}
	));

	addOption(ToggleOption("Kick From Vehicle Loop")
		.addToggle(vars.bKickFromVehicleLoop).addTranslation());

	addOption(ButtonOption("Stalker Killer Jet")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::JetAttackPlayer(player);
			});
		}
	));

	addOption(ToggleOption("Angry Vehicles")
		.addToggle(vars.bAngryVehicles).addTranslation());

	addOption(ButtonOption("Infinite Black Screen")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveMenuVars::GiveInfiniteBlackScreen(player);
			});
		}
	));

	addOption(ToggleOption("Spam Spectate Message")
		.addToggle(vars.bSpectateMessageSpam).addTranslation());

	addOption(ToggleOption("Annoying Sound Spam")
		.addToggle(vars.bAnnoyingSoundSpam).addTranslation());

	addOption(ToggleOption("Disco Time")
		.addToggle(vars.bDiscoTime)
		.addTooltip("Disable this before leaving the session or you risk crashing!").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Disco Delay")
		.addNumber(vars.iDiscoDelay, "%dms", 1).addMin(25).addMax(10000)
		.addTooltip("Disable this before leaving the session or you risk crashing!").addTranslation());

	addOption(ToggleOption("24/7 NightTime")
		.addToggle(vars.bAlwaysNighttime)
		.addTooltip("Disable this before leaving the session or you risk crashing!").addTranslation());

	addOption(ToggleOption("24/7 Daytime")
		.addToggle(vars.bAlwaysDaytime)
		.addTooltip("Disable this before leaving the session or you risk crashing!").addTranslation());

	addOption(ToggleOption("The Old Switcheroo")
		.addToggle(vars.bTheOldSwitcharoo)
		.addTooltip("Disable this before leaving the session or you risk crashing!").addTranslation());
}

/*Update once when submenu is opened*/
void AllNetworkPlayersAbusiveMenu::UpdateOnce() {} //NetworkPlayerAbusiveMenuVars

/*Update while submenu is active*/
void AllNetworkPlayersAbusiveMenu::Update() {}

/*Background update*/
void AllNetworkPlayersAbusiveMenu::FeatureUpdate() {
	pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
		if (vars.bExplode) 
			NetworkPlayerAbusiveMenuVars::ExplodePlayer(player);

		if (vars.bForceField)
			NetworkPlayerAbusiveMenuVars::ForcefieldPlayer(player);

		if (vars.bIncapacitate)
			NetworkPlayerAbusiveMenuVars::FreezePlayerInPlace(player);

		if (vars.bAlwaysWanted)
			NetworkPlayerAbusiveMenuVars::GivePlayerStars(player, 5);

		if (vars.bShakeCamera) 
			NetworkPlayerAbusiveMenuVars::ShakePlayerCamera(player);

		if (vars.bTrollMoneyBags)
			NetworkPlayerAbusiveMenuVars::TrollMoneyBags(player);

		if (vars.bGlitchPlayersLoop) 
			NetworkPlayerAbusiveMenuVars::GlitchPlayerLoop(player);

		if (vars.bKickFromVehicleLoop)
			NetworkPlayerAbusiveMenuVars::KickPlayerFromVehicle(player);

		if (vars.bAngryVehicles) 
			NetworkPlayerAbusiveMenuVars::AngryVehicles(player);

		if (vars.bSpectateMessageSpam) 
			NetworkPlayerAbusiveMenuVars::SpectateNotification(player);

		if (vars.bAnnoyingSoundSpam)
			NetworkPlayerAbusiveMenuVars::AnnoyingSoundSpam(player);

		if (vars.bExplodeTalking) {
			if (NetworkIsPlayerTalking(player.Id))
				NetworkPlayerAbusiveMenuVars::ExplodePlayer(player);
		}

	});

	if (vars.bDiscoTime) {
		static int timer;
		static bool state;
		if (NetworkIsSessionActive() && NetworkIsPlayerActive(GetLocalPlayer().Id)) {
			pUtils.RunTimedFunction(&timer, vars.iDiscoDelay, [&] {
				NetworkOverrideClockTime((state ? 12 : 23), 0, 0);
				pNatives.SyncLobbyTimeWithMyTime();
				state = !state;
			});
		}
	}

	if (vars.bAlwaysNighttime) {
		static int timer;
		if (NetworkIsSessionActive() && NetworkIsPlayerActive(GetLocalPlayer().Id)) {
			pUtils.RunTimedFunction(&timer, 10000, [&] {
				NetworkOverrideClockTime(23, 0, 0);
				pNatives.SyncLobbyTimeWithMyTime();
			});
		}
	}

	if (vars.bAlwaysDaytime) {
		static int timer;
		if (NetworkIsSessionActive() && NetworkIsPlayerActive(GetLocalPlayer().Id)) {
			pUtils.RunTimedFunction(&timer, 10000, [&] {
				NetworkOverrideClockTime(12, 0, 0);
				pNatives.SyncLobbyTimeWithMyTime();
			});
		}
	}

	if (vars.bTheOldSwitcharoo) {
		static int timer, time;
		static bool state;
		if (NetworkIsSessionActive() && NetworkIsPlayerActive(GetLocalPlayer().Id)) {
			pUtils.RunTimedFunction(&timer, 200, [&] {
				NetworkOverrideClockTime(time, 0, 0);
				pNatives.SyncLobbyTimeWithMyTime();
				state ? time-- : time++;
				if (time == 23 || time == 0) {
					state = !state;
				}
			});
		}
	}

}

/*Singleton*/
AllNetworkPlayersAbusiveMenu* _instance;
AllNetworkPlayersAbusiveMenu* AllNetworkPlayersAbusiveMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AllNetworkPlayersAbusiveMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
AllNetworkPlayersAbusiveMenu::~AllNetworkPlayersAbusiveMenu() { delete _instance; }