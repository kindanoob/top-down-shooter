

#include "entity.h"
#include "util.h"
#include "config.h"



void Entity::draw(sf::RenderWindow &window){
    animation_manager().draw(window, this);
}


bool Entity::check_collision_with_map2(std::vector<std::vector<char> > &game_map){
    double x = get_x();
    double y = get_y() - INFO_RECT_SHAPE_HEIGHT;
    bool found_collision = false;
    for(int i = (x - get_BB_w() / 2) / MAP_TILE_WIDTH_IN_PIXELS; i <= (x + get_BB_w() / 2) / MAP_TILE_WIDTH_IN_PIXELS; ++i){
        for(int j = (y - get_BB_h() / 2) / MAP_TILE_HEIGHT_IN_PIXELS; j <= (y + get_BB_h() / 2) / MAP_TILE_HEIGHT_IN_PIXELS; ++j){
            char curr = game_map[j][i];
            if(!Util::is_collision_obstacle(curr)){
                continue;
            }
            sf::FloatRect curr_rect = sf::FloatRect(i * MAP_TILE_WIDTH_IN_PIXELS, j * MAP_TILE_HEIGHT_IN_PIXELS + INFO_RECT_SHAPE_HEIGHT, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS);
            if(Util::check_collision(curr_rect, get_position(), 16)){
                //std::cout << "found collision, x: " << x << ", y: " << y << ", rect center x: " <<
                //i * MAP_TILE_WIDTH_IN_PIXELS + 16 << ", rect center y: " << j * MAP_TILE_HEIGHT_IN_PIXELS + 16 <<
                //", char: " << curr << ", i: " << i << ", j: " << j << std::endl;
                sf::Vector2f new_pos = Util::resolve_collision(curr_rect, get_position(), 16);
                get_sprite().setPosition(new_pos);
                set_x(new_pos.x);
                set_y(new_pos.y);
            }
        }
    }
    set_dx(0);
    set_dy(0);
    return found_collision;
}


bool Entity::check_collision_with_map(std::vector<std::vector<char> > &game_map, Collision_direction dir){
    double x = get_x();
    double y = get_y() - INFO_RECT_SHAPE_HEIGHT;
    bool found_collision = false;
    for(int i = (x - get_BB_w() / 2) / MAP_TILE_WIDTH_IN_PIXELS; i < (x + get_BB_w() / 2) / MAP_TILE_WIDTH_IN_PIXELS; ++i){
        for(int j = (y - get_BB_h() / 2) / MAP_TILE_HEIGHT_IN_PIXELS; j < (y + get_BB_h() / 2) / MAP_TILE_HEIGHT_IN_PIXELS; ++j){

            //std::cout << "i: " << i << ", j: " << j << ", x: " << x << ", y: " << y <<
            //", w: " << get_BB_w() << ", h: " << get_BB_h() << std::endl;
            //std::cout << "new x: " << get_BB_x() << std::endl;std::endl;
            //std::cout << "i: " << i << ", j: " << j << ", x: " << x << ", y: " << y <<
            //", w: " << get_BB_w() << ", h: " << get_BB_h() << std::endl;
            if((i < 0) || (j < 0)){
                //std::cout << "i: " << i << ", j: " << j << ", x: " << x << ", y: " << y <<
                //", w: " << get_BB_w() << ", h: " << get_BB_h() << std::endl;
            }
            char curr = game_map[j][i];
            sf::FloatRect curr_rect = sf::FloatRect(i * MAP_TILE_WIDTH_IN_PIXELS, j * MAP_TILE_HEIGHT_IN_PIXELS, MAP_TILE_WIDTH_IN_PIXELS, MAP_TILE_HEIGHT_IN_PIXELS);
            bool found = false;

            if(dir == Collision_direction::horizontal){
                /*
                if(Util::is_horizontal_collision_obstacle(curr)){
                    if(get_dx() > 0 * EPSILON){
                        set_x(i * MAP_TILE_WIDTH_IN_PIXELS - get_BB_w() / 2);
                    }
                    else if(get_dx()  < -EPSILON){
                        set_x((i + 1) * MAP_TILE_WIDTH_IN_PIXELS + get_BB_w() / 2);
                    }
                    found_collision = true;
                    found = true;
                    //break;
                }
                */
                switch(curr){
                    case 'V':{
                        if(get_dx() > EPSILON){
                            set_x(i * MAP_TILE_WIDTH_IN_PIXELS - get_BB_w() / 2);
                        }
                        else if(get_dx()  < -EPSILON){
                            set_x((i + 1) * MAP_TILE_WIDTH_IN_PIXELS + get_BB_w() / 2);
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'E':{
                        //std::cout << "vertical, dx: " << get_dx() << std::endl;
                        if(get_dx() > 0){
                            set_x(i * MAP_TILE_WIDTH_IN_PIXELS - get_BB_w() / 2);
                            //std::cout << "collision, x: " << x << ", y: " << y << ", i: " << i <<
                            //", j: " << j << ", w: " << get_BB_w() << ", h: " << get_BB_h() << std::endl;
                            //std::cout << "new x: " << get_BB_x() << std::endl;
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'F':{
                        if(get_dx()  < 0){
                            set_x((i + 1) * MAP_TILE_WIDTH_IN_PIXELS + get_BB_w() / 2);
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'A':{
                        if(x < curr_rect.left - 12){
                            if(get_dx() > EPSILON){
                                set_x(i * MAP_TILE_WIDTH_IN_PIXELS - get_BB_w() / 2);
                            }
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                    case 'D':{
                        if(x < curr_rect.left - 12){
                            if(get_dx() > EPSILON){
                                set_x(i * MAP_TILE_WIDTH_IN_PIXELS - get_BB_w() / 2);
                            }
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                    case 'B':{
                        if(x > curr_rect.left + MAP_TILE_WIDTH_IN_PIXELS + 12){
                            //std::cout << "in B" << std::endl;
                            if(get_dx()  < -EPSILON){
                                set_x((i + 1) * MAP_TILE_WIDTH_IN_PIXELS + get_BB_w() / 2);
                            }
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                    case 'C':{
                        if(x > curr_rect.left + MAP_TILE_WIDTH_IN_PIXELS + 12){
                            if(get_dx()  < -EPSILON){
                                set_x((i + 1) * MAP_TILE_WIDTH_IN_PIXELS + get_BB_w() / 2);
                            }
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                    case 'J':{
                        //if((get_y() > curr_rect.top) && (get_y() < curr_rect.top + MAP_TILE_HEIGHT_IN_PIXELS) && (get_dx() > 0)){
                        if(get_dx() > 0){
                            set_x(i * MAP_TILE_WIDTH_IN_PIXELS - get_BB_w() / 2);
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'L':{
                        //if((get_y() > curr_rect.top) && (get_y() < curr_rect.top + MAP_TILE_HEIGHT_IN_PIXELS) && (get_dx() < 0)){
                        if(get_dx() < 0){
                            set_x((i + 1) * MAP_TILE_WIDTH_IN_PIXELS + get_BB_w() / 2);
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'K':{
                        if(y > curr_rect.top + 12){
                        //if((x < curr_rect.left - 15) || (x > curr_rect.left + MAP_TILE_WIDTH_IN_PIXELS + 15)){
                           if(get_dx() > 0){
                                set_x(i * MAP_TILE_WIDTH_IN_PIXELS - get_BB_w() / 2);
                            }
                            else if(get_dx()  < 0){
                                set_x((i + 1) * MAP_TILE_WIDTH_IN_PIXELS + get_BB_w() / 2);
                            }
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                    case 'M':{
                        //std::cout << "in M" << std::endl;
                        //std::cout << "dx > 0, dy: " << get_dy() << std::endl;
                        //std::cout << "x: " << get_x() << ", y: " << get_y() << ", left: " <<
                        //curr_rect.top << ", left + w: " << curr_rect.left + 48 << std::endl;
                        if(y < curr_rect.top + MAP_TILE_HEIGHT_IN_PIXELS + 12){
                            std::cout << "GOOD" << std::endl;

                        //if((get_x() < curr_rect.left - 15) || (get_x() > curr_rect.left + MAP_TILE_WIDTH_IN_PIXELS + 15)){
                            if(get_dx() > 0){

                                set_x(i * MAP_TILE_WIDTH_IN_PIXELS - get_BB_w() / 2);
                            }
                            else if(get_dx()  < 0){
                                std::cout << "dx < 0, dy: " << get_dy() << std::endl;
                                std::cout << "x: " << get_x() << ", y: " << get_y() << ", left: " <<
                                curr_rect.left << ", left + w: " << curr_rect.left + 32 << std::endl;
                                set_x((i + 1) * MAP_TILE_WIDTH_IN_PIXELS + get_BB_w() / 2);
                            }
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                }
            }
            else if(dir == Collision_direction::vertical){
                /*
                if(Util::is_vertical_collision_obstacle(curr)){
                    if(get_dy() > 0){
                        set_y(INFO_RECT_SHAPE_HEIGHT + j * MAP_TILE_HEIGHT_IN_PIXELS - get_BB_h() / 2);
                    }
                    else if(get_dy() < 0){
                        set_y(INFO_RECT_SHAPE_HEIGHT + (j + 1) * MAP_TILE_HEIGHT_IN_PIXELS + get_BB_h() / 2);
                    }
                    found_collision = true;
                    found = true;
                    //break;
                }
                */
                switch(curr){
                    case 'H':{
                        //std::cout << "found H with dy: " << get_dy() << std::endl;
                        if(get_dy() > 0){
                            std::cout << "in H vertical" << std::endl;
                            set_y(INFO_RECT_SHAPE_HEIGHT + j * MAP_TILE_HEIGHT_IN_PIXELS - get_BB_h() / 2);
                        }
                        else{
                            set_y(INFO_RECT_SHAPE_HEIGHT + (j + 1) * MAP_TILE_HEIGHT_IN_PIXELS + get_BB_h() / 2);
                        }

                        found_collision = true;
                        found = true;
                        break;
                    }

                    case 'G':{
                        if(get_dy() > 0){
                            set_y(INFO_RECT_SHAPE_HEIGHT + j * MAP_TILE_HEIGHT_IN_PIXELS - get_BB_h() / 2);
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'I':{
                        if(get_dy() < EPSILON){

                            //std::cout << "collision, x: " << x << ", y: " << y << ", i: " << i <<
                            //", j: " << j << ", w: " << get_w() << ", h: " << get_h() << std::endl;
                            set_y(INFO_RECT_SHAPE_HEIGHT + (j + 1) * MAP_TILE_HEIGHT_IN_PIXELS + get_BB_h() / 2);
                            //std::cout << "new y: " << get_y() << std::endl;
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'A':{
                        if(get_dy() > 0){
                            //std::cout << "QQ A" << std::endl;
                            set_y(INFO_RECT_SHAPE_HEIGHT + j * MAP_TILE_HEIGHT_IN_PIXELS - get_BB_h() / 2);
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                    case 'B':{
                        if(get_dy() > 0){
                            //std::cout << "in B vertical" << std::endl;
                            //std::cout << "QQ" << std::endl;
                            set_y(INFO_RECT_SHAPE_HEIGHT + j * MAP_TILE_HEIGHT_IN_PIXELS - get_BB_h() / 2);
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                    case 'C':{
                        if(get_dy() < 0){
                            set_y(INFO_RECT_SHAPE_HEIGHT + (j + 1) * MAP_TILE_HEIGHT_IN_PIXELS + get_BB_h() / 2);
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'D':{
                        if(get_dy() < 0){
                            set_y(INFO_RECT_SHAPE_HEIGHT + (j + 1) * MAP_TILE_HEIGHT_IN_PIXELS + get_BB_h() / 2);
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'J':{
                        std::cout << "in J" << std::endl;
                        if(get_x() > curr_rect.left - 12){
                        //if((y < curr_rect.top - 16) || (y > curr_rect.top + MAP_TILE_HEIGHT_IN_PIXELS + 16)){
                            if(get_dy() > 0){
                                set_y(INFO_RECT_SHAPE_HEIGHT + j * MAP_TILE_HEIGHT_IN_PIXELS - get_BB_h() / 2);
                            }
                            else if(get_dy() < 0){
                                set_y(INFO_RECT_SHAPE_HEIGHT + (j + 1) * MAP_TILE_HEIGHT_IN_PIXELS + get_BB_h() / 2);
                            }
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                    case 'L':{
                        std::cout << "in L" << std::endl;
                        if(x < curr_rect.left + MAP_TILE_WIDTH_IN_PIXELS + 12){
                        //if((get_y() < curr_rect.top - 16) || (get_y() > curr_rect.top + MAP_TILE_HEIGHT_IN_PIXELS + 16)){
                            if(get_dy() > 0){
                                std::cout << "dy > 0, dx: " << get_dx() << std::endl;
                                set_y(INFO_RECT_SHAPE_HEIGHT + j * MAP_TILE_HEIGHT_IN_PIXELS - get_BB_h() / 2);
                            }
                            else if(get_dy() < 0){
                                std::cout << "dy < 0, dx: " << get_dx() << std::endl;
                                set_y(INFO_RECT_SHAPE_HEIGHT + (j + 1) * MAP_TILE_HEIGHT_IN_PIXELS + get_BB_h() / 2);
                            }
                            found_collision = true;
                            found = true;
                            break;
                        }
                    }
                    case 'K':{
                        if(get_dy() > 0){
                            set_y(INFO_RECT_SHAPE_HEIGHT + j * MAP_TILE_HEIGHT_IN_PIXELS - get_BB_h() / 2);
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                    case 'M':{
                        if(get_dy() < 0){
                            set_y(INFO_RECT_SHAPE_HEIGHT + (j + 1) * MAP_TILE_HEIGHT_IN_PIXELS + get_BB_h() / 2);
                        }
                        found_collision = true;
                        found = true;
                        break;
                    }
                }
            }
            if(found){
                get_sprite().setPosition(sf::Vector2f(get_x(), get_y()));
            }
        }
    }

    ///Set dx and dy to zero here! Do it only after last check, currently it is vertical one
    ///To see which check is last, refer to update() function from play_state.cpp
    if(dir == Collision_direction::vertical){
        set_dy(0);
    }
    else if(dir == Collision_direction::horizontal){
        set_dx(0);
    }
    //std::cout << "here" << std::endl;
    return found_collision;
}



void Entity::update_offset_x(){
    if ((get_x() > SCREEN_WIDTH / 2) && (get_x() < MAP_WIDTH_IN_PIXELS - SCREEN_WIDTH / 2 )){
        set_offset_x(get_x() - SCREEN_WIDTH / 2);
        //std::cout << "x: " << get_x() << ", w / 2: " << SCREEN_WIDTH / 2 <<
        //", w - sw / 2: " << GAME_MAP_WIDTH - SCREEN_WIDTH / 2 << std::endl;
    }
    else if(get_x() <= SCREEN_WIDTH / 2){
        set_offset_x(0);
    }
    else if(get_x() >= MAP_WIDTH_IN_PIXELS - SCREEN_WIDTH / 2){
        set_offset_x(MAP_WIDTH_IN_PIXELS - SCREEN_WIDTH);
    }
}

void Entity::update_offset_y(){
    if ((get_y() > SCREEN_HEIGHT / 2) && (get_y() < MAP_HEIGHT_IN_PIXELS - SCREEN_HEIGHT / 2 )){
        set_offset_y(get_y() - SCREEN_HEIGHT / 2);
    }
    else if(get_y() <= SCREEN_HEIGHT / 2){
        set_offset_y(0);
    }
    else if(get_y() >= MAP_HEIGHT_IN_PIXELS - SCREEN_HEIGHT / 2){
        set_offset_y(MAP_HEIGHT_IN_PIXELS - SCREEN_HEIGHT);
    }
}



/*
void Entity::check_collision_with_ball(Entity *b){
    double d = dist_squared(get_x(), get_y(), b -> get_x(), b -> get_y());
    double sum_radius = get_r() + b -> get_r();
    double cutoff = sum_radius * sum_radius;
    if(d > cutoff){
        return;
    }
    double shift = get_r() + b -> get_r() - dist(get_x(), get_y(), b -> get_x(), b -> get_y());
    double v_x = get_x() - b -> get_x();
    double v_y = get_y() - b -> get_y();
    double len = length(v_x, v_y);
    v_x /= len;
    v_y /= len;
    v_x *= shift;
    v_y *= shift;
    set_x(get_x() + v_x);
    set_y(get_y() + v_y);

    //double center_x = get_x() - b -> get_x();
    //double center_y = get_y() - b -> get_y();
    //double dot_prod = dot_product(get_dx() - b -> get_dx(), get_dy() - b -> get_dy(), center_x, center_y);
    //double d_centers = dist_squared(get_x(), get_y(), b -> get_x(), b -> get_y());

    //set_dx(get_dx() - center_x * dot_prod / d_centers);
    //b -> set_dx(b -> get_dx() + center_x * dot_prod / d_centers);
    //set_dy(get_dy() - center_y * dot_prod / d_centers);
    //b -> set_dy(b -> get_dy() + center_y * dot_prod / d_centers);
}
*/
