/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_rsa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 09:25:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/06/03 09:25:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_rsa.h"
#include <stdio.h>
// <<<<<<< HEAD
// #include <fcntl.h>
// #define MAX_PRIME 4294967296

// static int	g_primes[100] = { 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
// 		37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
// 		107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
// 		179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241,
// 		251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
// 		331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
// 		409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479,
// 		487, 491, 499, 503, 509, 521, 523, 541, 547};
		
// int			generate_value(unsigned int *value)
// {
// 	int i;
// 	int fd;

// 	i = 0;
// 	fd = open("/dev/urandom", O_RDONLY);
// 	read(fd, value, sizeof(unsigned int));
// 	close(fd);
// 	*value *= 1;
// 	if (*value % 2 == 0)
// 		*value += 1;
// 	while (i < 100)
// 	{
// 		if (*value % g_primes[i] == 0)
// 			return (1);
// 		else
// 			i++;
// 	}
// 	return (0);
// }
// void divide(int dvsr, char *array)
// {
// int rem = 0;
// int dvnd;
// int quot;
// size_t i;
//     for(i = 0; i < (sizeof(array)/sizeof(array[0])) ; i++){
//         dvnd = (rem * 10) + (array[i] - 48);
//         rem = dvnd % dvsr;
//         quot = dvnd / dvsr;
//         array[i] = quot + 48;
//     }
// }

// void		start_generate_prime(void)
// {
// 	unsigned int	prime1;
// 	unsigned int	prime2;

// 	while (generate_value(&prime1))
// 		;
// 	while (generate_value(&prime2))
// 		;
// 	printf(":::::(%u)\n", prime1);
// 	printf(":::::(%u)\n", prime2);
// 	char array[10] = {'9','8','7','6','5','4','3','2','1','0'};
// 	ft_printf("=>%s\n", array);
// 	divide(8, &array[0]);
// 	ft_printf("=>%s\n", array);
// =======
// #include <fcntl.h>
void		mini_itoa_one_value_digits(char *str, int i, int value)
{
		while (str[i])
			i++;
		str[i] = 48 + value;
}

void		mini_itoa_two_difits(char *str, int i, int value)
{
	if (i == 0 && str[i] == 0)
	{
		str[i] = 49;
		str[i + 1] = 48 + value % 10;
	}
	else if (i == 0 && str[i] != 0)
	{
		str[i]++;
	}
	else if (str[i] != 0)
	{
		i += 2;
		mini_itoa_two_difits(str, i - 1, value);
	}
	else
	{
		str[i] = 48 + value % 10;
		if (str[i - 1] - 48 < 9)
			str[i - 1]++;
		else
			mini_itoa_two_difits(str, i - 1, value);
	}
}

void		power_two(char *str1, char *str2, int power)
{
	int i;
	int j;

	while (power--)
	{
		i = 0;
		while (str1[i])
		{
			j = str1[i] - 48;
			if (j < 5 && str2[i] == 0)
			{
				str2[i] = 48 + j * 2;
			}
			else if (j < 5 && str2[i] != 0)
			{
				mini_itoa_one_value_digits(str2, i + 1, j * 2);
			}
			else
				mini_itoa_two_difits(str2, i, j * 2);
			i++;
		}
		ft_strclr(str1);
		ft_strcpy(str1, str2);
		ft_strclr(str2);
	}
}

char		*generate_string(int power)
{
	char *str1;
	char *str2;

	str1 = malloc(9999);
	str2 = malloc(9999);
	str1[0] = '2';
	power_two(str1, str2, power);
	free(str2);
	return (str1);
}

void		generate_prime_numbers(unsigned int *one, unsigned int *two, int power)
{
	int randomData = open("/dev/urandom", O_RDONLY);
	// int randomData1 = open("/dev/random", O_RDONLY);
	if (randomData < 0 && *two)
	{
		// something went wrong
	}
	char *str = generate_string(power);
	printf("%s\n", str);
	read(randomData, one, sizeof(*one));
	// *one = ABS(*one);
	// printf(":::%u\n", *one);
}

void		start_genrsa(int argc, char **argv, int i)
{
	if (argc || argv || i)
		;
	unsigned int one, two;
	int power;
	if (*(argv + 2) == NULL)
		power = 31;
	else 
	{
		power = (ft_atoi(*(argv + 2))) - 1; // devizion 2 for search two multyplay integers
		if (power < 7)
			exit(0);
	}
	generate_prime_numbers(&one, &two, power);
}

void		start_rsa(int argc, char **argv, int i)
{
	if (argc || argv || i)
		;
}

void		start_rsautl(int argc, char **argv, int i)
{
	if (argc || argv || i)
		;
}
