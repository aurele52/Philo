/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:07:09 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/07 14:29:39 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_exit(t_pos *garbage, char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	if (garbage != 0)
		ft_posclear(garbage, 1);
	return (0);
}
