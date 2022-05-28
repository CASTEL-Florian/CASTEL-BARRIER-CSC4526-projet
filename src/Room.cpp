#include "Room.h"
#include "Room.h"
#include "Room.h"
#include <vector>
#include <set>
#include <map>
#include <random>


Room::Room(int x, int y) :
    x(x), y(y)
{
}

void Room::open_path(std::pair<int, int> const& target) {
       
    if (target.first - x == 0) {
        if (target.second - y > 0)
            down = true;
        else
            up = true;
    }
    else {
        
        if (target.first - x > 0) 
            right = true;
        else
            left = true;
    }
}





void Room::display(sf::RenderWindow& window) const {
    sf::RectangleShape rect;
    float size = 40;
    rect.setSize(sf::Vector2f(0.9 * size, 0.9 * size));
    float posx = size * x - (0.45 * size) + (window.getSize().x / 2);
    float posy = size * y - (0.45 * size) + (window.getSize().y / 2);
    rect.setPosition(posx, posy);
    if (x == 0 && y == 0)
        rect.setFillColor(sf::Color::Red);
    window.draw(rect);
    if (up) {
        sf::RectangleShape path;
        float pposx = posx + (0.4 * size);
        float pposy = posy;
        path.setSize(sf::Vector2f(0.1 * size, 0.3 * size));
        path.setPosition(pposx, pposy);
        path.setFillColor(sf::Color::Magenta);
        window.draw(path);
    }
    if (down) {
        sf::RectangleShape path;
        float pposx = posx + (0.4 * size);
        float pposy = posy + (0.6 * size);
        path.setSize(sf::Vector2f(0.1 * size, 0.3 * size));
        path.setPosition(pposx, pposy);
        path.setFillColor(sf::Color::Blue);
        window.draw(path);
    }
    if (left) {
        sf::RectangleShape path;
        float pposx = posx;
        float pposy = posy + (0.4 * size);
        path.setSize(sf::Vector2f(0.3 * size, 0.1 * size));
        path.setPosition(pposx, pposy);
        path.setFillColor(sf::Color::Black);
        window.draw(path);
    }
    if (right) {
        sf::RectangleShape path;
        float pposx = posx + (0.6 * size);
        float pposy = posy + (0.4 * size);
        path.setSize(sf::Vector2f(0.3 * size, 0.1 * size));
        path.setPosition(pposx, pposy);
        path.setFillColor(sf::Color::Cyan);
        window.draw(path);
    }
    
}

std::pair<int, int> Room::get_position() const {
    return std::pair(x, y);
}

bool Room::is_opened(int direction)
{
    if (direction == 0)
        return up;
    if (direction == 1)
        return down;
    if (direction == 2)
        return left;
    if (direction == 3)
        return right;
    return false;
}

int Room::get_x() const
{
    return x;
}

int Room::get_y() const
{
    return y;
}
