#include <gtest/gtest.h>
#include "RoomGenerator.h"

TEST(TestMapGeneration, TestRoom) {
    RoomGenerator roomGenerator;
    int nb_rooms = 100;
    /*
    auto rooms = roomGenerator.generateMap(nb_rooms);
    std::map<std::pair<int, int>, Room> positions_to_rooms;
    for (auto& room : rooms) {
        positions_to_rooms[room.get_position()] = room;
    }
    EXPECT_EQ(0, 1);  // test non terminé
    */
}
