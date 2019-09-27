/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 22:31:46 by tvandivi          #+#    #+#             */
/*   Updated: 2019/09/23 19:29:42 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		main(int ac, char **av)
{
	t_getopt glb_opt;

	if (ac == 3)
	{
		ft_opt_init(&glb_opt);
		glb_opt.c = ft_getopt(ac, av, &glb_opt);
		ft_ssl_preform_action(&glb_opt, ac, av);
		ft_ssl_free_optins(&glb_opt);
	}
	else
	{
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	}
	return (0);
}
