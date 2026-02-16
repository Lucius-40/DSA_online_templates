#pragma once
#include<bits/stdc++.h>

using namespace std ;


template<class K, class V>
class AVL_Tree{
    
    class Node {
    public:
        K key ;
        V value ;
        Node* left ;
        Node* right;
        int height ;
        
        Node(){
            left = nullptr ;
            right = nullptr ;
            height = 1 ;
        }
    };

    Node* root ;

    Node* find_min(Node* node){
        Node* temp = node ;
        while(temp->left){
            temp = temp->left ;
        }
        return temp;
    }
    
    Node* leftRotate(Node* node) {
        Node* r = node->right;
        Node* to_move = r->left;
        r->left = node;
        node->right = to_move;
        node->height = max(height(node->left), height(node->right)) + 1;
        r->height = max(height(r->left), height(r->right)) + 1;
        return r;
        
    }
    
    Node* rightRotate(Node* node) {
        Node* l = node->left ;
        Node* to_move = l->right ;
        l->right = node ;
        node->left = to_move ;
        node->height = max(height(node->right), height(node->left))+1 ;
        l->height = max(height(l->right), height(l->left))+1 ;
        return l ;
    }
    int height(Node *n) {
        if (n == nullptr)
            return 0;
        return n->height;
    }
    
    Node* search(Node* node, K key) {
        if (node == nullptr) return nullptr;
        if (key == node->key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }
    

    
    
    Node* delete_util(Node* node, K key) {
        if(node == nullptr) return nullptr;
        if(node->key > key)
            node->left = delete_util(node->left, key);
        else if (node-> key < key)
            node->right = delete_util(node->right,key);
        
        else {
            if(! node->left and !node->right){
                delete node ;
                return nullptr ;
            }
            else if (! node->left){
                Node* temp = node->right ;
                delete node ;
                return temp ;
            }
            else if (! node->right){
                Node* temp = node->left ;
                delete node ;
                return temp ;
            }
            else {
                Node* successor = find_min(node->right);
                node->key = successor->key ;
                node->value = successor->value ;
                node->right = delete_util(node->right, successor->key);
            }
        }

        if(node == nullptr) return nullptr ;

        node->height = max(height(node->left), height(node->right)) + 1 ;

        int baln = height(node->left) - height(node->right);

        if (baln > 1 and height(node->left->left) >= height(node->left->right)){
            return rightRotate(node);
        }

        if(baln > 1 and height(node->left->left) < height(node->left->right)){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (baln < -1 and height(node->right->right) >= height(node->right->left)){
            return leftRotate(node);
        }
        if(baln < -1 and height(node->right->left) > height(node->right->right)){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node ;
       
    }

    Node* insert_util(Node* node , Node* ins){

        if(node == nullptr)return ins ;
        if(ins->key < node->key)
            node->left = insert_util(node->left, ins);
        else if (ins->key > node->key)
            node->right = insert_util(node->right, ins);
        
        node->height = 1 + max(height(node->left), height(node->right));

        int baln = height(node->left) - height(node->right); 

        // 2 cases each needs to be handled :((
        if (baln > 1 and ins->key < node->left->key){
            return rightRotate(node);
        }

        if(baln > 1 and ins->key > node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (baln < -1 and ins->key > node->right->key){
            return leftRotate(node);
        }
        if(baln < -1 and ins->key < node->right->key){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node ;
    }
    
   
    void preOrder(Node* node) {
        if (node == nullptr) return;
        cout << node->key  << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
    
    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->key << " ";
        inOrder(node->right);
    }
    
    void postOrder(Node* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->key << " ";
    }
    
    void levelOrder() {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->key << " ";
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }
    
    public :

    AVL_Tree(){
        root = nullptr ;
    }
    
    
    bool insert(K key, V value) {
        if(!root){
            Node* node = new Node ;
            node->key = key ;
            node->value = value ;
            root = node ;
            return true ;
        }
        if (search(root , key) != nullptr) return false ;
        Node* node = new Node ;
        node->key = key ;
        node->value = value ;
        root = insert_util(root, node);
        return true ;
    }
    
    bool deleteKey(K key) {
        if(! search(root,key)) return false ;
        root = delete_util(root, key);
        return true ;
    }

    void traversal(int scheme){
        if(scheme <1 or scheme >4){
            cout << "Invalid traversal scheme!";
            return ;
        }
        if(scheme == 1)
            preOrder(root);
        
        else if (scheme == 2)
            inOrder(root);
            // levelOrder();
        else if(scheme == 3)
            postOrder(root);
        else 
            levelOrder();
    }
    void printTreeStructure() {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            cout << "level " << level << ": ";
            for (int i = 0; i < levelSize; i++) {
                Node* current = q.front();
                q.pop();
                cout << current->key << " ";
                if (current->left != nullptr) q.push(current->left);
                if (current->right != nullptr) q.push(current->right);
            }
            cout << endl;
            level++;
        }
    }

};

