#include "philo_one.h"

int	main(int ac, char **av)
{
	t_simulation	*simulation;

	if (check_valid_arg(ac, av))
		return (1);
	simulation = (t_simulation *)ft_calloc(1, sizeof(t_simulation)
			* ft_atoi(av[1]));
	if (!simulation)
		return (print_error("Memory allocaton error.\n"));
	create_simulation(simulation, av, ac == 6);
	start_simulation(simulation);
	free_simulation(simulation);
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
		pthread_mutex_init(&simulation[i].fork, NULL);
		if (i != 0)
			simulation[i].prev = &simulation[i -1].fork;
		simulation[i].eating_time = simulation[0].eating_time;
		simulation[i].sleeping_time = simulation[0].sleeping_time;
		simulation[i].meal_times = simulation[0].meal_times;
		simulation[i].start = simulation[0].start;
		simulation[i].last_meal = simulation[0].start;
		simulation[i].philo = i + 1;
	}
	simulation[0].prev = &simulation[simulation[0].philo_nbr - 1].fork;
}

static int	init_mutexes(pthread_mutex_t *state, pthread_mutex_t *msg)
{
	if (pthread_mutex_init(state, NULL) != 0)
		return (1);
	if (pthread_mutex_init(msg, NULL) != 0)
		return (1);
	return (0);
}

int	start_simulation(t_simulation *simulation)
{
	pthread_mutex_t	state;
	pthread_mutex_t	msg;
	pthread_t		tid;
	pthread_t		tid2;
	int				i;

	i = 0;
	if (init_mutexes(&state, &msg))
		return (print_error("Mutex init error\n"));
	pthread_mutex_lock(&state);
	while (i < simulation[0].philo_nbr)
	{
		simulation[i].state = &state;
		simulation[i].msg = &msg;
		if (pthread_create(&tid, NULL, philo_life, &simulation[i++]) != 0)
			return (print_error("Thread init error\n"));
		pthread_detach(tid);
	}
	if (pthread_create(&tid2, NULL, monitor, &simulation[0]) != 0)
		return (1);
	pthread_join(tid2, NULL);
	pthread_mutex_lock(&state);
	pthread_mutex_destroy(&state);
	pthread_mutex_destroy(&msg);
	return (0);
}

void	free_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation[0].philo_nbr)
		pthread_mutex_destroy(&simulation[i++].fork);
	free(simulation);
}
