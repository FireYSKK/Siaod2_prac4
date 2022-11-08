#pragma once
#ifndef _AVLTREE_H
#define _AVLTREE_H
#include <iostream>
using namespace std;

class AVLTree;

struct Node
{
    int license;
    int fileIndex;
    AVLTree* left = nullptr;
    AVLTree* right = nullptr;

    Node(int lic, int indx) {
        this->license = lic;
        this->fileIndex = indx;
    }
};

class AVLTree {
    Node* root = nullptr;
    int height = 1;
public:
    // ���������� root->license
    int getValue();
    // ���������� ������� ����
    int getBalance(AVLTree* next);
    // ������ ������� ������������ ���� �
    AVLTree* rightRotate(AVLTree* y);
    // ����� ������� ������������ ���� �
    AVLTree* leftRotate(AVLTree* x);
    // ���������� ���� � ������
    AVLTree* addNode(int license, int fileIndex, AVLTree* next = nullptr);
    // �������� ���� �� ������
    AVLTree* deleteNode(int key, AVLTree* next);
    // ����� ������ (���������� ����� �������)
    void display(int level, AVLTree* current);
};
#endif