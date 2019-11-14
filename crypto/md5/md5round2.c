/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5round2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:31:47 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/11 18:37:43 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	md5r2_1(uint32_t state[4], uint32_t x, uint32_t so)
{
	state[0] += G(state[1], state[2], state[3]);
	state[0] += (x + so);
	state[0] = ROT_L(state[0], 5);
	state[0] += state[1];
}

void	md5r2_2(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[3] += G(state[0], state[1], state[2]);
	state[3] += (x + so);
	state[3] = ROT_L(state[3], 9);
	state[3] += state[0];
}

void	md5r2_3(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[2] += G(state[3], state[0], state[1]);
	state[2] += (x + so);
	state[2] = ROT_L(state[2], 14);
	state[2] += state[3];
}

void	md5r2_4(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[1] += G(state[2], state[3], state[0]);
	state[1] += (x + so);
	state[1] = ROT_L(state[1], 20);
	state[1] += state[2];
}
