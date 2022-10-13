/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:44:47 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/11 14:24:08 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_deathmutex(t_philo *philo)
{
	pthread_mutex_unlock(&philo->deathmutex);
	return (1);
}

void	*ft_checkmutexlock(t_list *act)
{
	ft_dropfork(act);
	return (0);
}

void	*ft_philo(void *temp)
{
	t_philo	*philo;
	t_list	*act;

	philo = ((t_temp *)temp)->philo;
	act = ((t_temp *)temp)->list;
	if (act->content->philonbr % 2 == 0)
		usleep(5000);
	pthread_mutex_lock(&philo->deathmutex);
	while (philo->isdead == 0)
	{
		pthread_mutex_unlock(&philo->deathmutex);
		ft_takefork(philo, act);
		pthread_mutex_lock(&philo->deathmutex);
		if (philo->isdead != 0)
		{
			pthread_mutex_unlock(&philo->deathmutex);
			return (ft_checkmutexlock(act));
		}
		pthread_mutex_unlock(&philo->deathmutex);
		if (ft_eatsleep(philo, act) == 1)
			return (ft_checkmutexlock(act));
		pthread_mutex_lock(&philo->deathmutex);
	}
	pthread_mutex_unlock(&philo->deathmutex);
	return (ft_checkmutexlock(act));
}

void	ft_instantdead(t_philo *philo)
{
	philo->isdead = 1;
	pthread_mutex_unlock(&philo->deathmutex);
}

int	ft_moniwhile(t_philo *philo, t_list *temp, int numberhaveeat)
{
	pthread_mutex_unlock(&philo->deathmutex);
	if (temp == philo->philosopher->start)
	{
		pthread_mutex_lock(&philo->numbermutex);
		numberhaveeat = 0;
		pthread_mutex_unlock(&philo->numbermutex);
	}
	pthread_mutex_lock(&philo->numbermutex);
	if (temp->content->timehaveeat >= philo->numberoftime)
		numberhaveeat++;
	pthread_mutex_unlock(&philo->numbermutex);
	pthread_mutex_lock(&temp->content->lastmutex);
	if (ft_gettime(philo) - temp->content->last > philo->timetodie)
		ft_dead(philo, temp);
	pthread_mutex_unlock(&temp->content->lastmutex);
	return (numberhaveeat);
}

void	*ft_monitor(void *data)
{
	t_philo	*philo;
	t_list	*temp;
	int		numberhaveeat;

	numberhaveeat = 0;
	philo = (t_philo *)data;
	temp = philo->philosopher->start;
	pthread_mutex_lock(&philo->deathmutex);
	while (philo->isdead == 0 && numberhaveeat != philo->numberofphilo)
	{
		numberhaveeat = ft_moniwhile(philo, temp, numberhaveeat);
		temp = temp->next->next;
		usleep(500);
		pthread_mutex_lock(&philo->deathmutex);
	}
	ft_instantdead(philo);
	return (0);
}
