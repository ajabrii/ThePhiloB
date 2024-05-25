/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:21:41 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/25 18:29:02 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

void kill_philos(t_ball *data)
{
    set_state(data, DIED);
}

bool check_death(t_ball *data)
{
    if (get_status(data) != EAT
            && ft_gettime() - get_lst_time(data) > data->t_die)
    {
        set_state(data, DIED);
        return (false);
    }
    return (true);
}

bool	someone_died(void)
{
	sem_t	*death;

	death = sem_open("/death", AT_EACCESS, 0);
	if (death == SEM_FAILED)
		return (false);
	sem_close(death);
	return (true);
}

void	let_others_know(void)
{
	sem_open("/death", O_CREAT, 0644, 0);
}

void	*check_state(void *var)
{
	t_ball	*data;

	data = (t_ball *)var;
	while (check_status(get_status(data)))
	{
        if (someone_died())
            return (set_state(data, END), NULL);
		if (!check_death(data))
		{
			sem_wait(data->psem);
			if (!check_death(data) && someone_died() == false)
			{
				set_state(data, DIED);
				let_others_know();
                printf(PER "%ld   %d" RES "    %s\n", ft_gettime() - data->start_t,
                                    data->philos.id, "died");
				sem_post(data->psem);
                break;
            }
			sem_post(data->psem);
		}
		usleep(1000);
	}
    return (NULL);
}

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

// //         if (data->philos.status == DIED) { // Check if philosopher is already dead
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
// //     return NULL;
// // }