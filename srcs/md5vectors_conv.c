/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5vectors_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:05:49 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/02 17:23:10 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned vec_f(unsigned b, unsigned c, unsigned d)
{
    return ((b) & (c)) | (~(b) & (d));
}

unsigned vec_g(unsigned b, unsigned c, unsigned d)
{
    return (((b) & (d)) | ((c) & ~(d)));
}

unsigned vec_h(unsigned b, unsigned c, unsigned d)
{
    return ((b) ^ (c) ^ (d));
}

unsigned vec_i(unsigned b, unsigned c, unsigned d)
{
    return ((c) ^ (b | ~(d)));
}

unsigned vec_rot_left(unsigned vec, unsigned rot)
{
    return (((vec) << (rot)) | (vec) >> (32 - (rot)))
}