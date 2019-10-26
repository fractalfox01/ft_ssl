#ifndef FT_MD5_H
#define FT_MD5_H

# ifndef ROT_L
#  define ROT_L(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# endif

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

# define FF(a, b, c, d, x, s, ac) { \
	a += F(b, c, d) + x + (unsigned int)ac; \
	a = ROT_L(a, s); \
	a += b; \
}

# define GG(a, b, c, d, x, s, ac) { \
	a += G(b, c, d) + x + (unsigned int)ac; \
	a = ROT_L(a, s); \
	a += b; \
}

# define HH(a, b, c, d, x, s, ac) { \
	a += H(b, c, d) + x + (unsigned int)ac; \
	a = ROT_L(a, s); \
	a += b; \
}

# define II(a, b, c, d, x, s, ac) { \
	a += I(b, c, d) + x + (unsigned int)ac; \
	a = ROT_L(a, s); \
	a += b; \
}

typedef struct		s_ft_md5
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned char	*msg;
	unsigned int	state[4];
	unsigned int	count[2];
	unsigned char	buf[64];
	unsigned short	rps1[4];
	unsigned short	rps2[4];
	unsigned short	rps3[4];
	unsigned short	rps4[4];
}               	t_md5_ctx;

typedef struct 		s_md5_glb
{
	int				size;
	unsigned char	*msg;
}					t_md5_glb;

typedef struct		s_transform
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	x[16];
}					t_tf;

/*
** MD5 padding functions
*/

unsigned char		*ft_md5(const unsigned char *d);
void				md5_update(t_md5_ctx *context, unsigned char *input, unsigned long mlen);
int					md5_pad_msg(t_md5_ctx *context, int bitlen, unsigned char*d);
void				ft_ssl_print_bits(unsigned char *msg, int size);
void				md5_decode(unsigned int *output, unsigned char *input, unsigned int len);
void				ft_md5_round1(unsigned int state[4], unsigned int x[16]);
void				ft_md5_round2(unsigned int state[4], unsigned int x[16]);
void				ft_md5_round3(unsigned int state[4], unsigned int x[16]);
void				ft_md5_round4(unsigned int state[4], unsigned int x[16]);
void				md5_clearout(t_md5_ctx *context);
void				md5_encode(unsigned char digest[16], unsigned int state[4], unsigned int len);
void				md5_final(unsigned char digest[16], t_md5_ctx *context);
void				md5_init(t_md5_ctx *context);
void				md5_decode(unsigned int output[16], unsigned char *input, unsigned int len);
void				md5_transform(t_md5_ctx *context, unsigned char buf[64]);

#endif