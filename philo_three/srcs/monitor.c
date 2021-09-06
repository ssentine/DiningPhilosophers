#include "philo_three.h"

static void	*philo_is_dead(long int now, t_simulation *simulation)
{
	print_msg(now, simulation->philo, DEAD, simulation);
	ft_putstr("-----End of simulation------\n");
	exit(1);
	return ((void *)1);
}

void	*monitor(void *ptr)
{
	t_simulation	*simulation;
	long int		now;

	simulation = (t_simulation *)ptr;
	while (21)
	{
		now = get_time();
		if (now - simulation->last_meal > simulation->dying_time)
			return (philo_is_dead(now, simulation));
		ft_usleep(1);
	}
	return (NULL);
}
