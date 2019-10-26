#ifndef FT_SSL_H
# define FT_SSL_H

# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "ft_md5.h"
# include "ft_sha224_256.h"

/*
 ** You are allowed the following functions:
 **    ◦open
 **    ◦close
 **    ◦read
 **    ◦write
 **    ◦malloc
 **    ◦free
 */

/*
** BUF_SIZE used for get_n_char in ft_ssl_preform_action
*/

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
void				ft_ssl_preform_action(t_getopt *glb_opt, t_opt *opt);
int					ft_getopt(int ac, char **av, t_getopt *glb_opt);
t_opt				*get_opt(t_getopt *glb_opt);
t_opt				*newsslnode(void);
t_opt				*get_opt(t_getopt *glb_opt);
unsigned char		*read_from_stdin(t_getopt *glb_opt);
unsigned char		*try_open(t_getopt *glb_opt, unsigned char *file);
void				ft_opt_init(t_getopt *glb_opt);

#endif
