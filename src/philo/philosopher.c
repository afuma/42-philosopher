/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:40:23 by blax              #+#    #+#             */
/*   Updated: 2023/10/21 14:03:27 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parsing(argc, argv) == 2)
		return (handle_error("Parsing failed !", ""));
	if (ft_init(&data, argc, argv) == 2)
		return (ft_error(&data, "Initialization failed !"));
	while (!is_finish(&data))
		usleep(125);
	free_all_resources(&data, data.num_philosophers);
	return (0);
}
