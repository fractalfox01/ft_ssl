/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:47:29 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/13 22:27:48 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "ft_md5.h"
# include "ft_sha224_256.h"

# ifndef BUF_SIZE
#  define BUF_SIZE		64
# endif

typedef struct		s_md5_pad
{
	int				padb;
	int				orig;
	int				o_b;
	int				i;
	int				a;
	int				b;
	long			p_fin;
	unsigned char	*p_msg;
}					t_pad;

typedef	struct		s_ft_opt
{
	char			*file;
	unsigned char	*message;
	unsigned char	chunk[64];
	unsigned char	cmdarg[2];
	struct s_ft_opt	*next;
}					t_opt;

typedef struct		s_ft_getopt
{
	int				success;
	int				end;
	int				skip;
	unsigned char	*chunk;
	int				opt_total;
	int				opt_i;
	int				opt_choice;
	int				opt_reverse;
	int				opt_quiet;
	t_opt			*opt;
}					t_getopt;

/*
** getopt functions
*/

unsigned char		*ft_md5(const unsigned char *d);
void				ft_ssl_message(char *invalid);
void				ft_ssl_free_optins(t_getopt *glb_opt);
uint8_t				*ft_ssl_preform_action(t_getopt *glb_opt, t_opt *opt);
int					ft_getopt(int ac, char **av, t_getopt *glb_opt, int i);
t_opt				*get_opt(t_getopt *glb_opt);
t_opt				*newsslnode(void);
t_opt				*get_opt(t_getopt *glb_opt);
unsigned char		*read_from_stdin(t_getopt *glb_opt);
unsigned char		*try_open(t_getopt *glb_opt, unsigned char *file);
void				ft_opt_init(t_getopt *glb_opt);
void				print_other(t_getopt g, t_opt *opt, uint8_t *d, int size);
char				*set_type(int size);
t_opt				*ft_ssl_parse_options(t_getopt *glb_opt, int ac, char **av);
void				print_p(uint8_t *digest, int size);
void				ft_ssl_get_type(char *type, t_getopt *glb_opt);
unsigned char		*ft_ujoin(uint8_t *s1, uint8_t *s2, int i, size_t len1);

#endif
