/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:19:52 by pablo             #+#    #+#             */
/*   Updated: 2020/11/02 01:39:31 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl_sha256.h>
#include <algorithms.h>
#include <ft.h>

#include <stdio.h>

static size_t			get_chunks_nb(size_t size)
{
	return (((size + 1 + 8 + 64 - 1) & ~(64 - 1)) / 64);
}

static void				ssl_sha256_crypt_message(unsigned int* vectors, unsigned int* chunks)
{
	unsigned int		tmps[2];
	unsigned int		iterator;

	iterator = -1;
	while (++iterator < SHA256_CYCLE_IT)
	{
		tmps[0] = vectors[H] + _g(vectors[E]) + ch_u32(vectors[E], vectors[F], vectors[G]) + g_kernel[iterator] + chunks[iterator];
		tmps[1] = ma_u32(vectors[A], vectors[B], vectors[C]) + _f(vectors[A]);
		vectors[H] = vectors[G];
		vectors[G] = vectors[F];
		vectors[F] = vectors[E];
		vectors[E] = vectors[D] + tmps[0];
		vectors[D] = vectors[C];
		vectors[C] = vectors[B];
		vectors[B] = vectors[A];
		vectors[A] = tmps[0] + tmps[1];
	}
}

static void				init_tmp_array(unsigned int* dest, unsigned int* src)
{
	size_t				iterator;

	iterator = -1;
	while (++iterator < 64)
	{
		if (iterator < 16)
			dest[iterator] = swap_u32bits(src[iterator]);
		else
			dest[iterator] = _i(dest[iterator - 2]) + _h(dest[iterator - 15]) + dest[iterator - 7] + dest[iterator - 16];
	}
}

static void				ssl_sha256_crypt(t_ssl_sha256* sha256, unsigned int* data)
{
	unsigned int		tmp[64];
	int					chunk_index;
	int					update_index;

	chunk_index = -1;
	ft_bzero(tmp, 64 * sizeof(unsigned int));
	while (++chunk_index < get_chunks_nb(sha256->bytes) - 1 && (update_index = -1))
	{
		ft_memcpy(sha256->algo_buff, sha256->buff, sizeof(sha256->algo_buff));
		init_tmp_array(tmp, data + chunk_index  * 64);
		ssl_sha256_crypt_message(sha256->algo_buff, tmp);
		while (++update_index < 8)
			sha256->buff[update_index] += sha256->algo_buff[update_index];
	}
}

const char*				ssl_sha256(const char *data)
{
	t_ssl_sha256		sha256;
	unsigned char*		message;
	const unsigned int	size = ft_strlen(data);

	sha256 = (t_ssl_sha256){.buff[A] = RVEC_A, .buff[B] = RVEC_B, \
		.buff[C] = RVEC_C, .buff[D] = RVEC_D, .buff[E] = RVEC_E, \
		.buff[F] = RVEC_F, .buff[G] = RVEC_G, .buff[H] = RVEC_H};
	if (!(sha256.bytes = append_padding((unsigned char**)&message, size, get_chunks_nb(size) * 64, swap_u64bits)))
		return (NULL);
	ft_memcpy(message, data, size);	
	ssl_sha256_crypt(&sha256, (unsigned int*)message);
	free(message);
	return (int_to_str_u32(sha256.buff, 72, 8, NULL));
}