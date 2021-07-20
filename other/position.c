/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:13:35 by flurk             #+#    #+#             */
/*   Updated: 2021/03/15 17:13:37 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_x(t_vars *vars, int i, int j)
{
	if (vars->map[i][j] == 'N')
	{
		vars->set.dirx = -1;
		vars->set.diry = 0;
		vars->set.planey = 0.66;
		vars->set.planex = 0;
	}
	else if (vars->map[i][j] == 'S')
	{
		vars->set.dirx = 1;
		vars->set.diry = 0;
		vars->set.planey = -0.66;
		vars->set.planex = 0;
	}
}

void	get_y(t_vars *vars, int i, int j)
{
	if (vars->map[i][j] == 'E')
	{
		vars->set.diry = 1;
		vars->set.dirx = 0;
		vars->set.planey = 0;
		vars->set.planex = 0.66;
	}
	else if (vars->map[i][j] == 'W')
	{
		vars->set.diry = -1;
		vars->set.dirx = 0;
		vars->set.planey = 0;
		vars->set.planex = -0.66;
	}
}

void	set_pos(t_vars *vars, int i, int j)
{
	if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S')
		get_x(vars, i, j);
	else
		get_y(vars, i, j);
}

void	get_pos(t_vars *vars)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < vars->count_map)
	{
		j = 0;
		while (j < ft_strlen(vars->map[i]))
		{
			if (!has_char(vars->map[i][j], " 012NSEW"))
				get_error("non valid map");
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S' ||
				vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
			{
				vars->pos == 0 ? vars->pos = 1 : get_error("non valid map");
				vars->set.posx = i + 0.5;
				vars->set.posy = j + 0.5;
				set_pos(vars, i, j);
			}
			j++;
		}
		i++;
	}
	if (vars->pos == 0)
		get_error("non valid map");
}

int		ft_close(void)
{
	exit(0);
}
