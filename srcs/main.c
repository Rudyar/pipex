/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 10:26:04 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 15:31:43 by arudy            ###   ########.fr       */
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
		ft_putstr_fd("Can't find env\n", 2);
		exit (EXIT_FAILURE);
	}
	data = find_data(ac, av, env);
	pipex(env, av, data);
	free_struct(data);
	// close_all(data);
	return (0);
}
