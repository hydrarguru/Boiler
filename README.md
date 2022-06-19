# Cross platfrom SFML + ImGUI project template 

# How to build?

#### You need CMake. Install it for command line atleast. If you are not sure if you have it: `cmake --version`
#### After installing CMake  follow steps 1-7
1. Clone project or download Zip-file and unzip it
2. Open terminal inside of the project
3. `mkdir build` -  to make "build" directory inside of project folder
4. `cd ./build` - go inside of "build" folder
5. `cmake ..` - to link files (On windows use command `cmake .. -G "MinGW Makefiles"` if you followed windows prerequisites guide)
6. `make` - to build project (On windows use command `mingw32-make.exe` if you followed windows prerequisites guide)
7. `./a` - to display output

# 3rd party libraries
## SFML
- SFML: SFML is a simple, fast, cross-platform and object-oriented multimedia API
- <https://github.com/SFML/SFML>

## Dear ImGui
- ImGui: Dear ImGui is a bloat-free graphical user interface library for C++.
- <https://github.com/ocornut/imgui>

## ImGui-SFML binding
- ImGui-SFML: Library which allows you to use Dear ImGui with SFML binding 
- <https://github.com/eliasdaler/imgui-sfml>

# p.s.
- https://github.com/lutrarutra/SFML-Project-Template
- Creator: lutrarutra
