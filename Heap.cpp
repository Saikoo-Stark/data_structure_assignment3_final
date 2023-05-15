#include "Trees.h"

bool Heap::ascCmp(float gpa1, float gpa2)
{
	return (gpa1 < gpa2);
}

bool Heap::descCmp(float gpa1, float gpa2)
{
	return (gpa1 > gpa2);
}

void Heap::heapify(vector<Student> &vec, int len, int ind)
{
	int l = 2 * ind + 1;
	int r = 2 * ind + 2;
	int flag = ind;

	if (l < len && (this->*cmp)(vec[flag].gpa, vec[l].gpa))
		flag = l;

	if (r < len && (this->*cmp)(vec[flag].gpa, vec[r].gpa))
		flag = r;

	if (flag != ind)
	{
		swap(vec[flag], vec[ind]);
		heapify(vec, len, flag);
	}
}

void Heap::heapSort(vector<Student> &vec)
{
	int len = vec.size();
	for (int i = len / 2 - 1; i >= 0; i--)
	{
		heapify(vec, len, i);
	}

	for (int i = len - 1; i >= 0; i--)
	{
		swap(vec[0], vec[i]);
		heapify(vec, i, 0);
	}
}

void Heap::loadData()
{
	ifstream fin("input.txt");
	if (!fin)
	{
		cout << "Unable to open file.";
		return;
	}

	int n;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		int id = 5;
		string name;
		float gpa;
		string dept;
		fin >> id;
		fin.ignore();
		getline(fin, name);
		fin >> gpa;
		fin.ignore();
		getline(fin, dept);

		// cout << id << " " << name << " " << gpa << " " << dept << endl;
		insert(id, name, gpa, dept);
	}

	// fclose(file);
}

Heap::Heap(int sortval)
{

	if (sortval == 1)
		cmp = &ascCmp;
	else
		cmp = &descCmp;

	loadData();
}

void Heap::insert(int id, string name, float gpa, string dept)
{
	Student student = {id, name, gpa, dept};
	students.push_back(student);
	heapSort(students);
}

void Heap::add()
{
	int id;
	string name, dept;
	float gpa;
	cout << "Enter ID : ";
	cin >> id;
	cin.ignore();

	cout << "Enter Name : ";
	getline(cin, name);

	cout << "Enter GPA : ";
	cin >> gpa;
	cin.ignore();

	cout << "Enter Department : ";
	getline(cin, dept);

	insert(id, name, gpa, dept);
}

void Heap::print()
{
	cout << "Print " << students.size() << " students\n";
	for (Student std : students)
	{
		cout << "[ " << std.id << ", " << std.name << ", " << std.gpa << ", " << std.dept << " ]\n";

		// cout << "\nid: " << std.id
		// 	 << "\nname: " << std.name
		// 	 << "\ngpa: " << std.gpa
		// 	 << "\ndept: " << std.dept << endl;
	}
}

void Heap::menu()
{

	int choice;
	do
	{
		cout
			<< "Choose one of the following options:" << endl
			<< "1. Add student" << endl
			<< "2. Print All (sorted by id)" << endl
			<< "3. Return to main menu" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			add();
			break;
		case 2:
			print();
			break;
		case 3:
			break;
		default:
			cout << "Enter a valid choice\n";
		}
	} while (choice != 3);
}
