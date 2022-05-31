#include "Room.h"
#include <vector>
#include <set>
#include <map>
#include <random>


Room::Room(int x, int y) :
    x(x), y(y)
{
    fog.setPrimitiveType(sf::Quads);
    fog.resize(8);
    fog[0].position = sf::Vector2f(-tileWidth, -tileHeight);
    fog[1].position = sf::Vector2f(0, -tileHeight);
    fog[2].position = sf::Vector2f(0, tileHeight * (roomHeight + 1));
    fog[3].position = sf::Vector2f(-tileWidth, tileHeight * (roomHeight + 1));
    fog[0].color = sf::Color::Black;
    fog[1].color = sf::Color(0, 0, 0, 0);
    fog[2].color = sf::Color(0, 0, 0, 0);
    fog[3].color = sf::Color::Black;

    fog[4].position = sf::Vector2f(-tileWidth * roomWidth, -tileHeight);
    fog[5].position = sf::Vector2f(-tileWidth, -tileHeight);
    fog[6].position = sf::Vector2f(-tileWidth,  2 * tileHeight * roomHeight);
    fog[7].position = sf::Vector2f(-tileWidth * roomWidth, 2 * tileHeight * roomHeight);
    fog[4].color = sf::Color::Black;
    fog[5].color = sf::Color::Black;
    fog[6].color = sf::Color::Black;
    fog[7].color = sf::Color::Black;

    sf::Transform transform;
    fogTransforms.reserve(4);
    transform.translate(sf::Vector2f(x * tileWidth * roomWidth, y * tileHeight * roomHeight));
    fogTransforms.push_back(transform);
    transform.rotate(90);
    transform.translate(sf::Vector2f(0, -tileHeight * roomHeight));
    fogTransforms.push_back(transform);
    transform.rotate(90);
    transform.translate(sf::Vector2f(0, -tileHeight * roomHeight));
    fogTransforms.push_back(transform);
    transform.rotate(90);
    transform.translate(sf::Vector2f(0, -tileHeight * roomHeight));
    fogTransforms.push_back(transform);
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
    window.draw(map);
}

void Room::display_fog(sf::RenderWindow& window) const{
    sf::Transform transform;
    transform.translate(sf::Vector2f(x * tileWidth * roomWidth, y * tileHeight * roomHeight));
    window.draw(fog, fogTransforms[0]);
    window.draw(fog, fogTransforms[1]);
    window.draw(fog, fogTransforms[2]);
    window.draw(fog, fogTransforms[3]);
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

void Room::enter()
{
    explored = true;
}

bool Room::isExplored() const
{
    return explored;
}

void Room::build(b2World* world, sf::Texture* m_tileset, std::vector<int> tiles, int corridorLength, int corridorWidth)
{
    int halfWidth = int(roomWidth / 2);
    int halfHeight = int(roomHeight / 2);
    for (int j = 1; j <= (int)(corridorWidth / 2) && j < halfWidth; j++) {
        if (up) {
            tiles[halfWidth] = emptyTile;
            tiles[halfWidth + j] = emptyTile;
            tiles[halfWidth - j] = emptyTile;
        }
        if (down) {
            tiles[tiles.size() - halfWidth - 1] = emptyTile;
            tiles[tiles.size() - halfWidth - 1 + j] = emptyTile;
            tiles[tiles.size() - halfWidth - 1 - j] = emptyTile;
        }
        if (left) {
            tiles[halfHeight * roomWidth] = emptyTile;
            tiles[(halfHeight + j) * roomWidth] = emptyTile;
            tiles[(halfWidth - j) * roomWidth] = emptyTile;
        }
        if (right) {
            tiles[(halfHeight + 1) * roomWidth - 1] = emptyTile;
            tiles[(halfHeight + 1 + j) * roomWidth - 1] = emptyTile;
            tiles[(halfHeight + 1 - j) * roomWidth - 1] = emptyTile;
        }
        for (int i = 0; i < roomWidth; i++) {
            for (int j = 0; j < roomHeight; j++) {
                if (tiles[i + j * roomWidth] != emptyTile) {
                    Box newBox;
                    newBox.init(world, b2Vec2(x * tileWidth * roomWidth + i * tileWidth + (0.5f * tileWidth), -(y * tileHeight * roomHeight) - j * tileHeight - (0.5f * tileHeight)), b2_staticBody, 1,  b2Vec2(tileWidth, tileHeight));
                }
            }
        }

    }
    map.load(m_tileset, sf::Vector2u(spriteWidth, spriteHeight), tiles, roomWidth, roomHeight);
    map.setPosition(x * tileWidth * roomWidth, y * tileHeight * roomHeight);
    map.setScale(sf::Vector2f((float)tileWidth / (float)spriteWidth,(float)tileHeight / (float)spriteHeight));
}
