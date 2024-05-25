/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:55:36 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/11 10:01:30 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "utils/utils.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_all
{
	int					ac;
	char				**av;
	int					size;
	char				**args;
	long				nphilo;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				nt_eat;
	long				start_time;
	bool				simulation;
	t_philo				*philos;
	pthread_t			motnitor1;
	pthread_t			motnitor2;
	pthread_mutex_t		pmtx;
	pthread_mutex_t		m_simulation;
	pthread_mutex_t		m_t_die;
	pthread_mutex_t		m_t_eat;
	pthread_mutex_t		m_t_sleep;
	pthread_mutex_t		m_start_time;
	pthread_mutex_t		*forks;

}						t_all;

typedef enum s_state
{
	EAT,
	SLEEP,
	THINK,
	DIED,
	QUIT
}						t_state;

struct					s_philo
{
	int					id;
	int					nb_meal;
	long				lst_time;
	t_all				*all;
	pthread_t			philo_thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	t_state				status;
	pthread_mutex_t		state;
	pthread_mutex_t		m_nb_meal;
	pthread_mutex_t		m_lst_time;
};
/* <tools.c> */
int						count_size(char **av);
char					**retunr_args(t_all *ps);
int						check_nbr(t_all *ps);
void					*ft_malloc(unsigned int size);
/* </tools.c> */

/* <Philosophers.c> */
void					philosophers_init(t_all *data);
void					fork_init(t_all *data);
void					ft_threads(t_all *data);
void					ft_join(t_all *data);
/* </Philosophers.c> */

/* <routine.c> */
void					*routine(void *data);
void					*check_state(void *data);
void					*ft_isfull(void *data);
/* </routine.c> */

/* <time.c> */
long					ft_gettime(void);
void					ft_usleep(long nb);
void					ft_output(t_all *data, int id, char *msg);
/* </time.c> */

/* <getters.c> */
long					get_lst_time(t_philo *philo);
t_state					get_state(t_philo *philo);
long					get_start_time(t_all *data);
bool					get_simulation(t_all *data);
long					get_nb_meal(t_philo *philo);
/* </getters.c> */

/* <setters.c> */
void					set_simulation(t_all *data, bool value);
void					set_nb_meal(t_philo *philo);
void					set_state(t_philo *philo, t_state status);
void					set_lst_time(t_philo *philo);
/* </setters.c> */

/* <eating.c> */
int						ft_eating(t_philo *philo);
/* </eating.c> */

/* <cleanup.c> */
void					ft_free_all(t_all *data);
/* </cleanup.c> */
#endif