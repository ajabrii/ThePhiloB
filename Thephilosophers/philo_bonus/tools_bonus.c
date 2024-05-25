/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:47:38 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/12 11:01:01 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	count_size(char **av)
{
	int	size;

	size = 0;
	if (!av)
		return (0);
	while (av[size])
		size++;
	return (size);
}

char	**retunr_args(t_ball *ps)
{
	int		i;
	char	*palestine;
	char	*arg;
	char	**args;

	if (!ps->av[1])
		return (NULL);
	arg = ft_strdup(ps->av[1]);
	if (!arg[0])
		ft_error("Error");
	i = 2;
	while (i < ps->ac)
	{
		if (!ps->av[i][0])
			ft_error("Error");
		palestine = ft_strjoin(arg, " ");
		free(arg);
		arg = ft_strjoin(palestine, ps->av[i]);
		free(palestine);
		i++;
	}
	args = ft_split(arg, ' ');
	return (free(arg), args);
}

int	check_nbr(t_ball *ps)
{
	int	i;
	int	p;

	i = 0;
	while (i < ps->size)
	{
		p = 0;
		if (ps->args[i][p] == '-' || ps->args[i][p] == '+')
			p++;
		if (!ps->args[i][p])
			return (0);
		while (ps->args[i][p])
		{
			if (!ft_isdigit(ps->args[i][p]))
				return (0);
			p++;
		}
		i++;
	}
	return (1);
}

void	*ft_malloc(unsigned int size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		return (NULL);
	return (res);
}
