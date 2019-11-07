/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldft_sha256.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:29:59 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/06 16:56:41 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sha224_256.h"

void	ft_sha256_encode(uint8_t *digest, uint32_t *s, uint32_t mlen)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (j < mlen)
	{
		digest[j + 3] = (uint8_t)(s[i] & 0xff);
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
		// ft_printf("b: %08b\n", w[t]);
		w[t] = ((uint32_t)msg[t4 + 3]) | \
			((uint32_t)msg[t4 + 2] << 8) | \
			((uint32_t)msg[t4 + 1] << 16) | \
			((uint32_t)msg[t4] << 24);
		// ft_printf("a: %08b\n", w[t]);
		t++;
		t4 += 4;
	}
	t = 16;
	while (t < 64)
	{
		w[t] = SHA256_SIG1(w[t - 2]) + w[t - 7] \
			+ SHA256_SIG0(w[t - 15]) + w[t - 16];
		t++;
	}
}
// 01234567
// abcdefgh
void	ft_sha256_transform(t_sha256_ctx *context, uint8_t buf[64])
{
	uint32_t i;
	uint32_t j;
	uint32_t k;
	// uint32_t abc[8];
	uint32_t w[64];

	i = 0;
	j = 0;
	k = 0;
	ft_sha256_decode(w, buf);
	while (i < 8)
	{
		context->abc[i] = context->sha256_h0[i];
		i++;
	}
	i = 0;
	int s = 0;
	while (s < 8)
		printf("%08x\n", context->abc[s++]);
	printf("\n");
	while (i < 64)
	{
		j = context->abc[7] + SHA256_SIGMA1(context->abc[4]) + SHA_CH(context->abc[4], context->abc[5], context->abc[6]) \
		+ context->k[i] + w[63 - i];
		k = SHA256_SIGMA0(context->abc[0]) + SHA_MAJ(context->abc[0], context->abc[1], context->abc[2]);
		context->abc[7] = context->abc[6];
		context->abc[6] = context->abc[5];
		context->abc[5] = context->abc[4];
		context->abc[4] = context->abc[3] + j;
		context->abc[3] = context->abc[2];
		context->abc[2] = context->abc[1];
		context->abc[1] = context->abc[0];
		context->abc[0] = j + k;
		i++;
		s = 0;
		printf("%d)\n", i);
		while (s < 8)
		printf("%08x\n", context->abc[s++]);
	}
	i = 0;
	while (i < 8)
	{
		context->sha256_h0[i] += context->abc[i];
		i++;
	}
	while (s < 8)
		printf("%08x\n", context->sha256_h0[s++]);
}

void	ft_sha256_update(t_sha256_ctx *ctx, uint8_t *input, uint32_t mlen)
{
	uint32_t	i;
	uint32_t	index;
	uint32_t	partlen;
	uint8_t		msg[64];

	i = 0;
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
			ft_memcpy(msg, (input + i), 64);
			ft_sha256_transform(ctx, msg);
			i += 64;
		}
	}
	COUNT2 = (mlen - i);
	ft_memcpy(ctx->msg_block, (input + i), (mlen - i));
}

void	ft_sha256_final(t_sha256_ctx *ctx, uint8_t digest[32])
{
	uint32_t i;
	uint32_t j;
	uint32_t padlen;

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
	i = 0;
	while (i < 8)
		ft_printf("%08x", ctx->sha256_h0[i++]);
	ft_printf("\n");
	ft_sha256_encode(digest, ctx->sha256_h0, 32);
}

void	ft_sha256(uint8_t *message)
{
	t_sha256_ctx	context;
	uint8_t			digest[32];
	int	i;

	i = 0;
	ft_sha256_init(&context, digest, message);
	ft_sha256_update(&context, message, ft_ustrlen(message));
	ft_sha256_final(&context, digest);
	i = 0;
	while (i < 32)
		ft_printf("%02x", digest[i++]);
	ft_printf("\n");
}
