/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:18:33 by pablo             #+#    #+#             */
/*   Updated: 2020/10/20 18:34:22 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

const char*         int_to_str(unsigned int* digest,
        unsigned int (*litle_endian)(unsigned int));
unsigned int        swap_32bits(unsigned int target);
unsigned long       swap_64bits(unsigned long target);


#endif