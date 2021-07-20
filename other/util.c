/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:21:01 by flurk             #+#    #+#             */
/*   Updated: 2021/03/11 14:21:03 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	step(t_vars *vars, t_frame *frame)
{
	if (frame->ray_dirx < 0)
	{
		frame->stepx = -1;
		frame->side_distx = (vars->set.posx - frame->mapx) * frame->delta_distx;
	}
	else
	{
		frame->stepx = 1;
		frame->side_distx = (frame->mapx + 1.0 - vars->set.posx) *
			frame->delta_distx;
	}
	if (frame->ray_diry < 0)
	{
		frame->stepy = -1;
		frame->side_disty = (vars->set.posy - frame->mapy) * frame->delta_disty;
	}
	else
	{
		frame->stepy = 1;
		frame->side_disty = (frame->mapy + 1.0 - vars->set.posy) *
			frame->delta_disty;
	}
}

void	dda(t_vars *vars, t_frame *frame)
{
	while (frame->hit == 0)
	{
		if (frame->side_distx < frame->side_disty)
		{
			frame->side_distx += frame->delta_distx;
			frame->mapx += frame->stepx;
			frame->side = 0;
		}
		else
		{
			frame->side_disty += frame->delta_disty;
			frame->mapy += frame->stepy;
			frame->side = 1;
		}
		if (vars->map[frame->mapx][frame->mapy] == '1')
			frame->hit = 1;
	}
}

double	ft_abs(double num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

int		has_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
