#include "ParticleSystem.h"
#include "myRandom.h"

ParticleSystem::ParticleSystem(sf::Texture* texture, float scale) : texture(texture)
{
}

void ParticleSystem::update(sf::Time elapsed)
{
    if (active)
        time += elapsed.asSeconds();
    for (auto it = particles.begin(); it != particles.end();) {
        it->get()->update(elapsed);
        if (it->get()->getLifetime() <= 0) {
            inactiveParticles.push_back(std::move(*it));
            it = particles.erase(it);
        }
        else {
            it++;
        }
    }
    
    if (time > timeBetweenSpawns) {
        time = 0;
        spawnParticle();
    }
}

void ParticleSystem::display(sf::RenderWindow& window) const
{
    sf::Sprite sprite;
    sf::CircleShape circle(0.6f);
    circle.setOrigin(sf::Vector2f(0.3f, 0.3f));
    for (auto const& particle : particles) {
        //sprite.setPosition(sf::Vector2f(particle->get_x(), particle->get_y()));
        circle.setPosition(sf::Vector2f(particle->get_x(), particle->get_y()));
        circle.setFillColor(sf::Color(0, 255, 0, 255 * alphaFromLifetime(particle->getLifetime())));
        //window.draw(sprite);
        window.draw(circle);
    }
}

void ParticleSystem::setPosition(sf::Vector2f pos)
{
    x = pos.x;
    y = pos.y;
}

void ParticleSystem::setRotation(float angle_)
{
    angle = angle_;
}

void ParticleSystem::setActive(bool flag)
{
    active = flag;
}

void ParticleSystem::spawnParticle()
{
    float particle_angle = angle + (random_0_to_1() - 0.5f) * dAngle;
    if (!inactiveParticles.empty()) {
        // There is at least one inactive particle. Use one of them instead of creating a new one.
        inactiveParticles[inactiveParticles.size() - 1]->init(x, y, speed, particle_angle, particleLifetime);
        particles.push_back(std::move(inactiveParticles[inactiveParticles.size() - 1]));
        inactiveParticles.pop_back();
    }
    else {
        // There are no inactive particle. Create a new one.
        auto particle = std::make_unique<Particle>();
        particle->init(x, y, speed, particle_angle, particleLifetime);
        particles.push_back(std::move(particle));
    }
}

float ParticleSystem::alphaFromLifetime(float lifetime) const {
    float value = 1 - (lifetime / particleLifetime);
    return 1 - value * value * value * value;

}