/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_getoptions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:03:38 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/13 22:28:12 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	ft_ssl_get_flag(unsigned char *flag, t_getopt *glb_opt, t_opt *opt)
{
	if (ft_ustrcmp(flag, (const unsigned char *)"-p") == 0)
	{
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
	else if (ft_ustrcmp(flag, (const unsigned char *)"-s") == 0)
	{
		opt->cmdarg[0] = 's';
		glb_opt->skip = 1;
	}
	else
		opt->cmdarg[0] = '\0';
}

void	set_msg1(t_getopt *glb_opt, t_opt *opt, uint8_t *mesg, uint8_t *msg)
{
	opt->file = (char *)ft_uchardup(mesg);
	opt->message = ft_uchardup(msg);
	glb_opt->opt_total++;
	opt->next = newsslnode();
	glb_opt->end = 0;
}

int		set_msg2(t_getopt *glb_opt, t_opt *opt, uint8_t *mesg)
{
	if (glb_opt->skip == 1)
	{
		opt->file = NULL;
		opt->message = ft_uchardup(mesg);
		glb_opt->opt_total++;
		opt->next = newsslnode();
		glb_opt->skip = 0;
		return (1);
	}
	return (0);
}

int		ft_ssl_proc(uint8_t *mesg, t_getopt *glb_opt, t_opt *opt, uint8_t *msg)
{
	if (ft_ustrcmp(mesg, (const uint8_t *)"0xdeadbeeef") == 0)
	{
		ft_ssl_get_flag((unsigned char *)"-p", glb_opt, opt);
		return (1);
	}
	if (ft_ustrcmp((const unsigned char *)"-r", mesg) == 0)
		glb_opt->opt_reverse = 1;
	else if (ft_ustrcmp((const unsigned char *)"-q", mesg) == 0)
		glb_opt->opt_quiet = 1;
	else if (ft_ustrcmp(mesg, (const unsigned char *)"-p") == 0)
		ft_ssl_get_flag(mesg, glb_opt, opt);
	else if (ft_ustrcmp(mesg, (const unsigned char *)"-s") == 0)
		ft_ssl_get_flag(mesg, glb_opt, opt);
	else if ((msg = try_open(glb_opt, mesg)))
	{
		set_msg1(glb_opt, opt, mesg, msg);
		ft_ustrdel(&msg);
	}
	else
		return (set_msg2(glb_opt, opt, mesg));
	return (1);
}

int		ft_getopt(int ac, char **av, t_getopt *glb_opt, int i)
{
	int				a;
	int				len;
	t_opt			*opt;
	unsigned char	*msg;

	a = 0;
	len = 0;
	msg = NULL;
	while (i++ < ac && glb_opt->success && glb_opt->end)
	{
		if (i == ac && ac != 2)
			break ;
		opt = get_opt(glb_opt);
		if (i == 1)
			ft_ssl_get_type(av[i], glb_opt);
		else if (ac == 2)
			ft_ssl_proc((unsigned char *)"0xdeadbeeef", glb_opt, opt, msg);
		else
		{
			if (msg)
				ft_ustrdel(&msg);
			ft_ssl_proc((unsigned char *)av[i], glb_opt, opt, msg);
		}
	}
	return (glb_opt->success);
}
