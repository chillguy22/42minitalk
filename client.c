/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:17:07 by eaktimur          #+#    #+#             */
/*   Updated: 2024/08/07 14:52:22 by eaktimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <signal.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		sign;

	sign = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}

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

void	send_message(int pid, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
	{
		i = 7;
		while (i >= 0)
		{
			if (((str[j] >> i) & 1) == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(200);
			i--;
		}
		j++;
	}
	i = 7;
	while (i-- >= 0)
	{
		kill(pid, SIGUSR2);
		usleep(200);
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		write(1, "\nReceived.\n", 12);
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*str;
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		write(1, "Pid is ", 7);
		putnbr(pid);
		write(1, "\n", 1);
		if (!pid)
		{
			write(1, "Incorrect pid.\n", 15);
			return (0);
		}
		str = argv[2];
		send_message(pid, str);
	}
	else
		write(1, "Usage: ./client <PID> <message>\n", 32);
}
