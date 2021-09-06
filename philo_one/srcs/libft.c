#include "philo_one.h"

static const char	*pass_empty(const char *str)
{
	while (*str == 32 || *str == 0 || *str == 10 || *str == 11 || *str == 12
		|| *str == 13)
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				sign;

	result = 0;
	sign = 1;
	str = pass_empty(str);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > 9223372036854775807)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		result = result * 10 + (*str++ - '0');
	}
	return ((int)(result * sign));
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*result;

	size *= count;
	result = (unsigned char *)malloc(size);
	if (!result)
		return (NULL);
	while (size-- > 0)
		result[size] = '\0';
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s++ != '\0')
		size++;
	return (size);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
