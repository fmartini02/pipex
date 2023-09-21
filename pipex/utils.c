/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:12:28 by fmartini          #+#    #+#             */
/*   Updated: 2023/05/10 17:13:34 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

char	*give_cmd(char *s)
{
	char	*r = (char *) malloc(10 * sizeof(char));
	int	i = 0;
	
	if(r == NULL)
		return(NULL);
	while((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z'))
	{
		r[i] = *s;
		s++;
		i++;
	}
	r[i] = '\0';
	return(r);
}
int	path_str(char **envp)
{
	int	i;
	int	j;
	char	*c;

	i = 0;
	j = 0;
	c = "PATH";
	
	while(envp[i][j] != '=')
	{
		if(envp[i][j] == c[j])
			j++;
		else
		{
			j=0;
			i++;
		}
	}
	return(i);
}


char *search_command(const char *command, char **envp)
{
    int	i;
    char **dir;
    int	j;
    char *str;

    i = path_str(envp);
    j = 0;
    str = ft_strchr(envp[i], '/');
    dir = ft_split(str, ':');
    command= ft_strjoin("/",command);
    while(dir[j])
    {
    	if(access(ft_strjoin(dir[j],command), X_OK) == 0)
    		return(ft_strjoin(dir[j],command));
    	j++;
    }
    return(0);
}
