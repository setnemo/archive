/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_whirlpool.h"
#include "ft_ssl_whirlpool_sbox.h"

void		rwh(uint64_t *b, uint64_t *a, int n, uint64_t c)
{
	*b = t[(a[n] >> 56) & 0xFF];
	*b ^= ROR64(t[(a[(n + 7) % 8] >> 48) & 0xFF], 8);
	*b ^= ROR64(t[(a[(n + 6) % 8] >> 40) & 0xFF], 16);
	*b ^= ROR64(t[(a[(n + 5) % 8] >> 32) & 0xFF], 24);
	*b ^= ROR64(t[(a[(n + 4) % 8] >> 24) & 0xFF], 32);
	*b ^= ROR64(t[(a[(n + 3) % 8] >> 16) & 0xFF], 40);
	*b ^= ROR64(t[(a[(n + 2) % 8] >> 8) & 0xFF], 48);
	*b ^= ROR64(t[a[(n + 1) % 8] & 0xFF], 56);
	*b ^= c;
}

uint64_t swapwh64(uint64_t x)
{
	x = ((((uint64_t)(x) & 0x00000000000000FFULL) << 56) | \
		(((uint64_t)(x) & 0x000000000000FF00ULL) << 40) | \
		(((uint64_t)(x) & 0x0000000000FF0000ULL) << 24) | \
		(((uint64_t)(x) & 0x00000000FF000000ULL) << 8) | \
		(((uint64_t)(x) & 0x000000FF00000000ULL) >> 8) | \
		(((uint64_t)(x) & 0x0000FF0000000000ULL) >> 24) | \
		(((uint64_t)(x) & 0x00FF000000000000ULL) >> 40) | \
		(((uint64_t)(x) & 0xFF00000000000000ULL) >> 56));
	return (x);
}

void whirlpoolUpdate(t_wh *context, const void *data, size_t length)
{
	size_t n;

	while(length > 0)
	{
		n = MIN(length, 64 - context->size);
		memcpy(context->buffer + context->size, data, n);
		context->size += n;
		context->totalSize += n;
		data = (uint8_t *) data + n;
		length -= n;
		if(context->size == 64)
		{
			whirlpoolProcessBlock(context);
			context->size = 0;
		}
	}
}

void whirlpoolFinal(t_wh *context, uint8_t *digest)
{
	int i;
	size_t paddingSize;
	uint64_t totalSize;

	totalSize = context->totalSize * 8;
	if (context->size < 32)
		paddingSize = 32 - context->size;
	else
		paddingSize = 64 + 32 - context->size;
	whirlpoolUpdate(context, padding, paddingSize);
	context->x[4] = 0;
	context->x[5] = 0;
	context->x[6] = 0;
	context->x[7] = swapwh64(totalSize);
	whirlpoolProcessBlock(context);
	for(i = 0; i < 8; i++)
		 context->h[i] = swapwh64(context->h[i]);
	if (digest != NULL)
		 memcpy(digest, context->digest, WHIRLPOOL_DIGEST_SIZE);
}

void whirlpoolProcessBlock(t_wh *context)
{
	int i;
	int j;

	uint64_t *x = context->x;
	uint64_t *k = context->k;
	uint64_t *l = context->l;
	uint64_t *state = context->state;

	i = -1;
	while (++i < 8)
		 x[i] = swapwh64(x[i]);
	ft_memcpy(k, context->h, sizeof(uint64_t) * 8);
	i = -1;
	while (++i < 8)
		state[i] = x[i] ^ k[i];
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 8)
		{
			if (j == 0)
				rwh(&l[0], k, 0, rc[i]);
			else
				rwh(&l[j], k, j, 0);	
		}
		ft_memcpy(k, l, sizeof(uint64_t) * 8);
		j = -1;
		while (++j < 8)
			rwh(&l[j], state, j, k[j]);
		ft_memcpy(state, l, sizeof(uint64_t) * 8);
	}
	i = -1;
	while (++i < 8)
		context->h[i] ^= state[i] ^ x[i];
}