
#include "working_file.h"
#include "tree_func.h"
#include "calc.h"
#include "differentiator.h"


char *s = NULL;

int main()
{

  tree *top = (tree *) calloc(1, sizeof(tree));
  char* string = read_file_in_array();

  top->size = 0;
  top->root = getG(string);


  FILE *source = fopen("source_expressions.dot", "w");
  tree_print(top, source);

  tree *top_1 = (tree *) calloc(1, sizeof(tree));
  top_1 -> root = Diff(top->root);
  delete_zero(top_1->root);
  delete_const(top_1->root);

  FILE *diff_express = fopen("diff_express.dot", "w");
  tree_print(top_1,diff_express);

  FILE* f = fopen("difff.txt", "w");
  write_tree_in_txt(top_1->root, f);

  FILE* ff = fopen("difff.tex", "w");
  begin_latex(ff);
  tree_pdf(top_1 -> root, ff);
  end_latex(ff);

  fclose(source);
  fclose(diff_express);
  fclose(f);
  fclose(ff);


  system("dot -Tpng source_expressions.dot -o tree_source.png");
  system("dot -Tpng diff_express.dot -o tree_diff.png");
  system("pdflatex difff.tex");
  system("gio open difff.pdf");
}

