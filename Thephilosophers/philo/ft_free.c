/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:38:53 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/11 10:01:50 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_free_all(t_all *data)
{
	int	index;

	index = -1;
	while (++index < data->nphilo)
	{
		pthread_mutex_destroy(&data->forks[index]);
		pthread_mutex_destroy(&data->philos[index].state);
		pthread_mutex_destroy(&data->philos[index].m_lst_time);
		pthread_mutex_destroy(&data->philos[index].m_nb_meal);
	}
	pthread_mutex_destroy(&data->pmtx);
	pthread_mutex_destroy(&data->m_simulation);
	pthread_mutex_destroy(&data->m_start_time);
	pthread_mutex_destroy(&data->m_t_die);
	pthread_mutex_destroy(&data->m_t_eat);
	pthread_mutex_destroy(&data->m_t_sleep);
	free(data->philos);
	free(data->forks);
}
