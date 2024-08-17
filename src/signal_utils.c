/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:36:31 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/17 23:53:10 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"readline.h"

int		check_state(void);
void	reset_signal(void);
void	reset_sig(int signum);
void	setup_signal(void);

void	setup_signal(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	ignore_sig(SIGQUIT);
	setup_sigint();
}

void	reset_signal(void)
{
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
}
