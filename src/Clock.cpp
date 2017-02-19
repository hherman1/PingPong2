#include "Clock.h"


namespace basicgraphics {

	Clock::Clock():
		time(std::chrono::steady_clock::now())
	{
	}


	Clock::~Clock()
	{
	}
	std::chrono::milliseconds Clock::tick()
	{
		auto old = time;
		time = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(time - old);
	}
}
