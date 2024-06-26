/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:30:33 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/31 10:35:19 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_state	get_status(t_ball *data)
{
	t_state	res;

	sem_wait(data->philos.semphilo);
	res = data->philos.status;
	sem_post(data->philos.semphilo);
	return (res);
}

long	get_lst_time(t_ball *data)
{
	long	res;

	sem_wait(data->philos.semphilo);
	res = data->philos.lst_time;
	sem_post(data->philos.semphilo);
	return (res);
}
