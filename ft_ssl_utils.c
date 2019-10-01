/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:22:06 by tvandivi          #+#    #+#             */
/*   Updated: 2019/09/30 09:47:20 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_opt_init(t_getopt *glb_opt)
{
	ft_bzero(glb_opt->flag, 2);
	glb_opt->c = 0;
	glb_opt->i = 1;
	glb_opt->ft_md5 = (ft_uchar *)ft_strdup("md5");
	glb_opt->ft_sha256 = (ft_uchar *)ft_strdup("sha256");
}

int	ssl_set_flag(t_getopt *glb_opt, char *s)
{
	if (ft_strcmp(s, "-p") == 0)
		glb_opt->flag[0] = 'p';
	if (ft_strcmp(s, "-q") == 0)
		glb_opt->flag[0] = 'q';
	if (ft_strcmp(s, "-r") == 0)
		glb_opt->flag[0] = 'r';
	if (ft_strcmp(s, "-s") == 0)
		glb_opt->flag[0] = 's';
	if (glb_opt->flag[0])
		return (1);
	ft_printf(FT_RED"Unrecognized flag value: %s\n"FT_END_ATTR, s);
	return (0);
}

/*
** ft_getopt returns (0) for md5 and (1) for sha256
*/

int		ft_getopt(int ac, char **av, t_getopt *glb_opt)
{
	if (ac == 4)
	{
		if (ssl_set_flag(glb_opt, av[1]) == 0)
			return (-1);
		if (ft_ustrcmp((const ft_uchar *)av[2], glb_opt->ft_md5) == 0)
			return (0);
		if (ft_ustrcmp((const ft_uchar *)av[2], glb_opt->ft_sha256) == 0)
			return (1);
	}
	else if (ac == 3)
	{
		if (ft_ustrcmp((const ft_uchar *)av[1], glb_opt->ft_md5) == 0)
			return (0);
		if (ft_ustrcmp((const ft_uchar *)av[1], glb_opt->ft_sha256) == 0)
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
	ft_strdel((char **)&(glb_opt->ft_md5));
	ft_strdel((char **)&(glb_opt->ft_sha256));
}

void	ft_ssl_preform_action(t_getopt *glb_opt, int ac, char **av)
{
	ft_uchar	md[ft_strlen(av[2])];
	int			i;
	int			a;

	i = 2;
	if ((a = glb_opt->flag[0]))
		i = 3;
	if (glb_opt->c == 0)
		ft_md5((ft_uchar *)av[i], ft_strlen(av[i]), (ft_uchar *)&md);
	else if (glb_opt->c == 1)
		ft_printf("sha256 not handled\n");
	else if (a == 1 || glb_opt->c == -1)
		ft_ssl_message(av[i - 1]);
}
