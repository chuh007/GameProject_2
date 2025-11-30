#pragma once
enum class Layer
{
	DEFAULT,
	BACKGROUND,
	// 밑에 변경 가능
	PLAYER,
	ENEMY,
	PROJECTILE,
	ENEMYPROJECTILE,
	END
};

enum class PenType
{
	RED, GREEN, MAGENTA,END
};

enum class BrushType
{
	HOLLOW, RED, GREEN, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode
{
	Once, Loop, Counted
};

enum class MoveState
{
	Stop, MoveTo, MoveDir
};

enum class PoolType
{
	Circle1,
};