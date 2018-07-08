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
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;
    temp->height = 1 + max(heightOrNeg1(temp->left), heightOrNeg1(temp->right));
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
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
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;
    temp->height = 1 + max(heightOrNeg1(temp->left), heightOrNeg1(temp->right));
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
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
    // your code here
    if (subtree == NULL) {
      return;
    }
    int d = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
    if (d > 1) {
      if (heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right) == 1) {
        rotateRight(subtree);
      } else {
        rotateLeftRight(subtree);
      }
    } else if (d < -1) {
      if (heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right) == -1) {
        rotateLeft(subtree);
      } else {
        rotateRightLeft(subtree);
      }
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
      subtree = new Node(key, value);
    } else if (key < subtree->key) {
      insert(subtree->left, key, value);
    } else if (key > subtree->key) {
      insert(subtree->right, key, value);
    }
    rebalance(subtree);
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
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * temp = subtree->left;
            if (temp->right == NULL) {
              swap(subtree, temp);
              remove(subtree->left, key);
            } else {
              while (temp->right->right != NULL) {
                temp = temp->right;
              }
              swap(subtree, temp->right);
              remove(temp->right, key);
            }

        } else {
            /* one-child remove */
            // your code here
            if (subtree->left == NULL) {
              Node * temp = subtree;
              subtree = temp->right;
              delete temp;
            } else if (subtree->right == NULL) {
              Node * temp = subtree;
              subtree = temp->left;
              delete temp;
            }
        }
        // your code here
    }
    rebalance(subtree);
}
