#pragma once

class Window {
	public:
		int height;
		int interval;
		int width;

		Window(int width, int height, int interval) :
			width(width),
			height(height),
			interval(interval)
		{}
};