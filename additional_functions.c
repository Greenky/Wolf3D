/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 18:29:02 by vmazurok          #+#    #+#             */
/*   Updated: 2019/01/23 17:11:50 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		side_movement(t_graphix *gfx, SDL_Scancode key, double move)
{
	if (key == SDL_SCANCODE_D || key == SDL_SCANCODE_RIGHT)
		move = fabs(move);
	else
		move = fabs(move) * (-1);
	if (gfx->map[(int)(gfx->player.pos_x + gfx->player.plane_x * move)]
		[(int)gfx->player.pos_y] == 0)
		gfx->player.pos_x += gfx->player.plane_x * move;
	if (gfx->map[(int)gfx->player.pos_x][(int)(gfx->player.pos_y +
		gfx->player.plane_y * move)] == 0)
		gfx->player.pos_y += gfx->player.plane_y * move;
}

void		ray_steping(t_step_data *step_dist, t_vector *hit_p,
t_vector v_dir)
{
	if (step_dist->dist_x < step_dist->dist_y)
	{
		step_dist->dist_x += fabs(1 / v_dir.x);
		hit_p->x += step_dist->step_x;
		hit_p->side = (step_dist->step_x > 0) ? 0 : 2;
	}
	else
	{
		step_dist->dist_y += fabs(1 / v_dir.y);
		hit_p->y += step_dist->step_y;
		hit_p->side = (step_dist->step_y > 0) ? 1 : 3;
	}
}

double		side_distance_counter(t_vector v_dir, t_graphix *gfx,
t_vector *hit_p)
{
	t_step_data	data;

	data.dist_x = 0;
	data.dist_y = 0;
	if (v_dir.x < 0 && (data.step_x = -1))
		data.dist_x = (gfx->player.pos_x - hit_p->x) * fabs(1 / v_dir.x);
	else if ((data.step_x = 1))
		data.dist_x = (hit_p->x + 1.0 - gfx->player.pos_x) * fabs(1 / v_dir.x);
	if (v_dir.y < 0 && (data.step_y = -1))
		data.dist_y = (gfx->player.pos_y - hit_p->y) * fabs(1 / v_dir.y);
	else if ((data.step_y = 1))
		data.dist_y = (hit_p->y + 1.0 - gfx->player.pos_y) * fabs(1 / v_dir.y);
	while (1)
	{
		ray_steping(&data, hit_p, v_dir);
		if (gfx->map[(int)hit_p->x][(int)hit_p->y] > 0)
			break ;
	}
	if (hit_p->side % 2 == 0)
		return ((hit_p->x - gfx->player.pos_x +
		(1 - data.step_x) / 2) / v_dir.x);
	else
		return ((hit_p->y - gfx->player.pos_y +
		(1 - data.step_y) / 2) / v_dir.y);
}

SDL_Surface	*load_texture(const char *path)
{
	SDL_Surface *texture;
	SDL_Surface	*new_text;

	if (!(texture = SDL_LoadBMP(path)))
	{
		ft_putstr_fd("ERROR LOADING BMP FILE\n", 2);
		exit(1);
	}
	new_text = SDL_ConvertSurfaceFormat(texture, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(texture);
	return (new_text);
}

int			chose_wall_color(t_graphix *gfx, t_hit_data h_data)
{
	int color;

	if (gfx->map[(int)h_data.hit_point.x][(int)h_data.hit_point.y] == 1)
		color = 0xFF0000;
	else if (gfx->map[(int)h_data.hit_point.x][(int)h_data.hit_point.y] == 2)
		color = 0x00FF00;
	else if (gfx->map[(int)h_data.hit_point.x][(int)h_data.hit_point.y] == 3)
		color = 0x0000FF;
	else if (gfx->map[(int)h_data.hit_point.x][(int)h_data.hit_point.y] == 4)
		color = 0x00FFFF;
	else if (gfx->map[(int)h_data.hit_point.x][(int)h_data.hit_point.y] == 5)
		color = 0xFF00FF;
	else if (gfx->map[(int)h_data.hit_point.x][(int)h_data.hit_point.y] == 6)
		color = 0xFFFF00;
	else
		color = 0xFFFFFF;
	if (h_data.hit_point.side % 2 == 1)
		color = color / 2;
	return (color);
}
