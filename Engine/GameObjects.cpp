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
	x = float(x0);
	y = float(y0);
	float delX = float(x1 - x0);
	float delY = float(y1 - y0);
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
	gfx.MakeRect(int(x), int(y), tileXSize, tileYSize, Colors::Green);
}

Player::Player(int _x, int _y)
{
	x = float(_x);
	y = float(_y);
	tileXSize = 10;
	tileYSize = 10;
}

void Player::Control(const Keyboard &kbd, const Mouse &mouse)
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
		bullets.back().Launch(int(x), int(y), mouse.GetPosX(), mouse.GetPosY());
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


void Player::Draw(Graphics &gfx) const
{
	const int x_int = int(x);
	const int y_int = int(y);

	gfx.PutPixel(x_int + 5, y_int,      color);
	gfx.PutPixel(x_int + 5, y_int + 1,  color);
	gfx.PutPixel(x_int + 5, y_int + 2,  color);
	gfx.PutPixel(x_int + 5, y_int + 8,  color);
	gfx.PutPixel(x_int + 5, y_int + 9,  color);
	gfx.PutPixel(x_int + 5, y_int + 10, color);
		
	gfx.PutPixel(x_int	  , y_int + 5,  color);
	gfx.PutPixel(x_int + 1 , y_int + 5,  color);
	gfx.PutPixel(x_int + 2 , y_int + 5,  color);
	gfx.PutPixel(x_int + 8 , y_int + 5,  color);
	gfx.PutPixel(x_int + 9 , y_int + 5,  color);
	gfx.PutPixel(x_int + 10, y_int + 5,  color);
}

SizeableRectangle::SizeableRectangle(int _x, int _y)
{
	x = float(_x);
	y = float(_y);
	tileXSize = 50;
	tileYSize = 50;
}

void SizeableRectangle::Draw(Graphics &gfx) const
{
	gfx.MakeRect(int(x), int(y), tileXSize, tileYSize, color);
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


