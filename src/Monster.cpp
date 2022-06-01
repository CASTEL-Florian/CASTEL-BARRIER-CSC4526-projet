#include "Monster.h"


Monster::Monster(Player* player) : player(player)
{
}

void Monster::display() const {

}

void Monster::update() {
	std::cout << current_cooldown << "\n";
	if (action == Follow && current_cooldown <= 0) {
		action = Attack;
		current_cooldown = attack_cooldown;
	}
	if (action == Attack) {

	}
}