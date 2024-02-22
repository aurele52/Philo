/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:38:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/07 17:40:30 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_threadinit(t_philo *philo, t_temp *temp)
{
	int	ret;

	ret = pthread_create(temp->list->content->philoid,
			NULL, &ft_philo, (void *)temp);
	if (ret)
		return (ft_exit(philo->garbage, "error thread\n"));
	return (1);
}

int	ft_monitorthreadinit(t_philo *philo)
{
	int	ret;

	philo->philosopher->start->back->content->philoid
		= ft_malloc(sizeof(pthread_t), philo->garbage);
	if (philo->philosopher->start->back->content->philoid == 0)
		return (ft_exit(philo->garbage, "malloc error\n"));
	ret = pthread_create(philo->philosopher->start->back->content->philoid,
			NULL, &ft_monitor, (void *)philo);
	if (ret)
		return (ft_exit(philo->garbage, "error thread\n"));
	return (1);
}

t_temp	*ft_tempinit(t_philo *philo, t_list *liste)
{
	t_temp	*temp;

	temp = ft_malloc(sizeof(*temp), philo->garbage);
	if (!temp)
		return (ft_exit2(philo->garbage, "malloc error\n"));
	temp->philo = philo;
	temp->list = liste;
	return (temp);
}
