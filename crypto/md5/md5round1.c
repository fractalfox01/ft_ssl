/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5round1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:31:44 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/11 18:37:43 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	md5r1_1(uint32_t state[4], uint32_t x, uint32_t so)
{
	state[0] += F(state[1], state[2], state[3]);
	state[0] += (x + so);
	state[0] = ROT_L(state[0], 7);
	state[0] += state[1];
}

void	md5r1_2(unsigned int state[4], uint32_t x, uint32_t so)
{
	state[3] += F(state[0], state[1], state[2]);
	state[3] += x + so;
	state[3] = ROT_L(state[3], 12);
	state[3] += state[0];
}

void	md5r1_3(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[2] += F(state[3], state[0], state[1]);
	state[2] += x + so;
	state[2] = ROT_L(state[2], 17);
	state[2] += state[3];
}

void	md5r1_4(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[1] += F(state[2], state[3], state[0]);
	state[1] += x + so;
	state[1] = ROT_L(state[1], 22);
	state[1] += state[2];
}
