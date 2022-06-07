#include "FishSpawner.h"

FishSpawner::FishSpawner(sf::Texture* fishTexture, Player* player, SoundHandler* soundHandler) : 
    fishTexture(fishTexture), player(player), soundHandler(soundHandler)
{
    spawnFishRoom(1, 0);
    spawnFishRoom(0, 1);
    spawnFishRoom(-1, 0);
    spawnFishRoom(0, -1);
}

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


void FishSpawner::display(sf::RenderWindow& window) const {
    for (auto const& fish : fishVector) {
        fish->display(window);
    }
}

void FishSpawner::spawnFish(float x, float y)
{
    if (!inactiveFish.empty()) {
        inactiveFish[inactiveFish.size() - 1]->init(x, y);
        fishVector.push_back(std::move(inactiveFish[inactiveFish.size() - 1]));
        inactiveFish.pop_back();
    }
    else {
        fishVector.push_back(std::make_unique<Fish>(fishTexture, this, player, 0.2f, x, y, soundHandler));
    }
}

void FishSpawner::spawnFishRoom(int dx, int dy)
{
    int numberOfFish = random_1_to_n(maxFishInRoom + 1) - 1;
    for (int i = 0; i < numberOfFish; i++) {
        float x = ((player->getRoomX() + dx) * roomWidth + random_1_to_n(roomWidth) - 1) * tileWidth;
        float y = ((player->getRoomY() + dy) * roomHeight + random_1_to_n(roomHeight) - 1) * tileHeight;
        spawnFish(x, y);
    }
}

bool FishSpawner::closeToPlayer(float x, float y) const
{
    float roomX = std::floor(x / (roomWidth * tileWidth));
    float roomY = std::floor(y / (roomWidth * tileWidth));
    return std::abs(roomX - player->getRoomX()) + std::abs(roomY - player->getRoomY()) <= 1;
}