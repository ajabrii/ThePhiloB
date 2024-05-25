/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 09:13:04 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/25 18:13:26 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "utils_bonus/utils.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>

typedef struct s_all_bonus t_ball;
typedef enum s_state
{
    EAT,
    SLEEP,
    THINK,
    DIED,
    FULL,
    END,
    QUIT
} t_state;

typedef struct s_philo_bonus
{
    int					id;
	int					nb_meal;
	long				lst_time;
	t_ball				*all;
    sem_t               *semphilo;
    t_state             status;
}                       t_bphilo;

struct s_all_bonus
{
    int					ac;
	char				**av;
	int					size;
	char				**args;
    char                *semid;
    long                nphilo;
    long				t_die;
	long				t_eat;
	long				t_sleep;
	long				nt_eat;
    long                start_t;
    sem_t               *forks;
    sem_t               *psem;
    t_bphilo            philos;
    pthread_t           monitor1;
};



/* <tools_bonus.c> */
char    **retunr_args(t_ball *ps);
int     count_size(char **av);
int     check_nbr(t_ball *ps);
void    *ft_malloc(unsigned int size);
/* </tools_bonus.c> */

/* <time_bonus.c> */
long    ft_gettime(void);
void    ft_usleep(long nb);
bool    ft_output(t_ball *data, char *msg);
/* </time_bonus.c> */

/* <getters_bonus.c> */
t_state get_status(t_ball *data);
long    get_lst_time(t_ball *data);
/* </getters_bonus.c> */

/* <setters_bonus.c> */
bool    set_philosopher(t_ball *data, int phid);
void    set_lst_time(t_ball *data);
void    set_state(t_ball *data, t_state state);
/* </setters_bonus.c> */

/* <process_bonus.c> */
int     process_f(t_ball *data);
bool    check_status(t_state state);
/* </process_bonus.c> */

/* <eating_bonus.c> */
bool    eating(t_ball *data);
/* </eating_bonus.c> */

/* <monitor_bonus.c> */
void    *check_state(void *var);
bool someone_died(void);
/* </monitor_bonus.c> */

#endif