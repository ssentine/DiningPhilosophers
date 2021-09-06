#include "philo_three.h"

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
	start_simulation(simulation, -1);
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
		simulation[i].philo_nbr = simulation[0].philo_nbr;
		simulation[i].dying_time = simulation[0].dying_time;
		simulation[i].eating_time = simulation[0].eating_time;
		simulation[i].sleeping_time = simulation[0].sleeping_time;
		simulation[i].meal_times = simulation[0].meal_times;
		simulation[i].start = simulation[0].start;
		simulation[i].last_meal = simulation[0].start;
		simulation[i].philo = i + 1;
	}
}

int	create_threads(t_simulation *simulation)
{
	pthread_t		tid;
	pthread_t		tid2;

	if (pthread_create(&tid, NULL, philo_life, simulation) != 0)
		return (print_error("Thread init error\n"));
	pthread_detach(tid);
	if (pthread_create(&tid2, NULL, monitor, simulation) != 0)
		return (print_error("Thread init error\n"));
	pthread_join(tid2, NULL);
	return (0);
}

void	waitpid_processes(t_simulation *simulation, pid_t *pids)
{
	int		status;
	int		i;

	i = 0;
	waitpid(0, &status, WUNTRACED);
	if (status == 256)
	{
		while (i < simulation->philo_nbr)
			kill(pids[i++], 1);
	}
	else if (status == 512)
	{
		simulation->full_philo++;
		if (simulation->full_philo == simulation->philo_nbr)
			ft_putstr("-----Everybody has eaten------\n");
		else
			waitpid_processes(simulation, pids);
	}
}

int	start_simulation(t_simulation *simulation, int i)
{
	sem_t			*forks;
	sem_t			*msg;
	pid_t			*pids;

	pids = (pid_t *)ft_calloc(1, simulation->philo_nbr * sizeof(pid_t));
	unlink_all();
	forks = sem_open("forks", O_CREAT, 0666, simulation->philo_nbr);
	msg = sem_open("msg", O_CREAT, 0666, 1);
	while (++i < simulation[0].philo_nbr)
	{
		simulation[i].forks = forks;
		simulation[i].msg = msg;
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (create_threads(&simulation[i]))
				break ;
		}
	}
	waitpid_processes(simulation, pids);
	unlink_all();
	free(pids);
	return (0);
}
