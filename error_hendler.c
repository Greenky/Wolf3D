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

void		error_hendler(char **line, int error_num)
{
	if (error_num == 0)
		ft_putstr_fd("Content error, file must include only numbers\n", 2);
	else if (error_num == 1)
		ft_putstr_fd("Invalid map or player parameters\n", 2);
	else if (error_num == 2)
		ft_putstr_fd("Specified map is too small\n", 2);
	else if (error_num == 3)
		ft_putstr_fd("Specified map is too large\n", 2);
	else if (error_num == 4)
		ft_putstr_fd("Specified map borders are not closed\n", 2);
	else if (error_num == 5)
		ft_putstr_fd("Player position is in texture\n", 2);
	else
		ft_putstr_fd("Unknown error\n", 2);
	if (line)
		free(*line);
	exit(1);
}
