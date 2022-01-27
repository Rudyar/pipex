/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:26:04 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 19:04:53 by arudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (envp[0] == NULL)
	{
		ft_putstr_fd("Can't find env\n", 2);
		exit (EXIT_FAILURE);
	}
	find_data(ac, av, envp, &data);
	pipex(envp, av, &data);
	free_struct(&data);
	if (close(data.infile) == -1)
		exit (EXIT_FAILURE);
	if (close(data.outfile) == -1)
		exit (EXIT_FAILURE);
	return (0);
}
