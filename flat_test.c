/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 18:29:02 by vmazurok          #+#    #+#             */
/*   Updated: 2018/09/09 18:10:43 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frameworks/SDL2.framework/Headers/SDL.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define VECTOR(a1, a2) (t_vector){a1, a2}

int map[10][10] =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

typedef struct	s_vector
{
	float x;
	float y;
}				t_vector;

typedef struct	s_ray
{
	t_vector origin;
	t_vector direction;
}				t_ray;

typedef struct	s_player
{
	t_vector	position;
	t_vector	view;
	float		view_angle;
}				t_player;

typedef struct	s_grafix
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	int				scr_size;
	t_player		player;
}				t_grafix;

void		set_pixel(SDL_Surface *surface, int x, int y, int color)
{
	if (x < surface->w && y < surface->h && x > 0 && y > 0)
	((int*)surface->pixels)[y * surface->w + x] = color;
}

float		distance(t_vector first, t_vector second)
{
	float a;
	float b;

	if (first.x != first.x || first.y != first.y ||
		second.x != second.x || second.y != second.y)
		return (INFINITY);
	a = first.x - second.x;
	b = first.y - second.y;
	return (sqrtf(a * a + b * b));
}

float		ray_cast(float angle, t_grafix *gfx)
{
    t_vector intersect_point;

    if (angle == M_PI_2 || angle == 3 * M_PI_2)
    {
        if (angle > 0 && angle < 180)
            intersect_point.y = (int)(gfx->player.position.y / 64) * 64 - 1;
        else
            intersect_point.y = (int)(gfx->player.position.y / 64) * 64 + 64;
    }


//	float bound_x = (ray.direction.x > 0) ? (int)ray.origin.x + 1 : (int)ray.origin.x;
//	float bound_y = (ray.direction.y > 0) ? (int)ray.origin.y + 1 : (int)ray.origin.y;
//
//	int step_x = (ray.direction.x > 0) ? 1 : -1;
//	int step_y = (ray.direction.y > 0) ? 1 : -1;
//
//	float next_x = (ray.direction.x / ray.direction.y) * (bound_y - ray.origin.y) + ray.origin.x;
//	float next_y = (ray.direction.y / ray.direction.x) * (bound_x - ray.origin.x) + ray.origin.y;
//
//	while ((bound_x < 10 && bound_x > -1) && (bound_y < 10 && bound_y > -1))
//	{
//		if (distance(VECTOR(next_x, bound_y), ray.origin) < distance(VECTOR(next_y, bound_x), ray.origin))
//		{
//			if (map[(int)next_x][(int)bound_y] != 0)
//				return (distance(VECTOR(next_x, bound_y), ray.origin));
//			bound_y += step_y;
//		}
//		else
//		{
//			if (map[(int)bound_x][(int)next_y] != 0)
//				return (distance(VECTOR(next_x, bound_y), ray.origin));
//			bound_x += step_x;
//		}
//	}
//	return (INFINITY);
}

void		draw_wall(int i, float distance, t_grafix *gfx)
{
	float wall_height;
	int j;

	if (distance == INFINITY)
	{
		j = -1;
		while (++j < 1000)
			set_pixel(gfx->surface, i, j, 0);
	}
	else
	{
		wall_height = 100.0f / distance;
		j = (int)(1000 - wall_height) / 2;
		while (j < ((1000 - wall_height) / 2) + wall_height)
		{
			set_pixel(gfx->surface, i, j, 0xFFFF);
			j++;
		}
	}
	
}

void		draw_world(t_grafix *gfx)
{
	float angle;
	float distance;


    bzero(gfx->surface->pixels, 1000 * 1000 * sizeof(int));
    while (gfx->player.view_angle < 0)
        gfx->player.view_angle += 360;
    while (gfx->player.view_angle > 360)
        gfx->player.view_angle -= 360;

    angle = gfx->player.view_angle;
    while (angle < gfx->player.view_angle + 60)
    {
        ray_cast(angle * M_PI / 180.0f, gfx);
        angle = angle + (60.0f / 1000.0f);
    }

//    float i;
//    t_ray ray;
//	i = -500;
//	ray.origin = gfx->player.position;

//	while (i < 500)
//	{
//		angle = 30 * (i / 500.0f);
//		ray.direction.x = gfx->player.view.x * cosf(angle * M_PI / 180.0f) -
//		gfx->player.view.y * sinf(angle * M_PI / 180.0f);
//		ray.direction.y = gfx->player.view.x * sinf(angle * M_PI / 180.0f) +
//		gfx->player.view.y * cosf(angle * M_PI / 180.0f);
//		distance = ray_cast(ray, gfx);
//		draw_wall(i + 500, distance, gfx);
//		i++;
//	}
	SDL_UpdateWindowSurface(gfx->window);
}

void		event_management(t_grafix *gfx, SDL_Event *event)
{
	int			running;
    t_vector    view;

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
				return ;
			}
			else if (event->type == SDL_KEYDOWN && event->key.keysym.scancode == SDL_SCANCODE_UP
			&& gfx->player.position.y > 1)
				gfx->player.position.y -= 0.1;
			else if (event->type == SDL_KEYDOWN && event->key.keysym.scancode == SDL_SCANCODE_DOWN
			&& gfx->player.position.y < 9)
				gfx->player.position.y += 0.1;
			else if (event->type == SDL_KEYDOWN && event->key.keysym.scancode == SDL_SCANCODE_LEFT)
                gfx->player.view_angle++;
			else if (event->type == SDL_KEYDOWN && event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
                gfx->player.view_angle--;
			draw_world(gfx);
		}
	}
}

int			main()
{
	t_grafix	gfx;
	SDL_Event	event;

	SDL_Init(SDL_INIT_EVERYTHING);
	gfx.window = SDL_CreateWindow("Wolf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
								1000, 1000, SDL_WINDOW_ALLOW_HIGHDPI);
	gfx.surface = SDL_GetWindowSurface(gfx.window);
	gfx.scr_size = 1000;

	gfx.player.position.x = 4;
	gfx.player.position.y = 4;
	gfx.player.view.x = 0;
	gfx.player.view.y = -1;

	
	draw_world(&gfx);
	event_management(&gfx, &event);
	return 0;
}