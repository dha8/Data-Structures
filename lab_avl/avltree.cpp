/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    
    // Stores the rotation name (don't remove this)
    functionCalls.push_back("rotateLeft");     

    // set ptrs
    Node * temp = t->right;
    t->right = temp->left;
    t->height = 1+((heightOrNeg1(t->right) >= heightOrNeg1(t->left))?
            heightOrNeg1(t->right) : heightOrNeg1(t->left));
    temp->left = t;
    temp->height = 1+(
            (heightOrNeg1(temp->right) >= heightOrNeg1(temp->left))?
            heightOrNeg1(temp->right) : heightOrNeg1(temp->left));
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    // Stores the rotation name (don't remove this)
    functionCalls.push_back("rotateRight"); 

    // set ptrs
    Node * temp = t->left;
    t->left = temp->right;
    t->height = 1+((heightOrNeg1(t->right) >= heightOrNeg1(t->left))?
            heightOrNeg1(t->right) : heightOrNeg1(t->left));
    temp->right= t;
    temp->height = 1+(
            (heightOrNeg1(temp->right) >= heightOrNeg1(temp->left))?
            heightOrNeg1(temp->right) : heightOrNeg1(temp->left));
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // case 1: NULL tree
    if(subtree==NULL||(subtree->left==NULL&&subtree->right==NULL)) return;
    
    int balance = heightOrNeg1(subtree->right)-heightOrNeg1(subtree->left);
    // case 2: right heavy
    if(balance > 1){
        // case L :
        if(subtree->right!=NULL && 
            (heightOrNeg1(subtree->right->right) < 
             heightOrNeg1(subtree->right->left))) 
            rotateRightLeft(subtree);
        // case stick:
        else rotateLeft(subtree); 
    }
    // case 3: left heavy
    if(balance < -1){
       if(subtree->left!=NULL && 
           (heightOrNeg1(subtree->left->right) > 
            heightOrNeg1(subtree->left->left))) 
           rotateLeftRight(subtree);
       // case stick:
       else rotateRight(subtree); 
    }
    
    // update height w/ max of subtrees + 1
    subtree->height = 1 + (
        (heightOrNeg1(subtree->right) >= heightOrNeg1(subtree->left))?
            heightOrNeg1(subtree->right) : heightOrNeg1(subtree->left) );

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    root = insertHelper(root, key, value);
}

template <class K, class V>
typename AVLTree<K,V>::Node* AVLTree<K, V>::insertHelper
    (Node*& subtree, const K& key, const V& value)
{
    if(subtree == NULL) return new Node(key,value); 
    // insert towards left
    if(key < subtree->key){
        subtree->left = insertHelper(subtree->left, key, value);
        rebalance(subtree->left);
    }
    // insert towarads right
    if(key > subtree->key){
        subtree->right = insertHelper(subtree->right, key, value);
        rebalance(subtree->right);
    }
    // rebalance and return after 
    rebalance(subtree);
    return subtree;
}


template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete(subtree);
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node * ptr = IOP(subtree);
            swap(ptr, subtree);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            Node * ptr = (subtree->left!=NULL)?subtree->left:subtree->right;
            delete(subtree);
            subtree = ptr;
        }
    }
    rebalance(subtree);
}

template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K,V>::IOP(Node * subtree){
    if(subtree==NULL || subtree->left==NULL) return NULL;
    Node * curr = subtree->left;
    while(curr->right!=NULL) curr = curr->right;
    return curr;
}

