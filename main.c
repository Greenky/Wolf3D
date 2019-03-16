/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wlof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 18:29:02 by vmazurok          #+#    #+#             */
/*   Updated: 2019/01/23 17:14:21 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		key_press_hendler(t_graphix *gfx, SDL_Scancode key)
{
	static double move = 0.15;

	if (key == SDL_SCANCODE_LSHIFT)
		move = (move == 0.15) ? 0.3 : 0.15;
	if (key == SDL_SCANCODE_SPACE)
		gfx->mode = (gfx->mode == 0) ? 1 : 0;
	if (key == SDL_SCANCODE_W || key == SDL_SCANCODE_UP || key == SDL_SCANCODE_S
	|| key == SDL_SCANCODE_DOWN)
	{
		if (key == SDL_SCANCODE_W || key == SDL_SCANCODE_UP)
			move = fabs(move);
		else
			move = fabs(move) * (-1);
		if (gfx->map[(int)(gfx->player.pos_x + gfx->player.dir_x * move)]
		[(int)gfx->player.pos_y] == 0)
			gfx->player.pos_x += gfx->player.dir_x * move;
		if (gfx->map[(int)gfx->player.pos_x][(int)(gfx->player.pos_y +
		gfx->player.dir_y * move)] == 0)
			gfx->player.pos_y += gfx->player.dir_y * move;
	}
	else if (key == SDL_SCANCODE_D || key == SDL_SCANCODE_RIGHT
	|| key == SDL_SCANCODE_A || key == SDL_SCANCODE_LEFT)
		side_movement(gfx, key, move);
}

void		movement_handling(t_graphix *gfx, SDL_Event *event, double old)
{
	if (event->type == SDL_KEYDOWN && event->key.keysym.scancode ==
	SDL_SCANCODE_KP_PLUS)
		gfx->rot += (gfx->rot < 0.5) ? 0.01 : 0;
	else if (event->type == SDL_KEYDOWN && event->key.keysym.scancode ==
	SDL_SCANCODE_KP_MINUS)
		gfx->rot -= (gfx->rot > 0.01) ? 0.01 : 0;
	if (event->type == SDL_KEYDOWN)
		key_press_hendler(gfx, event->key.keysym.scancode);
	if (event->type == SDL_MOUSEMOTION)
	{
		gfx->rot = (event->motion.xrel > 0) ? fabs(gfx->rot) * (-1) :
		fabs(gfx->rot);
		old = gfx->player.dir_x;
		gfx->player.dir_x = gfx->player.dir_x * cos(gfx->rot) -
		gfx->player.dir_y * sin(gfx->rot);
		gfx->player.dir_y = old * sin(gfx->rot) + gfx->player.dir_y *
		cos(gfx->rot);
		old = gfx->player.plane_x;
		gfx->player.plane_x = gfx->player.plane_x * cos(gfx->rot) -
		gfx->player.plane_y * sin(gfx->rot);
		gfx->player.plane_y = old * sin(gfx->rot) + gfx->player.plane_y *
		cos(gfx->rot);
	}
	draw_world(gfx);
}

void		event_management(t_graphix *gfx, SDL_Event *event)
{
	int		running;

	running = 1;
	while (running)
	{
		while (SDL_PollEvent(event))
		{
			if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN &&
			event->key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				SDL_FreeSurface(gfx->surface);
				SDL_DestroyWindow(gfx->window);
				SDL_Quit();
				running = 0;
				break ;
			}
			else
				movement_handling(gfx, event, 0);
		}
	}
}

void		put_params(t_graphix *gfx)
{
	if (gfx->player.pos_x == 1)
		gfx->player.pos_x += 0.5;
	if (gfx->player.pos_y == 1)
		gfx->player.pos_y += 0.5;
	gfx->player.dir_x = -1;
	gfx->player.dir_y = 0;
	gfx->player.plane_x = 0;
	gfx->player.plane_y = 0.5;
	gfx->mode = 0;
	gfx->rot = 0.04;
	gfx->textures = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 6);
	gfx->textures[0] =
	load_texture("/Users/vmazurok/Wolf3D/textures/redbrick.bmp");
	gfx->textures[1] =
	load_texture("/Users/vmazurok/Wolf3D/textures/eagle.bmp");
	gfx->textures[2] =
	load_texture("/Users/vmazurok/Wolf3D/textures/mossy.bmp");
	gfx->textures[3] =
	load_texture("/Users/vmazurok/Wolf3D/textures/wood.bmp");
	gfx->textures[4] =
	load_texture("/Users/vmazurok/Wolf3D/textures/colorstone.bmp");
	gfx->textures[5] =
	load_texture("/Users/vmazurok/Wolf3D/textures/greystone.bmp");
}

int			main(int argc, char **argv)
{
	t_graphix			gfx;
	SDL_Event			event;

	if (argc != 2)
	{
		write(2, "Specify one parameter\nUsage: ./Wolf3D map_file\n", 47);
		exit(1);
	}
	map_parsing(argv[1], &gfx);
	put_params(&gfx);
	SDL_Init(SDL_INIT_EVERYTHING);
	gfx.window = SDL_CreateWindow("Wolf", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(gfx.window, SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	gfx.surface = SDL_GetWindowSurface(gfx.window);
	draw_world(&gfx);
	event_management(&gfx, &event);
	return (0);
}
