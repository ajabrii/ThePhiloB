/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilss.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:10:24 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/12 11:01:43 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_error(char *err)
{
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	exit(1);
}

static int	ft_check(long nb, int flag)
{
	if (nb <= flag || nb > 2147483647)
		return (0);
	return (1);
}

long	ft_atol(char *str, int flag)
{
	int		i;
	long	r;
	int		sign;

	i = 0;
	r = 0;
	sign = 1;
	if (!str)
		return (0);
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	if (!ft_check((r * sign), flag))
		ft_error("Error");
	return (r * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
