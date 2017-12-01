


#include "game_map.h"
#include "application.h"
#include "display.h"
#include "resource_holder.h"
#include "texture_manager.h"
#include "rng.h"
#include "config.h"
#include "room.h"
#include "util.h"



Game_map::Game_map(int width, int height, int map_fill_percentage,
                   int tile_width_in_pixels, int tile_height_in_pixels,
                   Application *app):
    width_(width), height_(height), map_fill_percentage_(map_fill_percentage), tile_width_in_pixels_(tile_width_in_pixels), tile_height_in_pixels_(tile_height_in_pixels){
    std::cout << "Game_map()" << std::endl;
    char_map_ = std::vector<std::vector<char> >(width, std::vector<char>(height, '1'));
    //char_map_ = std::vector<std::vector<char> >(width, std::vector<char>(height, '1'));

    process_map(app -> display -> window);
    //print_map_to_console();
    init_sprites(app);
}


void Game_map::reset(){
    char_map_ = std::vector<std::vector<char> >(width(), std::vector<char>(height(), '1'));
}

std::vector<std::vector<char> >& Game_map::char_map(){
    return char_map_;
}

void Game_map:: print_map_to_console(){
    std::cout << "print_map_to_console, w: " << width() << ", h: " << height() << std::endl;
    std::cout << std::endl;
    for(int i = 0; i < height(); ++i){
        std::cout << " ";
        for(int j = 0; j < width(); ++j){
            std::cout << char_map_[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Game_map::randomize_map(int map_fill_percent){
    for(int i = 0; i < char_map_.size(); ++i){
        for(int j = 0; j < char_map_[0].size(); ++j){
            if((i == 0) || (j == 0) || (i == char_map_.size() - 1) || (j == char_map_[0].size() - 1)){
                char_map_[i][j] = '1';
                continue;
            }
            int rand_int = Rng::int_in_range(0, 100);
            //int rand_int = 0;
            if(rand_int < map_fill_percent){
                char_map_[i][j] = '1';
            }
            else{
                char_map_[i][j] = '0';
            }
        }
    }
}


bool Game_map::is_valid_cell(int i, int j){
    return (i >= 0) && (i < height()) && (j >= 0) && (j < width());
}


int Game_map::count_neighbors(int i, int j, char c){
    int cnt = 0;
    for(int dx = -1; dx < 2; ++dx){
        for(int dy = -1; dy < 2; ++dy){
            if((dx == 0) && (dy == 0)){
                continue;
            }
            if(is_valid_cell(i + dy, j + dx) && (char_map_[i + dy][j + dx] == c)){
                ++cnt;
            }
        }
    }
    return cnt;
}


void Game_map::smooth_map(int num_iterations){
    for(int k = 0; k < num_iterations; ++k){
        for(int i = 1; i < char_map_.size() - 1; ++i){
            for(int j = 1; j < char_map_[0].size() - 1; ++j){
                char curr = char_map_[i][j];
                int cnt = count_neighbors(i, j, GREEN_TILE);
                if(curr == WHITE_TILE){//if the cell is dead
                    if(std::find(BIRTH_VALUES.begin(), BIRTH_VALUES.end(), cnt) !=
                       BIRTH_VALUES.end()){
                        char_map_[i][j] = GREEN_TILE;
                    }
                }
                else{//if the cell is alive
                    if(std::find(SURVIVE_VALUES.begin(), SURVIVE_VALUES.end(), cnt) ==
                            SURVIVE_VALUES.end()){
                        char_map_[i][j] = WHITE_TILE;
                    }
                }
                //if(cnt < neighbor_cutoff){

            }
        }
    }
}


void Game_map::draw_map(sf::RenderWindow& window, double offset_x, double offset_y){
    for(int i = 0; i < height(); ++i){
        for(int j = 0; j < width(); ++j){
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(tile_width_in_pixels_, tile_width_in_pixels_));
            rect.setPosition(sf::Vector2f(offset_x + j * tile_width_in_pixels_, offset_y + i * tile_width_in_pixels_));
            if(char_map_[i][j] == '1'){
                rect.setFillColor(sf::Color(0, 0, 0));
            }
            else{
                rect.setFillColor(sf::Color(255, 255, 255));
            }
            window.draw(rect);
        }
    }
}


bool Game_map::is_on_boundary(int i, int j){
    return (char_map_[i + 1][j] == '1') || (char_map_[i - 1][j] == '1') ||
            (char_map_[i][j - 1] == '1') || (char_map_[i][j + 1] == '1');
}


int Game_map::height(){
    return char_map_.size();
}


int Game_map::width(){
    return char_map_[0].size();
}


std::vector<Room *> Game_map::generate_rooms(){
    std::vector<Room *> rooms;
    std::vector<std::vector<int> > visited(height(), std::vector<int>(width(), 0));
    for(int i = 0; i < height(); ++i){
        for(int j = 0; j < width(); ++j){
            if(!visited[i][j] && (char_map_[i][j] == '0')){
                std::vector<Node *> connected_component;
                dfs(i, j, visited, connected_component);
                Room  *new_room = new Room(connected_component, this);
                rooms.push_back(new_room);
            }
        }
    }
    return rooms;
}

int Game_map::count_connected_componenets(std::vector<Room *>& rooms){
    //std::cout << "in count_connected_componenets, rooms size: " << rooms.size() << std::endl;
    int cnt = 0;
    std::vector<std::vector<int> > visited(height(), std::vector<int>(width(), 0));
    std::vector<std::pair<int, int> > connected_component;
    for(int i = 0; i < height(); ++i){
        for(int j = 0; j < width(); ++j){
            if(!visited[i][j] && (char_map_[i][j] == '0')){
                //std::cout << "started DFS from " << i << ", " << j << std::endl;
                dfs_simple(i, j, visited, connected_component);
                ++cnt;
            }
        }
    }
    return cnt;
}


std::vector<std::vector<std::pair<int, int> > > Game_map::group_tiles_into_connected_componenets(
                                                            std::vector<Room *>& rooms){
    std::vector<std::vector<std::pair<int, int> > > res;
    int cnt = 0;
    std::vector<std::vector<int> > visited(height(), std::vector<int>(width(), 0));
    for(int i = 0; i < height(); ++i){
        for(int j = 0; j < width(); ++j){
            if(!visited[i][j] && (char_map_[i][j] == '0')){
                std::vector<std::pair<int, int> > cc;
                dfs_simple(i, j, visited, cc);
                res.push_back(cc);
            }
        }
    }
    return res;
}


void Game_map::remove_connected_components(std::vector<Room *>& rooms){
    std::vector<std::vector<std::pair<int, int> > > connected_components =
        group_tiles_into_connected_componenets(rooms);
    std::sort(connected_components.begin(), connected_components.end(),
              Util::cmp_tile_connected_components_by_size_descending);
    for(int i = 1; i < connected_components.size(); ++i){
        for(auto& n: connected_components[i]){
            char_map_[n.first][n.second] = '1';
        }
    }
}

void Game_map::dfs(int i, int j, std::vector<std::vector<int> >& visited,
                   std::vector<Node *>& connected_component){
    visited[i][j] = 1;
    Node *new_node = new Node(j, i);
    connected_component.push_back(new_node);
    if((is_valid_cell(i + 1, j)) && !visited[i + 1][j] && (char_map_[i + 1][j] == '0')){
        dfs(i + 1, j, visited, connected_component);
    }
    if((is_valid_cell(i - 1, j)) && !visited[i - 1][j] && (char_map_[i - 1][j] == '0')){
        dfs(i - 1, j, visited, connected_component);
    }
    if((is_valid_cell(i, j + 1)) && !visited[i][j + 1] && (char_map_[i][j + 1] == '0')){
        dfs(i, j + 1, visited, connected_component);
    }
    if((is_valid_cell(i, j - 1)) && !visited[i][j - 1] && (char_map_[i][j - 1] == '0')){
        dfs(i, j - 1, visited, connected_component);
    }
}


void Game_map::dfs_simple(int i, int j, std::vector<std::vector<int> >& visited,
                        std::vector<std::pair<int, int> >& connected_component){
    visited[i][j] = 1;
    connected_component.push_back(std::make_pair(i, j));
    if((is_valid_cell(i + 1, j)) && !visited[i + 1][j] && (char_map_[i + 1][j] == '0')){
        dfs_simple(i + 1, j, visited, connected_component);
    }
    if((is_valid_cell(i - 1, j)) && !visited[i - 1][j] && (char_map_[i - 1][j] == '0')){
        dfs_simple(i - 1, j, visited, connected_component);
    }
    if((is_valid_cell(i, j + 1)) && !visited[i][j + 1] && (char_map_[i][j + 1] == '0')){
        dfs_simple(i, j + 1, visited, connected_component);
    }
    if((is_valid_cell(i, j - 1)) && !visited[i][j - 1] && (char_map_[i][j - 1] == '0')){
        dfs_simple(i, j - 1, visited, connected_component);
    }
}

void Game_map::dfs_room(Room *room, std::vector<Room *>& rooms, std::vector<Room *>& visited,
              std::vector<Room *>& connected_component){
    if(std::find(visited.begin(), visited.end(), room) != visited.end()){
        return;
    }
    visited.push_back(room);
    connected_component.push_back(room);
    for(auto& r: room -> connected_rooms_){
        dfs_room(r, rooms, visited, connected_component);
    }
}


std::vector<std::vector<Room *> > Game_map::group_rooms_into_connected_components(
                                std::vector<Room *>& rooms){
    std::vector<std::vector<Room *> > res;
    std::vector<Room *> visited;
    for(int i = 0; i < rooms.size(); ++i){
        std::vector<Room *> connected_component;
        dfs_room(rooms[i], rooms, visited, connected_component);
        if(!connected_component.empty()){
            res.push_back(connected_component);
        }
    }
    return res;
}


void Game_map::connect_main_room_to_other_rooms(Room *main_room, std::vector<Room *>& rooms,
                                      std::vector<std::vector<Room *> >& rooms_connected_components){
    for(auto& v: rooms_connected_components){
        if(std::find(v.begin(), v.end(), main_room) == v.end()){
            main_room -> connect_room(main_room -> get_closest_room(v));
        }
    }
}


void Game_map::create_passageways(){
    std::vector<std::vector<Room *> > rooms_connected_components =
        group_rooms_into_connected_components(room_vector_);
    //std::cout << "before components: " << rooms_connected_components.size() << std::endl;
    //double offset_x = 0;
    //double offset_y = 0;
    double offset_x = OFFSET_X;
    double offset_y = OFFSET_Y;
    for(int i = 0; i < room_vector_.size(); ++i){
        for(auto& r: room_vector_[i] -> connected_rooms_){
            if(room_vector_[i] == r){
                continue;
            }
            //std::cout << "connecting room " << room_vector_[i] << " with " <<
            //r << std::endl;
            //double x0 = room_vector_[i] -> node_vector_[0] -> x_;
            //double y0 = room_vector_[i] -> node_vector_[0] -> y_;
            std::pair<Node *, Node *> closest_nodes =
                room_vector_[i] -> get_closest_nodes(r);
            if(!closest_nodes.first || !closest_nodes.second){
                continue;
            }
            //std::cout << "closest nodes: " << closest_nodes.first << ", " <<
            //closest_nodes.second << std::endl;
            if(closest_nodes.first == nullptr){
                std::cout << "first triggered" << std::endl;
            }
            if(closest_nodes.second == nullptr){
                std::cout << "second triggered" << std::endl;
            }
            double x0 = closest_nodes.first -> x_;
            double y0 = closest_nodes.first -> y_;
            x0 *= tile_width_in_pixels_;
            y0 *= tile_width_in_pixels_;
            x0 += offset_x;
            y0 += offset_y;
            //double x1 = r -> node_vector_[0] -> x_;
            //double y1 = r -> node_vector_[0] -> y_;
            double x1 = closest_nodes.second -> x_;
            double y1 = closest_nodes.second -> y_;
            x1 *= tile_width_in_pixels_;
            y1 *= tile_width_in_pixels_;
            x1 += offset_x;
            y1 += offset_y;
            double a = 0;
            double b = 0;
            double c = 0;
            bool triggered = false;
            if(fabs(x0 - x1) < EPSILON){//if the line is vertical, e.g. x = x0
                a = 1;
                b = 0;
                c = -x0;
                //std::cout << "triggered x" << std::endl;
                //std::cout << "point A: " << x0 - offset_x << ", " << y0 - offset_y << std::endl;
                //std::cout << "point B: " << x1 - offset_x << ", " << y1 - offset_y << std::endl;
                //std::cout << "line: " << a << " * x + " << b <<
                            //" * y + " << c << " = 0" << std::endl;
                //triggered = true;
            }
            else if(fabs(y0 - y1) < EPSILON){//if the line is vertical, e.g. x = x0
                a = 0;
                b = 1;
                c = -y0;
                //std::cout << "triggered y" << std::endl;
                //std::cout << "point A: " << x0 - offset_x << ", " << y0 - offset_y << std::endl;
                //std::cout << "point B: " << x1 - offset_x << ", " << y1 - offset_y << std::endl;
                //std::cout << "line: " << a << " * x + " << b <<
                            //" * y + " << c << " = 0" << std::endl;
            }
            else{
                a = (y0 - y1) / (x0 - x1);
                b = 1;
                c = y0 - a * x0;
                a *= -1;
                c *= -1;
            }
            //std::cout << "point A: " << x0 << ", " << y0 << std::endl;
            //std::cout << "point B: " << x1 << ", " << y1 << std::endl;
            //std::cout << "line: " << a << " * x + " << b << std::endl;
            int cnt = 0;
            for(int i = 0; i < height(); ++i){
                for(int j = 0; j < width(); ++j){
                    if(triggered){
                        //std::cout << "i: " << i << ", j: " << j << std::endl;
                    }
                    double x = j * tile_width_in_pixels_ + tile_width_in_pixels_ / 2 + offset_x;
                    double y = i * tile_width_in_pixels_ + tile_width_in_pixels_ / 2 + offset_y;
                    double dist = Util::dist_from_point_to_line(x, y, a, b, c);
                    if(dist < tile_width_in_pixels_ * SQRT_2){
                    //if(dist < tile_width_in_pixels_ * 2){
                        double dist_to_first_end = Util::dist_squared_from_point_to_point(x, y, x0, y0);
                        double dist_to_second_end = Util::dist_squared_from_point_to_point(x, y, x1, y1);
                        double dist_first_to_second = Util::dist_squared_from_point_to_point(x0, y0, x1, y1);
                        if((dist_to_first_end <= dist_first_to_second) &&
                           (dist_to_second_end <= dist_first_to_second)){
                            char_map_[i][j] = '0';
                            ++cnt;
                        }
                    }
                }
            }
            if(cnt == 0){
                std::cout << "cnt: " << cnt << std::endl;
            }
        }
    }
    //std::cout << "after components: " << rooms_connected_components.size() << std::endl;
}


void Game_map::connect_rooms(std::vector<Room *>& rooms){
    connect_closest_rooms();
    sort(room_vector_.begin(), room_vector_.end(), Room::cmp_rooms_by_size);
    if(!room_vector_.empty()){
        room_vector_[0] -> is_main_room_ = true;
    }
    std::vector<std::vector<Room *> > rooms_connected_components =
        group_rooms_into_connected_components(room_vector_);
    //std::cout << "rooms size: " << rooms.size() << std::endl;
    std::cout << "before conn comp size:  " << rooms_connected_components.size() << std::endl;
    if(!room_vector_.empty()){
        connect_main_room_to_other_rooms(room_vector_[0], room_vector_, rooms_connected_components);
    }
    rooms_connected_components =
        group_rooms_into_connected_components(room_vector_);
    std::cout << "after conn comp size:  " << rooms_connected_components.size() << std::endl;
    for(const auto& cc: rooms_connected_components){
        for(const auto& r: cc){
            //std::cout << "room " << r << ", x: " << r -> node_vector_[0] -> x_ <<
            //", y: " << r -> node_vector_[0] -> y_ << std::endl;
        }
    }
}

void Game_map::connect_closest_rooms(){
    if(room_vector_.empty()){
        std::cout << "Error. Cannot connect rooms, because room list is empty." << std::endl;
        return;
    }
    if(room_vector_.size() == 1){
        std::cout << "Error. Cannot connect rooms, because room list contains "
        << "only one room" << std::endl;
        return;
    }
    //std::cout << "size: " << room_vector_.size() << std::endl;
    for(int i = 0; i < room_vector_.size(); ++i){
        room_vector_[i] -> connect_room(room_vector_[i] -> get_closest_room(room_vector_));
    }
}


void Game_map::process_map(sf::RenderWindow *window){
    randomize_map(map_fill_percentage_);
    smooth_map(NUM_ITERATIONS_SMOOTH);
    room_vector_ = generate_rooms();
    //connect_closest_rooms();
    std::cout << "number of rooms: " << room_vector_.size() << std::endl;
    for(const auto& r: room_vector_){
        //std::cout << "connected rooms: " << r -> connected_rooms_.size() << std::endl;
    }
    for(const auto& r: room_vector_){
        //std::cout << "nodes size: " << r -> node_vector_.size() <<
        //", boundary nodes size: " << r -> boundary_nodes_.size() << std::endl;
        if(r -> boundary_nodes_.empty()){
            //std::cout << "room size: " << r -> node_vector_.size() <<
            //", boundary size: " << r -> boundary_nodes_.size() << std::endl;
            for(const auto& n: r -> node_vector_){
                //std::cout << "x: " << n -> x_ << ", y: " << n -> y_ <<
                //", is on boundary: " << is_on_boundary(n -> y_, n -> x_) << std::endl;
            }
        }
    }

    int cnt = 0;
    //int cnt = count_connected_componenets(room_vector_);
    //std::cout << "CNT: " << cnt << std::endl;
    connect_rooms(room_vector_);
    //cnt = count_connected_componenets(room_vector_);
    //std::cout << "CNT: " << cnt << std::endl;

    //draw_room_connections(window);
    smooth_map(NUM_ITERATIONS_SMOOTH);
    //cnt = count_connected_componenets(room_vector_);
    //std::cout << "CNT: " << cnt << std::endl;
    create_passageways();
    cnt = count_connected_componenets(room_vector_);
    std::cout << "CNT before: " << cnt << std::endl;
    remove_connected_components(room_vector_);
    cnt = count_connected_componenets(room_vector_);
    std::cout << "CNT after: " << cnt << std::endl;
    //smooth_map(NUM_ITERATIONS_SMOOTH);
    ///connect_rooms(room_vector_);
    //create_passageways();
    ///connect_rooms(room_vector_);
    //create_boundaries();
}


void Game_map::draw_room_connections(sf::RenderWindow& window){
    for(int i = 0; i < room_vector_.size(); ++i){
        Room *curr = room_vector_[i];
        for(auto& r: room_vector_[i] -> connected_rooms_){
            sf::VertexArray line(sf::LinesStrip, 2);
            //int rand_index_0 = rand() % curr -> node_vector_.size();
            //int rand_index_1 = rand() % r -> node_vector_.size();
            int rand_index_0 = 0;
            int rand_index_1 = 0;
            line[0].position = sf::Vector2f(curr -> node_vector_[rand_index_0] -> x_ * tile_width_in_pixels_ + OFFSET_X, curr -> node_vector_[rand_index_0] -> y_ * tile_width_in_pixels_ + OFFSET_Y);
            line[1].position = sf::Vector2f(r -> node_vector_[rand_index_1] -> x_ * tile_width_in_pixels_ + OFFSET_X, r -> node_vector_[rand_index_1] -> y_ * tile_width_in_pixels_ + OFFSET_Y);
            line[0].color = sf::Color(255, 0, 0);
            line[1].color = sf::Color(255, 0, 0);
            window.draw(line);
        }
    }
}


void Game_map::create_boundaries(){
    for(int i = 0; i < height(); ++i){
        for(int j = 0; j < width(); ++j){
            if((i == 0) || (i == height() - 1) || (j == 0) || (j == width() - 1)){
                char_map_[i][j] = '1';
            }
        }
    }
}


/*
void Game_map::transform_map(){
    for(int i = 0; i < height(); ++i){
        for(int j = 0; j < width(); ++j){
            char curr = char_map_[i][j];
            if()
        }
    }
}
*/

void Game_map::init_sprites(Application *app){
    game_map_vertical_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_vertical_sprite_.setTextureRect(sf::IntRect(0, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_horizontal_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_horizontal_sprite_.setTextureRect(sf::IntRect(1 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_top_left_corner_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_top_left_corner_sprite_.setTextureRect(sf::IntRect(2 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_top_right_corner_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_top_right_corner_sprite_.setTextureRect(sf::IntRect(3 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_bottom_right_corner_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_bottom_right_corner_sprite_.setTextureRect(sf::IntRect(4 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_bottom_left_corner_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_bottom_left_corner_sprite_.setTextureRect(sf::IntRect(5 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_top_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_top_sprite_.setTextureRect(sf::IntRect(7 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_right_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_right_sprite_.setTextureRect(sf::IntRect(8 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_left_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_left_sprite_.setTextureRect(sf::IntRect(9 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_bottom_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_bottom_sprite_.setTextureRect(sf::IntRect(10 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_left_cap_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_left_cap_sprite_.setTextureRect(sf::IntRect(11 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_top_cap_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_top_cap_sprite_.setTextureRect(sf::IntRect(12 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_right_cap_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_right_cap_sprite_.setTextureRect(sf::IntRect(13 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    game_map_bottom_cap_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    game_map_bottom_cap_sprite_.setTextureRect(sf::IntRect(14 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    floor_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    floor_sprite_.setTextureRect(sf::IntRect(6 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    wall_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    wall_sprite_.setTextureRect(sf::IntRect(15 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

    brown_sprite_.setTexture(app -> resource_holder -> textures -> get_resource(Texture_name::game_map_texture));
    brown_sprite_.setTextureRect(sf::IntRect(16 * MAP_TILE_WIDTH_IN_PIXELS, 0, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS));

}
