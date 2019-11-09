/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 22:31:46 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/08 16:36:46 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ssl.h"

t_opt	*ft_ssl_parse_options(t_getopt *glb_opt, int ac, char **av)
{
	t_opt		*opt;
	int			a;
	ft_opt_init(glb_opt);
	opt = glb_opt->opt;
	if ((a = ft_getopt(ac, av, glb_opt)) == 0)
	{
		if (glb_opt->opt_choice == 0)
			ft_printf("usage: ft_ssl command [command opts] [command args]\n");
		else
			ft_printf("Bad ssl option\n");
		return (NULL);
	}
	return (opt);
}

void	output_hash(t_opt *opt, t_getopt glb_opt, uint8_t *digest, int size)
{
	int		i;
	char	*mtype;

	i = 0;
	if (size == 16)
		mtype = ft_strdup("MD5");
	else
		mtype = ft_strdup("SHA256");
	if (opt->cmdarg[0] == 'p')
	{
		if (glb_opt.opt_choice == 1)
		{
			if (glb_opt.opt_quiet == 0)
				ft_printf("%s", opt->message);
			i = 0;
			while (i < size)
				ft_printf("%02x", digest[i++]);
			ft_printf("\n");
		}
		if (glb_opt.opt_choice == 2)
		{
			if (glb_opt.opt_quiet == 0)
				ft_printf("%s", opt->message);
			i = 0;
			while (i < size)
				ft_printf("%02x", digest[i++]);
			ft_printf("\n");
		}
	}
	else
	{
		if (glb_opt.opt_quiet == 1)
		{
			i = 0;
			while (i < size)
				ft_printf("%02x", digest[i++]);
			ft_printf("\n");
		}
		else if (glb_opt.opt_reverse == 1)
		{
			i = 0;
			while (i < size)
				ft_printf("%02x", digest[i++]);
			if (glb_opt.opt_quiet == 0)
				ft_printf(" \"%s\"\n", opt->message);
		}
		else if (opt->cmdarg[0] == 's')
		{
			i = 0;
			if (glb_opt.opt_quiet == 0)
				ft_printf("%s (\"%s\") = ", mtype, opt->message);
			while (i < size)
				ft_printf("%02x", digest[i++]);
			ft_printf("\n");
		}
		else
		{
			i = 0;
			while (i < size)
				ft_printf("%02x", digest[i++]);
			ft_printf("\n");
		}
	}
}

int		main(int ac, char **av)
{
	t_getopt	glb_opt;
	t_opt		*opt;
	uint8_t		*digest;

	if (ac >= 2)
	{
		opt = ft_ssl_parse_options(&glb_opt, ac, av);
		if (opt)
		{
			while (opt->message)
			{
				// ft_printf("message: %s\n", opt->message);
				digest = ft_ssl_preform_action(&glb_opt, opt);
				if (glb_opt.opt_choice == 1)
					output_hash(opt, glb_opt, digest, 16);
				if (glb_opt.opt_choice == 2)
					output_hash(opt, glb_opt, digest, 32);
				opt = opt->next;
			}
		}	//ft_ssl_free_optins(&glb_opt);
	}
	else
	{
		if (glb_opt.opt_choice == 0)
			ft_ssl_message(av[1]);
		else
			ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	}
	return (0);
}
