/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_whirlpool.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:38:20 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:38:21 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_WHIRLPOOL_H
# define FT_SSL_WHIRLPOOL_H
# include <stdint.h>
# include <string.h>


typedef struct
 {
    union
    {
       uint64_t h[8];
       uint8_t digest[64];
    };
    union
    {
       uint64_t x[8];
       uint8_t buffer[64];
    };
 
    uint64_t k[8];
    uint64_t l[8];
    uint64_t state[8];
 
    size_t size;
    uint64_t totalSize;
 } WhirlpoolContext;
 
 
 //Whirlpool related constants
 
 //Whirlpool related functions
 void whirlpoolCompute(const void *data, size_t length, uint8_t *digest);
 void whirlpoolInit(WhirlpoolContext *context);
 void whirlpoolUpdate(WhirlpoolContext *context, const void *data, size_t length);
 void whirlpoolFinal(WhirlpoolContext *context, uint8_t *digest);
 void whirlpoolProcessBlock(WhirlpoolContext *context);
 

/*
** ****************************************************************************
** ************************* MACROS for transform *****************************
** ****************************************************************************
*/


/*
** ****************************************************************************
** **************************** struct for data *******************************
** ****************************************************************************
*/


/*
** ****************************************************************************
** **************************** const hash table ******************************
** ****************************************************************************
*/


/*
** ****************************************************************************
** ********************************* files ************************************
** ****************************************************************************
*/



#endif
