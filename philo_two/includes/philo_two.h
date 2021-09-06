#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# define FORK		1
# define EAT		2
# define SLEEP		3
# define THINK		4
# define DEAD		5

typedef struct s_simulation
{
	sem_t			*forks;
	sem_t			*state;
	sem_t			*msg;
	int				philo_nbr;
	long int		dying_time;
	long int		eating_time;
	long int		sleeping_time;
	long int		start;
	long			last_meal;
	int				already_ate;
	int				meal_times;
	int				philo;
	int				full_philo;
}					t_simulation;

//MAIN
void	create_simulation(t_simulation *simulation, char **av, int meal_times);
int		start_simulation(t_simulation *simulation, int i);
void	free_simulation(t_simulation *simulation);

//PHILO_LIFE
void	take_forks(t_simulation *simulation);
void	put_forks(t_simulation *simulation);
void	*philo_life(void *ptr);

//MONITOR
void	*monitor(void *ptr);

//LIBFT
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);

//PRINT_MSG
int		print_error(char *str);
void	print_msg(long time, int philo, int type, t_simulation *simulation);
void	ft_putnbr(long nb);
void	ft_putstr(char *s);
void	ft_putchar(char c);

//UTILS
time_t	get_time(void);
void	ft_usleep(long int interval_ms);
int		check_valid_arg(int ac, char **av);

#endif 
