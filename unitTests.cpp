#include <gtest/gtest.h>
#include "RoomGenerator.h"
#include "TreasureManager.h"

/**
 * Check that when a room is open toward another room, the latter is open toward the first one.
 */
TEST(TestMapGeneration, TestConnectionsBetweenRoom) {
    RoomGenerator roomGenerator;
    int nb_rooms = 100;
    auto rooms = roomGenerator.generateMap(nb_rooms);
    std::map<std::pair<int, int>, int> pos_to_room_index;
    
    for (int i = 0; i < rooms.size(); i++) {
        pos_to_room_index[rooms[i]->get_position()] = i;
    }
    for (auto const &[pos, id] : pos_to_room_index) {
        if (rooms[id]->is_opened(0)) {
            auto it = pos_to_room_index.find(std::pair<int, int>(pos.first, pos.second - 1));
            EXPECT_TRUE(it != pos_to_room_index.end());
            if (it != pos_to_room_index.end())
                EXPECT_TRUE(rooms[it->second]->is_opened(1));
        }
        if (rooms[id]->is_opened(1)) {
            auto it = pos_to_room_index.find(std::pair<int, int>(pos.first, pos.second + 1));
            EXPECT_TRUE(it != pos_to_room_index.end());
            if (it != pos_to_room_index.end())
                EXPECT_TRUE(rooms[it->second]->is_opened(0));
        }
        if (rooms[id]->is_opened(2)) {
            auto it = pos_to_room_index.find(std::pair<int, int>(pos.first - 1, pos.second));
            EXPECT_TRUE(it != pos_to_room_index.end());
            if (it != pos_to_room_index.end())
                EXPECT_TRUE(rooms[it->second]->is_opened(3));
        }
        if (rooms[id]->is_opened(3)) {
            auto it = pos_to_room_index.find(std::pair<int, int>(pos.first + 1, pos.second));
            EXPECT_TRUE(it != pos_to_room_index.end());
            if (it != pos_to_room_index.end())
                EXPECT_TRUE(rooms[it->second]->is_opened(2));
        }
    }
}

/**
 * Check that every room is accessible.
 */
TEST(TestMapGeneration, TestRoomAccessibility) {
    RoomGenerator roomGenerator;
    int nb_rooms = 100;
    auto rooms = roomGenerator.generateMap(nb_rooms);
    std::map<std::pair<int, int>, int> pos_to_room_index;

    for (int i = 0; i < rooms.size(); i++) {
        pos_to_room_index[rooms[i]->get_position()] = i;
    }
    std::vector<std::pair<int, int>> adjacent_positions;
    adjacent_positions.push_back(std::pair(0, 1));
    adjacent_positions.push_back(std::pair(0, -1));
    adjacent_positions.push_back(std::pair(1, 0));
    adjacent_positions.push_back(std::pair(-1, 0));
    std::set<int> explored_rooms;
    std::set<int> rooms_to_explore = {0};

    // Graph connectivity test algorithm.
    while (!rooms_to_explore.empty()) {
        auto room_id = rooms_to_explore.begin();
        auto [pos_x, pos_y] = rooms[*room_id]->get_position();
        for (auto const& [adj_x, adj_y] : adjacent_positions) {
            auto adjacent_room = pos_to_room_index.find(std::pair<int, int>(pos_x + adj_x, pos_y + adj_y));
            if (adjacent_room != pos_to_room_index.end() && !explored_rooms.contains(adjacent_room->second)) {
                rooms_to_explore.insert(adjacent_room->second);
            }
        }
        explored_rooms.insert(*room_id);
        rooms_to_explore.erase(room_id);

    }
    ASSERT_EQ(explored_rooms.size(), nb_rooms);
}

TEST(TestTreasures, TestNumberOfTreasures) {
    b2Vec2 gravity(0.0f, 0.0f);
    auto world = std::make_unique<b2World>(gravity);
    RoomGenerator roomGenerator;
    int nb_rooms = 100;

    auto rooms = roomGenerator.generateMap(nb_rooms);


    std::vector<sf::Texture> textures(11, sf::Texture());
    rooms = roomGenerator.buildRooms(world.get(), std::move(rooms), &textures);
    TreasureManager treasureManager{nullptr, nullptr, nullptr, nullptr};
    treasureManager.createTreasures(rooms);
    int nbTreasures = 0;
    int nbCoins = 0;
    for (auto const& room : rooms) {
        std::vector<std::unique_ptr<Object>> const* objects = room->getObjects();
        for (auto const& object : *objects) {
            // Count the number of each type of treasure in the room.
            auto const* treasure = dynamic_cast<Treasure*>(object.get());
            if (treasure) {
                if (treasure->getIsCoin())
                    nbCoins++;
                else
                    nbTreasures++;
            }
        }
    }
    ASSERT_EQ(nbCoins, coinCount);
    ASSERT_EQ(nbTreasures, treasuresCount);
}