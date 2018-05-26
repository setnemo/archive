/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha256.h"

static void bswapw(uint32_t *p, uint32_t i)
{
	while (i--)
		p[i] = (RR(p[i],24) & 0x00ff00ff) | (RR(p[i],8) & 0xff00ff00);
}

static void rtrf(uint32_t *b, uint32_t *p, uint32_t i, uint32_t j)
{
	B(7,i) += (j ? (p[i & 15] += G1(P(i,14)) + P(i,9) + G0(P(i,1))) : p[i & 15])
			+ K[i+j] + S1(B(4,i))
			+ (B(6,i) ^ (B(4,i) & (B(5,i) ^ B(6,i))));
	B(3,i) += B(7,i);
	B(7,i) += S0(B(0,i)) + ( (B(0,i) & B(1,i)) | (B(2,i) & (B(0,i) ^ B(1,i))) );
}

static void hash(t_sha256 *data)
{
	uint32_t b[8], *p, j;

	b[0] = data->hash[0]; b[1] = data->hash[1]; b[2] = data->hash[2];
	b[3] = data->hash[3]; b[4] = data->hash[4]; b[5] = data->hash[5];
	b[6] = data->hash[6]; b[7] = data->hash[7];

	for (p = data->buf, j = 0; j < 64; j += 16)
		rtrf(b, p,  0, j), rtrf(b, p,  1, j), rtrf(b, p,  2, j),
		rtrf(b, p,  3, j), rtrf(b, p,  4, j), rtrf(b, p,  5, j),
		rtrf(b, p,  6, j), rtrf(b, p,  7, j), rtrf(b, p,  8, j),
		rtrf(b, p,  9, j), rtrf(b, p, 10, j), rtrf(b, p, 11, j),
		rtrf(b, p, 12, j), rtrf(b, p, 13, j), rtrf(b, p, 14, j),
		rtrf(b, p, 15, j);

	data->hash[0] += b[0]; data->hash[1] += b[1]; data->hash[2] += b[2];
	data->hash[3] += b[3]; data->hash[4] += b[4]; data->hash[5] += b[5];
	data->hash[6] += b[6]; data->hash[7] += b[7];

}

void sha256init(t_sha256 *data)
{
	data->len[0] = data->len[1] = 0;
	data->hash[0] = 0x6a09e667; data->hash[1] = 0xbb67ae85;
	data->hash[2] = 0x3c6ef372; data->hash[3] = 0xa54ff53a;
	data->hash[4] = 0x510e527f; data->hash[5] = 0x9b05688c;
	data->hash[6] = 0x1f83d9ab; data->hash[7] = 0x5be0cd19;

}

void sha256hash(t_sha256 *data, uint8_t *dat, uint32_t sz)
{
	register uint32_t i = data->len[0] & 63, l, j;

	if ((data->len[0] += sz) < sz)  ++(data->len[1]);

	for (j = 0, l = 64-i; sz >= l; j += l, sz -= l, l = 64, i = 0)
	{
		MEMCP((char *)data->buf + i, &dat[j], l);
		BSWP(data->buf, 16 );
		hash(data);
	}
	MEMCP((char *)data->buf + i, &dat[j], sz);

}

void sha256done(t_sha256 *data, uint8_t *buf)
{
	uint32_t i = (uint32_t)(data->len[0] & 63), j = ((~i) & 3) << 3;

	BSWP(data->buf, (i + 3) >> 2);

	data->buf[i >> 2] &= 0xffffff80 << j;
	data->buf[i >> 2] |= 0x00000080 << j;

	if (i < 56)
		i = (i >> 2) + 1;
	else
		data->buf[15] ^= (i < 60) ? data->buf[15] : 0, hash(data), i = 0;

	while (i < 14)
		data->buf[i++] = 0;
	data->buf[14] = (data->len[1] << 3)|(data->len[0] >> 29);
	data->buf[15] = data->len[0] << 3;

	hash(data);

	for (i = 0; i < 32; i++)
		data->buf[i % 16] = 0,
	buf[i] = (uint8_t)(data->hash[i >> 2] >> ((~i & 3) << 3));

}

