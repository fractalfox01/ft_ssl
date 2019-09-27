#ifndef FT_SSL_H
# define FT_SSL_H

# include <math.h>
# include <unistd.h>
# include "../vogsphere_ftprintf/includes/ft_printf.h"

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

# define FF(b, c, d) (d ^ (b & (c ^ d)))
# define FG(b, c, d) FF (d, b, c)
# define FH(b, c, d) (b ^ c ^ d)
# define FI(b, c, d) (c ^ (b | ~d))

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_ft_getopt
{
	int				i;
	int				c;
    char			*ft_md5;
	char			*ft_sha256;
}					t_getopt;

typedef unsigned Digest[4];
typedef unsigned char *u_int32_ssl;

typedef struct	s_ft_md5
{
	int     		k[64];
	int         	rps[64];
	int         	a0;
	int         	b0;
	int         	c0;
	int         	d0;
	int				l; /* (= msg.length/4 + 2)  length (int 32-bit integers) of msg + '1' + appended length */
	int				n;
	unsigned int	**m;
	unsigned char  	*message;
}               	t_md5;

unsigned			*ft_md5(const char *msg, int mlen);
unsigned			*ft_sha256(const char *msg, int mlen);
void				ft_ssl_message(char *invalid);
void				ft_ssl_free_optins(t_getopt *glb_opt);
void				ft_ssl_preform_action(t_getopt *glb_opt, int ac, char **av);
int					ft_getopt(int ac, char **av, t_getopt *glb_opt);
void				ft_opt_init(t_getopt *glb_opt);
int					ft_scmp(const char *s1, const char *s2);
int					get_md5_buffer(t_md5 *md5);

#endif
