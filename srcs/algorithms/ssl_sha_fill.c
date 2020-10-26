/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 05:51:06 by pablo             #+#    #+#             */
/*   Updated: 2020/10/26 09:01:26 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithms.h>

unsigned int ch_u32(unsigned int e, unsigned int f, unsigned int g)
{
    return ((e & f) ^ (~e & g));
}


unsigned long ch_u64(unsigned long e, unsigned long f, unsigned long g)
{
    return ((e & f) ^ (~e & g));
}

unsigned int ma_u32(unsigned int a, unsigned int b, unsigned int c)
{
    return ((a & b) ^ (a & c) ^ (b & c));
}


unsigned long ma_u64(unsigned long a, unsigned long b, unsigned long c)
{
    return ((a & b) ^ (a & c) ^ (b & c));
}

/*
unsigned int e0_u32(unsigned int a)
{
    // mmm
    return (vec_rot_left_u32(a, 2) ^ vec_rot_left_u32(a, 3) ^ vec_rot_left_u32(a, 22));
}

unsigned long e0_u64(unsigned long a)
{
    
}

unsigned int e1_u32(unsigned int e)
{

}

unsigned long e1_u64(unsigned long e)
{
    
}
*/
unsigned int _f(unsigned int x)
{
    return (vec_rot_right_u32(x, 2) ^ vec_rot_right_u32(x, 13) ^ vec_rot_right_u32(x, 22));
}

unsigned int _g(unsigned int x)
{
    return (vec_rot_right_u32(x, 6) ^ vec_rot_right_u32(x, 11) ^ vec_rot_right_u32(x, 25));
}

unsigned int _h(unsigned int x)
{
    return (vec_rot_right_u32(x, 7) ^ vec_rot_right_u32(x, 18) ^ (x >> 3));
}

unsigned int _i(unsigned int x)
{
    return (vec_rot_right_u32(x, 17) ^ vec_rot_right_u32(x, 19) ^ (x >> 10));
}

unsigned long u64_f(unsigned long x)
{
    return (vec_rot_right_u64(x, 28) ^ vec_rot_right_u64(x, 34) ^ vec_rot_right_u64(x, 39));
}

unsigned long u64_g(unsigned long x)
{
    return (vec_rot_right_u64(x, 14) ^ vec_rot_right_u64(x, 18) ^ vec_rot_right_u64(x, 41));
}

unsigned long u64_h(unsigned long x)
{
    return (vec_rot_right_u64(x, 1) ^ vec_rot_right_u64(x, 8) ^ (x >> 7));
}

unsigned long u64_i(unsigned long x)
{
    return (vec_rot_right_u64(x, 19) ^ vec_rot_right_u64(x, 361) ^ (x >> 6));
}