/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:36:18 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 19:27:59 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_args(int ac, char **av)
{
	size_t	i;

	i = 0;
	if (av[2] == NULL || av[3] == NULL || ac != 5)
	{
		ft_putstr_fd("Error\nEx args : < file1 cmd1 | cmd2 > file2\n", 2);
		exit (EXIT_FAILURE);
	}
	while (av[2][i] == ' ')
		i++;
	if (i == ft_strlen(av[2]))
	{
		ft_putstr_fd("Error\nEx args : < file1 cmd1 | cmd2 > file2\n", 2);
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (av[3][i] == ' ')
		i++;
	if (i == ft_strlen(av[3]))
	{
		ft_putstr_fd("Error\nEx args : < file1 cmd1 | cmd2 > file2\n", 2);
		exit (EXIT_FAILURE);
	}
}

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

char	*check_access(int c, char **strs, t_data *data)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (strs[i])
	{
		if (access(strs[i], F_OK) == 0)
		{
			path = malloc(sizeof(char) * ft_strlen(strs[i]) + 1);
			if (!path)
				return (cmd_not_found(data, c));
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
	return (cmd_not_found(data, c));
}

void	fill_data(char *str, t_data *data)
{
	if (add_cmd(data->child1, data->cmd1[0]) == 1
		|| add_cmd(data->child2, data->cmd2[0]) == 1)
		data_error(data, str);
	free(str);
	if (access(data->cmd1[0], F_OK) == 0)
		data->path1 = ft_strdup(data->cmd1[0]);
	else
		data->path1 = check_access(1, data->child1, data);
	if (access(data->cmd2[0], F_OK) == 0)
		data->path2 = ft_strdup(data->cmd2[0]);
	else
		data->path2 = check_access(2, data->child2, data);
}

void	find_data(int ac, char **av, char **env, t_data *data)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
	check_args(ac, av);
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
	init_data(full_path, av, data);
	fill_data(full_path, data);
}
