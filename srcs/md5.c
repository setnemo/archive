/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 10:07:36 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 10:07:37 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static ULL getu32 (unsigned char *addr)
{
	return (((((unsigned long)addr[3] << 8) | addr[2]) << 8)
		| addr[1]) << 8 | addr[0];
}

static void putu32 (ULL data, unsigned char *addr)
{
	addr[0] = (unsigned char)data;
	addr[1] = (unsigned char)(data >> 8);
	addr[2] = (unsigned char)(data >> 16);
	addr[3] = (unsigned char)(data >> 24);
}

void md5init(t_md5 *md5data)
{
	md5data->buf[0] = 0x67452301;
	md5data->buf[1] = 0xefcdab89;
	md5data->buf[2] = 0x98badcfe;
	md5data->buf[3] = 0x10325476;

	md5data->bits[0] = 0;
	md5data->bits[1] = 0;
}

void md5update(t_md5 *md5data, unsigned char *buf, unsigned len)
{
	ULL				t;
	unsigned char	*p;

	t = md5data->bits[0];
	if ((md5data->bits[0] = (t + ((ULL)len << 3)) & 0xffffffff) < t)
		md5data->bits[1]++;
	md5data->bits[1] += len >> 29;
	t = (t >> 3) & 0x3f;
	if (t)
	{
		p = md5data->in + t;
		t = 64 - t;
		if (len < t) {
			memcpy(p, buf, len);
			return ;
		}
		memcpy(p, buf, t);
		md5transform(md5data->buf, md5data->in);
		buf += t;
		len -= t;
	}
	while (len >= 64)
	{
		memcpy(md5data->in, buf, 64);
		md5transform(md5data->buf, md5data->in);
		buf += 64;
		len -= 64;
	}
	memcpy(md5data->in, buf, len);
}

void md5final(unsigned char digest[], t_md5 *md5data)
{
	unsigned count;
	unsigned char *p;

	count = (md5data->bits[0] >> 3) & 0x3F;
	p = md5data->in + count;
	*p++ = 0x80;
	count = 64 - 1 - count;
	if (count < 8)
	{
		memset(p, 0, count);
		md5transform(md5data->buf, md5data->in);
		memset(md5data->in, 0, 56);
	}
	else
		memset(p, 0, count - 8);
	putu32(md5data->bits[0], md5data->in + 56);
	putu32(md5data->bits[1], md5data->in + 60);
	md5transform(md5data->buf, md5data->in);
	putu32(md5data->buf[0], digest);
	putu32(md5data->buf[1], digest + 4);
	putu32(md5data->buf[2], digest + 8);
	putu32(md5data->buf[3], digest + 12);
	memset(md5data, 0, sizeof(md5data));
}

void md5transform1(t_mds *md)
{
	MD5STEP(F1, md->a, md->b, md->c, md->d, md->in[0]+0xd76aa478, 7);
	MD5STEP(F1, md->d, md->a, md->b, md->c, md->in[1]+0xe8c7b756, 12);
	MD5STEP(F1, md->c, md->d, md->a, md->b, md->in[2]+0x242070db, 17);
	MD5STEP(F1, md->b, md->c, md->d, md->a, md->in[3]+0xc1bdceee, 22);
	MD5STEP(F1, md->a, md->b, md->c, md->d, md->in[4]+0xf57c0faf, 7);
	MD5STEP(F1, md->d, md->a, md->b, md->c, md->in[5]+0x4787c62a, 12);
	MD5STEP(F1, md->c, md->d, md->a, md->b, md->in[6]+0xa8304613, 17);
	MD5STEP(F1, md->b, md->c, md->d, md->a, md->in[7]+0xfd469501, 22);
	MD5STEP(F1, md->a, md->b, md->c, md->d, md->in[8]+0x698098d8, 7);
	MD5STEP(F1, md->d, md->a, md->b, md->c, md->in[9]+0x8b44f7af, 12);
	MD5STEP(F1, md->c, md->d, md->a, md->b, md->in[10]+0xffff5bb1, 17);
	MD5STEP(F1, md->b, md->c, md->d, md->a, md->in[11]+0x895cd7be, 22);
	MD5STEP(F1, md->a, md->b, md->c, md->d, md->in[12]+0x6b901122, 7);
	MD5STEP(F1, md->d, md->a, md->b, md->c, md->in[13]+0xfd987193, 12);
	MD5STEP(F1, md->c, md->d, md->a, md->b, md->in[14]+0xa679438e, 17);
	MD5STEP(F1, md->b, md->c, md->d, md->a, md->in[15]+0x49b40821, 22);
}

void md5transform2(t_mds *md)
{
	MD5STEP(F2, md->a, md->b, md->c, md->d, md->in[1]+0xf61e2562, 5);
	MD5STEP(F2, md->d, md->a, md->b, md->c, md->in[6]+0xc040b340, 9);
	MD5STEP(F2, md->c, md->d, md->a, md->b, md->in[11]+0x265e5a51, 14);
	MD5STEP(F2, md->b, md->c, md->d, md->a, md->in[0]+0xe9b6c7aa, 20);
	MD5STEP(F2, md->a, md->b, md->c, md->d, md->in[5]+0xd62f105d, 5);
	MD5STEP(F2, md->d, md->a, md->b, md->c, md->in[10]+0x02441453, 9);
	MD5STEP(F2, md->c, md->d, md->a, md->b, md->in[15]+0xd8a1e681, 14);
	MD5STEP(F2, md->b, md->c, md->d, md->a, md->in[4]+0xe7d3fbc8, 20);
	MD5STEP(F2, md->a, md->b, md->c, md->d, md->in[9]+0x21e1cde6, 5);
	MD5STEP(F2, md->d, md->a, md->b, md->c, md->in[14]+0xc33707d6, 9);
	MD5STEP(F2, md->c, md->d, md->a, md->b, md->in[3]+0xf4d50d87, 14);
	MD5STEP(F2, md->b, md->c, md->d, md->a, md->in[8]+0x455a14ed, 20);
	MD5STEP(F2, md->a, md->b, md->c, md->d, md->in[13]+0xa9e3e905, 5);
	MD5STEP(F2, md->d, md->a, md->b, md->c, md->in[2]+0xfcefa3f8, 9);
	MD5STEP(F2, md->c, md->d, md->a, md->b, md->in[7]+0x676f02d9, 14);
	MD5STEP(F2, md->b, md->c, md->d, md->a, md->in[12]+0x8d2a4c8a, 20);
}

void md5transform3(t_mds *md)
{
	MD5STEP(F3, md->a, md->b, md->c, md->d, md->in[5]+0xfffa3942, 4);
	MD5STEP(F3, md->d, md->a, md->b, md->c, md->in[8]+0x8771f681, 11);
	MD5STEP(F3, md->c, md->d, md->a, md->b, md->in[11]+0x6d9d6122, 16);
	MD5STEP(F3, md->b, md->c, md->d, md->a, md->in[14]+0xfde5380c, 23);
	MD5STEP(F3, md->a, md->b, md->c, md->d, md->in[1]+0xa4beea44, 4);
	MD5STEP(F3, md->d, md->a, md->b, md->c, md->in[4]+0x4bdecfa9, 11);
	MD5STEP(F3, md->c, md->d, md->a, md->b, md->in[7]+0xf6bb4b60, 16);
	MD5STEP(F3, md->b, md->c, md->d, md->a, md->in[10]+0xbebfbc70, 23);
	MD5STEP(F3, md->a, md->b, md->c, md->d, md->in[13]+0x289b7ec6, 4);
	MD5STEP(F3, md->d, md->a, md->b, md->c, md->in[0]+0xeaa127fa, 11);
	MD5STEP(F3, md->c, md->d, md->a, md->b, md->in[3]+0xd4ef3085, 16);
	MD5STEP(F3, md->b, md->c, md->d, md->a, md->in[6]+0x04881d05, 23);
	MD5STEP(F3, md->a, md->b, md->c, md->d, md->in[9]+0xd9d4d039, 4);
	MD5STEP(F3, md->d, md->a, md->b, md->c, md->in[12]+0xe6db99e5, 11);
	MD5STEP(F3, md->c, md->d, md->a, md->b, md->in[15]+0x1fa27cf8, 16);
	MD5STEP(F3, md->b, md->c, md->d, md->a, md->in[2]+0xc4ac5665, 23);
}

void md5transform4(t_mds *md)
{
	MD5STEP(F4, md->a, md->b, md->c, md->d, md->in[0]+0xf4292244, 6);
	MD5STEP(F4, md->d, md->a, md->b, md->c, md->in[7]+0x432aff97, 10);
	MD5STEP(F4, md->c, md->d, md->a, md->b, md->in[14]+0xab9423a7, 15);
	MD5STEP(F4, md->b, md->c, md->d, md->a, md->in[5]+0xfc93a039, 21);
	MD5STEP(F4, md->a, md->b, md->c, md->d, md->in[12]+0x655b59c3, 6);
	MD5STEP(F4, md->d, md->a, md->b, md->c, md->in[3]+0x8f0ccc92, 10);
	MD5STEP(F4, md->c, md->d, md->a, md->b, md->in[10]+0xffeff47d, 15);
	MD5STEP(F4, md->b, md->c, md->d, md->a, md->in[1]+0x85845dd1, 21);
	MD5STEP(F4, md->a, md->b, md->c, md->d, md->in[8]+0x6fa87e4f, 6);
	MD5STEP(F4, md->d, md->a, md->b, md->c, md->in[15]+0xfe2ce6e0, 10);
	MD5STEP(F4, md->c, md->d, md->a, md->b, md->in[6]+0xa3014314, 15);
	MD5STEP(F4, md->b, md->c, md->d, md->a, md->in[13]+0x4e0811a1, 21);
	MD5STEP(F4, md->a, md->b, md->c, md->d, md->in[4]+0xf7537e82, 6);
	MD5STEP(F4, md->d, md->a, md->b, md->c, md->in[11]+0xbd3af235, 10);
	MD5STEP(F4, md->c, md->d, md->a, md->b, md->in[2]+0x2ad7d2bb, 15);
	MD5STEP(F4, md->b, md->c, md->d, md->a, md->in[9]+0xeb86d391, 21);
}

void md5transform(ULL buf[], unsigned char inraw[])
{
	t_mds	md;
	int		i;

	i = -1;
	while (16 > ++i)
		md.in[i] = getu32(inraw + 4 * i);
	md.a = buf[0];
	md.b = buf[1];
	md.c = buf[2];
	md.d = buf[3];
	md5transform1(&md);
	md5transform2(&md);
	md5transform3(&md);
	md5transform4(&md);
	buf[0] += md.a;
	buf[1] += md.b;
	buf[2] += md.c;
	buf[3] += md.d;
}

// int main (int argc, char **argv)
// {
// 	t_md5 context;
// 	unsigned char checksum[16];
// 	int i;
// 	int j;

// 	if (argc < 2)
// 	{
// 		fprintf (stderr, "usage: %s string-to-hash\n", argv[0]);
// 		return (1);
// 	}
// 	for (j = 1; j < argc; ++j)
// 	{
// 		printf ("MD5 (\"%s\") = ", argv[j]);
// 		md5init (&context);
// 		md5update (&context, argv[j], strlen (argv[j]));
// 		md5final (checksum, &context);
// 		for (i = 0; i < 16; i++)
// 		{
// 			printf ("%02x", (unsigned int) checksum[i]);
// 		}
// 		printf ("\n");
// 	}
// 	return 0;
// }
