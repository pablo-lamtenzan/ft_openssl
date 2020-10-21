/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha512.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:31:20 by pablo             #+#    #+#             */
/*   Updated: 2020/10/21 20:09:47 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl_sha512.h>
#include <algorithms.h>
#include <ft.h>

static void				sll_sha256_crypt_message(unsigned long* vectors, unsigned long* chunks)
{
	unsigned long		tmps[6];
	unsigned int		iterator;

	iterator = -1;
	while (++iterator < SHA256_CYCLE_IT)
	{
		tmps[0] = vec_rot_right_u64(vectors[A], 28) ^ vec_rot_right_u64(vectors[A], 34) \
				^ vec_rot_right_u64(vectors[A], 39);
		tmps[1] = vec_rot_right_u64(vectors[E], 14) ^ vec_rot_right_u64(vectors[E], 18) \
			^ vec_rot_right_u64(vectors[E], 41);
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

static void				cp_array_u64bits(unsigned long* dest, unsigned long* src)
{
	unsigned long		iterator;
	unsigned long		x;
	unsigned long		y;

	ft_memcpy(dest, src, 16 *sizeof(unsigned int));
	iterator = 15;
	while (++iterator < 80)
	{
		x = vec_rot_right_u64(dest[iterator - 15], 1) \
			^ vec_rot_left_u64(dest[iterator - 15], 8) ^ (dest[iterator - 15] >> 7);
		y = vec_rot_right_u64(dest[iterator - 2], 19) \
			^ vec_rot_left_u64(dest[iterator - 2], 61) ^ (dest[iterator - 2] >> 6);
		dest[iterator] = dest[iterator - 16] + x + dest[iterator - 7] + y;
	}
}

static void				sll_sha512_crypt(t_ssl_sha512* sha512, unsigned char* data)
{
	const unsigned int	chunks_nb = sha512->bits / CHUNK_BIT_SIZE;
	unsigned long*		tmp;
	int					chunk_index;
	int					update_index;

	chunk_index = -1;
	if (!(tmp = ft_calloc(sizeof(unsigned long), 80)))
		return ; // this isn't secure
	while (++chunk_index < chunks_nb && (update_index = -1))
	{
		ft_memcpy(sha512->algo_buff, sha512->buff, sizeof(sha512->algo_buff));
		cp_array_u64bits(tmp, (unsigned long *)(data + chunk_index * CHUNK_BYTE_SIZE));
		sll_sha512_crypt_message(sha512->algo_buff, tmp);
		while (++update_index < 8)
			sha512->buff[update_index] += sha512->algo_buff[update_index];
	}
	free(tmp);
}

const char*				sll_sha512(const char *data)
{
	t_ssl_sha512		sha512;
	char*				message;
	unsigned int*		digest;
	const unsigned int	size = ft_strlen(data);
	unsigned int		bytes;

	bytes = size + 9 + CHAR_BIT;
	while (bytes++ * CHAR_BIT % CHUNK_BIT_SIZE)
		;
	sha512 = (t_ssl_sha512){.buff[A] = RVEC_A, .buff[B] = RVEC_B, \
		.buff[C] = RVEC_C, .buff[D] = RVEC_D, .buff[E] = RVEC_E, \
		.buff[F] = RVEC_F, .buff[G] = RVEC_G, .buff[H] = RVEC_H};
	if (!(message = ft_calloc(1, bytes)) \
		|| !(digest = ft_calloc(1, sizeof(sha512.buff))))
		return ((void*)0);
	ft_strlcpy(message, data, size);
	sha512.bytes = append_padding_shaXXX((unsigned long*)message, size, \
			swap_u64bits);
	sha512.bits = sha512.bytes * CHAR_BIT;
	sll_sha256_crypt(&sha512, message);
	ft_memcpy(digest, sha512.buff, sizeof(sha512.buff));
	free(message);
	return (int_to_str(digest, swap_u64bits));
}
