#include "stdafx.h"

Rainbow pMainRainbowHandler;

void Rainbow::Run() {
	if (bEnabled) {
		switch (iInc) {
		case 0:
			m_color.r = 255;
			m_color.g = 0;
			m_color.b = 0;
			iInc++;
			break;
		case 1:
			m_color.g++;
			if (m_color.g == 255)
				iInc++;
			break;
		case 2:
			m_color.r--;
			if (m_color.r == 0)
				iInc++;
			break;
		case 3:
			m_color.b++;
			if (m_color.b == 255)
				iInc++;
			break;
		case 4:
			m_color.g--;
			if (m_color.g == 0)
				iInc++;
			break;
		case 5:
			m_color.r++;
			if (m_color.r == 255)
				iInc++;
			break;
		case 6:
			m_color.b--;
			if (m_color.b == 0)
				iInc = 0;
			break;
		}
		Update();
	}
}

void Rainbow::Add(Color* color) {
	m_defaults.push_back(make_pair(*color, color));
	m_colors.push_back(color);
}

void Rainbow::Remove(Color* color) {
	auto exists = find(m_colors.begin(), m_colors.end(), color);
	if (exists != m_colors.end()) {
		color->r = GetDefault(color).r;
		color->g = GetDefault(color).g;
		color->b = GetDefault(color).b;

		m_colors.erase(remove(m_colors.begin(), m_colors.end(), color), m_colors.end());

		for (int i = 0; i < m_defaults.size(); i++) {
			if (m_defaults.at(i).second == color) { // compare the ptrs
				m_defaults.erase(m_defaults.begin() + i);
				break;
			}
		}
	}
}

void Rainbow::Stop() {
	bEnabled = false;

	for (int i = 0; i < m_colors.size(); i++) {
		m_colors[i]->r = GetDefault(m_colors[i]).r;
		m_colors[i]->g = GetDefault(m_colors[i]).g;
		m_colors[i]->b = GetDefault(m_colors[i]).b;
	}
}

void Rainbow::Start() {
	bEnabled = true;
}

bool Rainbow::Exists(Color* color) {
	auto exists = find(m_colors.begin(), m_colors.end(), color);
	return exists != m_colors.end();
}

Color Rainbow::GetDefault(Color* ptr) {
	for (int i = 0; i < m_defaults.size(); i++) {
		if (m_defaults.at(i).second == ptr) { // compare the ptrs
			return m_defaults.at(i).first;
		}
	}

	return Color();
}

void Rainbow::Update() {
	for (int i = 0; i < m_colors.size(); i++) {
		m_colors[i]->r = m_color.r;
		m_colors[i]->g = m_color.g;
		m_colors[i]->b = m_color.b;
	}
}

void Rainbow::Toggle(bool toggle) {
	if (toggle) {
		Start();
	} else {
		Stop();
	}
}
