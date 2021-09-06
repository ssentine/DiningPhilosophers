#include "philo_three.h"

long int	get_time(void)
{
	static struct timeval	time;
	time_t					result;

	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (result);
}

void	ft_usleep(long int interval_ms)
{
	long int	now_ms;
	long int	stop_ms;

	stop_ms = get_time() + interval_ms;
	now_ms = get_time();
	while (now_ms < stop_ms)
	{
		usleep(50);
		now_ms = get_time();
	}
}

int	check_valid_arg(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	if (ac != 5 && ac != 6)
		return (print_error("Number of arguments should be 5 or 6.\n"));
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (print_error("Not only numbers.\n"));
		}
	}
	if (ft_atoi(av[1]) == 0)
		return (print_error("Numbers of philos should be more than 0.\n"));
	return (0);
}

void	unlink_all(void)
{
	sem_unlink("forks");
	sem_unlink("msg");
}
