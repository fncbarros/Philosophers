/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:42:55 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/23 15:42:56 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <stdio.h>
# include <unistd.h>
# include <stdint.h>

int		argcheck(int argc, char **argv);
int		ft_printerr(int n);
/*int		set_error(int *ptr, int err);*/

#endif
