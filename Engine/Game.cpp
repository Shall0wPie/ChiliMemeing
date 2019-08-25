/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	blessRng( rd()),
	xRng(0 , gfx.ScreenWidth - 20),
	yRng(0 , gfx.ScreenHeight - 20)
{
	crossHair.SetColor({ 255, 0, 0});

	int mobsTospawn = 12;

	for (int i = 0; i < mobsTospawn; i++)
	{
		mobs.emplace_back(StupidMob(0, 0));
		//mobs[i].Respawn();
	}
}

Game::~Game()
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	crossHair.Control(wnd.kbd, wnd.mouse);
	CheckBorderCollision(crossHair);
	
	for (int i = 0; i < mobs.size(); i++)
	{
		mobs[i].MoveTowards(crossHair);
		CheckBorderCollision(mobs[i]);
	}

	for (int bulletCounter = 0; bulletCounter < crossHair.bullets.size(); bulletCounter++)
	{
		if (CheckBorderCollision(crossHair.bullets[bulletCounter]))
		{
			crossHair.bullets.erase(crossHair.bullets.begin() + bulletCounter);
			bulletCounter--;
			continue;
		}

		for (int mobCounter = 0; mobCounter < mobs.size(); mobCounter++)
		{
			if (crossHair.bullets[bulletCounter].CheckCollision(mobs[mobCounter]))
			{
				mobs[mobCounter].Respawn(xRng(blessRng), yRng(blessRng), gfx);
				crossHair.bullets.erase(crossHair.bullets.begin() + bulletCounter);
				bulletCounter--;
				break;
			}
		}
	}
}

void Game::ComposeFrame()
{
	crossHair.Draw(gfx);

	for (int i = 0; i < mobs.size(); i++)
		mobs[i].Draw(gfx);

	for (int i = 0; i < crossHair.bullets.size(); i++)
		crossHair.bullets[i].Draw(gfx);
}


bool Game::CheckBorderCollision(GameObject &obj)
{
	bool isColliding = false;
	if (obj.x < 0)
	{
		obj.x = 0;
		isColliding = true;
	}
	else if (obj.x > float(gfx.ScreenWidth - obj.tileXSize - 1))
	{
		obj.x = float(gfx.ScreenWidth - obj.tileXSize - 1);
		isColliding = true;
	}

	if (obj.y < 0)
	{
		obj.y = 0;
		isColliding = true;
	}
	else if (obj.y > float(gfx.ScreenHeight - obj.tileYSize - 1))
	{
		obj.y = float(gfx.ScreenHeight - obj.tileYSize - 1);
		isColliding = true;
	}
	return isColliding;
}
