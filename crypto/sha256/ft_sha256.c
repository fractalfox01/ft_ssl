/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:29:59 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/26 16:53:26 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include "../../includes/ft_sha224_256.h"

int		ft_sha224_256addlen(t_sha224_256_ctx *context, uint32_t length)
{
	context->addtemp = context->length_low;
	context->length_low += length;
	context->corrupted = context->length_low;
	if ((context->corrupted < context->addtemp) && (++context->length_high))
		return (FT_SHA_TOO_LONG);
	return (context->corrupted);
}

int		ft_sha256input(t_sha224_256_ctx *context, uint8_t *msg, uint32_t length)
{
	if (context && msg)
	{
		while (length--)
		{
			context->message[context->message_index++] = *msg;
			msg++;
		}
	}
	return (FT_SHA_SUCESS);
}

void		set224_h0(t_sha224_256_ctx *ctx)
{
	ctx->sha256_h0[0] = 0xc1059ed8;
	ctx->sha256_h0[1] = 0x367cd507;
	ctx->sha256_h0[2] = 0x3070dd17;
	ctx->sha256_h0[3] = 0xf70e5939;
	ctx->sha256_h0[4] = 0xffc00b31;
	ctx->sha256_h0[5] = 0x68581511;
	ctx->sha256_h0[6] = 0x64f98fa7;
	ctx->sha256_h0[7] = 0xbefa4fa4;
}

void		set256_h0(t_sha224_256_ctx *ctx)
{
	ctx->sha256_h0[0] = 0x6A09E667;
	ctx->sha256_h0[1] = 0xBB67AE85;
	ctx->sha256_h0[2] = 0x3C6EF372;
	ctx->sha256_h0[3] = 0xA54FF53A;
	ctx->sha256_h0[4] = 0x510E527F;
	ctx->sha256_h0[5] = 0x9B05688C;
	ctx->sha256_h0[6] = 0x1F83D9AB;
	ctx->sha256_h0[7] = 0x5BE0CD19;
}

void	k1(uint32_t k[64])
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

void	k2(uint32_t k[64])
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

void	k_set(uint32_t k[64])
{
	k1(k);
	k2(k);
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

int			ft_sha224_256init(t_sha224_256_ctx *ctx, int sha_type, uint8_t *msg)
{
	int	i;

	i = 0;
	if (ctx && sha_type)
	{
		while (i < 8)
			ctx->abcdefgh[i++] = 0;
		i = 0;
		while (i < 64)
			ctx->w[i++] = 0;
		ctx->addtemp = 0;
		ctx->computed = 0;
		ctx->corrupted = 0;
		i = 0;
		while (i < 8)
			ctx->intermediate_hash[i++] = 0;
		ctx->length_high = 0;
		ctx->length_low = 0;
		ctx->message = ft_uchardup(msg);
		ctx->message_index = 0;
		ft_memset(ctx->msg_block, 0, 64);
		k_set(ctx->k);
		if (sha_type == 244)
			set224_h0(ctx);
		else if (sha_type == 256)
			set256_h0(ctx);
		return (FT_SHA_SUCESS);
	}
	return (FT_STATE_ERROR);
}

void	ft_sha224_256encode(uint32_t w[64], uint8_t mb[64])
{
	int	t;
	int	t4;

	t = 0;
	t4 = 0;
	while (t < 16)
	{
		w[t] = ((uint32_t)mb[t4] << 24) | \
			((uint32_t)mb[t4 + 1] << 16) | \
			((uint32_t)mb[t4 + 2] << 8) | \
			((uint32_t)mb[t4 + 3]);
		t++;
		t += 4;
	}
}

void	ft_sha224_256process_message(t_sha224_256_ctx *ctx)
{
	int			t;
	int			t4;
	uint32_t	tmp1;
	uint32_t	tmp2;

	t = -1;
	t4 = 0;
	if (ctx)
	{
		// ft_sha224_256encode(ctx->w, ctx->msg_block);
		while (t++ < 16)
		{
			ctx->w[t] = ((uint32_t)ctx->msg_block[t4] << 24) | \
				((uint32_t)ctx->msg_block[t4 + 1] << 16) | \
				((uint32_t)ctx->msg_block[t4 + 2] << 8) | \
				((uint32_t)ctx->msg_block[t4 + 3]);
			t4 += 4;
		}
		t = -1;
		while (t++ < 64)
			ctx->w[t] = SHA256_SIG1(ctx->w[t - 2] + ctx->w[t - 7] + \
				SHA256_SIG0(ctx->w[t - 15]) + ctx->w[t - 16]);
		t = -1;
		while (t++ < 8)
			ctx->abcdefgh[t] = ctx->intermediate_hash[t];
		t = 0;
		while (t < 64)
		{
			tmp1 = ctx->abcdefgh[7] + SHA256_SIG1(ctx->abcdefgh[4]) + \
				SHA_CH(ctx->abcdefgh[4], ctx->abcdefgh[5], ctx->abcdefgh[6]) \
				+ ctx->k[t] + ctx->w[t];
			tmp2 = SHA256_SIGMA0(ctx->abcdefgh[0]) + SHA_MAJ(ctx->abcdefgh[0], ctx->abcdefgh[1], ctx->abcdefgh[2]);
			ctx->abcdefgh[7] = ctx->abcdefgh[6];
			ctx->abcdefgh[6] = ctx->abcdefgh[5];
			ctx->abcdefgh[5] = ctx->abcdefgh[4];
			ctx->abcdefgh[4] = ctx->abcdefgh[3] + tmp1;
			ctx->abcdefgh[3] = ctx->abcdefgh[2];
			ctx->abcdefgh[2] = ctx->abcdefgh[1];
			ctx->abcdefgh[1] = ctx->abcdefgh[0];
			ctx->abcdefgh[0] = tmp1 + tmp2;
			t++;
		}
	}
}

void	ft_sha224_256finalize(t_sha224_256_ctx *context, uint8_t pad_byte)
{
	if (context && pad_byte)
	{
		//%s
	}
}

void	ft_sha224_256pad_message(t_sha224_256_ctx *context, uint8_t pad_byte)
{
	if (context && pad_byte)
	{
		//%s
	}
}

int		ft_sha224_256result_n(t_sha224_256_ctx *context, uint8_t md[], int hsize)
{
	if (context && md && hsize)
	{
		//%s
	}
	return (FT_SHA_SUCESS);
}

void	ft_sha256(const uint8_t *msg)
{
	t_sha224_256_ctx	context;

	ft_printf("sha256: %s\n", msg);
	ft_sha224_256init(&context, 256, (uint8_t *)msg);
	ft_sha224_256process_message(&context);

}
