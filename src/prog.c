/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:43:37 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/07 17:44:25 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_philowrite(t_philo *philo, int text, int philonbr)
{
	pthread_mutex_lock(&philo->writemutex);
	ft_putnbr(ft_gettime(philo));
	write(1, " ", 1);
	ft_putnbr(philonbr);
	write(1, " ", 1);
	if (text == 0)
		write(1, "died\n", 5);
	else if (text == 1)
		write(1, "has taken a fork\n", 17);
	else if (text == 2)
		write(1, "is eating\n", 10);
	else if (text == 3)
		write(1, "is sleeping\n", 12);
	else if (text == 4)
		write(1, "is thinking\n", 12);
	else if (text == 5)
		write(1, "has drop\n", 9);
	pthread_mutex_unlock(&philo->writemutex);
}

void	ft_dead(t_philo *philo, t_list *act)
{
	pthread_mutex_lock(&philo->deathmutex);
	if (philo->isdead == 0)
		ft_philowrite(philo, 0, act->content->philonbr);
	philo->isdead = 1;
	pthread_mutex_unlock(&philo->deathmutex);
}

int	ft_usleep(t_philo *philo, unsigned long long time)
{
	while (time > 10000)
	{
		pthread_mutex_lock(&philo->deathmutex);
		if (philo->isdead != 0)
			return (ft_deathmutex(philo));
		pthread_mutex_unlock(&philo->deathmutex);
		usleep(10000);
		time = time - 10000;
	}
	pthread_mutex_lock(&philo->deathmutex);
	if (philo->isdead != 0)
		return (ft_deathmutex(philo));
	pthread_mutex_unlock(&philo->deathmutex);
	usleep(time);
	pthread_mutex_lock(&philo->deathmutex);
	if (philo->isdead != 0)
		return (ft_deathmutex(philo));
	pthread_mutex_unlock(&philo->deathmutex);
	return (0);
}

int	ft_eatsleep2(t_philo *philo, t_list *act)
{
	ft_dropfork(act);
	ft_philowrite(philo, 3, act->content->philonbr);
	if (ft_usleep(philo, philo->timetosleep * 1000) == 1)
		return (1);
	ft_philowrite(philo, 4, act->content->philonbr);
	usleep(1000);
	pthread_mutex_lock(&philo->deathmutex);
	if (philo->isdead != 0)
		return (ft_deathmutex(philo));
	pthread_mutex_unlock(&philo->deathmutex);
	return (0);
}

int	ft_eatsleep(t_philo *philo, t_list *act)
{
	pthread_mutex_lock(&philo->deathmutex);
	if (philo->isdead != 0)
		return (ft_deathmutex(philo));
	pthread_mutex_unlock(&philo->deathmutex);
	pthread_mutex_lock(&act->content->lastmutex);
	act->content->last = ft_gettime(philo);
	pthread_mutex_unlock(&act->content->lastmutex);
	ft_philowrite(philo, 2, act->content->philonbr);
	act->content->timehaveeat++;
	pthread_mutex_lock(&act->content->lastmutex);
	act->content->last = ft_gettime(philo);
	pthread_mutex_unlock(&act->content->lastmutex);
	if (ft_usleep(philo, philo->timetoeat * 1000) == 1)
		return (1);
	if (ft_eatsleep2(philo, act) == 1)
		return (1);
	return (0);
}
