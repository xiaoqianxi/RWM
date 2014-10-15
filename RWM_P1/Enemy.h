#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include <SDL.h>
#include <Box2D/Box2D.h>

class Enemy{
private:
	
	SDL_Rect enemyRect;
	SDL_Surface* enemy, *temp;

public:
	Enemy(int x, int y);
	~Enemy();

	void DrawEnemy(SDL_Surface* screenSurface, bool Front);
	
	void UpdateRect();

	SDL_Rect GetRect();


};


#endif // __ENEMY_H_INCLUDED__