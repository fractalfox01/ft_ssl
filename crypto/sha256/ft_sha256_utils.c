/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 09:13:39 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/06 16:23:57 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sha224_256.h"

static void     k1(uint32_t k[64])
{
	k[0] = 0x428a2f98;
	k[1] = 0x71374491;
	k[2] = 0xb5c0fbcf;
	k[3] = 0xe9b5dba5;
	k[4] = 0x3956c25b;
	k[5] = 0x59f111f1;
	k[6] = 0x923f82a4;
	k[7] = 0xab1c5ed5;
	k[8] = 0xd807aa98;
	k[9] = 0x12835b01;
	k[10] = 0x243185be;
	k[11] = 0x550c7dc3;
	k[12] = 0x72be5d74;
	k[13] = 0x80deb1fe;
	k[14] = 0x9bdc06a7;
	k[15] = 0xc19bf174;
	k[16] = 0xe49b69c1;
	k[17] = 0xefbe4786;
	k[18] = 0x0fc19dc6;
	k[19] = 0x240ca1cc;
	k[20] = 0x2de92c6f;
	k[21] = 0x4a7484aa;
	k[22] = 0x5cb0a9dc;
	k[23] = 0x76f988da;
	k[24] = 0x983e5152;
}

static void	    k2(uint32_t k[64])
{
	k[25] = 0xa831c66d;
	k[26] = 0xb00327c8;
	k[27] = 0xbf597fc7;
	k[28] = 0xc6e00bf3;
	k[29] = 0xd5a79147;
	k[30] = 0x06ca6351;
	k[31] = 0x14292967;
	k[32] = 0x27b70a85;
	k[33] = 0x2e1b2138;
	k[34] = 0x4d2c6dfc;
	k[35] = 0x53380d13;
	k[36] = 0x650a7354;
	k[37] = 0x766a0abb;
	k[38] = 0x81c2c92e;
	k[39] = 0x92722c85;
	k[40] = 0xa2bfe8a1;
	k[41] = 0xa81a664b;
	k[42] = 0xc24b8b70;
	k[43] = 0xc76c51a3;
	k[44] = 0xd192e819;
	k[45] = 0xd6990624;
	k[46] = 0xf40e3585;
	k[47] = 0x106aa070;
	k[48] = 0x19a4c116;
	k[49] = 0x1e376c08;
}

static void	    k3(uint32_t k[64])
{
	k[50] = 0x2748774c;
	k[51] = 0x34b0bcb5;
	k[52] = 0x391c0cb3;
	k[53] = 0x4ed8aa4a;
	k[54] = 0x5b9cca4f;
	k[55] = 0x682e6ff3;
	k[56] = 0x748f82ee;
	k[57] = 0x78a5636f;
	k[58] = 0x84c87814;
	k[59] = 0x8cc70208;
	k[60] = 0x90befffa;
	k[61] = 0xa4506ceb;
	k[62] = 0xbef9a3f7;
	k[63] = 0xc67178f2;
}

static void	    init_loops(t_sha256_ctx *context, uint8_t digest[32])
{
	int	i;

	i = 0;
	while (i < 8)
		context->abc[i++] = 0;
	i = 0;
	while (i < 3)
		context->count[i++] = 0;
	i = 0;
	while (i < 64)
		context->w[i++] = 0;
	i = 0;
	while (i < FT_SHA256MSIZE)
		context->msg_block[i++] = 0;
	i = 0;
	while (i < (FT_SHA256HSIZE / 4))
		context->msg_block[i++] = 0;
	i = 0;
	while (i < 32)
		digest[i++] = 0;
}

void	        ft_sha256_init(t_sha256_ctx *ctx, uint8_t d[32], uint8_t *message)
{
	init_loops(ctx, d);
	ctx->message = ft_uchardup(message);
	ctx->length = ft_ustrlen(message);
	ctx->bit_len = ctx->length * 8;
	k1(ctx->k);
	k2(ctx->k);
	k3(ctx->k);
	ctx->sha256_h0[0] = 0x6A09E667;
	ctx->sha256_h0[1] = 0xBB67AE85;
	ctx->sha256_h0[2] = 0x3C6EF372;
	ctx->sha256_h0[3] = 0xA54FF53A;
	ctx->sha256_h0[4] = 0x510E527F;
	ctx->sha256_h0[5] = 0x9B05688C;
	ctx->sha256_h0[6] = 0x1F83D9AB;
	ctx->sha256_h0[7] = 0x5BE0CD19;
	if (ctx->length >= 64)
		COUNT1 = 64;
	else
		COUNT1 = ctx->length;
	// ft_printf("Length: %u bitlen: %u\n", ctx->length, ctx->bit_len);
}
