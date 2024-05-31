/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:34:22 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/31 11:15:52 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	set_philosopher(t_ball *data, int phid)
{
	data->semid = ft_strjoin("/philo_", ft_itoa(phid));
	if (!data->semid)
		return (false);
	sem_unlink(data->semid);
	data->philos.semphilo = sem_open(data->semid, O_CREAT, 0644, 1);
	if (data->philos.semphilo == SEM_FAILED)
	{
		free(data->semid);
		ft_error("Error in data->philos.semphilo");
	}
	sem_unlink(data->semid);
	free(data->semid);
	data->philos.id = phid;
	set_lst_time(data);
	return (true);
}

void	set_lst_time(t_ball *data)
{
	sem_wait(data->philos.semphilo);
	data->philos.lst_time = ft_gettime();
	sem_post(data->philos.semphilo);
}

void	set_state(t_ball *data, t_state state)
{
	sem_wait(data->philos.semphilo);
	data->philos.status = state;
	sem_post(data->philos.semphilo);
}
