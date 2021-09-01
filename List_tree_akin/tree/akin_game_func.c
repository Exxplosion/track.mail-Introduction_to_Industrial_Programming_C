#include "akin_game_func.h"

void add_node(tree* s, node* node_supp)
{
    char *ans = (char *) malloc(30 * sizeof(char));
    char *otl = (char *) malloc(30 * sizeof(char));
    if(ans == NULL || otl == NULL)
    {
        errno = NOPE_MEM;
        err("NOPE_MEM");
    }
	scanf("%s", ans);
	ans[strlen(ans)] = '\0';

    printf("Kakoe otli4ie %s & %s?\n", ans, node_supp -> val);
    getchar(); //мб как-то по- другому можно...
 	fgets(otl, 50, stdin);
	otl[strlen(otl) - 1] = '\0';

    char* previous = node_supp -> val;
    node_supp -> val = otl;

    node_push_after(s, RIGHT, previous, node_supp);
    node_push_after(s, LEFT, ans, node_supp);
    printf("Okey!\n");
}


void play_akin(tree *t)
{
    assert(t != NULL);

    char c,n;
    node* node_supp = t->root;

    while (node_supp->left)
    {
        printf("%s? y - yes, n - no\n", node_supp->val);
        scanf("%c", &c); //fix it...
        scanf("%c", &m);

        //fgets(str, 100, stdin);

        switch (c)
        {
            case 'y':
            {
                node_supp = node_supp -> left;
                break;
            }
            case 'n':
            {
                node_supp = node_supp -> right;
                break;
            }
            default: 
            {
                printf("return\n");
                break;
            }
        }
    }

    printf("eto %s, y - yes n - no?????\n", node_supp->val);
    scanf ("%c", &c);
    scanf ("%c", &m);

    switch (c)
        {
            case 'y':
            {
                printf("heh heheeheheheheheheh\n");
                break;
            }
            case 'n':
            {
                printf("Ya eshe ychys... \n");
                printf("A KTO ETO???\n");
                add_node(t, node_supp);
                break;
            }
            default: 
            {
                printf("return2, /%c/ \n", m);
                break;
            }
        }
}