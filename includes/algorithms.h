/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:18:33 by pablo             #+#    #+#             */
/*   Updated: 2020/10/21 19:40:03 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

const char*             int_to_str(unsigned int* digest,
        unsigned int (*litle_endian)(unsigned int));
unsigned int            swap_u32bits(unsigned int target);
unsigned long           swap_u64bits(unsigned long target);
unsigned int            vec_rot_left_u32(unsigned int vec, unsigned int rot);
unsigned int            vec_rot_right_u32(unsigned int vec, unsigned int rot);
unsigned long           vec_rot_left_u64(unsigned long vec, unsigned long rot);
unsigned long           vec_rot_right_u64(unsigned long vec, unsigned long rot);

#endif