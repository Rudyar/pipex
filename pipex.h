/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:26:51 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 19:28:28 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**child1;
	char	**child2;
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
}t_data;

void	find_data(int ac, char **av, char **env, t_data *data);
void	init_data(char *path, char **av, t_data *data);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*cmd_not_found(t_data *data, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	pipex(char **env, char **av, t_data *data);
void	free_strs(char **strs);
void	free_struct(t_data *data);
void	close_all(t_data *data);
void	ft_putstr_fd(char *s, int fd);
void	data_error(t_data *data, char *path);
void	error_pid1(t_data *data);
void	error_pid2(t_data *data);
void	error_dup2(t_data *data);
void	error_dup22(t_data *data);
#endif
