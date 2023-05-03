/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:28:35 by bbessard          #+#    #+#             */
/*   Updated: 2023/05/03 09:15:14 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** On prend en argument le ProcessID et un message. 
** On envoie le message caractère par caractère en convertissant 
** chaque caractère en sa représentation binaire.
** On envoie un signal en fonction de la valeur de chaque bit binaire. 
** Si le bit est 0, on envoie un signal SIGUSR1 et si le bit est 1, 
** on envoie un signal SIGUSR2. 
** On utilise la fonction usleep pour ralentir l'envoi des signaux 
** afin de permettre au processus récepteur de traiter les signaux reçus.
*/

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

/*
** On prend en arguments: le PID du processus de 
** réception et le message à envoyer.
** On vérifie que deux arguments ont été passés en entrée.
** On convertit le PID en entier et on stocke le message dans une variable. 
** On gère les erreurs. Si le PID est invalide ou si le message est vide, 
** on affiche un message d'erreur correspondant. Sinon, on
** appelle la fonction send_signals pour envoyer le message au 
** processus récepteur.
*/

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
