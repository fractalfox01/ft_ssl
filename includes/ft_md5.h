/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:47:15 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/12 13:08:49 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# ifndef ROT_L
#  define ROT_L(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# endif

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

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
}					t_md5_ctx;

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
void				md5_update(t_md5_ctx *context, uint8_t *input, uint64_t m);
int					md5_pad_msg(t_md5_ctx *context, int bitlen, uint8_t *d);
void				ft_ssl_print_bits(unsigned char *msg, int size);
void				md5_decode(unsigned int *output, uint8_t *i, uint32_t l);
void				md5r1_1(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r1_2(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r1_3(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r1_4(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r2_1(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r2_2(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r2_3(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r2_4(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r3_1(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r3_2(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r3_3(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r3_4(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r4_1(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r4_2(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r4_3(unsigned int state[4], unsigned int x, uint32_t so);
void				md5r4_4(unsigned int state[4], unsigned int x, uint32_t so);
void				ft_md5_round1(unsigned int state[4], unsigned int x[16]);
void				ft_md5_round2(unsigned int state[4], unsigned int x[16]);
void				ft_md5_round3(unsigned int state[4], unsigned int x[16]);
void				ft_md5_round4(unsigned int state[4], unsigned int x[16]);
void				md5_clearout(t_md5_ctx *context);
void				md5_encode(unsigned char d[16], uint32_t s[4], uint32_t l);
void				md5_final(unsigned char digest[16], t_md5_ctx *context);
void				md5_init(t_md5_ctx *context);
void				md5_decode(unsigned int o[16], uint8_t *input, uint32_t l);
void				md5_transform(t_md5_ctx *context, unsigned char buf[64]);

#endif
