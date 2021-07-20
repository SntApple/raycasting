/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:17:36 by flurk             #+#    #+#             */
/*   Updated: 2021/03/17 17:17:37 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img(int fd, t_vars *vars)
{
	unsigned char	buf[3];
	unsigned int	color;
	int				i;
	int				j;

	i = vars->set.screen_height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < vars->set.screen_width)
		{
			color = get_color(&vars->data, j, i);
			buf[0] = (unsigned char)(color);
			buf[1] = (unsigned char)(color >> 8);
			buf[2] = (unsigned char)(color >> 16);
			write(fd, buf, 3);
			j++;
		}
		i--;
		write(fd, 0, 1);
	}
}

void	info(int fd, t_vars *vars)
{
	unsigned char	buf[40];
	int				n;

	ft_memset(buf, 0, 40);
	buf[0] = (unsigned char)40;
	n = vars->set.screen_width;
	buf[4] = (unsigned char)(n % 256);
	buf[5] = (unsigned char)(n / 256 % 256);
	buf[6] = (unsigned char)(n / 256 / 256 % 256);
	buf[7] = (unsigned char)(n / 256 / 256 / 256);
	n = vars->set.screen_height;
	buf[8] = (unsigned char)(n % 256);
	buf[9] = (unsigned char)(n / 256 % 256);
	buf[10] = (unsigned char)(n / 256 / 256 % 256);
	buf[11] = (unsigned char)(n / 256 / 256 / 256);
	buf[12] = (unsigned char)(1);
	buf[14] = (unsigned char)(24);
	write(fd, buf, 40);
}

void	header(int fd)
{
	unsigned char	buf[14];

	ft_memset(buf, 0, 14);
	buf[0] = (unsigned char)(66);
	buf[1] = (unsigned char)(77);
	buf[10] = (unsigned char)(54);
	write(fd, buf, 14);
}

void	save(t_vars *vars)
{
	int fd;

	fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		get_error("cant create bmp file");
	header(fd);
	info(fd, vars);
	img(fd, vars);
	close(fd);
}
