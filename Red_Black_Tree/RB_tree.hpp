#include<bits/stdc++.h>

using namespace std ;

template<class K, class V>
class Red_Black_Tree{
    enum Color {red , black};
    class Node {
        public : 
        Color color  ;
        Node* left ;
        Node* right ;
        Node* parent ;
        K key ;
        V value ;
        int size ;
        Node(K key){
            left = nullptr ;
            right = nullptr ;
            parent = nullptr ;
            this->key = key ;
            color = red ;
            size = 1 ;
        }

    };
    Node* root ;

    Node* sister(Node* node){
        if(node->parent == nullptr)return nullptr ;
        if(node->parent->left == node)return node->parent->right ;
        else return node->parent->left ;
    }

    Color color_util(Node* node){
        if(! node) return black ;
        return node->color ;
    }

    int getSize(Node* node){
        return node ? node->size : 0 ;
    }

    void updateSize(Node* node){
        if(node){
            node->size = 1 + getSize(node->left) + getSize(node->right) ;
        }
    }

    void left_rotate(Node* node){
        Node* newParent = node->right ;
        if(node == root){
            root = newParent ;
        }

        node->right = newParent->left ;
        if(newParent->left)newParent->left->parent = node ;
        newParent->parent = node->parent ;
        if(node->parent != nullptr && node->parent->left == node)
            node->parent->left = newParent;
        else if (node->parent != nullptr && node->parent->right == node)
            node->parent->right = newParent ;
        node->parent = newParent ;
        newParent->left = node ;

        updateSize(node) ;
        updateSize(newParent) ;
        root->parent = nullptr ;
    }

    void right_rotate(Node* node){
        Node* newParent = node->left ;
        if(node == root){
            root = newParent ;
        }

        node->left = newParent->right ;
        if(newParent->right) newParent->right->parent = node ;
        newParent->parent = node->parent ;
        if(node->parent != nullptr && node->parent->left == node)
            node->parent->left = newParent;
        else if (node->parent != nullptr && node->parent->right == node)
            node->parent->right = newParent ;
        node->parent = newParent ;
        newParent->right = node ;

        updateSize(node) ;
        updateSize(newParent) ;
        root->parent = nullptr ;
    }


    Node* search(Node* node, K key) {
        if (node == nullptr) return nullptr;
        if (key == node->key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }
    void redVioalation(Node* node){
        if (root == node){root->color = black ; return ;}
        if(node->parent->color == black )return ;
        Node* father = node->parent ;
        Node* uncle = nullptr ;
        Node* grandfather = father->parent ;
    
        if(grandfather->left == father){
            uncle = grandfather->right ;
            // case 1(a)
            if(father->left == node and (!uncle or uncle->color == black) ){
                right_rotate(grandfather);
                father->color = black ;
                grandfather->color = red ;
            }
            // case 1(b)
            else if(father->right == node and (!uncle or uncle->color == black) ){
                left_rotate(father);
                right_rotate(grandfather);
                node->color = black ;
                grandfather->color = red ;
            }
            else if (uncle and uncle->color == red){
                uncle->color = black ;
                father->color = black ;
                grandfather->color = red ;
                redVioalation(grandfather);
            }
        }
        else if (grandfather->right == father){
            uncle = grandfather->left ;
            // case 1(a) mirrored
            if(father->right == node and (!uncle or uncle->color == black) ){
                left_rotate(grandfather);
                father->color = black ;
                grandfather->color = red ;
            }
            // case 1(b) mirrored
            else if(father->left == node and (!uncle or uncle->color == black) ){
                right_rotate(father);
                left_rotate(grandfather);
                node->color = black ;
                grandfather->color = red ;
            }
            else if (uncle and uncle->color == red){
                uncle->color = black ;
                father->color = black ;
                grandfather->color = red ;
                redVioalation(grandfather);
            }
        }
        
    }

    Node* insert_util(Node* node, Node* ins){
        if(node == nullptr) return ins ;
        else if(ins->key > node->key)
            node->right = insert_util(node->right, ins);
        else
            node->left = insert_util(node->left, ins);
        
        if(node->left == ins or node->right == ins){
            ins->parent = node ;
        }
        updateSize(node) ;
        return node ;
    }

    Node* find_min(Node* node){
        Node* temp = node ;
        while(temp->left){
            temp = temp->left ;
        }
        return temp;
    }
    void fixDoubleBlack( Node* x){
        if(x==root)return ;
        Node* sibling = sister(x);
        Node* mother = x->parent ;
        Node* far_niece , *closer_niece ;

        // Supercase : x is on the left of parent : 
        if(mother->left == x){
            far_niece = (sibling)?sibling->right:nullptr ;
            closer_niece = (sibling)?sibling->left:nullptr ;
            //case 1 : sister, niece all black 
            if(color_util(sibling)==black and color_util(far_niece)==black and color_util(closer_niece)==black){
                // make parent black and sister red
                sibling->color = red ;
                if(mother->color == black){
                    fixDoubleBlack(mother);
                }
                else {
                    mother->color = black;
                }
            }// we move the problem upwards here

            else if(color_util(sibling)==red){
                sibling->color = black ;
                mother-> color = red ;
                left_rotate(mother);
                fixDoubleBlack(x);
            }

            else if (color_util(sibling)==black and color_util(far_niece)==red){
                sibling->color = mother->color ;
                mother->color = black ;
                left_rotate(mother);
                far_niece->color = black ;
            }
            else if (color_util(sibling)==black and color_util(far_niece)==black and color_util(closer_niece)==red){
                closer_niece->color = black ;
                sibling->color = red ;
                right_rotate(sibling);
                fixDoubleBlack(x);
            }

        }

        else if(mother->right == x){
            far_niece = (sibling)?sibling->left:nullptr ;
            closer_niece = (sibling)?sibling->right:nullptr ;
            //case 1 : sister, niece all black 
            if(color_util(sibling)==black and color_util(far_niece)==black and color_util(closer_niece)==black){
                // make parent black and sister red
                sibling->color = red ;
                if(mother->color == black){
                    fixDoubleBlack(mother);
                }
                else {
                    mother->color = black;
                }
            }// we move the problem upwards here

            else if(color_util(sibling)==red){
                sibling->color = black ;
                mother-> color = red ;
                right_rotate(mother);
                fixDoubleBlack(x);
            }

            else if (color_util(sibling)==black and color_util(far_niece)==red){
                sibling->color = mother->color ;
                mother->color = black ;
                right_rotate(mother);
                far_niece->color = black ;
            }
            else if (color_util(sibling)==black and color_util(far_niece)==black and color_util(closer_niece)==red){
                closer_niece->color = black ;
                sibling->color = red ;
                left_rotate(sibling);
                fixDoubleBlack(x);
            }

        }
    }

    Node* replacement(Node* n){
        if(!n->left and !n->right) return nullptr ;
        if(!n->right)return n->left ;
        if(!n->left) return n->right ;
        else return find_min(n->right);
    }

    void delete_util(Node* n){
        Node* x = replacement(n);
        bool DB = (color_util(n)==black and color_util(x)==black);// a problem 
        // if n is a black leaf , it is required to keep the node to fix the DB violation
        // because cannot access the parent and other nodes of a null node
        //case 01 : n is a  leaf 
        if (x == nullptr){
            if(n->color == red){
                if(n->parent->left==n)n->parent->left = nullptr ;
                else n->parent->right = nullptr ;
                delete n ;
                return ;
            }
            
            else if(root == n){
                root = nullptr ;
                delete n ;
                return ;
            }

            // n is a black leaf , we havedouble black violation at n where n is now null, but for convinience we keep the null for nbow 
            //fixDoubleBlack(n);
            else {
                fixDoubleBlack(n);
                if(n->parent->left==n)n->parent->left = nullptr ;
                else n->parent->right = nullptr ;
                delete n ;
            }
        }

        else if (!n->left  or !n->right){
            // n is not a leaf and therefore is replaced by x 
            if(n-> color == red){
                if(n->parent->left==n)n->parent->left = x;
                else n->parent->right = x ;
                x->parent = n->parent ;
                delete n ;
                return ;
            }
            else if(n==root){
                // it must only have a red child ;
                n->key = x->key ;
                n->value = x->value ;
                n->left = n->right = nullptr ;
                delete x ;
                return ;
            }
            else if (n->color == black and x->color == red){
                if(n->parent->left==n)n->parent->left = x;
                else n->parent->right = x ;
                x->parent = n->parent ;
                delete n ;
                x->color = black ;
                return ;
            }
            else {
                if(n->parent->left==n)n->parent->left = x;
                else n->parent->right = x ;
                x->parent = n->parent ;
                delete n ;
                // x is double black 
                fixDoubleBlack(x);
                return ;
            }


        }

        else {
            // n has 2 children and the problem is moved downwards 
            Node* temp = find_min(n->right);
            n->key = temp->key ;
            n->value = temp->value ;
            delete_util(temp);
        }
    }

    public :
    Red_Black_Tree(){
        root = nullptr ;
    }

    bool insert(K key, V value){
        if(! root){
            Node* node = new Node(key);
            node->color = black ;
            node->value = value ;
            root = node ;
            return true ;
        }
        if(! search(root, key)){
            Node* node = new Node(key);
            node->value = value ;
            root = insert_util(root, node);
            redVioalation(node);
            return true ;
        }
        return false ;

    }

    bool delete_key(K key){
        if(root==nullptr) return false ;
        Node* n = search(root, key); 
        if(!n)return false ;
        delete_util(n);
        return true;
    }

    bool search(K key, V &value){
        Node * n = search(root, key);
        if(!n)return false ;
        
        value = n->value ;
        return true ;
        
    }

    int countLess(K value) {
        return countLess_util(root, value);
    }

private:
    int countLess_util(Node* node, K value) {
        if (node == nullptr) return 0;
        
        if (value > node->key) {
            // Count: all nodes in left subtree + current node + nodes in right subtree less than value
            return getSize(node->left) + 1 + countLess_util(node->right, value);
        } else {
            // Only count nodes in left subtree
            return countLess_util(node->left, value);
        }
    }

public:

};

