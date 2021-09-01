#include "tree_func.h"
#include "akin_game_func.h"
#include "working_file.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



int main()
{
	system("clear");

	tree *s = (tree *) malloc(sizeof(tree));

	char* tree_text = read_file_in_array();

	int i = 0;

	s -> root = formation_tree(s, tree_text, &i);
	FILE* file = fopen("base.txt", "w");

	printf("Welcome! Poigraem??\n");
	printf("Options: [1] - start game\n"
					"[2] - show tree\n"
					"[0] - ya naigralsya...\n");
	int ans, rrr;
	//scanf("%d", &ans);
	ans = getchar();
	rrr = getchar();
	while (1)
	{
		switch (ans)
		{
			case '1':
			{
				play_akin(s);
				write_tree_in_txt(s->root, file);
				tree_print(s);
				break;
			}
			case '2':
			{
				write_tree_in_txt(s->root, file);
				tree_print(s);
				system("dot -Tpng dump.dot -o tree_show.png");
				system("xviewer tree_show.png");
				break;
			}
			case '0':
			{
				printf("Bye!");
				exit(0);
			}
			default:
			{
				printf("Options: [1] - start game\n"
						"[2] - show tree\n"
						"[0] - ya naigralsya...\n");
				break;
			}
		}
		printf("Options: [1] - start game\n"
					"[2] - show tree\n"
					"[0] - ya naigralsya...\n");
		ans = getchar();
	}
}