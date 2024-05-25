/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:38:34 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/12 11:47:00 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_sleeping(t_philo *philo)
{
	set_state(philo, SLEEP);
	if (get_state(philo) == DIED)
		return (0);
	ft_output(philo->all, philo->id, PER "is sleeping" RES);
	ft_usleep(philo->all->t_sleep);
	return (1);
}

int	ft_thinking(t_philo *philo)
{
	set_state(philo, THINK);
	if (get_state(philo) == DIED)
		return (0);
	ft_output(philo->all, philo->id, ORG "is thinking" RES);
	return (1);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_lst_time(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->all->t_eat);
	while (get_state(philo) != DIED && !get_simulation(philo->all))
	{
		if (!ft_eating(philo))
			break ;
		if (get_state(philo) == DIED)
			break ;
		if (!ft_sleeping(philo))
			break ;
		if (get_state(philo) == DIED)
			break ;
		if (!ft_thinking(philo))
			break ;
		if (get_state(philo) == DIED)
			break ;
	}
	return (NULL);
}
