#include "Room.h"
#include <vector>
#include <set>
#include <map>
#include <random>
#include "RoomGenerator.h"
#include "Crab.h"
#include "Crate.h"

enum class ObjectType{Empty, Treasure, Crab, Crate, Wall};

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

/**
 * Open a path in the room toward an adjacent room postion.
 *
 * @param target position of the adjacent room.
 */
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




/**
 * Display the room tilemap.
 *
 * @param window on which the room has to be drawn.
 */
void Room::display(sf::RenderWindow& window) const {
    window.draw(map);
}

/**
 * Display the fog around the room.
 *
 * @param window on which the fog has to be drawn.
 */
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

/**
 * Get the position of the room.
 *
 * @return pair of integers representing the position of the room.
 */
std::pair<int, int> Room::get_position() const {
    return std::pair(x, y);
}

/**
 * Get whether a path is opened in the room in a certain direction.
 *
 * @param direction 0 for up, 1 for down, 2 for left, 3 for right.
 * @return true if the path is open, false if the path is closed.
 */
bool Room::is_opened(int direction) const
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

/**
 * Get the x position of the room.
 *
 * @return x position of the room.
 */
int Room::get_x() const
{
    return x;
}

/**
 * Get the y position of the room.
 *
 * @return y position of the room.
 */
int Room::get_y() const
{
    return y;
}

/**
 * Tell the room that the player visited it.
 */

void Room::enter()
{
    explored = true;
}

/**
 * @return true if the player already visited the room.
 */
bool Room::isExplored() const
{
    return explored;
}

/**
 * Get whether the room is a dead end (if it is opened in only one direction).
 *
 * @return true if the room is a dead end.
 */
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

/**
 * Register an adjacent room.
 *
 * @param room adjacent room.
 */
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

/**
 * Get the x position of the room.
 *
 * @param world box2d world.
 * @param m_tileset tileset texture.
 * @param tiles vector of integer representing the tiles.
 * @param objectsMap vector of integer representing objects and blocs to add in the room.
 */
void Room::build(b2World* world, sf::Texture* m_tileset, std::vector<int> tiles, std::vector<int> objectsMap)
{
    int halfWidth = int(roomWidth / 2);
    int halfHeight = int(roomHeight / 2);

    // Open a path in the tilemap in directions the room is opened. 
    if (up)
        tiles[halfWidth] = emptyTile;
    if (down)
        tiles[tiles.size() - halfWidth - 1] = emptyTile;
    if (left)
        tiles[halfHeight * roomWidth] = emptyTile;
    if (right)
        tiles[(halfHeight + 1) * roomWidth - 1] = emptyTile;
    for (int j = 1; j <= (corridorWidth / 2) && j < halfWidth; j++) {
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
            // If there are walls in the object map, add them to the tilemap.
            if (!objectsMap.empty() && objectsMap[i + j * roomWidth] == (int)ObjectType::Wall) {
                tiles[i + j * roomWidth] = 1;
            }

            // Randomize the tiles.
            int choice = random_1_to_n(numberOfTilesChoices);
            if (tiles[i + j * roomWidth] != emptyTile) {
                // Create a solid box an choose a random texture for the solid bloc.
                Box newBox;
                newBox.init(world, b2Vec2(x * tileWidth * roomWidth + i * tileWidth + (0.5f * tileWidth), (y * tileHeight * roomHeight) + j * tileHeight + (0.5f * tileHeight)), b2_staticBody, b2Vec2(tileWidth, tileHeight));
                tiles[i + j * roomWidth] = choice;
            }
            else{
                // Select a random texture for the "empty" bloc.
                if (random_1_to_n(100)>emptyBackgroundTilePercentage)
                    tiles[i + j * roomWidth] = numberOfTilesChoices + 1 + choice;
            }

        }
    }
    
    map.load(m_tileset, sf::Vector2u(spriteWidth, spriteHeight), tiles, roomWidth, roomHeight);
    map.setPosition((float)(x * tileWidth * roomWidth), (float)(y * tileHeight * roomHeight));
    map.setScale(sf::Vector2f((float)tileWidth / (float)spriteWidth,(float)tileHeight / (float)spriteHeight));
}

/**
 * Generate objects in the room.
 *
 * @param world box2d world.
 * @param objectsMap vector of integer representing objects and blocs to add in the room.
 * @param textures vector of textures.
 */
void Room::generateObjects(b2World* world, std::vector<int> const& objectsMap, std::vector<sf::Texture>* textures)
{
    objectsTilemap = objectsMap;
    if (!objectsMap.empty()) {
        for (int i = 0; i < roomWidth; i++) {
            for (int j = 0; j < roomHeight; j++) {
                float posX = (float)(x * tileWidth * roomWidth + i * tileWidth) + (0.5f * tileWidth);
                float posY = (float)(y * tileHeight * roomHeight + j * tileHeight) + (0.5f * tileHeight);
                if (objectsMap[i + j * roomWidth] == int(ObjectType::Treasure)) {
                    treasurePos.push_back(std::pair(
                        posX,
                        posY
                    ));
                }
                else if (objectsMap[i + j * roomWidth] == int(ObjectType::Crab)) {
                    addObject(std::make_unique<Crab>(world, &(*textures)[2], 0.2f, b2Vec2(posX, posY)));
                }
                else if (objectsMap[i + j * roomWidth] == int(ObjectType::Crate)) {
                    addObject(std::make_unique<Crate>(world, &(*textures)[1], 0.2f, b2Vec2(posX, posY)));
                }
            }
        }
    }
}

/**
 * Display objects in the room.
 *
 * @param window on which objects will be drawn.
 */
void Room::displayObjects(sf::RenderWindow& window) const
{
    for (auto const& o : objects)
        o->display(window);
}

/**
 * Update objects in the room. If the objects gets out of the room, it is moved the the new room object list.
 *
 * @param elapsed time since last frame.
 */
void Room::updateObjects(sf::Time elapsed)
{
    for (auto it = objects.begin(); it != objects.end();) {
        it->get()->update(elapsed);
        int roomX = (int)(std::floor(it->get()->get_x() / (roomWidth * tileWidth)));
        int roomY = (int)(std::floor(it->get()->get_y() / (roomHeight * tileHeight)));

        // Move the object in an adjacent room if it left the current one.
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

/**
 * Add an object to the room.
 *
 * @param object to add.
 */
void Room::addObject(std::unique_ptr<Object> object)
{
    objects.push_back(std::move(object));
}

/**
 * Get the new room an object is in.
 *
 * @param roomX new room x position.
 * @param roomY new room y position.
 * @return the room the object is in.
 */
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

/**
 * Get the adjacent rooms.
 *
 * @return pointers to adjacent rooms.
 */
std::vector<Room*> Room::getAjacentRooms()
{
    return std::vector<Room*>{upRoom, downRoom, leftRoom, rightRoom};
}

/**
 * Get the positions of the treasures in the room.
 *
 * @return positions of the treasures in the room.
 */
std::vector<std::pair<int, int>> Room::getTreasurePos()
{
    return treasurePos;
}

/**
 * Find an available position in the room (not in a solid object).
 *
 * @return the available position coordinates.
 */
std::pair<float, float> Room::findAvailableCoinPosition()
{
    std::pair<float, float> pos(x * roomWidth * tileWidth, y * roomHeight * tileHeight);

    // Get a random position in the room.
    int dx = random_1_to_n(roomWidth - 2);
    int dy = random_1_to_n(roomHeight - 2);
    if (!objectsTilemap.empty()) {
        while (objectsTilemap[dx + dy * roomHeight] != 0) {
            // Try again if the coin was about to be created on another object.
            dx = random_1_to_n(roomWidth - 2);
            dy = random_1_to_n(roomHeight - 2);
        }
    }
    pos.first += (dx + 0.5f) * tileWidth;
    pos.second += (dy + 0.5f) * tileHeight;
    return pos;
}
