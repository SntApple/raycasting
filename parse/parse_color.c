/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:32:54 by flurk             #+#    #+#             */
/*   Updated: 2021/03/15 14:32:55 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		get_f(char **ar, t_vars *vars)
{
	char	**f;
	int		r;
	int		g;
	int		b;

	if (ar[1] && !ar[2])
	{
		f = ft_split(ar[1], ',');
		if (!f)
			get_error("cant get memory");
		if (f[0] && f[1] && f[2] && is_num(f[0]) && is_num(f[1]) &&
			is_num(f[2]) && !f[3])
		{
			r = ft_atoi(f[0]);
			g = ft_atoi(f[1]);
			b = ft_atoi(f[2]);
			if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
				get_error("non valid color");
			vars->tex.floor = create_trgb(0, r, g, b);
			free_ar(f);
			return (1);
		}
	}
	return (0);
}

int		get_c(char **ar, t_vars *vars)
{
	char	**c;
	int		r;
	int		g;
	int		b;

	if (ar[1] && !ar[2])
	{
		c = ft_split(ar[1], ',');
		if (!c)
			get_error("cant get memory");
		if (c[0] && c[1] && c[2] && is_num(c[0]) && is_num(c[1]) &&
			is_num(c[2]) && !c[3])
		{
			r = ft_atoi(c[0]);
			g = ft_atoi(c[1]);
			b = ft_atoi(c[2]);
			if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
				get_error("non valid color");
			vars->tex.ceiling = create_trgb(0, r, g, b);
			free_ar(c);
			return (1);
		}
	}
	return (0);
}

int		check_commas(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] == ',')
				count++;
			i++;
		}
	}
	if (count != 2)
		return (0);
	return (1);
}

int		get_col(char **ar, t_vars *vars, int *ans)
{
	if (!ft_strncmp(ar[0], "F", 2))
	{
		if (check_commas(ar[1]) && get_f(ar, vars))
		{
			*ans *= 17;
		}
	}
	else if (!ft_strncmp(ar[0], "C", 2))
	{
		if (check_commas(ar[1]) && get_c(ar, vars))
		{
			*ans *= 19;
		}
	}
	else
		return (0);
	return (1);
}
