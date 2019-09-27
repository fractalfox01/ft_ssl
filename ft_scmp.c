/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:12:50 by tvandivi          #+#    #+#             */
/*   Updated: 2019/09/23 19:33:45 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "ft_ssl.h"

int	ft_scmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				diff;
	int				i;
	int				j;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	diff = *str1 - *str2;
	i = 0;
	j = 0;
	while (diff == 0)
	{
		diff += str1[i] - str2[j];
		if (diff != 0 || (str1[i] == '\0' && str2[j] == '\0'))
			return (diff);
		if (str1[i] != '\0')
			i++;
		if (str2[j] != '\0')
			j++;
	}
	return (diff);
}
