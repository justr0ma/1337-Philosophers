/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halaqoh <halaqoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:15:46 by halaqoh           #+#    #+#             */
/*   Updated: 2022/06/04 22:53:30 by halaqoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pint(t_filozof *p, int i, char *msg)
{
	pthread_mutex_lock(&p->roma);
	printf("%zu %d  %s \n", tim() - p->t0, i + 1, msg);
	pthread_mutex_unlock(&p->roma);
}

void	run(t_filozof *p, int i)
{
	p->is_eating[i] = 0;
	pint(p, i, " is sleeping");
	ft_usleep(p->tslep);
	pint(p, i, " is thinking");
}

int	ft_alleat(t_filozof *p)
{
	size_t	a;

	a = 0;
	while (a < p->nbr_philo)
	{
		if (p->is_alleat[a] != p->nbr_to_eat)
			return (1);
		a++;
	}
	return (0);
}

void	*routine(t_filozof *p)
{
	int				i;
	int				k;

	k = 0;
	pthread_mutex_lock(&p->roma);
	i = p->vv;
	p->l_eat[i] = tim() - p->t0;
	pthread_mutex_unlock(&p->roma);
	p->is_alleat[i] = 0;
	while (k++ < p->nbr_to_eat || (p->nbr_to_eat == -1))
	{
		pthread_mutex_lock(&p->fork[i]);
		pint(p, i, " has taken a frist fork");
		pthread_mutex_lock(&p->fork[(i + 1) % p->nbr_philo]);
		p->is_eating[i] = 1;
		pint(p, i, " has taken a second fork");
		pint(p, i, " is eating ");
		p->l_eat[i] = tim() - p->t0;
		ft_usleep(p->teat);
		p->is_alleat[i] += 1;
		pthread_mutex_unlock(&p->fork[i]);
		pthread_mutex_unlock(&p->fork[(i + 1) % p->nbr_philo]);
		run(p, i);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_filozof		*p;
	size_t			i;
	size_t			tn;

	init_p(&p, argv, argc);
	i = 0;
	tn = 0;
	p->t0 = tim();
	pthread_mutex_init(&p->roma, NULL);
	while (i < p->nbr_philo)
	{
		pthread_mutex_init(&p->fork[i], NULL);
		p->is_eating[i] = 0;
		i++;
	}
	if (is_mat(p, tn))
		return (0);
	i = 0;
	while (i < p->nbr_philo)
		pthread_mutex_destroy(&p->fork[i++]);
	return (0);
}
