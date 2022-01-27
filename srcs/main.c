/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:26:04 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 12:30:37 by arudy            ###   ########.fr       */
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
		ft_putstr_fd(av[2], 2);
		ft_putstr_fd(" : Command not found\n", 2);
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (av[3][i] == ' ')
		i++;
	if (i == ft_strlen(av[3]))
	{
		ft_putstr_fd(av[3], 2);
		ft_putstr_fd(" : Command not found\n", 2);
		exit (EXIT_FAILURE);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_struct(t_data *data)
{
	free_strs(data->child1);
	free_strs(data->child2);
	free_strs(data->cmd1);
	free_strs(data->cmd2);
	free(data->path1);
	free(data->path2);
	free(data);
}

void	close_all(t_data *data)
{
	close(data->infile);
	close(data->outfile);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (env[0] == NULL)
	{
		ft_putstr_fd("Can't find data in env\n", 2);
		exit (EXIT_FAILURE);
	}
	check_args(ac, av);
	data = find_data(env, av);
	// pipex(env, av, &data);
	free_struct(data);
	// close_all(&data);
	return (0);
}
