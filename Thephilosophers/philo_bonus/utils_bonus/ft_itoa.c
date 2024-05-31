/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:42:14 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/12 10:57:38 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_count_digit(int nb)
{
	int	counter;

	counter = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		counter += 1;
		nb /= 10;
	}
	return (counter);
}

static char	*ft_transform(char *d, int nbr, int s, int n)
{
	while (nbr-- > 0)
	{
		d[nbr + s] = (n % 10) + '0';
		n = n / 10;
	}
	return (d);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		num;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	num = ft_count_digit(n);
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * (sign + num + 1));
	if (!str)
		return (NULL);
	if (sign)
		str[0] = '-';
	str[num + sign] = '\0';
	ft_transform(str, num, sign, n);
	return (str);
}
