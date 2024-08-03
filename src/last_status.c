/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:19:01 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/03 19:22:58 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/last_status.h"

void	set_last_status(unsigned int *status, unsigned int value)
{
	if (status)
		*status = value;
}

unsigned int	get_last_status(const unsigned int *status)
{
	if (status != NULL)
		return (*status);
	else
		return (0);
}
