/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:21:41 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/31 11:00:48 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_philos(void)
{
	sem_open("/death", O_CREAT, 0644, 0);
}

bool	check_death(t_ball *data)
{
	sem_wait(data->psem);
	if (get_status(data) != EAT && ft_gettime()
		- get_lst_time(data) > data->t_die)
	{
		set_state(data, DIED);
		return (false);
	}
	else if (get_status(data) == DIED)
	{
		sem_post(data->psem);
		return (true);
	}
	sem_post(data->psem);
	return (true);
}

bool	philo_died(void)
{
	sem_t	*death;

	death = sem_open("/death", 0, 0);
	if (death == SEM_FAILED)
		return (false);
	sem_close(death);
	return (true);
}

void	*check_state(void *var)
{
	t_ball	*data;

	data = (t_ball *)var;
	while (check_status(get_status(data)))
	{
		if (philo_died())
			return (set_state(data, END), NULL);
		if (!check_death(data))
		{
			sem_wait(data->psem);
			if (!check_death(data) && philo_died() == false)
			{
				set_state(data, DIED);
				kill_philos();
				printf(PER "%ld   %d" RES "    %s\n", ft_gettime()
					- data->start_t, data->philos.id, "died");
				sem_post(data->psem);
				break ;
			}
			sem_post(data->psem);
		}
		usleep(1000);
	}
	return (NULL);
}

// void *check_state(void *var)
// {
//     t_ball *data;

//     data = (t_ball *)var;
//     while (check_status(get_status(data)))
//     {
//         if (philo_died())
//             return (set_state(data, END), NULL);
//         if (!check_death(data))
//         {
//             sem_wait(data->psem);
//             if (get_status(data) == DIED && philo_died() == false)
//             {
//                 printf(PER "%ld   %d" RES "    %s\n", ft_gettime()
// - data->start_t, data->philos.id, "died");
//                 sem_post(data->psem);
//                 break ;
//             }
//             sem_post(data->psem);
//         }
//         usleep(1000);
//     }
//     return (NULL);
// }

// void *check_state(void *var)
// {
//     t_ball *data = (t_ball *)var;
//     bool death_notified = false;

//     while (1)
//     {
//         if (data->philos.status == DIED)
//         {
//             // Another philosopher has already died, exit
//             exit(0);
//         }

//         if (!check_death(data))
//         {
//             // Philosopher has died
//             // set_state(data, DIED);

//             if (!death_notified)
//             {
//                 // Print death message if not already notified
//                 ft_output(data, "died");
//                 death_notified = true;
//             }

//             // Notify other threads if necessary
//             // kill_philos(data);

//             // Exit thread
//             exit(0);
//         }

//         // Sleep for 1 ms
//         usleep(1000);
//     }
// }

// // void    *check_state(void *var)
// // {
// //     t_ball *data = (t_ball *)var;
// //     static int flag;

// //     while (1)
// //     {

// //         if (data->philos.status == DIED) {
// Check if philosopher is already dead
// //             exit(0);
// //         }
// //         long current_time = ft_gettime();
// //         long time_since_last_meal = current_time - data->philos.lst_time;
// //         if (time_since_last_meal > data->t_die)
// //         {
// //             data->philos.status = DIED;
// //             if (!flag)
// //             {
// //                 ft_output(data, "died");
// //                 flag = 1;
// //             }
// //             kill_philos(data);
// //             exit(0);
// //             // printf("hello\n");
// //         }
// //         usleep(1000); // Check every 1 ms
// //     }
// //     return (NULL);
// // }