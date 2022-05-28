#include "Monster.h"


void Monster::display() const {

}

void Monster::update() {
	if (action == Follow && current_cooldown <= 0) {
		action = Attack;
		current_cooldown = attack_cooldown;
	}
	if (action == Attack) {

	}
}