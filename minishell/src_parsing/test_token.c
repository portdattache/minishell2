/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:29:05 by broboeuf          #+#    #+#             */
/*   Updated: 2025/04/04 16:43:02 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	printf("=== Token List ===\n");
	while (current)
	{
		printf("Type: %d, Value: [%s]\n", current->type, current->value);
		current = current->next;
	}
	printf("==================\n");
}

int	main(void)
{
	t_token *tokens;
	char *test_input[] = {"ls -l", "echo \"Hello World\"", "cat < file.txt", "prout << | oim.txt", "grep foo | wc -l", "echo test > file.txt", "ls echo Hello pwd", NULL};

	tokens = NULL;
	for (int i = 0; test_input[i] != NULL; i++)
	{
		printf("\n--- Testing: \"%s\" ---\n", test_input[i]);
		if (create_list_token(&tokens, test_input[i]))
			print_tokens(tokens);
		else
			printf("Tokenization failed!\n");
		tokens_free(&tokens);
	}
	return (0);
}
