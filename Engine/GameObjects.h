#pragma once
#include "Graphics.h"
#include "MainWindow.h"
#include "Timer.h"

class GameObject
{
public:
	float x;
	float y;
	float dx;
	float dy;
	int tileXSize;
	int tileYSize;
	Color color;
	static Timer timer;
	static float dt;
private:
public:
	GameObject();
	virtual void Draw(Graphics &gfx) const = 0;
	void SetColor(Color _color);
	bool CheckCollision(const GameObject &obj) const;
};

class Projectile : public GameObject
{
private:
	static constexpr float speed = 5*60;
public:
	Projectile();
	void Launch(float x0, float y0, float x1, float y1);
	void Move();
	void Draw(Graphics &gfx) const;
};

class Player : public GameObject
{
private:
	static constexpr float friction = 6.0f;
	static constexpr float speed = 4*60 + friction;
public:
	std::vector<Projectile> bullets;

	Player(float _x, float _y);
	void Control(const Keyboard &kbd, const Mouse &mouse);
	void Draw(Graphics &gfx) const;
};

class SizeableRectangle : public GameObject
{
public:
	SizeableRectangle(float _x, float _y);
	void ControlSizes(const Keyboard &kbd);
	void Draw(Graphics &gfx) const;
};

class StupidMob : public GameObject
{
private:
	static constexpr float speed = 1*60;
public:
	bool isAlive;
	StupidMob(float _x, float _y);
	void MoveTowards(GameObject &target);
	void Respawn(float _x, float _y, const Graphics &gfx);
	void Draw(Graphics &gfx) const;
};
