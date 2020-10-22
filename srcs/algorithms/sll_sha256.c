/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sll_sha256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:19:52 by pablo             #+#    #+#             */
/*   Updated: 2020/10/22 18:47:52 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sll_sha256.h>
#include <algorithms.h>
#include <ft.h>

static void				sll_sha256_crypt_message(unsigned int* vectors, unsigned int* chunks)
{
	unsigned int		tmps[6];
	unsigned int		iterator;

	iterator = -1;
	while (++iterator < SHA256_CYCLE_IT)
	{
		tmps[0] = vec_rot_right_u32(vectors[A], 2) ^ vec_rot_right_u32(vectors[A], 13) \
				^ vec_rot_right_u32(vectors[A], 22);
		tmps[1] = vec_rot_right_u32(vectors[E], 6) ^ vec_rot_right_u32(vectors[E], 11) \
			^ vec_rot_right_u32(vectors[E], 25);
		tmps[2] = (vectors[A] & vectors[B]) ^ (vectors[A] & vectors[C]) \
			^ (vectors[B] & vectors[C]);
		tmps[3] = (vectors[E] & vectors[F]) ^ ~(vectors[E] & vectors[G]);
		tmps[4] = tmps[0] + tmps[2];
		tmps[5] = vectors[H] + tmps[1] + tmps[3] + g_kernel[iterator] + chunks[iterator];
		vectors[H] = vectors[G];
		vectors[G] = vectors[F];
		vectors[F] = vectors[E];
		vectors[E] = vectors[D] + tmps[5];
		vectors[D] = vectors[C];
		vectors[C] = vectors[B];
		vectors[B] = vectors[A];
		vectors[A] = tmps[4] + tmps[5];
	}
}

static void				cp_array_u32bits(unsigned int* dest, unsigned int* src)
{
	unsigned long		iterator;
	unsigned int		x;
	unsigned int		y;

	ft_memcpy(dest, src, 16 *sizeof(unsigned int));
	iterator = 15;
	while (++iterator < 64)
	{
		x = vec_rot_right_u32(dest[iterator - 15], 7) \
			^ vec_rot_left_u32(dest[iterator - 15], 18) ^ (dest[iterator - 15] >> 3);
		y = vec_rot_right_u32(dest[iterator - 2], 17) \
			^ vec_rot_left_u32(dest[iterator - 2], 19) ^ (dest[iterator - 2] >> 10);
		dest[iterator] = dest[iterator - 16] + x + dest[iterator - 7] + y;
	}
}

static void				sll_sha256_crypt(t_ssl_sha256* sha256, unsigned int* data)
{
	const unsigned int	chunks_nb = sha256->bits / CHUNK_BIT_SIZE;
	unsigned int*		tmp[64];
	int					chunk_index;
	int					update_index;

	chunk_index = -1;
	ft_bzero(tmp, 64 * sizeof(unsigned int));
	while (++chunk_index < chunks_nb && (update_index = -1))
	{
		ft_memcpy(sha256->algo_buff, sha256->buff, sizeof(sha256->algo_buff));
		cp_array_u32bits(tmp, data + chunk_index * 16);
		sll_sha256_crypt_message(sha256->algo_buff, tmp);
		while (++update_index < 8)
			sha256->buff[update_index] += sha256->algo_buff[update_index];
	}
}

const char*				sll_sha256(const char *data)
{
	t_ssl_sha256		sha256;
	char*				message;
	unsigned int*		digest;
	const unsigned int	size = ft_strlen(data);
	unsigned int		bytes;

	bytes = size + 9;
	while (bytes++ * CHAR_BIT % CHUNK_BIT_SIZE)
		;
	sha256 = (t_ssl_sha256){.buff[A] = RVEC_A, .buff[B] = RVEC_B, \
		.buff[C] = RVEC_C, .buff[D] = RVEC_D, .buff[E] = RVEC_E, \
		.buff[F] = RVEC_F, .buff[G] = RVEC_G, .buff[H] = RVEC_H};
	if (!(message = ft_calloc(sizeof(char), bytes)) \
		|| !(digest = ft_calloc(sizeof(unsigned int), 8)))
		return ((void*)0);
	ft_strlcpy(message, data, size);
	sha256.bytes = append_padding_shaXXX((unsigned int*)message, size, \
			swap_u32bits);
	sha256.bits = sha256.bytes * CHAR_BIT;
	sll_sha256_crypt(&sha256, message);
	ft_memcpy(digest, sha256.buff, sizeof(sha256.buff));
	free(message);
	return (long_to_str((unsigned long*)digest, swap_u64bits));
}