/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:20:37 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 12:44:58 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_data	*init_data(char *path, char **av)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	if (!data)
		return (0);
	data->child1 = NULL;
	data->child2 = NULL;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->path1 = NULL;
	data->path2 = NULL;
	data->cmd1 = ft_split(av[2], ' ');
	if (!data->cmd1)
		data_error(data, path);
	data->cmd2 = ft_split(av[3], ' ');
	if (!data->cmd2)
		data_error(data, path);
	data->child1 = ft_split(path, ':');
	if (!data->child1)
		data_error(data, path);
	data->child2 = ft_split(path, ':');
	if (!data->child2)
		data_error(data, path);
	return (data);
}

char	*cmd_not_found(t_data *data)
{
	ft_putstr_fd("")
	free_struct(data);
	exit (EXIT_FAILURE);
}
