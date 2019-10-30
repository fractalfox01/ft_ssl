/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha224.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:25:20 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/29 20:53:57 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include "../../includes/ft_sha224_256.h"

void	ft_sha224(unsigned char *msg)
{
	unsigned char	md[64];
	int				i;

	i = 0;
	while (i < 64)
		md[i++] = 0;
	ft_printf("sha224: %s\n", msg);
}
