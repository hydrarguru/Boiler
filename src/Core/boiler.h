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
#include <memory>

//SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//ImGui
#include <imgui-SFML.h>
#include <imgui.h>

//mINI
#include "mini.h"

//Resource defines:
constexpr auto ENGINE_FONT = "fonts/OpenSans-Regular.ttf";
constexpr auto ENGINE_FONT_ALT = "fonts/Roboto.ttf";




template<typename T>
void DebugLog(T log_msg)
{
	std::cout << log_msg << std::endl;
};