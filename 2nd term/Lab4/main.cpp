#include <iostream>
#include "Tree.h"
#include "BinaryTree.h"
#include "Catalogue.h"

void treeTest();
void binaryTreeTest();
void catalogueTest();

int main(){

    //treeTest();
    //binaryTreeTest();
    catalogueTest();

    return 0;
}

void treeTest(){
    Tree* tree = new Tree(5);
    tree->add(10,0.4);
    tree->add(11,0.9);
    tree->add(1,0.1);
    tree->add(2,0.1);

    tree->print();

    tree->remove(10);

    std::cout << std::endl;

    tree->print();
}

void binaryTreeTest(){
    BinaryTree* binaryTree = new BinaryTree(3);
    binaryTree->add(0);
    binaryTree->add(1);
    binaryTree->add(6);
    binaryTree->add(3);
    binaryTree->add(6);

    binaryTree->print();
}

void catalogueTest(){
    Catalogue* catalogue = new Catalogue("root");

    catalogue->addFolder("Folder1");
    catalogue->addFolder("Folder2");
    catalogue->addFile("File1", 10);

    catalogue = catalogue->goTo("Folder2");
    catalogue->addFile("Another File", 5);

    catalogue = catalogue->goTo("root");
    catalogue->print();


    catalogue = catalogue->goTo("Folder2");
    std::cout << std::endl;
    catalogue->print();

    std:: cout  << std::endl << "Catalogue size: " << catalogue->getCatalogueSize() << std::endl;
    std:: cout << "Folders count: " << catalogue->getFoldersCount() << std::endl;
    std:: cout << "Files count: " << catalogue->getFilesCount() << std::endl;

    std:: cout << "Min time: " << catalogue->getMinTime() << std::endl;
    std:: cout << "Max time: " << catalogue->getMaxTime() << std::endl;

}