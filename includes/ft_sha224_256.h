/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha224_256.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:52:25 by tvandivi          #+#    #+#             */
/*   Updated: 2019/11/08 12:30:20 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA224_256_H
# define FT_SHA224_256_H

# include "ft_ssl.h"

/*
** sha224 and 256 return values
*/

# define FT_SHA_SUCESS		0
# define FT_SHA_NULL		1
# define FT_SHA_TOO_LONG	2
# define FT_STATE_ERROR		3
# define FT_BAD_PARAM		4

/*
**	Hash sizes, Hash bits, and Message sizes for sha224 and sha256
*/

# define FT_SHA224HSIZE		28
# define FT_SHA256HSIZE		32

# define FT_SHA224HBITS		224
# define FT_SHA256HBITS		256

# define FT_SHA224MSIZE		64
# define FT_SHA256MSIZE		64

/*
** Bit shift macro: shift x, n bits to the right
*/

# define SHA256_SHIFT(x, n)	((n) >> (x))

# ifndef ROT_L
#  define ROT_L(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# endif

# ifndef ROT_R
#  define ROT_R(n, x) ((x >> n) | (x << (32 - n)))
# endif

/*
** SHA-224 and SHA-256 use six logical functions, where each function
** operates on 32-bit words, which are represented as x, y, and z.  The
** result of each function is a new 32-bit word.
*/

# define SHA_CH(x, y, z)	(((x) & (y)) ^ (~(x) & (z)))
# define SHA_MAJ(x, y, z)	(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define SHA256_SIGMA0(x)	(ROT_R(2, x) ^ ROT_R(13, x) ^ ROT_R(22, x))
# define SHA256_SIGMA1(x)	(ROT_R(6, x) ^ ROT_R(11, x) ^ ROT_R(25, x))
# define SHA256_SIG0(x)		(ROT_R(7, x) ^ ROT_R(18, x) ^ SHA256_SHIFT(3, x))
# define SHA256_SIG1(x)		(ROT_R(17, x) ^ ROT_R(19, x) ^ SHA256_SHIFT(10, x))

# define COUNT0				ctx->count[0]
# define COUNT1				ctx->count[1]
# define COUNT2				ctx->count[2]

typedef struct	s_ft_sha
{
	uint32_t	count[3];
	uint32_t	w[64];
	uint32_t	sha256_h0[8];
	uint8_t		msg_block[FT_SHA256MSIZE];
	uint32_t	abc[8];
	uint32_t	k[64];
	uint8_t		*message;
	uint32_t	length;
	uint64_t	bit_len;
}				t_sha256_ctx;

void		ft_sha256(uint8_t *msg);
void		ft_sha224(uint8_t *msg);
void		ft_sha256_init(t_sha256_ctx *ctx, uint8_t d[32], uint8_t *msg);
void		ft_sha256_final(t_sha256_ctx *context, uint8_t digest[32]);
void		ft_sha256_decode(uint32_t *w, uint8_t *msg);
void		ft_sha256_encode(uint8_t digest[32], uint32_t s[8], uint32_t mlen);
void		ft_sha256_transform(t_sha256_ctx *context, uint8_t buf[64]);
void		ft_sha256_update(t_sha256_ctx *ctx, uint8_t *input, uint32_t mlen);

#endif
