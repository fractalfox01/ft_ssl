/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 21:05:42 by tvandivi          #+#    #+#             */
/*   Updated: 2019/09/26 20:17:19 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vogsphere_ftprintf/includes/ft_printf.h"
#include "ft_ssl.h"
#include <limits.h>

/*
** Resources:
** https://en.wikipedia.org/wiki/MD5#Algorithm
*/

static void	set_round_1(t_md5 *md5)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		md5->rps[i++] = 7;
		md5->rps[i++] = 12;
		md5->rps[i++] = 17;
		md5->rps[i++] = 22;
	}
}

static void	set_round_2(t_md5 *md5)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		md5->rps[i++] = 5;
		md5->rps[i++] = 9;
		md5->rps[i++] = 14;
		md5->rps[i++] = 20;
	}
}

static void	set_round_3(t_md5 *md5)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		md5->rps[i++] = 4;
		md5->rps[i++] = 11;
		md5->rps[i++] = 16;
		md5->rps[i++] = 23;
	}
}

static void	set_round_4(t_md5 *md5)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		md5->rps[i++] = 6;
		md5->rps[i++] = 10;
		md5->rps[i++] = 15;
		md5->rps[i++] = 21;
	}
}

static int F(u_int32_ssl *x, u_int32_ssl *y, u_int32_ssl *z)
{
	return ((x && y) || (!x && z));
}

// static void rot1()
// {
	
// }

void		init_rounds(t_md5 *md5)
{
	set_round_1(md5);
	set_round_2(md5);
	set_round_3(md5);
	set_round_4(md5);
}

void		init_table(t_md5 *md5)
{
	int	i;

	i = 0;
	while (i < 64)
	{
		md5->k[i] = floor((ft_power(2, 32) * ft_abs(sin(i + 1))));
		i++;
	}
}

void		init_vars(t_md5 *md5, char *msg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	md5->a0 = 0x67452301;
	md5->b0 = 0xefcdab89;
	md5->c0 = 0x98badcfe;
	md5->d0 = 0x10325476;
}

void		md5_init(t_md5 *md5, char *msg)
{
	int	i;

	i = 0;
	md5->m = NULL;
	init_rounds(md5);
	init_table(md5);
	init_vars(md5, msg);
}

void	hlpr(unsigned char *msg, t_md5 *md5, int mlen)
{
	int i = 0;
	int j = 0;
	int b = 16;

	while (j < mlen && (i - 4) < mlen)
	{
		md5->m[j] = (unsigned int *)malloc(sizeof(unsigned int) * b);
		while (i < b)
		{
			md5->m[j][i] = (msg[i + 3] << 24);
			md5->m[j][i] = (msg[i + 2] << 16);
			md5->m[j][i] = (msg[i + 1] << 8);
			md5->m[j][i] = (msg[i + 0] << 0);
			i++;
		}
		b += 16;
		j++;
	}
}

void	new_ustr(t_md5 *md5, unsigned char *msg, int mlen)
{
	int i = 0;

	while (i < mlen)
	{
		md5->message[i] = msg[i];
		i++;
	}
	md5->message[i] = 0x80;
}

int		get_i(mlen)
{
	int i;

	i = 0;
	while (((mlen + i) % 512) != 448)
		i++;
	return (i);
}

void	pad_message(t_md5 *md5, unsigned char *msg, int mlen)
{
	unsigned char	*msg2;
	int i = 0;
	int a = 0;
	int b = mlen;
	int c = 0;
	int j = 0;
	md5->message = (unsigned char *)malloc(sizeof(unsigned char) * (mlen) + 1);
	new_ustr(md5, msg, mlen);
	if (mlen > 512)
	{
		mlen -= (mlen / 512) * 512;
	}
	i = get_i(mlen);
	ft_printf("b: %d\nsize: %d\n", b, (mlen + i + 2 + 64 + b));
	c = (mlen + i + 2 + 64 + b);
	md5->m = (unsigned int **)malloc(sizeof(unsigned int*) * c);
	hlpr(msg, md5, b);
	c = b + 2;
	while (c < (mlen + i + 1 + 64 + b))
	{
		md5->m[c++] = 0;
	}
	md5->n = (mlen + i + 1 + 64 + b);
}

unsigned	*ft_md5(const char *msg, int mlen)
{
	t_md5			md5;
	unsigned int	ret;
	unsigned int	tmp;

	tmp = 0;
	int a = 0;
	int i = 0;
	int j = 0;
	if (msg && mlen)
	{
		md5_init(&md5, (char *)msg);
		pad_message(&md5, (unsigned char *)msg, mlen);
		while ((i) < md5.n)
		{
			while (j < 16)
			{
				ft_printf("message: %u\n", md5.m[i][j]);
				j++;
				a++;
			}
			j = 0;
			i++;
		}
	}
	return (FT_SSL_NULL);
}
