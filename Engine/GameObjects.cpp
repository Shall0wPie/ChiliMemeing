#include "GameObjects.h"

GameObject::GameObject() : x(0), y(0),	dx(0), dy(0),
													tileXSize(0), tileYSize(0), 
													color({255, 255, 255})
{
}

void GameObject::SetColor(Color _color)
{
	color = _color;
}

bool GameObject::CheckCollision(const GameObject &obj) const
{
		return (x <= obj.x + obj.tileXSize &&
			obj.x <= x + tileXSize &&
			y <= obj.y + obj.tileYSize &&
			obj.y <= y + tileYSize);
}

Projectile::Projectile()
{
	tileXSize = 10;
	tileYSize = 10;
}

void Projectile::Launch(int x0, int y0, int x1, int y1)
{
	x = x0;
	y = y0;
	float delX = x1 - x0;
	float delY = y1 - y0;
	float c = sqrt(delX * delX + delY * delY);

	dx = delX/c * speed;
	dy = delY/c * speed;
}

void Projectile::Move()
{
	x += dx;
	y += dy;
}

void Projectile::Draw(Graphics &gfx) const
{
	gfx.MakeRect(x, y, tileXSize, tileYSize, Colors::Green);
}

Unit::Unit(int _x, int _y)
{
	x = _x;
	y = _y;
	tileXSize = 10;
	tileYSize = 10;
}

void Unit::Control(const Keyboard &kbd, const Mouse &mouse)
{
	bool adIsPresed = false;
	bool wsIsPresed = false;
	if (kbd.KeyIsPressed('W'))
	{
		dy = -speed;
		wsIsPresed = true;
	}
	if (kbd.KeyIsPressed('S'))
	{
		dy = speed;
		wsIsPresed = true;
	}
	if (kbd.KeyIsPressed('A'))
	{
		dx = -speed;
		adIsPresed = true;
	}
	if (kbd.KeyIsPressed('D'))
	{
		dx = speed;
		adIsPresed = true;
	}

	if (kbd.KeyIsPressed(VK_SHIFT))
	{
		if (adIsPresed)
			dx *= 2.0f;
		if (wsIsPresed)
			dy *= 2.0f;
	}

	if (mouse.LeftIsPressed())
	{
		bullets.emplace_back(Projectile());
		bullets.back().Launch(x, y, mouse.GetPosX(), mouse.GetPosY());
		bullets.back().x = x;
		bullets.back().y = y;
	}

	if (dx > friction)
		dx -= friction;
	else if (dx < -friction)
		dx += friction;
	else
		dx = 0;


	if (dy > friction)
		dy -= friction;
	else if (dy < -friction)
		dy += friction;
	else
		dy = 0;


	x += dx;
	y += dy;

	for (int i = 0; i < bullets.size(); i++)
		bullets[i].Move();
}


void Unit::Draw(Graphics &gfx) const
{
	gfx.PutPixel(x + 5, y,      color);
	gfx.PutPixel(x + 5, y + 1,  color);
	gfx.PutPixel(x + 5, y + 2,  color);
	gfx.PutPixel(x + 5, y + 8,  color);
	gfx.PutPixel(x + 5, y + 9,  color);
	gfx.PutPixel(x + 5, y + 10, color);
		
	gfx.PutPixel(x, y + 5,      color);
	gfx.PutPixel(x + 1, y + 5,  color);
	gfx.PutPixel(x + 2, y + 5,  color);
	gfx.PutPixel(x + 8, y + 5,  color);
	gfx.PutPixel(x + 9, y + 5,  color);
	gfx.PutPixel(x + 10, y + 5, color);
}

SizeableRectangle::SizeableRectangle(int _x, int _y)
{
	x = _x;
	y = _y;
	tileXSize = 50;
	tileYSize = 50;
}

void SizeableRectangle::Draw(Graphics &gfx) const
{
	gfx.MakeRect(x, y, tileXSize, tileYSize, color);
}

void SizeableRectangle::ControlSizes(const Keyboard &kbd)
{
	if (kbd.KeyIsPressed('W')) { y -= 2;	tileYSize += 2; }
	if (kbd.KeyIsPressed('S')) { tileYSize +=2; }
	if (kbd.KeyIsPressed('A')) { x -= 2;	tileXSize += 2; }
	if (kbd.KeyIsPressed('D')) { tileXSize += 2; }
			 
	if (kbd.KeyIsPressed(VK_UP))		{ tileYSize -= 2; }
	if (kbd.KeyIsPressed(VK_DOWN))  { y += 2; tileYSize -= 2; }
	if (kbd.KeyIsPressed(VK_LEFT))  { tileXSize -= 2; }
	if (kbd.KeyIsPressed(VK_RIGHT)) { x += 2; tileXSize -=2; }

	if (tileXSize < 0)
		tileXSize = 0;
	if (tileYSize < 0)
		tileYSize = 0;
}


