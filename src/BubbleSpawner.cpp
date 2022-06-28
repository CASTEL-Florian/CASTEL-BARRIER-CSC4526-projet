#include "BubbleSpawner.h"

BubbleSpawner::BubbleSpawner(sf::Texture* bubbleTexture, Player* player, OxygenBar* oxygenBar, SoundHandler* soundHandler) :
   bubbleTexture(bubbleTexture), player(player), oxygenBar(oxygenBar), soundHandler(soundHandler)
{
}

void BubbleSpawner::update(sf::Time elapsed)
{
    time += elapsed.asSeconds();
    if (time > timeBetweenSpawn) {
        time = 0;
        float r = minSpawnRadius + random_0_to_1() * (maxSpawnRadius - minSpawnRadius);
        float angle = random_0_to_1() * b2_pi * 2;
        float x = player->get_x() + (r * std::cosf(angle));
        float y = player->get_y() + (r * std::sinf(angle));
        spawnBubble(x, y);
    }
    for (auto it = bubbleVector.begin(); it != bubbleVector.end();) {
        it->get()->update(elapsed);
        if (!it->get()->isAlive()) {
            inactiveBubbles.push_back(std::move(*it));
            it = bubbleVector.erase(it);
        }
        else {
            it++;
        }
    }
}

void BubbleSpawner::display(sf::RenderWindow& window) const
{
    for (auto const& bubble : bubbleVector) {
        bubble->display(window);
    }
}

void BubbleSpawner::spawnBubble(float x, float y)
{
    if (!inactiveBubbles.empty()) {
        // There is at least one inactive bubble. Use one of them instead of creating a new one.
        inactiveBubbles[inactiveBubbles.size() - 1]->init(x, y);
        bubbleVector.push_back(std::move(inactiveBubbles[inactiveBubbles.size() - 1]));
        inactiveBubbles.pop_back();
    }
    else {
        // There are no inactive bubble. Create a new one.
        auto bubble = std::make_unique<Bubble>(bubbleTexture, player, oxygenBar, soundHandler);
        bubble->init(x, y);
        bubbleVector.push_back(std::move(bubble));
    }
}
