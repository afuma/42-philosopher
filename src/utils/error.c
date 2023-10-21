/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:12:13 by blax              #+#    #+#             */
/*   Updated: 2023/10/19 15:02:37 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

int	handle_error(const char *msg, const char *type_msg)
{
	if (!msg)
		return (2);
	if (!type_msg)
	{
		printf("Error: %s\n", msg);
		return (2);
	}
	printf("Error:");
	if (ft_strcmp(type_msg, "memory") == 0)
		printf("Memory allocating for %s failed !\n", msg);
	else if (ft_strcmp(type_msg, "init") == 0)
		printf("Initialization of %s failed!\n", msg);
	else if (ft_strcmp(type_msg, "init_mutex") == 0)
		printf("Initialization for mutex %s failed!\n", msg);
	return (2);
}

int	ft_error(t_data *data, char *msg)
{
	printf("Error: %s\n", msg);
	free_all_resources(data, data->num_philosophers);
	return (2);
}
