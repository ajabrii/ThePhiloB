/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:48:42 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/31 11:12:32 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	thinking(t_ball *data)
{
	set_state(data, THINK);
	if (!ft_output(data, ORG "is thinking" RES))
		return (false);
	return (true);
}

bool	sleeping(t_ball *data)
{
	set_state(data, SLEEP);
	if (!ft_output(data, PER "is sleeping" RES))
		return (false);
	ft_usleep(data->t_sleep);
	return (true);
}

void	routine(t_ball *data, int id)
{
	if (set_philosopher(data, id) == false)
		ft_error("Error in set_philosophers");
	if (data->philos.id % 2 == 0)
		ft_usleep(data->t_eat - 10);
	if (pthread_create(&data->monitor1, NULL, &check_state, data))
		ft_error("Error in pthread create");
	while (1)
	{
		if (!eating(data) || !check_status(get_status(data))
			|| !check_status(get_status(data)))
			break ;
		if (!sleeping(data) || !check_status(get_status(data))
			|| !check_status(get_status(data)))
			break ;
		if (!thinking(data) || !check_status(get_status(data))
			|| !check_status(get_status(data)))
			break ;
	}
	if (!pthread_join(data->monitor1, NULL))
		exit(0);
	sem_close(data->philos.semphilo);
}
