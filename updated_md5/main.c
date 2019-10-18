/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 22:31:46 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/18 14:08:09 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ssl.h"

int		main(int ac, char **av)
{
	t_getopt	glb_opt;
	int			a;
	int			i;
	t_opt		*opt;

	i = 0;
	if (ac >= 3)
	{
		ft_opt_init(&glb_opt);
		while (i < ac)
		{
			if (ft_strcmp(av[i], "as") == 0)
				av[i][0] = '-';
			else if (ft_strcmp(av[i], "ar") == 0)
				av[i][0] = '-';
			else if (ft_strcmp(av[i], "aq") == 0)
				av[i][0] = '-';
			i++;
		}
		//av[2][0] = '-';
		if ((a = ft_getopt(ac, av, &glb_opt)) == 0)
		{
			if (glb_opt.opt_choice == 0)
				ft_printf("usage: ft_ssl command [command opts] [command args]\n");
			else
				ft_printf("Bad ssl option\n");
			return (0);
		}
		ft_printf("total: %d\tchoice: %d\treverse %d\tquiet: %d\n", glb_opt.opt_total, glb_opt.opt_choice, glb_opt.opt_reverse, glb_opt.opt_quiet);
		opt = glb_opt.opt;
		while (opt->message)
		{
			ft_printf("msg: %s\n", opt->message);
			opt = opt->next;
		}	
		
		// ft_printf("first msg: %s\nsecond msg: %s\nthird msg: %s\n", glb_opt.opt->message, glb_opt.opt->next->message, glb_opt.opt->next->next->message);
		// ft_ssl_preform_action(&glb_opt, ac, av);
		// ft_ssl_free_optins(&glb_opt);
	}
	else
	{
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	}
	return (0);
}
