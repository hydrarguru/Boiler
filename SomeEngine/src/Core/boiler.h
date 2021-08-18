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

//SFML
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

//ImGui
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <ImGuiSFML/imgui-SFML.h>

//mINI
#include "mini/ini.h"

//Resource defines:
constexpr auto ENGINE_ICON = "Resources/Images/boiler_icon.png";
constexpr auto ENGINE_FONT = "Fonts/Roboto.ttf";

//Logging
inline void DebugLog(std::string log_msg)
{
	auto time = std::chrono::system_clock::now();
	std::cout << log_msg << std::endl;
	std::ofstream file;
	file.open("log_file.txt", std::ios::app);
	file  << "Time: " << time << " Log: " << log_msg << "\n";
	file.close();
}

inline void DebugLog(char log_msg)
{
	auto time = std::chrono::system_clock::now();
	std::cout << log_msg << std::endl;
	std::ofstream file;
	file.open("log_file.txt", std::ios::app);
	file << "Time: " << time << " Log: " << log_msg << "\n";
	file.close();
}

inline void DebugLog(float log_msg)
{
	auto time = std::chrono::system_clock::now();
	std::cout << log_msg << std::endl;
	std::ofstream file;
	file.open("log_file.txt", std::ios::app);
	file  << "Time: " << time << " Log: " << log_msg << "\n";
	file.close();
}

inline void DebugLog(double log_msg)
{
	auto time = std::chrono::system_clock::now();
	std::cout << log_msg << std::endl;
	std::ofstream file;
	file.open("log_file.txt", std::ios::app);
	file << "Time: " << time << " Log: " << log_msg << "\n";
	file.close();
}

inline void DebugLog(int log_msg)
{
	auto time = std::chrono::system_clock::now();
	std::cout << log_msg << std::endl;
	std::ofstream file;
	file.open("log_file.txt", std::ios::app);
	file  << "Time: " << time << " Log: " << log_msg << "\n";
	file.close();
}