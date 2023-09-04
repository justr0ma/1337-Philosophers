/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halaqoh <halaqoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:02:50 by halaqoh           #+#    #+#             */
/*   Updated: 2022/06/04 23:03:15 by halaqoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	signe(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		j;
	long	n;
	long	c;

	i = 0;
	j = 1;
	n = 0;
	c = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	j = signe(str[i]);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + str[i] - '0';
		if (n < c && j == -1)
			return (0);
		if (n < c)
			return (-1);
		c = n;
		i++;
	}
	return (j * n);
}

void	init_p(t_filozof **p, char **argv, int argc)
{
	struct timeval	current_time;

	*p = malloc(sizeof(t_filozof));
	(*p)->philo = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	(*p)->fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	(*p)->l_eat = malloc(sizeof(size_t) * ft_atoi(argv[1]));
	(*p)->is_eating = malloc(sizeof(size_t) * ft_atoi(argv[1]));
	(*p)->is_alleat = malloc(sizeof(size_t) * ft_atoi(argv[1]));
	(*p)->nbr_philo = ft_atoi(argv[1]);
	(*p)->tdie = ft_atoi(argv[2]);
	(*p)->teat = ft_atoi(argv[3]);
	(*p)->tslep = ft_atoi(argv[4]);
	gettimeofday(&current_time, NULL);
	(*p)->t0 = current_time.tv_usec;
	(*p)->nbr_to_eat = -1;
	if (argc == 6)
		(*p)->nbr_to_eat = ft_atoi(argv[5]);
}

long	tim(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000);
}

int	is_mat(t_filozof *p, size_t	tn)
{
	size_t	i;

	i = 0;
	while (p->vv < p->nbr_philo)
	{
		pthread_create(&p->philo[p->vv], NULL, (void *)routine, p);
		usleep(100);
		pthread_mutex_lock(&p->roma);
		p->vv += 1;
		pthread_mutex_unlock(&p->roma);
	}
	while (ft_alleat(p) || p->nbr_to_eat == -1)
	{
		if (i >= p->nbr_philo)
			i = 0;
		tn = tim() - p->t0;
		if ((tn - p->l_eat[i]) >= p->tdie && p->is_eating[i] == 0)
		{
			pthread_mutex_lock(&p->roma);
			printf("%zu %lu mat mat \n", tn, i + 1);
			return (0);
		}
		i++;
	}
	return (0);
}
