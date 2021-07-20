/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:10:41 by flurk             #+#    #+#             */
/*   Updated: 2021/03/11 15:10:42 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			floor_and_ceiling(t_vars *vars, int x)
{
	int y;

	y = 0;
	while (y < vars->set.screen_height / 2)
	{
		my_mlx_pixel_put(&vars->data, x, y, vars->tex.ceiling);
		y++;
	}
	while (y < vars->set.screen_height)
	{
		my_mlx_pixel_put(&vars->data, x, y, vars->tex.floor);
		y++;
	}
}

unsigned int	get_color(t_data *data, int x, int y)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void			ft_color(t_vars *vars, t_draw *draw, int x, t_frame *frame)
{
	unsigned int	color;
	int				y;

	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		if (frame->side == 0)
		{
			if (frame->ray_dirx > 0)
				color = get_color(&vars->tex.no, draw->texx, draw->tex_pos);
			else
				color = get_color(&vars->tex.so, draw->texx, draw->tex_pos);
		}
		else
		{
			if (frame->ray_diry > 0)
				color = get_color(&vars->tex.we, draw->texx, draw->tex_pos);
			else
				color = get_color(&vars->tex.ea, draw->texx, draw->tex_pos);
		}
		draw->tex_pos += draw->step;
		my_mlx_pixel_put(&vars->data, x, y, color);
		++y;
	}
}

void			draw_tx(t_vars *vars, t_frame *frame, t_draw *draw, int x)
{
	double	wallx;

	draw->draw_end = draw->line_height / 2 + vars->set.screen_height / 2;
	if (draw->draw_end >= vars->set.screen_height)
		draw->draw_end = vars->set.screen_height;
	if (frame->side == 0)
		wallx = vars->set.posy + frame->perp_wall_dist * frame->ray_diry;
	else
		wallx = vars->set.posx + frame->perp_wall_dist * frame->ray_dirx;
	wallx -= floor((wallx));
	vars->set.z[x] = frame->perp_wall_dist;
	draw->texx = (int)(wallx * (double)vars->set.tex_width);
	if (frame->side == 0 && frame->ray_dirx > 0)
		draw->texx = vars->set.tex_width - draw->texx - 1;
	if (frame->side == 1 && frame->ray_diry < 0)
		draw->texx = vars->set.tex_width - draw->texx - 1;
	draw->step = 1.0 * vars->set.tex_height / draw->line_height;
	draw->tex_pos = (draw->draw_start - vars->set.screen_height / 2 +
		draw->line_height / 2) * draw->step;
	ft_color(vars, draw, x, frame);
}

void			pre_color(t_vars *vars, t_frame *frame, int x)
{
	t_draw	draw;

	if (frame->side == 0)
		frame->perp_wall_dist = (frame->mapx - vars->set.posx + (1 -
			frame->stepx) / 2) / frame->ray_dirx;
	else
		frame->perp_wall_dist = (frame->mapy - vars->set.posy + (1 -
			frame->stepy) / 2) / frame->ray_diry;
	vars->square_cf = (3 * (double)vars->set.screen_width) / (4 *
		(double)vars->set.screen_height);
	draw.line_height = (int)(vars->set.screen_height / frame->perp_wall_dist
		* vars->square_cf);
	draw.draw_start = -draw.line_height / 2 + vars->set.screen_height / 2;
	if (draw.draw_start < 0)
		draw.draw_start = 0;
	draw_tx(vars, frame, &draw, x);
}
