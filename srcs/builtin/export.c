#include "minishell.h"

static void	sort_env(t_list *export);
static void	print_export(t_list *export);
static int find_in_env(t_data *data, char	*prompt);

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
		i = 1;
		arr = ft_split(data->prompt, ' ');
		if (arr[1])
			if (!find_in_env(data, arr[1]))
				ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(arr[1])));
		ft_free_str_arr(arr);
	}
}

int	find_in_env(t_data *data, char	*prompt)
{
	t_list	*temp;
	char	**arr;
	char	**env;

	temp = data->env;
	arr = ft_split(prompt, '=');
	while (temp)
	{
		env = ft_split(temp->content, '=');
		if (ft_strcmp(env[0], arr[0]) == 0)
		{
			if (arr[1])
			{
				free(temp->content);
				temp->content = ft_strdup(prompt);
			}
			ft_free_str_arr(env);
			ft_free_str_arr(arr);
			return (1);
		}
		ft_free_str_arr(env);
		temp = temp->next;
	}
	ft_free_str_arr(arr);
	return (0);
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

void	print_export(t_list *export)
{
	char	**arr;

	while (export)
	{
		arr = ft_split((char *)export->content, '=');
		if (arr[1])
			printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
		else
			printf("declare -x %s=\"\"\n", arr[0]);
		ft_free_str_arr(arr);
		export = export->next;
	}
}

// apenas permitir sobrescrever usando export

// verificar se o nome de variavel é valido e o conteudo é valido

// quando unset é usado, aquela variavel nao exite mais

// dar export da mesma variavel de novo

// quando uma pessoa for mudar uma variavel, verificar se essa variavel
// existe dentro do env, se sim, mudar ela no env

// caso a pessoa tente dar export em uma variavel que foi declarada
// anteriormente ela vai para o env
// caso a pessoa tente dar export em uma variavel que nao foi declarada
// essa variavel é exibida apenas quando é digitado 'export' e nao existe
// no env

// quando chamar o env: o que tiver sinal '=' a gente printa
// quando chamar o export: printar 'declare x' na frente e aspas
// duplas nas variaveis

//res negativo significa que a primeira string esta mais no inicio do alfabeto
//res positivo significa que a primeira string esta mais no final do alfabeto