#include "BST.h"

void BST::search()
{
	int id;
	cout << "ID: ";
	cin >> id;
	pair<Student *, bool> tmp = search(id, root);
	if (tmp.second)
	{
		cout << "Student is found.\n";
		cout << "[ " << tmp.first->ID << ", " << tmp.first->name << ", " << tmp.first->GPA << ", "
			 << tmp.first->department << " ]\n";
	}
	else
	{
		cout << "Student is not found.\n";
	}
}

pair<Student *, bool> BST::search(int id, Student *node)
{			   // search for a student with given id
	if (!node) // if there are no students already
		return make_pair(nullptr, false);

	if (id == node->ID) // if found return it and also return true
		return make_pair(node, true);

	if (id < node->ID) // if on left side
		return search(id, node->left);
	else // if on right side
		return search(id, node->right);
}

void BST::print_inorder()
{
	cout << "Print " << count << " Students.\n";
	print_inorder(root);
	cout << "Students per Departments:\n";
	for (auto &dept : cardinality)
	{
		cout << dept.first << " " << dept.second << " Students\n";
	}
}

void BST::print_inorder(Student *node)
{ // prints students sorted by id
	if (node)
	{
		print_inorder(node->left);
		cout << "[ " << node->ID << ", " << node->name << ", " << node->GPA << ", "
			 << node->department << " ]\n";
		print_inorder(node->right);
	}
}

void BST::deleteStudent()
{
	int id;
	cout << "id: ";
	cin >> id;
	pair<Student *, bool> tmp = search(id, root);
	if (tmp.second)
	{
		cout << "Student is found.\n";
		cardinality[tmp.first->department]--;

		// remove department if it has no students
		for (auto it = cardinality.begin(); it != cardinality.end();)
		{
			if (it->second == 0)
			{
				it = cardinality.erase(it);
			}
			else
			{
				++it;
			}
		}
		cout << "[ " << tmp.first->ID << ", " << tmp.first->name << ", " << tmp.first->GPA << ", "
			 << tmp.first->department << " ]\n";
		deleteStudent(id, root);
		cout << "Student is deleted.\n";
		count--;
	}
	else
	{
		cout << "Student is not found.\n";
	}
}

void BST::deleteStudent(int id, Student *&node)
{
	if (!node)
	{
		return;
	}
	if (id < node->ID)
	{
		deleteStudent(id, node->left);
	}
	else if (id > node->ID)
	{
		deleteStudent(id, node->right);
	}
	else if (node->left && node->right)
	{
		Student *tmp = minNode(node->right);
		node->ID = tmp->ID;
		node->name = tmp->name;
		node->GPA = tmp->GPA;
		node->department = tmp->department;
		deleteStudent(tmp->ID, node->right);
	}
	else
	{
		Student *old = node;
		node = (node->left) ? node->left : node->right;
		delete old;
	}
}

void BST::add()
{
	Student *info = getAttributes();
	add(info, root);
	cout << "\nStudent is added\n";
	cardinality[info->department]++;
	count++;
}

void BST::add(Student *node, Student *base)
{ // add new student
	if (!root)
	{ // if the first student
		root = node;
		return;
	}
	if (node->ID < base->ID)
	{
		if (!base->left) // if node doesn't have left child
			base->left = node;
		else
			add(node, base->left);
	}
	else if (node->ID > base->ID)
	{
		if (!base->right) // if node doesn't have right child
			base->right = node;
		else
			add(node, base->right);
	}
}

Student *BST::minNode(Student *cur)
{ // gets the min node in the tree/subtree
	while (cur && cur->left)
		cur = cur->left;
	return cur;
}

Student *BST::getAttributes()
{ // get student data
	int id;
	double gpa;
	string name, dept;

	cout << "ID: ";
	cin >> id;

	cout << "Name: ";
	cin.ignore();
	getline(cin, name);

	cout << "GPA: ";
	cin >> gpa;

	cout << "Department: ";
	cin >> dept;

	Student *info = new Student(id, name, gpa, dept);
	return info;
}

void BST::loadfile()
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

		add(new Student(id, name, gpa, dept), root);
		cardinality[dept]++;
		count++;
	}
	fin.close();
}

void menu()
{
	BST Students;
	Students.loadfile();

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
			Students.add();
			break;
		case 2:
			Students.deleteStudent();
			break;
		case 3:
			Students.search();
			break;
		case 4:
			Students.print_inorder();
			break;
		case 5:
			break;
		default:
			cout << "Enter a valid choice\n";
		}
	} while (choice != 5);
}
