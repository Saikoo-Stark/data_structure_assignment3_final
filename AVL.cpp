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
	}
	fin.close();
}

AVLTree::BinaryNode *AVLTree::search(int id, AVLTree::BinaryNode *node)
{
	if (!node)
		return nullptr;

	if (id == node->data.ID)
		return node;

	if (id < node->data.ID)
		return search(id, node->left);

	return search(id, node->right);
}

void AVLTree::searchID(int id)
{
	if (!search(id, root))
	{
		cout << "ID : " << id << " is not found !" << endl;
	}
	else
	{
		search(id, root)->data.printDetails();
	}
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
		BinaryNode *tmp = node;

		if (!node->left && !node->right)
			node = nullptr;
		else if (!node->right)
			node = node->left;
		else if (!node->left)
			node = node->right;
		else
		{
			BinaryNode *mn = min_node(node->right);
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
	cardinality[target.department]++;
	count++;

	if (!root)
		root = new AVLTree::BinaryNode(target);
	else
		root = insert_node(target, root);
	cout << "std num " << count << " now dept is" << target.department << " " << cardinality[target.department] << endl;
}

void AVLTree::delete_value(int id)
{
	if (root)
	{
		cardinality[search(id, root)->data.department]--;
		root = delete_node(id, root);
		count--;
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

void AVLTree::menu()
{
	int choice;
	do
	{
		cout
			<< "Choose one of the following options:" << endl
			<< "1. Add student" << endl
			<< "2. Remove student" << endl
			<< "3. Search student" << endl
			<< "4. Print All (sorted by id)" << endl
			<< "5. Return to main menu" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			add();
			break;
		case 2:
			deleteStudent();
			break;
		case 3:
			search();
			break;
		case 4:
			print_inorder();
			break;
		case 5:
			break;
		default:
			cout << "Enter a valid choice\n";
		}
	} while (choice != 5);
}

void AVLTree::add()
{
	string name, department;
	int id;
	float gpa;
	cout << "Enter student id :  ";
	cin >> id;
	cout << "Enter student name :  ";
	cin >> name;
	cout << "Enter student department :  ";
	cin >> department;
	cout << "Enter student gpa :  ";
	cin >> gpa;
	Student s = Student(id, name, gpa, department);
	insert_value(s);
}

void AVLTree::deleteStudent()
{
	int id;
	cout << "please enter student ID to delete";
	cin >> id;
	delete_value(id);
}

void AVLTree::search()
{
	int id;
	cout << "please enter student ID to delete";
	cin >> id;
	searchID(id);
}
