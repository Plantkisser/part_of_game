#include <stdio.h>
#include <iostream>
#include "tree_sort.h"


int main()
{
	Tree<int> *t;
	t = nullptr;

	t = t->add_val(t, 2);
	t = t->add_val(t, 1);
	t = t->add_val(t, 3);

	t->print_tree();

	t->destroy_tree(t); 

	return 0;
}