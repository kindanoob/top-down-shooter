
#include <iostream>
#include <SFML/Graphics.hpp>

#include "util.h"
#include "config.h"

namespace Util{
    double dist_squared(double x1, double y1, double x2, double y2){
        double dx = x1 - x2;
        double dy = y1 - y2;
        return dx * dx + dy * dy;
    }

    double dist(double x1, double y1, double x2, double y2){
        return sqrt(dist_squared(x1, y1, x2, y2));
    }


    double length(double x1, double y1){
        return dist(x1, y1, 0, 0);
    }


    double dist_squared(const sf::Vector2f& u, const sf::Vector2f& v){
        double dx = u.x - v.x;
        double dy = u.y - v.y;
        return dx * dx + dy * dy;
    }


    double dist(const sf::Vector2f& u, const sf::Vector2f& v){
        return sqrt(dist_squared(u, v));
    }


    double len(const sf::Vector2f& v){
        return dist(v, sf::Vector2f(0, 0));
    }

    double dist_squared_from_point_to_point(double x0, double y0, double x1, double y1){
        double dx = x0 - x1;
        double dy = y0 - y1;
        return dx * dx + dy * dy;
    }

    double dist_from_point_to_point(double x0, double y0, double x1, double y1){
        return sqrt(dist_squared_from_point_to_point(x0, y0, x1, y1));
    }


    //line equation: y = a * x + b, ignore vertical line case for now
    double dist_from_point_to_line(double point_x, double point_y,
                                   double line_a, double line_b, double line_c){
        return fabs(line_a * point_x + line_b * point_y + line_c) / sqrt(line_a * line_a + line_b * line_b);
    }

    double dot_product(double x1, double y1, double x2, double y2){
        return x1 * x2 + y1 * y2;
    }

    double dot_product(const sf::Vector2f& u, const sf::Vector2f& v){
        return u.x * v.x + u.y * v.y;
    }

    void normalize(sf::Vector2f& v){
        double len_v = len(v);
        v.x /= len_v;
        v.y /= len_v;
    }

    bool is_wall(char c){
        return (c == 'V') || (c == 'H') || (c == 'A') || (c == 'B') ||
        (c == 'C') || (c == 'D') || (c == 'E') || (c == 'F') || (c == 'G') || (c == 'H');
    }


    bool pixel_outside_of_map(double x, double y){
        return (x < 32) || (x > MAP_WIDTH_IN_PIXELS - 32) ||
        (y < 32) || (y > MAP_HEIGHT_IN_PIXELS - 32);
    }

    bool tile_outside_of_map(double j, double i){
        return (i < 0) || (i > MAP_HEIGHT_IN_TILES - 1) ||
                (j < 0) || (j > MAP_WIDTH_IN_TILES - 1);
    }


    bool is_horizontal_collision_obstacle(char c){
        return (c == 'V') || (c == 'A') || (c == 'B') || (c == 'C') ||
               (c == 'D') || (c == 'E') || (c == 'F') || (c == 'J') ||
               (c == 'K') || (c == 'L') || (c == 'M');
    }


    bool is_vertical_collision_obstacle(char c){
        return (c == 'H') || (c == 'A') || (c == 'B') || (c == 'C') ||
               (c == 'D') || (c == 'G') || (c == 'I') || (c == 'J') ||
               (c == 'K') || (c == 'L') || (c == 'M');
    }


    bool is_collision_obstacle(char c){
        return (c == 'V') || (c == 'H') ||
               (c == 'A') || (c == 'B') || (c == 'C') || (c == 'D') ||
               (c == 'E') || (c == 'F') || (c == 'G') || (c == 'I') ||
               (c == 'J') || (c == 'K') || (c == 'L') || (c == 'M') ||
               (c == '1');
    }


    //returns 0 if there is no collision,
    sf::Vector2f square_side_collision(const sf::FloatRect& rect, double circle_x, double circle_y, double circle_r){
        double rect_x = rect.left + rect.width / 2;
        double rect_y = rect.top + rect.height / 2;
        double center_x = circle_x - rect_x;
        double center_y = circle_y - rect_y;
        double side_x = fabs(center_x) - rect.width / 2;
        double side_y = fabs(center_y) - rect.height / 2;
        if((side_x > circle_r) || (side_y > circle_r)){
            //std::cout << "NO" << std::endl;
            return sf::Vector2f(circle_x, circle_y);
        }
        double dx = 0;
        double dy = 0;
        if((fabs(center_x) > rect.width / 2) || (fabs(center_y) > rect.height / 2)){
            //std::cout << "YES" << std::endl;
            if(center_x > rect.width / 2){
                return sf::Vector2f(rect.left + rect.width + circle_r, circle_y);
            }
            if(center_x < -rect.width / 2){
                return sf::Vector2f(rect.left - circle_r, circle_y);
            }
            if(center_y > rect.height / 2){
                return sf::Vector2f(circle_x, rect.top + rect.height + circle_r);
            }
            if(center_y < -rect.height / 2){
                return sf::Vector2f(circle_x, rect.top - circle_r);
            }
        }
        ///Here we know that circle is near rect's corner
        double has_collided = side_x * side_x + side_y * side_y < circle_r * circle_r;
        if(!has_collided){
            //std::cout << "NO" << std::endl;
            return sf::Vector2f(circle_x, circle_y);
        }
        double center_len = length(center_x, center_y);
        center_x /= center_len;
        center_y /= center_len;
        double dist_top_left = dist_squared(circle_x, circle_y, rect.left, rect.top);
        double dist_top_right = dist_squared(circle_x, circle_y, rect.left + rect.width, rect.top);
        double dist_bottom_left = dist_squared(circle_x, circle_y, rect.left, rect.top + rect.height);
        double dist_bottom_right = dist_squared(circle_x, circle_y, rect.left + rect.width, rect.top + rect.height);
        double shift = circle_r - std::min(std::min(dist_bottom_left, dist_bottom_right), std::min(dist_top_left, dist_top_right));
        center_x *= shift;
        center_y *= shift;
        //std::cout << "YES" << std::endl;
        return sf::Vector2f(center_x, center_y);
    }


    sf::Vector2f quadratic_equation(double a, double b, double c){
        double sqrt_d = sqrt(b * b - 4 * a * c);
        double x1 = (-b - sqrt_d) / (2 * a);
        double x2 = (-b + sqrt_d) / (2 * a);
        return sf::Vector2f(x1, x2);
    }

    //a, b - coefficients of the direction vector of line
    double circle_line_intersection(const sf::Vector2f& circle, double r, sf::Vector2f& corner){
        double diff_y = circle.y - corner.y;
        double diff_x = circle.x - corner.x;
        double a = diff_y / diff_x;
        double b = circle.y - a * circle.x;
        ///Now we know the line equation y = a * x + b
        //std::cout << "line: " << a << " * x + " << b << std::endl;
        sf::Vector2f intersection_points = quadratic_equation(a * a + 1, 2 * (a * b - a * circle.y - circle.x), circle.x * circle.x + (b - circle.y) * (b - circle.y) - r * r);
        sf::Vector2f first_point = sf::Vector2f(intersection_points.x, a * intersection_points.x + b);
        sf::Vector2f second_point = sf::Vector2f(intersection_points.y, a * intersection_points.y + b);
        //std::cout << "first point: (" << first_point.x << ", " << first_point.y << "), second point: (" <<
        //second_point.x << ", " << second_point.y << ")" << std::endl;
        double dist1 = dist(first_point, corner);
        double dist2 = dist(second_point, corner);
        double shift = std::min(dist1 ,dist2);
        //std::cout << "dist1: " << dist1 << ", dist2: " << dist2 << ", shift: " << shift << std::endl;
        return shift;
    }

    bool check_collision(sf::FloatRect& rect, const sf::Vector2f& circle, double circle_r){
        double rect_x = rect.left + rect.width / 2;
        double rect_y = rect.top + rect.height / 2;
        //std::cout << "checking collision of rect (" << rect_x << ", " << rect_y << ") and circle (" <<
        //circle.x << ", " << circle.y << ")" << std::endl;
        sf::Vector2f center = circle - sf::Vector2f(rect_x, rect_y);
        double len_center = len(center);
        double dist_x = fabs(center.x) - rect.width / 2;
        double dist_y = fabs(center.y) - rect.height / 2;
        if((dist_x > circle_r) || (dist_y > circle_r)){
            return false;
        }
        if((dist_x <= 0) || (dist_y <= 0)){
            return true;
        }
        bool close_to_corner = (fabs(center.x) - rect.width / 2) * (fabs(center.x) - rect.width / 2) + (fabs(center.y) - rect.height / 2) * (fabs(center.y) - rect.height / 2) <= circle_r * circle_r;
        if(!close_to_corner){
            return false;
        }
        return true;
    }


    sf::Vector2f resolve_collision(sf::FloatRect& rect, const sf::Vector2f& circle, double r){
        double rect_x = rect.left + rect.width / 2;
        double rect_y = rect.top + rect.height / 2;
        //std::cout << "resolving collision between rect (" << rect_x << ", " << rect_y <<
        //") and circle (" << circle.x << ", " << circle.y << ")" << std::endl;

        sf::Vector2f rect_center = sf::Vector2f(rect_x, rect_y);
        sf::Vector2f center = circle - sf::Vector2f(rect_x, rect_y);
        double len_center = len(center);
        double dist_x = fabs(center.x) - rect.width / 2;
        double dist_y = fabs(center.y) - rect.height / 2;
        if(fabs(center.x) <= rect.width / 2){
            if(center.y >= rect.height / 2){
                //std::cout << "BOTTOM" << std::endl;
                return sf::Vector2f(circle.x, rect_y + rect.height / 2 + r);
            }
            //std::cout << "TOP" << std::endl;
            return sf::Vector2f(circle.x, rect_y - rect.height / 2 - r);
        }
        if(fabs(center.y) <= rect.height / 2){
            if(center.x >= rect.width / 2){
                //std::cout << "RIGHT" << std::endl;
                return sf::Vector2f(rect_x + rect.width / 2 + r, circle.y);
            }
            //std::cout << "LEFT" << std::endl;
            return sf::Vector2f(rect_x - rect.width / 2 - r, circle.y);
        }
        //std::cout << "CORNER" << std::endl;
        sf::Vector2f corner;
        if(center.x > 0){
            if(center.y > 0){
                corner = sf::Vector2f(rect_center + sf::Vector2f(rect.width / 2, rect.height / 2));
            }
            else{
                corner = sf::Vector2f(rect_center + sf::Vector2f(rect.width / 2, -rect.height / 2));
            }
        }
        else{
            if(center.y > 0){
               corner = sf::Vector2f(rect_center + sf::Vector2f(-rect.width / 2, rect.height / 2));
            }
            else{
                corner = sf::Vector2f(rect_center + sf::Vector2f(-rect.width / 2, -rect.height / 2));
            }
        }

        double shift = circle_line_intersection(circle, r, corner);
        sf::Vector2f diff = circle - corner;
        normalize(diff);
        diff.x *= shift;
        diff.y *= shift;
        sf::Vector2f new_pos = circle + diff;
        return new_pos;
    }

    bool cmp_tile_connected_components_by_size_descending(
                std::vector<std::pair<int, int> >& cc1, std::vector<std::pair<int, int> >& cc2){
        return cc1.size() > cc2.size();
    }
}



