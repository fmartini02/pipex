/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:06:20 by fmartini          #+#    #+#             */
/*   Updated: 2023/05/10 17:11:56 by fmartini         ###   ########.fr       */
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

size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*give_cmd(char *s);
int	path_str(char **envp);
char *search_command(const char *command, char **envp);
int	ft_wcount(const char *str, char c);
char	*ft_ultstrdup(const char *str, int start, int finish);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**set_args(char *s);
int	opt_count(char *s);
char	*ft_strchr(const char *s, int c);
void	funz(int *fdp, int fd_out, char *s, char **envp);
void	get_file(int fd_in, int *fdp, char **envp, char *s);
void	check(int in, int out);
void	create_pip(int *fdp);
int	change_fd(int fd, int fdp);


#endif
