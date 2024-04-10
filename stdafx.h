#pragma once

#pragma warning(disable: 4191)
#pragma warning(disable: 4244)
#pragma warning(disable: 4312)
#pragma warning(disable: 4309)
#pragma warning(disable: 4305)
#pragma warning(disable: 4800)
#pragma warning(disable: 4101)
#pragma warning(disable: 4477)


#define _CRT_SECURE_NO_WARNINGS
/*Windows includes*/
#include <windows.h>
#include <windowsx.h>

#include <string>
#include <xstring>

#include <tlhelp32.h>

#include <sstream>
#include <fstream>
#include <iostream>

#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <chrono>

#include <memory>
#include <Psapi.h>
#include <cctype> 

#include <timeapi.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

#include <ShlObj.h>
#include <WinBase.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>



#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
//#pragma comment(lib, "FW1FontWrapper.lib")

using namespace std;
using namespace DirectX;
//using namespace DirectX::SimpleMath;

/*Minhook*/
#include "minhook.h"

#include "util/json.h"
using namespace nlohmann;

template <typename T, int N>
constexpr int NUMOF(T(&)[N]) { return N; }

/*vmprotect*/
#include "auth/vm/include/VMProtectSDK.h"
#pragma comment(lib, "VMProtectSDK64.lib")


#define DEBUG_
#define USER_B

#ifdef DEBUG
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LOG_DEV(x, ...) { printf("[%s %s] -> "  x  "\n", "PERPLEX DEV",  __FILENAME__, __VA_ARGS__); }
#else
#define LOG_DEV
#endif

__forceinline const char* operator""_Protect(const char* string, std::size_t) {
#ifndef DEBUG
	return VMProtectDecryptStringA(string);
#else
	return string;
#endif
}

__forceinline const char* operator""_ProtectUltra(const char* string, std::size_t) {
#ifndef DEBUG
	const char* out = VMProtectDecryptStringA(string);
	VMProtectFreeString(string);
	return out;
#else
	return string;
#endif
}

/*
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "PostProcess.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"  */

//#define LOG_PUBLIC(x, ...) { printf("[PERPLEX] -> "  x  "\n", __VA_ARGS__); /*do file log here*/ }

//#include "auth/web/json.hpp"
#include "util/json.h"
using nlohmann::json;

#include "extras/vectorStructs.h"

/*Utils*/
#include "util/types.h"
#include "util/utils.h"
#include "util/threadPool.h"
#include "util/fiberManager.h"
#include "util/fiberPool.h"
#include "util/translationString.h"
#include "util/oceanManager.h"
#include "util/sha256.h"
#include "util/config.h"
#include "util/pugiconfig.hpp"
#include "util/pugixml.hpp"
#include "auth/reg.h"

/*Memory*/
#include "util/memory/memory.h"

/*Security*/
#include "security/metric.h"
#include "security/metrics/metricDebuggerPresent.h"
#include "security/metrics/metricFunctionIntegrity.h"
#include "security/metrics/metricMemoryIntegrity.h"

/*Messenger*/
#include "security/messenger/messenger.h"

/*Auth*/
#include "auth/web/winhttpclient.h"
#include "auth/packetEncryption.h"
#include "auth/network.h"
#include "auth/requests.h"

/*Natives*/
#include "natives/crossmap.h"
#include "natives/invoker.h"
#include "natives/natives.h"
#include "natives/nativeBridge.h"

/*Pools*/
#include "backend/pools/poolManager.h"
#include "backend/pools/entityPool.h"
#include "backend/pools/objectPool.h"
#include "backend/pools/pedPool.h"
#include "backend/pools/vehiclePool.h"

/*ReClass*/
#include "util/memory/reclass.h"

#include "backend/pools/drawablePool.h"

/*Backend*/
#include "backend/backendHooking.h"
#include "backend/backendMain.h"
#include "backend/backendNatives.h"
#include "backend/backendAnticheat.h"

/*backend d3d*/
//#include "backend/d3d/includes/FW1FontWrapper.h"
#include "backend/d3d/vertexd3d.h"
#include "backend/d3d/dxRenderer.h"
#include "backend/backendD3D.h"

#include "security/security.h"

/*Renderer*/
#include "menu/renderer.h"

#include "util/input/keyboard.h"
#include "util/input/input.h"

/*Menu Util*/
#include "menu/util/playerManager.h"
#include "menu/util/entityControl.h"
#include "menu/util/rainbowManager.h"
#include "menu/util/infoHandler.h"
#include "menu/util/infoBox.h"
#include "menu/util/animations.h"

/*Option*/
#include "menu/options/option.h"
#include "menu/options/buttonOption.h"
#include "menu/options/toggleOption.h"
#include "menu/options/numberOption.h"
#include "menu/options/scrollOption.h"
#include "menu/options/submenuOption.h"
#include "menu/options/breakOption.h"
#include "menu/options/radioOption.h"

/*Submenu*/
#include "menu/submenu.h"
#include "menu/submenuHandler.h"

/*Menu*/
#include "menu/globals.h"
#include "menu/menu.h"
#include "menu/util/menuFunctions.h"