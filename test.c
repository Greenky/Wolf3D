/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   govnotest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <vmazurok@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 18:29:02 by vmazurok          #+#    #+#             */
/*   Updated: 2018/08/19 18:29:03 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdib.h>

typedef struct	s_grafix
{
	void		*mlx;
	void		*win;
	void		*img;
	int			scr_size;
	t_player	player;
}				t_grafix;


typedef struct	s_vector
{
	int x;
	int y;
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
	int			dist;
}				t_player;

void		pixel_add(t_grafix *gfx, int x, int y, unsigned int color)
{
	int bpp;
	int size_l;
	int end;
	int *buff;

	if (x >= 0 && x < gfx->scr_size && y >= 0 && y < gfx->scr_size)
	{
		buff = (int *)mlx_get_data_addr(gfx->img, &bpp, &size_l, &end);
		buff[(int)(gfx->scr_size) * y + x] = color;
	}
}

int			key_press(int key, t_grafix *gfx);
{

}

void		ray_cast(ray, gfx)
{
	// IN PROGRES
}

void		draw_world(t_grafix *gfx)
{
	float i;
	float angle;
	t_ray ray;

	i = -500;
	ray.origin = gfx->player.position;
	while (i < 500)
	{
		angle = 30 * (i / 500f);
		ray.direction.x = player.view.x * cos(angle * M_PI / 180f) - player.view.y * sin(angle * M_PI / 180f);
		ray.direction.y = player.view.x * sin(angle * M_PI / 180f) + player.view.y * cos(angle * M_PI / 180f);
		ray_cast(ray, gfx);
		i++;
	}
}

int			main()
{
	t_grafix gfx;
	gfx.mlx = mlx_init();
	gfx.win = mlx_new_window(gfx.mlx, 1000, 1000, "Wol");
	gfx.img = mlx_new_image(gfx.mlx, 1000, 1000);
	gfx.scr_size = 1000;

	gfx.player.position.x = 40;
	gfx.player.position.y = 40;
	gfx.player.view.x = 0;
	gfx.player.view.y = -1;

	char map[10][10] =
	{
		{"W        W"},
		{"W        W"},
		{"W        W"},
		{"W        W"},
		{"W        W"},
		{"W        W"},
		{"W        W"},
		{"W        W"},
		{"W        W"},
		{"WWWWWWWWWW"},
	};
	draw_world(&gfx);
	mlx_key_hook(gfx.win, key_press, &gfx);
	mlx_loop(gfx.mlx);
	return 0;
}