/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha256.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:12:55 by pablo             #+#    #+#             */
/*   Updated: 2020/10/26 06:38:00 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_SHA256_H
# define SSL_SHA256_H

#include <limits.h>

#define A       0
#define B       1
#define C       2
#define D       3
#define E       4
#define F       5
#define G       6
#define H       7

#define RVEC_A	0x6a09e667
#define RVEC_B	0xbb67ae85
#define RVEC_C	0x3c6ef372
#define RVEC_D	0xa54ff53a
#define RVEC_E	0x510e527f
#define RVEC_F	0x9b05688c
#define RVEC_G	0x1f83d9ab
#define RVEC_H	0x5be0cd19

# define SHA256_CYCLE_IT           64

#define CHUNK_BYTE_SIZE	128
#define CHUNK_BIT_SIZE CHUNK_BYTE_SIZE * CHAR_BIT

typedef struct                  s_ssl_sha256
{
    unsigned int				buff[8];
    unsigned int				algo_buff[8];
    unsigned int				bits;
    unsigned int				bytes;
}                               t_ssl_sha256;

/* first 32 bits of the fractional part of the cube root of the 64 1st primes */
static unsigned int const	g_kernel[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

unsigned int ch_u32(unsigned int e, unsigned int f, unsigned int g);
unsigned int ma_u32(unsigned int a, unsigned int b, unsigned int c);
unsigned int e0_u32(unsigned int a);
unsigned int o1_u32(unsigned int e);
unsigned int _f(unsigned int x);
unsigned int _g(unsigned int x);
unsigned int _h(unsigned int x);
unsigned int _i(unsigned int x);

#endif