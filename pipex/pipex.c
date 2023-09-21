/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:04:42 by fmartini          #+#    #+#             */
/*   Updated: 2023/05/24 17:18:44 by fmartini         ###   ########.fr       */
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

#define BUFFER_SIZE 4096

void	get_file(int fd_in, int *fdp, char **envp, char *s)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd_in);
	close(fdp[0]);
	if (dup2(fdp[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fdp[1]);
	if (execve(search_command(give_cmd(s), envp),
		set_args(s), envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	funz(int *fdp, int fd_out, char *s, char **envp)
{
	if (dup2(fdp[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fdp[0]);
	if(dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd_out);
	close(fdp[1]);
	if (execve(search_command(give_cmd(s), envp),
			set_args(s), envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	check(int in, int out)
{
	if (in == -1 || out == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void	create_pip(int *fdp)
{
	if (pipe(fdp) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		fdp[2];
	int		fd_in;
	int		fd_out;
	int		i;

	i = 2;
	if (ac >= 5)
	{
		fd_in = open(ft_strjoin("./", av[1]), O_RDONLY);
		fd_out = open(ft_strjoin("./", av[ac - 1]),
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		check(fd_in, fd_out);
		create_pip(fdp);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			get_file(fd_in, fdp, envp, av[i]);
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
				funz(fdp, fd_out, av[i], envp);
		}
	}
}
