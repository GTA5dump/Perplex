#include "stdafx.h"

OceanManager pOceanManager;

bool OceanManager::Init(uint64_t address) {
	pOceanManager.pWaterQuads.oceanQuads = reinterpret_cast<QuadData*>(GetAddressFromInstruction(address));
	return true;
}

void OceanManager::Run(OceanManagerTypes command, bool toggle) {
	for (int i = 0; i < pOceanManager.pWaterQuads.oceanQuads->sCount; i++) {
		DWORD64 quad_struct = pOceanManager.pWaterQuads.oceanQuads->dwQuadPool + (i * 0x1C);
		switch(command) {
		case RemoveOcean: 
			*reinterpret_cast<float*>(quad_struct + 0x14) = (toggle ? -10000.0f : 0.0f);
			break;
		case BiggerWaves: {
			auto WaveAmplitude = *reinterpret_cast<short*>(quad_struct + 0x8);
			toggle ? WaveAmplitude += 2000 : WaveAmplitude -= 2000;
			*reinterpret_cast<short*>(quad_struct + 0x8) = WaveAmplitude;
			}break;
		case ClearWaterEffect:
			*reinterpret_cast<int*>(quad_struct + 0x8) = (toggle ? 0x01010101 : 0x1A1A1A1A);
			break;
		default:
			//invalid
			break;
		}
	}
}
