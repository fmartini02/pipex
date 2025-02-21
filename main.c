/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:36:03 by francema          #+#    #+#             */
/*   Updated: 2025/02/21 11:33:56 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(int ac, char **av)
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
