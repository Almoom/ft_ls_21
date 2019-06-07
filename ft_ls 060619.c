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
#include <sys/stat.h>
#include "ft_ls.h"

t_btree		*btree_create_node(char *item)
{
	t_btree *tree;

	if ((tree = malloc(sizeof(t_btree))) == NULL)
		return (NULL);
	if (tree)
	{
		tree->item = item;
		tree->left = NULL;
		tree->right = NULL;
	}
	return (tree);
}

void 	ft_create_tree(t_btree *root, t_btree *new)
{
	while (root)
	{
		if (ft_strcmp(root->item, new->item) < 0)
		{
			if (root->right)
				root = root->right;
			else
			{
				root->right = new;
				break ;
			}
		}
		else
		{
			if (root->left)
				root = root->left;
			else
			{
				root->left = new;
				break ;
			}
		}
	}
}

void	ft_print_tree(t_btree *root)
{
	t_btree *tree;

	if (!(tree = root))
		return ;
	else
	{
		ft_print_tree(tree->left);
		printf("%s\n", tree->item);
		ft_print_tree(tree->right);
	}
}

void 	ft_create_tree_r(t_btree *root, t_btree *new)
{
	while (root)
	{
		if (ft_strcmp(root->item, new->item) > 0)
		{
			if (root->right)
				root = root->right;
			else
			{
				root->right = new;
				break ;
			}
		}
		else
		{
			if (root->left)
				root = root->left;
			else
			{
				root->left = new;
				break ;
			}
		}
	}
}

int	ft_ls_simple(char *name, int flag)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				i;
	t_btree			*root;

	i = 0;
	//printf("%s\n", "--");
	if (!(dirp = opendir(name)))
		return (0);
	while ((dp = readdir(dirp)))
	{
		if (dp->d_name[0] != '.' && flag == 0)
		{
			i == 0 ? root = btree_create_node(dp->d_name) : ft_create_tree(root, btree_create_node(dp->d_name));
			i = 1;
		}
		if (flag == 1)
		{
			i == 0 ? root = btree_create_node(dp->d_name) : ft_create_tree(root, btree_create_node(dp->d_name));
			i = 1;
		}
		if (dp->d_name[0] != '.' && flag == 2)
		{
			i == 0 ? root = btree_create_node(dp->d_name) : ft_create_tree_r(root, btree_create_node(dp->d_name));
			i = 1;
		}
		if (flag == 3)
		{
			i == 0 ? root = btree_create_node(dp->d_name) : ft_create_tree_r(root, btree_create_node(dp->d_name));
			i = 1;
		}
		// if (ft_strcmp(dp->d_name, ".") != 0 && ft_strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.' && flag == 0)
		// {
		// 	ft_ls_simple(ft_strjoin_free(ft_strjoinchar(name, '/', 0), dp->d_name, 0, 0), 0);
		// }
	}
	ft_print_tree(root);
	(void)closedir(dirp);
	return (1);
}

void 	ft_check_flags(char *s, char *arr)
{
	int i;

	i = 0;
	while (s[0] == '-' && s[++i])
		if (ft_strchr("CFRacdilqrtu", s[i]))
			arr[s[i]] = s[i];
}

int		ft_error_flags(char *arr)
{
	int i;

	i = 0;
	while (arr[i] == '-')
		i++;
	if (i == 128)
		return (1);
	return (0);
}

void 	ft_separ(char *arr, char *s)
{
	if (s[0] == '-')
		s = ".";
	if (ft_strchr(arr, 'a') && ft_strchr(arr, 'r'))
		ft_ls_simple(s, 3);
	else if (ft_strchr(arr, 'a'))
		ft_ls_simple(s, 1);
	else if (ft_strchr(arr, 'r'))
		ft_ls_simple(s, 2);
}

int		main(int argc, char **argv)
{
	int i;
	char arr[129];

	i = 0;
	ft_memset(arr, '-', 128);
	arr[128] = 0;
	if (argc == 1)
		ft_ls_simple(".", 0);
	else
	{
		while (++i < argc)
			ft_check_flags(argv[i], arr);
		ft_error_flags(arr) ? ft_ls_simple(argv[i - 1], 0) : ft_separ(arr, argv[i - 1]);
	}
	printf("%s\n", arr);
	return (0);
}
