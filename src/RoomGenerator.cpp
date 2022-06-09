#include "RoomGenerator.h"
#include "TreasureManager.h"
#include "myRandom.h"



RoomGenerator::RoomGenerator()
{
    m_tileset = std::make_unique<sf::Texture>();
    // load the tileset texture
    if (!(*m_tileset).loadFromFile(tileset)) {
        std::cerr << "Could not open tileset\n";
        return;
    }
        
    emptyRoomTilemap = loadXMLroom(emptyRoomFile);
    for (auto file : treasureRoomFiles)
        treasureRoomTilemaps.push_back(loadXMLroom(file));
    for (auto file : standardRoomFiles)
        standardRoomTilemaps.push_back(loadXMLroom(file));
    
}

/**
 * Generate the rooms.
 * 
 * Starting from an initial room at position (0,0), the algorithm adds a room next to a previously
 * generated one until the total room count is nb_rooms.
 *
 * @param nb_rooms number of rooms to generate.
 * @return vector of rooms.
 */

std::vector<std::unique_ptr<Room>> RoomGenerator::generateMap(int nb_rooms) 
{
    float farthestRoomDistance = 0;
    std::vector<std::unique_ptr<Room>> rooms;
    std::map<std::pair<int, int>, int> available_positions;
    std::vector<std::pair<int, int>> adjacent_positions;
    adjacent_positions.push_back(std::pair(0, 1));
    adjacent_positions.push_back(std::pair(0, -1));
    adjacent_positions.push_back(std::pair(1, 0));
    adjacent_positions.push_back(std::pair(-1, 0));
    rooms.push_back(std::make_unique<Room>(0, 0));
    roomPositions.insert(std::pair(0, 0));
    for (auto pos : adjacent_positions)
        available_positions[pos] = 0;
    int cur_index = 1;
    for (int i = 0; i < nb_rooms - 1; i++) {
        // Select a random position for a room, adjacent to a room already created.
        int new_room_index = random_1_to_n((int)available_positions.size()) - 1;
        auto it = std::begin(available_positions);
        std::advance(it, new_room_index);
        auto [new_x, new_y] = it->first;

        auto new_room = std::make_unique<Room>(new_x, new_y); // Create the new room.

        // Open a path between the two adjacent rooms
        new_room->open_path(rooms[it->second]->get_position());
        rooms[it->second]->open_path(new_room->get_position());

        new_room->linkToRoom(rooms[it->second].get());
        rooms[it->second]->linkToRoom(new_room.get());
        rooms.push_back(std::move(new_room));
        roomPositions.insert(std::pair(new_x, new_y));
        available_positions.erase(it);

        // Add the rooms adjacent to the one just created to the available position set.
        for (auto const& [adj_x, adj_y] : adjacent_positions) {
            if (!roomPositions.contains(std::pair(adj_x + new_x, adj_y + new_y)))
                available_positions[std::pair(adj_x + new_x, adj_y + new_y)] = cur_index;
        }
        cur_index++;

        // Update farthest room.
        float roomDistance = new_x * new_x + new_y * new_y;
        if (roomDistance > farthestRoomDistance) {
            farthestRoomDistance = roomDistance;
            farthestRoomPos = std::pair<int, int>(new_x, new_y);
        }
    }

    
    return rooms;
}

/**
 * Build the rooms.
 * 
 * Select a type for rooms (standard room or treasure room) and a random variant before building
 * the rooms and generating objets in them.
 *
 * @param world box2d world.
 * @param rooms vector of rooms.
 * @param textures vector of textures.
 * @return the vector of rooms built.
 */
std::vector<std::unique_ptr<Room>> RoomGenerator::buildRooms(b2World* world, std::vector<std::unique_ptr<Room>> rooms, std::vector<sf::Texture>* textures)
{
    std::vector<int> deadEnds;
    std::vector<int> normalRooms;
    std::vector<bool> treasureRooms(rooms.size(), false);

    // Find rooms that are dead ends and those that are not.
    for (int i = 0; i < rooms.size(); i++) {
        if (i > 0) {
            if (rooms[i]->isDeadEnd())
                deadEnds.push_back(i);
            else
                normalRooms.push_back(i);
        }
    }

    if (deadEnds.size() >= treasuresCount) {
        // Create treasure rooms in random dead ends.
        for (int i = 0; i < treasuresCount; i++) {
            int randomIndex = random_1_to_n(deadEnds.size()) - 1;
            auto it = deadEnds.begin() + randomIndex;
            treasureRooms[*it] = true;
            deadEnds.erase(it);
        }

    }
    else {
        // Create treasure rooms in all dead ends.
        for (auto const& id : deadEnds) {
            treasureRooms[id] = true;
        }
        // Create remaining treasure rooms in random other rooms.
        for (int i = 0; i < treasuresCount - deadEnds.size(); i++) {
            if (normalRooms.size() <= 0) {
                break;
            }
            int randomIndex = random_1_to_n(normalRooms.size()) - 1;
            auto it = normalRooms.begin() + randomIndex;
            treasureRooms[*it] = true;
            normalRooms.erase(it);
        }
    }

    rooms[0]->build(world, m_tileset.get(), emptyRoomTilemap, std::vector<int> {});

    for (int i = 1; i < rooms.size(); i++) {
        if (treasureRooms[i]) {
            // Use a treasure room tilemap for treasure rooms.
            int roomType = random_1_to_n(treasureRoomTilemaps.size()) - 1;
            rooms[i]->build(world, m_tileset.get(), emptyRoomTilemap, treasureRoomTilemaps[roomType]);
            rooms[i]->generateObjects(world, treasureRoomTilemaps[roomType], textures);
        }
        else
        {
            // Use a standard room tilemap for others rooms.
            if (standardRoomTilemaps.empty() || random_1_to_n(100) < (int)(emptyRoomProportion * 100))
                rooms[i]->build(world, m_tileset.get(), emptyRoomTilemap, std::vector<int> {});
            else {
                int roomType = random_1_to_n(standardRoomTilemaps.size()) - 1;
                rooms[i]->build(world, m_tileset.get(), emptyRoomTilemap, standardRoomTilemaps[roomType]);
                rooms[i]->generateObjects(world, standardRoomTilemaps[roomType], textures);
            }
        }
    }

    return rooms;
}

/**
 * Get the position of the farthest room from player spawn position.
 *
 * @return farthest room position.
 */
std::pair<int, int> RoomGenerator::getFarthestRoomPos() const
{
    return farthestRoomPos;
}

/**
 * Get a random position of a room.
 *
 * @return pair of integers representing the room position.
 */
std::pair<int, int> RoomGenerator::getRandomRoomPos() const
{
    auto it = std::begin(roomPositions);
    std::advance(it, random_1_to_n(roomPositions.size()) - 1);
    return *it;
}

/**
 * Load an xml room file.
 *
 * @param file name of the file to open.
 * @return data in the form of an integer vector.
 */

std::vector<int> RoomGenerator::loadXMLroom(std::string file) const
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file.c_str());
    
    std::vector<int> data;

    if (!result)
    {
        std::cerr << "Could not open map file because " << result.description() << std::endl;
        return std::vector<int> {};
    }
    std::string csv = doc.child("map").child("layer").child("data").text().get();
    std::string delimiter = ",";
    std::string token;
    std::erase(csv, '\n');
    size_t pos = 0;
    while ((pos = csv.find(delimiter)) != std::string::npos) {
        token = csv.substr(0, pos);
        data.push_back(stoi(token));
        csv.erase(0, pos + delimiter.length());
    }
    data.push_back(stoi(csv));
    return data;
}
