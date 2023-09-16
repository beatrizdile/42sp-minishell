#include "minishell.h"

static void	search_export(t_data *data, char *str);
static void	sort_env(t_list *export);
static void	print_export(t_list *export);

void	export_builtin(t_data *data)
{
	t_list	*export;
	char	**arr;
	int		i;

	export = NULL;
	if (!ft_strcmp(data->prompt, "export"))
		sort_env(copy_env_list(data->env, export));
	else
	{
		i = 0;
		arr = ft_split(data->prompt, ' ');
		while (arr[i] != NULL)
		{
			search_export(data, arr[i]);
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	sort_env(t_list *export)
{
	t_list	*temp1;
	t_list	*temp2;
	int		swapped;

	temp2 = NULL;
	while (true)
	{
		temp1 = export;
		swapped = 0;
		while (temp1->next != temp2)
		{
			if (ft_strcmp(temp1->content, temp1->next->content) > 0)
			{
				ft_swap_lst(temp1);
				swapped = 1;
			}
			temp1 = temp1->next;
		}
		temp2 = temp1;
		if (!swapped)
			break ;
	}
	print_export(export);
	free_list(export);
}

static void	search_export(t_data *data, char *str)
{
	t_var	*temp;

	temp = data->var;
	while (temp)
	{
		if (ft_strcmp(temp->key, str) == 0)
		{
			ft_lstadd_back(&data->env, ft_lstnew(temp->str));
			break ;
		}
		temp = temp->next;
	}
}

void	print_export(t_list *export)
{
	while (export)
	{
		printf("%s\n", (char *)export->content);
		export = export->next;
	}
}

// caso a pessoa tente dar export em uma variavel que foi declarada
// anteriormente ela vai para o env
// caso a pessoa tente dar export em uma variavel que nao foi declarada
// essa variavel é exibida apenas quando é digitado 'export'

// deixar o env inteiro dentro do var
// quando chamar o env: o que tiver sinal '=' a gente printa
// quando chamar o export: printar 'declare x' na frente e aspas
// duplas nas variaveis

//res negativo significa que a primeira string esta mais no inicio do alfabeto
//res positivo significa que a primeira string esta mais no final do alfabeto