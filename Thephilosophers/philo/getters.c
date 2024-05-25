/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:56:15 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/05 14:33:45 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	get_lst_time(t_philo *philo)
{
	long	res;

	pthread_mutex_lock(&philo->m_lst_time);
	res = philo->lst_time;
	pthread_mutex_unlock(&philo->m_lst_time);
	return (res);
}

t_state	get_state(t_philo *philo)
{
	t_state	status;

	pthread_mutex_lock(&philo->state);
	status = philo->status;
	pthread_mutex_unlock(&philo->state);
	return (status);
}

long	get_start_time(t_all *data)
{
	long	res;

	pthread_mutex_lock(&data->m_start_time);
	res = data->start_time;
	pthread_mutex_unlock(&data->m_start_time);
	return (res);
}

long	get_nb_meal(t_philo *philo)
{
	long	res;

	pthread_mutex_lock(&philo->m_nb_meal);
	res = philo->nb_meal;
	pthread_mutex_unlock(&philo->m_nb_meal);
	return (res);
}

bool	get_simulation(t_all *data)
{
	bool	res;

	pthread_mutex_lock(&data->m_simulation);
	res = data->simulation;
	pthread_mutex_unlock(&data->m_simulation);
	return (res);
}
