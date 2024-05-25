/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:50:52 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/05 14:29:47 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	check_death(t_philo *philo)
{
	bool	result;

	result = false;
	if (ft_gettime() - get_lst_time(philo) > philo->all->t_die
		&& get_state(philo) != EAT)
	{
		set_state(philo, DIED);
		result = true;
	}
	return (result);
}

void	kill_philos(t_all *data)
{
	int	i;

	i = -1;
	while (++i < data->nphilo)
	{
		set_state(&data->philos[i], DIED);
	}
}

void	*check_state(void *info)
{
	int		i;
	t_philo	*philo;
	t_all	*data;

	data = (t_all *)info;
	philo = data->philos;
	i = -1;
	while (++i < data->nphilo && !get_simulation(data))
	{
		if (check_death(&philo[i]) && !get_simulation(data))
		{
			ft_output(data, philo[i].id, RED "died" RES);
			set_simulation(data, true);
			kill_philos(data);
			break ;
		}
		if (i == data->nphilo - 1)
			i = -1;
		usleep(1000);
	}
	return (NULL);
}

bool	philo_is_full(t_philo *philo)
{
	bool	res;

	res = false;
	if (get_nb_meal(philo) >= philo->all->nt_eat)
		res = true;
	return (res);
}

void	*ft_isfull(void *info)
{
	int		i;
	t_all	*data;

	data = (t_all *)info;
	i = -1;
	while (++i < data->nphilo && !get_simulation(data))
	{
		usleep(1000);
		if (!philo_is_full(&data->philos[i]))
			i = -1;
	}
	if (!get_simulation(data))
	{
		set_simulation(data, true);
		kill_philos(data);
	}
	return (NULL);
}
