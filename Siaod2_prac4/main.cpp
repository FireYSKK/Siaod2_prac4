#include <iostream>
#include<fstream>
#include<string>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include "Tree.h"
#include "BF.h"
#include "avltree.h"
using namespace std;

string filename = "file10000.bin";

void operator<<(ostream& stream, const record r) {
    cout << r.license << " " << r.name << " " << r.owner << endl;
}

record findRecord(int key, AVLTree* binTree) {
    AVLTree* node = binTree->findNode(key, binTree);

    if (node) {
        //Чтение записи из файла
        fstream fdirect(filename, ios::binary | ios::out | ios::in);
        record rec;
        fdirect.seekg((node->getIndex()) * sizeof(record), ios::beg);
        fdirect.read((char*)&rec, sizeof(record));

        return rec;
    }
    record rec;
    rec.empty = true;
    return rec;
}

int main() {

    // Комменты с числами, это ключи из моего файла
    // Генерируйте свои файлы >_<
    // А то нас могут поиметь
    // Спасибо

    // Генерировать тут (в скобках размер)
    //   |
    //   |
    //  \ /
    BF binFile = BF(filename);
    //binFile.generateFile(10000);

    // Бинарное дерево поиска (обычное)
     
    BST* binTree = nullptr;
    int fileIndex = 0;
    ifstream fin(filename, ios::binary | ios::in);
    record rec;
    while (!fin.eof()) {
        fin.read((char*)&rec, sizeof(record));
        if (!rec.empty) {
            if (fileIndex == 0) {
                binTree = (new BST())->insertItem(binTree, rec.license, fileIndex);
            }
            else {
                binTree->insertItem(binTree, rec.license, fileIndex);
            }
        }
        fileIndex++;
    }

    // Time consumed
    auto start = std::chrono::system_clock::now();
    // 15: 1799968149 1200446723
    // 100: 476514495
    // 1000: 1739882252
    // 2000: 40715941
    // 5000: 938504129
    // 10000: 1353653019
    cout << binFile.findRecord(1353653019, binTree);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << elapsed.count() << " s" << '\n';
    
    binTree->display(0, binTree);
    
    binTree = binTree->deleteItem(binTree, 1200446723);
    cout << "----------------------------------" << endl;
    binTree->display(0, binTree);
    

    // АВЛ дерево
    AVLTree* avltree = new AVLTree();
    int fileIndex = 0;
    ifstream fin(filename, ios::binary | ios::in);
    record rec;
    while (!fin.eof()) {
        fin.read((char*)&rec, sizeof(record));
        //cout << rec;
        if (!rec.empty)
        {
            if (fileIndex == 0) {
                avltree = avltree->addNode(rec.license, fileIndex);
            }
            else
                avltree = avltree->addNode(rec.license, fileIndex, avltree);
        }
        fileIndex++;
    }

    auto start = std::chrono::system_clock::now();
    // 15: 1799968149 1200446723
    // 100: 476514495
    // 1000: 1739882252
    // 2000: 40715941
    // 5000: 938504129
    // 10000: 1353653019
    cout << findRecord(1353653019, avltree);

    // Time consumed
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << elapsed.count() << " s" << '\n';

    avltree->display(0, avltree);
    cout << "Total rotations: " << avltree->getRotations() << endl;
    cout << "----------------------------------" << endl;

    avltree = avltree->deleteNode(1200446723, avltree);
    avltree->display(0, avltree);
    cout << "Total rotations: " << avltree->getRotations() << endl;





    // RAM used
    // Чекайте библиотеки
    // Нужны windows.h и psapi.h
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
    std::cout << physMemUsedByMe << '\n';

	return 0;
}