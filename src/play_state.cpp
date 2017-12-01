#include <iostream>
#include <sstream>

#include "application.h"
#include "display.h"
#include "play_state.h"
//#include "delay_state.h"
#include "game_over_state.h"
#include "entity.h"
#include "enemy.h"
#include "enemy_easy.h"
#include "enemy_mediuim.h"
#include "bullet.h"
#include "player.h"
#include "texture_manager.h"
#include "font_manager.h"
#include "sound_manager.h"
#include "music_manager.h"
#include "resource_holder.h"
#include "util.h"
#include "game_map.h"
#include "mini_map.h"



Play_state::Play_state(Application *app): Game_state(app){
    std::cout << "Play_state()" << std::endl;
    game_map_ = new Game_map(MAP_WIDTH_IN_TILES, MAP_HEIGHT_IN_TILES,
                             MAP_FILL_PERCENTAGE, MAP_TILE_WIDTH_IN_PIXELS,
                             MAP_TILE_HEIGHT_IN_PIXELS, app);
    //entity_list = new std::list<Entity *>;
    init_entities(app);
    info_rect_shape().setSize(sf::Vector2f(SCREEN_WIDTH, INFO_RECT_SHAPE_HEIGHT));
    info_rect_shape().setPosition(INFO_RECT_SHAPE_INITIAL_POSITION);
    info_rect_shape().setFillColor(INFO_RECT_COLOR);
    set_info_rect_shape_initial_position(INFO_RECT_SHAPE_INITIAL_POSITION);
    player_info_text().setFont(app -> resource_holder -> fonts -> get_resource(Font_name::ubuntu_font));
    player_info_text().setPosition(INFO_TEXT_INITIAL_POSITION);
    player_info_text().setCharacterSize(PLAYER_INFO_TEXT_SIZE);
    player_info_text().setColor(sf::Color::Black);
    set_info_text_initial_position(INFO_TEXT_INITIAL_POSITION);
    //auto s = player -> animation_manager().get_current_animation().sprite;
    //std::cout << "in Play_state() player sprite pos: " << s.getPosition().x << ", " <<
    //s.getPosition().y << std::endl;

    //play_music(app);
    mini_map = new Mini_map();
};


Play_state::~Play_state(){
    std::cout << "~Play_state()" << std::endl;
}


///is called right after Play_state is pushed onto the stack
void Play_state::init(Application *app){
    player -> set_health(PLAYER_HEALTH);
    player -> set_is_alive(true);
    set_initial_enemy_spawn(true);
    //player -> set_x(PLAYET_INITIAL_X_POSITION);
    //player -> set_y(PLAYET_INITIAL_Y_POSITION);
    app -> display -> set_mouse_cursor_visible(false);
    play_state_clock().restart();
}


void Play_state::input(){
    //player_paddle -> get_player_input();
    //bot_paddle -> get_computer_move(ball);
};


void Play_state::input(const sf::Event &event){
    //
};


void Play_state::input(Application *app){
    sf::Event event;
    while(app -> display -> window -> pollEvent(event)){
        if(event.type == sf::Event::Closed){
            app -> display -> window -> close();
            //destroy();
            //return;
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                player -> set_is_shooting(true);
                //if(player -> shoot_duration() > player -> shoot_duration_in_milliseconds()){
                    //player -> set_shoot_duration_in_milliseconds(0);
                //}
                //player -> shoot_sound().play();
            }
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::M){
                if(show_mini_map()){
                    set_show_mini_map(false);
                }
                else{
                    set_show_mini_map(true);
                }
                //std::cout << "Now show_mini_map is " << show_mini_map() << std::endl;

            }
        }
    }
    player -> get_input_from_player(app -> display -> window);
}


void Play_state::update(double dt, Application *app){

    auto s = player -> animation_manager().get_current_animation().sprite;
    //std::cout << "in update() before player sprite pos: " << s.getPosition().x << ", " <<
    //s.getPosition().y << std::endl;
    //std::cout << "AAA " << player -> get_x() << ", " << player -> get_y() << std::endl;
    //play_music(app);
    //player -> play_shoot_sound();
    //sf::SoundBuffer buff;
    //buff.loadFromFile("resources/sounds/player_shoot1.wav");;
    //sf::Sound sound;
    //sound.setBuffer(buff);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
     //   sound.play();
    //}
    ///update stuff
    update_info_text(app);
    update_enemy_population(app -> resource_holder -> textures -> get_resource(Texture_name::enemy_easy_texture), app -> resource_holder -> textures -> get_resource(Texture_name::enemy_medium_texture));
    //s = player -> animation_manager().get_current_animation().sprite;
    //std::cout << "in update() QQ offset player sprite pos: " << s.getPosition().x << ", " <<
    //s.getPosition().y << std::endl;
    player -> update(dt);
    player -> set_aftershot_delay(player -> aftershot_delay() + play_state_clock().getElapsedTime().asMilliseconds());



    for(auto& e: enemy_list){
        double x = player -> get_x() - e -> get_x();
        double y = player -> get_y() - e -> get_y();
        double temp_angle = atan2(y, x);
        double enemy_angle = temp_angle / PI * 180;
        e -> set_player_angle(enemy_angle);
        e -> update(dt);
        //std::cout << "enemy: " << e << ", dx: " << e -> get_dx() << ", dy: " <<
        //e -> get_dy() << std::endl;
    }

    for(auto& b: bullet_list){
        b -> set_player_x(player -> get_x());
        b -> set_player_y(player -> get_y());
        b -> update(dt);
        b -> check_collision_with_map(game_map() -> char_map());
    }

    ///create new bullets
    if(player -> get_is_shooting()){
        player -> set_aftershot_delay(0);
        sf::FloatRect rect = player -> get_sprite().getGlobalBounds();
        double bullet_x = player -> get_gun_x();
        double bullet_y = player -> get_gun_y();
        sf::Vector2f player_dir_vec = -player -> get_position() + player -> get_gun();
        double len = Util::len(player_dir_vec);
        player_dir_vec.x *= 24 / len;
        player_dir_vec.y *= 24 / len;
        bullet_x += player_dir_vec.x;
        bullet_y += player_dir_vec.y;
        double phi = player -> get_sprite().getRotation();
        double bullet_dx = BULLET_DX * cos(player -> get_sprite().getRotation() / 180.0 * PI);
        double bullet_dy = BULLET_DY * sin(player -> get_sprite().getRotation() / 180.0 * PI);
        int bullet_angle = 0;
        bullet_list.push_back(new Bullet(bullet_x, bullet_y, 16, 16, bullet_dx, bullet_dy, bullet_angle, 0, PLAYER_DAMAGE, app -> resource_holder -> textures -> get_resource(Texture_name::bullet_texture), 0, 0));
        //if(true){
            //player -> play_shoot_sound();
        //}

        ///gun knockback after player shoots
        {
            sf::Vector2f player_dir_vec = -player -> get_position() + player -> get_gun();
            double len = Util::len(player_dir_vec);
            player_dir_vec.x *= PLAYER_GUN_KNOCKBACK_DISTANCE / len;
            player_dir_vec.y *= PLAYER_GUN_KNOCKBACK_DISTANCE / len;
            double phi = player -> get_sprite().getRotation();
            while(phi > 90){
                phi -= 90;
            }
            player_dir_vec.x *= -cos(phi / 180.0 * PI);
            player_dir_vec.y *= -sin(phi / 180.0 * PI);
            player -> set_x(player -> get_x() + player_dir_vec.x);
            player -> set_y(player -> get_y() + player_dir_vec.y);
            //std::cout << "angle: " << player -> get_sprite().getRotation() << ", sin: " <<
            //sin(player -> get_sprite().getRotation() / 180.0 * PI) << ", cos: " <<
            //cos(player -> get_sprite().getRotation() / 180.0 * PI) <<
            //", dir x: " << player_dir_vec.x << ", dir y: " << player_dir_vec.y << std::endl;
        }
        player -> set_is_shooting(false);
    }


    ///check collisions
    //player -> check_collision_with_map(game_map() -> char_map());
    //player -> check_collision_with_map(game_map() -> char_map(), Collision_direction::horizontal);
    //player -> check_collision_with_map(game_map() -> char_map(), Collision_direction::vertical);
    player -> check_collision_with_map2(game_map() -> char_map());

    for(auto& e: enemy_list){
        player -> check_collision_with_enemy(e);
        e -> check_collision_with_map2(game_map() -> char_map());
    }
    bool found_collision = false;
    int NUM_ITER = 10;
    for(int i = 0; i < NUM_ITER; ++i){
        for(auto it = enemy_list.begin(); it != enemy_list.end(); ++it){
            player -> check_collision_with_enemy(*it);
            //(*it) -> check_collision_with_player(player);
            player -> check_collision_with_map2(game_map() -> char_map());
            (*it) -> check_collision_with_map2(game_map() -> char_map());
            //player -> check_collision_with_map(game_map() -> char_map(), Collision_direction::horizontal);
            //player -> check_collision_with_map(game_map() -> char_map(), Collision_direction::vertical);
            //(*it) -> check_collision_with_map(game_map() -> char_map(), Collision_direction::horizontal);
            //(*it) -> check_collision_with_map(game_map() -> char_map(), Collision_direction::vertical);
            for(auto it2 = enemy_list.begin(); it2 != enemy_list.end(); ++it2){
                if(it != it2){
                    (*it) -> check_collision_with_enemy(*it2);
                    (*it) -> check_collision_with_map2(game_map() -> char_map());
                    (*it2) -> check_collision_with_map2(game_map() -> char_map());
                    //(*it2) -> check_collision_with_enemy(*it);
                    //player -> check_collision_with_enemy(*it);
                    //player -> check_collision_with_enemy(*it2);
                    //(*it) -> check_collision_with_player(player);
                    //(*it2) -> check_collision_with_player(player);
                    //(*it) -> check_collision_with_map(game_map() -> char_map(), Collision_direction::horizontal);
                    //(*it) -> check_collision_with_map(game_map() -> char_map(), Collision_direction::vertical);
                    //(*it2) -> check_collision_with_map(game_map() -> char_map(), Collision_direction::horizontal);
                    //(*it2) -> check_collision_with_map(game_map() -> char_map(), Collision_direction::vertical);
                    //player -> check_collision_with_map(game_map() -> char_map(), Collision_direction::horizontal);
                    //player -> check_collision_with_map(game_map() -> char_map(), Collision_direction::vertical);

                }
            }
        }
    }



    //player -> check_collision_with_map(game_map() -> char_map());


    //std::cout << "TIME: " << play_state_clock().getElapsedTime().asMilliseconds() << std::endl;
    ///update bullets duration and check for animation switch
    for(auto& b: bullet_list){
        b -> set_alive_duration(b -> alive_duration() + play_state_clock().getElapsedTime().asMilliseconds());
        //std::cout << "DURATION: " << b -> alive_duration() << std::endl;
        if(b -> alive_duration() > BULLET_FIRE_ANIMATION_DURATION_IN_MILLISECONDS){
        //if(b -> ticks_alive_ > 20){
            b -> set_bounding_box(sf::FloatRect(0, 0, 16, 16));
            b -> set_animation("bullet_default_animation");
        }
        //else{
        else if(b -> animation_manager().current_animation == "bullet_fire_animation"){
            b -> get_sprite().setTextureRect(sf::IntRect(0, 0, 24, 24));
            b -> get_sprite().setOrigin(sf::Vector2f(12, 12));
            sf::Vector2f dir = player -> get_gun() - sf::Vector2f(player -> get_x(), player -> get_y());
            double len = sqrt(dir.x * dir.x + dir.y * dir.y);
            dir.x *= 12 / len;
            dir.y *= 12 / len;
            b -> get_sprite().setPosition(player -> get_gun() + dir);
        }
    }

    ///set dead objects, delete dead bullets

    for(auto it = enemy_list.begin(); it != enemy_list.end();++it){
        for(auto it2 = bullet_list.begin(); it2 != bullet_list.end();){
            double d = Util::dist((*it2) -> get_x(), (*it2) -> get_y(), (*it) -> get_x(), (*it) -> get_y());
            if(d <= (*it2) -> get_BB_h() + (*it) -> get_BB_h()){
                if((*it) -> get_is_alive()){
                    (*it) -> set_health((*it) -> get_health() - (*it2) -> get_damage());
                    if((*it) -> get_health() <= 0){
                        if((*it) -> get_type() == Enemy_type::enemy_easy){
                            app -> set_player_score(app -> player_score() + SCORE_REWARD_ENEMY_EASY);
                        }
                        else if((*it) -> get_type() == Enemy_type::enemy_medium){
                            app -> set_player_score(app -> player_score() + SCORE_REWARD_ENEMY_MEDIUM);
                        }
                        (*it) -> set_is_alive(false);
                    }
                }
                Bullet *temp = *it2;
                it2 = bullet_list.erase(it2);
                delete(temp);
            }
            else{
                ++it2;
            }
        }
    }

    if(player -> get_health() <= 0){
        player -> set_is_alive(false);
    }

    ///delete dead objects
    for(auto it = bullet_list.begin(); it != bullet_list.end();){
        if((*it) -> get_is_alive()){
            ++it;
        }
        else{
            Bullet *temp = *it;
            it = bullet_list.erase(it);
            delete(temp);
        }
    }

    for(auto it = enemy_list.begin(); it != enemy_list.end(); ++it){
        if(!((*it) -> get_is_alive())){
            Enemy *temp = *it;
            it = enemy_list.erase(it);
            delete(temp);
        }
    }




    ///update player offset
    player -> update_offset_x();
    player -> update_offset_y();

    //if(player -> aftershot_delay() < AFTERSHOT_DELAY_IN_MILLISECONDS){
    if(false){
        //sf::Vector2f player_dir_vec = -player -> get_position() + player -> get_gun();
        int rand_x = (rand() % MODULO) - 2 * MODULO;
        int rand_y = (rand() % MODULO) - 2 * MODULO;
        sf::Vector2f screenshake_dir_vec = sf::Vector2f(rand_x, rand_y);
        double len = Util::len(screenshake_dir_vec);
        screenshake_dir_vec.x *= AFTERSHOT_OFFSET_IN_PIXELS / len;
        screenshake_dir_vec.y *= AFTERSHOT_OFFSET_IN_PIXELS / len;
        screenshake_dir_vec.x *= -cos(player -> get_sprite().getRotation() / 180.0 * PI);
        screenshake_dir_vec.y *= -sin(player -> get_sprite().getRotation() / 180.0 * PI);
        player -> set_offset_x(player -> get_offset_x() + screenshake_dir_vec.x);
        player -> set_offset_y(player -> get_offset_y() + screenshake_dir_vec.y);
        std::cout << "angle: " << player -> get_sprite().getRotation() << ", sin: " <<
        sin(player -> get_sprite().getRotation() / 180.0 * PI) << ", cos: " <<
        cos(player -> get_sprite().getRotation() / 180.0 * PI) << ", new offset: " << player -> get_offset_x() << ", " <<
        player -> get_offset_y() << ", dir x: " << screenshake_dir_vec.x << ", dir y: " <<
        screenshake_dir_vec.y << std::endl;
    }
    if(player -> aftershot_delay() < 0){
        //
    }
    else if(player -> aftershot_delay() < AFTERSHOT_DELAY_IN_MILLISECONDS){
        sf::Vector2f screenshake_dir_vec = sf::Vector2f(0, 1);
        screenshake_dir_vec.x *= AFTERSHOT_OFFSET_IN_PIXELS;
        screenshake_dir_vec.y *= AFTERSHOT_OFFSET_IN_PIXELS;
        player -> set_offset_x(player -> get_offset_x() + screenshake_dir_vec.x);
        player -> set_offset_y(player -> get_offset_y() + screenshake_dir_vec.y);
    }
    else if((player -> aftershot_delay() > 2 * AFTERSHOT_DELAY_IN_MILLISECONDS) &&
    (player -> aftershot_delay() < 3 * AFTERSHOT_DELAY_IN_MILLISECONDS)){
        sf::Vector2f screenshake_dir_vec = sf::Vector2f(0, -1);
        screenshake_dir_vec.x *= AFTERSHOT_OFFSET_IN_PIXELS;
        screenshake_dir_vec.y *= AFTERSHOT_OFFSET_IN_PIXELS;
        player -> set_offset_x(player -> get_offset_x() + screenshake_dir_vec.x);
        player -> set_offset_y(player -> get_offset_y() + screenshake_dir_vec.y);
    }
    else if((player -> aftershot_delay() > 4 * AFTERSHOT_DELAY_IN_MILLISECONDS) &&
    (player -> aftershot_delay() < 5 * AFTERSHOT_DELAY_IN_MILLISECONDS)){
        sf::Vector2f screenshake_dir_vec = sf::Vector2f(1, 0);
        screenshake_dir_vec.x *= AFTERSHOT_OFFSET_IN_PIXELS;
        screenshake_dir_vec.y *= AFTERSHOT_OFFSET_IN_PIXELS;
        player -> set_offset_x(player -> get_offset_x() + screenshake_dir_vec.x);
        player -> set_offset_y(player -> get_offset_y() + screenshake_dir_vec.y);
    }
    else if((player -> aftershot_delay() > 6 * AFTERSHOT_DELAY_IN_MILLISECONDS) &&
    (player -> aftershot_delay() < 7 * AFTERSHOT_DELAY_IN_MILLISECONDS)){
        sf::Vector2f screenshake_dir_vec = sf::Vector2f(-1, 0);
        screenshake_dir_vec.x *= AFTERSHOT_OFFSET_IN_PIXELS;
        screenshake_dir_vec.y *= AFTERSHOT_OFFSET_IN_PIXELS;
        player -> set_offset_x(player -> get_offset_x() + screenshake_dir_vec.x);
        player -> set_offset_y(player -> get_offset_y() + screenshake_dir_vec.y);
    }


    ///view is updated here!
    app -> display -> update_view(player -> get_offset_x(), player -> get_offset_y());

    ///update mouse positon w.r.t. new view
    player -> update_mouse_world_position(app);

    //update_score();
    //update_fps_count();

    //player -> update(dt);


    //std::cout << "player health: " << player -> get_health() << std::endl;
    if(!(player -> get_is_alive())){
        app -> display -> view_reset_to_initial_state();
        Game_over_state *new_game_over_state = new Game_over_state(app);
        app -> change_state(new_game_over_state);
        //app -> change_state(app -> game_over_state);
        reset(app);
        delete(this);
        std::cout << "play state popped" << std::endl;
    }
    update_info_panel();
    ///Clock restart is here
    play_state_clock().restart();
};


void Play_state::draw(Application *app){
    app -> display -> clear(PLAY_STATE_BACKGROUND_COLOR);
    //draw_map(app);
    //draw_map2(app);
    draw_player_fov(app);
    //auto s = player -> animation_manager().get_current_animation().sprite;
    //std::cout << "in draw() player sprite pos: " << s.getPosition().x << ", " <<
    //s.getPosition().y << std::endl;
    app -> display -> draw(player -> animation_manager().get_current_animation().sprite);


    for(auto& e: enemy_list){
        app -> display -> draw(e -> animation_manager().get_current_animation().sprite);
    }
    for(auto& b: bullet_list){
        app -> display -> draw(b -> animation_manager().get_current_animation().sprite);
    }
    app -> display -> draw(player -> get_aim_sprite());
    app -> display -> draw(info_rect_shape());
    app -> display -> draw(player_info_text());
    if(show_mini_map()){
        draw_mini_map(app);
    }

};

void Play_state::init_entities(Application *app){
    std::cout << "in init entities" << std::endl;
    create_player(app);
    std::cout << "out init entities" << std::endl;
    //create_font();
    //create_score_text(font, SCORE_TEXT_SIZE);
    //create_fps_count_text(font, SCORE_TEXT_SIZE);
    //init_mini_map_rect_shape();
}


/*
void Play_state::create_field(){
    field_rect.setSize(sf::Vector2f(FIELD_WIDTH, FIELD_HEIGHT));
    field_rect.setPosition(100, 100);
    field_rect.setFillColor(sf::Color::Yellow);
    field_rect.setOutlineThickness(FIELD_BORDER_THICKNESS);
    field_rect.setOutlineColor(sf::Color::Black);
}
*/


/*
void Play_state::create_score_text(const sf::Font &font, const unsigned int text_size){
    //score_text = new sf::Text();
    score_text.setFont(font);
    score_text.setCharacterSize(text_size);
    score_text.setColor(sf::Color::Black);
    score_text.setPosition(OFFSET_X, OFFSET_Y / 2);
    std::ostringstream score_text_stringstream;
    score_text_stringstream << "Player " << application -> player_score << " : " << application -> bot_score << " Bot" << std::endl;
    score_text.setString(score_text_stringstream.str());
}
*/


/*
void Play_state::create_font(){
    font.loadFromFile(FONTS_PATH + "ubuntu.ttf");
}
*/


void Play_state::create_player(Application *app){
    //std::cout << "in play state, create player" << std::endl;
    sf::Texture player_texture = app -> resource_holder -> textures -> get_resource(Texture_name::player_texture);
    sf::Texture player_aim_texture = app -> resource_holder -> textures -> get_resource(Texture_name::player_aim_texture);
    auto r = player_texture.getSize();

    //std::cout << "x: " << r.x << ", y: " << r.y << std::endl;
    //std::vector<std::vector<char> > char_map = game_map() -> char_map();
    bool found = false;
    int player_pox_x = -1;
    int player_pox_y = -1;
    for(int i = 0; i < game_map() -> height(); ++i){
        for(int j = 0; j < game_map() -> width(); ++j){
            if((i > 0) && (i < game_map() -> height() - 1) &&
               (j > 0) && (j < game_map() -> width() - 1) &&
               (game_map() -> char_map()[i][j] == '0') &&
               (game_map() -> char_map()[i + 1][j] == '0') &&
               (game_map() -> char_map()[i - 1][j] == '0') &&
               (game_map() -> char_map()[i][j + 1] == '0') &&
               (game_map() -> char_map()[i][j - 1] == '0') &&
               (game_map() -> char_map()[i + 1][j + 1] == '0') &&
               (game_map() -> char_map()[i + 1][j - 1] == '0') &&
               (game_map() -> char_map()[i - 1][j + 1] == '0') &&
               (game_map() -> char_map()[i - 1][j - 1] == '0')){
                player_pox_x = j * MAP_TILE_WIDTH_IN_PIXELS;
                player_pox_y = i * MAP_TILE_HEIGHT_IN_PIXELS + INFO_RECT_SHAPE_HEIGHT;
                std::cout << "found player pos, i: " << i << ", j: " << j << ", x: " <<
                player_pox_x << ", y: " << player_pox_y << std::endl;
                found = true;
                break;
            }
        }
        if(found){
            break;
        }
    }
    //player = new Player(0, 100, 40, 32, 0, 0, 0, PLAYER_HEALTH, PLAYER_DAMAGE, player_texture, 0, 0, player_aim_texture, 0, 0);
    player = new Player(player_pox_x, player_pox_y, 40, 32, 0, 0, 0, PLAYER_HEALTH, PLAYER_DAMAGE, player_texture, 0, 0, player_aim_texture, 0, 0);  
    
    //player -> set_shoot_sound(app -> resource_holder -> sounds -> get_resource(Sound_name::player_shoot_sound));
    
    //player -> set_shoot_duration_in_milliseconds(app -> resource_holder -> sounds -> get_resource(Sound_name::player_shoot_sound).getDuration().asMilliseconds());
}


/*
void Play_state::update_score(){
    std::ostringstream score_text_stringstream;
    score_text_stringstream << "Player " << application -> player_score << " : " << application -> bot_score << " Bot" << std::endl;
    score_text.setString(score_text_stringstream.str());
    if(std::max(application -> player_score, application -> bot_score) == MATCH_WINNER_SCORE){
        is_initialized = false;
        application -> change_state(application -> game_over_state);
    }
}


void Play_state::create_fps_count_text(const sf::Font &font, const unsigned int text_size){
    fps_count_text.setFont(font);
    fps_count_text.setCharacterSize(text_size);
    fps_count_text.setColor(sf::Color::Black);
    fps_count_text.setPosition(SCREEN_WIDTH - 2 * OFFSET_X, OFFSET_Y / 2);
    //fps_count_text.setPosition(100, 100);
    std::ostringstream fps_count_text_stringstream;
    fps_count_text_stringstream << "FPS: " << application -> fps_count << std::endl;
    fps_count_text.setString(fps_count_text_stringstream.str());
}


void Play_state::update_fps_count(){
    std::ostringstream fps_count_text_stringstream;
    fps_count_text_stringstream << "FPS: " << application -> fps_count << std::endl;
    fps_count_text.setString(fps_count_text_stringstream.str());
}
*/


void Play_state::update_enemy_population(const sf::Texture &enemy_easy_texture,
                             const sf::Texture& enemy_medium_texture){
    //std::cout << "in update_enemy_population() " << std::endl;
    int safe_zone = 16 * 3;
    if(initial_enemy_spawn()){
        //std::cout << "initial spawn" << std::endl;
        safe_zone += 10 * 16;
        set_initial_enemy_spawn(false);
    }

    while(Enemy_easy::enemy_easy_cnt < ENEMY_EASY_COUNT){
        std::cout << Enemy_easy::enemy_easy_cnt << ", " << ENEMY_EASY_COUNT << std::endl;

        int rand_x;
        int rand_y;
        while(true){
            bool found = true;
            rand_x = 16 * 2 + rand() % (SCREEN_WIDTH - 4 * 16);
            rand_y = 16 * 2 + rand() % (SCREEN_HEIGHT - 4 * 16);
            if(rand_y - 16 <= INFO_RECT_SHAPE_HEIGHT){
                found = false;
                continue;
            }
            for(auto &e: enemy_list){
                double d = Util::dist(rand_x, rand_y, e -> get_x(), e -> get_y());
                if(d <= 16 + 16){
                    found = false;
                    break;//generated position intersects with existing enemy
                }
            }
            double d = Util::dist(rand_x, rand_y, player -> get_x(), player -> get_y());
            if(d <= safe_zone){
                found = false;
            }
            double x = rand_x;
            double y = rand_y - INFO_RECT_SHAPE_HEIGHT;
            for(int i = (x - 16) / MAP_TILE_WIDTH_IN_PIXELS; i < (x + 16) / MAP_TILE_WIDTH_IN_PIXELS; ++i){
                for(int j = (y - 16) / MAP_TILE_HEIGHT_IN_PIXELS; j < (y + 16) / MAP_TILE_HEIGHT_IN_PIXELS; ++j){
                    char curr = game_map() -> char_map()[j][i];
                    if((curr == 'H') || (curr == 'V') || (curr == 'A') || (curr == 'B') || (curr == 'C') || (curr == 'D')){
                        found = false;
                        break;
                    }
                }
            }
            if(found){
                break;
            }
        }
        enemy_list.push_back(new Enemy_easy(rand_x, rand_y, 32, 32, ENEMY_EASY_DX, ENEMY_EASY_DY, 0, ENEMY_EASY_HEALTH, ENEMY_EASY_DAMAGE, enemy_easy_texture, 0, 0));
    }
    while(Enemy_medium::enemy_medium_cnt < ENEMY_MEDIUM_COUNT){
        int rand_x;
        int rand_y;
        while(true){
            bool found = true;
            rand_x = 16 * 2 + rand() % (SCREEN_WIDTH - 4 * 16);
            rand_y = 16 * 2 + rand() % (SCREEN_HEIGHT - 4 * 16);
            if(rand_y - 16 <= INFO_RECT_SHAPE_HEIGHT){
                found = false;
                continue;
            }
            for(auto &e: enemy_list){
                double d = Util::dist(rand_x, rand_y, e -> get_x(), e -> get_y());
                if(d <= 16 + 16){
                    found = false;
                    break;//generated position intersects with existing enemy
                }
            }
            double d = Util::dist(rand_x, rand_y, player -> get_x(), player -> get_y());
            if(d <= safe_zone){
                found = false;
            }
            double x = rand_x;
            double y = rand_y - INFO_RECT_SHAPE_HEIGHT;
            for(int i = (x - 16) / MAP_TILE_WIDTH_IN_PIXELS; i < (x + 16) / MAP_TILE_WIDTH_IN_PIXELS; ++i){
                for(int j = (y - 16) / MAP_TILE_HEIGHT_IN_PIXELS; j < (y + 16) / MAP_TILE_HEIGHT_IN_PIXELS; ++j){
                    char curr = game_map() -> char_map()[j][i];
                    if((curr == 'H') || (curr == 'V') || (curr == 'A') || (curr == 'B') || (curr == 'C') || (curr == 'D')){
                        found = false;
                        break;
                    }
                }
            }
            if(found){
                break;
            }
        }
        enemy_list.push_back(new Enemy_medium(rand_x, rand_y, 32, 32, ENEMY_MEDIUM_DX, ENEMY_MEDIUM_DY, 0, ENEMY_MEDIUM_HEALTH, ENEMY_MEDIUM_DAMAGE, enemy_medium_texture, 0, 0));
    }
}


///is called after the Play_state is popped from the stack
void Play_state::reset(Application *app){
    //std::cout << "enemy size before: " << enemy_list.size() << std::endl;
    for(auto it = enemy_list.begin(); it != enemy_list.end(); ){
        Enemy *temp = *it;
        it = enemy_list.erase(it);
        delete temp;
    }
    for(auto it = bullet_list.begin(); it != bullet_list.end(); ){
        Bullet *temp = *it;
        it = bullet_list.erase(it);
        delete temp;
    }
    app -> display -> set_mouse_cursor_visible(true);
    //app -> resource_holder -> music -> play_state_music().stop();
    //std::cout << "enemy size after: " << enemy_list.size() << std::endl;
}



void Play_state::update_info_text(Application *app){
    std::ostringstream oss;
    oss << "Health: " << player -> get_health();
    oss << "                    ";///<--- 20 spaces here
    oss << "Score: " << app -> player_score();
    player_info_text().setString(oss.str());
}


void Play_state::update_info_panel(){
    player_info_text().setPosition(info_text_initial_position().x + player -> get_offset_x(), info_text_initial_position().y + player -> get_offset_y());
    info_rect_shape().setPosition(info_rect_shape_initial_position().x + player -> get_offset_x(), info_rect_shape_initial_position().y + player -> get_offset_y());
}


void Play_state::draw_player_fov(Application *app){
    double angle_step = FOV_STEP_IN_DEGREES * PI / 180.0;//1 degree in radians
    double angle = 0;
    //sf::Vector2f dir_orig = player -> direction();
    sf::Vector2f dir_orig = sf::Vector2f(1, 0);
    sf::Vector2f dir = dir_orig;
    //rotate player dir vector counterclockwise
    for(int i = 0; i < 360 / FOV_STEP_IN_DEGREES; ++i){
        dir.x = cos(angle_step) * dir.x - sin(angle_step) * dir.y;
        dir.y = sin(angle_step) * dir.x + cos(angle_step) * dir.y;
        draw_map2(app, dir);
        //angle += angle_step;
    }
    dir = dir_orig;
    for(int i = 0; i < 0 / FOV_STEP_IN_DEGREES; ++i){
        dir.x = cos(angle_step) * dir.x + sin(angle_step) * dir.y;
        dir.y = -sin(angle_step) * dir.x + cos(angle_step) * dir.y;
        draw_map2(app, dir);
        //angle += angle_step;
    }
}

void Play_state::draw_map2(Application *app, const sf::Vector2f& dir){
    ///third method
    //first determine the direction of moving along the x axis
    //double dot_prod = Util::dot_product(player -> direction(), sf::Vector2f(1, 0));
    double dot_prod = Util::dot_product(dir, sf::Vector2f(1, 0));
    //std::cout << "dot_prod: " << dot_prod << std::endl;
    double x_step = (dot_prod > 0) ? 1 : -1;
    //now determine the line equation a * x + b * y + c = 0
    //calculate the direction vector of the line
    sf::Vector2f player_dir_orth = sf::Vector2f(-dir.y, dir.x);
    double a = player_dir_orth.x;
    double b = player_dir_orth.y;
    double x0 = player -> get_x();
    double y0 = player -> get_y();
    //double x0 = player -> get_gun_x();
    //double y0 = player -> get_gun_y();
    double c = -a * x0 - b * y0;
    //double c = -Util::dot_product(player_dir_orth, player -> get_position());
    //std::cout << "player direction: " << player -> direction().x << ", " <<
    //player -> direction().y << std::endl;
    //std::cout << "line, a: " << a << ", b: " << b <<
    //", c: " << c << std::endl;
    x_step *= 10 / sqrt(a * a + 1);
    double curr_x = player -> get_x();
    double curr_y = player -> get_y() - INFO_RECT_SHAPE_HEIGHT;
    //double curr_x = player -> get_gun_x();
    //double curr_y = player -> get_gun_y() - INFO_RECT_SHAPE_HEIGHT;
    //std::cout << "curr x: " << curr_x << ", curr_y: " << curr_y << std::endl;
    int player_j = curr_x / MAP_TILE_WIDTH_IN_PIXELS;
    int player_i = curr_y / MAP_TILE_HEIGHT_IN_PIXELS;
    //std::cout << "player_j: " << player_j << ", player_i: " << player_i << std::endl;
    //std::cout << "x_step: " << x_step << std::endl;
    int ind_i = player_i;
    int ind_j = player_j;
    //std::cout << "before, ind_i: " << ind_i << ", ind_j: " << ind_j << std::endl;

    while(true){
        curr_x += x_step;
        curr_y = -a / b * curr_x - c / b;
        //std::cout << "curr_x: " << curr_x << ", curr_y: " << curr_y << std::endl;
        int temp_j = curr_x / MAP_TILE_WIDTH_IN_PIXELS;
        int temp_i = curr_y / MAP_TILE_HEIGHT_IN_PIXELS;
        if((temp_j < 0) || (temp_j > MAP_WIDTH_IN_TILES - 0)){
            break;
        }
        if((temp_i < 0) || (temp_i > MAP_HEIGHT_IN_TILES + INFO_RECT_SHAPE_HEIGHT / MAP_TILE_HEIGHT_IN_PIXELS)){
            break;
        }
        ind_i = temp_i;
        ind_j = temp_j;
    }
    //std::cout << "after, ind_i: " << ind_i << ", ind_j: " << ind_j << std::endl;
    int dx = abs(player_j - ind_j);
    int dy = abs(player_i - ind_i);
    int curr_j = player_j;
    int curr_i = player_i;
    std::vector<std::pair<int, int> > fov_vec;
    fov_vec.push_back(std::make_pair(curr_j, curr_i));
    int x_inc = (ind_j > player_j) ? 1 : -1;
    int y_inc = (ind_i > player_i) ? 1 : -1;
    int error = dx - dy;
    dx *= 2;
    dy *= 2;
    int n = 1 + dx + dy;

    for(; n > 0; --n){
        //game_map() -> wall_sprite_.setOrigin(sf::Vector2f(-8, -8));
        //game_map() -> wall_sprite_.setPosition(MAP_TILE_WIDTH_IN_PIXELS * curr_x,
                            //MAP_TILE_HEIGHT_IN_PIXELS * curr_y + 1 * INFO_RECT_SHAPE_HEIGHT);
        //app -> display -> draw(game_map() -> wall_sprite_);
        if(error > 0){
            curr_j += x_inc;
            error -= dy;
        }
        else if(error < 0){
            curr_i += y_inc;
            error += dx;
        }
        else{
            curr_j += x_inc;
            curr_i += y_inc;
            error -= dy;
            error += dx;
            --n;
        }
        ///Ad hoc, push only those tiles that have valid coordinates (j, i)
        if(!Util::tile_outside_of_map(curr_j, curr_i)){
            fov_vec.push_back(std::make_pair(curr_j, curr_i));
        }
        //if((curr_i >= 0) && (curr_i <= MAP_HEIGHT_IN_TILES) &&
           //(curr_j >= 0) && (curr_j <= MAP_HEIGHT_IN_TILES)){
            //fov_vec.push_back(std::make_pair(curr_j, curr_i));
        //}
    }
    int cnt_obstacles = 0;//keeps track of obstacles on the sight line, in order
    //of their appearance
    for(const auto& p: fov_vec){
        int i = p.second;
        int j = p.first;
        //std::cout << "i: " << i << ", j: " << j << ", h: " <<
        //game_map() -> char_map().size() << ", w: " <<
        //game_map() -> char_map()[0].size() << std::endl;
        if(Util::tile_outside_of_map(j, i)){
            //break;
        }
        char curr = game_map() -> char_map()[i][j];
        //game_map() -> wall_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i);
        //app -> display -> draw(game_map() -> wall_sprite_);
        switch(curr){
            case '1':{
                int cnt_neighbors = game_map() -> count_neighbors(i, j, '1');
                if(cnt_neighbors > 6){
                    game_map() -> brown_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> brown_sprite_);
                }
                else{
                    game_map() -> wall_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + 1 * INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> wall_sprite_);
                }
                break;
            }
            case '0':{
                game_map() -> floor_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + 1 * INFO_RECT_SHAPE_HEIGHT);
                app -> display -> draw(game_map() -> floor_sprite_);
                break;
            }
        }
        //if(Util::is_collision_obstacle(game_map() -> char_map()[i][j])){
        if((curr == '1') || Util::tile_outside_of_map(j, i)){
            //break;
            ++cnt_obstacles;
            if(cnt_obstacles == 2){
                //break;
            }
        }
    }
}

void Play_state::draw_map(Application *app){
    for(int i = 0; i < MAP_HEIGHT_IN_TILES; ++i){
        for(int j = 0; j < MAP_WIDTH_IN_TILES; ++j){
            char curr = game_map() -> char_map()[i][j];
            sf::Vector2f tile_position = sf::Vector2f(MAP_TILE_WIDTH_IN_PIXELS * j,
                                MAP_TILE_HEIGHT_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
            sf::Vector2f player_to_tile_vec = sf::Vector2f(tile_position -
                                                      player -> get_position());
            double cos_angle = Util::dot_product(player -> direction(), player_to_tile_vec);
            cos_angle /= Util::len(player -> direction()) * Util::len(player_to_tile_vec);
            double dist_squared_player_to_tile =
                Util::dist_squared(player -> get_x(), player -> get_y(),
                    MAP_TILE_WIDTH_IN_PIXELS * j, MAP_TILE_HEIGHT_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
            ///first method
            //if(dist_squared_player_to_tile > DIST_SQUARED_VISIBILITY_CUTOFF){
               //continue;
            //}
            ///second method
            //if(cos_angle < PLAYER_ANGLE_VISIBILITY_CUTOFF){
                //if(dist_squared_player_to_tile > DIST_SQUARED_VISIBILITY_CUTOFF){
                    //continue;
                //}
            //}


            switch(curr){
                case '1':{
                    game_map() -> wall_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> wall_sprite_);
                    break;
                }
                case '0':{
                    //std::cout << "horizontal" << std::endl;
                    game_map() -> floor_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> floor_sprite_);
                    break;
                }
                case 'H':{
                    //std::cout << "horizontal" << std::endl;
                    game_map() -> game_map_horizontal_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_horizontal_sprite_);
                    break;
                }
                case 'V':{
                    //std::cout << "vertical" << std::endl;
                    game_map() -> game_map_vertical_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_vertical_sprite_);
                    break;
                }
                case 'A':{
                    //std::cout << "vertical" << std::endl;
                    game_map() -> game_map_top_left_corner_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_top_left_corner_sprite_);
                    break;
                }
                case 'B':{
                    //std::cout << "vertical" << std::endl;
                    game_map() -> game_map_top_right_corner_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_top_right_corner_sprite_);
                    break;
                }
                case 'C':{
                    //std::cout << "vertical" << std::endl;
                    game_map() -> game_map_bottom_right_corner_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_bottom_right_corner_sprite_);
                    break;
                }
                case 'D':{
                    //std::cout << "vertical" << std::endl;
                    game_map() -> game_map_bottom_left_corner_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_bottom_left_corner_sprite_);
                    break;
                }
                case 'E':{
                    //std::cout << "vertical" << std::endl;
                    game_map() -> game_map_left_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_left_sprite_);
                    break;
                }
                case 'F':{
                    //std::cout << "vertical" << std::endl;
                    game_map() -> game_map_right_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_right_sprite_);
                    break;
                }
                case 'G':{
                    //std::cout << "vertical" << std::endl;
                    game_map() -> game_map_top_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_top_sprite_);
                    break;
                }
                case 'I':{
                    //std::cout << "vertical" << std::endl;
                    game_map() -> game_map_bottom_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_bottom_sprite_);
                    break;
                }
                case 'J':{
                    game_map() -> game_map_left_cap_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_left_cap_sprite_);
                    break;
                }
                case 'K':{
                    game_map() -> game_map_top_cap_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_top_cap_sprite_);
                    break;
                }
                case 'L':{
                    game_map() -> game_map_right_cap_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_right_cap_sprite_);
                    break;
                }
                case 'M':{
                    game_map() -> game_map_bottom_cap_sprite_.setPosition(MAP_TILE_HEIGHT_IN_PIXELS * j, MAP_TILE_WIDTH_IN_PIXELS * i + INFO_RECT_SHAPE_HEIGHT);
                    app -> display -> draw(game_map() -> game_map_bottom_cap_sprite_);
                    break;
                }
            }
        }
    }
}

void Play_state::play_sounds(){
    if(player -> get_is_shooting()){
        player -> shoot_sound().play();
    }
}

void Play_state::play_music(Application *app){
    if(!(app -> resource_holder -> music -> play_state_music().getStatus() == sf::Music::Status::Playing)){
        app -> resource_holder -> music -> play_state_music().play();
    }
}


void Play_state::draw_mini_map(Application *app){
    mini_map -> rect_shape().setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) +
                                         sf::Vector2f(player -> get_offset_x(), player -> get_offset_y()));
    app -> display -> draw(mini_map -> rect_shape());
    for(int i = 0; i < MAP_HEIGHT_IN_TILES; ++i){
        for(int j = 0; j < MAP_WIDTH_IN_TILES; ++j){
            sf::RectangleShape r;
            r.setSize(sf::Vector2f(MINI_MAP_TILE_WIDTH_IN_PIXELS, MINI_MAP_TILE_HEIGHT_IN_PIXELS));
            //r.setOrigin(sf::Vector2f(MINI_MAP_TILE_WIDTH_IN_PIXELS / 2, MINI_MAP_TILE_HEIGHT_IN_PIXELS / 2));
            r.setPosition(mini_map -> rect_shape().getPosition() -
                          mini_map -> rect_shape().getOrigin() +
                          sf::Vector2f(j * MINI_MAP_TILE_WIDTH_IN_PIXELS, i * MINI_MAP_TILE_HEIGHT_IN_PIXELS));
            if(game_map() -> char_map()[i][j] == '0'){
                r.setFillColor(sf::Color(255, 255, 255));
            }
            else{
                r.setFillColor(sf::Color(0, 0, 0));
            }
            app -> display -> draw(r);
        }
    }
    sf::RectangleShape player_rect;
    player_rect.setSize(sf::Vector2f(MINI_MAP_TILE_WIDTH_IN_PIXELS, MINI_MAP_TILE_HEIGHT_IN_PIXELS));
    player_rect.setOrigin(sf::Vector2f(MINI_MAP_TILE_WIDTH_IN_PIXELS / 2, MINI_MAP_TILE_HEIGHT_IN_PIXELS / 2));
    player_rect.setPosition(mini_map -> rect_shape().getPosition() -
                            mini_map -> rect_shape().getOrigin() +
                            sf::Vector2f(MINI_MAP_TILE_WIDTH_IN_PIXELS * (player -> get_x() / MAP_TILE_WIDTH_IN_PIXELS),
                                         MINI_MAP_TILE_HEIGHT_IN_PIXELS * ((player -> get_y() - INFO_RECT_SHAPE_HEIGHT) / MAP_TILE_HEIGHT_IN_PIXELS)));
    player_rect.setFillColor(sf::Color(255, 0, 0));
    app -> display -> draw(player_rect);
    sf::RectangleShape screen_rect;
    screen_rect.setSize(sf::Vector2f(SCREEN_WIDTH / MAP_TILE_WIDTH_IN_PIXELS * MINI_MAP_TILE_WIDTH_IN_PIXELS,
                                     (SCREEN_HEIGHT - INFO_RECT_SHAPE_HEIGHT) * MINI_MAP_TILE_HEIGHT_IN_PIXELS / MAP_TILE_HEIGHT_IN_PIXELS));
    screen_rect.setOrigin(sf::Vector2f(screen_rect.getSize().x / 2, screen_rect.getSize().y / 2) +
                          sf::Vector2f(0, -6));///<--- ad hoc!!!
    screen_rect.setPosition(player_rect.getPosition());
    screen_rect.setFillColor(sf::Color(255, 255, 255, 0));
    screen_rect.setOutlineThickness(1);
    screen_rect.setOutlineColor(sf::Color(255, 0, 0));
    double screen_rect_x = 0;
    double screen_rect_y = 0;
    if(screen_rect.getPosition().x - screen_rect.getSize().x / 2 <
       mini_map -> rect_shape().getPosition().x - mini_map -> rect_shape().getSize().x / 2){
        screen_rect_x = mini_map -> rect_shape().getPosition().x - mini_map -> rect_shape().getSize().x / 2;
        screen_rect.setPosition(sf::Vector2f(screen_rect_x + screen_rect.getSize().x / 2,
                                             screen_rect.getPosition().y));
    }
    else if(screen_rect.getPosition().x + screen_rect.getSize().x / 2 >
       mini_map -> rect_shape().getPosition().x + mini_map -> rect_shape().getSize().x / 2){
        screen_rect_x = mini_map -> rect_shape().getPosition().x + mini_map -> rect_shape().getSize().x / 2;
        screen_rect.setPosition(sf::Vector2f(screen_rect_x - screen_rect.getSize().x / 2,
                                             screen_rect.getPosition().y));
    }
    if(screen_rect.getPosition().y - screen_rect.getSize().y / 2 <
       mini_map -> rect_shape().getPosition().y - mini_map -> rect_shape().getSize().y / 2){
        screen_rect_y = mini_map -> rect_shape().getPosition().y -
                        mini_map -> rect_shape().getSize().y / 2;
        screen_rect.setPosition(sf::Vector2f(screen_rect.getPosition().x,
                                             screen_rect_y + screen_rect.getSize().y / 2));
    }
    else if(screen_rect.getPosition().y + screen_rect.getSize().y / 2 >
       mini_map -> rect_shape().getPosition().y + mini_map -> rect_shape().getSize().y / 2){
        screen_rect_y = mini_map -> rect_shape().getPosition().y + mini_map -> rect_shape().getSize().y / 2;
        screen_rect.setPosition(sf::Vector2f(screen_rect.getPosition().x,
                                             screen_rect_y - screen_rect.getSize().y / 2));
    }
    app -> display -> draw(screen_rect);
}
