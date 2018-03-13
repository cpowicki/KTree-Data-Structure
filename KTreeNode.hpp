//
//  KTreeNode.hpp
//  
//
//  Created by Charlie Powicki on 10/28/17.
//
//

#ifndef KTreeNode_hpp
#define KTreeNode_hpp

#include <stdio.h>
#include <vector>

using namespace std;
/* I implement KTreeNode using two vectors, one for keys and one for pointers to children nodes. The index of
 * the pointer in vector indicates that it is to the left of the corresponding key in the keys vector, except
 * for the case where the size of the pointer vector exceeds the size of the keys, meaning that the pointer
 * at the last index of the pointer vector is to the right of the key at the last index of the key vector.
 */
class KTreeNode
{
public:
    vector<int> keys;
    vector<KTreeNode*> pointers;
    int degree;
    KTreeNode(vector<int> k, vector<KTreeNode*> p, int d);
    void print_tree(int indent);
    bool search_tree(int search_key);
    static void insert_key(KTreeNode* curr, int newkey);
    static KTreeNode* insert_wrapper(KTreeNode* root, int newkey);
    static bool pre_split(KTreeNode* curr, KTreeNode* x, int point_index);
};

#endif /* KTreeNode_hpp */
