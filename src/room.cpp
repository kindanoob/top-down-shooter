

#include <iostream>



#include "room.h"
#include "game_map.h"
#include "config.h"
#include "util.h"

bool Room::cmp_rooms_by_size(Room *room_one, Room *room_two){
    return room_one -> get_size() > room_two -> get_size();
}


Room::Room(std::vector<Node *>& node_vector, Game_map *game_map):
    node_vector_(node_vector){
    create_boundary_nodes(game_map);
    //set_closest_room(r)
};


void Room::create_boundary_nodes(Game_map *game_map){
    for(auto& n: node_vector_){
        if(game_map -> is_on_boundary(n -> x_, n -> y_)){
            boundary_nodes_.push_back(n);
        }
    }
}

int Room::calc_distance_to_room(Room* other_room){
    int min_dist = MAP_WIDTH_IN_TILES * MAP_WIDTH_IN_TILES + MAP_HEIGHT_IN_TILES * MAP_HEIGHT_IN_TILES;
    for(auto& node: boundary_nodes()){
        for(auto& other_node: other_room -> boundary_nodes()){
            int dx = node -> x_ - other_node -> x_;
            int dy = node -> y_ - other_node -> y_;
            int curr_dist = dx * dx + dy * dy;
            //int curr_dist = abs(node -> x_ - other_node -> x_) +
                            //abs(node -> y_ - other_node -> y_);
            if(curr_dist < min_dist){
                min_dist = curr_dist;
            }
        }
    }
    return min_dist;
}


Room *Room::get_closest_room(std::vector<Room *>& rooms){
    Room *min_dist_room = nullptr;
    int min_dist = -1;
    //int min_dist = MAP_WIDTH_IN_TILES * MAP_WIDTH_IN_TILES + MAP_HEIGHT_IN_TILES * MAP_HEIGHT_IN_TILES;
    if(this == rooms[0]){
        min_dist = calc_distance_to_room(rooms[1]);
        min_dist_room = rooms[1];
    }
    else{
        min_dist = calc_distance_to_room(rooms[0]);
        min_dist_room = rooms[0];
    }
    //std::cout << "before, min_dist: " << min_dist << std::endl;
    for(int i = 0; i < rooms.size(); ++i){
        if(rooms[i] == this){
            continue;
        }
        int curr_dist = calc_distance_to_room(rooms[i]);
        //std::cout << "curr_dist: " << curr_dist << std::endl;
        if(curr_dist < min_dist){
            min_dist_room = rooms[i];
            min_dist = curr_dist;
        }
    }
    return min_dist_room;
}

void Room::connect_room(Room *other_room){
    //std::cout << "in connect_room: " << other_room << ", " << this << std::endl;
    connected_rooms_.push_back(other_room);
    other_room -> connected_rooms_.push_back(this);
}

std::vector<Node *> Room::boundary_nodes(){
    return boundary_nodes_;
}

//int room_size_;
int Room::get_size(){
    return node_vector_.size();
}

//this function returns the pair of two nodes (one from the caller room, another -
//from the other_room room) which is the pair with smallest distance between the nodes
std::pair<Node *, Node *> Room::get_closest_nodes(Room *other_room){
    //std::cout << "this: " << this << ", other room: " << other_room << std::endl;
    Node *this_node = nullptr;
    Node *other_node = nullptr;
    //int min_dist = MAP_WIDTH_IN_TILES * MAP_WIDTH_IN_TILES + MAP_HEIGHT_IN_TILES * MAP_HEIGHT_IN_TILES;
    //std::cout << "min dist: " << min_dist << std::endl;
    int min_dist = 2000000000;
    //std::cout << "boundary size: " << boundary_nodes().size() << ", other boundary size: " <<
    //other_room -> boundary_nodes().size() << std::endl;
    for(auto& curr_node: boundary_nodes()){
        for(auto& curr_other_node: other_room -> boundary_nodes()){
            double curr_dist = Util::dist_squared_from_point_to_point(curr_node -> x_, curr_node -> y_,
                                            curr_other_node -> x_, curr_other_node -> y_);
            //std::cout << "curr dist: " << curr_dist << ", min dist: " <<
            //min_dist << std::endl;
            //int dx = node -> x_ - other_node -> x_;
            //int dy = node -> y_ - other_node -> y_;
            //int curr_dist = dx * dx + dy * dy;
            //int curr_dist = abs(node -> x_ - other_node -> x_) +
                            //abs(node -> y_ - other_node -> y_);
            if(curr_dist < min_dist){
                min_dist = curr_dist;
                this_node = curr_node;
                other_node = curr_other_node;
            }
        }
    }
    std::pair<Node *, Node *> res(this_node, other_node);
    return res;
}
