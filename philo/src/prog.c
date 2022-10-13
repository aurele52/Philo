/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:43:37 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/11 14:02:44 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_philowrite(t_philo *philo, int text, int philonbr)
{
	

	pthread_mutex_lock(&philo->writemutex);
	if (text == 0)
		printf("%lld %i died\n", ft_gettime(philo), philonbr);
	else if (text == 1)
		printf("%lld %i has taken a fork\n", ft_gettime(philo), philonbr);
	else if (text == 2)
		printf("%lld %i is eating\n", ft_gettime(philo), philonbr);
	else if (text == 3)
		printf("%lld %i is sleeping\n", ft_gettime(philo), philonbr);
	else if (text == 4)
		printf("%lld %i is thinking\n", ft_gettime(philo), philonbr);
	else if (text == 5)
		printf("%lld %i has drop\n", ft_gettime(philo), philonbr);
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
	unsigned long long	timeact;

	timeact = ft_gettime(philo);
	while (ft_gettime(philo) < timeact + time)
	{
		pthread_mutex_lock(&philo->deathmutex);
		if (philo->isdead != 0)
			return (ft_deathmutex(philo));
		pthread_mutex_unlock(&philo->deathmutex);
		usleep(1000);
	}
	return (0);
}

int	ft_eatsleep2(t_philo *philo, t_list *act)
{
	ft_dropfork(act);
	ft_philowrite(philo, 3, act->content->philonbr);
	if (ft_usleep(philo, philo->timetosleep) == 1)
		return (1);
	ft_philowrite(philo, 4, act->content->philonbr);
	usleep(5000);
	pthread_mutex_lock(&philo->deathmutex);
	if (philo->isdead != 0)
		return (ft_deathmutex(philo));
	pthread_mutex_unlock(&philo->deathmutex);
	return (0);
}

int	ft_eatsleep(t_philo *philo, t_list *act)
{
	pthread_mutex_lock(&philo->deathmutex);
	if (philo->isdead == 1)
		return (ft_deathmutex(philo));
	pthread_mutex_unlock(&philo->deathmutex);
	pthread_mutex_lock(&act->content->lastmutex);
	act->content->last = ft_gettime(philo);
	pthread_mutex_unlock(&act->content->lastmutex);
	ft_philowrite(philo, 2, act->content->philonbr);
	pthread_mutex_lock(&philo->numbermutex);
	act->content->timehaveeat++;
	pthread_mutex_unlock(&philo->numbermutex);
	if (ft_usleep(philo, philo->timetoeat) == 1)
		return (1);
	if (ft_eatsleep2(philo, act) == 1)
		return (1);
	return (0);
}
