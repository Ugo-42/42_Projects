/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/29 13:41:24 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"


#if EXTRA

#include <SDL2/SDL.h>

void visualizeTriangle(Point const &a, Point const &b, Point const &c, Point const &p)
{
	const int W=800;
	const int M=W/10;
	const int MX=16;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win=SDL_CreateWindow("Debug",100,100,W,W,0);
	SDL_Renderer* r=SDL_CreateRenderer(win,-1,0);

	SDL_SetRenderDrawColor(r,0,0,0,255);
	SDL_RenderClear(r);

	// Scale coordinates
	int ax = M + a.getX().toInt() * (W - 2*M) / MX;
	int ay = W - M - a.getY().toInt() * (W - 2*M) / MX;
	int bx = M + b.getX().toInt() * (W - 2*M) / MX;
	int by = W - M - b.getY().toInt() * (W - 2*M) / MX;
	int cx = M + c.getX().toInt() * (W - 2*M) / MX;
	int cy = W - M - c.getY().toInt() * (W - 2*M) / MX;
	int px = M + p.getX().toInt() * (W - 2*M) / MX;
	int py = W - M - p.getY().toInt() * (W - 2*M) / MX;

	// Draw triangle (green)
	SDL_SetRenderDrawColor(r,0,255,0,255);
	SDL_RenderDrawLine(r,ax,ay,bx,by);
	SDL_RenderDrawLine(r,bx,by,cx,cy);
	SDL_RenderDrawLine(r,cx,cy,ax,ay);

	// Draw point (red)
	SDL_SetRenderDrawColor(r,255,0,0,255);
	SDL_Rect rect={px-3,py-3,6,6};
	SDL_RenderFillRect(r,&rect);

	SDL_RenderPresent(r);

	// Wait until window closed
	SDL_Event e;
	int quit = 0;
	while(!quit){
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT) quit = 1;
		}
		SDL_Delay(16);
	}

	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

#endif


static Fixed area(Point const &p1, Point const &p2, Point const &p3)
{
	Fixed result = (p1.getX() * (p2.getY() - p3.getY())
				  + p2.getX() * (p3.getY() - p1.getY())
				  + p3.getX() * (p1.getY() - p2.getY()));

	return result < 0 ? result * -1 : result;
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed areaABC = area(a, b, c);
	Fixed areaPAB = area(point, a, b);
	Fixed areaPBC = area(point, b, c);
	Fixed areaPCA = area(point, c, a);

	bool inside = (areaABC == (areaPAB + areaPBC + areaPCA));

	if (areaPAB == 0 || areaPBC == 0 || areaPCA == 0)
		return false;

	return inside;
}

int main( void )
{
	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		Point a(2, 2);
		Point b(16, 3);
		Point c(3, 9);

		Point p1(3, 3);
		Point p2(16, 4);
		Point p3(5, 0);

#if EXTRA
		visualizeTriangle(a, b, c, p1);
		visualizeTriangle(a, b, c, p2);
		visualizeTriangle(a, b, c, p3);
#endif

		ECHO("P1: " << (bsp(a, b, c, p1) ? "true" : "false"));
		ECHO("P2: " << (bsp(a, b, c, p2) ? "true" : "false"));
		ECHO("P3: " << (bsp(a, b, c, p3) ? "true" : "false"));
	}

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}
