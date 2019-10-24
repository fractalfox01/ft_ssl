#ifndef FT_SHA224_256_H
#define FT_SHA224_256_H

# define SHA256_SHIFT(x, n) ((n) >> (x))

/*
** SHA sigma macros
*/

# define SHA256_SIGMA0(x) (ROT_R(2, x) ^ ROT_R(13, x) ^ ROT_R(22, x))
# define SHA256_SIGMA1(x) (ROT_R(6, x) ^ ROT_R(11, x) ^ ROT_R(25, x))
# define SHA256_SIG0(x) (ROT_R(7, x) ^ ROT_R(18, x) ^ ROT_R(3, x))
# define SHA256_SIG1(x) (ROT_R(17, x) ^ ROT_R(19, x) ^ ROT_R(10, x))

# define SHA224_256ADDLEN(context, length) (addTemp = (context)->Length_Low, (context)->Corrupted = (((context)->Length_Low += (length)) < addTemp) && (++(context)->Length_High == 0) ? shaInputTooLong : (context)->Corrupted)

typedef struct  s_ft_sha
{
    int         a;
}               t_sha256_ctx;

void    ft_sha256(const unsigned char *msg);
int     ft_sha224_256Reset(t_sha256_ctx *context, uint32_t *H0);
void    ft_sha224_256ProcessMessage(t_sha256_ctx *context);
void    ft_sha224_256Finalize(t_sha256_ctx *context, uint8_t Pad_Byte);
void    ft_sha224_256PadMessage(t_sha256_ctx *context, uint8_t Pad_Byte);
int     ft_sha224_256ResultN(t_sha256_ctx *context, uint8_t Message_Digest[], int HashSize);

#endif