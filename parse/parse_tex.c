/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:06:52 by flurk             #+#    #+#             */
/*   Updated: 2021/03/15 14:06:53 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		parse_tex(char **ar)
{
	int		fd;
	char	*c;

	if (ar[1] && !ar[2])
	{
		c = ft_strrchr(ar[1], '.');
		if (ft_strncmp(++c, "xpm", 4))
			get_error("non valid texture or sprite");
		fd = open(ar[1], O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			return (1);
		}
	}
	return (0);
}

int		get_spr(char **ar, t_vars *vars, int *ans)
{
	if (!ft_strncmp(ar[0], "S", 2) && parse_tex(ar))
	{
		if ((vars->tex.path_sp = ft_strdup(ar[1])) == NULL)
			get_error("cant get memory");
		*ans *= 13;
	}
	else
		return (0);
	return (1);
}

int		get_we(char **ar, t_vars *vars)
{
	if (!ft_strncmp(ar[0], "WE", 3) && parse_tex(ar))
	{
		if ((vars->tex.path_we = ft_strdup(ar[1])) == NULL)
			get_error("cant get memory");
		return (1);
	}
	return (0);
}

int		get_tex(char **ar, t_vars *vars, int *ans)
{
	if (!ft_strncmp(ar[0], "NO", 3) && parse_tex(ar))
	{
		if ((vars->tex.path_no = ft_strdup(ar[1])) == NULL)
			get_error("cant get memory");
		*ans *= 3;
	}
	else if (!ft_strncmp(ar[0], "SO", 3) && parse_tex(ar))
	{
		if ((vars->tex.path_so = ft_strdup(ar[1])) == NULL)
			get_error("cant get memory");
		*ans *= 5;
	}
	else if (!ft_strncmp(ar[0], "EA", 3) && parse_tex(ar))
	{
		if ((vars->tex.path_ea = ft_strdup(ar[1])) == NULL)
			get_error("cant get memory");
		*ans *= 7;
	}
	else if (get_we(ar, vars))
		*ans *= 11;
	else
		return (0);
	return (1);
}

int		get_resol(char **ar, t_vars *vars, int *ans)
{
	int	width;
	int	height;

	if (!ft_strncmp(ar[0], "R", 2) && ar[1] && ar[2] && is_num(ar[1]) &&
		is_num(ar[2]))
	{
		width = ft_atoi(ar[1]);
		height = ft_atoi(ar[2]);
		if (width == -1)
			width = 2147483647;
		if (height == -1)
			height = 2147483647;
		if (width > 0 && height > 0 && !ar[3])
		{
			vars->set.screen_height = height;
			vars->set.screen_width = width;
			*ans *= 2;
			get_screen_size(&vars->set);
			return (1);
		}
		else
			get_error("non valid resolution");
	}
	return (0);
}
