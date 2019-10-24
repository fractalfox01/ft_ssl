#ifndef FT_SHA256_H
#define FT_SHA256_H

# define SHA256_SHIFT(x, n) ((n) >> (x))

/*
** SHA sigma macros
*/

# define SHA256_SIGMA0(x) (ROTATE_RIGHT(2, x) ^ ROTATE_RIGHT(13, x) ^ ROTATE_RIGHT(22, x))
# define SHA256_SIGMA1(x) (ROTATE_RIGHT(6, x) ^ ROTATE_RIGHT(11, x) ^ ROTATE_RIGHT(25, x))
# define SHA256_SIG0(x) (ROTATE_RIGHT(7, x) ^ ROTATE_RIGHT(18, x) ^ ROTATE_RIGHT(3, x))
# define SHA256_SIG1(x) (ROTATE_RIGHT(17, x) ^ ROTATE_RIGHT(19, x) ^ ROTATE_RIGHT(10, x))

unsigned char   ft_sha256(const unsigned char *msg);

#endif