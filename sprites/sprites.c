/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:21:45 by flurk             #+#    #+#             */
/*   Updated: 2021/03/17 17:21:46 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_col(t_vars *vars, int texx, int stripe)
{
	int				y;
	int				d;
	int				texy;
	unsigned int	color;

	y = vars->spr.draw_starty;
	while (y < vars->spr.draw_endy)
	{
		d = (y - vars->spr.vmove_screen) * 256 -
			vars->set.screen_height * 128 + vars->spr.sprite_height
				* 128;
		texy = ((d * vars->set.tex_height) / vars->spr.sprite_height)
			/ 256;
		color = get_color(&vars->tex.sp, texx, texy);
		if (color != 0x00000000)
			my_mlx_pixel_put(&vars->data, stripe, y, color);
		y++;
	}
}

void	put_spr(t_vars *vars, int stripe)
{
	int				texx;

	while (stripe < vars->spr.draw_endx)
	{
		texx = (int)(256 * (stripe - (-vars->spr.sprite_width / 2 +
			vars->spr.sprite_screenx)) * vars->set.tex_width /
				vars->spr.sprite_width) / 256;
		if (vars->spr.transformy > 0 && stripe >= 0 && stripe <=
			vars->set.screen_width && vars->spr.transformy <
				vars->set.z[stripe])
		{
			put_col(vars, texx, stripe);
		}
		stripe++;
	}
}

void	pre_sprite(t_vars *vars)
{
	int	stripe;

	vars->spr.vmove_screen = (int)(vars->spr.vmove / vars->spr.transformy);
	vars->spr.sprite_height = abs((int)(vars->set.screen_height /
		vars->spr.transformy)) * vars->square_cf;
	vars->spr.draw_starty = -vars->spr.sprite_height / 2 +
		vars->set.screen_height / 2 + vars->spr.vmove_screen;
	if (vars->spr.draw_starty < 0)
		vars->spr.draw_starty = 0;
	vars->spr.draw_endy = vars->spr.sprite_height / 2 + vars->set.screen_height
		/ 2 + vars->spr.vmove_screen;
	if (vars->spr.draw_endy >= vars->set.screen_height)
		vars->spr.draw_endy = vars->set.screen_height;
	vars->spr.sprite_width = abs((int)(vars->set.screen_height /
		vars->spr.transformy)) * vars->square_cf;
	vars->spr.draw_startx = -vars->spr.sprite_width / 2 +
		vars->spr.sprite_screenx;
	if (vars->spr.draw_startx < 0)
		vars->spr.draw_startx = 0;
	vars->spr.draw_endx = vars->spr.sprite_width / 2 +
		vars->spr.sprite_screenx - 1;
	if (vars->spr.draw_endx >= vars->set.screen_width)
		vars->spr.draw_endx = vars->set.screen_width;
	stripe = vars->spr.draw_startx;
	put_spr(vars, stripe);
}

void	draw_sprite(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->count_spr)
	{
		vars->spr.spritex = vars->sprites[i][0] - vars->set.posx;
		vars->spr.spritey = vars->sprites[i][1] - vars->set.posy;
		vars->spr.inv_det = 1.0 / (vars->set.planex * vars->set.diry -
			vars->set.dirx * vars->set.planey);
		vars->spr.transformx = vars->spr.inv_det * (vars->set.diry *
			vars->spr.spritex - vars->set.dirx * vars->spr.spritey);
		vars->spr.transformy = vars->spr.inv_det * (-vars->set.planey *
			vars->spr.spritex + vars->set.planex * vars->spr.spritey);
		vars->spr.sprite_screenx = (int)((vars->set.screen_width / 2) *
			(1 + vars->spr.transformx / vars->spr.transformy));
		vars->spr.vmove = 0.0;
		pre_sprite(vars);
		++i;
	}
}

void	update_sprite(t_vars *vars)
{
	int		k;
	int		i;
	size_t	j;

	k = 0;
	i = 0;
	while (i < vars->count_map)
	{
		j = 0;
		while (j < ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] == '2')
			{
				vars->sprites[k][0] = i + 0.5;
				vars->sprites[k][1] = j + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
	spr_distance(vars);
	sort_spr(vars->sprites, vars->count_spr);
}
