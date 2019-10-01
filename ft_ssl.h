#ifndef FT_SSL_H
# define FT_SSL_H

# include <math.h>
# include "libft/libft.h"

/*
 ** rps: specifies sround per shift
 */

/*
 ** You are allowed the following functions:
 **    ◦open
 **    ◦close
 **    ◦read
 **    ◦write
 **    ◦malloc
 **    ◦free
 */

# define DEBUG 0
# define FT_SSL_NULL		(void *)0
# define FT_BLACK			"\033[0;30m"
# define FT_RED				"\033[0;31m"
# define FT_GREEN			"\033[0;32m"
# define FT_BROWN			"\033[0;33m"
# define FT_BLUE			"\033[0;34m"
# define FT_PURPLE			"\033[0;35m"
# define FT_CYAN			"\033[0;36m"
# define FT_LIGHTGRAY		"\033[0;37m"
# define FT_DARKGRAY    	"\033[1;30m"
# define FT_LIGHT_RED		"\033[1;31m"
# define FT_LIGHTGREEN		"\033[1;32m"
# define FT_YELLOW			"\033[1;33m"
# define FT_LIGHTBLUE		"\033[1;34m"
# define FT_LIGHTPURPLE		"\033[1;35m"
# define FT_LIGHTCYAN		"\033[1;36m"
# define FT_WHITE			"\033[1;37m"
# define FT_CLEAR_SCREEN	"\033[d"
# define FT_BOLD			"\033[1m"
# define FT_UNDERLINE		"\033[4m"
# define FT_END_ATTR		"\033[0m"

typedef unsigned char	ft_uchar;
typedef unsigned long	ft_ulong;
typedef	long long		ft_llong;

typedef struct		s_ft_getopt
{
	char			flag[2];
	int				i;
	int				c;
    ft_uchar		*ft_md5;
	ft_uchar		*ft_sha256;
}					t_getopt;

typedef struct		s_ft_md5
{
	unsigned long	i[2];
	unsigned long	buf[4];
	unsigned char	in[64];
	unsigned char	digest[16];
	unsigned char	*msg;
	unsigned int	size;
}               	t_md5_ctx;

unsigned char		*ft_md5(const unsigned char *d, unsigned long n, unsigned char *md);
void				ft_ssl_message(char *invalid);
void				ft_ssl_free_optins(t_getopt *glb_opt);
void				ft_ssl_preform_action(t_getopt *glb_opt, int ac, char **av);
int					ft_getopt(int ac, char **av, t_getopt *glb_opt);
void				ft_opt_init(t_getopt *glb_opt);
int					ft_scmp(const char *s1, const char *s2);

#endif
