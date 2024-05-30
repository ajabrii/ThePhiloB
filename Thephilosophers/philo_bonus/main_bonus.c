/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 09:42:38 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/30 10:14:17 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

// try to fix the ./philo_bonus 4 310 200 100 one philo should die(the output is not correct)
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
	// sem_unlink("/sem_forks");
	// sem_unlink("/psem");
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
	data->flag = 0;
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
		// system("leaks philo_bonus");
    }
	return (0);
}
