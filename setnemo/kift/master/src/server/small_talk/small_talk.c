/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_talk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshcherb <kshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:45:45 by kshcherb          #+#    #+#             */
/*   Updated: 2018/09/04 21:46:04 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "server/small_talk.h"

char	*flip_a_coin(void *arg)
{
	int digit;

	(void)arg;
	srand(time(NULL));
	digit = rand() % 2;
	if (digit == 1)
		return (strdup("head"));
	else
		return (strdup("tail"));
}

char	*crystal_ball(void *arg)
{
	int digit;

	(void)arg;
	srand(time(NULL));
	digit = rand() % 8;
	if (digit == 0)
		return (strdup("yes definitely"));
	else if (digit == 1)
		return (strdup("you may rely on it"));
	else if (digit == 2)
		return (strdup("yes"));
	else if (digit == 3)
		return (strdup("most likely"));
	else if (digit == 4)
		return (strdup("ask again later"));
	else if (digit == 5)
		return (strdup("cannot predict now"));
	else if (digit == 6)
		return (strdup("my reply is no"));
	else if (digit == 7)
		return (strdup("my sources say no"));
	return (strdup("the magic ball is broken"));
}

char	*roll_the_dice(void *arg)
{
	int digit;

	(void)arg;
	srand(time(NULL));
	digit = rand() % 6;
	if (digit == 0)
		return (strdup("one out of six"));
	else if (digit == 1)
		return (strdup("two out of six"));
	else if (digit == 2)
		return (strdup("three out of six"));
	else if (digit == 3)
		return (strdup("four out of six"));
	else if (digit == 4)
		return (strdup("five out of six"));
	else if (digit == 5)
		return (strdup("six out of six"));
	return (strdup("the dice is broken"));
}

char	*sing_song(void *arg)
{
	int digit;

	(void)arg;
	srand(time(NULL));
	digit = rand() % 3;
	if (digit == 0)
		return (strdup("haay I jast met you and this is crazy, but here's my "
		"number, so call me maaaybeee"));
	else if (digit == 1)
		return (strdup("liyve to win,, till you die,, till the light dies in "
		"your eyes"));
	else if (digit == 2)
		return (strdup("op, eroinaa op op eroinaa maa"));
	return (strdup("i forgot all the songs"));
}
