#include "Enemy.h"

Enemy::Enemy(int x, int y)
{
	enemyRect.x = x;
	enemyRect.y = y;
}

Enemy::~Enemy()
{}

void Enemy::DrawEnemy(SDL_Surface* screenSurface, bool Front)
{
	if (Front)
	{
		temp = SDL_LoadBMP( "enemy.bmp" );
	}
	else
	{
		temp = SDL_LoadBMP( "enemy1.bmp" );
	}
	
	enemy = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_RGB888,0);
	SDL_FreeSurface(temp);

	SDL_BlitSurface( enemy, NULL, screenSurface, &enemyRect );
}

void Enemy::UpdateRect()
{

}

SDL_Rect Enemy::GetRect()
{
	return enemyRect;
}