#include <gtest/gtest.h>
#include "RoomGenerator.h"


TEST(TestMapGeneration, TestConnectionsBetweenRoom) {
    RoomGenerator roomGenerator;
    int nb_rooms = 100;
    auto rooms = roomGenerator.generateMap(nb_rooms);
    std::map<std::pair<int, int>, int> pos_to_room_index;
    
    for (int i = 0; i < rooms.size(); i++) {
        pos_to_room_index[rooms[i]->get_position()] = i;
    }
    for (auto &[pos, id] : pos_to_room_index) {
        if (rooms[id]->is_opened(0)) {
            auto it = pos_to_room_index.find(std::pair<int, int>(pos.first, pos.second + 1));
            EXPECT_TRUE(it != pos_to_room_index.end());
            if (it != pos_to_room_index.end())
                EXPECT_TRUE(rooms[it->second]->is_opened(1));
        }
        if (rooms[id]->is_opened(1)) {
            auto it = pos_to_room_index.find(std::pair<int, int>(pos.first, pos.second - 1));
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