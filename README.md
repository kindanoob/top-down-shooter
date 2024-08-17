# top_down_shooter

![top_down_shooter](resources/top_down_shooter.png)

![top_down_shooter_minimap](resources/top_down_shooter_minimap.png)

Basic engine for top-down shooter game implemented in C++ using SFML

Requirements: 
    1) C++14 
    2) SFML 2.6.1
    
The program was tested on Ubuntu 22.04 LTS Jammy, gcc 11.4.0.

Instructions for an out-or-place build:
1) Go to the directory containing the CMakeLists.txt file.
2) Run `cmake -S . -B build`. This will create a `build` directory and put CMake files there.
3) Go to the `build` directory.
4) Build the project (e.g. for Unix makefiles it is achieved by running `make` command in the terminal).
5) Launch the executable file "top_down_shooter".
6) Mouse controls. Use mouse to navigate the main menu. Click on the menu buttons with left mouse click.
    While in game, use left mouse click to shoot.
7) Keyboard controls. Use WASD keys to move your character up/left/down/right. Press M key to show/hide minimap.
    Press K key to end the game.
8) Currently there is only one sandbox level with a procedurally generated map and without any goal.


The project is early in the development stage and there are a lot of things to be implemented.
