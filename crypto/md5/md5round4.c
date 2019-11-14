/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5round4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:29:01 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/11 18:37:42 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	md5r4_1(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[0] += I(state[1], state[2], state[3]);
	state[0] += (x + so);
	state[0] = ROT_L(state[0], 6);
	state[0] += state[1];
}

void	md5r4_2(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[3] += I(state[0], state[1], state[2]);
	state[3] += (x + so);
	state[3] = ROT_L(state[3], 10);
	state[3] += state[0];
}

void	md5r4_3(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[2] += I(state[3], state[0], state[1]);
	state[2] += (x + so);
	state[2] = ROT_L(state[2], 15);
	state[2] += state[3];
}

void	md5r4_4(unsigned int state[4], unsigned int x, uint32_t so)
{
	state[1] += I(state[2], state[3], state[0]);
	state[1] += (x + so);
	state[1] = ROT_L(state[1], 21);
	state[1] += state[2];
}
