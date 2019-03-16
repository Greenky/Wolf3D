/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wlof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 18:29:02 by vmazurok          #+#    #+#             */
/*   Updated: 2019/01/23 16:09:48 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static int	wall_drawer(t_graphix *gfx, t_hit_data h_data, int x, int text_x)
{
	int		height;
	int		start;
	int		end;
	int		color;
	double	text_y;

	height = (int)(gfx->surface->h / h_data.wall_dist);
	start = -height / 2 + gfx->surface->h / 2;
	if (start < 0)
		start = 0;
	end = height / 2 + gfx->surface->h / 2;
	if (end >= gfx->surface->h)
		end = gfx->surface->h - 1;
	while (start++ < end)
	{
		text_y = (((start * 256 - gfx->surface->h * 128 + height * 128)
		* 63.0) / (double)height) / 256;
		if (gfx->mode == 1)
			color = ((int*)gfx->textures[h_data.hit_point.side]->pixels)[64 *
			(int)text_y + text_x];
		else
			color = chose_wall_color(gfx, h_data);
		((int*)gfx->surface->pixels)[start * gfx->surface->w + x] = color;
	}
	return (end);
}

static void	floor_texturing(t_graphix *gfx, t_hit_data h_data,
t_vector wall_hit, int x)
{
	double		dist;
	double		curr_dist;
	double		coef;
	t_vector	curr_coord;
	int			y;

	dist = 0;
	y = h_data.bottom;
	if (h_data.bottom < 0)
		h_data.bottom = gfx->surface->h;
	while (++y < gfx->surface->h)
	{
		curr_dist = gfx->surface->h / (2.0 * y - gfx->surface->h);
		coef = (curr_dist - dist) / (h_data.wall_dist - dist);
		curr_coord.x = coef * wall_hit.x + (1.0 - coef) * gfx->player.pos_x;
		curr_coord.y = coef * wall_hit.y + (1.0 - coef) * gfx->player.pos_y;
		((int*)gfx->surface->pixels)[y * gfx->surface->w + x] =
		(((int *)gfx->textures[4]->pixels)[64 * ((int)(curr_coord.y * 64) %
		64) + ((int)(curr_coord.x * 64) % 64)] >> 1) & 8355711;
		((int*)gfx->surface->pixels)[(gfx->surface->h - y) * gfx->surface->w +
		x] = ((int *)gfx->textures[5]->pixels)[64 * ((int)(curr_coord.y * 64)
		% 64) + ((int)(curr_coord.x * 64) % 64)];
	}
}

static void	floor_drawer(t_graphix *gfx, t_hit_data h_data, int x)
{
	t_vector	wall_hit;

	if (h_data.hit_point.side % 2 == 0 && h_data.view_dir.x > 0)
	{
		wall_hit.x = h_data.hit_point.x;
		wall_hit.y = h_data.hit_point.y + h_data.wall_x;
	}
	else if (h_data.hit_point.side % 2 == 0 && h_data.view_dir.x < 0)
	{
		wall_hit.x = h_data.hit_point.x + 1.0;
		wall_hit.y = h_data.hit_point.y + h_data.wall_x;
	}
	else if (h_data.hit_point.side % 2 == 1 && h_data.view_dir.y > 0)
	{
		wall_hit.x = h_data.hit_point.x + h_data.wall_x;
		wall_hit.y = h_data.hit_point.y;
	}
	else
	{
		wall_hit.x = h_data.hit_point.x + h_data.wall_x;
		wall_hit.y = h_data.hit_point.y + 1.0;
	}
	floor_texturing(gfx, h_data, wall_hit, x);
}

static int	hit_point_finder(t_graphix *gfx, int x, t_hit_data *h_data)
{
	int texture_x;

	h_data->hit_point.x = (int)gfx->player.pos_x;
	h_data->hit_point.y = (int)gfx->player.pos_y;
	h_data->view_dir.x = gfx->player.dir_x + gfx->player.plane_x * (2 * x /
	(double)(gfx->surface->w) - 1);
	h_data->view_dir.y = gfx->player.dir_y + gfx->player.plane_y * (2 * x /
	(double)(gfx->surface->w) - 1);
	h_data->wall_dist = side_distance_counter(h_data->view_dir, gfx,
	&(h_data->hit_point));
	if (h_data->hit_point.side % 2 == 0)
		h_data->wall_x = gfx->player.pos_y + h_data->wall_dist *
		h_data->view_dir.y;
	else
		h_data->wall_x = gfx->player.pos_x + h_data->wall_dist *
		h_data->view_dir.x;
	h_data->wall_x -= (int)h_data->wall_x;
	texture_x = (int)(h_data->wall_x * 64.0);
	if (h_data->hit_point.side % 2 == 0 && h_data->view_dir.x > 0)
		texture_x = 64 - texture_x - 1;
	if (h_data->hit_point.side % 2 == 1 && h_data->view_dir.y < 0)
		texture_x = 64 - texture_x - 1;
	return (texture_x);
}

void		draw_world(t_graphix *gfx)
{
	t_hit_data	h_data;
	int			x;
	int			texture_x;

	x = 0;
	while (x < gfx->surface->w)
	{
		texture_x = hit_point_finder(gfx, x, &h_data);
		h_data.bottom = wall_drawer(gfx, h_data, x, texture_x);
		if (gfx->mode == 1)
			floor_drawer(gfx, h_data, x);
		x++;
	}
	SDL_UpdateWindowSurface(gfx->window);
	bzero(gfx->surface->pixels, gfx->surface->w * gfx->surface->h * 4);
}
