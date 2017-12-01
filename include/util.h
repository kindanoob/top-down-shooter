#ifndef UTIL_H
#define UTIL_H

#include <cmath>

#include <SFML/Graphics.hpp>


namespace Util{
    double dist_squared(double x1, double y1, double x2, double y2);
    double dist(double x1, double y1, double x2, double y2);
    double length(double x1, double y1);
    double dist_squared_from_point_to_point(double x0, double y0, double x1, double y1);
    double dist_from_point_to_point(double x0, double y0, double x1, double y1);
    double dist_from_point_to_line(double point_x, double point_y,
                               double line_a, double line_b, double line_c);
    double dot_product(double x1, double y1, double x2, double y2);
    double dot_product(const sf::Vector2f& u, const sf::Vector2f& v);
    void normalize(sf::Vector2f& v);
    bool is_wall(char c);
    bool pixel_outside_of_map(double x, double y);
    bool tile_outside_of_map(double j, double i);
    bool is_vertical_collision_obstacle(char c);
    bool is_horizontal_collision_obstacle(char c);
    bool is_collision_obstacle(char c);
    sf::Vector2f square_side_collision(const sf::FloatRect& rect, double circle_x, double circle_y, double circle_r);
    sf::Vector2f quadratic_equation(double a, double b, double c);
    double circle_line_intersection(const sf::Vector2f& circle, double r, sf::Vector2f& corner);
    bool check_collision(sf::FloatRect& rect, const sf::Vector2f& circle, double r);
    sf::Vector2f resolve_collision(sf::FloatRect& rect, const sf::Vector2f& circle, double r);
    double length(double x1, double y1);
    double dist_squared(const sf::Vector2f& u, const sf::Vector2f& v);
    double dist(const sf::Vector2f& u, const sf::Vector2f& v);
    double len(const sf::Vector2f& v);
    bool cmp_tile_connected_components_by_size_descending(
                std::vector<std::pair<int, int> >& cc1, std::vector<std::pair<int, int> >& cc2);
}



//double dot_product()

#endif // UTIL_H
