#include "Trees.h"
using namespace std;

void AVLTree::loadfile()
{
	ifstream fin("input.txt");
	if (!fin)
	{
		cout << "Unable to open file.";
		return;
	}

	string str;
	getline(fin, str);
	int x = stoi(str);
	for (int i = 0; i < x; ++i)
	{

		int id;
		string name;
		double gpa;
		string dept;

		getline(fin, str);
		id = stoi(str);
		getline(fin, name);
		getline(fin, str);

		gpa = stod(str);
		getline(fin, dept);

		insert_value(Student(id, name, gpa, dept));
		cardinality[dept]++;
	}
	fin.close();
}

bool AVLTree::search(Student target, AVLTree::BinaryNode *node)
{
	if (!node)
		return false;

	if (target.ID == node->data.ID)
		return true;

	if (target.ID < node->data.ID)
		return search(target, node->left);

	return search(target, node->right);
}

AVLTree::BinaryNode *AVLTree::right_rotation(AVLTree::BinaryNode *Q)
{
	AVLTree::BinaryNode *P = Q->left;
	Q->left = P->right;
	P->right = Q;
	Q->update_height();
	P->update_height();
	return P;
}

AVLTree::BinaryNode *AVLTree::left_rotation(AVLTree::BinaryNode *P)
{
	AVLTree::BinaryNode *Q = P->right;
	P->right = Q->left;
	Q->left = P;
	P->update_height();
	Q->update_height();
	return Q;
}

AVLTree::BinaryNode *AVLTree::balance(AVLTree::BinaryNode *node)
{
	if (node->balance_factor() == 2)
	{
		if (node->left->balance_factor() == -1)
			node->left = left_rotation(node->left);

		node = right_rotation(node);
	}
	else if (node->balance_factor() == -2)
	{
		if (node->right->balance_factor() == 1)
			node->right = right_rotation(node->right);

		node = left_rotation(node);
	}
	return node;
}

AVLTree::BinaryNode *AVLTree::insert_node(Student target, AVLTree::BinaryNode *node)
{
	if (target.ID < node->data.ID)
	{
		if (!node->left)
			node->left = new AVLTree::BinaryNode(target);
		else
			node->left = insert_node(target, node->left);
	}
	else if (target.ID > node->data.ID)
	{
		if (!node->right)
			node->right = new AVLTree::BinaryNode(target);
		else
			node->right = insert_node(target, node->right);
	}
	node->update_height();
	return balance(node);
}

AVLTree::BinaryNode *AVLTree::min_node(AVLTree::BinaryNode *cur)
{
	while (cur && cur->left)
		cur = cur->left;
	return cur;
}

AVLTree::BinaryNode *AVLTree::delete_node(int id, AVLTree::BinaryNode *node)
{
	if (id < node->data.ID)
		node->left = delete_node(id, node->left);
	else if (id > node->data.ID)
		node->right = delete_node(id, node->right);
	else
	{
		AVLTree::BinaryNode *tmp = node;

		if (!node->left && !node->right)
			node = nullptr;
		else if (!node->right)
			node = node->left;
		else if (!node->left)
			node = node->right;
		else
		{
			AVLTree::BinaryNode *mn = min_node(node->right);
			node->data = mn->data;
			node->right = delete_node(node->data.ID, node->right);
			tmp = nullptr;
		}
		if (tmp)
			delete tmp;
	}
	if (node)
	{
		node->update_height();
		node = balance(node);
	}
	return node;
}

void AVLTree::print_inorder(AVLTree::BinaryNode *node)
{
	if (node)
	{
		print_inorder(node->left);
		cout << "[ " << node->data.ID << ", " << node->data.name << ", " << node->data.GPA << ", "
			 << node->data.department << " ]\n";
		print_inorder(node->right);
	}
}

void AVLTree::insert_value(Student target)
{
	if (!root)
		root = new AVLTree::BinaryNode(target);
	else
		root = insert_node(target, root);
}

void AVLTree::delete_value(int id)
{
	if (root)
	{
		root = delete_node(id, root);
	}
}

void AVLTree::print_inorder()
{
	cout << "Print " << count << " Students.\n";
	print_inorder(root);
	cout << "Students per Departments:\n";
	for (auto &dept : cardinality)
	{
		cout << dept.first << " " << dept.second << " Students\n";
	}
}

int main()
{
	Student s1(13, "karim", 3.5, "CS");
	Student s2(15, "Mostafa", 3.7, "CS");
	Student s3(20, "Ibrahim", 3.7, "IS");
	Student s4(14, "Eslam", 3.6, "IS");
	Student s5(25, "Saiko", 1.2, "DS");
	AVLTree av;
	av.insert_value(s1);
	av.insert_value(s2);
	av.insert_value(s3);
	av.insert_value(s4);
	av.insert_value(s5);

	//    av.print_inorder();
	av.delete_value(3);
	av.print_inorder();
	return 0;
}
