#pragma once

auto MOUSEMANAGER_H_TEMPLATE { R"(#pragma once

namespace be {

enum class MouseButton:char { Left = 1, Middle = 2, Right = 3 };

class MouseManager {
public:
	static MouseManager &getInstance();
	
	bool isButtonPressed(MouseButton btn) const;
	bool isButtonDown(MouseButton btn) const;
	bool isButtonReleased(MouseButton btn) const;
	
	void getMouseCoords(int &x, int &y) const;
	void getMouseRelCoords(int &dx, int &dy) const;
private:
	template<typename T>
	friend class Game;
	
	MouseManager() = default;
	~MouseManager() = default;
	
	void update();
	
	void buttonPressed(MouseButton btn);
	void buttonReleased(MouseButton btn);
	
	void mouseMoved(int x, int y, int dx, int dy);
	
	int m_scroll { 0 };
	
	int m_x { 0 };
	int m_y { 0 };
	
	int m_dx { 0 };
	int m_dy { 0 };
	
	char m_buttonState { 0 };
};

} // namespace be
)" };

auto MOUSEMANAGER_CPP_TEMPLATE { R"(#include "be/MouseManager.h"

namespace be {

MouseManager &MouseManager::getInstance() {
	static MouseManager instance;
	return instance;
}

bool MouseManager::isButtonPressed(MouseButton btn) const {
	char btnMask = (1 << (static_cast<char>(btn) - 1));
	return !((btnMask << 4) & m_buttonState) && (btnMask & m_buttonState);
}

bool MouseManager::isButtonDown(MouseButton btn) const {
	char btnMask = (1 << (static_cast<char>(btn) - 1));
	return (btnMask & m_buttonState);
}

bool MouseManager::isButtonReleased(MouseButton btn) const {
	char btnMask = (1 << (static_cast<char>(btn) - 1));
	return ((btnMask << 4) & m_buttonState) && !(btnMask & m_buttonState);
}

void MouseManager::update() {
	char currFrameMask = m_buttonState & 0x0f;
	m_buttonState = (currFrameMask << 4) | currFrameMask;
	m_dx = m_dy = 0;
}

void MouseManager::buttonPressed(MouseButton btn) {
	m_buttonState = (1 << (static_cast<char>(btn) - 1)) | m_buttonState;
}

void MouseManager::buttonReleased(MouseButton btn) {
	m_buttonState = ((1 << (static_cast<char>(btn) - 1)) ^ 0xff) & m_buttonState;
}

void MouseManager::mouseMoved(int x, int y, int dx, int dy) {
	m_x = x;
	m_y = y;
	m_dx = dx;
	m_dy = dy;
}

} // namespace be
)" };