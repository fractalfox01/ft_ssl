/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:22:06 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/23 15:53:00 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

t_opt	*newsslnode(void)
{
	t_opt	*opt;
	int		i;

	i = 0;
	opt = (t_opt *)malloc(sizeof(t_opt) * 1);
	opt->message = NULL; // original message read in
	while (i < 64)
		opt->chunk[i++] = '\0'; // 64 bit chunk; used while proccessing chunks through algo
	i = 0;
	while (i < 2)
		opt->cmdarg[i++] = '\0'; // command type; -p -s (pipe, string, file)?
	opt->next = NULL;
	return (opt);
}

void	ft_opt_init(t_getopt *glb_opt)
{
	glb_opt->success = 1;
	glb_opt->end = 1;
	glb_opt->skip = 0;
	glb_opt->opt_choice = 0;
	glb_opt->opt_total = 0;
	glb_opt->opt_i = 1;
	glb_opt->chunk = NULL;  // var used while reading in get_n_char
	glb_opt->opt_quiet = 0;
	glb_opt->opt_reverse = 0;
	glb_opt->opt = newsslnode();
}

t_opt	*get_opt(t_getopt *glb_opt)
{
	t_opt	*opt;
	int		i;

	i = 0;
	opt = glb_opt->opt;
	while (i < glb_opt->opt_total)
	{
		opt = opt->next;
		i++;
	}
	return (opt);
}

/*
 ** ft_getopt returns (0) for md5 and (1) for sha256
 */

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

unsigned char	*read_from_stdin(t_getopt *glb_opt)
{
	int				b;
	unsigned char	*msg;

	b = 0;
	msg = ft_ustrnew(1);
	msg[0] = '\0';
	while ((b = get_n_char(0, &glb_opt->chunk, BUF_SIZE)) > 0)
	{
		msg = ft_ustrjoin(msg, glb_opt->chunk);
		ft_ustrdel(&glb_opt->chunk);
	}
	msg[ft_ustrlen(msg) - 1] = '\0';
	close(0);
	return (msg);
}

unsigned char	*try_open(t_getopt *glb_opt, unsigned char *file)
{
	int				b;
	int				fd;
	unsigned char	*msg;

	b = 0;
	fd = 0;
	msg = ft_ustrnew(1);
	// ft_printf("trying %s\n", file);
	fd = open((const char *)file, O_APPEND, O_RDONLY);
	if (fd >= 0)
	{
		while ((b = get_n_char(fd, &glb_opt->chunk, BUF_SIZE)) > 0)
		{
			msg = ft_ustrjoin(msg, glb_opt->chunk);
			ft_ustrdel(&glb_opt->chunk);
		}
		msg[ft_ustrlen(msg) - 1] = '\0';
		close(fd);
		return (msg);
	}
	//close(fd);
	return (NULL);
}

void	ft_ssl_preform_action(t_getopt *glb_opt, t_opt *opt)
{
	if (glb_opt->opt_choice == 1)
	{
		ft_md5_pre(opt->message);
	}
}
