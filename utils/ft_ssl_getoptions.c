/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_getoptions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:03:38 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/24 15:56:23 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	ft_ssl_get_type(char *type, t_getopt *glb_opt)
{
	if (ft_strcmp(type, "md5") == 0)
		glb_opt->opt_choice = 1;
	else if (ft_strcmp(type, "sha256") == 0)
		glb_opt->opt_choice = 2;
	else if (ft_strcmp(type, "sha224") == 0)
		glb_opt->opt_choice = 3;
	else
		glb_opt->success = 0;
}

void    ft_ssl_get_flag(unsigned char *flag, t_getopt *glb_opt, t_opt *opt)
{
	if (ft_ustrcmp(flag, (const unsigned char *)"-p") == 0)
	{
		// ft_printf("total: %d\tp flag\n", glb_opt->opt_total);
		glb_opt->opt_total++;
		opt->cmdarg[0] = 'p';
		opt->message = (unsigned char *)read_from_stdin(glb_opt);
		opt->next = newsslnode();
		if (!(opt->message))
		{
			glb_opt->success = 0;
			return ;
		}
	}
	else
	{
		opt->cmdarg[0] = 's';
		glb_opt->skip = 1;
	}
}

int    ft_ssl_proccess_message(unsigned char *message, t_getopt *glb_opt, t_opt *opt, unsigned char *msg)
{
	if (ft_ustrcmp((const unsigned char *)"-r", message) == 0)
		glb_opt->opt_reverse = 1;
	else if (ft_ustrcmp((const unsigned char *)"-q", message) == 0)
		glb_opt->opt_quiet = 1;
	else if (ft_ustrcmp(message, (const unsigned char *)"-p") == 0)
		ft_ssl_get_flag(message, glb_opt, opt);
	else if (ft_ustrcmp(message, (const unsigned char *)"-s") == 0)
		ft_ssl_get_flag(message, glb_opt, opt);
	else if ((msg = try_open(glb_opt, message)))
	{
		opt->message = ft_uchardup(msg);
		glb_opt->opt_total++;
		opt->next = newsslnode();
		glb_opt->end = 0;
	}
	else
	{
		if (glb_opt->skip == 1)
		{
			opt->message = ft_uchardup(message);
			glb_opt->opt_total++;
			opt->next = newsslnode();
			glb_opt->skip = 0;
		}
		else
		{
			// ft_printf("bad end\n");
			return (0);
		}
	}
	// ft_printf("msg = %s\n", msg);
	return (1);
}

int		ft_getopt(int ac, char **av, t_getopt *glb_opt)
{
	int				i;
	int				a;
	int				len;
	t_opt			*opt;
	unsigned char	*msg;

	i = 1;
	a = 0;
	len = 0;
	msg = NULL;
	while (i < ac && glb_opt->success && glb_opt->end)
	{
		opt = get_opt(glb_opt);
		if (i == 1)
			ft_ssl_get_type(av[i], glb_opt);
		else
		{
			// if (i == 7)
			// 	ft_printf("7 = %s\n", av[8]);
			// ft_printf("its %d\n", i);
			ft_ssl_proccess_message((unsigned char *)av[i], glb_opt, opt, msg);
		}
		// if (msg)
		// 	ft_strdel((void *)msg);
		i++;
	}
	// ft_printf("i = %d\tsuccess = %d\tend = %d\n", i, glb_opt->success, glb_opt->end);
	return (glb_opt->success);
}
