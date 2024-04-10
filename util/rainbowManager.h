#pragma once

class Rainbow {
public:
	Rainbow() {
		iInc = 0;
	}


	void Run();

	void Add(Color* color);

	void Remove(Color* color);

	void Stop();

	void Start();

	bool Exists(Color* color);

	void Toggle(bool toggle);

private:
	Color m_color;
	vector<Color*> m_colors;
	vector<pair<Color, Color*>> m_defaults;
	bool bEnabled;
	int iInc;

	Color GetDefault(Color* ptr);

	void Update();
};

extern Rainbow pMainRainbowHandler;