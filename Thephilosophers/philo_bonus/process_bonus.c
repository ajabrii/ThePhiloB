/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:38:51 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/25 19:09:39 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"


bool    check_status(t_state state)
{
    if (state == DIED)
        return (false);
    else if (state == FULL)
        return (false);
    else if (state == END)
        return (false);
    else
        return (true);
}
bool    thinking(t_ball *data)
{
    set_state(data, THINK);
    if (!ft_output(data, ORG"is thinking"RES))
        return (false);
    return (true);
}

bool    sleeping(t_ball *data)
{
    set_state(data, SLEEP);
    if (!ft_output(data, PER"is sleeping"RES))
        return (false);
    ft_usleep(data->t_sleep);
    return (true);
}
//useless
void set_start_t(t_ball *data)
{
    sem_wait(data->philos.semphilo);
    data->start_t = ft_gettime();
    sem_post(data->philos.semphilo);
}

void    routine(t_ball *data, int id)
{
    if (set_philosopher(data, id) == false)
        ft_error("Error in set_philosophers");
    if (data->philos.id % 2 == 0)
        ft_usleep(data->t_eat);
    if (data->nphilo % 2 != 0)
    {
        if (data->philos.id == data->nphilo && data->nphilo > 1)
            ft_usleep(data->t_eat);
    }
    if (pthread_create(&data->monitor1,NULL, &check_state, data))
        ft_error("Error in pthread create");
    while (1)
    {
        if (!eating(data) || !check_status(get_status(data)))
        {
            // printf("eat return false\n");
            break;
        }
        if (!sleeping(data) || !check_status(get_status(data)))
        {
            break;
        }
        if (!thinking(data) || !check_status(get_status(data)))
        {
            // printf("think return false\n");
            break;
        }
    }
    if (!pthread_join(data->monitor1, NULL))
        exit(0);
    sem_close(data->philos.semphilo);
}
int     process_f(t_ball *data)
{
    int pid;
    int index;

    index = 0;
    data->start_t = ft_gettime();
    while (index++ < data->nphilo)
    {
        pid = fork();
        if (pid == -1)
            ft_error("Error in fork");
        if (!pid)
            routine(data, index);
    }
   while (waitpid(-1, NULL, 0) > 0)
       ;
   return (1);
}
