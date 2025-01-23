/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:52:45 by francema          #+#    #+#             */
/*   Updated: 2025/01/23 19:09:21 by francema         ###   ########.fr       */
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

enum pipe_macro
{
	READ_END,
	WRITE_END
};

typedef struct s_pipex
{
	int		**pipe_fd;
	int		pip_idx;
	char	**cmds;
	int		cmd_idx;
	int		n_cmds;
	int		here_doc_flag;
	char	*delimiter;
	char	*file_in;
	char	*file_out;
}	t_pipex;

int		main(int argc, char **argv);
char	*find_path(char *cmd);
void	execute_cmds(t_pipex *pip, char *path);
void	execute_here_doc(t_pipex *pip, char *path);
void	init_struct(t_pipex *pip, char **av, int ac);


#endif
