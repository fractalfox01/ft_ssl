/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 22:31:46 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/23 15:54:22 by tvandivi         ###   ########.fr       */
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

int		main(int ac, char **av)
{
	t_getopt	glb_opt;
	t_opt		*opt;

	if (ac >= 3)
	{
		opt = ft_ssl_parse_options(&glb_opt, ac, av);
		if (opt)
		{
			while (opt->message)
			{
				ft_printf("message: %s\n", opt->message);
				ft_ssl_preform_action(&glb_opt, opt);
				opt = opt->next;
			}
		}	//ft_ssl_free_optins(&glb_opt);
	}
	else
	{
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	}
	return (0);
}
