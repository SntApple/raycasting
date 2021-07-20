/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:14:23 by flurk             #+#    #+#             */
/*   Updated: 2021/03/15 17:14:24 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_param(t_vars *vars)
{
	vars->count_spr = 0;
	vars->set.z = ft_calloc(vars->set.screen_width, sizeof(double));
	if (!vars->set.z)
		get_error("cant get memory");
}

void	init_key(t_vars *vars)
{
	vars->key.bc_w = 0;
	vars->key.fw_w = 0;
	vars->key.bc = 0;
	vars->key.fw = 0;
	vars->key.l = 0;
	vars->key.r = 0;
	vars->key.sl = 0;
	vars->key.sr = 0;
}

void	init_frame(t_vars *vars, t_frame *frame, int x)
{
	frame->camerax = 2 * x / (double)vars->set.screen_width - 1;
	frame->ray_dirx = vars->set.dirx + vars->set.planex * frame->camerax;
	frame->ray_diry = vars->set.diry + vars->set.planey * frame->camerax;
	frame->mapx = (int)vars->set.posx;
	frame->mapy = (int)vars->set.posy;
	frame->hit = 0;
	frame->delta_distx = ft_abs(1 / frame->ray_dirx);
	frame->delta_disty = ft_abs(1 / frame->ray_diry);
}

void	fill_spr(t_vars *vars)
{
	int	k;

	k = 0;
	while (k < vars->count_spr)
	{
		if ((vars->sprites[k] = malloc(sizeof(double) * 3)) == NULL)
		{
			free_spr(k, vars->sprites);
			get_error("cant get memory");
		}
		k++;
	}
}

void	init_sprites(t_vars *vars)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < vars->count_map)
	{
		j = 0;
		while (j < ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] == '2')
			{
				vars->count_spr++;
			}
			j++;
		}
		i++;
	}
	vars->sprites = malloc(sizeof(double*) * vars->count_spr);
	if (!vars->sprites)
		get_error("cant get memory");
	fill_spr(vars);
}
