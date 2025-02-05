/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:51:05 by fmartini          #+#    #+#             */
/*   Updated: 2025/01/27 16:00:52 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_char(const char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	str = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	str = malloc((ft_strlen_char(s1, '\0') + ft_strlen_char(s2, '\0') + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (++i < ft_strlen_char(s1, '\0'))
		str[i] = s1[i];
	while (j < ft_strlen_char(s2, '\0'))
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
