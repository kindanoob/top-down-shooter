#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


///C stands for corner tile, H stands for horizontal, V stands for vertical

const std::vector<std::string> GAME_MAP = {
    "AHHHHHHHHHHHHHHHHHHHHHGHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHB",
    "V                     V                                    V",
    "V                     V                                    V",
    "V                     V                                    V",
    "V                     V                                    V",
    "V                     V               K          K         V",
    "V                     V               V          V         V",
    "V                     V               V          V         V",
    "V                     DHHHHHHHHHHHHHHHC          V         V",
    "V                                                V         V",
    "V                                                V         V",
    "EHHHHHHHHHHHHHHHHHHHHHB               K          V         V",
    "V                     V               V          V         V",
    "V                     V               V          M         V",
    "V                     V               V                    V",
    "V                     V               V                    V",
    "V                     V               V          K         V",
    "V                     V               DHHHHHHHHHHC         V",
    "V                     V                                    V",
    "V                     V                                    V",
    "V                     V                                    V",
    "V                     V     JHHHHHHHHB                     V",
    "V                     V              V                     V",
    "V                     V              V                     V",
    "V                     V              V                     V",
    "V                     V              V                     V",
    "V                     DHHHHB         M                     V",
    "V                          V                               V",
    "V                          V                               V",
    "V                          V                               V",
    "V                          V                               V",
    "V                          M                               V",
    "V                                                          V",
    "V                                                          V",
    "V                                                          V",
    "V                 JHHHHHHHHHL                              V",
    "V                                                          V",
    "V                                                          V",
    "V                                                          V",
    "DHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHC"
};


class Application;
class Room;
class Node;

class Game_map{
public:
    std::vector<std::vector<char> > char_map_;
    int width_;
    int height_;
    int map_fill_percentage_;
    int tile_width_in_pixels_;
    int tile_height_in_pixels_;
    std::vector<Room *> room_vector_;
public:
    Game_map(int width, int height, int map_fill_percentage,
             int tile_width_in_pixels, int tile_height_in_pixels,
             Application *app);
    std::vector<std::vector<char> >& char_map();
    void randomize_map(int map_fill_percent);
    void print_map_to_console();
    bool is_valid_cell(int i, int j);
    bool is_on_boundary(int i, int j);
    int count_neighbors(int i, int j, char c);
    void smooth_map(int num_iterations);
    void draw_map(sf::RenderWindow& window, double offset_x, double offset_y);
    void remove_region(int i, int j);
    int width();
    int height();
    std::vector<Room *> generate_rooms();
    void dfs(int i, int j, std::vector<std::vector<int> >& visited,
                   std::vector<Node *>& connected_component);
    void dfs_room(Room *room, std::vector<Room *>& rooms, std::vector<Room *>& visited,
              std::vector<Room *>& connected_component);
    std::vector<std::vector<Room *> > group_rooms_into_connected_components(
                                std::vector<Room *>& rooms);
    void connect_main_room_to_other_rooms(Room *main_room, std::vector<Room *>& rooms,
                            std::vector<std::vector<Room *> >& rooms_connected_components);
    void create_passageways();
    void process_map(sf::RenderWindow *window);
    void connect_closest_rooms();
    void draw_room_connections(sf::RenderWindow& window);
    void reset();
    void create_boundaries();
    int count_connected_componenets(std::vector<Room *>& rooms);
    std::vector<std::vector<std::pair<int, int> > > group_tiles_into_connected_componenets(
                                                            std::vector<Room *>& rooms);

    void remove_connected_components(std::vector<Room *>& rooms);
    void dfs_simple(int i, int j, std::vector<std::vector<int> >& visited,
                        std::vector<std::pair<int, int> >& connected_component);
    void connect_rooms(std::vector<Room *>& rooms);


    void init_sprites(Application *app);

    sf::Sprite game_map_horizontal_sprite_;
    sf::Sprite game_map_vertical_sprite_;
    sf::Sprite game_map_top_left_corner_sprite_;
    sf::Sprite game_map_top_right_corner_sprite_;
    sf::Sprite game_map_bottom_left_corner_sprite_;
    sf::Sprite game_map_bottom_right_corner_sprite_;
    sf::Sprite game_map_top_sprite_;
    sf::Sprite game_map_bottom_sprite_;
    sf::Sprite game_map_left_sprite_;
    sf::Sprite game_map_right_sprite_;
    sf::Sprite game_map_left_cap_sprite_;
    sf::Sprite game_map_top_cap_sprite_;
    sf::Sprite game_map_right_cap_sprite_;
    sf::Sprite game_map_bottom_cap_sprite_;
    sf::Sprite game_map_wall_borderless_sprite_;
    sf::Sprite floor_sprite_;
    sf::Sprite wall_sprite_;
    sf::Sprite brown_sprite_;
};

#endif // GAME_MAP_H
