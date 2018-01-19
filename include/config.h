#ifndef CONFIG_H_
#define CONFIG_H_

#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>

///Math constants
const double SQRT_2 = sqrt(2);
const double PI = 3.1415926;
const double EPSILON = 0.000001;
const int MODULO = 1000000000;
const int FOV_NUM_ITER = 30;
const double FOV_STEP_IN_DEGREES = 1;

///Screen
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int SCREEN_DIAG = sqrt(SCREEN_WIDTH * SCREEN_WIDTH + SCREEN_HEIGHT * SCREEN_HEIGHT);
const int FRAME_RATE_LIMIT = 200;
const int ANTIALIASING_LEVEL = 8;
const std::string SCREEN_TITLE = "Top down shooter";
//const sf::Color BACKGROUND_COLOR = sf::Color(200, 200, 200);
//const sf::Color BACKGROUND_COLOR = sf::Color(255, 255, 255);

const int DIST_SQUARED_VISIBILITY_CUTOFF = 2 * 96 * 96;//8 seems ok without angle restrictions
const double PLAYER_ANGLE_VISIBILITY_CUTOFF = 0.9;//SQRT_2 / 2;

///Colors
const sf::Color MAIN_MENU_STATE_BACKGROUND_COLOR = sf::Color(150, 150, 150);
const sf::Color PLAY_STATE_BACKGROUND_COLOR = sf::Color(0, 0, 0);
const sf::Color GAME_OVER_STATE_BACKGROUND_COLOR = sf::Color(150, 150, 150);

///Map
const int MAP_WIDTH_IN_TILES = 150;
const int MAP_HEIGHT_IN_TILES = 150;

const int MAP_TILE_WIDTH_IN_PIXELS = 32;
const int MAP_TILE_HEIGHT_IN_PIXELS = 32;

const int NUM_ITERATIONS_SMOOTH = 10;


///Mini map
const int MINI_MAP_WIDTH_IN_PIXELS = MAP_WIDTH_IN_TILES * 4;
const int MINI_MAP_HEIGHT_IN_PIXELS = MAP_HEIGHT_IN_TILES * 4;
const int MINI_MAP_TILE_WIDTH_IN_PIXELS = MINI_MAP_WIDTH_IN_PIXELS / MAP_WIDTH_IN_TILES;
const int MINI_MAP_TILE_HEIGHT_IN_PIXELS = MINI_MAP_HEIGHT_IN_PIXELS / MAP_HEIGHT_IN_TILES;
const int MINI_MAP_ALPHA_VALUE = 10;
const int MINI_MAP_OUTLINE_THICKNESS = 8;
const sf::Color MINI_MAP_OUTLINE_COLOR = sf::Color::Yellow;//sf::Color(50, 50, 250);

///Info rectangle
//const int INFO_RECT_SHAPE_HEIGHT = MAP_TILE_HEIGHT_IN_PIXELS * 2;
const int INFO_RECT_SHAPE_HEIGHT = MAP_TILE_HEIGHT_IN_PIXELS * 3;//SCREEN_HEIGHT / 10;
const int PLAYER_INFO_TEXT_SIZE = 30;
const sf::Color INFO_RECT_COLOR = sf::Color(150, 150, 200);

///Map
const int MAP_WIDTH_IN_PIXELS = MAP_WIDTH_IN_TILES * MAP_TILE_WIDTH_IN_PIXELS;//SCREEN_WIDTH;
const int MAP_HEIGHT_IN_PIXELS = MAP_HEIGHT_IN_TILES * MAP_TILE_HEIGHT_IN_PIXELS + INFO_RECT_SHAPE_HEIGHT;//SCREEN_HEIGHT;

const int MAP_FILL_PERCENTAGE = 50;//44;
//const int NEIGHBOR_CUTOFF = 4;

const double OFFSET_X = 0;
const double OFFSET_Y = INFO_RECT_SHAPE_HEIGHT;

///Tile symbols
const char WHITE_TILE = '0';
const char GREEN_TILE = '1';
const char BROWN_TILE = '2';
const char BLUE_TILE = '3';



///Resource paths
const std::string FONTS_PATH = "resources/fonts/";
const std::string TEXTURES_PATH = "resources/textures/";
const std::string SOUNDS_PATH = "resources/sounds/";
const std::string MUSIC_PATH = "resources/music/";

///Text size
const int GAME_OVER_TEXT_SIZE = 60;
const int SCORE_TEXT_SIZE = 40;
const int PRESS_ANY_KEY_TEXT_SIZE = 20;
const int MENU_TEXT_SIZE = 20;


const int PLAYER_RADIUS = 20;


const double PLAYER_DX = 0.1;
const double PLAYER_DY = 0.1;

const double ENEMY_EASY_DX = 0.03;
const double ENEMY_EASY_DY = 0.03;

const double ENEMY_MEDIUM_DX = 0.015;
const double ENEMY_MEDIUM_DY = 0.015;

const double BULLET_DX = 0.95;
const double BULLET_DY = 0.95;

const int PLAYER_HEALTH = 100;
const int ENEMY_EASY_HEALTH = 30;
const int ENEMY_MEDIUM_HEALTH = 60;

const int PLAYER_DAMAGE = 10;
const int ENEMY_EASY_DAMAGE = 10;
const int ENEMY_MEDIUM_DAMAGE = 20;

const int PLAYER_INVUL_DURATION = 5000;//in milliseconds

const int DIST_FROM_GUN_TO_PLAYER_CENTER = 24;

const int OUTLINE_THICKNESS = 2;

const int TIME_ADJUSTMENT_COEFF = 800;


const int ENEMY_EASY_COUNT = 0;
const int ENEMY_MEDIUM_COUNT = 0;


const double ENEMY_EASY_ANIMATION_SPEED = 0.005;
const double ENEMY_MEDIUM_ANIMATION_SPEED = 0.0025;

const int ENEMY_EASY_ANIMATION_FRAMES_COUNT = 4;
const int ENEMY_MEDIUM_ANIMATION_FRAMES_COUNT = 4;


const int SCORE_REWARD_ENEMY_EASY = 5;
const int SCORE_REWARD_ENEMY_MEDIUM = 10;
const int SCORE_REWARD_ENEMY_HARD = 20;



const sf::Vector2f INFO_RECT_SHAPE_INITIAL_POSITION = sf::Vector2f(0, 0);
const sf::Vector2f INFO_TEXT_INITIAL_POSITION = sf::Vector2f(10, 10);

const sf::Vector2f VIEW_INITIAL_CENTER = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
const sf::Vector2f VIEW_INITIAL_SIZE = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);

const int PLAYET_INITIAL_X_POSITION = SCREEN_WIDTH / 2;
const int PLAYET_INITIAL_Y_POSITION = SCREEN_HEIGHT / 2;

const int AFTERSHOT_DELAY_IN_MILLISECONDS = 50;
const int AFTERSHOT_OFFSET_IN_PIXELS = 4;

const int BULLET_FIRE_ANIMATION_DURATION_IN_MILLISECONDS = 100;

const int PLAYER_GUN_KNOCKBACK_DISTANCE = 8;


const int MENU_BUTTON_WIDTH = 200;
const int MENU_BUTTON_HEIGHT = 100;
const sf::Vector2f MENU_BUTTON_SIZE = sf::Vector2f(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
const sf::Color MENU_BUTTON_COLOR = sf::Color(255, 255, 255);
const double MENU_BUTTON_OUTLINE_THICKNESS = 5;
const sf::Color MENU_BUTTON_OUTLINE_COLOR = sf::Color(0, 0, 0);

const int MENU_NEW_GAME_BUTTON_POSITION_X = (SCREEN_WIDTH - MENU_BUTTON_WIDTH) / 2;
const int MENU_NEW_GAME_BUTTON_POSITION_Y = 300;
const sf::Vector2f MENU_NEW_GAME_BUTTON_POSITION = sf::Vector2f(MENU_NEW_GAME_BUTTON_POSITION_X, MENU_NEW_GAME_BUTTON_POSITION_Y);

const int MENU_OPTIONS_BUTTON_POSITION_X = MENU_NEW_GAME_BUTTON_POSITION_X - MENU_BUTTON_WIDTH - 2 * MENU_BUTTON_OUTLINE_THICKNESS;
const int MENU_OPTIONS_BUTTON_POSITION_Y = MENU_NEW_GAME_BUTTON_POSITION_Y + MENU_BUTTON_HEIGHT + 2 * MENU_BUTTON_OUTLINE_THICKNESS;
const sf::Vector2f MENU_OPTIONS_BUTTON_POSITION = sf::Vector2f(MENU_OPTIONS_BUTTON_POSITION_X, MENU_OPTIONS_BUTTON_POSITION_Y);

const int MENU_EXIT_BUTTON_POSITION_X = MENU_OPTIONS_BUTTON_POSITION_X - MENU_BUTTON_WIDTH - 2 * MENU_BUTTON_OUTLINE_THICKNESS;
const int MENU_EXIT_BUTTON_POSITION_Y = MENU_OPTIONS_BUTTON_POSITION_Y + MENU_BUTTON_HEIGHT + 2 * MENU_BUTTON_OUTLINE_THICKNESS;
const sf::Vector2f MENU_EXIT_BUTTON_POSITION = sf::Vector2f(MENU_EXIT_BUTTON_POSITION_X, MENU_EXIT_BUTTON_POSITION_Y);



const sf::Color MENU_TEXT_COLOR = sf::Color(0, 0, 0);
const int MENU_CHARACTER_SIZE = 20;

const sf::Color MENU_BUTTON_DEFAULT_COLOR = sf::Color(255, 255, 255);
const sf::Color MENU_BUTTON_ON_SELECT_COLOR = sf::Color(0, 150, 0);

///Weapons
const double PISTOL_DAMAGE = 10;
const double PISTOL_SHOOT_DELAY = 0;
const double PISTOL_SPAWN_PROBABILITY = 1;

///Options state
const int OPTIONS_WINDOW_WIDTH = 600;
const int OPTIONS_WINDOW_HEIGHT = 400;
const int OPTIONS_STATE_TEXT_SIZE = 20;

///Sound
const int PLAY_STATE_VOLUME_LEVEL = 3;


///Procedural
const std::vector<int> BIRTH_VALUES = {5,6,7,8};//if dead cell has number of neighbors that
                    //belongs to this set of values, it becomes alive, o/w it stays dead
const std::vector<int> SURVIVE_VALUES = {4,5,6,7,8};//if alive cell has number of neighbors that
                    //belongs to this set, it stays alive, o/w it becomes dead

///Examples of cellular automata:
//---https://en.wikipedia.org/wiki/Life-like_cellular_automaton
//---B5678/S45678 - default
//---B5678/S345678 - 25...55
//---B5678/S2345678 - 15...55
//---B5678/S12345678 - 10...40
//---B678/S12345678 - 10...80
//---B78/S12345678 - 40
//---B678/S35678 - 60, 65, 70, 75, 80
//---B35678/S35678 - 10, 15, 20,25
//---B35678/S235678 - 1...10
//---B5678/S25678 - 65, 70
//---B678/S2567
//---B4678/S35678 - Anneal - 45...55
//---B35678/S5678 - Diamoeba - 40...45
//---B3678/S34678 - Day & Night 20...40
//---B3/S23 - Conway's Game of Life
//---B368/S245 - Morley
//---B36/S125 - 2x2
//---B/S1
//---B/S12
//---B/S14
//---B/S23
//---B/S24
//---B123/S
//---B13/S

#endif // CONFIG_H_

