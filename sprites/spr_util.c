/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spr_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:20:39 by flurk             #+#    #+#             */
/*   Updated: 2021/03/17 17:20:40 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	spr_distance(t_vars *vars)
{
	double	distance;
	int		i;

	i = 0;
	while (i < vars->count_spr)
	{
		distance = pow(vars->sprites[i][0] - vars->set.posx, 2) +
		pow(vars->sprites[i][1] - vars->set.posy, 2);
		vars->sprites[i][2] = distance;
		i++;
	}
}

void	swap_p(double **s1, double **s2)
{
	double	*p;

	p = *s1;
	*s1 = *s2;
	*s2 = p;
}

void	sort_spr(double **sprites, int count)
{
	int	i;
	int	j;

	j = count - 1;
	while (j > 0)
	{
		i = 0;
		while (i < j)
		{
			if (sprites[i][2] < sprites[i + 1][2])
				swap_p(&sprites[i], &sprites[i + 1]);
			i++;
		}
		j--;
	}
}

void	free_spr(int k, double **sprites)
{
	int	i;

	i = 0;
	while (i < k)
		free(sprites[i++]);
	free(sprites);
}

void	get_addr(t_vars *vars)
{
	vars->tex.no.addr = mlx_get_data_addr(vars->tex.no.img,
		&vars->tex.no.bits_per_pixel, &vars->tex.no.line_length,
			&vars->tex.no.endian);
	vars->tex.so.addr = mlx_get_data_addr(vars->tex.so.img,
		&vars->tex.so.bits_per_pixel, &vars->tex.so.line_length,
			&vars->tex.so.endian);
	vars->tex.we.addr = mlx_get_data_addr(vars->tex.we.img,
		&vars->tex.we.bits_per_pixel, &vars->tex.we.line_length,
			&vars->tex.we.endian);
	vars->tex.ea.addr = mlx_get_data_addr(vars->tex.ea.img,
		&vars->tex.ea.bits_per_pixel, &vars->tex.ea.line_length,
			&vars->tex.ea.endian);
	vars->tex.sp.addr = mlx_get_data_addr(vars->tex.sp.img,
		&vars->tex.sp.bits_per_pixel, &vars->tex.sp.line_length,
			&vars->tex.sp.endian);
}
