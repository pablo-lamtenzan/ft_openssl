/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_sha512.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:31:20 by pablo             #+#    #+#             */
/*   Updated: 2020/11/02 01:39:41 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl_sha512.h>
#include <algorithms.h>
#include <ft.h>

static unsigned long	get_chunks_nb(unsigned long size)
{
	return (((size + 1 + 8 + 128 - 1) & ~(128 - 1)) / 128);
}

static void				ssl_sha512_crypt_message(unsigned long* vectors, unsigned long* chunks)
{
	unsigned long		tmps[2];
	unsigned int		iterator;

	iterator = -1;
	while (++iterator < SHA512_CYCLE_IT)
	{
		tmps[0] = vectors[H] + u64_g(vectors[E]) + ch_u64(vectors[E], vectors[F], vectors[G]) + g_kernel[iterator] + chunks[iterator];
		tmps[1] = ma_u64(vectors[A], vectors[B], vectors[C]) + u64_f(vectors[A]);
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

static void				init_tmp_array(unsigned long* dest, unsigned long* src)
{
	int				iterator;

	iterator = -1;
	while (++iterator < 80)
	{
		if (iterator < 16)
			dest[iterator] = swap_u64bits(src[iterator]);
		else
			dest[iterator] = u64_i(dest[iterator - 2]) + u64_h(dest[iterator - 15]) + dest[iterator - 7] + dest[iterator - 16];
	}
}

static void				ssl_sha512_crypt(t_ssl_sha512* sha512, unsigned long* data)
{
	unsigned long		tmp[80];
	int					chunk_index;
	int					update_index;

	chunk_index = -1;
	ft_bzero(tmp, 80 * sizeof(unsigned long));
	while (++chunk_index < get_chunks_nb(sha512->bytes) - 1 && (update_index = -1))
	{
		ft_memcpy(sha512->algo_buff, sha512->buff, sizeof(sha512->algo_buff));
		init_tmp_array(tmp, data + chunk_index * 128);
		ssl_sha512_crypt_message(sha512->algo_buff, tmp);
		while (++update_index < 8)
			sha512->buff[update_index] += sha512->algo_buff[update_index];
	}
}

const char*				ssl_sha512(const char *data)
{
	t_ssl_sha512		sha512;
	char*				message;
	const unsigned int	size = ft_strlen(data);

	sha512 = (t_ssl_sha512){.buff[A] = RVEC_A, .buff[B] = RVEC_B, \
		.buff[C] = RVEC_C, .buff[D] = RVEC_D, .buff[E] = RVEC_E, \
		.buff[F] = RVEC_F, .buff[G] = RVEC_G, .buff[H] = RVEC_H};
	if (!(sha512.bytes = append_padding((unsigned char**)&message, size, get_chunks_nb(size) * 128, swap_u64bits)))
		return (NULL);
	ft_memcpy(message, data, size);
	ssl_sha512_crypt(&sha512, (unsigned long*)message);
	free(message);
	return (long_to_str_u64(sha512.buff, 144, 8, NULL));
}
