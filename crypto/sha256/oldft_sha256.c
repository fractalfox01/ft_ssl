/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:29:59 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/29 16:49:21 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include "../../includes/ft_sha224_256.h"

// int		ft_sha224_256addlen(t_sha224_256_ctx *context, uint32_t length)
// {
// 	context->addtemp = context->length_low;
// 	context->length_low += length;
// 	context->corrupted = context->length_low;
// 	if ((context->corrupted < context->addtemp) && (++context->length_high))
// 		return (FT_SHA_TOO_LONG);
// 	return (context->corrupted);
// }

// int		ft_sha256input(t_sha224_256_ctx *context, uint8_t *msg, uint32_t length)
// {
// 	if (context && msg)
// 	{
// 		while (length--)
// 		{
// 			context->message[context->message_index++] = *msg;
// 			if ((ft_sha224_256addlen(context, 8) == FT_SHA_SUCESS) && (context->message_index == FT_SHA256MSIZE))
// 				ft_sha224_256process_message(context);
// 			msg++;
// 		}
// 	}
// 	return (context->corrupted);
// }

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
		i = 0;
		while (i < 8)
		{
			ctx->intermediate_hash[i] = ctx->sha256_h0[i];
			i++;
		}
		return (FT_SHA_SUCESS);
	}
	return (FT_STATE_ERROR);
}

// void	ft_sha224_256process_messag(t_sha224_256_ctx *ctx)
// {
// 	int			t;
// 	int			t4;
// 	uint32_t	tmp1;
// 	uint32_t	tmp2;

// 	t = -1;
// 	t4 = 0;
// 	if (ctx)
// 	{
// 		while (++t < 16)
// 		{
// 			ctx->w[t] = ((uint32_t)ctx->msg_block[t4] << 24) | \
// 						((uint32_t)ctx->msg_block[t4 + 1] << 16) | \
// 						((uint32_t)ctx->msg_block[t4 + 2] << 8) | \
// 						((uint32_t)ctx->msg_block[t4 + 3] << 0);
// 			t4 += 4;
// 		}
// 		t = -1;
// 		while (++t < 64)
// 			ctx->w[t] = SHA256_SIG1(ctx->w[t - 2] + ctx->w[t - 7] + \
// 					SHA256_SIG0(ctx->w[t - 15]) + ctx->w[t - 16]);
// 		t = -1;
// 		while (++t < 8)
// 			ctx->abcdefgh[t] = ctx->intermediate_hash[t];
// 		t = 0;
// 		while (t < 64)
// 		{
// 			tmp1 = ctx->abcdefgh[7] + SHA256_SIG1(ctx->abcdefgh[4]) + \
// 				SHA_CH(ctx->abcdefgh[4], ctx->abcdefgh[5], \
// 					ctx->abcdefgh[6]) + ctx->k[t] + ctx->w[t];
// 			tmp2 = SHA256_SIGMA0(ctx->abcdefgh[0]) + SHA_MAJ(ctx->abcdefgh[0], \
// 					ctx->abcdefgh[1], ctx->abcdefgh[2]);
// 			ctx->abcdefgh[7] = ctx->abcdefgh[6];
// 			ctx->abcdefgh[6] = ctx->abcdefgh[5];
// 			ctx->abcdefgh[5] = ctx->abcdefgh[4];
// 			ctx->abcdefgh[4] = ctx->abcdefgh[3] + tmp1;
// 			ctx->abcdefgh[3] = ctx->abcdefgh[2];
// 			ctx->abcdefgh[2] = ctx->abcdefgh[1];
// 			ctx->abcdefgh[1] = ctx->abcdefgh[0];
// 			ctx->abcdefgh[0] = tmp1 + tmp2;
// 			t++;
// 		}
// 		ctx->intermediate_hash[0] += ctx->abcdefgh[0];
// 		ctx->intermediate_hash[1] += ctx->abcdefgh[1];
// 		ctx->intermediate_hash[2] += ctx->abcdefgh[2];
// 		ctx->intermediate_hash[3] += ctx->abcdefgh[3];
// 		ctx->intermediate_hash[4] += ctx->abcdefgh[4];
// 		ctx->intermediate_hash[5] += ctx->abcdefgh[5];
// 		ctx->intermediate_hash[6] += ctx->abcdefgh[6];
// 		ctx->intermediate_hash[7] += ctx->abcdefgh[7];
// 		ctx->message_index = 0;
// 	}
// }

void	sha256encode(unsigned char digest[32], unsigned int state[8], unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	// ((uint32_t)buf[t4] << 24) | \
	// ((uint32_t)buf[t4 + 1] << 16) | \
	// ((uint32_t)buf[t4 + 2] << 8) | \
	// ((uint32_t)buf[t4 + 3] << 0);
	while (j < len)
	{
		digest[j] = (unsigned char)((state[i] >> 24) & 0xff);
		digest[j + 1] = (unsigned char)((state[i] >> 16) & 0xff);
		digest[j + 2] = (unsigned char)((state[i] >> 8) & 0xff);
		digest[j + 3] = (unsigned char)((state[i] >> 0) & 0xff);
		i++;
		j += 4;
	}
}

void	sha256_final(t_sha224_256_ctx *context, uint8_t *pad_byte)
{
	unsigned char	bits[32];
	unsigned char	padding[64];
	unsigned int	index;
	unsigned int	padlen;

	ft_memset(padding, 0, 64);
	padding[0] = 0x80;
	ft_memset(bits, 0, 32);
	sha256encode();
}

void	ft_sha224_256pad_message(t_sha224_256_ctx *context, uint8_t *pad_byte)
{
	if (context->message_index >= (FT_SHA256MSIZE - 8))
	{
		context->msg_block[context->message_index++] = pad_byte;
		while (context->message_index < FT_SHA256MSIZE)
			context->msg_block[context->message_index++] = 0;
		sha256_transform(context, context->msg_block);
	}
	else
		context->msg_block[context->message_index++] = pad_byte;
	while (context->message_index < (FT_SHA256MSIZE - 8))
		context->msg_block[context->message_index++] = 0;
	context->msg_block[56] = (uint8_t)(context->length_high >> 24);
	context->msg_block[57] = (uint8_t)(context->length_high >> 16);
	context->msg_block[58] = (uint8_t)(context->length_high >> 8);
	context->msg_block[59] = (uint8_t)(context->length_high);
	context->msg_block[60] = (uint8_t)(context->length_low >> 24);
	context->msg_block[61] = (uint8_t)(context->length_low >> 16);
	context->msg_block[62] = (uint8_t)(context->length_low >> 8);
	context->msg_block[63] = (uint8_t)(context->length_low);
	sha256_transform(context, context->msg_block);
}

// int		ft_sha224_256reset(t_sha224_256_ctx *ctx, uint32_t *h0)
// {
// 	int	i;

// 	i = 0;
// 	if (!ctx)
// 		return (FT_SHA_NULL);
// 	ctx->length_high = 0;
// 	ctx->length_low = 0;
// 	while (i < 8)
// 		ctx->intermediate_hash[i] = h0[i];
// 	ctx->computed = 0;
// 	ctx->corrupted = FT_SHA_SUCESS;
// 	return (FT_SHA_SUCESS);
// }

// int		ft_sha256finalbits(t_sha224_256_ctx *ctx, uint8_t msg_bits, uint32_t len)
// {
// 	static uint8_t masks[8];
// 	static uint8_t markbit[8];

// 	masks[0] = 0b00000000;
// 	masks[1] = 0b10000000;
// 	masks[2] = 0b11000000;
// 	masks[3] = 0b11100000;
// 	masks[4] = 0b11110000;
// 	masks[5] = 0b11111000;
// 	masks[6] = 0b11111100;
// 	masks[7] = 0b11111110;
// 	markbit[0] = 0b10000000;
// 	markbit[1] = 0b01000000;
// 	markbit[2] = 0b00100000;
// 	markbit[3] = 0b00010000;
// 	markbit[4] = 0b00001000;
// 	markbit[5] = 0b00000100;
// 	markbit[6] = 0b00000010;
// 	markbit[7] = 0b00000001;
// 	if (!(ctx))
// 		return (FT_SHA_NULL);
// 	if (!len)
// 		return (FT_SHA_SUCESS);
// 	if (ctx->corrupted)
// 		return (ctx->corrupted);
// 	if (ctx->computed)
// 	{
// 		ctx->corrupted = FT_STATE_ERROR;
// 		return (ctx->corrupted);
// 	}
// 	if (len >= 8)
// 	{
// 		ctx->corrupted = FT_BAD_PARAM;
// 		return (ctx->corrupted);
// 	}
// 	ft_sha224_256addlen(ctx, len);
// 	ft_sha224_256finalize(ctx, (uint8_t)(msg_bits & masks[len]) | markbit[len]);
// }

// int		ft_sha224_256result_n(t_sha224_256_ctx *context, uint8_t md[], int hsize)
// {
// 	int	i;

// 	i = 0;
// 	if (!context)
// 		return (FT_SHA_NULL);
// 	if (!md)
// 		return (FT_SHA_NULL);
// 	if (context->corrupted)
// 		return (context->corrupted);
// 	if (context->computed)
// 		ft_sha224_256finalize(context, 0x80);
// 	while (i < hsize)
// 		md[i] = (uint8_t)(context->intermediate_hash[i >> 2] >> 8 * (3 - (i & 0x03)));
// 	return (FT_SHA_SUCESS);
// }
// void	sha256_final(unsigned char digest[32], t_sha224_256_ctx *context)
// {
// 	unsigned char	bits[8];
// 	unsigned
// }

void	sha256_transform(t_sha224_256_ctx *ctx, unsigned char buf[64])
{
	int			t;
	int			t4;
	uint32_t	tmp1;
	uint32_t	tmp2;

	t = -1;
	t4 = 0;
	if (ctx)
	{
		while (++t < 16)
		{
			ctx->w[t] = ((uint32_t)buf[t4] << 24) | \
						((uint32_t)buf[t4 + 1] << 16) | \
						((uint32_t)buf[t4 + 2] << 8) | \
						((uint32_t)buf[t4 + 3] << 0);
			t4 += 4;
		}
		t = -1;
		while (++t < 64)
			ctx->w[t] = SHA256_SIG1(ctx->w[t - 2] + ctx->w[t - 7] + \
					SHA256_SIG0(ctx->w[t - 15]) + ctx->w[t - 16]);
		t = -1;
		while (++t < 8)
			ctx->abcdefgh[t] = ctx->intermediate_hash[t];
		t = 0;
		while (t < 64)
		{
			tmp1 = ctx->abcdefgh[7] + SHA256_SIG1(ctx->abcdefgh[4]) + \
				SHA_CH(ctx->abcdefgh[4], ctx->abcdefgh[5], \
					ctx->abcdefgh[6]) + ctx->k[t] + ctx->w[t];
			tmp2 = SHA256_SIGMA0(ctx->abcdefgh[0]) + SHA_MAJ(ctx->abcdefgh[0], \
					ctx->abcdefgh[1], ctx->abcdefgh[2]);
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
		ctx->intermediate_hash[0] += ctx->abcdefgh[0];
		ctx->intermediate_hash[1] += ctx->abcdefgh[1];
		ctx->intermediate_hash[2] += ctx->abcdefgh[2];
		ctx->intermediate_hash[3] += ctx->abcdefgh[3];
		ctx->intermediate_hash[4] += ctx->abcdefgh[4];
		ctx->intermediate_hash[5] += ctx->abcdefgh[5];
		ctx->intermediate_hash[6] += ctx->abcdefgh[6];
		ctx->intermediate_hash[7] += ctx->abcdefgh[7];
		ctx->message_index = 0;
	}
}

void	sha256_update(t_sha224_256_ctx *context, uint8_t *input, uint32_t mlen)
{
	unsigned int	i;
	unsigned int	index;
	unsigned int	partlen;

	index = 0;
	while (index < 3)
		context->count[index++] = 0;
	index = ((unsigned int)(context->count[0] >> 3) & 63);
	if ((context->count[0] += (unsigned int)(mlen << 3)) < (unsigned int)(mlen << 3))
		context->count[1]++;
	context->count[1] += (unsigned int)(mlen >> 29);
	partlen = 64 - index;
	if (mlen >= partlen)
	{
		ft_memcpy((void *)(context->msg_block + index), input, partlen);
		i = partlen;
		sha256_transform(context, context->msg_block);
		while ((i + 63) < mlen)
		{
			sha256_transform(context, (context->message + i));
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memcpy((unsigned char *)(context->message + index), (unsigned char *)(input + i), mlen - i);
}

void	ft_sha256(const uint8_t *msg)
{
	t_sha224_256_ctx	context;
	unsigned char		digest[32];
	int					i;

	i = 7;
	ft_printf("sha256: %s\n", msg);
	ft_sha224_256init(&context, 256, (uint8_t *)msg);
	sha256_update(&context, (uint8_t *)msg, ft_ustrlen((uint8_t *)msg));
	sha256_final(&context, digest);
	while (i < 8)
		ft_printf("%02x", context.intermediate_hash[i++]);
	ft_printf("\n");
}
