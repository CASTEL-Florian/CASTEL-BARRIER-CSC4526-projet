#include "Room.h"
#include <vector>
#include <set>
#include <map>
#include <random>
#include "RoomGenerator.h"

enum class ObjectType{Empty, Treasure};

Room::Room(int x, int y) :
    x(x), y(y)
{
    fogOpen.setPrimitiveType(sf::Quads);
    fogOpen.resize(12);

    int offset = (roomWidth - 1) / 2 - (corridorWidth - 1)/2;
    fogOpen[0].position = sf::Vector2f(-tileWidth * roomWidth, -tileHeight);
    fogOpen[1].position = sf::Vector2f(-tileWidth, -tileHeight);
    fogOpen[2].position = sf::Vector2f(-tileWidth, offset * tileWidth);
    fogOpen[3].position = sf::Vector2f(-tileWidth * roomWidth, (offset - 4) * tileWidth);
    fogOpen[4].position = sf::Vector2f(-tileWidth * roomWidth, (offset - 4) * tileWidth);
    fogOpen[5].position = sf::Vector2f(-tileWidth, offset * tileWidth);
    fogOpen[6].position = sf::Vector2f(-tileWidth, (offset + corridorWidth) * tileWidth);
    fogOpen[7].position = sf::Vector2f(-tileWidth * roomWidth, (offset + corridorWidth + 4) * tileWidth);
    fogOpen[8].position = sf::Vector2f(-tileWidth * roomWidth, (offset + corridorWidth + 4) * tileWidth);
    fogOpen[9].position = sf::Vector2f(-tileWidth, (offset + corridorWidth) * tileWidth);
    fogOpen[10].position = sf::Vector2f(-tileWidth, 2 * tileHeight * roomHeight);
    fogOpen[11].position = sf::Vector2f(-tileWidth * roomWidth, 2 * tileHeight * roomHeight);

    fogOpen[0].color = sf::Color::Black;
    fogOpen[1].color = sf::Color::Black;
    fogOpen[2].color = sf::Color::Black;
    fogOpen[3].color = sf::Color::Black;
    fogOpen[4].color = sf::Color::Black;
    fogOpen[5].color = sf::Color::Transparent;
    fogOpen[6].color = sf::Color::Transparent;
    fogOpen[7].color = sf::Color::Black;
    fogOpen[8].color = sf::Color::Black;
    fogOpen[9].color = sf::Color::Black;
    fogOpen[10].color = sf::Color::Black;
    fogOpen[11].color = sf::Color::Black;

    fogClose.setPrimitiveType(sf::Quads);
    fogClose.resize(8);
    fogClose[0].position = sf::Vector2f(-tileWidth, -tileHeight);
    fogClose[1].position = sf::Vector2f(0, -tileHeight);
    fogClose[2].position = sf::Vector2f(0, tileHeight * (roomHeight + 1));
    fogClose[3].position = sf::Vector2f(-tileWidth, tileHeight * (roomHeight + 1));
    fogClose[0].color = sf::Color::Black;
    fogClose[1].color = sf::Color(0, 0, 0, 0);
    fogClose[2].color = sf::Color(0, 0, 0, 0);
    fogClose[3].color = sf::Color::Black;

    fogClose[4].position = sf::Vector2f(-tileWidth * roomWidth, -tileHeight);
    fogClose[5].position = sf::Vector2f(-tileWidth, -tileHeight);
    fogClose[6].position = sf::Vector2f(-tileWidth, 2 * tileHeight * roomHeight);
    fogClose[7].position = sf::Vector2f(-tileWidth * roomWidth, 2 * tileHeight * roomHeight);
    fogClose[4].color = sf::Color::Black;
    fogClose[5].color = sf::Color::Black;
    fogClose[6].color = sf::Color::Black;
    fogClose[7].color = sf::Color::Black;

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
    if(left)
        window.draw(fogOpen, fogTransforms[0]);
    else
        window.draw(fogClose, fogTransforms[0]);
    if(up)
        window.draw(fogOpen, fogTransforms[1]);
    else
        window.draw(fogClose, fogTransforms[1]);
    if(right)
        window.draw(fogOpen, fogTransforms[2]);
    else
        window.draw(fogClose, fogTransforms[2]);
    if(down)
        window.draw(fogOpen, fogTransforms[3]);
    else
        window.draw(fogClose, fogTransforms[3]);
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

bool Room::isDeadEnd() const
{
    if (up)
        return !down && !left && !right;
    if (down)
        return !up && !left && !right;
    if (left)
        return !up && !down && !right;
    if (right)
        return !up && !left && !down;
    return false;
}

void Room::linkToRoom(Room* room)
{
    if (room->get_x() > x) {
        rightRoom = room;
        return;
    }
    if (room->get_x() < x) {
        leftRoom = room;
        return;
    }
    if (room->get_y() < y) {
        upRoom = room;
        return;
    }
    if (room->get_y() > y) {
        downRoom = room;
        return;
    }
}

void Room::build(b2World* world, sf::Texture* m_tileset, std::vector<int> tiles)
{
    int halfWidth = int(roomWidth / 2);
    int halfHeight = int(roomHeight / 2);
    if (up)
        tiles[halfWidth] = emptyTile;
    if (down)
        tiles[tiles.size() - halfWidth - 1] = emptyTile;
    if (left)
        tiles[halfHeight * roomWidth] = emptyTile;
    if (right)
        tiles[(halfHeight + 1) * roomWidth - 1] = emptyTile;
    for (int j = 1; j <= (int)(corridorWidth / 2) && j < halfWidth; j++) {
        if (up) {
            tiles[halfWidth + j] = emptyTile;
            tiles[halfWidth - j] = emptyTile;
        }
        if (down) {
            tiles[tiles.size() - halfWidth - 1 + j] = emptyTile;
            tiles[tiles.size() - halfWidth - 1 - j] = emptyTile;
        }
        if (left) {
            tiles[(halfHeight + j) * roomWidth] = emptyTile;
            tiles[(halfWidth - j) * roomWidth] = emptyTile;
        }
        if (right) {            tiles[(halfHeight + 1 + j) * roomWidth - 1] = emptyTile;
            tiles[(halfHeight + 1 - j) * roomWidth - 1] = emptyTile;
        }
    }
    for (int i = 0; i < roomWidth; i++) {
        for (int j = 0; j < roomHeight; j++) {
            int choice = random_1_to_n(numberOfTilesChoices);
            if (tiles[i + j * roomWidth] != emptyTile) {
                Box newBox;
                newBox.init(world, b2Vec2(x * tileWidth * roomWidth + i * tileWidth + (0.5f * tileWidth), (y * tileHeight * roomHeight) + j * tileHeight + (0.5f * tileHeight)), b2_staticBody, b2Vec2(tileWidth, tileHeight));
                tiles[i + j * roomWidth] = choice;
            }
            else{
                if (random_1_to_n(100)<emptyBackgroundTilePercentage)
                    tiles[i + j * roomWidth] = numberOfTilesChoices + 1 + choice;
            }

        }
    }
    
    map.load(m_tileset, sf::Vector2u(spriteWidth, spriteHeight), tiles, roomWidth, roomHeight);
    map.setPosition(x * tileWidth * roomWidth, y * tileHeight * roomHeight);
    map.setScale(sf::Vector2f((float)tileWidth / (float)spriteWidth,(float)tileHeight / (float)spriteHeight));
}

void Room::generateObjects(std::vector<int> const& objects)
{
    if (objects.size() > 0) {
        for (int i = 0; i < roomWidth; i++) {
            for (int j = 0; j < roomHeight; j++) {
                if (objects[i + j * roomWidth] == int(ObjectType::Treasure)) {
                    treasurePos.push_back(std::pair(
                        x * tileWidth * roomWidth + i * tileWidth + (0.5f * tileWidth),
                        y * tileHeight * roomHeight + j * tileHeight + (0.5f * tileHeight)
                    ));
                }
            }
        }
    }
}

void Room::displayObjects(sf::RenderWindow& window) const
{
    for (auto const& o : objects)
        o->display(window);
}

void Room::updateObjects(sf::Time elapsed)
{
    for (auto it = objects.begin(); it != objects.end();) {
        it->get()->update(elapsed);
        int roomX = std::floor(it->get()->get_x() / (roomWidth * tileWidth));
        int roomY = std::floor(it->get()->get_y() / (roomHeight * tileHeight));
        if (roomX > x) {
            rightRoom->addObject(std::move(*it));
            it = objects.erase(it);
        }
        else if (roomX < x) {
            leftRoom->addObject(std::move(*it));
            it = objects.erase(it);
        }
        else if (roomY > y) {
            downRoom->addObject(std::move(*it));
            it = objects.erase(it);
        }
        else if (roomY < y) {
            upRoom->addObject(std::move(*it));
            it = objects.erase(it);
        }
        else
            it++;
    }
}

void Room::addObject(std::unique_ptr<Object> object)
{
    objects.push_back(std::move(object));
}

Room* Room::updateCurrentRoom(int roomX, int roomY) 
{
    if (roomX > x) {
        return rightRoom;
    }
    if (roomX < x) {
        return leftRoom;
    }
    if (roomY < y) {
        return upRoom;
    }
    if (roomY > y) {
        return downRoom;
    }
    return this;
}

std::vector<Room*> Room::getAjacentRooms()
{
    return std::vector<Room*>{upRoom, downRoom, leftRoom, rightRoom};
}

std::vector<std::pair<int, int>> Room::getTreasurePos()
{
    return treasurePos;
}
