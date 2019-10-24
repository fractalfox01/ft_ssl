#ifndef FT_MD5_H
#define FT_MD5_H

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

# define FF(a, b, c, d, x, s, ac) { \
	a += F(b, c, d) + x + (unsigned int)ac; \
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

#endif