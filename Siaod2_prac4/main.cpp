#include <iostream>
#include<fstream>
#include<string>
#include "Tree.h"
#include "BF.h"
#include "avltree.h"
using namespace std;

// Узлы для удаления 1799968149 1200446723

void operator<<(ostream& stream, const record r) {
    cout << r.license << " " << r.name << " " << r.owner << endl;
}

int main() {
    // Бинарное дерево поиска (обычное)
     
    /*/BST* b = new BST(), * binTree = nullptr;
    BF binFile = BF("file15.bin");
    int fileIndex = 0;
    ifstream fin("file15.bin", ios::binary | ios::in);
    record rec;
    while (!fin.eof()) {
        fin.read((char*)&rec, sizeof(record));
        if (!rec.empty) {
            if (fileIndex == 0) {
                binTree = b->insertItem(binTree, rec.license, fileIndex);
            }
            else {
                binTree->insertItem(binTree, rec.license, fileIndex);
            }
        }
        fileIndex++;
    }
    
    binTree->display(0, binTree);
    
    binTree = binTree->deleteItem(binTree, 1200446723);
    cout << "----------------------------------" << endl;
    binTree->display(0, binTree);
    
    cout << binFile.findRecord(1799968149, binTree);*/


    // АВЛ дерево
    AVLTree* avltree = new AVLTree();
    BF binFile = BF("file15.bin");
    int fileIndex = 0;
    ifstream fin("file15.bin", ios::binary | ios::in);
    record rec;
    while (!fin.eof()) {
        fin.read((char*)&rec, sizeof(record));
        cout << rec;
        if (!rec.empty)
        {
            if (fileIndex == 0)
                avltree = avltree->addNode(rec.license, fileIndex);
            else
                avltree = avltree->addNode(rec.license, fileIndex, avltree);
        }
        fileIndex++;
    }

    avltree->display(0, avltree);
    cout << "----------------------------------" << endl;

    avltree = avltree->deleteNode(1200446723, avltree);
    avltree->display(0, avltree);

	return 0;
}