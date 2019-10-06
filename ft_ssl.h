#ifndef FT_SSL_H
# define FT_SSL_H

# include <math.h>
# include <fcntl.h>
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

# ifndef BUF_SIZE

/*
** BUF_SIZE used for get_n_char in ft_ssl_preform_action
*/

#  define BUF_SIZE 64

# endif

# define DEBUG 0

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/*
** Transformations for rounds 1 2 3 and 4
*/

# define FF(a, b, c, d, x, s, ac) { \
	(a) += F ((b), (c), (d)) + (x) + (ft_u4)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
	(a) += G ((b), (c), (d)) + (x) + (ft_u4)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
	(a) += H ((b), (c), (d)) + (x) + (ft_u4)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
	(a) += I ((b), (c), (d)) + (x) + (ft_u4)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}

typedef struct	s_ft_getopt
{
	char		*message;
	char		*chunk;
	char		flag[5];
	int			i;
	int			c;
    ft_u1		*ft_md5;
	ft_u1		*ft_sha256;
}				t_getopt;

typedef struct	s_ft_md5
{
	ft_u8		i[2];
	ft_u4		state[4];
	ft_u8		buf[4];
	ft_u4		count[2];
	ft_u1		in[64];
	ft_u4		kspc[64];
	ft_u1		digest[16];
	ft_u2		rps1[4];
	ft_u2		rps2[4];
	ft_u2		rps3[4];
	ft_u2		rps4[4];
	ft_u2		*rots[4];
	ft_u1		*msg;
	ft_u4		size;
}               t_md5_ctx;

ft_u1			*ft_md5(const ft_u1 *d, ft_u8 n, ft_u1 *md);
void			ft_ssl_message(char *invalid);
void			ft_ssl_free_optins(t_getopt *glb_opt);
void			ft_ssl_preform_action(t_getopt *glb_opt, int ac, char **av);
int				ft_getopt(int ac, char **av, t_getopt *glb_opt);
void			ft_opt_init(t_getopt *glb_opt);

#endif
