/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:58:19 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/07 18:19:10 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_mutexdestroy(t_philo *philo)
{
	t_list	*list;

	list = philo->philosopher->start;
	pthread_mutex_destroy(&philo->deathmutex);
	pthread_mutex_destroy(&philo->writemutex);
	pthread_mutex_destroy(&list->content->lastmutex);
	list = list->next;
	pthread_mutex_destroy(&list->content->forkmutex);
	list = list->next;
	while (list != list->pos->start)
	{
		pthread_mutex_destroy(&list->content->lastmutex);
		list = list->next;
		pthread_mutex_destroy(&list->content->forkmutex);
		list = list->next;
	}
}

int	ft_go(t_philo *philo, int i, t_temp *temp, t_list *mem)
{
	philo->base = philo->base + ft_gettime(philo);
	while (i++ < philo->numberofphilo)
	{
		temp = ft_tempinit(philo, mem);
		if (!temp)
			return (0);
		if (ft_threadinit(philo, temp) == 0)
			return (0);
		mem = mem->next->next;
	}
	if (ft_monitorthreadinit(philo) == 0)
		return (0);
	mem = philo->philosopher->start;
	while (i-- > 1)
	{
		pthread_join(*mem->content->philoid, NULL);
		mem = mem->next->next;
	}
	pthread_join(*philo->philosopher->start->back->content->philoid, NULL);
	ft_mutexdestroy(philo);
	return (ft_exit(philo->garbage, 0));
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;
	t_list	*mem;
	t_temp	*temp;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_exit(0, "argument error\n"));
	philo = ft_philoinit(argc, argv);
	if (!philo)
		return (0);
	while (i++ < philo->numberofphilo)
	{
		ft_philosopherinit(philo);
		if (!philo)
			return (0);
		ft_forkinit(philo);
		if (!philo)
			return (0);
	}
	i = 0;
	temp = 0;
	mem = philo->philosopher->start;
	return (ft_go(philo, i, temp, mem));
}
