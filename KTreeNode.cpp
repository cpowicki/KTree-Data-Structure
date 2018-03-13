//
//  KTreeNode.cpp
//  
//
//  Created by Charlie Powicki on 10/28/17.
// * This is generalized to work for any BTree with minimum degree K. * Extra Credit? :)
//

#include "KTreeNode.hpp"
#include <iostream>
#include <random>
using namespace std;

KTreeNode::KTreeNode (vector<int> k, vector<KTreeNode*> p, int d)
{
    degree = d;
    keys = k;
    pointers = p;
}

void KTreeNode::print_tree(int indent)
{
    //If there are no keys in the node, we're in a "null" leaf, and we have nothing to print.
    if (this->keys.size() == 0) {
        return;
    } else {
        //Start at the rightmost node, and work our way up and left.
        if (this->pointers.size() > this->keys.size()){
            this->pointers[pointers.size() - 1]->print_tree(indent + 4);
        }
        for (int i = this->keys.size() - 1 ; i >= 0; i--){
            cout << string(indent, ' ') + to_string(this->keys[i]) + " " << endl;
            if (i < this->pointers.size()){
                this->pointers[i]->print_tree(indent + 4);
            }
        }
    }
}
/* Recursive search function through the tree, returning true or false and taking the key
 * we want to find as a parameter.
 */
bool KTreeNode::search_tree(int search_key)
{
    if (this->keys.size() == 0){
        return false;
    }
    int i = 0;
    while (i < this->keys.size() && search_key > this->keys[i]){ i++; }
    if (search_key == this->keys[i]){
        return true;
    } else {
        if (this->pointers.size() <= i) {
            return false;
        } else {
            return this->pointers[i]->search_tree(search_key);
        }
    }
}
/* A wrapper function for dealing with the case in which we have to split the root node.
 * Returns the new node, takes the current root and the new insert key as parameters.
 */
KTreeNode* KTreeNode::insert_wrapper(KTreeNode* root, int newkey){
    if (root->keys.size() >= (2 * root->degree) - 1) { //If the root is full...
        vector<int> rootK;
        rootK.assign(1, 1);
        vector<KTreeNode*> rootP;
        rootP.assign(1, root);
        KTreeNode* newRoot = new KTreeNode(rootK, rootP, root->degree); //make our new root node.
        //Call the split function on the previous root using our special case of -1 to indicate
        //We're creating a new root.
        KTreeNode::pre_split(newRoot, root, -1);
        root = newRoot;
    }
    //If the root is not full, just call insert as usual.
    KTreeNode::insert_key(root, newkey);
    return root;
}
void KTreeNode::insert_key(KTreeNode* curr, int newkey)
{
    //First, get the correct index of the pointer (or in the keys vector) to insert our newkey.
    int i = 0;
    while (i < curr->keys.size() && newkey > curr->keys[i]){ i++;}
    //If we are in a leaf... insert to the key vector
    if (curr->pointers.size() <= i) {
        curr->keys.insert(curr->keys.begin() + i, newkey);
    } else {
        bool split = pre_split(curr, curr->pointers[i], i);
        //If we split the next node, our current node has changed, so we recall this function.
        if (split){
            insert_key(curr,newkey);
        //If not, just proceed to the next node.
        } else {
            insert_key(curr->pointers[i], newkey);
        }
    }
}
bool KTreeNode::pre_split(KTreeNode* curr, KTreeNode* x, int point_index)
{
    if (x->keys.size() >= (2 * curr->degree) - 1){ //if the node is full.
        int med_index = (x->keys.size()-1) / 2; //The median index
        //Create two vectors for the left and right keys. 
        vector<int> leftkeys;
        leftkeys.assign(x->keys.begin(), x->keys.begin() + med_index);
        vector<int> rightkeys;
        rightkeys.assign(x->keys.begin() + med_index+1, x->keys.begin() + x->keys.size());
        //Create two vectors to split the pointers in the left and right portions of
        //the node we're splitting.
        vector<KTreeNode*> leftpointers;
        vector<KTreeNode*> rightpointers;
        //If all pointers are to the left of the median index, assign them all to the new left node.
        if (x->pointers.size() < med_index + 1){
            leftpointers.assign(x->pointers.begin(), x->pointers.begin() + x->pointers.size());
        //Otherwise, divide the pointers around the median index.
        } else {
            leftpointers.assign(x->pointers.begin(), x->pointers.begin() + med_index + 1 );
            rightpointers.assign(x->pointers.begin() + med_index + 1, x->pointers.begin() + x->pointers.size());
        }
        //Create the new left/right child nodes.
        KTreeNode* left = new KTreeNode(leftkeys, leftpointers, curr->degree);
        KTreeNode* right = new KTreeNode(rightkeys, rightpointers, curr->degree);
        //Special case for the root node.
        if(point_index == -1){
            curr->keys.assign(1, x->keys[med_index]);
        /*If the pointer we "came down on" from curr to split node x exceeds the number of keys
        * in curr, or in other words, the rightmost pointer, we append the vector with the 
        * key at the median index. */
        } else if (point_index > curr->keys.size() - 1) {
            curr->keys.push_back(x->keys[med_index]);
        // Otherwise, we insert it into the key vector
        } else {
            vector<int>::iterator it = curr->keys.begin() + point_index;
            curr->keys.insert(it, x->keys[med_index]);
        }
        //Again, special case for the root node.
        if (point_index == -1){
            curr->pointers.assign(1, left); curr->pointers.push_back(right);
        } else {
            //Remove the pointer along which we came down from the curr node.
            vector<KTreeNode*>::iterator it2 = curr->pointers.begin() + point_index;
            curr->pointers.erase(it2);
            //If the pointer was the last one, (rightmost), we append the vector.
            if (point_index > curr->pointers.size() - 1){
                curr->pointers.push_back(left);
                curr->pointers.push_back(right);
            //Otherwise, we insert them at the appropriate positions.
            } else {
                curr->pointers.insert(it2, left);
                curr->pointers.insert(it2 + 1, right);
            }
        }
        return true;
    }
    return false;
}
int main(){
    
}
