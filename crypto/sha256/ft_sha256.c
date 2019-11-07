/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:54:13 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/05 18:11:28 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sha224_256.h"

void	ft_sha256_update(t_sha256_ctx *ctx, uint8_t *input, uint32_t mlen)
{
	unsigned int	i;
	unsigned int	index;
	unsigned int	partlen;
	uint8_t		padding[64];

	index = ((unsigned int)(ctx->count[0] >> 3) & 63);
	if ((SHA_C1 += (unsigned int)(mlen << 3)) < (unsigned int)(mlen << 3))
		SHA_C2++;
	SHA_C2 += (unsigned int)(mlen >> 29);
	partlen = 64 - index;
	if (mlen >= partlen)
	{
		ft_memcpy((ctx->msg_block + index), input, partlen);
		i = partlen;
		ft_sha256_transform(ctx, ctx->msg_block);
		while ((i + 63) < mlen)
		{
			ft_sha256_transform(ctx, (ctx->message + i));
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memset(padding, 0, 64);
	ft_memcpy(padding, (ctx->message + i), (mlen - i));

	uint32_t	k;
	uint32_t	b;
	uint32_t	padlen;
	uint8_t		bits[8];
	uint8_t		digest[32];

	b = 0;
	k = ctx->length;
	// ft_sha256_encode(bits, ctx->count, 2);
	padding[mlen - i] = 0x80;
	k = (unsigned int)((ctx->count[0] >> 3) & 0x3f);
	padlen = (k < 56) ? (56 - k) : (120 - k);
	if (padlen >= 56)
	{
		ft_sha256_transform(ctx, padding);
		ft_memset(ctx->msg_block, 0, 56);
	}
	// while (b < padlen)
	// {
	// 	context->msg_block[63 - b] = (uint8_t)((context->bit_len >> (b * 8)) & 0xff);
	// 	b++;
	// }
	/*
	** combine padding and bits, bits gos at last 8;
	** hardcodable check rfc
	*/
	ft_memcpy((padding + 56), bits, 8);
	ft_sha256_transform(ctx, padding);
	ft_sha256_encode(digest, ctx->sha256_h0, 8);
	i = 0;
	while (i < 8)
		ft_printf("%08x", ctx->sha256_h0[i++]);
	ft_printf("\n");
	// ft_memset(context, 0, sizeof(context));
}

void	ft_sha256_decode(uint32_t *w, uint8_t *msg)
{
	uint32_t	t;
	uint32_t	t4;

	t = 0;
	t4 = 0;
	while (t < 64)
	{
		w[t] = ((uint32_t)msg[t4 + 3]) | \
			((uint32_t)msg[t4 + 2] << 8) | \
			((uint32_t)msg[t4 + 1] << 16) | \
			((uint32_t)msg[t4] << 24);
		t++;
		t4 += 4;
	}
	t = 16;
	while (t < 64)
	{
		w[t] = SHA256_SIG1(w[t - 2]) + w[t - 7] \
			+ SHA256_SIG1(w[t - 15]) + w[t - 16];
		t++;
	}
}

void	ft_sha256_transform(t_sha256_ctx *context, uint8_t buf[64])
{
	uint32_t i;
	uint32_t j;
	uint32_t k;
	uint32_t abc[8];
	uint32_t w[64];

	i = 0;
	j = 0;
	k = 0;
	ft_sha256_decode(w, buf);
	while (i < 8)
	{
		j = abc[7] + SHA256_SIGMA1(abc[4]) + SHA_CH(abc[4], abc[5], abc[6]) \
		+ context->k[i] + w[i];
		k = SHA256_SIGMA0(abc[0]) + SHA_MAJ(abc[0], abc[1], abc[2]);
		abc[7] = abc[6];
		abc[6] = abc[5];
		abc[5] = abc[4];
		abc[4] = abc[3] + j;
		abc[3] = abc[2];
		abc[2] = abc[1];
		abc[1] = abc[0];
		abc[0] = j + k;
		i++;
	}
	i = 0;
	while (i < 8)
	{
		context->sha256_h0[i] = abc[i];
		i++;
	}
}

void	ft_sha256_encode(uint8_t *digest, uint32_t *s, uint32_t mlen)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < mlen)
	{
		digest[j + 3] = (uint8_t)(s[i] & 0xff);
		digest[j + 2] = (uint8_t)((s[i] >> 8) & 0xff);
		digest[j + 1] = (uint8_t)((s[i] >> 16) & 0xff);
		digest[j] = (uint8_t)((s[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void	ft_sha256_final(t_sha256_ctx *context, uint8_t digest[32])
{
	uint32_t	i;
	uint32_t	b;
	uint32_t	padlen;
	uint8_t		bits[8];
	uint8_t		padding[64];

	b = 0;
	i = context->length;
	ft_memset(padding, 0, 64);
	ft_sha256_encode(bits, context->count, 8);
	context->msg_block[i] = 0x80;
	i = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padlen = (i < 56) ? (56 - i) : (120 - i);
	if (padlen >= 56)
	{
		ft_sha256_transform(context, padding);
		ft_memset(context->msg_block, 0, 56);
	}
	// while (b < padlen)
	// {
	// 	context->msg_block[63 - b] = (uint8_t)((context->bit_len >> (b * 8)) & 0xff);
	// 	b++;
	// }
	ft_sha256_transform(context, bits);
	ft_sha256_encode(digest, context->sha256_h0, 8);
	// ft_memset(context, 0, sizeof(context));
}

void	ft_sha256(uint8_t *message)
{
	t_sha256_ctx	context;
	uint8_t			digest[32];
	int	i;

	i = 0;
	ft_sha256_init(&context, digest, message);
	ft_sha256_update(&context, message, ft_ustrlen(message));
	// ft_sha256_final(&context, digest);
	i = 0;
	while (i < 32)
		ft_printf("%02x", digest[i++]);
	ft_printf("\n");
}

