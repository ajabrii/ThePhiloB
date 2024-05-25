/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:46:30 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/25 18:53:55 by kali             ###   ########.fr       */
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


	long	t;
	int 	id;

	t = ft_gettime() - data->start_t;
	sem_wait(data->psem);
	id = data->philos.id;
	if (get_status(data) == DIED)
	{
		printf(PER "%ld   %d" RES "   	died\n", t, id);
		sem_post(data->psem);
		return (false);
	}
	else
		printf(PER "%ld   %d" RES "    %s\n", t, data->philos.id, msg);
	sem_post(data->psem);
	// sem_wait(data->psem);
	// if (someone_died())
	// {
	// 	sem_post(data->psem);
	// 	return (false);
	// }
	// printf(PER "%ld   %d" RES "    %s\n", ft_gettime() - data->start_t, data->philos.id, msg);
	// sem_post(data->psem);
	return (true);
}
