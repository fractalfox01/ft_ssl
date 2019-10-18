/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:11:05 by tvandivi          #+#    #+#             */
/*   Updated: 2019/10/12 11:21:52 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static int	get_pad_nbr(int bitlen)
{
	int	padbits;

	padbits = 0;
	while (((bitlen + padbits) % 512) < 448)
	{
		padbits++;
	}
	return (padbits);
}

static void    helper_md5(t_md5_ctx *context, unsigned int orig, unsigned int padb, unsigned char *p_msg)
{
    int    a;
    int    i;
    long            final;
    i = 56;
	final = (long long)(orig * 8) >> i;
	while (a++ < 8)
	{
		p_msg[(orig + ((padb + (56 - i)) / 8))] = final;
		i -= 8;
		final = (long long)(orig * 8) >> i;
	}
	context->size = orig + (padb / 8) + 8;
	context->msg = (unsigned char *)malloc(sizeof(unsigned char) * context->size);
	ft_memcpy(context->msg, p_msg, (orig + (padb / 8) + 8));
}

void		init_padr(t_pad *padr, int bitl)
{
	padr->b = 0;
	padr->i = 0;
	padr->o_b = bitl;
	padr->orig = bitl;
	padr->p_fin = 0;
	if (bitl > 512)
	{
		padr->i = bitl / 512;
		bitl = bitl - (padr->i * 512);
		padr->i = 0;
	}
	padr->padb = get_pad_nbr(bitl * 8);
	padr->a = ((padr->orig * 8) + padr->padb) + 64;
	padr->p_msg = (unsigned char *)malloc(sizeof(unsigned char) * (padr->a / 8));
	ft_bzero(padr->p_msg, (padr->a / 8));
	padr->a = 0;
}

int			md5_pad_msg(t_md5_ctx *context, int bitlen, unsigned char *d)
{
	t_pad	padr;

	init_padr(&padr, bitlen);
	ft_memcpy(padr.p_msg, d, padr.orig);
	padr.p_msg[padr.o_b++] = 0x80;
	padr.i = 56;
	padr.p_fin = (long long)(padr.orig * 8) >> padr.i;
	while (padr.a++ < 8)
	{
		padr.p_msg[(padr.orig + ((padr.padb + (56 - padr.i)) / 8))] = padr.p_fin;
		padr.i -= 8;
		padr.p_fin = (long long)(padr.orig * 8) >> padr.i;
	}
	context->size = (padr.orig + (padr.padb / 8)) + 8;
	context->msg = (unsigned char *)malloc(sizeof(unsigned char) * context->size);
	ft_memcpy(context->msg, padr.p_msg, (padr.orig + (padr.padb / 8)) + 8);
	return (1);

}

void			ft_ssl_print_bits(t_md5_ctx *context)
{
	int	i;

	i = 0;
	ft_printf("Padded bits:\n");
	while (i < context->size)
	{
		ft_printf("%10hhb ", context->msg[i]);
		i++;
		if ((i % 8) == 0 && i != 0)
			ft_printf("\n");
	}
	ft_printf("\nEnd of bits:\n");
}