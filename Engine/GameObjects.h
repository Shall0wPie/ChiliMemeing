#pragma once
#include "Graphics.h"
#include "MainWindow.h"

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
	static constexpr float speed = 5;
public:
	Projectile();
	void Launch(int x0, int y0, int x1, int y1);
	void Move();
	void Draw(Graphics &gfx) const;
};

class Player : public GameObject
{
private:
	static constexpr float friction = 0.1f;
	static constexpr float speed = 4 + friction;
public:
	std::vector<Projectile> bullets;

	Player(int _x, int _y);
	void Control(const Keyboard &kbd, const Mouse &mouse);
	void Draw(Graphics &gfx) const;
};


class SizeableRectangle : public GameObject
{
public:
	SizeableRectangle(int _x, int _y);
	void Draw(Graphics &gfx) const;
	void ControlSizes(const Keyboard &kbd);
};
