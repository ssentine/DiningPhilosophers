#include "philo_three.h"

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putnbr(long nb)
{
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar('-');
	}
	if (nb < 10)
		ft_putchar(nb + 48);
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

int	print_error(char *str)
{
	if (str)
		write (2, str, ft_strlen(str));
	return (1);
}

static void	print_str_msg(int type)
{
	if (type == FORK)
		ft_putstr("has taken a fork\n");
	else if (type == EAT)
		ft_putstr("is eating\n");
	else if (type == SLEEP)
		ft_putstr("is sleeping\n");
	else if (type == THINK)
		ft_putstr("is thinking\n");
	else if (type == DEAD)
		ft_putstr("died\n");
}

void	print_msg(long now, int philo, int type, t_simulation *simulation)
{
	sem_wait(simulation->msg);
	ft_putnbr(now - simulation->start);
	ft_putchar('\t');
	ft_putnbr(philo);
	ft_putchar('\t');
	print_str_msg(type);
	if (type != DEAD)
		sem_post(simulation->msg);
}
