/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:18:33 by pablo             #+#    #+#             */
/*   Updated: 2020/10/20 22:14:38 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

const char*             int_to_str(unsigned int* digest,
        unsigned int (*litle_endian)(unsigned int));
unsigned int            swap_u32bits(unsigned int target);
unsigned long           swap_u64bits(unsigned long target);
unsigned                vec_rot_left(unsigned vec, unsigned rot);
unsigned int            vec_rot_right(unsigned int vec, unsigned int rot);


#endif