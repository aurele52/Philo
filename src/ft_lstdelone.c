/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:08:00 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/06 21:11:42 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_lstdelone(t_list *list, int garbage)
{
	if (garbage == 1)
		free(list->content);
	*list->pos->size = *list->pos->size - 1;
	if (list->pos->start->back == list->pos->start)
		list->pos->start = 0;
	else
	{
		if (list->pos->start == list)
			list->pos->start = list->next;
		list->back->next = list->next;
		list->next->back = list->back;
	}
	if (garbage == 1)
		free(list);
}
