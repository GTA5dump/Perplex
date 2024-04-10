#include "stdafx.h"
#include "../submenus/main/networking/playerList/playerListMenu.h"

PlayerManager pPlayerManager;

bool IsFriend(int player) {
	int handle[76];
	NetworkHandleFromPlayer(player, &handle[0], 13);
	if (NetworkIsHandleValid(&handle[0], 13))
		if (NetworkIsFriend(&handle[0])) return true;
	return false;
}

const char* GetNameFromHandle(int player) {
	int handle[76];
	NetworkHandleFromPlayer(player, &handle[0], 13);
	if (NetworkIsHandleValid(&handle[0], 13)) {
		return NetworkGetGamertagFromHandle(&handle[0]);
	}

	return nullptr;
}

bool IsPlayerInsideApartment(SPlayer& player) {
	return (GetInteriorAtCoords(player.Coords.x, player.Coords.y, player.Coords.z) != -1);
}

bool IsGod(SPlayer& player) {
	uint64_t cPed = pPoolManager.GetEntityAddress(player.Ped);
	if (cPed != 0) {
		return (*reinterpret_cast<BYTE*>(cPed + 0x0189) != 0);
	}
	return false;
}

void SetupGeoLocation(SPlayer& player) {
	if (NetworkIsInSession()) {
		if (!player.bGeoDataSet) {
			CPlayerInfo* NetPlayer = nullptr;
			auto NetPlayerManger = ReClass::GetNetworkPlayerManager();
			if (NetPlayerManger) {
				if (NetPlayerManger->m_players != nullptr) {
					const auto PlayerData = NetPlayerManger->m_players[player.Id];
					if (PlayerData != nullptr) {
						if (PlayerData->PlayerInfo != nullptr) {
							NetPlayer = PlayerData->PlayerInfo;
						}
					}
				}
			}

			if (NetPlayer != nullptr) {
				BYTE* ExternalIP = reinterpret_cast<BYTE*>(&NetPlayer->ExternalIP);
				if (NetPlayer->ExternalIP && ExternalIP && NetPlayer->ExternalPort) {
					player.ip = pUtils.cprintf("%d.%d.%d.%d", *(ExternalIP + 3), *(ExternalIP + 2), *(ExternalIP + 1), *(ExternalIP));
					player.port = pUtils.cprintf("%d", static_cast<int>(NetPlayer->ExternalPort));

					if (pMenu.bShowLocationsInInfobox) {
						LOG_DEV("Pushing IP: %s, For GEO Lookup...", player.ip.c_str());
						pInfoBox.GeoLocationLookups.push(&player);
						player.bGeoDataSet = true;
					}
				}
			}
		}
	}
}

void SetHeadshotHandle(SPlayer& player) {
	for (int i = 0; i < 200; i++) { //player.HeadshotHandle = Global(1385294).At((player.Id + 1), 5).At(2).As<int>();
		auto id = Global(1385294).At(i, 5).At(1).As<int>();
		if (player.Id == id) {
			auto headshot_id = Global(1385294).At(i, 5).At(2).As<int>();
			player.HeadshotHandle = headshot_id;
		}
	}
	//auto id = Global(1385294).At(player.Id, 5).At(2).Get<int>();
}

void PlayerManager::Update() {
	for (int i = 0; i < 34; i++) {
		SPlayer& player = Players[i];

		player.Reset();

		player.bConnected = NetworkIsPlayerActive(i) && NetworkIsPlayerConnected(i);

		if (!player.bConnected) { // things that need to be executed when the player leaves
			if (player.bRape1 || player.bRape2) {
				DetachEntity(GetLocalPlayer().Ped, true, true);
				ClearPedTasksImmediately(GetLocalPlayer().Ped);
			}

			player = SPlayer();
			continue;
		}

		player.Id = i;
		player.Ped = GetPlayerPedScriptIndex(i);

		if (player.Ped < 0) { //fix random invalidness
			player = SPlayer();
			continue;
		}

		player.bExists = DoesEntityExist(player.Ped);

		if (!player.bExists) continue;

		player.Vehicle_ = GetVehiclePedIsIn(player.Ped, false);
		player.LastVehicle = GetVehiclePedIsIn(player.Ped, true);
		player.Name = GetPlayerName(i);
		//player.NameFromHandle = GetNameFromHandle(i);
		player.Health = GetEntityHealth(player.Ped);
		player.MaxHealth = GetEntityMaxHealth(player.Ped);
		player.bIsHost = NetworkGetHostOfScript("Freemode", -1, 0) == i;
		player.Coords = GetEntityCoords(player.Ped, false);
		player.Team = GetPlayerTeam(player.Id);
		player.bIsInInterior = IsPlayerInsideApartment(player);
		player.bIsGodmode = IsGod(player);
		player.bIsFriend = IsFriend(i);
		player.bIsInVehicle = IsPedInAnyVehicle(player.Ped, true);
		player.fHeading = GetEntityHeading(player.Ped);
		player.Entity = IsPedInAnyVehicle(player.Ped, 0) ? player.Vehicle_ : player.Ped;
		GetCurrentPedWeapon(player.Ped, &player.WeaponHash, 1);
		player.bHasWeaponInHand = (player.WeaponHash && player.WeaponHash != 2725352035);
		player.bIsTalking = NetworkIsPlayerTalking(player.Id);
		player.bIsShooting = IsPedShooting(player.Ped);
		player.bIsDead = IsPlayerDead(player.Id);

		if (GetLocalPlayer().Ped)
			player.bVisible = HasEntityClearLosToEntity(GetLocalPlayer().Ped, player.Ped, 1);

		if (player.bIsInVehicle) {
			auto _ped = GetPedInVehicleSeat(player.Vehicle_, -1, 0);
			player.bInOtherPlayersVehicle = (IsPedAPlayer(_ped) && _ped != player.Ped);
		} else {
			player.bInOtherPlayersVehicle = false;
		}

		if (!player.HeadshotHandle && player.bExists)
			SetHeadshotHandle(player);

		//DecorSetInt(GetLocalPlayer().Ped, "CokeInPossession", GetRandomIntInRange(5513, 5800));
		//auto DetectionValue = DecorGetInt(player.Ped, "CokeInPossession");
		//player.bPerplexUser = (DetectionValue >= pBackend.iMenuIdentifiers[0] && DetectionValue <= pBackend.iMenuIdentifiers[1]);

		if (player.bHasWeaponInHand)
			player.WeaponEntity = GetCurrentPedWeaponEntityIndex(player.Ped);

		if (!player.bGeoDataSet)
			SetupGeoLocation(player);

		GetScreenCoordFromWorldCoord(player.Coords.x, player.Coords.y, player.Coords.z, &player.W2S.x, &player.W2S.y);

		if (player.iRockstarID == NULL) {
			auto NetPlayerManger = ReClass::GetNetworkPlayerManager();
			if (NetPlayerManger != nullptr) {
				if (NetPlayerManger->m_players != nullptr) {
					const auto PlayerData = NetPlayerManger->m_players[player.Id];
					if (PlayerData != nullptr) {
						if (PlayerData->PlayerInfo != nullptr) {
							player.iRockstarID = PlayerData->PlayerInfo->RockstarID;
						}
					}
				}
			}
		}
	}

	pLocalPlayer = &Players[PlayerId()];
}

SPlayer& PlayerManager::GetPlayer(int index) { return Players[index]; }
SPlayer& PlayerManager::GetLocalPlayer() { return *pLocalPlayer; }

SPlayer& GetPlayer(int index) { return pPlayerManager.GetPlayer(index); }
SPlayer& GetLocalPlayer() { return pPlayerManager.GetLocalPlayer(); }
SPlayer& GetSelectedPlayer() { return GetPlayer(PlayerListMenuVars::vars.iSelectedPlayer); }

void PlayerManager::OnlinePlayerCallback(bool doMe, bool overrideExcludes, function<void(SPlayer&)> callback) {
	if (NetworkIsInSession()) {
		for (auto& p : Players) {
			if (p.bExists) {
				if (!doMe && p.Id == GetLocalPlayer().Id) continue;
				//if (!overrideExcludes/* && ExcludesMenuVars::IsExcluded(p)*/) continue;
				callback(p);
			}
		}
	}
}