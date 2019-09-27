/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:22:06 by tvandivi          #+#    #+#             */
/*   Updated: 2019/09/24 10:49:29 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_opt_init(t_getopt *glb_opt)
{
	glb_opt->c = 0;
	glb_opt->i = 1;
	glb_opt->ft_md5 = ft_strdup("md5");
	glb_opt->ft_sha256 = ft_strdup("sha256");
}

int		ft_getopt(int ac, char **av, t_getopt *glb_opt)
{
	if (glb_opt->i < ac)
	{
		if (ft_scmp(av[1], glb_opt->ft_md5) == 0)
			return (0);
		if (ft_scmp(av[1], glb_opt->ft_sha256) == 0)
			return (1);
	}
	return (-1);
}

void	ft_ssl_message(char *invalid)
{
	ft_printf(FT_RED);
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", invalid);
	ft_printf(FT_GREEN);
	ft_printf("Standard commands:\n\nMessage Digest commands:\nmd5\n \
			sha256\n\n");
	ft_printf("Cipher commands:\n");
	ft_printf(FT_END_ATTR);
}

void	ft_ssl_free_optins(t_getopt *glb_opt)
{
	ft_strdel(&(glb_opt->ft_md5));
	ft_strdel(&(glb_opt->ft_sha256));
}

void	ft_ssl_preform_action(t_getopt *glb_opt, int ac, char **av)
{
	if (glb_opt->c == 0)
		ft_md5(av[2], ft_strlen(av[2]));
	else if (glb_opt->c == 1)
		ft_sha256(av[2], ft_strlen(av[2]));
	else
		ft_ssl_message(av[1]);
}
