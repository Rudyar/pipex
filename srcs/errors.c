/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:59:56 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 19:03:11 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_pid1(t_data *data)
{
	close(data->infile);
	close(data->outfile);
	free_struct(data);
	exit (EXIT_FAILURE);
}

void	error_pid2(t_data *data)
{
	close(data->infile);
	close(data->outfile);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	free_struct(data);
	exit (EXIT_FAILURE);
}

void	error_dup2(t_data *data)
{
	close(data->infile);
	close(data->outfile);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	free_struct(data);
	exit (EXIT_FAILURE);
}

void	error_dup22(t_data *data)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(data->infile);
	close(data->outfile);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	free_struct(data);
	exit (EXIT_FAILURE);
}
