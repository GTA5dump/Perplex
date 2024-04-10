#include "stdafx.h"

infoRender pInfoRender;

void infoRender::Render() {
	int index = 0;
	for (auto data : Messages) {
		if (data.second > GetGameTimer() - 800) {
			pRenderer.DrawString(data.first.c_str(), 0.010f, 0.015f + (0.025f * index), FontChaletLondon, 0.325f, { 255, 255, 255 }, bOutline);
			index++;
		}
	}
}

void infoRender::Update(int id, string str) {
	if (id < Messages.size()) {
		Messages.at(id) = { str, GetGameTimer() };
	}
}

int infoRender::Register() {
	auto output = Messages.size();
	Messages.push_back({ string(), 0 });
	return output;
}

void infoRender::Unregister(int id) {
	if (id < Messages.size()) {
		Messages.erase(Messages.begin() + id);
	}
}