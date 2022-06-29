#include "ParticleSystem.h"
#include "myRandom.h"

ParticleSystem::ParticleSystem(sf::Texture* texture) : texture(texture)
{
}

/**
 * Update the particles, generate new ones, or make them inactive if their lifetime reaches zero.
 *
 * @param elapsed time since last frame.
 */
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

/**
 * Display the bubbles on the window.
 *
 * @param window on which the bubbles are drawn.
 */
void ParticleSystem::display(sf::RenderWindow& window) const
{
    sf::Sprite particleSprite;
    particleSprite.setTexture(*texture);
    particleSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    particleSprite.setScale(sf::Vector2f(0.1f, 0.1f));
    for (auto const& particle : particles) {
        particleSprite.setPosition(sf::Vector2f(particle->get_x(), particle->get_y()));
        particleSprite.setColor(sf::Color(255, 255, 255, 255 * alphaFromLifetime(particle->getLifetime())));
        window.draw(particleSprite);
    }
}

/**
 * Change the position of the particle system.
 *
 * @param pos : new position of the particle system.
 */
void ParticleSystem::setPosition(sf::Vector2f pos)
{
    x = pos.x;
    y = pos.y;
}

/**
 * Change the rotation of the particle system.
 *
 * @param angle_ : new angle of the particle system.
 */
void ParticleSystem::setRotation(float angle_)
{
    angle = angle_;
}

/**
 * Change whether the particle system spawns particles or not.
 *
 * @param flag : true if the particle system has to spawn particles.
 */
void ParticleSystem::setActive(bool flag)
{
    active = flag;
}

/**
 * Spawn a particle.
 */
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

/**
 * Calculate the alpha of the particle depending on it's remaining lifetime.
 *
 * @param lifetime of the particle.
 */
float ParticleSystem::alphaFromLifetime(float lifetime) const {
    float value = 1 - (lifetime / particleLifetime);
    return 1 - value * value * value * value;

}