#include "TileMap.h"
#include "myRandom.h"

/**
 * Load the tilemap. Each tile has a random rotation.
 *
 * @param tileset textures of the tiles.
 * @param tileSize size of the sprite of a tile in pixels.
 * @param tiles vector of integers representing the tiles in the room.
 * @param width of the tilemap
 * @param height of the tilemap
 */
void TileMap::load(sf::Texture* tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height)
{
    m_tileset = tileset;
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];
            // find its position in the tileset texture
            
            int tu = tileNumber % (m_tileset->getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset->getSize().x / tileSize.x);
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            std::vector<sf::Vector2f> corners = { sf::Vector2f(tu * tileSize.x, tv * tileSize.y) ,
                sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y) ,
                sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y) ,
                sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y) };
            int rotation = random_1_to_n(4) - 1;
            // define its 4 texture coordinates
            for (int k = 0; k < 4; k++) 
                quad[k].texCoords = corners[(rotation + k) % 4];
        }
}

/**
 * Draw the tilemap.
 */
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}
