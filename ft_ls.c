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

t_ls	*ft_lst_add(t_ls *head, t_ls *new)
{
	t_ls *t;
	t_ls *tmp;
	t_ls *pre;

	t = head;
	while (t)
	{
		//printf("%s -- %s\n", t->nm, new->nm);
		//printf("%s -- %s\n", t->way, new->way);
		if (ft_strcmp(t->way, new->way) > 0 || (ft_strcmp(t->way, new->way) == 0 && ft_strcmp(t->nm, new->nm) > 0))
			break ;
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
	t->par->next = new;
	new->par = t->par;
	new->next = t;
	t->par = new;
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

// t_t	*ft_t_new(size_t max, char *way)
// {
// 	t_t *list;
//
// 	if (!(list = (t_t*)ft_memalloc(sizeof(t_t))))
// 		return (NULL);
// 	if (!(list->way = ft_strnew(ft_strlen(way))))
// 	{
// 		ft_memdel((void**)&list);
// 		return (NULL);
// 	}
// 	ft_memcpy(list->way, way, ft_strlen(way));
// 	list->max = nm_len;
// 	return (list);
// }

void	ft_max(t_ls *head)
{
	t_ls *list;

	list = head;
	while (list)
	{
		if (list->par && ft_strcmp(list->par->way, list->way) == 0)
			list->par->nm_len = list->nm_len = list->par->max = list->max = list->par->nm_len > list->nm_len ? list->par->nm_len : list->nm_len;
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
	int j = 0;

	i++;
	//printf("%d\n", i);
	dirp = opendir(name);
	if (dirp == NULL)
	{
		free(name);
		return (head);
	}
	t = ft_strjoinchar(name, '/', 1);
	//printf("%s\n", t);
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
	while (j++ < 10)
		ft_max(head);
	free(t);
	(void)closedir(dirp);
	return (head);
}

int		main()//int argc, char **argv)
{
	t_ls *list;
	t_ls *head;
	char *name;
	int i;

	i = -1;
	name = ".";
	head = ft_lst_new(name, ft_strlen(name), i, name);
	//ft_lsr("/Users/ljalikak");
	list = ft_lsr(ft_strdup(name), head, i);
	while (list)
	{
		//if (list->par)
		printf("%zu\t%s\t%s\n", list->max, list->way, list->nm);
		if (list->next)
			list = list->next;
		else
			break ;
	}
	return (0);
}

// t_t	*ft_t_new(size_t max, char *way)
// {
// 	t_t *list;
//
// 	if (!(list = (t_t*)ft_memalloc(sizeof(t_t))))
// 		return (NULL);
// 	if (!(list->way = ft_strnew(ft_strlen(way))))
// 	{
// 		ft_memdel((void
// t_t	*ft_t_new(size_t max, char *way)
// {
// 	t_t *list;
//
// 	if (!(list = (t_t*)ft_memalloc(sizeof(t_t))))
// 		return (NULL);
// 	if (!(list->way = ft_strnew(ft_strlen(way))))
// 	{
// 		ft_memdel((void
// t_t	*ft_t_new(size_t max, char *way)
// {
// 	t_t *list;
//
// 	if (!(list = (t_t*)ft_memalloc(sizeof(t_t))))
// 		return (NULL);
// 	if (!(list->way = ft_strnew(ft_strlen(way))))
// 	{
// 		ft_memdel((void
