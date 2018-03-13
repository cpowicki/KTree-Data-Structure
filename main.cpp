//
//  main.cpp
//  
//
//  Created by Charlie Powicki on 10/29/17.
//
//
#include "KTreeNode.cpp"
#include <stdio.h>
#include <iostream>
#include <random>
using namespace std;

int main(int argc, char* argv[])
{
    int min_degree;
    int Upperbound;
    int numElements;
    if (argc < 4 || argc > 4){
        cout << "This program takes 3 Integer arguments:" << endl << "1. Minimum Degree of the BTree" << endl;
        cout << "2. Upperbound on the range of values to be inserted in the tree." << endl;
        cout << "3. Total number of values to insert." << endl;
        return 0;
    } else {
        min_degree = atoi(argv[1]);
        Upperbound = atoi(argv[2]);
        numElements = atoi(argv[3]);
    }
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1,Upperbound);
    vector<int> tmp;
    tmp.assign(1, distribution(generator));
    vector<KTreeNode*> points;
    KTreeNode::KTreeNode root = KTreeNode(tmp, points, min_degree);
    int insert_element;
    for (int i = 0; i < numElements + 1; i++){
        insert_element = distribution(generator);
        cout << "Insert: " + to_string(insert_element) + " ";
        root = *KTreeNode::insert_wrapper(&root,insert_element);
        cout << endl;
        root.KTreeNode::print_tree(0);
        cout << "--------------------------------------------------" << endl;
    }
}
