#include "stdafx.h"
#include "menu/submenus/main/spawn/manager/objectmanger/editobjectMenu.h"

InfoBox pInfoBox;

#pragma region Info Box Functions 
namespace Function {

	const char* GetHeading(SPlayer& player) {
		int heading = GetEntityHeading(player.Ped);
		if (heading >= 0 && heading <= 90) {
			return pUtils.cprintf("N (%i)", heading);
		} else if (heading >= 90 && heading <= 180) {
			return pUtils.cprintf("E (%i)", heading);
		} else if (heading >= 180 && heading <= 270) {
			return pUtils.cprintf("S (%i)", heading);
		} else if (heading >= 270 && heading <= 360) {
			return pUtils.cprintf("W (%i)", heading);
		} else
			return "~c~Unknown";
	}

	const char* GetAmmo(SPlayer& player) {
		int clip_ammo;
		if (player.WeaponEntity != NULL) {
			GetAmmoInClip(player.Ped, player.WeaponHash, &clip_ammo);
			return pUtils.cprintf("%d/%d", GetAmmoInPedWeapon(player.Ped, player.WeaponHash), clip_ammo);
		}
		return "~c~None";
	}

	const char* GetRole(SPlayer& player) {
		if (player.bIsHost)
			return "Host";
		if (player.Id == GetLocalPlayer().Id)
			return "Me";
		else if (player.bIsFriend)
			return "Friend";
		else
			return "Client";
	}

	bool IsMoving(SPlayer& player) {
		return (GetEntitySpeed(player.Entity) > 0);
	}

	const char* GetWalletValue(SPlayer& player) {
		const auto cash = Global(Globals::PLAYER_BASE).At(player.Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_WALLET).As<uint64_t>();
		return pUtils.cprintf("$%d", cash);
	}

	const char* GetBankValue(SPlayer& player) {
		const auto wallet = Global(Globals::PLAYER_BASE).At(player.Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_WALLET).As<uint64_t>();
		const auto total = Global(Globals::PLAYER_BASE).At(player.Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_TOTAL).As<uint64_t>();
		return pUtils.cprintf("$%d", (total - wallet));
	}

	const char* GetLevelValue(SPlayer& player) {
		const auto level = Global(Globals::PLAYER_BASE).At(player.Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_LEVEL).As<uint64_t>();
		return pUtils.cprintf("%d", level);
	}

	const char* GetKDValue(SPlayer& player) {
		const auto kd = Global(Globals::PLAYER_BASE).At(player.Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_KD).As<float>();
		return pUtils.cprintf("%.2f", kd);
	}

	const char* GetKillsValue(SPlayer& player) {
		const auto kills = Global(Globals::PLAYER_BASE).At(player.Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_KILLS).As<uint64_t>();
		return pUtils.cprintf("%d", kills);
	}

	const char* GetDeathsValue(SPlayer& player) {
		const auto deaths = Global(Globals::PLAYER_BASE).At(player.Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_DEATHS).As<uint64_t>();
		return pUtils.cprintf("%d", deaths);
	}

	const char* GetStreet(SPlayer& player) {
		Hash StreetName, CrossingRoad;
		GetStreetNameAtCoord(player.Coords.x, player.Coords.y, player.Coords.z, &StreetName, &CrossingRoad);
		return GetStreetNameFromHashKey(StreetName);
	}

	bool DoesPlayerHaveModdedModel(SPlayer& player) {
		return (GetEntityModel(player.Ped) != GetHashKey("MP_F_Freemode_01") && GetEntityModel(player.Ped) != GetHashKey("MP_M_Freemode_01"));
	}

	const char* GetCurrentWeapon(SPlayer& player) {
		switch (player.WeaponHash) {
			case -1569615261:
				return "~c~Unarmed";
			case -1716189206:
				return "Knife";
			case 1737195953:
				return "Nightstick";
			case 1317494643:
				return "Hammer";
			case -1786099057:
				return "Bat";
			case 1141786504:
				return "Golf Club";
			case -2067956739:
				return "Crow Bar";
			case 453432689:
				return "Pistol";
			case 1593441988:
				return "Combat Pistol";
			case 584646201:
				return "AP Pistol";
			case -1716589765:
				return "Pistol 50";
			case 324215364:
				return "Micro SMG";
			case 736523883:
				return "SMG";
			case -270015777:
				return "Assault SMG";
			case -1074790547:
				return "Assault Rifle";
			case -2084633992:
				return "Carbine Rifle";
			case -1357824103:
				return "Advanced Rifle";
			case -1660422300:
				return "MG";
			case 2144741730:
				return "Combat MG";
			case 487013001:
				return "Pump Shotgun";
			case 2017895192:
				return "Sawn-off Shotgun";
			case -494615257:
				return "Assault Shotgun";
			case -1654528753:
				return "Bullpup Shotgun";
			case 911657153:
				return "Stungun";
			case 100416529:
				return "Sniper Rifle";
			case 205991906:
				return "Heavy Sniper";
			case -1568386805:
				return "Grenade Launcher";
			case 1305664598:
				return "Grenade Launcher Smoke";
			case -1312131151:
				return "RPG";
			case 375527679:
				return "Passenger Rocket";
			case 324506233:
				return "Airstrike Rocket";
			case 1752584910:
				return "Stringer";
			case 1119849093:
				return "Minigun";
			case -1813897027:
				return "Grenade";
			case 741814745:
				return "Sticky Bomb";
			case -37975472:
				return "Smoke Grenade";
			case -1600701090:
				return "BZ Gas";
			case 615608432:
				return "Molotov";
			case 101631238:
				return "Fire Extinguisher";
			case 883325847:
				return "Petrol Can";
			case -38085395:
				return "Digi Scanner";
			case -2000187721:
				return "Briefcase";
			case 28811031:
				return "Briefcase 2";
			case 600439132:
				return "Ball";
			case 1233104067:
				return "Flare";
			case -1090665087:
				return "Vehicle Rocket";
			default:
				return "~c~Unknown Weapon";
		}
	}

}

#pragma endregion

void ErrorGeoLocation(SPlayer* player, const char* error, const char* msg = "Unavailable") {
	player->isp = msg;
	player->city = msg;
	player->country = msg;
	player->countryCode = "N/A";
	player->timezone = msg;
	player->regionName = msg;
	LOG_PUBLIC(error);
}

void InfoBox::GEOUpdate() {
	static string response;
	bool secondtry = false;
top:
	if (!GeoLocationLookups.empty()) {
		response.clear();
		auto player = GeoLocationLookups.front();
		try { 
			response = pNetwork.GeoLookup(player->ip);
			if (!pUtils.DoesStingHaveInvalidChars(response)) {
				if (pUtils.IsValidJSONResponse(response)) {
					player->isp.clear();
					player->city.clear();
					player->country.clear();
					player->countryCode.clear();


					json object = json::parse(response);

					if (!object.empty()) {
						if (!object["status"].is_null()) {
							if (object["status"].get<string>() == "success") {
								if (!object["isp"].is_null()) {
									player->isp = object["isp"].get<string>();
								}

								if (!object["city"].is_null()) {
									player->city = object["city"].get<string>();
								}

								if (!object["country"].is_null()) {
									player->country = object["country"].get<string>();
								}

								if (!object["countryCode"].is_null()) {
									player->countryCode = object["countryCode"].get<string>();
								}

								if (!object["regionName"].is_null()) {
									player->regionName = object["regionName"].get<string>();
								}

								if (!object["timezone"].is_null()) {
									player->timezone = object["timezone"].get<string>();
								}
							}
							else {
								LOG_DEV("GEO location api error 1...");
								ErrorGeoLocation(player, "GEO location api error 1...");
							}
						}
						else {
							LOG_DEV("GEO location api error 2...");
							ErrorGeoLocation(player, "GEO location api error 2...");
						}
					}
					else {
						LOG_DEV("GEO location object data is empty...");
						ErrorGeoLocation(player, "GEO location object data is empty...");
					}
				}
				else {
					if (!secondtry) {
						LOG_DEV("Failed first geo attempt, trying again...");
						secondtry = true;
						goto top;
					} else {
						LOG_DEV("Failed json validation check");
						ErrorGeoLocation(player, "Failed json validation check");
					}
				}
			} else {
				if (!secondtry) {
					LOG_DEV("Failed first geo attempt, trying again...");
					secondtry = true;
					goto top;
				} else {
					LOG_DEV("Geo response has invalid chars");
					ErrorGeoLocation(player, "Geo response has invalid chars", "Invalid");
				}
			}

			GeoLocationLookups.pop();
			} 
		catch (json::parse_error& e) {
			LOG_DEV("Known GEO exception - message: %s || id: %d || byte pos: %llu", e.what(), e.id, e.byte);
			ErrorGeoLocation(player, pUtils.cprintf("Known GEO exception - message: %s || id: %d || byte pos: %llu", e.what(), e.id, e.byte));
			GeoLocationLookups.pop();
		} catch (...) { //doing this incase the json returns bad (e.g. if the api is down or something)
			LOG_DEV("Unknwon error with geo location");
			ErrorGeoLocation(player, "Unknwon error with geo location");
			GeoLocationLookups.pop();
		}
	}
	Sleep(1000);
}

void InfoBox::DrawPlayerPicture(SPlayer& player) {
	if (player.HeadshotHandle != NULL) {
		if (IsPedheadshotValid(player.HeadshotHandle)) {
			if (IsPedheadshotReady(player.HeadshotHandle)) {
				auto str = GetPedheadshotTxdString(player.HeadshotHandle);
				if (str != nullptr) {
					pRenderer.DrawRect(0.549f + (pMenu.uiPos.x + plusX), 0.124f + pMenu.uiPos.y, 0.0771f, 0.136f, { pMenu.HeaderColor.r, pMenu.HeaderColor.g, pMenu.HeaderColor.b, 255 });
					pRenderer.DrawSprite(Texture(str, str), 0.549f + (pMenu.uiPos.x + plusX), 0.124f + pMenu.uiPos.y, 0.0761f, 0.133f, 0.0f, { 255, 255, 255 });
					return;
				}
			}
		}
	}
	pRenderer.DrawRect(0.549f + (pMenu.uiPos.x + plusX), 0.124f + pMenu.uiPos.y, 0.0771f, 0.136f, { pMenu.HeaderColor.r, pMenu.HeaderColor.g, pMenu.HeaderColor.b, 255 });
	pRenderer.DrawSprite(Texture("assassinations", "targetquestion"), 0.549f + (pMenu.uiPos.x + plusX), 0.124f + pMenu.uiPos.y, 0.0761f, 0.133f, 0.0f, { 255, 255, 255 });
}

char infoboxBuffer[50];
void InfoBox::AddInfoBoxItem(string name, string value, InfoBoxTextTypes type, bool requirement) {
	if (requirement) {
		switch (type) {
		case Profile:
			if (pNextRenderInfoboxIDS->ProfileItemIndex == 4) return;
			pUtils.VABuffer(infoboxBuffer, 50, "%s: %s", name.c_str(), value.c_str());
			pRenderer.DrawString(infoboxBuffer, 0.593f + (pMenu.uiPos.x + plusX), 0.073f + (0.031f * pNextRenderInfoboxIDS->ProfileItemIndex) + pMenu.uiPos.y, 0, 0.35f, pMenu.MenuTextColor, false, -1);
			//pRenderer.DrawString(value, 0.229f + pMenu.uiPos.x, 0.073f + (0.031f * ProfileItemIndex) + pMenu.uiPos.y, 0, pMenu.SpazScale.x, { 255, 255, 255 }, false, 2, 0.229f);
			pNextRenderInfoboxIDS->ProfileItemIndex++;
			break;

		case Left:
			pUtils.VABuffer(infoboxBuffer, 50, "%s:", name.c_str());
			pRenderer.DrawString(infoboxBuffer, 0.510f + (pMenu.uiPos.x + plusX), (!pNextRenderInfoboxIDS->ProfileItemIndex ? 0.073f : 0.207f) + (0.031f * pNextRenderInfoboxIDS->LeftItemIndex) + pMenu.uiPos.y, 0, 0.35f, pMenu.MenuTextColor, false, -1);
			pRenderer.DrawString(value.c_str(), 0.343f + (pMenu.uiPos.x + plusX), (!pNextRenderInfoboxIDS->ProfileItemIndex ? 0.073f : 0.207f) + (0.031f * pNextRenderInfoboxIDS->LeftItemIndex) + pMenu.uiPos.y, 0, 0.35f, pMenu.MenuTextColor, false, 2, 0.343f - plusX);
			pNextRenderInfoboxIDS->LeftItemIndex++;
			break;

		case Right:
			pUtils.VABuffer(infoboxBuffer, 50, "%s:", name.c_str());
			pRenderer.DrawString(infoboxBuffer, 0.624f + (pMenu.uiPos.x + plusX), (!pNextRenderInfoboxIDS->ProfileItemIndex ? 0.073f : 0.207f) + (0.031f * pNextRenderInfoboxIDS->RightItemIndex) + pMenu.uiPos.y, 0, 0.35f, pMenu.MenuTextColor, false, -1);
			pRenderer.DrawString(value.c_str(), 0.229f + (pMenu.uiPos.x + plusX), (!pNextRenderInfoboxIDS->ProfileItemIndex ? 0.073f : 0.207f) + (0.031f * pNextRenderInfoboxIDS->RightItemIndex) + pMenu.uiPos.y, 0, 0.35f, pMenu.MenuTextColor, false, 2, 0.229f - plusX);
			pNextRenderInfoboxIDS->RightItemIndex++;
			break;

		case Across:
			int index = (pNextRenderInfoboxIDS->LeftItemIndex > pNextRenderInfoboxIDS->RightItemIndex ? pNextRenderInfoboxIDS->LeftItemIndex : pNextRenderInfoboxIDS->RightItemIndex);
			pUtils.VABuffer(infoboxBuffer, 50, "%s:", name.c_str());
			pRenderer.DrawString(infoboxBuffer, 0.510f + (pMenu.uiPos.x + plusX), (!pNextRenderInfoboxIDS->ProfileItemIndex ? 0.073f : 0.207f) + (0.031f * index) + pMenu.uiPos.y, 0, 0.35f, pMenu.MenuTextColor, false, -1);
			pRenderer.DrawString(value.c_str(), 0.229f + (pMenu.uiPos.x + plusX), (!pNextRenderInfoboxIDS->ProfileItemIndex ? 0.073f : 0.207f) + (0.031f * pNextRenderInfoboxIDS->RightItemIndex) + pMenu.uiPos.y, 0, 0.35f, pMenu.MenuTextColor, false, 2, 0.229f - plusX);
			pNextRenderInfoboxIDS->LeftItemIndex++;
			pNextRenderInfoboxIDS->RightItemIndex++;
			break;
		}
	}
}

void InfoBox::RenderPlayerInfo(SPlayer& player) {
	static int index;

	plusX = (!pMenu.IsOpen() ? 0.23f : 0.0f);

	if (!pMenu.bPlayerlistInfoBox) return;

	if (pMenu.bDisplayPlayerInfoBox && NetworkIsSessionActive() && DoesEntityExist(player.Ped) && player.bConnected) {
		pRenderer.DrawRect(0.62f + (pMenu.uiPos.x + plusX), 0.145f + (0.016f * index) + pMenu.uiPos.y, 0.23f, 0.183f + (0.033 * index), pMenu.BackgroundColor); //background
		pRenderer.DrawRect(0.7345f + (pMenu.uiPos.x + plusX), 0.145f + (0.016f * index) + pMenu.uiPos.y, 0.001f, 0.183f + (0.033 * index), pMenu.HeaderColor); //sidebar

		DrawPlayerPicture(player);

		pNextRenderInfoboxIDS = &PlayerInfoboxItemPos;

		//Profile
		AddInfoBoxItem("Name", player.Name, Profile);

		AddInfoBoxItem("Rockstar ID", pUtils.cprintf("%lld", player.iRockstarID), Profile);

		if (GetPlayerWantedLevel(player.Id) > 0)
			AddInfoBoxItem("Wanted Level", pUtils.cprintf("%d", GetPlayerWantedLevel(player.Id)), Profile);
		else
			AddInfoBoxItem("Wanted Status", "~c~None", Profile);

		AddInfoBoxItem("Role", Function::GetRole(player), Profile);

		//Left
		AddInfoBoxItem("Wallet", Function::GetWalletValue(player), Left);
		AddInfoBoxItem("Bank", Function::GetBankValue(player), Left);
		AddInfoBoxItem("Level", Function::GetLevelValue(player), Left);
		AddInfoBoxItem("Ammo", Function::GetAmmo(player), Left);
		AddInfoBoxItem("Health", pUtils.cprintf("%d%%", (GetEntityHealth(player.Ped) ? (GetEntityHealth(player.Ped) * 100 / GetEntityMaxHealth(player.Ped)) : 0)), Left);
		AddInfoBoxItem("Armour", pUtils.cprintf("%d%%", GetPedArmour(player.Ped)), Left);
		AddInfoBoxItem("Inside Vehicle", player.bIsInVehicle ? "Yes" : "No", Left);

		//Right
		AddInfoBoxItem("X", pUtils.cprintf("%.2f", player.Coords.x), Right);
		AddInfoBoxItem("Y", pUtils.cprintf("%.2f", player.Coords.y), Right);
		AddInfoBoxItem("Z", pUtils.cprintf("%.2f", player.Coords.z), Right);
		AddInfoBoxItem("Speed", pUtils.cprintf("%d MPH", static_cast<int>(GetEntitySpeed(player.Entity) * 2.236936f)), Right);
		AddInfoBoxItem("Heading", Function::GetHeading(player), Right);
		AddInfoBoxItem("Distance", pUtils.cprintf("%.2fm", pUtils.GetDistanceBetweenCoords(GetLocalPlayer().Coords, player.Coords)), Right);
		AddInfoBoxItem("Moving", Function::IsMoving(player) ? "Yes" : "No", Right);
		//IsMoving

		//Across
		AddInfoBoxItem("Street", Function::GetStreet(player), Across);
		AddInfoBoxItem("Vehicle", _GetLabelText(GetDisplayNameFromVehicleModel(GetEntityModel(player.Vehicle_))), Across, player.bIsInVehicle);
		AddInfoBoxItem("Weapon", Function::GetCurrentWeapon(player), Across);
		AddInfoBoxItem("Modder Warning", "Player Is Modding", Across, (player.bIsCheater || player.bPerplexUser));
		AddInfoBoxItem("Perplex Status", "Player Is A Perplex User", Across, player.bPerplexUser);
		AddInfoBoxItem("Notice", "~r~Player Is Being Kicked", Across, player.bKickInProgress);

		//Apartment data
		//1589747 = playerbasestruct // 790 = playerbasestruct size //index base = 211

		//Left
		AddInfoBoxItem("Kills", Function::GetKillsValue(player), Left);
		AddInfoBoxItem("Deaths", Function::GetDeathsValue(player), Left);
		AddInfoBoxItem("K/D", Function::GetKDValue(player), Left);
		AddInfoBoxItem("Modded Model", Function::DoesPlayerHaveModdedModel(player) ? "Yes" : "No", Left);

		//Right

		if (player.Id != GetLocalPlayer().Id) {
			AddInfoBoxItem("IP", (!player.bPerplexUser ? player.ip : "Hidden"), Right);
			AddInfoBoxItem("Port", (!player.bPerplexUser ? player.port : "Hidden"), Right);
			AddInfoBoxItem("Country", (!player.bPerplexUser ? player.country : "Hidden"), Right, pMenu.bShowLocationsInInfobox);
			AddInfoBoxItem("Code", (!player.bPerplexUser ? player.countryCode : "Hidden"), Right, pMenu.bShowLocationsInInfobox);

			//Across
			AddInfoBoxItem("Region", (!player.bPerplexUser ? player.regionName : "Hidden"), Across, pMenu.bShowLocationsInInfobox);
			AddInfoBoxItem("City", (!player.bPerplexUser ? player.city : "Hidden"), Across, pMenu.bShowLocationsInInfobox);
			AddInfoBoxItem("ISP", (!player.bPerplexUser ? player.isp : "Hidden"), Across, pMenu.bShowLocationsInInfobox);
			AddInfoBoxItem("Timezone", (!player.bPerplexUser ? player.timezone : "Hidden"), Across, pMenu.bShowLocationsInInfobox);
		}

		index = (pNextRenderInfoboxIDS->LeftItemIndex > pNextRenderInfoboxIDS->RightItemIndex ? pNextRenderInfoboxIDS->LeftItemIndex : pNextRenderInfoboxIDS->RightItemIndex) - 1;
		pNextRenderInfoboxIDS->Reset();
	}
}

void InfoBox::RenderObjectCreatorInfo(Object object) {
	static int index;

	if (DoesEntityExist(object)) { 
		const auto coords = GetEntityCoords(object, true);
		const auto rotation = GetEntityRotation(object, 2);

		Hash street, crossing;
		GetStreetNameAtCoord(coords.x, coords.y, coords.z, &street, &crossing);

		pNextRenderInfoboxIDS = &ObjectCreatorInfoboxItemPos;

		pRenderer.DrawRect(0.62f + pMenu.uiPos.x, 0.065f + (0.016f * index) + pMenu.uiPos.y, 0.23f, 0.018f + (0.033 * index), pMenu.BackgroundColor); //background
		pRenderer.DrawRect(0.7345f + pMenu.uiPos.x, 0.065f + (0.016f * index) + pMenu.uiPos.y, 0.001f, 0.018f + (0.033 * index), pMenu.HeaderColor); //sidebar

		//left
		AddInfoBoxItem("X", pUtils.cprintf("%.3f", coords.x), Left);
		AddInfoBoxItem("Y", pUtils.cprintf("%.3f", coords.y), Left);
		AddInfoBoxItem("Z", pUtils.cprintf("%.3f", coords.z), Left);

		//right
		AddInfoBoxItem("Pitch", pUtils.cprintf("%.3f", rotation.x), Right);
		AddInfoBoxItem("Roll", pUtils.cprintf("%.3f", rotation.y), Right);
		AddInfoBoxItem("Yaw", pUtils.cprintf("%.3f", rotation.z), Right);

		//left
		AddInfoBoxItem("Distance", pUtils.cprintf("%.3f", ObjectSpawnMenuVars::vars.fObjectDistance), Left);

		//right
		AddInfoBoxItem("Hash", pUtils.cprintf("0x%x", GetEntityModel(object)), Right);

		//across
		AddInfoBoxItem("Distance From Ground", pUtils.cprintf("%.3fm", GetEntityHeightAboveGround(object)), Across);
		AddInfoBoxItem("Street", GetStreetNameFromHashKey(street), Across);

		index = (pNextRenderInfoboxIDS->LeftItemIndex > pNextRenderInfoboxIDS->RightItemIndex ? pNextRenderInfoboxIDS->LeftItemIndex : pNextRenderInfoboxIDS->RightItemIndex);
		pNextRenderInfoboxIDS->Reset();
	}
}

void InfoBox::RednerObjectManagerInfo(ObjectSpawnMenuVars::sObjectData object) {
	static int index;
	if (DoesEntityExist(object.handle)) {
		const auto coords = GetEntityCoords(object.handle, true);
		const auto rotation = GetEntityRotation(object.handle, 2);

		int min, hour, sec;
		pUtils.WorkOutTimeSinceEntitySpawn(object.iSpawnTime, &hour, &min, &sec);

		Hash street, crossing;
		GetStreetNameAtCoord(coords.x, coords.y, coords.z, &street, &crossing);

		pNextRenderInfoboxIDS = &ObjectManagerInfoboxItemPos;

		pRenderer.DrawRect(0.62f + pMenu.uiPos.x, 0.065f + (0.016f * index) + pMenu.uiPos.y, 0.23f, 0.018f + (0.033 * index), pMenu.BackgroundColor); //background
		pRenderer.DrawRect(0.7345f + pMenu.uiPos.x, 0.065f + (0.016f * index) + pMenu.uiPos.y, 0.001f, 0.018f + (0.033 * index), pMenu.HeaderColor); //sidebar

		//across
		AddInfoBoxItem("Name", object.pName, Across);

		//left
		AddInfoBoxItem("X", pUtils.cprintf("%.3f", coords.x), Left);
		AddInfoBoxItem("Y", pUtils.cprintf("%.3f", coords.y), Left);
		AddInfoBoxItem("Z", pUtils.cprintf("%.3f", coords.z), Left);

		//right
		AddInfoBoxItem("Pitch", pUtils.cprintf("%.3f", rotation.x), Right);
		AddInfoBoxItem("Roll", pUtils.cprintf("%.3f", rotation.y), Right);
		AddInfoBoxItem("Yaw", pUtils.cprintf("%.3f", rotation.z), Right);

		//right
		AddInfoBoxItem("Hash", pUtils.cprintf("0x%x", object.hModel), Right);

		//left
		AddInfoBoxItem("Distance", pUtils.cprintf("%.3fm", pUtils.GetDistanceBetweenCoords(coords, GetLocalPlayer().Coords)), Left);

		//across
		AddInfoBoxItem("Distance From Ground", pUtils.cprintf("%.3fm", GetEntityHeightAboveGround(object.handle)), Across);
		AddInfoBoxItem("Street", GetStreetNameFromHashKey(street), Across);
		AddInfoBoxItem("Time Since Spawn", pUtils.cprintf("%02dh:%02dm:%02ds", hour, min, sec), Across);

		index = (pNextRenderInfoboxIDS->LeftItemIndex > pNextRenderInfoboxIDS->RightItemIndex ? pNextRenderInfoboxIDS->LeftItemIndex : pNextRenderInfoboxIDS->RightItemIndex);
		pNextRenderInfoboxIDS->Reset();
	}
}