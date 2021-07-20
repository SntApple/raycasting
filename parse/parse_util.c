/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:30:20 by flurk             #+#    #+#             */
/*   Updated: 2021/03/18 14:36:10 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		is_num(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] < '0' || s[i++] > '9')
				return (0);
		}
	}
	return (1);
}

void	get_screen_size(t_set *set)
{
	int	height;
	int	width;

	mlx_get_screen_size(&width, &height);
	if (width < set->screen_width)
		set->screen_width = width;
	if (height < set->screen_height)
		set->screen_height = height;
}
