/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:10 by flurk             #+#    #+#             */
/*   Updated: 2021/03/15 14:37:11 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_list(t_list **p)
{
	t_list *s;

	if (*p)
	{
		while (*p)
		{
			s = *p;
			*p = (*p)->next;
			free(s);
		}
	}
	p = 0;
}

int		get_map(t_vars *vars, t_list **new)
{
	int		i;
	t_list	*p;

	p = *new;
	vars->map = malloc(sizeof(char*) * vars->count_map);
	if (!vars->map)
		get_error("cant get memory for map");
	i = 0;
	while (i < vars->count_map)
	{
		vars->map[i] = p->content;
		p = p->next;
		i++;
	}
	free_list(new);
	if (!is_valid(vars, vars->map))
		get_error("non valid map");
	get_pos(vars);
	return (1);
}

int		parse_map(int fd, t_vars *vars)
{
	char	*line;
	int		l;
	t_list	*new;

	vars->count_map = 0;
	l = 1;
	if ((line = malloc(1)) == NULL)
		get_error("cant get memory for line");
	line[0] = '\0';
	new = NULL;
	while (!ft_strncmp(line, "", 1) && l > 0)
	{
		free(line);
		l = get_next_line(fd, &line);
	}
	while (ft_strncmp(line, "", 1) && l > 0)
	{
		ft_lstadd_back(&new, ft_lstnew(line));
		vars->count_map++;
		l = get_next_line(fd, &line);
	}
	ft_lstadd_back(&new, ft_lstnew(line));
	vars->count_map++;
	get_map(vars, &new);
	return (1);
}
