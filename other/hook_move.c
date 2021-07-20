/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 19:30:54 by flurk             #+#    #+#             */
/*   Updated: 2021/03/16 19:31:01 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		valid_pos(char c)
{
	if (c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

void	move(t_vars *vars, double move_speed)
{
	if (vars->key.fw == 1 || vars->key.fw_w == 1)
	{
		if (valid_pos(vars->map[(int)(vars->set.posx + vars->set.dirx *
			move_speed)]
			[(int)vars->set.posy]))
		{
			vars->set.posx += vars->set.dirx * move_speed;
		}
		if (valid_pos(vars->map[(int)vars->set.posx][(int)(vars->set.posy +
			vars->set.diry * move_speed)]))
			vars->set.posy += vars->set.diry * move_speed;
	}
	if (vars->key.bc == 1 || vars->key.bc_w == 1)
	{
		if (valid_pos(vars->map[(int)(vars->set.posx - vars->set.dirx *
			move_speed)]
			[(int)vars->set.posy]))
			vars->set.posx -= vars->set.dirx * move_speed;
		if (valid_pos(vars->map[(int)vars->set.posx][(int)(vars->set.posy -
			vars->set.diry * move_speed)]))
			vars->set.posy -= vars->set.diry * move_speed;
	}
}

void	rot(t_vars *vars, double r)
{
	double old_dx;
	double old_px;

	if (vars->key.r == 1)
	{
		old_dx = vars->set.dirx;
		vars->set.dirx = vars->set.dirx * cos(r) - vars->set.diry * sin(r);
		vars->set.diry = old_dx * sin(r) + vars->set.diry * cos(r);
		old_px = vars->set.planex;
		vars->set.planex = vars->set.planex * cos(r) - vars->set.planey *
			sin(r);
		vars->set.planey = old_px * sin(r) + vars->set.planey * cos(r);
	}
	if (vars->key.l == 1)
	{
		old_dx = vars->set.dirx;
		vars->set.dirx = vars->set.dirx * cos(-r) - vars->set.diry * sin(-r);
		vars->set.diry = old_dx * sin(-r) + vars->set.diry * cos(-r);
		old_px = vars->set.planex;
		vars->set.planex = vars->set.planex * cos(-r) -
			vars->set.planey * sin(-r);
		vars->set.planey = old_px * sin(-r) + vars->set.planey * cos(-r);
	}
}

void	strafe(t_vars *vars, double move_speed)
{
	if (vars->key.sr == 1)
	{
		if (valid_pos(vars->map[(int)(vars->set.posx + vars->set.planex *
			move_speed)]
			[(int)vars->set.posy]))
		{
			vars->set.posx += vars->set.planex * move_speed;
		}
		if (valid_pos(vars->map[(int)vars->set.posx][(int)(vars->set.posy +
			vars->set.planey * move_speed)]))
			vars->set.posy += vars->set.planey * move_speed;
	}
	if (vars->key.sl == 1)
	{
		if (valid_pos(vars->map[(int)(vars->set.posx - vars->set.planex *
			move_speed)]
			[(int)vars->set.posy]))
			vars->set.posx -= vars->set.planex * move_speed;
		if (valid_pos(vars->map[(int)vars->set.posx][(int)(vars->set.posy -
			vars->set.planey * move_speed)]))
			vars->set.posy -= vars->set.planey * move_speed;
	}
}
