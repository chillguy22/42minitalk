/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:13:26 by eaktimur          #+#    #+#             */
/*   Updated: 2024/07/22 16:31:43 by eaktimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> // For signal handling
#include <signal.h>
#include <signal.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> // For pause() and getpid()
#include <unistd.h>

void	putnbr(int n)
{
	char	temp;

	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
	}
	if (n >= 10)
		putnbr(n / 10);
	temp = (n % 10) + '0';
	write(1, &temp, 1);
}

void	convert_to_char(int pid, int bit)
{
	static int	i = 0;
	static char	c = 0;

	if (i < 8)
	{
		c |= bit << (7 - i);
		i++;
	}
	if (i == 8)
	{
		if (c == '\0' && pid)
			kill(pid, SIGUSR1);
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

void	sig_action(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		convert_to_char(info->si_pid, 1);
	else if (signum == SIGUSR2)
		convert_to_char(info->si_pid, 0);
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "\033[1;32m Welcome to the server \xF0\x9F\x98\x8E \033[0m", 40);
	write(1, " \n Server PID: ", 15);
	putnbr(getpid());
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = &sig_action;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
	}
	return (0);
}
