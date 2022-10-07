/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_posclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:11:43 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/02 14:52:43 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_posclear(t_pos *pos, int freee)
{
	while (*pos->size != 0)
		ft_lstdelone(pos->start, freee);
	if (freee == 1)
	{
		free(pos->size);
		free(pos);
	}
}
