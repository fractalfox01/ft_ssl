/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:22:06 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/04 16:54:32 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_opt_init(t_getopt *glb_opt)
{
	ft_bzero(glb_opt->flag, 5);
	glb_opt->c = 0;
	glb_opt->i = 1;
	glb_opt->chunk = NULL;
	glb_opt->message = ft_strdup(" ");
	glb_opt->ft_md5 = (ft_uchar *)ft_strdup("md5");
	glb_opt->ft_sha256 = (ft_uchar *)ft_strdup("sha256");
}

int	ssl_set_flag(t_getopt *glb_opt, char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s) - 1;
	i = 0;
	if (s[0] == '-')
	{
		while (len > 0)
		{
			if (s[len] == 'p')
				glb_opt->flag[i] = 'p';
			else if (s[len] == 'q')
				glb_opt->flag[i] = 'q';
			else if (s[len] == 'r')
				glb_opt->flag[i] = 'r';
			else if (s[len] == 's')
				glb_opt->flag[i] = 's';
			i++;
			len--;
		}
		if (glb_opt->flag[0])
			return (1);
		ft_printf(FT_RED"Unrecognized flag value: %s\n"FT_END_ATTR, s);
	}
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
		if (ssl_set_flag(glb_opt, av[1]) == 1)
		{
			if (!(!(ft_strchr((const char *)glb_opt->flag, 'p'))))
			{
				if (ft_ustrcmp((const ft_uchar *)av[2], glb_opt->ft_md5) == 0)
					return (0);
			}
		}
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

char	*read_from_stdin(t_getopt *glb_opt)
{
	int		b;
	char	*msg;

	b = 0;
	msg = ft_strnew(2);
	while ((b = get_n_char(0, &glb_opt->chunk, BUF_SIZE)) > 0)
	{
		msg = ft_strjoin(msg, glb_opt->chunk);
		ft_strdel(&glb_opt->chunk);
	}
	msg[ft_strlen(msg) - 1] = '\0';
	close(0);
	return (msg);
}

char	*try_open(t_getopt *glb_opt, char *file)
{
	int			b;
	int			fd;
	char		*msg;

	b = 0;
	fd = 0;
	msg = ft_strnew(2);
	fd = open(file, O_APPEND, O_RDONLY);
	if (fd > 0)
	{
		while ((b = get_n_char(fd, &glb_opt->chunk, BUF_SIZE)) > 0)
		{
			msg = ft_strjoin(msg, glb_opt->chunk);
			ft_strdel(&glb_opt->chunk);
		}
		msg[ft_strlen(msg) - 1] = '\0';
		close(fd);
		return (msg);
	}
	return (NULL);
}

void	read_and_parse(t_getopt *glb_opt, char **av, ft_uchar md[], int i)
{
	char	*msg;

	if (!(!(ft_strchr((const char *)glb_opt->flag, 'p'))))
	{
		msg = read_from_stdin(glb_opt);
		if (!(ft_strchr((const char *)glb_opt->flag, 'q')))
			ft_printf("MD5 (%s) = ", av[i]);
		ft_md5((const ft_uchar *)msg, ft_strlen((char *)msg), (ft_uchar *)&md);
	}
	else
	{
		if (!(!(msg = try_open(glb_opt, av[i]))))
		{
			if (!(ft_strchr((const char *)glb_opt->flag, 'q')))
				ft_printf("%s\n", msg);
			ft_md5((const ft_uchar *)msg, ft_strlen(msg), (ft_uchar *)&md);
		}
		else
		{
			if (!(ft_strchr((const char *)glb_opt->flag, 'q')))
				ft_printf("%s\n", av[i]);
			ft_md5((ft_uchar *)av[i], ft_strlen(av[i]), (ft_uchar *)&md);
		}
	}
}

void	ft_ssl_preform_action(t_getopt *glb_opt, int ac, char **av)
{
	ft_uchar	md[ft_strlen(av[2])];
	int			i;
	int			a;

	i = 2;
	if ((a = glb_opt->flag[0]))
	{
		if (!(ft_strchr((const char *)glb_opt->flag, 'p')))
			i = 2;
		else
			i = 3;
	}
	if (glb_opt->c == 0)
	{
		read_and_parse(glb_opt, av, md, i);
	}
	else if (glb_opt->c == 1)
	{
		ft_printf("sha256 not handled\n");
	}
	else if (a == 1 || glb_opt->c == -1)
		ft_ssl_message(av[i - 1]);
}
