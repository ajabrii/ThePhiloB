#include "philo_bonus.h"

int	count_size(char **av)
{
	int	size;

	size = 0;
	if (!av)
		return (0);
	while (av[size])
		size++;
	return (size);
}

char	**retunr_args(t_ball *ps)
{
	int		i;
	char	*palestine;
	char	*arg;
	char	**args;

	if (!ps->av[1])
		return (NULL);
	arg = ft_strdup(ps->av[1]);
	if (!arg[0])
		ft_error("Error");
	i = 2;
	while (i < ps->ac)
	{
		if (!ps->av[i][0])
			ft_error("Error");
		palestine = ft_strjoin(arg, " ");
		free(arg);
		arg = ft_strjoin(palestine, ps->av[i]);
		free(palestine);
		i++;
	}
	args = ft_split(arg, ' ');
	return (free(arg), args);
}

int	check_nbr(t_ball *ps)
{
	int	i;
	int	p;

	i = 0;
	while (i < ps->size)
	{
		p = 0;
		if (ps->args[i][p] == '-' || ps->args[i][p] == '+')
			p++;
		if (!ps->args[i][p])
			return (0);
		while (ps->args[i][p])
		{
			if (!ft_isdigit(ps->args[i][p]))
				return (0);
			p++;
		}
		i++;
	}
	return (1);
}

void	*ft_malloc(unsigned int size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		return (NULL);
	return (res);
}

long	ft_gettime(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		ft_error("gettimeofday() Error");
	return ((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
}

void	ft_usleep(long nb)
{
	long	time;

	time = ft_gettime();
	while ((ft_gettime() - time) < nb)
	{
		usleep(500);
	}
}

bool	ft_output(t_ball *data, char *msg)
{
	sem_post(data->psem);
	sem_wait(data->psem);
	if (philo_died())
	{
		sem_post(data->psem);
		return (false);
	}
	printf(PER "%ld   %d" RES "    %s\n", ft_gettime() - data->start_t,
		data->philos.id, msg);
	sem_post(data->psem);
	return (true);
}

bool	set_philosopher(t_ball *data, int phid)
{
	data->semid = ft_strjoin("/philo_", ft_itoa(phid));
	if (!data->semid)
		return (false);
	sem_unlink(data->semid);
	data->philos.semphilo = sem_open(data->semid, O_CREAT, 0644, 1);
	if (data->philos.semphilo == SEM_FAILED)
	{
		free(data->semid);
		ft_error("Error in data->philos.semphilo");
	}
	sem_unlink(data->semid);
	free(data->semid);
	data->philos.id = phid;
	set_lst_time(data);
	return (true);
}

void	set_lst_time(t_ball *data)
{
	sem_wait(data->philos.semphilo);
	data->philos.lst_time = ft_gettime();
	sem_post(data->philos.semphilo);
}

void	set_state(t_ball *data, t_state state)
{
	sem_wait(data->philos.semphilo);
	data->philos.status = state;
	sem_post(data->philos.semphilo);
}

bool	thinking(t_ball *data)
{
	set_state(data, THINK);
	if (!ft_output(data, ORG "is thinking" RES))
		return (false);
	return (true);
}

bool	sleeping(t_ball *data)
{
	set_state(data, SLEEP);
	if (!ft_output(data, PER "is sleeping" RES))
		return (false);
	ft_usleep(data->t_sleep);
	return (true);
}

void	routine(t_ball *data, int id)
{
	if (set_philosopher(data, id) == false)
		ft_error("Error in set_philosophers");
	if (data->philos.id % 2 == 0)
		ft_usleep(data->t_eat - 10);
	if (pthread_create(&data->monitor1, NULL, &check_state, data))
		ft_error("Error in pthread create");
	while (1)
	{
		if (!eating(data) || !check_status(get_status(data))
			|| !check_status(get_status(data)))
			break ;
		if (!sleeping(data) || !check_status(get_status(data))
			|| !check_status(get_status(data)))
			break ;
		if (!thinking(data) || !check_status(get_status(data))
			|| !check_status(get_status(data)))
			break ;
	}
	if (!pthread_join(data->monitor1, NULL))
		exit(0);
	sem_close(data->philos.semphilo);
}

bool	check_status(t_state state)
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

void	set_start_t(t_ball *data)
{
	sem_wait(data->psem);
	data->start_t = ft_gettime();
	sem_post(data->psem);
}

int	process_f(t_ball *data)
{
	int	pid;
	int	index;

	index = 0;
	set_start_t(data);
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


void	drop_forks(t_ball *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
}

static void	onephilo(t_ball *data)
{
	sem_wait(data->forks);
	ft_output(data, CY "has taken a fork" RES);
	ft_usleep(data->t_die);
	ft_output(data, RED "died" RES);
	set_state(data, DIED);
	sem_post(data->forks);
	exit(0);
}

bool	is_full(t_ball *data)
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

bool	eating(t_ball *data)
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

void	semaphore_init(t_ball *data)
{
	sem_unlink("/death");
	sem_unlink("/sem_forks");
	sem_unlink("/psem");
	data->forks = sem_open("/sem_forks", O_CREAT, 0644, data->nphilo);
	if (data->forks == SEM_FAILED)
		ft_error("Error in data->forks");
	data->psem = sem_open("/psem", O_CREAT, 0644, 1);
	if (data->psem == SEM_FAILED)
		ft_error("Error in data->psem");
}

static void	get_init(t_ball *data)
{
	data->nphilo = ft_atol(data->args[0], 0);
	data->t_die = ft_atol(data->args[1], 0);
	data->t_eat = ft_atol(data->args[2], 0);
	data->t_sleep = ft_atol(data->args[3], 0);
	if (!data->args[4])
		data->nt_eat = -42;
	else
		data->nt_eat = ft_atol(data->args[4], -1);
	data->philos.all = data;
	data->philos.nb_meal = 0;
	data->philos.lst_time = QUIT;
	semaphore_init(data);
}

static int	parsing(int argc, char **argv, t_ball *data)
{
	int	i;

	i = -1;
	data->av = argv;
	data->ac = argc;
	data->args = retunr_args(data);
	data->size = count_size(data->args);
	if (data->size < 4 || data->size > 5)
		return (0);
	if (!check_nbr(data))
		return (0);
	get_init(data);
	while (data->args[++i])
	{
		free(data->args[i]);
	}
	free(data->args);
	return (1);
}

int	main(int argc, char **argv)
{
	t_ball	all;

	if (!parsing(argc, argv, &all))
	{
		ft_error("Error");
		return (1);
	}
	else
	{
		process_f(&all);
		sem_close(all.forks);
		sem_close(all.psem);
	}
	return (0);
}
