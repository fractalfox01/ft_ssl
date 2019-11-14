/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:57:31 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/13 22:28:04 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

/*
** DESCRIPTION:
**
** opt->message: original message read in
** opt->chunk[64]: used for proccessing the message in 64 bits at a time.
** opt->cmdarg: represents how the message is to be read in.
** 		(-p = pipe/stdin)
** 		(-s = common string, char **av)
**
** RETURN:
**
** Return type is a new t_opt structure
*/

t_opt	*newsslnode(void)
{
	t_opt	*opt;
	int		i;

	i = 0;
	opt = (t_opt *)malloc(sizeof(t_opt) * 1);
	opt->file = NULL;
	opt->message = NULL;
	while (i < 64)
		opt->chunk[i++] = '\0';
	i = 0;
	while (i < 2)
		opt->cmdarg[i++] = '\0';
	opt->next = NULL;
	return (opt);
}

/*
** Initialization of options structure.
*/

void	ft_opt_init(t_getopt *glb_opt)
{
	glb_opt->success = 1;
	glb_opt->end = 1;
	glb_opt->skip = 0;
	glb_opt->opt_choice = 0;
	glb_opt->opt_total = 0;
	glb_opt->opt_i = 1;
	glb_opt->chunk = NULL;
	glb_opt->opt_quiet = 0;
	glb_opt->opt_reverse = 0;
	glb_opt->opt = newsslnode();
}

/*
** Returns the last node in options structure.
** (end signified by glb_opt->opt_total)
*/

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

t_opt	*ft_ssl_parse_options(t_getopt *glb_opt, int ac, char **av)
{
	t_opt		*opt;
	int			a;

	ft_opt_init(glb_opt);
	opt = glb_opt->opt;
	if ((a = ft_getopt(ac, av, glb_opt, 0)) == 0)
	{
		if (glb_opt->opt_choice == 0)
			ft_printf("usage: ft_ssl command [command opts] [command args]\n");
		else
			ft_printf("Bad ssl option\n");
		return (NULL);
	}
	return (opt);
}

void	print_p(uint8_t *digest, int size)
{
	int	i;

	i = 0;
	while (i < size)
		ft_printf("%02x", digest[i++]);
	ft_printf("\n");
}
