/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:28:18 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/23 19:38:38 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	ft_md5_round1(unsigned int state[4], unsigned int x[16])
{
	FF(state[0], state[1], state[2], state[3], x[0], 7, 0xd76aa478);
	FF(state[3], state[0], state[1], state[2], x[1], 12, 0xe8c7b756);
	FF(state[2], state[3], state[0], state[1], x[2], 17, 0x242070db);
	FF(state[1], state[2], state[3], state[0], x[3], 22, 0xc1bdceee);
	FF(state[0], state[1], state[2], state[3], x[4], 7, 0xf57c0faf);
	FF(state[3], state[0], state[1], state[2], x[5], 12, 0x4787c62a);
	FF(state[2], state[3], state[0], state[1], x[6], 17, 0xa8304613);
	FF(state[1], state[2], state[3], state[0], x[7], 22, 0xfd469501);
	FF(state[0], state[1], state[2], state[3], x[8], 7, 0x698098d8);
	FF(state[3], state[0], state[1], state[2], x[9], 12, 0x8b44f7af);
	FF(state[2], state[3], state[0], state[1], x[10], 17, 0xffff5bb1);
	FF(state[1], state[2], state[3], state[0], x[11], 22, 0x895cd7be);
	FF(state[0], state[1], state[2], state[3], x[12], 7, 0x6b901122);
	FF(state[3], state[0], state[1], state[2], x[13], 12, 0xfd987193);
	FF(state[2], state[3], state[0], state[1], x[14], 17, 0xa679438e);
	FF(state[1], state[2], state[3], state[0], x[15], 22, 0x49b40821);
}

void	ft_md5_round2(unsigned int state[4], unsigned int x[16])
{
	GG(state[0], state[1], state[2], state[3], x[1], 5, 0xf61e2562);
	GG(state[3], state[0], state[1], state[2], x[6], 9, 0xc040b340);
	GG(state[2], state[3], state[0], state[1], x[11], 14, 0x265e5a51);
	GG(state[1], state[2], state[3], state[0], x[0], 20, 0xe9b6c7aa);
	GG(state[0], state[1], state[2], state[3], x[5], 5, 0xd62f105d);
	GG(state[3], state[0], state[1], state[2], x[10], 9, 0x2441453);
	GG(state[2], state[3], state[0], state[1], x[15], 14, 0xd8a1e681);
	GG(state[1], state[2], state[3], state[0], x[4], 20, 0xe7d3fbc8);
	GG(state[0], state[1], state[2], state[3], x[9], 5, 0x21e1cde6);
	GG(state[3], state[0], state[1], state[2], x[14], 9, 0xc33707d6);
	GG(state[2], state[3], state[0], state[1], x[3], 14, 0xf4d50d87);
	GG(state[1], state[2], state[3], state[0], x[8], 20, 0x455a14ed);
	GG(state[0], state[1], state[2], state[3], x[13], 5, 0xa9e3e905);
	GG(state[3], state[0], state[1], state[2], x[2], 9, 0xfcefa3f8);
	GG(state[2], state[3], state[0], state[1], x[7], 14, 0x676f02d9);
	GG(state[1], state[2], state[3], state[0], x[12], 20, 0x8d2a4c8a);
}

void	ft_md5_round3(unsigned int state[4], unsigned int x[16])
{
	HH(state[0], state[1], state[2], state[3], x[5], 4, 0xfffa3942);
	HH(state[3], state[0], state[1], state[2], x[8], 11, 0x8771f681);
	HH(state[2], state[3], state[0], state[1], x[11], 16, 0x6d9d6122);
	HH(state[1], state[2], state[3], state[0], x[14], 23, 0xfde5380c);
	HH(state[0], state[1], state[2], state[3], x[1], 4, 0xa4beea44);
	HH(state[3], state[0], state[1], state[2], x[4], 11, 0x4bdecfa9);
	HH(state[2], state[3], state[0], state[1], x[7], 16, 0xf6bb4b60);
	HH(state[1], state[2], state[3], state[0], x[10], 23, 0xbebfbc70);
	HH(state[0], state[1], state[2], state[3], x[13], 4, 0x289b7ec6);
	HH(state[3], state[0], state[1], state[2], x[0], 11, 0xeaa127fa);
	HH(state[2], state[3], state[0], state[1], x[3], 16, 0xd4ef3085);
	HH(state[1], state[2], state[3], state[0], x[6], 23, 0x4881d05);
	HH(state[0], state[1], state[2], state[3], x[9], 4, 0xd9d4d039);
	HH(state[3], state[0], state[1], state[2], x[12], 11, 0xe6db99e5);
	HH(state[2], state[3], state[0], state[1], x[15], 16, 0x1fa27cf8);
	HH(state[1], state[2], state[3], state[0], x[2], 23, 0xc4ac5665);
}

void	ft_md5_round4(unsigned int state[4], unsigned int x[16])
{
	II(state[0], state[1], state[2], state[3], x[0], 6, 0xf4292244);
	II(state[3], state[0], state[1], state[2], x[7], 10, 0x432aff97);
	II(state[2], state[3], state[0], state[1], x[14], 15, 0xab9423a7);
	II(state[1], state[2], state[3], state[0], x[5], 21, 0xfc93a039);
	II(state[0], state[1], state[2], state[3], x[12], 6, 0x655b59c3);
	II(state[3], state[0], state[1], state[2], x[3], 10, 0x8f0ccc92);
	II(state[2], state[3], state[0], state[1], x[10], 15, 0xffeff47d);
	II(state[1], state[2], state[3], state[0], x[1], 21, 0x85845dd1);
	II(state[0], state[1], state[2], state[3], x[8], 6, 0x6fa87e4f);
	II(state[3], state[0], state[1], state[2], x[15], 10, 0xfe2ce6e0);
	II(state[2], state[3], state[0], state[1], x[6], 15, 0xa3014314);
	II(state[1], state[2], state[3], state[0], x[13], 21, 0x4e0811a1);
	II(state[0], state[1], state[2], state[3], x[4], 6, 0xf7537e82);
	II(state[3], state[0], state[1], state[2], x[11], 10, 0xbd3af235);
	II(state[2], state[3], state[0], state[1], x[2], 15, 0x2ad7d2bb);
	II(state[1], state[2], state[3], state[0], x[9], 21, 0xeb86d391);
}

// void		md5transform(t_md5_ctx *context, unsigned int *state, unsigned char *buf)
// {
	
// }

// void		show_me_kspc(unsigned int *kspc)
// {
// 	int	i = 0;

// 	while (i < 64)
// 	{
// 		ft_printf("k[i] %x\n", kspc[i++]);
// 	}
// }

void	md5_clearout(t_md5_ctx *context)
{
	context->a = 0;
	context->b = 0;
	context->c = 0;
	context->d = 0;
}

void		md5_encode(unsigned char digest[16], unsigned int state[4], unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		digest[j] = (unsigned char)(state[i] & 0xff);
		digest[j+1] = (unsigned char)((state[i] >> 8) & 0xff);
		digest[j+2] = (unsigned char)((state[i] >> 16) & 0xff);
		digest[j+3] = (unsigned char)((state[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void		md5_final(unsigned char digest[16], t_md5_ctx *context)
{
	unsigned char	bits[8];
	unsigned char	padding[64];
	unsigned int	index;
	unsigned int	padlen;

	ft_memset(padding, 0, 64);
	padding[0] = 0x80;
	ft_memset(bits, 0, 8);
	md5_encode(bits, context->count, 8);
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padlen = (index < 56) ? (56 - index) : (120 - index);
	md5_update(context, padding, padlen);
	md5_update(context, bits, 8);
	md5_encode(digest, context->state, 16);
	ft_memset(context, 0, sizeof(context));
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
	context->rps3[3] = 23;
	context->rps4[0] = 6;
	context->rps4[1] = 10;
	context->rps4[2] = 15;
	context->rps4[3] = 21;
}

void	md5_init(t_md5_ctx *context)
{
	int	i;

	i = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
	context->a = 0;
	context->b = 0;
	context->c = 0;
	context->d = 0;
	while (i < 2)
		context->count[i++] = 0;
	i = 0;
	while (i < 64)
		context->buf[i++] = '\0';
	//set_rps(context);
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

void	md5_decode(unsigned int output[16], unsigned char *input, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = ((unsigned int)(input[j])) | ((unsigned int)((input[j + 1] << 8))) | ((unsigned int)((input[j + 2] << 16))) | ((unsigned int)((input[j + 3] << 24)));
		i++;
		j += 4;
	}
}

void md5_transform(t_md5_ctx *context, unsigned char buf[64])
{
	int				i;
	unsigned int	x[16];
	unsigned int	state[4];

	i = 0;
	state[0] = context->state[0];
	state[1] = context->state[1];
	state[2] = context->state[2];
	state[3] = context->state[3];
	while (i < 16)
		x[i++] = 0;
	md5_decode(x, buf, 64);
	i = 0;
	ft_md5_round1(state, x);
	ft_md5_round2(state, x);
	ft_md5_round3(state, x);
	ft_md5_round4(state, x);
	context->state[0] += state[0];
	context->state[1] += state[1];
	context->state[2] += state[2];
	context->state[3] += state[3];
	md5_clearout(context);
	ft_memset(x, 0, 16);
}

void		md5_update(t_md5_ctx *context, unsigned char *input, unsigned long mlen)
{
	unsigned int	i;
	unsigned int	index;
	unsigned int	partlen;

	index = ((unsigned int)(context->count[0] >> 3) & 63);
	if ((context->count[0] += (unsigned int)(mlen << 3)) < (unsigned int)(mlen << 3))
		context->count[1]++;
	context->count[1] += (unsigned int)(mlen >> 29);
	partlen = 64 - index;
	if (mlen >= partlen)
	{
		ft_memcpy((void *)(context->buf + index), input, partlen);
		i = partlen;
		md5_transform(context, context->buf);
		while ((i + 63) < mlen)
		{
			md5_transform(context, (context->msg + i));
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memcpy((unsigned char *)(context->buf + index), (unsigned char *)(input + i), mlen - i);
}

unsigned char		*ft_md5_pre(const unsigned char *d)
{
	t_md5_ctx		context;
	unsigned char	md[16];
	int	i;

	i = 0;
	while (i < 16)
		md[i++] = 0;
	i = 0;
	md5_init(&context);
	while (i < 16)
	{
		md[i++] = 0;
	}
	context.msg = ft_uchardup(d);
	md5_update(&context, (unsigned char *)d, ft_ustrlen((unsigned char *)d));
	md5_final(md, &context);
	i = 0;
	while (i < 16)
		ft_printf("%02x", md[i++]);
	ft_printf("\n");
	return (NULL);
}
