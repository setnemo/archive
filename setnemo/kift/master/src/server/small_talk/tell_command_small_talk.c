/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tell_command_small_talk.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshcherb <kshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:45:45 by kshcherb          #+#    #+#             */
/*   Updated: 2018/09/04 21:44:59 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "server/small_talk.h"

char	*tell_me_something(void *arg)
{
	int digit;

	(void)arg;
	srand(time(NULL));
	digit = rand() % 8;
	if (digit == 0)
		return (strdup("my creators are Vitaliy Ribalko, Artem Pahomov,"
		"Dana Mulish, Konstantyn Shcherbyna"));
	else if (digit == 1)
		return (strdup("cats have fewer toes on their back paws"));
	else if (digit == 2)
		return (strdup("that tiny pocket in jeans was designed to store pocket"
		" watches"));
	else if (digit == 3)
		return (strdup("turkeys can blush"));
	else if (digit == 4)
		return (strdup("mercedes invented a car controlled by joystick"));
	else if (digit == 5)
		return (strdup("you cannot snore and dream at the same time"));
	else if (digit == 6)
		return (strdup("a single cloud can weight more than 1 million pounds"));
	else if (digit == 7)
		return (strdup("donald duck comics were banned from Finland because "
		"he doesn’t wear pants"));
	return (strdup("i dont want to talk"));
}

char	*tell_a_joke(void *arg)
{
	int digit;

	(void)arg;
	srand(time(NULL));
	digit = rand() % 6;
	if (digit == 0)
		return (strdup("What did the traffic light say to the car? "
		"Don’t look! I’m about to change. haa.haa.haa"));
	else if (digit == 1)
		return (strdup("Why was the little strawberry crying?"
		"His mom was in a jam. haa.haa.haa"));
	else if (digit == 2)
		return (strdup("How do you befriend a squirrel?"
		"Just act like a nut. haa.haa.haa"));
	else if (digit == 3)
		return (strdup("What do you call a pony with a cough?"
		"A little hoarse. haa.haa.haa"));
	else if (digit == 4)
		return (strdup("I just wrote a book on reverse psychology."
		"Do not read it! haa.haa.haa"));
	else if (digit == 5)
		return (strdup("Who does a pharaoh talk to when he’s sad?"
		"His mummy, of course. haa.haa.haa"));
	return (strdup("i dont know any jokes"));
}
