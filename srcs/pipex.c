/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:09:19 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 15:32:20 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_access_child_1(char **av, t_data *data)
{
	data->infile = open(av[1], O_RDONLY);
	if (!data->infile)
	{
		perror(av[1]);
		ft_putstr_fd(" : Can't open the file\n", 2);
		free_struct(data);
		exit (EXIT_FAILURE);
	}
}

void	check_access_child_2(char **av, t_data *data)
{
	data->outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!data->outfile)
	{
		perror(av[4]);
		ft_putstr_fd(" : Can't open the file\n", 2);
		free_struct(data);
		close(data->infile);
		exit (EXIT_FAILURE);
	}
}

void	child_1(char **av, char **env, t_data *data)
{
	dup2(data->infile, 0);
	close(data->pipe_fd[0]);
	dup2(data->pipe_fd[1], 1);
	execve(data->path1, data->cmd1, env);
	ft_putstr_fd(av[2], 2);
	ft_putstr_fd(" : can't exec cmd\n", 2);
	free_struct(data);
}

void	child_2(char **av, char **env, t_data *data)
{
	dup2(data->outfile, 1);
	close(data->pipe_fd[1]);
	dup2(data->pipe_fd[0], 0);
	execve(data->path2, data->cmd2, env);
	ft_putstr_fd(av[3], 2);
	ft_putstr_fd(" : can't exec cmd\n", 2);
	free_struct(data);
}

void	pipex(char **env, char **av, t_data *data)
{
	int	status;

	check_access_child_1(av, data);
	check_access_child_2(av, data);
	pipe(data->pipe_fd);
	if (pipe(data->pipe_fd) == -1)
		return ;
	data->pid1 = fork();
	if (data->pid1 < 0)
		return ;
	if (data->pid1 == 0)
		child_1(av, env, data);
	data->pid2 = fork();
	if (data->pid2 < 0)
		return ;
	if (data->pid2 == 0)
		child_2(av, env, data);
	if (close(data->pipe_fd[0]) == -1)
		exit (EXIT_FAILURE);
	if (close(data->pipe_fd[1]) == -1)
		exit (EXIT_FAILURE);
	// waitpid(data->pid1, NULL, 0);
	wait(&status);
	close(data->infile);
	close(data->outfile);
}
