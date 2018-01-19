#ifndef MUSIC_MANAGER_H_
#define MUSIC_MANAGER_H_


#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>




enum class Music_name {
    play_state_music
};


class Music_manager {
public:
    Music_manager();
    ~Music_manager();
    void add_play_state_music();
    //sf::Music& get_resource(Music_name name){
        //return resource_map[name];
    //}
    //void add_resource(Music_name name, const std::string &filename, sf::Music& music_resource){
        //if(!music_resource.openFromFile(filename)){
            //std::cout << "Failed to open resource from file " << filename << std::endl;
            //return;
        //}
        //resource_map.insert(std::make_pair(name, res));
        //resource_map.insert(std::make_pair(name, music_resource));
    //}
    sf::Music& play_state_music() {
        return play_state_music_;
    }
private:
    sf::Music play_state_music_;
    //std::map<Music_name, sf::Music&> resource_map;
};

#endif // MUSIC_MANAGER_H_
