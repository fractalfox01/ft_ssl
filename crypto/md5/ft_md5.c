/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:28:18 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/29 20:56:49 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include "../../includes/ft_md5.h"

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
}

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

unsigned char		*ft_md5(const unsigned char *d)
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
