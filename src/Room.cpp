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
    window.draw(map);
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
