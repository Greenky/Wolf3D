/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 20:01:45 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/01 20:04:04 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strequ(char const *s1, char const *s2)
{
	int i;

	i = 0;
	if (!(s1) || !(s2))
		return (0);
	if (s1[0] == 0 && s2[0] == 0)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		else if (s1[i + 1] == 0 && s2[i + 1] == 0)
			return (1);
		i++;
	}
	return (0);
}
