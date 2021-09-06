#include "philo_two.h"

int	main(int ac, char **av)
{
	t_simulation	*simulation;
	int				i;

	i = 0;
	if (check_valid_arg(ac, av))
		return (1);
	simulation = (t_simulation *)ft_calloc(1, sizeof(t_simulation)
			* ft_atoi(av[1]));
	if (!simulation)
		return (print_error("Memory allocaton error.\n"));
	create_simulation(simulation, av, ac == 6);
	start_simulation(simulation, i);
	free(simulation);
	return (0);
}

void	create_simulation(t_simulation *simulation, char **av, int meal_times)
{
	int	i;

	i = -1;
	simulation[0].philo_nbr = ft_atoi(av[1]);
	simulation[0].dying_time = ft_atoi(av[2]);
	simulation[0].eating_time = ft_atoi(av[3]);
	simulation[0].sleeping_time = ft_atoi(av[4]);
	simulation[0].start = get_time();
	if (meal_times)
		simulation[0].meal_times = ft_atoi(av[5]);
	else
		simulation[0].meal_times = -1;
	while (++i < simulation[0].philo_nbr)
	{
		simulation[i].eating_time = simulation[0].eating_time;
		simulation[i].sleeping_time = simulation[0].sleeping_time;
		simulation[i].meal_times = simulation[0].meal_times;
		simulation[i].start = simulation[0].start;
		simulation[i].last_meal = simulation[0].start;
		simulation[i].philo = i + 1;
	}
}

static void	unlink_sems(void)
{
	sem_unlink("forks");
	sem_unlink("state");
	sem_unlink("msg");
}

static int	clean_all(sem_t *state)
{
	sem_wait(state);
	unlink_sems();
	return (0);
}

int	start_simulation(t_simulation *simulation, int i)
{
	sem_t			*state;
	sem_t			*forks;
	sem_t			*msg;
	pthread_t		tid;

	unlink_sems();
	forks = sem_open("forks", O_CREAT, 0666, simulation->philo_nbr);
	state = sem_open("state", O_CREAT, 0666, 1);
	msg = sem_open("msg", O_CREAT, 0666, 1);
	sem_wait(state);
	while (i < simulation[0].philo_nbr)
	{
		simulation[i].forks = forks;
		simulation[i].state = state;
		simulation[i].msg = msg;
		if (pthread_create(&tid, NULL, philo_life, &simulation[i++]) != 0)
			return (print_error("Thread init error\n") && clean_all(state));
		pthread_detach(tid);
	}
	if (pthread_create(&tid, NULL, monitor, &simulation[0]) != 0)
		return (clean_all(state));
	pthread_join(tid, NULL);
	return (clean_all(state));
}
