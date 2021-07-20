/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:07:58 by flurk             #+#    #+#             */
/*   Updated: 2021/03/15 17:08:00 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		check_nb(char **map, int i, size_t j)
{
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' ' ||
		map[i][j + 1] == ' ')
		return (0);
	return (1);
}

int		check_after_min(int i, size_t j, char **map)
{
	while (j < ft_strlen(map[i]))
	{
		if (map[i][j] == '0' || has_char(map[i][j], "NSWE2"))
			return (0);
		j++;
	}
	return (1);
}

int		check_inside(t_vars *vars, char **map)
{
	int		i;
	size_t	j;
	size_t	min;

	i = 1;
	while (i < vars->count_map - 1)
	{
		j = 1;
		min = ft_strlen(map[i]);
		min = min < ft_strlen(map[i - 1]) ? min : ft_strlen(map[i - 1]);
		min = min < ft_strlen(map[i + 1]) ? min : ft_strlen(map[i + 1]);
		while (j < min)
		{
			if (map[i][j] == '0' || has_char(map[i][j], "NSWE2"))
				if (!check_nb(map, i, j))
					return (0);
			j++;
		}
		if (!check_after_min(i, j, map))
			return (0);
		i++;
	}
	return (1);
}

void	check_last(t_vars *vars, char **map)
{
	size_t	j;
	int		i;

	j = 0;
	i = vars->count_map - 1;
	while (j < ft_strlen(map[i]))
	{
		if (map[i][j] != ' ' && map[i][j] != '1')
			get_error("non valid map");
		j++;
	}
}

int		is_valid(t_vars *vars, char **map)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < vars->count_map)
	{
		if ((map[i][0] != ' ' && map[i][0] != '1') || ((map[i][ft_strlen(map[i])
			- 1] != ' ') && map[i][ft_strlen(map[i]) - 1] != '1'))
			get_error("non valid map");
		i++;
	}
	while (j < ft_strlen(vars->map[0]))
	{
		if (map[0][j] != ' ' && map[0][j] != '1')
			get_error("non valid map");
		j++;
	}
	check_last(vars, vars->map);
	if (check_inside(vars, map))
		return (1);
	return (0);
}
