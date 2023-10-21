/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:06:34 by edesaint          #+#    #+#             */
/*   Updated: 2023/10/19 15:06:36 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosopher.h"

bool	param_overflow_char(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_overflow_char(argv[i]))
		{
			handle_error("Argument have a value superior to INTMAX !", "");
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_overflow_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 10)
			return (true);
		i++;
	}
	return (false);
}

bool	is_valid_number(char *argv[])
{
	int			i;
	long int	nb;

	i = 1;
	while (argv[i])
	{
		nb = ft_atol(argv[i]);
		if (nb > INT_MAX || nb <= 0)
		{
			handle_error("Argument have a wrong value !", "");
			return (false);
		}
		i++;
	}
	return (true);
}

long int	ft_atol(const char *str)
{
	long int	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

int	ft_atoi(const char *str)
{
	return ((int) ft_atol(str));
}
