/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:52:45 by francema          #+#    #+#             */
/*   Updated: 2025/02/04 16:38:58 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

enum e_pipe
{
	READ_END,
	WRITE_END
};

typedef struct s_pipex
{
	char	**envp;
	int		**pipe_fd;
	char	**cmds;
	char	**args;
	int		pip_idx;
	int		cmd_idx;
	int		n_cmds;
	char	*delimiter;
	char	*file_in;
	char	*file_out;
	char	*path;
	int		here_doc_flag;
}	t_pipex;

int		main(int argc, char **argv, char **envp);
void	init_struct(t_pipex *pip, char **av, int ac, char **envp);
char	*find_path(char *cmd);
char	**give_args(char *cmd);
void	close_pipfd(t_pipex *pip);
void	execute_cmds(t_pipex *pip);
void	execute_here_doc(t_pipex *pip);
void	free_mem(t_pipex *pip, int exit_code);

#endif
