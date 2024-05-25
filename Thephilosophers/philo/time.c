/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:46:30 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/05 16:05:48 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	ft_output(t_all *data, int id, char *msg)
{
	long	t;

	t = ft_gettime() - get_start_time(data);
	pthread_mutex_lock(&data->pmtx);
	if (!get_simulation(data))
		printf(PER "%ld   %d" RES "    %s\n", t, id, msg);
	pthread_mutex_unlock(&data->pmtx);
}
