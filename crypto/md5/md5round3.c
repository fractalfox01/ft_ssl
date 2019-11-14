/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5round3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:31:49 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/11 18:37:43 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	md5r3_1(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[0] += H(state[1], state[2], state[3]);
	state[0] += (x + so);
	state[0] = ROT_L(state[0], 4);
	state[0] += state[1];
}

void	md5r3_2(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[3] += H(state[0], state[1], state[2]);
	state[3] += (x + so);
	state[3] = ROT_L(state[3], 11);
	state[3] += state[0];
}

void	md5r3_3(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[2] += H(state[3], state[0], state[1]);
	state[2] += (x + so);
	state[2] = ROT_L(state[2], 16);
	state[2] += state[3];
}

void	md5r3_4(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[1] += H(state[2], state[3], state[0]);
	state[1] += (x + so);
	state[1] = ROT_L(state[1], 23);
	state[1] += state[2];
}
