/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:40:47 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/10 16:07:22 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_exit2(t_pos *garbage, char *str)
{
	ft_exit(garbage, str);
	return (0);
}

int	ft_philoinit2(t_philo *philo, int argc, char **argv)
{
	philo->isdead = 0;
	philo->numberofphilo = ft_atoi(argv[1]);
	philo->timetodie = ft_atoi(argv[2]);
	philo->timetoeat = ft_atoi(argv[3]);
	philo->timetosleep = ft_atoi(argv[4]);
	philo->numberoftime = 0;
	if (philo->numberofphilo < 1)
		return (0);
	if (argc == 6)
		philo->numberoftime = ft_atoi(argv[5]);
	else
		philo->numberoftime = 999999999;
	return (1);
}

t_philo	*ft_philoinit(int argc, char **argv)
{
	t_philo				*philo;
	t_pos				*garbage;
	struct timeval		time;

	garbage = ft_setpos(0);
	if (!garbage)
		return (ft_exit2(0, "fail malloc\n"));
	philo = ft_malloc(sizeof(*philo), garbage);
	if (!philo)
		return (ft_exit2(garbage, "fail malloc\n"));
	philo->garbage = garbage;
	if (ft_philoinit2(philo, argc, argv) == 0)
		return (ft_exit2(philo->garbage, "invalid argument\n"));
	gettimeofday(&time, 0);
	philo->base = (unsigned long long)time.tv_usec / 1000
		+ (unsigned long long)time.tv_sec * 1000;
	philo->philosopher = ft_setpos(philo->garbage);
	if (pthread_mutex_init(&philo->writemutex, NULL) != 0)
		return (ft_exit2(philo->garbage, "mutex init error\n"));
	if (pthread_mutex_init(&philo->numbermutex, NULL) != 0)
		return (ft_exit2(philo->garbage, "mutex init error\n"));
	if (pthread_mutex_init(&philo->deathmutex, NULL) != 0)
		return (ft_exit2(philo->garbage, "mutex init error\n"));
	return (philo);
}

unsigned long long	ft_gettime(t_philo *philo)
{
	struct timeval		time;

	gettimeofday(&time, 0);
	return ((unsigned long long)time.tv_usec / 1000
		+ (unsigned long long)time.tv_sec
		* 1000 - philo->base);
}

int	ft_philosopherinit(t_philo *philo)
{
	ft_lstnew(ft_malloc(sizeof(t_philosophe),
			philo->garbage), philo->philosopher, philo->garbage);
	if (philo->philosopher->start->back == 0)
		return (ft_exit(philo->garbage, "malloc error\n"));
	philo->philosopher->start->back->content->philoid
		= ft_malloc(sizeof(pthread_t), philo->garbage);
	if (philo->philosopher->start->back->content->philoid == 0)
		return (ft_exit(philo->garbage, "malloc error\n"));
	philo->philosopher->start->back->content->timehaveeat = 0;
	philo->philosopher->start->back->content->last = 0;
	philo->philosopher->start->back->content->rightarm = 0;
	philo->philosopher->start->back->content->leftarm = 0;
	philo->philosopher->start->back->content->philonbr
		= *philo->philosopher->size / 2 + 1;
	philo->philosopher->start->back->content->fork
		= philo->philosopher->start->back->content->philonbr % 2 + 1;
	if (pthread_mutex_init(
			&philo->philosopher->start->back->content->lastmutex, NULL) != 0)
		return (ft_exit(philo->garbage, "mutex init error 1\n"));
	return (1);
}
