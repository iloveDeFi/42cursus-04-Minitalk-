/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:28:40 by bbessard          #+#    #+#             */
/*   Updated: 2023/04/19 12:52:59 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** Pour convertir des caractères en bits, qui peuvent ensuite 
** être transmis via des signaux en messages compréhensibles.
*/

int	ft_recursive_power(int nb, int power)
{
	int	res;

	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	else
	{
		res = nb * ft_recursive_power(nb, power - 1);
		return (res);
	}
}

/*
** Si *s1 = "hello" et letter = '!' alors tab = hello!
*/
char	*add_letter_to_string(char const *s1, char const letter)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	tab = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	tab[j++] = letter;
	tab[j] = 0;
	free ((void *)(s1));
	return (tab);
}

/*
** On utilise la fonction signal_handler pour écouter les signaux et 
reconstruire la chaîne de caractères. en utilisant le code ASCII, 
** chaque caractère sera représenté par un octet (8 bits) de données. 
** Cela signifie que le processus émetteur devra envoyer huit signaux 
** (SIGUSR1 ou SIGUSR2) pour chaque caractère de la chaîne.
**
** Signal_handler est appelée à chaque fois que le serveur reçoit un signal 
** SIGUSR1 ou SIGUSR2 du client. Elle est responsable de la 
** réception et de la conversion des signaux binaires en caractères ASCII,
**  qui sont ensuite stockés dans une chaîne de caractères pour former
**  le message complet envoyé par le client.
*/
void	signal_handler(int signum)
{
	static int	counter = 0;
	static int	result = 0;
	static int	len = 0;
	static char	*final;

	if (!final)
		final = ft_strdup("");
	if (signum == SIGUSR1)
		result = result + 0;
	else if (signum == SIGUSR2)
		result = result + (1 * ft_recursive_power(2, 7 - counter));
	counter++;
	if (counter == 8)
	{
		final = add_letter_to_string(final, result);
		if (result == '\0')
		{
			ft_printf("%s\n", final);
			final = NULL;
		}
		counter = 0;
		result = 0;
		len += 1;
	}
}

/*
** Ce code initialise le programme serveur en capturant les signaux SIGUSR1 et
** SIGUSR2 et en attendant la réception de signaux en continu.
** La fonction signal_handler sera appelée lorsqu'un signal est reçu et 
** effectuera le traitement correspondant.

** signal_received.sa_handler = signal_handler; affecte la fonction 
** signal_handler à la variable sa_handler de la structure signal_received.
** La fonction signal_handler sera appelée lorsque le processus recevra 
** le signal spécifié par sigaction.
 */

int	main(void)
{
	struct sigaction	signal_received;

	ft_printf("Welcome to my server\n");
	ft_printf("Server's PID: %d\n", getpid());
	signal_received.sa_handler = signal_handler;
	signal_received.sa_flags = 0;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
		usleep(50);
}