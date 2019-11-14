/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:29:59 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/11 18:49:17 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sha224_256.h"

void	ft_256encode(uint8_t *digest, uint32_t *s, uint32_t mlen)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (j < mlen)
	{
		digest[j + 3] = (uint8_t)((s[i]) & 0xff);
		digest[j + 2] = (uint8_t)((s[i] >> 8) & 0xff);
		digest[j + 1] = (uint8_t)((s[i] >> 16) & 0xff);
		digest[j] = (uint8_t)((s[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void	ft_sha256_decode(uint32_t *w, uint8_t *msg)
{
	uint32_t	t;
	uint32_t	t4;

	t = 0;
	t4 = 0;
	while (t4 < 64)
	{
		w[t] = ((uint32_t)msg[t4 + 3]) | \
			((uint32_t)msg[t4 + 2] << 8) | \
			((uint32_t)msg[t4 + 1] << 16) | \
			((uint32_t)msg[t4 + 0] << 24);
		t++;
		t4 += 4;
	}
	t = 16;
	while (t < 64)
	{
		w[t] = SHA256_SIG1(w[t - 2]) + w[t - 7] + \
			SHA256_SIG0(w[t - 15]) + w[t - 16];
		t++;
	}
}

void	u256(t_256ctx *ctx, uint8_t *input, uint32_t mlen, uint32_t i)
{
	uint32_t	index;
	uint32_t	partlen;
	uint8_t		msg[64];

	i = 64;
	ft_memset(msg, 0, 64);
	index = ((uint32_t)(COUNT0 >> 3) & 63);
	if ((COUNT0 += (uint32_t)(mlen << 3)) < (uint32_t)mlen << 3)
		COUNT1++;
	COUNT1 += (uint32_t)(mlen >> 29);
	partlen = (64 - index);
	if (mlen >= partlen)
	{
		ft_memcpy(msg, input, 64);
		ft_sha256_transform(ctx, msg);
		while ((i + 63) <= mlen)
		{
			ft_sha256_transform(ctx, (input + i));
			i += 64;
		}
	}
	else
		i = 0;
	COUNT2 = (mlen - i);
	ft_memcpy(ctx->msg_block, (input + i), (mlen - i));
}

void	ft_sha256_final(t_256ctx *ctx, uint8_t digest[32])
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	padlen;

	i = ctx->length;
	j = 0;
	ctx->msg_block[COUNT2] = 0x80;
	padlen = (uint32_t)((ctx->count[0] >> 3) & 0x3f);
	while (j < 8)
	{
		ctx->msg_block[63 - j] = (uint8_t)((ctx->bit_len >> (j * 8)) & 0xff);
		j++;
	}
	ft_sha256_transform(ctx, ctx->msg_block);
	ft_256encode(digest, ctx->sha256_h0, 32);
}

uint8_t	*ft_sha256(uint8_t *message)
{
	t_256ctx	context;
	uint8_t		md[32];
	uint8_t		*digest;
	int			i;

	i = 0;
	ft_sha256_init(&context, md, message);
	u256(&context, message, ft_ustrlen(message), 0);
	ft_sha256_final(&context, md);
	i = -1;
	digest = ft_ustrnew(32);
	while (i++ < 32)
		digest[i] = md[i];
	return (digest);
}
