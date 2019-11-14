/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:03:56 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/11 18:33:50 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	ft_md5_round1(unsigned int state[4], unsigned int x[16])
{
	md5r1_1(state, x[0], 0xd76aa478);
	md5r1_2(state, x[1], 0xe8c7b756);
	md5r1_3(state, x[2], 0x242070db);
	md5r1_4(state, x[3], 0xc1bdceee);
	md5r1_1(state, x[4], 0xf57c0faf);
	md5r1_2(state, x[5], 0x4787c62a);
	md5r1_3(state, x[6], 0xa8304613);
	md5r1_4(state, x[7], 0xfd469501);
	md5r1_1(state, x[8], 0x698098d8);
	md5r1_2(state, x[9], 0x8b44f7af);
	md5r1_3(state, x[10], 0xffff5bb1);
	md5r1_4(state, x[11], 0x895cd7be);
	md5r1_1(state, x[12], 0x6b901122);
	md5r1_2(state, x[13], 0xfd987193);
	md5r1_3(state, x[14], 0xa679438e);
	md5r1_4(state, x[15], 0x49b40821);
}

void	ft_md5_round2(unsigned int state[4], unsigned int x[16])
{
	md5r2_1(state, x[1], 0xf61e2562);
	md5r2_2(state, x[6], 0xc040b340);
	md5r2_3(state, x[11], 0x265e5a51);
	md5r2_4(state, x[0], 0xe9b6c7aa);
	md5r2_1(state, x[5], 0xd62f105d);
	md5r2_2(state, x[10], 0x2441453);
	md5r2_3(state, x[15], 0xd8a1e681);
	md5r2_4(state, x[4], 0xe7d3fbc8);
	md5r2_1(state, x[9], 0x21e1cde6);
	md5r2_2(state, x[14], 0xc33707d6);
	md5r2_3(state, x[3], 0xf4d50d87);
	md5r2_4(state, x[8], 0x455a14ed);
	md5r2_1(state, x[13], 0xa9e3e905);
	md5r2_2(state, x[2], 0xfcefa3f8);
	md5r2_3(state, x[7], 0x676f02d9);
	md5r2_4(state, x[12], 0x8d2a4c8a);
}

void	ft_md5_round3(unsigned int state[4], unsigned int x[16])
{
	md5r3_1(state, x[5], 0xfffa3942);
	md5r3_2(state, x[8], 0x8771f681);
	md5r3_3(state, x[11], 0x6d9d6122);
	md5r3_4(state, x[14], 0xfde5380c);
	md5r3_1(state, x[1], 0xa4beea44);
	md5r3_2(state, x[4], 0x4bdecfa9);
	md5r3_3(state, x[7], 0xf6bb4b60);
	md5r3_4(state, x[10], 0xbebfbc70);
	md5r3_1(state, x[13], 0x289b7ec6);
	md5r3_2(state, x[0], 0xeaa127fa);
	md5r3_3(state, x[3], 0xd4ef3085);
	md5r3_4(state, x[6], 0x4881d05);
	md5r3_1(state, x[9], 0xd9d4d039);
	md5r3_2(state, x[12], 0xe6db99e5);
	md5r3_3(state, x[15], 0x1fa27cf8);
	md5r3_4(state, x[2], 0xc4ac5665);
}

void	ft_md5_round4(unsigned int state[4], unsigned int x[16])
{
	md5r4_1(state, x[0], 0xf4292244);
	md5r4_2(state, x[7], 0x432aff97);
	md5r4_3(state, x[14], 0xab9423a7);
	md5r4_4(state, x[5], 0xfc93a039);
	md5r4_1(state, x[12], 0x655b59c3);
	md5r4_2(state, x[3], 0x8f0ccc92);
	md5r4_3(state, x[10], 0xffeff47d);
	md5r4_4(state, x[1], 0x85845dd1);
	md5r4_1(state, x[8], 0x6fa87e4f);
	md5r4_2(state, x[15], 0xfe2ce6e0);
	md5r4_3(state, x[6], 0xa3014314);
	md5r4_4(state, x[13], 0x4e0811a1);
	md5r4_1(state, x[4], 0xf7537e82);
	md5r4_2(state, x[11], 0xbd3af235);
	md5r4_3(state, x[2], 0x2ad7d2bb);
	md5r4_4(state, x[9], 0xeb86d391);
}

void	md5_transform(t_md5_ctx *context, unsigned char buf[64])
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
