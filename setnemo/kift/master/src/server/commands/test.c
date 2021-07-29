/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:51:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 21:48:48 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*hello_test_callback(void *arg)
{
	(void)arg;
	return (strdup("hello my name is jopa assistant. i am the best assistant"
	"designed by UNIT Factory students."));
}
