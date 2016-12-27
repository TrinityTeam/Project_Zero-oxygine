#pragma once


class Application {
public:
	static void run();

	Application() = delete;
	Application(const Application&) = delete;

private:
	static bool loop();

};
