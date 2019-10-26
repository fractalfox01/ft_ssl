/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha224_256.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:52:25 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/26 16:35:32 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA224_256_H
# define FT_SHA224_256_H

/*
** sha224 and 256 return values
*/

# define FT_SHA_SUCESS		0
# define FT_SHA_NULL		1
# define FT_SHA_TOO_LONG	2
# define FT_STATE_ERROR		3

/*
**	Hash sizes for sha224 and sha256
*/

# define FT_SHA224HSIZE		28
# define FT_SHA256HSIZE		32

# define FT_SHA224HBITS		224
# define FT_SHA256HBITS		256

# define FT_SHA224MSIZE		64
# define FT_SHA256MSIZE		64

# define SHA_CH(x, y, z)      (((x) & ((y) ^ (z))) ^ (z))
# define SHA_MAJ(x, y, z)     (((x) & ((y) | (z))) | ((y) & (z)))

/*
** Bit shift macro: shift x, n bits to the right 
*/

# define SHA256_SHIFT(x, n) ((n) >> (x))

# ifndef ROT_L
#  define ROT_L(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# endif

# ifndef ROT_R
#  define ROT_R(x, n) (((x) >> (n)) | ((x) << (32-(n))))
# endif

/*
** SHA sigma macros
*/

# define SHA256_SIGMA0(x) (ROT_R(2, x) ^ ROT_R(13, x) ^ ROT_R(22, x))
# define SHA256_SIGMA1(x) (ROT_R(6, x) ^ ROT_R(11, x) ^ ROT_R(25, x))
# define SHA256_SIG0(x) (ROT_R(7, x) ^ ROT_R(18, x) ^ ROT_R(3, x))
# define SHA256_SIG1(x) (ROT_R(17, x) ^ ROT_R(19, x) ^ ROT_R(10, x))

// # define SHA224_256ADDLEN(context, length) (addTemp = (context)->length_low, \
// 	(context)->corrupted = (((context)->length_low += (length)) < addTemp) \
// 	&& (++(context)->length_high == 0) ? shaInputTooLong : (context)->corrupted)

enum {
	shaSuccess = 0,
	shaNull,
	shaInputTooLong,
	shaStateError,
	shaBadParam
};

/*
** message:				Original message
** msg_block:			512-bit message blocks
** intermediate_hash:	Message Digest
** length_high:			Message length in bits
** length_low:			Message length in bits
** message_index:		Message_Block array index
** computed:			Is the hash computed?
** corupted:			Cumulative corruption code
*/

typedef struct		s_ft_sha
{
	uint32_t		abcdefgh[8];
	uint32_t		w[64];
	uint32_t		addtemp;
	uint32_t		sha256_h0[FT_SHA256HSIZE / 4];
	uint8_t			*message;
	uint8_t			msg_block[FT_SHA256MSIZE];
	uint32_t		intermediate_hash[FT_SHA256HSIZE / 4];
	uint32_t		length_high;
	uint32_t		length_low;
	int_least16_t	message_index;
	uint32_t		computed;
	uint32_t		corrupted;
	uint32_t		k[64];
}					t_sha224_256_ctx;

void		ft_sha256(const uint8_t *msg);
void		ft_sha224(const uint8_t *msg);
int			ft_sha224_256init(t_sha224_256_ctx *ctx, int sha_type, uint8_t *msg);
int			sha256input(t_sha224_256_ctx *ctx, uint8_t *msg, uint32_t length);
void		sha224_256process_message(t_sha224_256_ctx *context);
void		sha224_256finalize(t_sha224_256_ctx *ctx, uint8_t pad_byte);
void		sha224_256pad_message(t_sha224_256_ctx *ctx, uint8_t pad_byte);
int			sha224_256result_n(t_sha224_256_ctx *ctx, uint8_t md[], int hsize);

#endif
