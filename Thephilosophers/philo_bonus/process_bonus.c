/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:38:51 by ajabri            #+#    #+#             */
/*   Updated: 2024/05/31 11:30:12 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
