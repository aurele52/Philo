/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:44:47 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/10 17:01:23 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_deathmutex(t_philo *philo)
{
	pthread_mutex_unlock(&philo->deathmutex);
	return (1);
}

void	*ft_philo(void *temp)
{
	t_philo	*philo;
	t_list	*act;

	philo = ((t_temp *)temp)->philo;
	act = ((t_temp *)temp)->list;
	if (act->content->philonbr % 2 == 0)
	{
		ft_philowrite(philo, 4, act->content->philonbr);
		usleep(1000);
	}
	pthread_mutex_lock(&philo->deathmutex);
	while (philo->isdead == 0)
	{
		pthread_mutex_unlock(&philo->deathmutex);
		ft_takefork(philo, act);
		if (ft_eatsleep(philo, act) == 1)
			return (0);
		pthread_mutex_lock(&philo->deathmutex);
		usleep(500);
	}
	pthread_mutex_unlock(&philo->deathmutex);
	return (0);
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
		usleep(500);
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
	pthread_mutex_lock(&philo->deathmutex);
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
	}
	ft_instantdead(philo);
	return (0);
}
