#include <iostream>
using namespace std;

class AVLTree
{
private:
	struct BinaryNode
	{
		int data{};
		int height{};
		BinaryNode *left{};
		BinaryNode *right{};

		BinaryNode(int data) : data(data)
		{
		}

		int ch_height(BinaryNode *node)
		{
			if (!node)
				return -1;
			return node->height;
		}

		int update_height()
		{
			return height = 1 + max(ch_height(left), ch_height(right));
		}

		int balance_factor()
		{
			return ch_height(left) - ch_height(right);
		}
	};

	BinaryNode *root{};

	bool search(int target, BinaryNode *node)
	{
		if (!node)
			return false;

		if (target == node->data)
			return true;

		if (target < node->data)
			return search(target, node->left);

		return search(target, node->right);
	}

	BinaryNode *right_rotation(BinaryNode *Q)
	{
		BinaryNode *P = Q->left;
		Q->left = P->right;
		P->right = Q;
		Q->update_height();
		P->update_height();
		return P;
	}

	BinaryNode *left_rotation(BinaryNode *P)
	{
		BinaryNode *Q = P->right;
		P->right = Q->left;
		Q->left = P;
		P->update_height();
		Q->update_height();
		return Q;
	}

	BinaryNode *balance(BinaryNode *node)
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

	BinaryNode *insert_node(int target, BinaryNode *node)
	{
		if (target < node->data)
		{
			if (!node->left)
				node->left = new BinaryNode(target);
			else
				node->left = insert_node(target, node->left);
		}
		else if (target > node->data)
		{
			if (!node->right)
				node->right = new BinaryNode(target);
			else
				node->right = insert_node(target, node->right);
		}
		node->update_height();
		return balance(node);
	}

	BinaryNode *min_node(BinaryNode *cur)
	{
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

	BinaryNode *delete_node(int target, BinaryNode *node)
	{
		if (!node)
			return nullptr;

		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
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
				node->right = delete_node(node->data, node->right);
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
	void print_inorder(BinaryNode *node)
	{
		if (!node)
			return;

		print_inorder(node->left);
		cout << node->data << " ";
		print_inorder(node->right);
	}

public:
	void insert_value(int target)
	{
		if (!root)
			root = new BinaryNode(target);
		else
			root = insert_node(target, root);
	}

	void delete_value(int target)
	{
		if (root)
		{
			root = delete_node(target, root);
		}
	}
	void print_inorder()
	{
		print_inorder(root);
	}
};
int main()
{
	AVLTree av;
	av.insert_value(1);
	av.insert_value(2);
	av.insert_value(5);
	av.insert_value(3);
	av.insert_value(4);
	av.insert_value(9);
	av.insert_value(7);
	//    av.print_inorder();
	av.delete_value(5);
	av.print_inorder();
	return 0;
}
