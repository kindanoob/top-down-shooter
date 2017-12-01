#include <iostream>


#include "animation.h"


Animation::Animation(){
    current_frame = 0;
    is_playing = true;
    flip = false;
    loop = true;
}

void Animation::tick(double time){
    if (!is_playing){
        return;
    }

    current_frame += speed * time;
    //std::cout << "current frame: " << current_frame << ", frames size: " <<
    //frames.size() << std::endl;
    if (current_frame >= frames.size()){
        current_frame -= frames.size();
        if (!loop){
            is_playing = false;
            return;
        }
    }
    int current_frame_index = static_cast<int>(current_frame);
    //std::cout << "current_frame: " << current_frame << ", int: " << current_frame_int <<
    //", size: " << frames.size() << std::endl;
    sprite.setTextureRect(frames[current_frame_index]);
    auto r = frames[current_frame_index];
    sprite.setOrigin(sf::Vector2f(r.width / 2, r.height / 2));
    //std::cout << "frame rect, left: " << r.left << ", top: " << r.top << ", w: " <<
    //r.width << ", h: " << r.height << std::endl;
    //std::cout << "at animation, rotation: " << sprite.getRotation()  << std::endl;

    //auto r = sprite.getOrigin();
    //std::cout << "origin x: " << r.x << ", y: " << r.y << std::endl;
    //sprite.rotate()
    if(flip){
        sprite.setTextureRect(frames_flip[current_frame_index]);
    }
}



