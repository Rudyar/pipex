/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:23:52 by arudy             #+#    #+#             */
/*   Updated: 2022/01/28 10:30:16 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_infile(char **av, t_data *data)
{
	data->infile = open(av[1], O_RDONLY);
	if (data->infile < 0)
	{
		perror(av[1]);
		free_struct(data);
		exit (2);
	}
}

void	open_outfile(char **av, t_data *data)
{
	data->outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->outfile < 0)
	{
		perror(av[4]);
		free_struct(data);
		close(data->infile);
		exit (2);
	}
}

void	child_1(char **av, char **env, t_data *data)
{
	if (dup2(data->infile, 0) == -1)
		error_dup2(data);
	if (close(data->pipe_fd[0]) == -1)
		error_dup2(data);
	if (dup2(data->pipe_fd[1], 1) == -1)
		error_dup2(data);
	execve(data->path1, data->cmd1, env);
	ft_putstr_fd(av[2], 2);
	ft_putstr_fd(": can't execute command\n", 2);
	free_struct(data);
	close(data->pipe_fd[1]);
	close(data->infile);
	close(data->outfile);
	exit(126);
}

void	child_2(char **av, char **env, t_data *data)
{
	if (dup2(data->outfile, 1) == -1)
		error_dup22(data);
	if (close(data->pipe_fd[1]) == -1)
		error_dup22(data);
	if (dup2(data->pipe_fd[0], 0) == -1)
		error_dup22(data);
	execve(data->path2, data->cmd2, env);
	ft_putstr_fd(av[3], 2);
	ft_putstr_fd(": can't execute command\n", 2);
	free_struct(data);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->infile);
	close(data->outfile);
	exit(126);
}

void	pipex(char **env, char **av, t_data *data)
{
	open_infile(av, data);
	open_outfile(av, data);
	if (pipe(data->pipe_fd) < 0)
		error_pid1(data);
	data->pid1 = fork();
	if (data->pid1 < 0)
		error_pid1(data);
	if (data->pid1 == 0)
		child_1(av, env, data);
	data->pid2 = fork();
	if (data->pid2 < 0)
		error_pid2(data);
	if (data->pid2 == 0)
		child_2(av, env, data);
	if (close(data->pipe_fd[0]) == -1)
		exit (EXIT_FAILURE);
	if (close(data->pipe_fd[1]) == -1)
		exit (EXIT_FAILURE);
	wait(NULL);
}
