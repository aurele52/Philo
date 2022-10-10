/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:49:50 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/10 17:04:16 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_takefork(t_philo *philo, t_list *act)
{
	if (act->content->philonbr % 2 == 0)
	{
		ft_takeleftfork(philo, act);
		ft_takerightfork(philo, act);
	}
	else
	{
		ft_takerightfork(philo, act);
		ft_takeleftfork(philo, act);
	}
}

void	ft_takerightfork(t_philo *philo, t_list *act)
{
	pthread_mutex_lock(&philo->deathmutex);
	while (act->content->rightarm == 0 && philo->isdead == 0)
	{
		pthread_mutex_unlock(&philo->deathmutex);
		pthread_mutex_lock(&act->back->content->forkmutex);
		if (act->back->content->fork == 1)
		{
			act->content->rightarm = 1;
			act->back->content->fork = 0;
			ft_philowrite(philo, 1, act->content->philonbr);
		}
		pthread_mutex_unlock(&act->back->content->forkmutex);
		pthread_mutex_lock(&philo->deathmutex);
		usleep(500);
	}
	pthread_mutex_unlock(&philo->deathmutex);
}

void	ft_dropfork(t_list *act)
{
	act->content->leftarm = 0;
	act->content->rightarm = 0;
	pthread_mutex_lock(&act->next->content->forkmutex);
	act->next->content->fork = 1;
	pthread_mutex_unlock(&act->next->content->forkmutex);
	pthread_mutex_lock(&act->back->content->forkmutex);
	act->back->content->fork = 1;
	pthread_mutex_unlock(&act->back->content->forkmutex);
}

void	ft_takeleftfork(t_philo *philo, t_list *act)
{
	pthread_mutex_lock(&philo->deathmutex);
	while (act->content->leftarm == 0 && philo->isdead == 0)
	{
		pthread_mutex_unlock(&philo->deathmutex);
		pthread_mutex_lock(&act->next->content->forkmutex);
		if (act->next->content->fork == 1)
		{
			act->content->leftarm = 1;
			act->next->content->fork = 0;
			ft_philowrite(philo, 1, act->content->philonbr);
		}
		pthread_mutex_unlock(&act->next->content->forkmutex);
		pthread_mutex_lock(&philo->deathmutex);
		usleep(500);
	}
	pthread_mutex_unlock(&philo->deathmutex);
}

int	ft_forkinit(t_philo *philo)
{
	philo->philosopher->start->back
		= ft_lstnew(ft_malloc(sizeof(t_philosophe),
				philo->garbage), philo->philosopher, philo->garbage);
	if (philo->philosopher->start->back == 0)
		return (ft_exit(philo->garbage, "malloc error\n"));
				philo->philosopher->start->back->content->fork = 1;
	if (pthread_mutex_init(
			&philo->philosopher->start->back->content->forkmutex, NULL) != 0)
		return (ft_exit(philo->garbage, "mutex init error 2\n"));
	return (1);
}
