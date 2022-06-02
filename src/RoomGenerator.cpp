#include "RoomGenerator.h"


int random_1_to_n(int const nbMax)
{
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    std::uniform_int_distribution<> distribution(1, nbMax);
    return distribution(engine);
}


RoomGenerator::RoomGenerator()
{
    m_tileset = std::make_unique<sf::Texture>();
    // load the tileset texture
    if (!(*m_tileset).loadFromFile(tileset)) {
        std::cerr << "Could not open tileset\n";
        return;
    }
        

    for (int i = 0; i < roomFiles.size(); i++) {
        roomTileMaps.push_back(std::vector<int> {});
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(roomFiles[i].c_str());

        if (!result)
        {
            std::cerr << "Could not open map file because " << result.description() << std::endl;
            return;
        }
        std::string csv = doc.child("map").child("layer").child("data").text().get();
        std::string delimiter = ",";
        std::string token;
        std::erase(csv, '\n');
        size_t pos = 0;
        while ((pos = csv.find(delimiter)) != std::string::npos) {
            token = csv.substr(0, pos);
            roomTileMaps[i].push_back(stoi(token));
            csv.erase(0, pos + delimiter.length());
        }
        roomTileMaps[i].push_back(stoi(csv));

    }
}

std::vector<std::unique_ptr<Room>> RoomGenerator::generateMap(b2World* world, int nb_rooms) const
{
    std::vector<std::unique_ptr<Room>> rooms;
    std::set<std::pair<int, int>> positions;
    std::map<std::pair<int, int>, int> available_positions;
    std::vector<std::pair<int, int>> adjacent_positions;
    adjacent_positions.push_back(std::pair(0, 1));
    adjacent_positions.push_back(std::pair(0, -1));
    adjacent_positions.push_back(std::pair(1, 0));
    adjacent_positions.push_back(std::pair(-1, 0));
    rooms.push_back(std::make_unique<Room>(0, 0));
    positions.insert(std::pair(0, 0));
    for (auto pos : adjacent_positions)
        available_positions[pos] = 0;
    int cur_index = 1;
    for (int i = 0; i < nb_rooms - 1; i++) {
        int new_room_index = random_1_to_n((int)available_positions.size()) - 1;
        auto it = std::begin(available_positions);
        std::advance(it, new_room_index);
        auto [new_x, new_y] = it->first;
        auto new_room = std::make_unique<Room>(new_x, new_y);
        new_room->open_path(rooms[it->second]->get_position());
        rooms[it->second]->open_path(new_room->get_position());
        rooms.push_back(std::move(new_room));
        positions.insert(std::pair(new_x, new_y));
        available_positions.erase(it);
        for (auto const& [adj_x, adj_y] : adjacent_positions) {
            if (!positions.contains(std::pair(adj_x + new_x, adj_y + new_y)))
                available_positions[std::pair(adj_x + new_x, adj_y + new_y)] = cur_index;
        }
        cur_index++;
    }
    for (auto &room : rooms) {
        room->build(world, m_tileset.get(), roomTileMaps[0], corridorWidth);
    }
    return rooms;
}

void RoomGenerator::buildCorridors()
{

}
