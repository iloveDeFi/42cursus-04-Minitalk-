/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:28:35 by bbessard          #+#    #+#             */
/*   Updated: 2023/05/08 09:44:45 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signals(int pid, char	*str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
	{
		i = -1;
		while (++i < 8)
		{
			if (((unsigned char)(str[j] >> (7 - i)) & 1) == 0)
				kill(pid, SIGUSR1);
			else if (((unsigned char)(str[j] >> (7 - i)) & 1) == 1)
				kill(pid, SIGUSR2);
			usleep(50);
		}
		j++;
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	char	*message;
	int		server_id;

	if (argc == 3)
	{
		server_id = ft_atoi(argv[1]);
		if (!server_id)
		{
			ft_printf("[ERROR]. Damn son. Wrong <PID>");
		}
		message = argv[2];
		if (message[0] == 0)
		{
			ft_printf("NOPE, you need to write something Marmaduke");
		}
		send_signals(server_id, message);
	}
	else
	{
		ft_printf("[ERROR]. Bingpot! You need only 2 arguments.\n");
		ft_printf("Write it properly son: ./client <PID> <MESSAGE>");
	}
	return (0);
}
