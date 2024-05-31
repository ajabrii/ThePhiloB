/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:46:30 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/31 10:13:12 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_gettime(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		ft_error("gettimeofday() Error");
	return ((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
}

void	ft_usleep(long nb)
{
	long	time;

	time = ft_gettime();
	while ((ft_gettime() - time) < nb)
	{
		usleep(500);
	}
}

bool	ft_output(t_ball *data, char *msg)
{
	sem_post(data->psem);
	sem_wait(data->psem);
	if (philo_died())
	{
		sem_post(data->psem);
		return (false);
	}
	printf(PER "%ld   %d" RES "    %s\n", ft_gettime() - data->start_t,
		data->philos.id, msg);
	sem_post(data->psem);
	return (true);
}
