/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:15:36 by ljalikak          #+#    #+#             */
/*   Updated: 2019/05/26 18:15:38 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include "ft_ls.h"
#include <errno.h>

// t_ls	*ft_lst_add(t_ls *head, t_ls *new) //-R
// {
// 	t_ls *t;
//
// 	t = head;
// 	while (t)
// 	{
// 		if (ft_strcmp(t->way, new->way) > 0 || (ft_strcmp(t->way, new->way) == 0 && ft_strcmp(t->nm, new->nm) > 0))
// 			break ;
// 		if (t->next)
// 		{
// 			t->next->par = t;
// 			t = t->next;
// 		}
// 		else
// 		{
// 			t->next = new;
// 			t->next->par = t;
// 			return (head);
// 		}
// 	}
// 	t->par->next = new;
// 	new->par = t->par;
// 	new->next = t;
// 	t->par = new;
// 	return (head);
// }

t_ls	*ft_lst_add(t_ls *head, t_ls *new) //-Rr
{
	t_ls *t;

	t = head;
	while (t)
	{
		if ((ft_strcmp(t->way, new->way) < 0 && t->par) || (ft_strcmp(t->way, new->way) == 0 && ft_strcmp(t->nm, new->nm) < 0))
		{
			t->par->next = new;
			new->par = t->par;
			new->next = t;
			t->par = new;
			return (head);
		}
		// if (ft_strcmp(t->way, new->way) < 0 && t->next)
		// {
		// 	new->next = t->next;
		// 	t->next = new;
		// 	new->par = t;
		// 	new->next->par = new;
		// 	return (head);
		// }
		if (t->next)
		{
			t->next->par = t;
			t = t->next;
		}
		else
		{
			t->next = new;
			t->next->par = t;
			return (head);
		}
	}

	return (head);
}

t_ls	*ft_lst_new(void const *nm, size_t nm_len, int i, char *way)
{
	t_ls *list;

	if (!(list = (t_ls*)ft_memalloc(sizeof(t_ls))))
		return (NULL);
	if (nm == NULL)
	{
		nm_len = 0;
		list->nm = NULL;
	}
	else
	{
		if (!(list->nm = ft_strnew(nm_len)) || !(list->way = ft_strnew(ft_strlen(way))))
		{
			ft_memdel((void**)&list);
			return (NULL);
		}
		ft_memcpy(list->nm, nm, nm_len);
		ft_memcpy(list->way, way, ft_strlen(way));
	}
	list->max = list->nm_len = nm_len;
	list->next = list->par = NULL;
	list->inv = i;
	return (list);
}

t_t	*ft_t_add(t_t *head, t_t *new)
{
	t_t *t;

	t = head;
	while (t)
	{
		if (t->next)
			t = t->next;
		else
			break ;
	}
	t->next = new;
	return (head);
}

t_t	*ft_t_new(t_ls *list)
{
	t_t *l;

	if (!(l = (t_t*)ft_memalloc(sizeof(t_t))))
		return (NULL);
	if (!(l->way = ft_strnew(ft_strlen(list->way))))
	{
		ft_memdel((void**)&l);
		return (NULL);
	}
	ft_memcpy(l->way, list->way, ft_strlen(list->way));
	l->max = ft_strlen(list->nm);
	return (l);
}

void	ft_max(t_ls *head, t_t *h)
{
	t_ls *list;
	t_t *l;

	list = head;
	l = h;
	while (list)
	{
		while (l)
		{
			if (ft_strcmp(l->way, list->way) == 0)
			{
				list->max = l->max;
				break ;
			}
			if (l->next)
				l = l->next;
			else
				break ;
		}
		if (list->next)
			list = list->next;
		else
			break ;
	}
}

t_ls *ft_lsr(char *name, t_ls *head, int i)
{
	DIR *dirp;
	struct dirent *dp;
	char *t;
	t_ls *list;

	i++;
	dirp = opendir(name);
	if (dirp == NULL)
	{
		free(name);
		return (head);
	}
	t = ft_strjoinchar(name, '/', 1);
	while ((dp = readdir(dirp)))
	{

		// list = ft_lst_new(dp->d_name, dp->d_namlen);
		// ft_lst_add(head, list);
		if (ft_strcmp(dp->d_name, ".") != 0 && ft_strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.')
		{
			//printf("%s\n", dp->d_name);
			list = ft_lst_new(dp->d_name, dp->d_namlen, i, t);
			head = ft_lst_add(head, list);
			ft_lsr(ft_strjoin_free(t, dp->d_name, 0, 0), head, i);
		}
	}
	free(t);
	(void)closedir(dirp);
	return (head);
}

t_t *ft_m(t_t *h, t_ls *list)
{
	t_t *t;

	t = h;
	while (t)
	{

		if (ft_strcmp(t->way, list->way) == 0)
		{
			t->max = t->max > ft_strlen(list->nm) ? t->max : ft_strlen(list->nm);
			return (h);
		}
		if (t->next)
			t = t->next;
		else
			break ;
	}
	t->next = ft_t_new(list);
	return (h);
}

int		main()//int argc, char **argv)
{
	t_ls *list;
	t_ls *head;
	t_t *h;
	t_t *l;
	char *name;
	int i;

	i = 0;
	name = ".";
	head = ft_lst_new(name, ft_strlen(name), i, name);
	h = ft_t_new(head);
	list = ft_lsr(ft_strdup(name), head, i);
	while (list)
	{
		l = ft_m(h, list);
		if (list->next)
			list = list->next;
		else
			break ;
	}
	ft_max(head, h);
	// list = head; // -R
	// while (list)
	// {
	// 	if (list->par)
	// 	{
	// 		if (ft_strcmp(list->par->way, list->way) != 0 && ft_strncmp(name, list->way, ft_strlen(list->way) - 1))
	// 			printf("%s\n", list->way);
	// 		if (list->next && ft_strcmp(list->next->way, list->way) != 0)
	// 			printf("%s", list->nm);
	// 		else if (!(list->next))
	// 			printf("%s\n", list->nm);
	// 		else
	// 			printf("%-*s", list->max + 3, list->nm);
	// 		if (list-> next && ft_strcmp(list->next->way, list->way) != 0)
	// 			printf("%s\n\n", "");
	//
	// 		//printf("%d\t%d\t%s\t%s\n", list->max, list->inv, list->way, list->nm);
	// 	}
	// 	if (list->next)
	// 		list = list->next;
	// 	else
	// 		break ;
	// }
	list = head; // -Rr
	while (list)
	{
		if (list->par)
		{
			if (list-> next && ft_strncmp(name, list->way, ft_strlen(list->way) - 1) == 0)
				printf("%-*s", list->max + 3, list->nm);
			else
				printf("%s\n", list->nm);
			// if (ft_strcmp(list->par->way, list->way) != 0 && ft_strncmp(name, list->way, ft_strlen(list->way) - 1))
			// 	printf("%s\n", list->way);
			// if (list->next && ft_strcmp(list->next->way, list->way) != 0)
			// 	printf("%s", list->nm);
			// else if (!(list->next))
			// 	printf("%s\n", list->nm);
			// else
			// 	printf("%-*s", list->max + 3, list->nm);
			// if (list-> next && ft_strcmp(list->next->way, list->way) != 0)
			// 	printf("%s\n\n", "");
		}
		if (list->next)
			list = list->next;
		else
			break ;
	}
	// l = h;
	// printf("%s\n", "============");
	// while (l)
	// {
	//
	// 	printf("%zu -- %s\n", l->max, l->way);
	// 	if (l->next)
	// 		l = l->next;
	// 	else
	// 		break ;
	// }

	return (0);
}
