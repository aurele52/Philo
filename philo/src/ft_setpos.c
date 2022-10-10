/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:38:33 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/06 21:12:20 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_pos	*ft_setpos(t_pos *garbage)
{
	t_pos	*pos;
	int		*size;

	size = ft_malloc(sizeof(*size), garbage);
	if (size == 0)
		return (0);
	pos = ft_malloc(sizeof(*pos), garbage);
	if (pos == 0)
	{
		if (garbage == 0)
			free(size);
		return (0);
	}
	pos->size = size;
	pos->start = 0;
	*size = 0;
	return (pos);
}
