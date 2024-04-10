#pragma once

enum OceanManagerTypes {
	RemoveOcean,
	BiggerWaves,
	ClearWaterEffect
};

struct sWaterTune {
	int WaterColor;
	float RippleScale;
	float OceanFoamScale;
	float SpecularFalloff;
	float FogPierceIntensity;
	float RefractionBlend;
	float RefractionExponent;
	float WaterCycleDepth;
	float WaterCycleFade;
	float WaterLightningDepth;
	float WaterLightningFade;
	float DeepWaterModDepth;
	float DeepWaterModFade;
	float GodRaysLerpStart;
	float GodRaysLerpEnd;
	float DisturbFoamScale;
	float FogMin[2];
	float FogMax[2];
};

class OceanManager {
private:

	struct QuadData {
		DWORD64 dwQuadPool;
		short sCount;
	};

	struct WaterData {
		QuadData* oceanQuads;
	}pWaterQuads;

public:
	bool Init(uint64_t address);
	void Run(OceanManagerTypes command, bool toggle);

	sWaterTune* pWaterTune;

};

extern OceanManager pOceanManager;
