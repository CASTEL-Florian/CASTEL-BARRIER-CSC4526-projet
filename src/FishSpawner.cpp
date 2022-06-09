#include "FishSpawner.h"

FishSpawner::FishSpawner(sf::Texture* fishTexture, Player* player, SoundHandler* soundHandler) : 
    fishTexture(fishTexture), player(player), soundHandler(soundHandler)
{
    spawnFishRoom(1, 0);
    spawnFishRoom(0, 1);
    spawnFishRoom(-1, 0);
    spawnFishRoom(0, -1);
}

/**
 * Update the fish, generate new ones or make theme inactive if necessary.
 *
 * @param elapsed time since last frame.
 */
void FishSpawner::update(sf::Time elapsed) {
    for (auto it = fishVector.begin(); it != fishVector.end();) {
        it->get()->update(elapsed);
        if (!closeToPlayer(it->get()->get_x(), it->get()->get_y())) {
            inactiveFish.push_back(std::move(*it));
                it = fishVector.erase(it);
        }
        else {
            it++;
        }
    }
    int newPlayerX = player->getRoomX();
    int newPlayerY = player->getRoomY();
    if (oldPlayerX != newPlayerX || oldPlayerY != newPlayerY) {
        spawnFishRoom(newPlayerX - oldPlayerX, newPlayerY - oldPlayerY);
        if (oldPlayerX != newPlayerX) {
            spawnFishRoom(0, 1);
            spawnFishRoom(0, -1);
        }
        else {
            spawnFishRoom(1, 0);
            spawnFishRoom(-1, 0);
        }
        oldPlayerX = newPlayerX;
        oldPlayerY = newPlayerY;
    }

}

/**
 * Display every fish.
 *
 * @param window on which objects have to be drawn.
 */
void FishSpawner::display(sf::RenderWindow& window) const {
    for (auto const& fish : fishVector) {
        fish->display(window);
    }
}

/**
 * Spawn a Fish.
 * 
 * Reuse an inactive fish if there is one or create a new fish.
 *
 * @param x x position of the fish.
 * @param y y position of the fish.
 */
void FishSpawner::spawnFish(float x, float y)
{
    if (!inactiveFish.empty()) {
        inactiveFish[inactiveFish.size() - 1]->init(x, y);
        fishVector.push_back(std::move(inactiveFish[inactiveFish.size() - 1]));
        inactiveFish.pop_back();
    }
    else {
        fishVector.push_back(std::make_unique<Fish>(fishTexture, player, 0.2f, x, y, soundHandler));
    }
}

/**
 * Spawn a random number of fish in a room.
 *
 * @param dx x position of the room in which generate fish minus the x position of the room where the player is.
 * @param dy y position of the room in which generate fish minus the y position of the room where the player is.
 */
void FishSpawner::spawnFishRoom(int dx, int dy)
{
    int numberOfFish = random_1_to_n(maxFishInRoom + 1) - 1;
    for (int i = 0; i < numberOfFish; i++) {
        float x = ((player->getRoomX() + dx) * roomWidth + random_1_to_n(roomWidth) - 1) * tileWidth;
        float y = ((player->getRoomY() + dy) * roomHeight + random_1_to_n(roomHeight) - 1) * tileHeight;
        spawnFish(x, y);
    }
}

/**
 * Determine if a position of an object is "close enough" to the player to keep it active.
 *
 * The object is kept active if it is in the same room as the player or if it is in an adjacent room.
 * 
 * @param x position of the object.
 * @param y position of the object.
 * @return true if the object is close enough.
 */
bool FishSpawner::closeToPlayer(float x, float y) const
{
    float roomX = std::floor(x / (roomWidth * tileWidth));
    float roomY = std::floor(y / (roomWidth * tileWidth));
    return std::abs(roomX - player->getRoomX()) + std::abs(roomY - player->getRoomY()) <= 1;
}