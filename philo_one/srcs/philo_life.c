#include "philo_one.h"

void	take_forks(t_simulation *simulation)
{
	if (simulation->philo % 2)
	{
		pthread_mutex_lock(&simulation->fork);
		print_msg(get_time(), simulation->philo, FORK, simulation);
		pthread_mutex_lock(simulation->prev);
		print_msg(get_time(), simulation->philo, FORK, simulation);
	}
	else
	{
		pthread_mutex_lock(simulation->prev);
		print_msg(get_time(), simulation->philo, FORK, simulation);
		pthread_mutex_lock(&simulation->fork);
		print_msg(get_time(), simulation->philo, FORK, simulation);
	}
}

void	put_forks(t_simulation *simulation)
{
	if (simulation->philo % 2)
	{
		pthread_mutex_unlock(simulation->prev);
		pthread_mutex_unlock(&simulation->fork);
	}
	else
	{
		pthread_mutex_unlock(&simulation->fork);
		pthread_mutex_unlock(simulation->prev);
	}
}

void	*philo_life(void *ptr)
{
	t_simulation	*simulation;

	simulation = (t_simulation *)ptr;
	if ((simulation->philo % 2) == 0)
		ft_usleep(1);
	while (21)
	{
		take_forks(simulation);
		simulation->last_meal = get_time();
		print_msg(get_time(), simulation->philo, EAT, simulation);
		ft_usleep(simulation->eating_time);
		put_forks(simulation);
		simulation->already_ate++;
		if (simulation->already_ate == simulation->meal_times)
			simulation->full_philo = 1;
		print_msg(get_time(), simulation->philo, SLEEP, simulation);
		ft_usleep(simulation->sleeping_time);
		print_msg(get_time(), simulation->philo, THINK, simulation);
	}
	return (NULL);
}
