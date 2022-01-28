/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:20:37 by arudy             #+#    #+#             */
/*   Updated: 2022/01/28 10:30:53 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	data_error(t_data *data, char *path)
{
	ft_putstr_fd("Can't init data\n", 2);
	free_struct(data);
	free(path);
	exit (EXIT_FAILURE);
}

void	init_data(char *path, char **av, t_data *data)
{
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
}

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = ft_strlen(src);
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (0);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*cmd_not_found(t_data *data, int c)
{
	if (c == 1)
		ft_putstr_fd(data->cmd1[0], 2);
	else if (c == 2)
		ft_putstr_fd(data->cmd2[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_struct(data);
	exit (127);
}
