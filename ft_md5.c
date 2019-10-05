/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:28:18 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/04 16:32:24 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		init_table(t_md5_ctx *md5)
{
	int	i;

	i = 0;
	while (i < 64)
	{
		md5->in[i] = floor((ft_power(2, 32) * ft_abs(sin(i + 1))));
		i++;
	}
}

void		md5_update(t_md5_ctx *context, ft_uchar *input, ft_ulong mlen)
{
	ft_ulong	t;
	ft_uchar	*p;

	t = context->i[0];
	if ((context->i[0] = (t + ((ft_ulong)mlen << 3))) < t)
	{
		context->i[1]++;
		context->i[1] += mlen >> 29;
	}
	t = (t >> 3) & 0x3f;
	if (t)
		*p = *((ft_uchar *)context->in + t);
	t = 64 - t;
	if (mlen < t)
	{
		ft_memcpy(p, input, mlen);
		return ;
	}
}

int			md5_init(t_md5_ctx *context)
{
	int i;

	i = 0;
	if (context)
	{
		ft_memset((void *)context->in, 0, 64);
		init_table(context);
		context->buf[0] = 0x67452301;
		context->buf[1] = 0xefcdab89;
		context->buf[2] = 0x98badcfe;
		context->buf[3] = 0x10325476;
		context->i[0] = 0;
		context->i[1] = 0;
		while (i < 16)
			context->digest[i++] = 0;
		return (1);
	}
	return (0);
}

static int	get_pad_nbr(int bitlen)
{
	int	padbits;

	padbits = 0;
	while (((bitlen + padbits) % 512) < 448)
	{
		padbits++;
	}
	return (padbits);
}

int			md5_pad_msg(t_md5_ctx *context, int bitlen, ft_uchar *d)
{
	int			padb;
	int			orig;
	int			one_bit;
	int			i;
	int			a;
	int			b;
	long	final;
	ft_uchar	*p_msg;

	orig = bitlen;
	one_bit = orig;
	padb = 0;
	i = 0;
	a = 0;
	b = 0;
	if (bitlen > 512)
	{
		i = bitlen / 512;
		bitlen = bitlen - (i * 512);
		i = 0;
	}
	padb = get_pad_nbr(bitlen * 8);
	a = ((((orig * 8) + padb)) + 64); //total size (in bits) needed for p_msg
	p_msg = (ft_uchar *)malloc(sizeof(ft_uchar) * (a / 8));
	ft_bzero(p_msg, (a / 8));
	a = 0;
	ft_memcpy(p_msg, d, orig);
	p_msg[one_bit++] = 0x80;
	i = 56;
	final = (long long)(orig * 8) >> i;
	while (a++ < 8) // update last 64 bits with totat bits in original message
	{
		p_msg[(orig + ((padb + (56 - i)) / 8))] = final;
		i -= 8;
		final = (long long)(orig * 8) >> i; // shift over in 8 bit increments;
	}
	context->size = ((((orig) + (padb / 8))) + 8);
	context->msg = (ft_uchar *)malloc(sizeof(ft_uchar) * context->size);
	ft_memcpy(context->msg, p_msg, ((((orig) + (padb / 8))) + 8));
	return (1);
}

void			ft_ssl_print_bits(t_md5_ctx *context)
{
	int	i;

	i = 0;
	while (i < context->size)
	{
		ft_printf("%10b ", context->msg[i]);
		i++;
		if ((i % 8) == 0 && i != 0)
			ft_printf("\n");
	}
}

void	md5_final(ft_uchar digest[16], t_md5_ctx *context)
{
	ft_printf("Padded message\n");
	ft_ssl_print_bits(context);
}

unsigned char		*ft_md5(const ft_uchar *d, ft_ulong n, ft_uchar *md)
{
	t_md5_ctx		context;
	unsigned int	i;

	i = 0;
	if (!md5_init(&context))
		return (NULL);
	md5_pad_msg(&context, ft_strlen((char *)d), (ft_uchar *)d);
	md5_update(&context, context.msg, context.size);
	md5_final(context.digest, &context);
	return (md);
}
