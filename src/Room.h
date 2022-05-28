#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
#include <iostream>
class Room
{
public:
	Room(int x, int y);
	void open_path(std::pair<int, int> const& target);
	void display(sf::RenderWindow &window) const;
	std::pair<int,int> get_position() const;
	bool is_opened(int direction);
	int get_x() const;
	int get_y() const;
private:
	int x;
	int y;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};

