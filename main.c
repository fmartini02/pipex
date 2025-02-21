/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:36:03 by francema          #+#    #+#             */
/*   Updated: 2025/02/21 11:06:10 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_part(t_pipex *pip)
{
	char	*path;

	path = pip->path;
	if (pip->pip_idx == 0)
		first_child(pip, path);
	else if (pip->pip_idx != pip->n_cmds -1)
		mid_child(pip, path);
	else
		last_child(pip, path);
}

void	here_doc_part(t_pipex *pip)
{
	execute_here_doc(pip);
	free_args(pip->args);
	free(pip->path);
	close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
}

void	parent_part(t_pipex *pip, pid_t pid)
{
	int	status;

	status = 0;
	if (pip->pip_idx != pip->n_cmds - 1)
		close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) != 1)
	{
		ft_printf(ERR "Error: child process failed\n" RESET);
		free_mid(pip, OPEN);
	}
	free_args(pip->args);
	free(pip->path);
}

void	main_utils(t_pipex *pip)
{
	pid_t	pid;

	pip->args = give_args(pip->cmds[pip->cmd_idx]);
	pip->path = find_path(pip->args[0], pip);
	if (pip->here_doc_flag == 1)
	{
		here_doc_part(pip);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(ERR "Error: fork failed" RESET);
		free_mid(pip, EXIT_FAILURE);
	}
	else if (pid == 0)
		child_part(pip);
	else
		parent_part(pip, pid);
}

int	check_args(int ac , char **av)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (i < ac)
	{
		if (!av[i] || !av[i][0])
			ret++;
		i++;
	}
	if (i < 5)
		ret++;
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_pipex	pipex;

	i = 0;
	if (check_args(ac, av))
	{
		ft_printf(ERR "Error:" RESET);
		ft_printf(WARN " Wrong number/type of arguments\n" RESET);
		ft_printf(OK "Usage:" RESET);
		ft_printf(" ./pipex file1 cmd1 cmd2 file2\n");
		exit(127);
	}
	else
		init_struct(&pipex, av, ac, envp);
	while (pipex.cmd_idx < pipex.n_cmds)
	{
		main_utils(&pipex);
		pipex.cmd_idx++;
		pipex.pip_idx++;
	}
	while (i < pipex.n_cmds - 1)
		close(pipex.pipe_fd[i++][READ_END]);
	free_end(&pipex, EXIT_SUCCESS);
}
