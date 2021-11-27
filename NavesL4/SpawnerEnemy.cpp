#include "SpawnerEnemy.h"

SpawnerEnemy::SpawnerEnemy(float x, float y, Game* game)
	: BaseEnemy("res/enemigo2.png", x, y, 80, 80, game) {

	timeToGenerate = 40;
	this->lifesLeft = 3;

	aDying = new Animation("res/wizard_death.png", width, height,
		800, 80, 6, 10, false, game);
	aMoving = new Animation("res/wizard_fly_forward.png", width, height,
		480, 80, 6, 6, true, game);
	aIdle = new Animation("res/wizard_idle.png", width, height,
		800, 80, 6, 10, true, game);

	animation = aIdle; // la animacion que se va a pintar
	state = game->stateIdle;

}

void SpawnerEnemy::update() {
	if (timeToGenerate >= 0)
		timeToGenerate--;

	BaseEnemy::update();
}

list<Enemy*> SpawnerEnemy::spawnEnemies() {
	list<Enemy*> ret;
	
	// Used for more realistic random values in X axis
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distrX(x-80, x+80); 
	std::uniform_int_distribution<int> distrVY(8, 18);
	for (int i = 0; i < enemiesToGenerate; i++) {
		int newEnemyX = distrX(eng);
		Enemy* newEnemy = new Enemy(newEnemyX, y - 10, game);
		newEnemy->vy = -1 * distrVY(eng);
		newEnemy->state == game->stateMoving;
		ret.push_back(newEnemy);
	}
	timeToGenerate = 300;
	return ret;
}