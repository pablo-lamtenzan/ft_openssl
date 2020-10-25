/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:45:52 by pablo             #+#    #+#             */
/*   Updated: 2020/10/25 05:03:13 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

#include <stdbool.h>
#include <stdlib.h>

#define ERROR_USAGE         1
#define ERROR_ALGONAME      2
#define ERROR_FILENF        4
#define ERROR_STRING        8

#define MSG_USAGE           "usage: ft_ssl command [command opts] [command args]\n"
#define MSG_ALGONAME        "ft_ssl: Error: %s is an invalid command.\n\nStandard commands:\n\nMessage Digest commands:\nmd5\nsha256\nsha512\nwirthlpool\n\nCipher commands:\n"
#define MSG_FILENF          "ft_ssl: Error: %s: No such file or dirrectory\n"
#define MSG_STRING           "ft_ssl: Error: Fatal: Flags -s misconfiguration or bad format\n"

bool        print_error(void* check, char error_code, char* arg);

#endif