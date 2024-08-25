/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:17:16 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/25 18:09:28 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAST_STATUS_H
# define LAST_STATUS_H

# include	"minishell.h"
# include	"error.h"
# include	"../libft/libft.h"

void			set_last_status(unsigned int *status, unsigned int value);
unsigned int	get_last_status(const unsigned int *status);

#endif
