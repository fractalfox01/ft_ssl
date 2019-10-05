/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:28:18 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/04 21:24:10 by tvandivi         ###   ########.fr       */
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

void	calck_md5_sine(ft_u1 in[64])
{
	double	s;
	double	pwr;
	int		i;

	i = 0;
	pwr = ft_power(2, 32);
	while (i < 64)
	{
		s = fabs(sin(1 + i));
		in[i] = (ft_u4)(s * pwr);
		i++;
	}
}

void	set_rps(t_md5_ctx *context)
{
	context->rps1[0] = 7;
	context->rps1[1] = 12;
	context->rps1[2] = 17;
	context->rps1[3] = 22;
	context->rps2[0] = 5;
	context->rps2[1] = 9;
	context->rps2[2] = 14;
	context->rps2[3] = 20;
	context->rps3[0] = 4;
	context->rps3[1] = 11;
	context->rps3[2] = 16;
	context->rps3[3] = 21;
	context->rps4[0] = 7;
	context->rps4[1] = 12;
	context->rps4[2] = 17;
	context->rps4[3] = 22;
}

void		md5_update(t_md5_ctx *context, ft_u1 *input, ft_u8 mlen)
{
	calck_md5_sine(context->in);
	set_rps(context);
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

/*
**  Md5_pad_msg takes in the sent message to be hashed and pads it off
**  into a 488 mod 512 bit format
**  with the last 64 bits representing the length of the original message.
**  The following code from below:  a = ((((orig * 8) + padb)) + 64); is the
**  total size (in bits) needed for p_msg
**  The while loop update last 64 bits with totat bits in original message
**  final is a right >> left << shift leaving 8 bits remaining
*/

int			md5_pad_msg(t_md5_ctx *context, int bitlen, ft_u1 *d)
{
	int			padb;
	int			orig;
	int			one_bit;
	int			i;
	int			a;
	int			b;
	long	final;
	ft_u1	*p_msg;

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
	a = ((((orig * 8) + padb)) + 64);
	p_msg = (ft_u1 *)malloc(sizeof(ft_u1) * (a / 8));
	ft_bzero(p_msg, (a / 8));
	a = 0;
	ft_memcpy(p_msg, d, orig);
	p_msg[one_bit++] = 0x80;
	i = 56;
	final = (long long)(orig * 8) >> i;
	while (a++ < 8)
	{
		p_msg[(orig + ((padb + (56 - i)) / 8))] = final;
		i -= 8;
		final = (long long)(orig * 8) >> i;
	}
	context->size = ((((orig) + (padb / 8))) + 8);
	context->msg = (ft_u1 *)malloc(sizeof(ft_u1) * context->size);
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

void	md5_final(ft_u1 digest[16], t_md5_ctx *context)
{
	ft_printf("Padded message\n");
	ft_ssl_print_bits(context);
}

unsigned char		*ft_md5(const ft_u1 *d, ft_u8 n, ft_u1 *md)
{
	t_md5_ctx		context;
	unsigned int	i;

	i = 0;
	if (!md5_init(&context))
		return (NULL);
	md5_pad_msg(&context, ft_strlen((char *)d), (ft_u1 *)d);
	md5_update(&context, context.msg, context.size);
	md5_final(context.digest, &context);
	return (md);
}
