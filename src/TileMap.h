#include <SFML/Graphics.hpp>
#include <iostream>


class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(sf::Texture* tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::VertexArray m_vertices;
    sf::Texture* m_tileset;
};