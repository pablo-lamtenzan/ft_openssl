/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:05:49 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/25 22:10:49 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned f(unsigned b, unsigned c, unsigned d)
{
    return ((b & c) | (~b & d));
}

unsigned g(unsigned b, unsigned c, unsigned d)
{
    return ((b & d) | (c & ~d));
}

unsigned h(unsigned b, unsigned c, unsigned d)
{
    return (b ^ c ^ d);
}

unsigned i(unsigned b, unsigned c, unsigned d)
{
    return (c ^ (b | ~d));
}

unsigned int f_op(unsigned int i)
{
    return (i);
}

unsigned int g_op(unsigned int i)
{
    return ((5 * i + 1) % 16);
}

unsigned int h_op(unsigned int i)
{
    return ((3 * i + 5) % 16);
}

unsigned int i_op(unsigned int i)
{
    return ((7 * i) % 16);
}