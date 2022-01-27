/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:36:18 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 12:44:29 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	add_cmd(char **data, char *cmd)
{
	int	i;

	i = 0;
	while (data[i])
	{
		data[i] = ft_strjoin(data[i], "/");
		if (!data[i])
			return (1);
		data[i] = ft_strjoin(data[i], cmd);
		if (!data[i])
			return (1);
		i++;
	}
	return (0);
}

char	*check_access(char **strs, t_data *data)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (strs[i])
	{
		if (access(strs[i], F_OK))
		{
			path = malloc(sizeof(char) * ft_strlen(strs[i]) + 1);
			if (!path)
				return (cmd_not_found(data));
			while (strs && strs[i][j])
			{
				path[j] = strs[i][j];
				j++;
			}
			path[j] = '\0';
			return (path);
		}
		i++;
	}
	return (cmd_not_found(data));
}

t_data	*fill_data(char *str, t_data *data)
{
	if (add_cmd(data->child1, data->cmd1[0]) == 1
		|| add_cmd(data->child2, data->cmd2[0]) == 1)
		data_error(data, str);
	free(str);
	data->path1 = check_access(data->child1, data);
	data->path2 = check_access(data->child2, data);
	return (data);
}

t_data	*find_data(char **env, char **av)
{
	int		i;
	char	*full_path;
	t_data	*data;

	i = 0;
	full_path = NULL;
	while (env[i++])
	{
		if (!ft_strncmp("PATH=", env[i], 4))
		{
			full_path = ft_substr(env[i], 5, ft_strlen(env[i]));
			if (!full_path)
				exit (EXIT_FAILURE);
			break ;
		}
	}
	if (!full_path)
	{
		ft_putstr_fd("Can't find PATH in env\n", 2);
		exit (EXIT_FAILURE);
	}
	data = init_data(full_path, av);
	return (fill_data(full_path, data));
}
