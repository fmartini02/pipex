/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:34:54 by fmartini          #+#    #+#             */
/*   Updated: 2023/05/18 15:41:37 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	opt_count(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		else if (!(*s == ' ' || *s == '\t' || *s == '\n'))
		{
			while (*s && (!(*s == ' ' || *s == '\t' || *s == '\n')))
				s++;
			i++;
		}
	}
	return (i);
}

char	**set_args(char *s)
{
	int		i;
	int		j;
	int		y;
	char	**args;

	i = opt_count(s);
	j = 0;
	y = 0;
	args = (char **) malloc((i + 1) * sizeof(char *));
	while (y < i)
	{
		while (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		args[y] = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
		while (!(*s == ' ' || *s == '\t' || *s == '\n') && *s)
		{
			args[y][j] = *s;
			s++;
			j++;
		}
		args[y][j] = '\0';
		y++;
		j = 0;
	}
	return (args);
}
