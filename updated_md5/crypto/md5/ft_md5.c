/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:28:18 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/12 11:37:57 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

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
	context->rots[0] = context->rps1;
	context->rots[1] = context->rps2;
	context->rots[2] = context->rps3;
	context->rots[3] = context->rps4;
}

void	ft_md5_round1(t_tf *trn, unsigned int x[16], unsigned short *rps1)
{
	FF(trn->a, trn->b, trn->c, trn->d, x[0], rps1[0], 0xd76aa478);
	FF(trn->d, trn->a, trn->b, trn->c, x[1], rps1[1], 0xe8c7b756);
	FF(trn->c, trn->d, trn->a, trn->b, x[2], rps1[2], 0x242070db);
	FF(trn->b, trn->c, trn->b, trn->a, x[3], rps1[3], 0xc1bdceee);
	FF(trn->a, trn->b, trn->c, trn->d, x[0], rps1[0], 0xf57c0faf);
	FF(trn->d, trn->a, trn->b, trn->c, x[1], rps1[1], 0x4787c62a);
	FF(trn->c, trn->d, trn->a, trn->b, x[2], rps1[2], 0xa8304613);
	FF(trn->b, trn->c, trn->d, trn->a, x[3], rps1[3], 0xfd469501);
	FF(trn->a, trn->b, trn->c, trn->d, x[0], rps1[0], 0x698098d8);
	FF(trn->d, trn->a, trn->b, trn->c, x[1], rps1[1], 0x8b44f7af);
	FF(trn->c, trn->d, trn->a, trn->b, x[2], rps1[2], 0xffff5bb1);
	FF(trn->b, trn->c, trn->d, trn->a, x[3], rps1[3], 0x895cd7be);
	FF(trn->a, trn->b, trn->c, trn->d, x[0], rps1[0], 0x6b901122);
	FF(trn->d, trn->a, trn->b, trn->c, x[1], rps1[1], 0xfd987193);
	FF(trn->c, trn->d, trn->a, trn->b, x[2], rps1[2], 0xa679438e);
	FF(trn->b, trn->c, trn->d, trn->a, x[3], rps1[3], 0x49b40821);
}

void	ft_md5_round2(t_tf *trn, unsigned int *x, unsigned short *rps2)
{
	GG(trn->a, trn->b, trn->c, trn->d, x[1], rps2[0], 0xf61e2562);
	GG(trn->d, trn->a, trn->b, trn->c, x[6], rps2[1], 0xc040b340);
	GG(trn->c, trn->d, trn->a, trn->b, x[11], rps2[2], 0x265e5a51);
	GG(trn->b, trn->c, trn->d, trn->a, x[0], rps2[3], 0xe9b6c7aa);
	GG(trn->a, trn->b, trn->c, trn->d, x[5], rps2[0], 0xd62f105d);
	GG(trn->d, trn->a, trn->b, trn->c, x[10], rps2[1], 0x2441453);
	GG(trn->c, trn->d, trn->a, trn->b, x[15], rps2[2], 0xd8a1e681);
	GG(trn->b, trn->c, trn->d, trn->a, x[4], rps2[3], 0xe7d3fbc8);
	GG(trn->a, trn->b, trn->c, trn->d, x[9], rps2[0], 0x21e1cde6);
	GG(trn->d, trn->a, trn->b, trn->c, x[14], rps2[1], 0xc33707d6);
	GG(trn->c, trn->d, trn->a, trn->b, x[3], rps2[2], 0xf4d50d87);
	GG(trn->b, trn->c, trn->d, trn->a, x[8], rps2[3], 0x455a14ed);
	GG(trn->a, trn->b, trn->c, trn->d, x[13], rps2[0], 0xa9e3e905);
	GG(trn->d, trn->a, trn->b, trn->c, x[2], rps2[1], 0xfcefa3f8);
	GG(trn->c, trn->d, trn->a, trn->b, x[7], rps2[2], 0x676f02d9);
	GG(trn->b, trn->c, trn->d, trn->a, x[12], rps2[3], 0x8d2a4c8a);
}

void	ft_md5_round3(t_tf *trn, unsigned int *x, unsigned short *rps3)
{
	HH(trn->a, trn->b, trn->c, trn->d, x[5], rps3[0], 0xfffa3942);
	HH(trn->d, trn->a, trn->b, trn->c, x[8], rps3[1], 0x8771f681);
	HH(trn->c, trn->d, trn->a, trn->b, x[11], rps3[2], 0x6d9d6122);
	HH(trn->b, trn->c, trn->d, trn->a, x[14], rps3[3], 0xfde5380c);
	HH(trn->a, trn->b, trn->c, trn->d, x[1], rps3[0], 0xa4beea44);
	HH(trn->d, trn->a, trn->b, trn->c, x[4], rps3[1], 0x4bdecfa9);
	HH(trn->c, trn->d, trn->a, trn->b, x[7], rps3[2], 0xf6bb4b60);
	HH(trn->b, trn->c, trn->d, trn->a, x[10], rps3[3], 0xbebfbc70);
	HH(trn->a, trn->b, trn->c, trn->d, x[13], rps3[0], 0x289b7ec6);
	HH(trn->d, trn->a, trn->b, trn->c, x[0], rps3[1], 0xeaa127fa);
	HH(trn->c, trn->d, trn->a, trn->b, x[3], rps3[2], 0xd4ef3085);
	HH(trn->b, trn->c, trn->d, trn->a, x[6], rps3[3], 0x4881d05);
	HH(trn->a, trn->b, trn->c, trn->d, x[9], rps3[0], 0xd9d4d039);
	HH(trn->d, trn->a, trn->b, trn->c, x[12], rps3[1], 0xe6db99e5);
	HH(trn->c, trn->d, trn->a, trn->b, x[15], rps3[2], 0x1fa27cf8);
	HH(trn->b, trn->c, trn->d, trn->a, x[2], rps3[3], 0xc4ac5665);
}

void	ft_md5_round4(t_tf *trn, unsigned int *x, unsigned short *rps4)
{
	II(trn->a, trn->b, trn->c, trn->d, x[0], rps4[0], 0xf4292244);
	II(trn->d, trn->a, trn->b, trn->c, x[7], rps4[1], 0x432aff97);
	II(trn->c, trn->d, trn->a, trn->b, x[14], rps4[2], 0xab9423a7);
	II(trn->b, trn->c, trn->d, trn->a, x[5], rps4[3], 0xfc93a039);
	II(trn->a, trn->b, trn->c, trn->d, x[12], rps4[0], 0x655b59c3);
	II(trn->d, trn->a, trn->b, trn->c, x[3], rps4[1], 0x8f0ccc92);
	II(trn->c, trn->d, trn->a, trn->b, x[10], rps4[2], 0xffeff47d);
	II(trn->b, trn->c, trn->d, trn->a, x[1], rps4[3], 0x85845dd1);
	II(trn->a, trn->b, trn->c, trn->d, x[8], rps4[0], 0x6fa87e4f);
	II(trn->d, trn->a, trn->b, trn->c, x[15], rps4[1], 0xfe2ce6e0);
	II(trn->c, trn->d, trn->a, trn->b, x[6], rps4[2], 0xa3014314);
	II(trn->b, trn->c, trn->d, trn->a, x[13], rps4[3], 0x4e0811a1);
	II(trn->a, trn->b, trn->c, trn->d, x[4], rps4[0], 0xf7537e82);
	II(trn->d, trn->a, trn->b, trn->c, x[11], rps4[1], 0xbd3af235);
	II(trn->c, trn->d, trn->a, trn->b, x[2], rps4[2], 0x2ad7d2bb);
	II(trn->b, trn->c, trn->d, trn->a, x[9], rps4[3], 0xeb86d391);
}

void	decode(unsigned int x[16], unsigned char *buf, unsigned int a)
{
	
}

void		md5transform(t_md5_ctx *context, unsigned int *state, unsigned char *buf)
{
	
}

void		show_me_kspc(unsigned int *kspc)
{
	int	i = 0;

	while (i < 64)
	{
		ft_printf("k[i] %x\n", kspc[i++]);
	}
}

void md5_rounds(t_tf *transform, t_md5_ctx *context, unsigned int *state, unsigned char *buf)
{
	int		i;

	i = 0;
	while (i < 16)
		transform->x[i++] = 0;
	ft_md5_round1(transform, transform->x, context->rps1);
	ft_md5_round2(transform, transform->x, context->rps2);
	ft_md5_round3(transform, transform->x, context->rps3);
	ft_md5_round4(transform, transform->x, context->rps4);
}

void		md5_update(t_md5_ctx *context, unsigned char *input, unsigned long mlen)
{
	t_tf			transform;
	unsigned int	i;
	unsigned int	index;
	unsigned int	partlen;

	transform.a = context->state[0];
	transform.b = context->state[1];
	transform.c = context->state[2];
	transform.d = context->state[3];
	index = (unsigned int)(context->count[0] >> 3) & 63;
	context->count[0] += (unsigned int)(mlen << 3);
	if (context->count[0] < (unsigned int)(mlen << 3))
		context->count[1]++;
	context->count[1] += (unsigned int)(mlen >> 29);
	partlen = 64 - index;
	ft_printf("ctx->count[0] = %d\n", context->count[0]);
	if (mlen >= partlen)
	{
		ft_memcpy((void *)context->in, input, partlen);
		while (i < 64)
			context->buffer[i++] = 0;
		i = 0;
		md5_rounds(&transform, context, context->state, context->buffer);
		while ((i) < mlen)
		{
			md5_rounds(&transform, context, context->state, (context->msg + i));
			i += 64;
		}
		index = 0;
	}
	else
		ft_memcpy((void *)context->buf[index], (void *)input, mlen - i);
	context->state[0] += transform.a;
	context->state[1] += transform.b;
	context->state[2] += transform.c;
	context->state[3] += transform.d;
}

void		init_table(t_md5_ctx *context)
{
	
}

int			md5_init(t_md5_ctx *context)
{
	int	i;

	i = 0;
	ft_bzero((void *)context->buffer, 64);
	ft_bzero((void *)context->count, 2);
	ft_bzero((void *)context->i, 2);
	// still needs to finish initializing all the values...
	// Whyyyyyyyyyyyyy!?
	return (1);
}

void		md5_final(unsigned char digest[16], t_md5_ctx *context)
{
	if (digest && context)
	{
		int	i = 0;
		int	a = 0;
		while (i < 16)
		{
			if (a < 4)
				ft_printf("digest: %hhx\tstate: %x\n", context->digest[i++], context->state[a++]);
			else
				ft_printf("digest: %hhx\n", context->digest[i++]);
		}
	}
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

unsigned char		*ft_md5(const unsigned char *d, unsigned long n, unsigned char *md)
{
	t_md5_ctx		context;
	unsigned int	i;

	i = 0;
	if (!md5_init(&context))
		return (NULL);
	md5_pad_msg(&context, ft_strlen((char *)d), (unsigned char *)d);
	ft_ssl_print_bits(&context);
	md5_update(&context, context.msg, context.size);
	md5_final(context.digest, &context);
	// ft_printf("thiers: ");
	// system("md5 fox.txt");
	// ft_printf("\n");
	return (md);
}
