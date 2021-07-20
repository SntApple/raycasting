/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:49:10 by flurk             #+#    #+#             */
/*   Updated: 2021/03/11 14:49:21 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		key_hook(t_vars *vars)
{
	double move_speed;
	double rot_speed;

	move_speed = 0.15;
	rot_speed = 0.05;
	if (vars->key.fw == 1 || vars->key.bc == 1 || vars->key.fw_w == 1 ||
		vars->key.bc_w == 1)
		move(vars, move_speed);
	if (vars->key.l == 1 || vars->key.r == 1)
		rot(vars, rot_speed);
	if (vars->key.sl == 1)
		strafe(vars, move_speed);
	if (vars->key.sr == 1)
		strafe(vars, move_speed);
	return (1);
}

int		key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
		vars->key.fw_w = 1;
	if (keycode == 126)
		vars->key.fw = 1;
	if (keycode == 1)
		vars->key.bc_w = 1;
	if (keycode == 125)
		vars->key.bc = 1;
	if (keycode == 124)
		vars->key.l = 1;
	if (keycode == 123)
		vars->key.r = 1;
	if (keycode == 0)
		vars->key.sl = 1;
	if (keycode == 2)
		vars->key.sr = 1;
	return (1);
}

int		key_release(int keycode, t_vars *vars)
{
	if (keycode == 13)
		vars->key.fw_w = 0;
	if (keycode == 126)
		vars->key.fw = 0;
	if (keycode == 1)
		vars->key.bc_w = 0;
	if (keycode == 125)
		vars->key.bc = 0;
	if (keycode == 124)
		vars->key.l = 0;
	if (keycode == 123)
		vars->key.r = 0;
	if (keycode == 0)
		vars->key.sl = 0;
	if (keycode == 2)
		vars->key.sr = 0;
	return (1);
}
