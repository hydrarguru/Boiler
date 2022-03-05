#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <map>
#include <filesystem>
#include <chrono>
#include <map>

//SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//mINI
#include "ini.h"

//Resource defines:
constexpr auto ENGINE_FONT = "OpenSans-Regular.ttf";




template<typename T>
void DebugLog(T log_msg)
{
	std::cout << log_msg << std::endl;
};