/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:57:21 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/13 18:08:18 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

/*
** ft_getopt returns (0) for md5 and (1) for sha256
*/

void			ft_ssl_message(char *invalid)
{
	ft_printf(FT_RED);
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", invalid);
	ft_printf(FT_GREEN);
	ft_printf("Standard commands:\n\nMessage Digest commands:\nmd5\n");
	ft_printf("sha256\n\n");
	ft_printf("Cipher commands:\n");
	ft_printf(FT_END_ATTR);
}

unsigned char	*read_from_stdin(t_getopt *glb_opt)
{
	int				b;
	unsigned char	*msg;

	b = 0;
	msg = ft_ustrnew(1);
	msg[0] = '\0';
	while ((b = get_n_char(0, &glb_opt->chunk, BUF_SIZE)) > 0)
	{
		msg = ft_ujoin(msg, glb_opt->chunk, -1, 0);
		ft_ustrdel(&glb_opt->chunk);
	}
	close(0);
	return (msg);
}

unsigned char	*try_open(t_getopt *glb_opt, unsigned char *file)
{
	int			b;
	int			fd;
	uint8_t		*msg;

	b = 0;
	fd = 0;
	if (glb_opt->skip == 1)
		return (NULL);
	fd = open((const char *)file, O_APPEND, O_RDONLY);
	if (fd >= 0)
	{
		msg = ft_ustrnew(1);
		while ((b = get_n_char(fd, &glb_opt->chunk, BUF_SIZE)) > 0)
		{
			msg = ft_ujoin(msg, glb_opt->chunk, -1, 0);
			ft_ustrdel(&glb_opt->chunk);
		}
		close(fd);
		return (msg);
	}
	return (NULL);
}

uint8_t			*ft_ssl_preform_action(t_getopt *glb_opt, t_opt *opt)
{
	if (glb_opt->opt_choice == 1)
		return (ft_md5(opt->message));
	else if (glb_opt->opt_choice == 2)
		return (ft_sha256(opt->message));
	return (NULL);
}

char			*set_type(int size)
{
	if (size == 16)
		return ("MD5");
	else
		return ("SHA256");
	return (NULL);
}
