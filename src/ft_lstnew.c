/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:58:02 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/06 23:49:49 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_list	*ft_lstnew(void *content, t_pos *pos, t_pos *garbage)
{
	t_list	*liste;

	liste = ft_malloc(sizeof(*liste), garbage);
	if (liste == 0)
		return (0);
	liste->content = content;
	liste->pos = pos;
	*liste->pos->size = *liste->pos->size + 1;
	if (pos->start == 0)
	{
		liste->next = liste;
		liste->back = liste;
		pos->start = liste;
	}
	else
	{
		liste->back = pos->start->back;
		liste->next = pos->start;
		if (*pos->size == 1)
			pos->start->next = liste;
		else
			pos->start->back->next = liste;
		pos->start->back = liste;
	}
	return (liste);
}
