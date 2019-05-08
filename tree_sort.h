template <typename T> 
class Tree
{
private:
	T obj;
	Tree* left;
	Tree* right;
public:
	Tree* add_val(Tree* tree, T object);
	void print_tree();
	Tree()
	{

	}
	void destroy_tree(Tree* t);
};



template <typename T>
Tree<T>* Tree<T>:: add_val (Tree* tree, T object)
{
	if (tree == nullptr)
	{
		tree = new Tree;
		tree->obj = object;
		tree->left = nullptr;
		tree->right = nullptr; 
		return tree;
	}

	if (obj > object)
		left = left->add_val(tree->left, object);
	else
		right = right->add_val(tree->right, object);
	return tree;
}

template <typename T>
void Tree <T>:: print_tree ()
{
	if (this != nullptr)
		std:: cout << obj << ' ';
	else
		return;

	if (left != nullptr)
		left->print_tree();
	if (right != nullptr)
		right->print_tree();
	return;
}	

template <typename T>
void Tree <T>:: destroy_tree(Tree* t)
{

	if (t->right != nullptr)
	{
		destroy_tree(t->right);
	}

	if (t->left != nullptr)
	{
		destroy_tree(t->left);
	}

	if (t->left == nullptr && t->right == nullptr)
	{
		free(t);
		printf("* ");
		t = nullptr;
		return;
	}

	return;
}
