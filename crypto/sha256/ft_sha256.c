/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:29:59 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/24 15:00:58 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include "../../includes/ft_sha224_256.h"



void	ft_sha256(const unsigned char *msg)
{
	unsigned char	md[64];
	int				i;

	i = 0;
	while (i < 64)
		md[i++] = 0;
	ft_printf("sha256: %s\n", msg);
}
