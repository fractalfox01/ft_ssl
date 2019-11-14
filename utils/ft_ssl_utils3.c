/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:05:24 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/13 18:10:41 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned char	*ft_ujoin(uint8_t *s1, uint8_t *s2, int i, size_t len1)
{
	unsigned char	*ptr;
	size_t			len2;

	if (s2)
	{
		len2 = ft_ustrlen((unsigned char *)s2);
		if (s1)
		{
			len1 = ft_ustrlen((unsigned char *)s1);
			len2 += len1;
		}
		ptr = ft_ustrnew((len2) + 1);
		if (s1)
		{
			while (++i < (int)len1)
				ptr[i] = s1[i];
		}
		len1 = 0;
		while (i < (int)(len2))
			ptr[i++] = s2[len1++];
		ptr[i] = '\0';
		ft_ustrdel(&s1);
		return (ptr);
	}
	return (NULL);
}
