/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudy <arudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:59:56 by arudy             #+#    #+#             */
/*   Updated: 2022/01/27 12:27:49 by arudy            ###   ########.fr       */
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
