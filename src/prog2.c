/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:44:47 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/07 17:45:50 by audreyer         ###   ########.fr       */
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
	}
	pthread_mutex_unlock(&philo->deathmutex);
	return (0);
}

void	ft_instantdead(t_philo *philo)
{
	pthread_mutex_lock(&philo->deathmutex);
	philo->isdead = 1;
	pthread_mutex_unlock(&philo->deathmutex);
}

void	*ft_monitor(void *data)
{
	t_philo	*philo;
	t_list	*temp;
	int		numberhaveeat;

	numberhaveeat = 0;
	philo = (t_philo *)data;
	temp = philo->philosopher->start;
	while (philo->isdead == 0 && numberhaveeat != philo->numberofphilo)
	{
		if (temp == philo->philosopher->start)
		{
			usleep(500);
			numberhaveeat = 0;
		}
		if (temp->content->timehaveeat >= philo->numberoftime)
			numberhaveeat++;
		pthread_mutex_lock(&temp->content->lastmutex);
		if (ft_gettime(philo) - temp->content->last > philo->timetodie)
			ft_dead(philo, temp);
		pthread_mutex_unlock(&temp->content->lastmutex);
		temp = temp->next->next;
	}
	ft_instantdead(philo);
	return (0);
}
