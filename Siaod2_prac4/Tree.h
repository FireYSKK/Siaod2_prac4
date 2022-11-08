#pragma once
#ifndef _TREE_H
#define _TREE_H
#include <iostream>

class BST {
	int license;
	int fileIndex;
	BST* head = nullptr;

	BST* left = nullptr;
	BST* right = nullptr;
public:

	BST();
	BST(int lic, int indx);
	BST(int lic, int indx, BST* head);

	int getIndex() {
		return this->fileIndex;
	}
	BST* getHead() {
		return this->head;
	}
	void setRight(BST* right) {
		this->right = right;
	}
	void setLeft(BST* left) {
		this->left = left;
	}

	// ���������� ���� � ������
	BST* insertItem(BST* root, int license, int fileIndex);
	// ����� �������� � ������
	BST* findItem(BST* root, int license);
	// �������� �������� �� ������
	BST* deleteItem(BST* root, int lic);
	// ����� ������ �� �����
	void display(int level = 0, BST* current = nullptr);
	// ������ ����� ������ � �������
	void traverseNLR(BST* current);
};

#endif