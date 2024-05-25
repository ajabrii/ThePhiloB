/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:31:56 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/05 15:58:43 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_lst_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_lst_time);
	philo->lst_time = ft_gettime();
	pthread_mutex_unlock(&philo->m_lst_time);
}

void	set_state(t_philo *philo, t_state status)
{
	pthread_mutex_lock(&philo->state);
	philo->status = status;
	pthread_mutex_unlock(&philo->state);
}

void	set_simulation(t_all *data, bool value)
{
	pthread_mutex_lock(&data->m_simulation);
	data->simulation = value;
	pthread_mutex_unlock(&data->m_simulation);
}

void	set_nb_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_nb_meal);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->m_nb_meal);
}
