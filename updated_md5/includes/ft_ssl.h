#ifndef FT_SSL_H
# define FT_SSL_H

# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"

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

# ifndef BUF_SIZE

/*
** BUF_SIZE used for get_n_char in ft_ssl_preform_action
*/

#  define BUF_SIZE		64

# endif

# define DEBUG 			0
# define SSL_MD5		"md5"
# define SSL_SHA256		"sha256"

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

// # define F(b,c,d)        ((((c) ^ (d)) & (b)) ^ (d))
// # define G(b,c,d)        ((((b) ^ (c)) & (d)) ^ (c))
// # define H(b,c,d)        ((b) ^ (c) ^ (d))
// # define I(b,c,d)        (((~(d)) | (b)) ^ (c))

# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/*
** Transformations for rounds 1 2 3 and 4
*/

# define FF(a, b, c, d, x, s, ac) { \
	a += F(a, c, d) + x + (unsigned int)ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

# define GG(a, b, c, d, x, s, ac) { \
	a += G(b, c, d) + x + (unsigned int)ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

# define HH(a, b, c, d, x, s, ac) { \
	a += H(b, c, d) + x + (unsigned int)ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

# define II(a, b, c, d, x, s, ac) { \
	a += I(b, c, d) + x + (unsigned int)ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

typedef struct		s_transform
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	x[16];
}					t_tf;

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
	char			*chunk;
	int				opt_total;
	int				opt_i;
	int				opt_choice;
	int				opt_reverse;
	int				opt_quiet;
	t_opt			*opt;
}					t_getopt;

typedef struct		s_ft_md5
{
	unsigned long	i[2];
	unsigned int	state[4];
	unsigned long	buf[4];
	unsigned int	count[2];
	unsigned char	in[64];
	unsigned int	kspc[64];
	unsigned char	digest[16];
	unsigned short	rps1[4];
	unsigned short	rps2[4];
	unsigned short	rps3[4];
	unsigned short	rps4[4];
	unsigned short	*rots[4];
	unsigned char	buffer[64];
	unsigned char	*msg;
	unsigned int	size;
}               	t_md5_ctx;

/*
** getopt functions
*/

unsigned char		*ft_md5(const unsigned char *d, unsigned long n, unsigned char *md);
void				ft_ssl_message(char *invalid);
void				ft_ssl_free_optins(t_getopt *glb_opt);
void				ft_ssl_preform_action(t_getopt *glb_opt, int ac, char **av);
int					ft_getopt(int ac, char **av, t_getopt *glb_opt);
void				ft_opt_init(t_getopt *glb_opt);
t_opt				*newsslnode(void);
t_opt				*get_opt(t_getopt *glb_opt);
char				*read_from_stdin(t_getopt *glb_opt);
char				*try_open(t_getopt *glb_opt, char *file);
/*
** MD5 padding functions
*/

int					md5_pad_msg(t_md5_ctx *context, int bitlen, unsigned char*d);
void				ft_ssl_print_bits(t_md5_ctx *context);

#endif
