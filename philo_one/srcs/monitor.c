#include "philo_one.h"

static void	*everybody_has_eaten(t_simulation *simulation)
{
	pthread_mutex_lock(simulation->msg);
	ft_putstr("-----Everybody has eaten------\n");
	pthread_mutex_unlock(simulation->state);
	return ((void *)1);
}

static void	*philo_is_dead(long int now, t_simulation *simulation, int i)
{
	print_msg(now, simulation[i].philo, DEAD, simulation);
	pthread_mutex_unlock(simulation->state);
	ft_putstr("-----End of simulation------\n");
	return ((void *)1);
}

void	*monitor(void *ptr)
{
	t_simulation	*simulation;
	int				full_philos;
	long int		now;
	int				i;

	i = -1;
	simulation = (t_simulation *)ptr;
	while (21)
	{
		i = -1;
		now = get_time();
		full_philos = 0;
		while (++i < simulation->philo_nbr)
		{
			if (simulation[i].full_philo == 1)
				full_philos++;
			if (now - simulation[i].last_meal > simulation[0].dying_time)
				return (philo_is_dead(now, simulation, i));
		}
		if (full_philos == simulation->philo_nbr)
			return (everybody_has_eaten(simulation));
	}
	return (NULL);
}
