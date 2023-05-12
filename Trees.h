#ifndef TREES_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

// Heap Tree

class Heap
{
private:
	struct Student
	{
		int id;
		string name;
		float gpa;
		string dept;
	};
	vector<Student> students;
	bool (Heap::*cmp)(float gpa1, float gpa2);
	bool ascCmp(float gpa1, float gpa2);
	bool descCmp(float gpa1, float gpa2);

	void loadData();
	void heapify(vector<Student> &vec, int len, int ind);
	void heapSort(vector<Student> &vec);

public:
	Heap(int sortval = 1);
	void insert(int id, string name, float gpa, string dept);
	// void remove(int id);
	// Student search(int id);
	void print();
	void menu();
};

// BST Tree

struct Student
{

	string name;
	int ID;
	double GPA;
	string department;
	Student *left{};
	Student *right{};

	Student(int id, string name, double gpa, string department) : ID(id), name(name), GPA(gpa), department(department) {}
};

class BST
{
private:
	Student *root{};
	map<string, int> cardinality; // to keep track of # of students in each department
	int count = 0;

	static Student *getAttributes();

	void add(Student *node, Student *base);

	void print_inorder(Student *node);

	Student *minNode(Student *cur);

	void deleteStudent(int id, Student *&node);

	pair<Student *, bool> search(int id, Student *node);

public:
	BST() : root(NULL) {}

	void add();

	void deleteStudent();

	void print_inorder();

	void search();

	void loadfile();
};

void menu();
#endif
