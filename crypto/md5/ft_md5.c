/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:28:18 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/13 10:31:05 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void			md5_encode(uint8_t digest[16], uint32_t state[4], uint32_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		digest[j] = (unsigned char)(state[i] & 0xff);
		digest[j + 1] = (unsigned char)((state[i] >> 8) & 0xff);
		digest[j + 2] = (unsigned char)((state[i] >> 16) & 0xff);
		digest[j + 3] = (unsigned char)((state[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void			md5_final(unsigned char digest[16], t_md5_ctx *context)
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

void			md5_decode(uint32_t output[16], uint8_t *input, uint32_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = ((uint32_t)(input[j])) | \
			((uint32_t)((input[j + 1] << 8))) | \
			((uint32_t)((input[j + 2] << 16))) | \
			((uint32_t)((input[j + 3] << 24)));
		i++;
		j += 4;
	}
}

void			md5_update(t_md5_ctx *ctx, uint8_t *input, uint64_t mlen)
{
	unsigned int	i;
	unsigned int	index;
	unsigned int	partlen;

	index = ((uint32_t)(ctx->count[0] >> 3) & 63);
	if ((ctx->count[0] += (uint32_t)(mlen << 3)) < (uint32_t)(mlen << 3))
		ctx->count[1]++;
	ctx->count[1] += (uint32_t)(mlen >> 29);
	partlen = 64 - index;
	if (mlen >= partlen)
	{
		ft_memcpy((void *)(ctx->buf + index), input, partlen);
		i = partlen;
		md5_transform(ctx, ctx->buf);
		while ((i + 63) < mlen)
		{
			md5_transform(ctx, (ctx->msg + i));
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memcpy((uint8_t *)(ctx->buf + index), (uint8_t *)(input + i), mlen - i);
}

unsigned char	*ft_md5(const unsigned char *d)
{
	t_md5_ctx		context;
	unsigned char	md[16];
	uint8_t			*digest;
	int				i;

	i = 0;
	while (i < 16)
		md[i++] = 0;
	i = 0;
	md5_init(&context);
	while (i < 16)
		md[i++] = 0;
	context.msg = ft_uchardup(d);
	md5_update(&context, (unsigned char *)d, ft_ustrlen((unsigned char *)d));
	md5_final(md, &context);
	digest = ft_ustrnew(16);
	i = -1;
	while (++i < 16)
		digest[i] = md[i];
	i = 0;
	while (i < 64)
		context.buf[i++] = 0;
	ft_strdel((char **)&context.msg);
	return (digest);
}
