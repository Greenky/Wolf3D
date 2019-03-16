/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parcing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 18:29:02 by vmazurok          #+#    #+#             */
/*   Updated: 2019/01/23 12:24:18 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static int	to_the_next_number(char *line, int i)
{
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] && line[i] > 32)
		error_hendler(&line, 0);
	while (line[i] && line[i] < 33)
		i++;
	return (i);
}

static void	parce_two_numbers(int fd, double *x, double *y)
{
	int		i;
	char	*line;

	i = 0;
	get_next_line(fd, &line);
	while (line[i] && line[i] < 33)
		i++;
	*x = ft_atoi(line + i);
	i = to_the_next_number(line, i);
	*y = ft_atoi(line + i);
	i = to_the_next_number(line, i);
	if (*x == 0 || *y == 0 || line[i])
		error_hendler(&line, 1);
	free(line);
}

static void	parce_line(int *map_line, char *line, double width)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (j < width)
	{
		while (line[k] && line[k] < 33)
			k++;
		map_line[j] = ft_atoi(line + k);
		while (line[k] && ft_isdigit(line[k]))
			k++;
		if (line[k] && line[k] > 32)
			error_hendler(&line, 0);
		j++;
		if (!line[k] && j != width)
			error_hendler(&line, 2);
		while (j == width && line[k] && line[k] < 33)
			k++;
		if (j == width && line[k])
			error_hendler(&line, 3);
	}
}

static void	evaluate_map(t_graphix *gfx)
{
	int j;
	int i;

	i = -1;
	while (++i < gfx->map_h)
	{
		j = -1;
		while (++j < gfx->map_w)
			if ((i == 0 || i == gfx->map_h - 1 || j == 0 || j == gfx->map_w -
			1) && gfx->map[i][j] == 0)
				error_hendler(NULL, 4);
	}
	if (gfx->map[(int)gfx->player.pos_x][(int)gfx->player.pos_y] != 0)
		error_hendler(NULL, 5);
}

void		map_parsing(char *file_name, t_graphix *gfx)
{
	int			fd;
	char		*line;
	int			i;

	if (((fd = open(file_name, O_RDONLY)) == -1) || (read(fd, NULL, 0) == -1))
	{
		perror("Error");
		exit(1);
	}
	parce_two_numbers(fd, &(gfx->map_w), &(gfx->map_h));
	parce_two_numbers(fd, &(gfx->player.pos_x), &(gfx->player.pos_y));
	gfx->map = (int **)malloc(sizeof(int*) * (int)gfx->map_h);
	i = -1;
	while (++i < gfx->map_h)
	{
		if (get_next_line(fd, &line) == 0)
			error_hendler(&line, 2);
		gfx->map[i] = (int *)malloc(sizeof(int) * (int)gfx->map_w);
		parce_line(gfx->map[i], line, gfx->map_w);
		free(line);
	}
	if (get_next_line(fd, &line) != 0)
		error_hendler(&line, 3);
	evaluate_map(gfx);
}
