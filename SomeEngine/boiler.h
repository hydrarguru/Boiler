#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <map>

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