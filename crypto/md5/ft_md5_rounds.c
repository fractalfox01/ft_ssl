/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_rounds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:25:58 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/29 20:27:11 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include "../../includes/ft_sha224_256.h"

void	ft_md5_round1(unsigned int state[4], unsigned int x[16])
{
	FF(state[0], state[1], state[2], state[3], x[0], 7, 0xd76aa478);
	FF(state[3], state[0], state[1], state[2], x[1], 12, 0xe8c7b756);
	FF(state[2], state[3], state[0], state[1], x[2], 17, 0x242070db);
	FF(state[1], state[2], state[3], state[0], x[3], 22, 0xc1bdceee);
	FF(state[0], state[1], state[2], state[3], x[4], 7, 0xf57c0faf);
	FF(state[3], state[0], state[1], state[2], x[5], 12, 0x4787c62a);
	FF(state[2], state[3], state[0], state[1], x[6], 17, 0xa8304613);
	FF(state[1], state[2], state[3], state[0], x[7], 22, 0xfd469501);
	FF(state[0], state[1], state[2], state[3], x[8], 7, 0x698098d8);
	FF(state[3], state[0], state[1], state[2], x[9], 12, 0x8b44f7af);
	FF(state[2], state[3], state[0], state[1], x[10], 17, 0xffff5bb1);
	FF(state[1], state[2], state[3], state[0], x[11], 22, 0x895cd7be);
	FF(state[0], state[1], state[2], state[3], x[12], 7, 0x6b901122);
	FF(state[3], state[0], state[1], state[2], x[13], 12, 0xfd987193);
	FF(state[2], state[3], state[0], state[1], x[14], 17, 0xa679438e);
	FF(state[1], state[2], state[3], state[0], x[15], 22, 0x49b40821);
}

void	ft_md5_round2(unsigned int state[4], unsigned int x[16])
{
	GG(state[0], state[1], state[2], state[3], x[1], 5, 0xf61e2562);
	GG(state[3], state[0], state[1], state[2], x[6], 9, 0xc040b340);
	GG(state[2], state[3], state[0], state[1], x[11], 14, 0x265e5a51);
	GG(state[1], state[2], state[3], state[0], x[0], 20, 0xe9b6c7aa);
	GG(state[0], state[1], state[2], state[3], x[5], 5, 0xd62f105d);
	GG(state[3], state[0], state[1], state[2], x[10], 9, 0x2441453);
	GG(state[2], state[3], state[0], state[1], x[15], 14, 0xd8a1e681);
	GG(state[1], state[2], state[3], state[0], x[4], 20, 0xe7d3fbc8);
	GG(state[0], state[1], state[2], state[3], x[9], 5, 0x21e1cde6);
	GG(state[3], state[0], state[1], state[2], x[14], 9, 0xc33707d6);
	GG(state[2], state[3], state[0], state[1], x[3], 14, 0xf4d50d87);
	GG(state[1], state[2], state[3], state[0], x[8], 20, 0x455a14ed);
	GG(state[0], state[1], state[2], state[3], x[13], 5, 0xa9e3e905);
	GG(state[3], state[0], state[1], state[2], x[2], 9, 0xfcefa3f8);
	GG(state[2], state[3], state[0], state[1], x[7], 14, 0x676f02d9);
	GG(state[1], state[2], state[3], state[0], x[12], 20, 0x8d2a4c8a);
}

void	ft_md5_round3(unsigned int state[4], unsigned int x[16])
{
	HH(state[0], state[1], state[2], state[3], x[5], 4, 0xfffa3942);
	HH(state[3], state[0], state[1], state[2], x[8], 11, 0x8771f681);
	HH(state[2], state[3], state[0], state[1], x[11], 16, 0x6d9d6122);
	HH(state[1], state[2], state[3], state[0], x[14], 23, 0xfde5380c);
	HH(state[0], state[1], state[2], state[3], x[1], 4, 0xa4beea44);
	HH(state[3], state[0], state[1], state[2], x[4], 11, 0x4bdecfa9);
	HH(state[2], state[3], state[0], state[1], x[7], 16, 0xf6bb4b60);
	HH(state[1], state[2], state[3], state[0], x[10], 23, 0xbebfbc70);
	HH(state[0], state[1], state[2], state[3], x[13], 4, 0x289b7ec6);
	HH(state[3], state[0], state[1], state[2], x[0], 11, 0xeaa127fa);
	HH(state[2], state[3], state[0], state[1], x[3], 16, 0xd4ef3085);
	HH(state[1], state[2], state[3], state[0], x[6], 23, 0x4881d05);
	HH(state[0], state[1], state[2], state[3], x[9], 4, 0xd9d4d039);
	HH(state[3], state[0], state[1], state[2], x[12], 11, 0xe6db99e5);
	HH(state[2], state[3], state[0], state[1], x[15], 16, 0x1fa27cf8);
	HH(state[1], state[2], state[3], state[0], x[2], 23, 0xc4ac5665);
}

void	ft_md5_round4(unsigned int state[4], unsigned int x[16])
{
	II(state[0], state[1], state[2], state[3], x[0], 6, 0xf4292244);
	II(state[3], state[0], state[1], state[2], x[7], 10, 0x432aff97);
	II(state[2], state[3], state[0], state[1], x[14], 15, 0xab9423a7);
	II(state[1], state[2], state[3], state[0], x[5], 21, 0xfc93a039);
	II(state[0], state[1], state[2], state[3], x[12], 6, 0x655b59c3);
	II(state[3], state[0], state[1], state[2], x[3], 10, 0x8f0ccc92);
	II(state[2], state[3], state[0], state[1], x[10], 15, 0xffeff47d);
	II(state[1], state[2], state[3], state[0], x[1], 21, 0x85845dd1);
	II(state[0], state[1], state[2], state[3], x[8], 6, 0x6fa87e4f);
	II(state[3], state[0], state[1], state[2], x[15], 10, 0xfe2ce6e0);
	II(state[2], state[3], state[0], state[1], x[6], 15, 0xa3014314);
	II(state[1], state[2], state[3], state[0], x[13], 21, 0x4e0811a1);
	II(state[0], state[1], state[2], state[3], x[4], 6, 0xf7537e82);
	II(state[3], state[0], state[1], state[2], x[11], 10, 0xbd3af235);
	II(state[2], state[3], state[0], state[1], x[2], 15, 0x2ad7d2bb);
	II(state[1], state[2], state[3], state[0], x[9], 21, 0xeb86d391);
}
