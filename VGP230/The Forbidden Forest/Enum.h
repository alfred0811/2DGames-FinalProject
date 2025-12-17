#pragma once

enum EntityType : int
{
	ET_NONE = 0,            // 0000
	ET_PLAYER = 1 << 0,       // 0001
	ET_PLAYER_ATTACK = 1 << 1,
	ET_TILE = 1 << 2,       // 0100
	ET_ENEMY = 1 << 3,       // 1000
	ET_PICKUP = 1 << 4,       // 1 0000
	ET_ENEMY_ATTACK = 1 << 5
};

enum TileType : int
{
	TT_NONE = 0,    // 0.......0000
	TT_GROUND,
	TT_WALL,
	TT_WATER,
	TT_GROUND2
};

enum class State
{
	Start,
	RunGame,
	End
};