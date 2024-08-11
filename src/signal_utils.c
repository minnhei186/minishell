/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:36:31 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/10 21:24:33 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"

volatile sig_atomic_t	g_sig;

g_sig = 0;

void	handler(int signum)
{
	g_sig = signum;
}
