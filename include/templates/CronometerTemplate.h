#pragma once

const auto CRONOMETER_H_TEMPLATE { R"(#pragma once

namespace be {

class Cronometer {
public:
	Cronometer() = default;
	~Cronometer() = default;
	
	void start();
	void stop();
	void resume();
	void restart();
	
	unsigned int getSeconds() const;
	unsigned int getMilliseconds() const;
	
	bool isRunning() const;
private:
	unsigned int m_startTime { 0 };
	unsigned int m_stopTime { 0 };
	
	bool m_isRunning { false };
};

} // namespace be
)" };

const auto CRONOMETER_CPP_TEMPLATE { R"(#include "be/Cronometer.h"

#include <SDL3/SDL.h>

namespace be {

void Cronometer::start() {
	if(!m_isRunning) {
		m_isRunning = true;
		m_startTime = SDL_GetTicks();
	}
}

void Cronometer::stop() {
	if(m_isRunning) {
		m_stopTime = SDL_GetTicks();
		m_isRunning = false;
	}
}

void Cronometer::resume() {
	if(m_isRunning) {
		m_startTime += SDL_GetTicks() - m_stopTime;
		m_isRunning = true;
	}
}

void Cronometer::restart() {
	m_isRunning = true;
	m_startTime = SDL_GetTicks();
}

unsigned int Cronometer::getSeconds() const {
	return ((m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime) / 1000;
}

unsigned int Cronometer::getMilliseconds() const {
	return (m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime;
}

bool Cronometer::isRunning() const {
	return m_isRunning;
}

} // namespace be
)" };