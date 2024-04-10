#pragma once

class infoRender {
private:
	vector<pair<string, int>>Messages;
public:
	bool bOutline;

	void Render();
	void Update(int id, string str);
	void Unregister(int id);
	void Toggle(int& id);
	int Register();
};
extern infoRender pInfoRender;