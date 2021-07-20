/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:52:09 by flurk             #+#    #+#             */
/*   Updated: 2021/03/07 13:52:14 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_next_frame(t_vars *vars)
{
	t_frame	frame;
	int		x;

	key_hook(vars);
	x = 0;
	while (x < vars->set.screen_width)
	{
		init_frame(vars, &frame, x);
		step(vars, &frame);
		dda(vars, &frame);
		floor_and_ceiling(vars, x);
		pre_color(vars, &frame, x);
		++x;
	}
	update_sprite(vars);
	draw_sprite(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	return (1);
}

void	get_textures(t_vars *vars)
{
	vars->tex.no.img = mlx_xpm_file_to_image(vars->mlx, vars->tex.path_no,
	&vars->set.tex_width, &vars->set.tex_height);
	if (!vars->tex.no.img)
		get_error("invalid north texture");
	vars->tex.so.img = mlx_xpm_file_to_image(vars->mlx, vars->tex.path_so,
		&vars->set.tex_width, &vars->set.tex_height);
	if (!vars->tex.so.img)
		get_error("invalid south texture");
	vars->tex.we.img = mlx_xpm_file_to_image(vars->mlx, vars->tex.path_we,
		&vars->set.tex_width, &vars->set.tex_height);
	if (!vars->tex.we.img)
		get_error("invalid west texture");
	vars->tex.ea.img = mlx_xpm_file_to_image(vars->mlx, vars->tex.path_ea,
		&vars->set.tex_width, &vars->set.tex_height);
	if (!vars->tex.ea.img)
		get_error("invalid east texture");
	vars->tex.sp.img = mlx_xpm_file_to_image(vars->mlx, vars->tex.path_sp,
		&vars->set.sp_width, &vars->set.sp_height);
	if (!vars->tex.sp.img)
		get_error("invalid sprite");
	get_addr(vars);
}

int		create_screen(t_vars vars)
{
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.set.screen_width,
		vars.set.screen_height, "cub3d");
	vars.data.img = mlx_new_image(vars.mlx, vars.set.screen_width,
		vars.set.screen_height);
	vars.data.addr = mlx_get_data_addr(vars.data.img,
		&vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);
	set_param(&vars);
	get_textures(&vars);
	free(vars.tex.path_no);
	free(vars.tex.path_so);
	free(vars.tex.path_ea);
	free(vars.tex.path_we);
	free(vars.tex.path_sp);
	init_sprites(&vars);
	render_next_frame(&vars);
	save(&vars);
	return (1);
}

void	create_window(t_vars vars)
{
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.set.screen_width,
		vars.set.screen_height, "cub3d");
	vars.data.img = mlx_new_image(vars.mlx, vars.set.screen_width,
		vars.set.screen_height);
	vars.data.addr = mlx_get_data_addr(vars.data.img,
		&vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);
	set_param(&vars);
	get_textures(&vars);
	free(vars.tex.path_no);
	free(vars.tex.path_so);
	free(vars.tex.path_ea);
	free(vars.tex.path_we);
	free(vars.tex.path_sp);
	init_sprites(&vars);
	init_key(&vars);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, key_release, &vars);
	mlx_hook(vars.win, 17, 1L << 0, ft_close, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}

int		main(int argc, char **argv)
{
	t_vars vars;

	vars.pos = 0;
	if (argc == 2 || argc == 3)
	{
		vars.save = argc == 3 ? 1 : 0;
		parse_name(argv[1]);
		if (parse_file(argv[1], &vars))
		{
			if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
				create_screen(vars);
			else if (argc == 2)
				create_window(vars);
			else
				get_error("non valid arguments");
		}
	}
	else if (argc == 1)
		get_error("has no map");
	else
		get_error("too many arguments");
	return (0);
}
