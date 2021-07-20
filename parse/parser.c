/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:05:59 by flurk             #+#    #+#             */
/*   Updated: 2021/03/15 14:06:00 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_ar(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar[i]);
	free(ar);
	ar = NULL;
}

int		split(t_vars *vars, char **line, int fd, int *ans)
{
	char	**ar;
	char	*str;

	str = *line;
	ar = ft_split(str, ' ');
	if (!ar)
		get_error("cant get memory");
	if (ar[0] == '\0')
		get_error("non valid map");
	else if (get_resol(ar, vars, ans))
		free_ar(ar);
	else if (get_tex(ar, vars, ans))
		free_ar(ar);
	else if (get_spr(ar, vars, ans))
		free_ar(ar);
	else if (get_col(ar, vars, ans))
		free_ar(ar);
	else if (ft_strncmp(str, "", 1))
		get_error("non valid map");
	free(str);
	if (*ans == 9699690 && parse_map(fd, vars))
		return (1);
	return (0);
}

int		get_text(int fd, t_vars *vars)
{
	char	*line;
	int		l;
	int		ans;

	ans = 1;
	l = 1;
	if ((line = malloc(1)) == NULL)
		get_error("cant get memory for line");
	line[0] = '\0';
	while (l > 0)
	{
		while (!ft_strncmp(line, "", 1))
		{
			free(line);
			l = get_next_line(fd, &line);
			if (l == 0)
				get_error("non valid map");
		}
		if (split(vars, &line, fd, &ans))
			return (1);
		l = get_next_line(fd, &line);
	}
	get_error("non valid map");
	return (0);
}

int		parse_file(char *name, t_vars *vars)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd >= 0 && get_text(fd, vars))
	{
		close(fd);
		return (1);
	}
	else
		get_error("cant open file");
	return (0);
}

void	parse_name(char *argv)
{
	char	*c;

	c = ft_strrchr(argv, '.');
	if (!c || !ft_strncmp(c, argv, ft_strlen(argv)) || ft_strncmp(++c, "cub",
		4))
		get_error("non valid map name");
}
