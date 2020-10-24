/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 22:02:00 by pablo             #+#    #+#             */
/*   Updated: 2020/10/24 04:20:15 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <stdlib.h>

static void print_hash(const char* hash, bool rev_mode, bool endline)
{
    if (rev_mode)
        printf("%s%c", reverse((char*)hash), endline ? '\n' : '\0');
    else
        printf("%s%c", hash, endline ? '\n' : '\0');
    free((char*)hash);
}

int         hash_and_print_digest(t_parse* parse)
{
    size_t  index;

    index = 0;
    if (parse->flags & PRINT_INPUT)
        printf("%s\n", parse->input_to_print);
    // not sure (not well explained in the subject) if i must print the stdin if i only have the "-s" flag. I SUPOSSE NO.
    if (parse->pipe_data && (parse->flags & PRINT_INPUT || (!parse->files && parse->flags & STRING_INPUT) || !parse->flags))
        print_hash(parse->algorithm(parse->pipe_data), parse->flags & REV_OUTPUT, true);
    if (parse->flags & STRING_INPUT && !(parse->flags & QUIET_MODE))
        printf(MD5_STRING, parse->string_input);
    if (parse->flags & STRING_INPUT)
        print_hash(parse->algorithm(parse->string_input), parse->flags & REV_OUTPUT, !(parse->flags & REV_OUTPUT));
    if (parse->flags & STRING_INPUT && parse->flags & REV_OUTPUT && !(parse->flags & QUIET_MODE))
        printf(" \"%s\"\n", parse->string_input);
    while (parse->files && parse->files[index])
    {
        if (!(parse->flags & QUIET_MODE) && !(parse->flags & REV_OUTPUT))
            printf("%s", MD5_FILE);
        print_hash(parse->algorithm(get_data_from_file(parse->files[index++])), parse->flags & REV_OUTPUT, !(parse->flags & REV_OUTPUT));
        if (parse->flags & REV_OUTPUT && !(parse->flags & QUIET_MODE))
            printf("%s\n", " file");
    }
    clear_all(parse);
    return (0);
}
