#include "Player.h"
enum state{Sleep, Follow, Attack, Flee};

class Monster {
public:
	Monster(Player* player);
	void display() const;
	void update();
private:
	double x;
	double y;
	double const attack_cooldown = 5;
	double const attack_duration = 1;
	double current_cooldown = 2;
	state action = Sleep;
	Player* player;
};