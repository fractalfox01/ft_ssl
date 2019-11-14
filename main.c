/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 22:31:46 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/13 18:17:50 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ssl.h"

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

void	print_other(t_getopt glb_opt, t_opt *opt, uint8_t *digest, int size)
{
	int		i;

	i = 0;
	if (glb_opt.opt_quiet == 1 || glb_opt.opt_reverse == 1)
	{
		while (i < size)
			printf("%02x", digest[i++]);
		if (glb_opt.opt_quiet == 0 && opt->cmdarg[0] == 's')
			printf(" \"%s\"\n", opt->message);
		else if (glb_opt.opt_quiet == 0)
			printf(" %s\n", opt->file);
		else
			printf("\n");
	}
	else
	{
		if (opt->cmdarg[0] == 's')
			printf("%s (\"%s\") ", set_type(size), opt->message);
		else
			printf("%s (\"%s\") ", set_type(size), opt->file);
		while (i < size)
			printf("%02x", digest[i++]);
		printf("\n");
	}
}

void	output_hash(t_opt *opt, t_getopt glb_opt, uint8_t *digest, int size)
{
	int		i;

	i = 0;
	if (opt->cmdarg[0] == 'p')
		print_p(digest, size);
	else
		print_other(glb_opt, opt, digest, size);
}

void	looper(t_getopt glb_opt, t_opt *opt)
{
	uint8_t		*digest;

	while (opt->message)
	{
		digest = ft_ssl_preform_action(&glb_opt, opt);
		if (glb_opt.opt_choice == 1)
			output_hash(opt, glb_opt, digest, 16);
		if (glb_opt.opt_choice == 2)
			output_hash(opt, glb_opt, digest, 32);
		opt = opt->next;
		ft_strdel((char **)&digest);
	}
}

void				ft_ssl_free_optins(t_getopt *glb_opt)
{
	t_opt	*tmp_opt;
	t_opt	*n;
	int		i;

	i = 0;
	if (glb_opt)
	{
		tmp_opt = glb_opt->opt;
		if (glb_opt->chunk)
			ft_strdel((char **)&glb_opt->chunk);
		while (tmp_opt)
		{
			while (i < 64)
				tmp_opt->chunk[i++] = 0;
			tmp_opt->cmdarg[0] = 0;
			tmp_opt->cmdarg[1] = 0;
			if (tmp_opt->message)
				ft_strdel((char **)&tmp_opt->message);
			if (tmp_opt->file)
			{
				ft_strdel((char **)&(tmp_opt->file));
			}
			n = tmp_opt->next;
			free((void *)tmp_opt);
			tmp_opt = n;
			i = 0;
		}
	}
}

int		main(int ac, char **av)
{
	t_getopt	glb_opt;
	t_opt		*opt;

	if (ac >= 2)
	{
		opt = ft_ssl_parse_options(&glb_opt, ac, av);
		if (opt)
		{
			looper(glb_opt, opt);
		}
	}
	else
	{
		if (glb_opt.opt_choice == 0)
			ft_ssl_message(av[1]);
		else
			ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	}
	ft_ssl_free_optins(&glb_opt);
	// system("leaks ft_ssl");
	return (0);
}
