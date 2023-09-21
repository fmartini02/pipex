/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:35 by fmartini          #+#    #+#             */
/*   Updated: 2022/10/12 15:33:34 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_wcount(const char *str, char c)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (*str)
	{
		if (*str != c && check == 0)
		{
			check = 1;
			i++;
		}
		else if (*str == c)
			check = 0;
		str++;
	}
	return (i);
}

char	*ft_ultstrdup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**arr;

	arr = malloc((ft_wcount(s, c) + 1) * sizeof(char *));
	if (!arr || !s)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || s[i] == '\0') && index >= 0)
		{
			arr[j++] = ft_ultstrdup(s, index, i);
			index = -1;
		}
		i++;
	}
	arr[j] = 0;
	return (arr);
}
