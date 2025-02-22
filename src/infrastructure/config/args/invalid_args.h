/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:01:25 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/22 12:18:13 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVALID_ARGS_H
# define INVALID_ARGS_H

# include <stdbool.h>
# include <stddef.h>

enum e_args
{
	MAX_ARG = 1,
};

bool	is_invalid_args(int argc, char *filename);

#endif
