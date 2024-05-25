/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:13:45 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/04 09:46:56 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	dropfork(t_philo *philo, char flag)
{
	if (flag == 'L')
	{
		if (pthread_mutex_unlock(philo->l_fork))
			return (0);
	}
	else if (flag == 'R')
	{
		if (pthread_mutex_unlock(philo->r_fork))
			return (0);
	}
	return (1);
}

int	take_lfork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork))
		return (0);
	ft_output(philo->all, philo->id, CY "has taken a fork" RES);
	return (1);
}

int	take_rfork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork))
		return (0);
	ft_output(philo->all, philo->id, CY "has taken a fork" RES);
	return (1);
}

int	asign_forks(t_philo *philo)
{
	if (philo->all->nphilo == 1)
	{
		take_lfork(philo);
		ft_usleep(philo->all->t_die);
		return (0);
	}
	if (!take_lfork(philo))
		return (0);
	if (!take_rfork(philo))
		return (0);
	return (1);
}

int	ft_eating(t_philo *philo)
{
	if (!asign_forks(philo))
		return (0);
	set_state(philo, EAT);
	ft_output(philo->all, philo->id, G "is eating" RES);
	set_lst_time(philo);
	ft_usleep(philo->all->t_eat);
	set_nb_meal(philo);
	dropfork(philo, 'L');
	dropfork(philo, 'R');
	return (1);
}
