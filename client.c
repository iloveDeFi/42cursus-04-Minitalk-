/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:28:35 by bbessard          #+#    #+#             */
/*   Updated: 2023/04/13 11:08:11 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** La fonction send_signals prend deux arguments: un PID et un message. 
** La fonction envoie le message caractère par caractère en convertissant 
** chaque caractère en sa représentation binaire, puis en envoyant un signal 
** à un autre processus en fonction de la valeur de chaque bit binaire. 
** Si le bit est 0, le programme envoie un signal SIGUSR1 et si le bit est 1, 
** il envoie un signal SIGUSR2. La fonction utilise également la fonction usleep 
** pour ralentir l'envoi des signaux afin de permettre au processus récepteur 
** de traiter les signaux reçus.
*/

void send_signals(int pid, char	*message)
{
	int				letter;
	int				i;

	letter = 0;
	while (message[letter])
	{
		i = -1;
		while (++i < 8)
		{
			if (((unsigned char)(message[letter] >> (7 - i)) & 1) == 0)
				kill(pid, SIGUSR1);
			else if (((unsigned char)(message[letter] >> (7 - i)) & 1) == 1)
				kill(pid, SIGUSR2);
			usleep(50);
		}
	letter++;
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}

/*
** La fonction main prend deux arguments: le PID du processus de réception et le 
** message à envoyer. Le programme vérifie d'abord que deux arguments ont été 
** passés en entrée, puis il convertit le PID en entier et stocke le message dans 
** une variable. Si le PID est invalide ou si le message est vide, le programme 
** affiche un message d'erreur correspondant. Sinon, le programme appelle la fonction 
** send_signals pour envoyer le message au processus récepteur.
*/ 

int	main(int argc, char **argv)
{
	char				*message;
	int					server_id;

	if (argc == 3)
	{
		server_id = ft_atoi(argv[1]);	
		if (!server_id)
		{
			ft_printf("[ERROR]. Wrong arg");
			return (0);
		}
		message = argv[2];
		if (message[0] == 0)
		{
			ft_printf("Tu n'as envoyé aucun texte ! Ecris un truc bro");
			return (0);
		}
		send_signals(server_id, message);
	}
	else
	{
		ft_printf("[ERROR]. Too much or too few arguments.\n Make sure ");
		ft_printf("you enter arguments as follow: ./client <PID> <MESSAGE>");
	}
	return (0);
}

/*
** Le programme envoie des signaux au processus récepteur en utilisant les valeurs 
** binaires de chaque caractère du message pour communiquer le message caractère 
** par caractère.
*/