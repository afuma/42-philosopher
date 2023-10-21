/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:21:11 by blax              #+#    #+#             */
/*   Updated: 2023/10/19 15:03:50 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	is_number(char *str)
{
	int	i;
	int	len_str;

	i = 0;
	len_str = ft_strlen(str);
	while (i < len_str)
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	param_is_number(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]))
		{
			handle_error("Argument is not a number !", "");
			return (false);
		}
		i++;
	}
	return (true);
}

int	parsing(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (handle_error("Number of arguments !", ""));
	if (!param_is_number(argv) || param_overflow_char(argv)
		|| !is_valid_number(argv))
	{
		return (2);
	}
	return (1);
}
