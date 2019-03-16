/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 16:20:31 by vmazurok          #+#    #+#             */
/*   Updated: 2019/01/23 17:11:59 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "frameworks/SDL2.framework/Headers/SDL.h"

typedef struct	s_step_data
{
	double	dist_x;
	double	dist_y;
	int		step_x;
	int		step_y;
}				t_step_data;

typedef struct	s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
}				t_player;

typedef struct	s_vector
{
	double	x;
	double	y;
	int		side;
}				t_vector;

typedef struct	s_hit_data
{
	t_vector	view_dir;
	t_vector	hit_point;
	double		wall_dist;
	double		wall_x;
	int			bottom;
}				t_hit_data;

typedef struct	s_graphix
{
	SDL_Window			*window;
	SDL_Surface			*surface;
	SDL_Surface			**textures;
	int					**map;
	int					mode;
	double				rot;
	double				map_w;
	double				map_h;
	t_player			player;
}				t_graphix;

int				get_next_line(int fd, char **line);
void			map_parsing(char *file_name, t_graphix *gfx);
void			error_hendler(char **line, int error_num);
int				chose_wall_color(t_graphix *gfx, t_hit_data h_data);
SDL_Surface		*load_texture(const char *path);
double			side_distance_counter(t_vector v_dir, t_graphix *gfx,
t_vector *hit_p);
void			ray_steping(t_step_data *step_dist, t_vector *hit_p,
t_vector v_dir);
void			draw_world(t_graphix *gfx);
void			side_movement(t_graphix *gfx, SDL_Scancode key, double move);

#endif
