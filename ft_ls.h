/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:17:09 by ljalikak          #+#    #+#             */
/*   Updated: 2019/05/26 18:17:11 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "/Users/ljalikak/Documents/Libft/Libft_21/libft.h"
# include <stdarg.h>

typedef struct		s_ls
{
	char			*nm;
	size_t			nm_len;
	char			*way;
	size_t			max;
	int				inv;
	struct s_ls		*next;
	struct s_ls 	*par;
}					t_ls;
typedef struct		s_t
{
	char			*way;
	size_t			max;
	struct s_ls		*next;
}					t_t;
#endif
