/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:07:20 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/09 11:13:10 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	md5_clearout(t_md5_ctx *context)
{
	context->a = 0;
	context->b = 0;
	context->c = 0;
	context->d = 0;
}

void	md5_init(t_md5_ctx *context)
{
	int	i;

	i = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
	context->a = 0;
	context->b = 0;
	context->c = 0;
	context->d = 0;
	while (i < 2)
		context->count[i++] = 0;
	i = 0;
	while (i < 64)
		context->buf[i++] = '\0';
}
