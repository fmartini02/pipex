/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:52:45 by francema          #+#    #+#             */
/*   Updated: 2025/02/19 17:51:18 by francema         ###   ########.fr       */
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
# include "ft_printf/bonus/ft_printf_bonus.h"

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define YELLOW "\033[0;33m"
# define MAGENTA "\033[0;35m"
# define WHITE "\033[0;37m"
# define BLACK "\033[0;30m"
# define PURPLE "\033[0;35m"
# define BROWN "\033[0;33m"
# define GREY "\033[0;37m"
# define GREEN "\033[0;32m"
# define BRIGHT_RED "\033[1;91m"
# define BRIGHT_BLUE "\033[1;94m"
# define BRIGHT_CYAN "\033[1;96m"
# define BRIGHT_YELLOW "\033[1;93m"
# define BRIGHT_MAGENTA "\033[1;95m"
# define BRIGHT_WHITE "\033[1;97m"
# define BRIGHT_BLACK "\033[1;90m"
# define BRIGHT_PURPLE "\033[1;95m"
# define BRIGHT_BROWN "\033[1;93m"
# define BRIGHT_GREY "\033[1;97m"
# define BRIGHT_GREEN "\033[1;92m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define B_U "\033[1;4m"
# define ERR "\033[1;4;91m"
# define OK "\033[1;92m"
# define WARN "\033[1;93m"
# define RESET "\033[0m"

enum e_pipe
{
	READ_END,
	WRITE_END
};

enum e_errors
{
	EXECVE = 2,
	PIPE = 3,
	OPEN = 4,
	DUP2 = 5,
	MALLOC = 6,
	PATH = 7,
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
	int		n_pipes;
	char	*delimiter;
	char	*file_in;
	char	*file_out;
	char	*path;
	int		here_doc_flag;
}	t_pipex;

int		main(int argc, char **argv, char **envp);
void	init_struct(t_pipex *pip, char **av, int ac, char **envp);
char	*find_path(char *cmd, t_pipex *pip);
char	**give_args(char *cmd);
void	close_pipfd(t_pipex *pip);
void	execute_here_doc(t_pipex *pip);
void	child_part(t_pipex *pip);
void	first_child(t_pipex *pip, char *path);
void	mid_child(t_pipex *pip, char *path);
void	last_child(t_pipex *pip, char *path);
void	free_here_doc(t_pipex *pip);
void	free_bf_execve(t_pipex *pip);
void	free_mid(t_pipex *pip, int exit_code);
void	free_end(t_pipex *pip, int exit_code);
void	free_args(char **args);

#endif
