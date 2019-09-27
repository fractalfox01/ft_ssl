/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:50:31 by tvandivi          #+#    #+#             */
/*   Updated: 2019/09/24 11:16:10 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <limits.h>

int		get_md5_buffer(t_md5 *md5)
{
    static unsigned int *tab[OPEN_MAX];
    int ret;

    ret = 0;
    while (ft_strlen((char *)md5->message) > 448)
    {
        
    }
    return (ret);
}
