/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:41:45 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/05 14:30:10 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fork_init(t_all *data)
{
	int	i;

	i = -1;
	while (++i < data->nphilo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return ;
	}
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[i - 1];
	i = 0;
	while (++i < data->nphilo)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
	}
}

void	philosophers_init(t_all *data)
{
	int	i;

	i = -1;
	while (++i < data->nphilo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_meal = 0;
		data->philos[i].all = data;
		data->philos[i].status = QUIT;
		pthread_mutex_init(&data->philos[i].state, NULL);
		pthread_mutex_init(&data->philos[i].m_nb_meal, NULL);
		pthread_mutex_init(&data->philos[i].m_lst_time, NULL);
	}
}

void	ft_threads(t_all *data)
{
	int	i;

	i = -1;
	data->start_time = ft_gettime();
	while (++i < data->nphilo)
		pthread_create(&data->philos[i].philo_thread, NULL, &routine,
			&data->philos[i]);
	pthread_create(&data->motnitor1, NULL, &check_state, data);
	if (data->nt_eat > 0)
		pthread_create(&data->motnitor2, NULL, &ft_isfull, data);
}

void	ft_join(t_all *data)
{
	int	i;

	i = -1;
	while (++i < data->nphilo)
		pthread_join(data->philos[i].philo_thread, NULL);
	pthread_join(data->motnitor1, NULL);
	if (data->nt_eat > 0)
		pthread_join(data->motnitor2, NULL);
}
