/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 05:35:05 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/12 05:35:07 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(int c);
static int	ft_iswhitespace(char c);

long long	parse_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error: In the arg\n");
				return (1);
			}
			j++;
		}
		if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > INT_MAX
			|| ft_atol(argv[1]) > 200)
		{
			printf("Error: In the arg\n");
			return (1);
		}
		i++;
	}
	return (0);
}

long long	ft_atol(const char *str)
{
	int			i;
	long long	out;

	i = 0;
	out = 0;
	while (ft_iswhitespace(str[i]))
		++i;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		out = out * 10 + (str[i] - '0');
		++i;
	}
	return (out);
}

static int	ft_iswhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
