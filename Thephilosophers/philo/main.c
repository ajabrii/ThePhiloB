/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:59:07 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/19 12:18:55 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	init_args(t_all *data)
{
	data->nphilo = ft_atol(data->args[0], 0);
	if (data->nphilo == -1337)
		return (0);
	data->t_die = ft_atol(data->args[1], 0);
	if (data->t_die == -1337)
		return (0);
	data->t_eat = ft_atol(data->args[2], 0);
	if (data->t_eat == -1337)
		return (0);
	data->t_sleep = ft_atol(data->args[3], 0);
	if (data->t_sleep == -1337)
		return (0);
	if (!data->args[4])
		data->nt_eat = -42;
	else
	{
		data->nt_eat = ft_atol(data->args[4], -1);
		if (data->nt_eat == -1337)
			return (0);
	}
	return (1);
}

static int	parsing(int argc, char **argv, t_all *data)
{
	int	i;

	i = -1;
	data->av = argv;
	data->ac = argc;
	if (data->ac < 5 || data->ac > 6)
		return (0);
	data->args = retunr_args(data);
	data->size = count_size(data->args);
	if (!check_nbr(data))
		return (0);
	else if (!init_args(data))
		return (0);
	while (data->args[++i])
		free(data->args[i]);
	free(data->args);
	return (1);
}

static void	get_init(t_all *data)
{
	data->simulation = false;
	pthread_mutex_init(&data->m_start_time, NULL);
	pthread_mutex_init(&data->m_t_die, NULL);
	pthread_mutex_init(&data->m_simulation, NULL);
	pthread_mutex_init(&data->m_t_eat, NULL);
	pthread_mutex_init(&data->m_t_sleep, NULL);
	pthread_mutex_init(&data->pmtx, NULL);
	data->philos = ft_malloc(sizeof(t_philo) * data->nphilo);
	data->forks = ft_malloc(sizeof(pthread_mutex_t) * data->nphilo);
	fork_init(data);
	philosophers_init(data);
	ft_threads(data);
	ft_join(data);
	ft_free_all(data);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (!parsing(argc, argv, &all))
	{
		ft_error("Error");
		return (1);
	}
	else
	{
		get_init(&all);
		// system("leaks philo");
	}
	return (0);
}
