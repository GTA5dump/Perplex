#pragma once

class Global {
private:
	void* _handle;

public:
	Global(int index) : _handle(&pBackend.GetGlobalPtr()[index >> 18 & 0x3F][index & 0x3FFFF]) {}
	Global(void* p) : _handle(p) {}
	Global(const Global& copy) : _handle(copy._handle) {}

	Global At(int index) const {
		return Global(reinterpret_cast<void**>(this->_handle) + (index));
	}

	Global At(int index, int size) const {
		return this->At(1 + (index * size));
	}

	template <typename T>
	T* Get() {
		return reinterpret_cast<T*>(this->_handle);
	}

	template <typename T>
	T& As() {
		return *this->Get<T>();
	}
};

namespace SCRIPTEVENTS {
	static const long long ECLIPSETELEPORT = -125347541; //1.47 - 1365267338   //1.46 = 1000837481				//1.44 = -328868154;
	static const long long INCREASERP = -121406262;			//1.46 = -181444979			//1.44 = -1306381802
	static const long long KICKFROMVEHICLE = -1089379066;	//1.47 = 1796063150  //1.46 = 325218053			//1.44 = 941101193
	static const long long FORCEINTOMISSION = -348418057; //1.47 = -2145536660;	//1.46 = -15432926				//1.44 = -1750269456
	static const long long NOTIFICATION = 564131320; //1.47 = 111286607;	// 1.46 = 713068249					//1.44 = -471892217
	static const long long NOTIFICATION2 = -154247493; //1.47 = -270262485;	//1.46 = 1009196241				//1.44 = -1955172318
	static const long long TRANSACTIONERROR = 189238289;

	static const long long NONHOSTKICK1 = -1246838892; //1.47 = 423635655;   //1.46 = -120668417;		//1.44 = 1886569883
	static const long long NONHOSTKICK2 = 930233414; //1.47 = 400031869	//1.46 = 1222825035					//1.44 = -1175363363
	static const long long NONHOSTKICK3 = 297770348; //1.47 = -510378036;	//1.46 = 769347061					//1.44 = 1394869423
	static const long long NONHOSTKICK4 = 498709856; //1.47 = -815817885;	//1.46 = 999090520					//1.44 = 2101106911
	static const long long NONHOSTKICK5 = 1432301416; //1.47 = -1264063129 //-1264063129;	//1.46 = 1642479322					//1.44 = 221861863
	static const long long NONHOSTKICK6 = -452918768; //1.47 = 1953937033;    //1.46 = 964496014
	static const long long NONHOSTKICK7 = -841066582; //1.47 = -1802878900;     //1.46 = 558809002
	static const long long NONHOSTKICK8 = 1152017566;//1.47 = 1209128713;
	static const long long NONHOSTKICK9 = -2120750352; //updated
	static const long long NONHOSTKICK10 = -423635655; //update later
	static const long long NONHOSTKICK11 = -1010395481; //updated
	static const long long NONHOSTKICK12 = -1882271245;  //updated
	static const long long NONHOSTKICK13 = -941739545;


	static const long long KICKTOSP1 = 1667907776; //1.47 = -1424895288; //1.46 = 994306218		//1.44 = 1119445978
	static const long long KICKTOSP2 = 774421744; //1.47 =  1314698923;	//1.46 = -928998106					//1.44 = 494384757,
	static const long long KICKTOSP3 = 1404046700; //1.47 = -158670784;	//1.46 = 1153942884						//1.44 = 1551051749

	static const long long CEOKICK = -701823896; //1.47 = -606032195;	//1.46 = -1190833098	 					//1.44 = 585981075
	static const long long CEOBAN = -327286343; //1.47 = -326132866;	   //1.46 = 360381720						//1.44 = 1318668309
	static const long long INVITE = 552065831; //1.47 = 715645088;	   //1.46 = -175474624						//1.44 = 729971264
	static const long long GOTR = -615431083; //1.47 = 1848739240;	  //1.46 = 1344161996							//1.44 = 469048255
	static const long long GNEVERWANTED = -163616977; //1.47 = 685727305;	//1.46 = 1475266103					//1.44 = 1511476871
	static const long long GCOPSTURNBLINDEYE = -1961284186; //1.47 = -1635856102;	//1.46 = 1555129594			//1.44 = 1603563014

	static const long long SPECTATINGMESSAGE = -38669034; //1.47 = 446273009;	//1.46 = 436170208				//1.44 = 1780315658
	static const long long FACECAMERAFORWARD = -42615386;	//1.46 = 566035618				//1.44 = -319074860
	static const long long FACECAMERAFORWARD2 = -1432407380; /*not updated*/				//1.44 = 1377126813
};

namespace Globals {
	static const int LEVEL = 290594; //1.47 = 289559;	//1.46 = 287850			//1.44 = 286291		//1.43 = 285062		//1.42 = 284737		
	static const int MPINSP = 4266905;				//1.44 = 4266042	//1.43 = 4265719;
	static const int PLAYER_BASE = 1590446; //1.47 = 1589819;		//1.46 = 1589747    	//1.44 = 1589291	//1.43 = 1595693	//1.42 = 1595681
	static const int PLAYER_PADDING = 871; //1.47 = 818;		//1.46 = 790  	//1.44 = 770		//1.43 = 680		//1.42 = 678
	static const int PLAYER_OFFSET = 211;
	static const int PLAYER_OFFSET_WALLET = 3;
	static const int PLAYER_OFFSET_TOTAL = 56; //bank money
	static const int PLAYER_OFFSET_XP = 5;
	static const int PLAYER_OFFSET_LEVEL = 6;
	static const int PLAYER_OFFSET_KD = 26;
	static const int PLAYER_OFFSET_KILLS = 28;
	static const int PLAYER_OFFSET_DEATHS = 29;
	static const int OTR_BASE = 2424073; //1.47 = 2424047;	//1.46 = 2423801		//1.44 = 2423644	//1.43 = 2422736	//1.42 = 2422736
	static const int OTR_PADDING = 421; //1.47 = 416;		//1.46 = 413		//1.44 = 406		//1.43 = 420
	static const int OTR_OFFSET = 200;				//1.44 = 196
	static const int BLIND_EYE_OFFSET = 4542;
	static const int BACKUP_HELI_OFFSET = 4380;
	static const int AMMO_DROP_OFFSET = 824;
	static const int OTR_PLAYERS_OFFSET = 222;		//1.44 = 218		//1.43 = 199
	static const int EFFECT_TIME_BASE = 2437549; //1.47 = 2437364; //1.46 = 2437022	//1.44 = 2436641
	static const int TIME_BASE = 2531497; //1.47 = 2528542;		//1.46 = 2524719	//1.44 = 2519572	//1.43 = 2436181	//1.42 = 2436169
	static const int TIME_OFFSET = 70;
	static const int NOIDLEKICK = 1368245;			//1.44 = 1363073	//1.42 = 1357213
	static const int TESTOSTERONE_OFFSET = 3880;   //1.46 = 3876	//1.44 = 3875

	//xmad 1.49 = 262145.f_4723
	static const int SNOW_BASE = 262145; //1.46 = 262145
	static const int SNOW_OFFSET = 4723;

	/*Interaction menu instructional queue*/
	static const int IMIQUEUE_BASE = 17367;			//1.44 = 17345
	static const int IMIQUEUE_OFFSET = 4767;		//1.44 = 4639
	static const int PHONE_BASE = 3889;				//1.44 = 14493
	static const int PHONE_BOOL1 = 14681;			//1.44 = 14659
	static const int PHONE_POSSET = 14441;			//1.44 = 14421
	static const int PHONE_POSGET = 14458;			//1.44 = 14438
	static const int PHONE_BITSET1 = 2384;			//1.44 = 2364
	static const int PHONE_BITSET2 = 2383;			//1.44 = 2363

	static const int REMOTE_BASE = 1626536;	 //1.46 = 1625435		//1.44 = 1624079
	static const int REMOTE_SIZE = 603;		//1.46 = 560		//1.44 = 558
	static const int REMOTE_OFFSET = 529;	//1.46 = 491		//1.44 = 491

	//OLD
	//static int TIME_PLAYERS_OFFSET = 71;	//1.43 = 71
	//static int stealth = 4262669; //1.43 = 4262346
};
