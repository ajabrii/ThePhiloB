/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:21:06 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/25 19:05:48 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	drop_forks(t_ball *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
}

// int	take_1fork(t_ball *data)
// {
//     sem_wait(data->forks);
//     if (!ft_output(data, CY "has taken a fork" RES))
//         return (0);
//     return (1);
// }

// int	take_2fork(t_ball *data)
// {
// 	sem_wait(data->forks);
//     if (!ft_output(data, CY "has taken a fork" RES))
//         return (0);
//     return (1);
// }

// int	asign_forks(t_ball *data)
// {
//     if (!take_1fork(data))
// 		return (0);
// 	if (!take_2fork(data))
//         return (0);
// 	return (1);
// }
static  void    onephilo(t_ball *data)
{
        sem_wait(data->forks);
        ft_output(data, CY "has taken a fork" RES);
        ft_usleep(data->t_die);
        ft_output(data, RED "died" RES);
        set_state(data, DIED);
        sem_post(data->forks);
        exit(0);
}

bool is_full(t_ball *data)
{
    if (data->nt_eat <= 0)
        return (false);
    if (data->nt_eat <= data->philos.nb_meal)
    {
        set_state(data, FULL);
        return (true);
    }
    return (false);
}

int	asign_forks(t_ball *data)
{
	sem_wait(data->forks);
	if (!ft_output(data, CY "has taken a fork" RES))
	{
        sem_post(data->forks);
        return (1);
	}
	if (data->nphilo == 1)
		return (1);
	sem_wait(data->forks);
	if (!check_status(get_status(data)))
	{
		drop_forks(data);
		return (1);
	}
	if (!ft_output(data, CY "has taken a fork" RES))
	{
		drop_forks(data);
		return (1);
	}
	return (0);
}
bool eating(t_ball *data)
{
    if (data->nphilo == 1)
        onephilo(data);
    else if (asign_forks(data))
        return (false);
    set_lst_time(data);
    set_state(data, EAT);
    if (!ft_output(data, G "is eating" RES))
    {
        drop_forks(data);
        return (false);
    }
    data->philos.nb_meal++;
    ft_usleep(data->t_eat);
    drop_forks(data);
    if (is_full(data))
        return (false);
    return (true);
}

// int	asign_forks(t_philo *philo)
// {
// 	if (philo->all->nphilo == 1)
// 	{
// 		take_lfork(philo);
// 		ft_usleep(philo->all->t_die);
// 		return (0);
// 	}
// 	if (!take_lfork(philo))
// 		return (0);
// 	if (!take_rfork(philo))
// 		return (0);
// 	return (1);
// }

