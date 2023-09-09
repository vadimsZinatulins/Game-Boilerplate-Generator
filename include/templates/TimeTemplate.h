#pragma once

auto TIMER_H_TEMPLATE { R"(#pragma once 
 
namespace be { 
 
class Time { 
public: 
   static inline unsigned int getTicks() { return m_ticks; } 
   static inline float getDeltaTime() { return m_deltaTime; } 
private: 
   template<typename T> 
   friend class Game; 
 
   Time(); 
   ~Time(); 
 
   static unsigned int m_ticks; 
   static float m_deltaTime; 
}; 
 
} // namespace be

)" };

auto TIMER_CPP_TEMPLATE { R"(#include "be/Time.h" 
#include "config.h" 

#include <SDL.h>

namespace be {

constexpr unsigned int MinTicksPerFrame = 1000 / FRAME_CAP;

unsigned int Time::m_ticks = 0;
float Time::m_deltaTime = 0.0f;

Time::Time() {
   unsigned int ticks = SDL_GetTicks();
   m_deltaTime = (float)(ticks - m_ticks) / 1000.0f;
   m_ticks = ticks;
}

Time::~Time() {
   unsigned int frameTicks = SDL_GetTicks() - m_ticks;
   if(frameTicks < MinTicksPerFrame) SDL_Delay(MinTicksPerFrame - frameTicks);
}

} // namespace be

)" };