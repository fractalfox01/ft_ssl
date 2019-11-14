/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:14:34 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/11 18:48:05 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_sha224_256.h"

static void	sha256_proccess_chunk(t_256ctx *ctx, uint8_t buf[64])
{
	int	i;

	i = 0;
	while (i < 3)
		ctx->tmp[i++] = 0;
	i = 0;
	while (i < 8)
		ctx->abc[i++] = 0;
	i = 0;
	while (i < 64)
		ctx->w[i++] = 0;
	i = 0;
	ft_sha256_decode(ctx->w, buf);
	while (i < 8)
	{
		ctx->abc[i] = ctx->sha256_h0[i];
		i++;
	}
}

void		ft_sha256_transform(t_256ctx *ctx, uint8_t buf[64])
{
	sha256_proccess_chunk(ctx, buf);
	while (ctx->tmp[0] < 64)
	{
		ctx->tmp[1] = ctx->abc[7] + SHA256_SIGMA1(ctx->abc[4]) + \
			SHA_CH(ctx->abc[4], ctx->abc[5], \
		ctx->abc[6]) + ctx->k[ctx->tmp[0]] + ctx->w[ctx->tmp[0]];
		ctx->tmp[2] = SHA256_SIGMA0(ctx->abc[0]) + \
			SHA_MAJ(ctx->abc[0], ctx->abc[1], ctx->abc[2]);
		ctx->abc[7] = ctx->abc[6];
		ctx->abc[6] = ctx->abc[5];
		ctx->abc[5] = ctx->abc[4];
		ctx->abc[4] = ctx->abc[3] + ctx->tmp[1];
		ctx->abc[3] = ctx->abc[2];
		ctx->abc[2] = ctx->abc[1];
		ctx->abc[1] = ctx->abc[0];
		ctx->abc[0] = ctx->tmp[1] + ctx->tmp[2];
		ctx->tmp[0]++;
	}
	ctx->tmp[0] = 0;
	while (ctx->tmp[0] < 8)
	{
		ctx->sha256_h0[ctx->tmp[0]] += ctx->abc[ctx->tmp[0]];
		ctx->tmp[0]++;
	}
}
