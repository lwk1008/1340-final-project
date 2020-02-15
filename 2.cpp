#include <iostream>
#include <iomanip>
using namespace std;

struct Node
{
    int id;
	int age;
    int height;
	Node * left;
    Node * right;
};
// get height of the tree
int getHeight(Node * p){
    if (p == NULL){
        return 0;
    }else{
        return p->height;
    }
}
// get difference of left and right sub tree
int getBalance(Node * p){
    if(p == NULL){
        return 0;
    }else{
        return getHeight(p->left)-getHeight(p->right);
    }
}
//get the max value
int getMax(int x, int y){
    if(x>y){
        return x;
    }else{
        return y;
    }
}

//right rotation
Node * rR(Node * p){
    Node *a = p->left;
    p->left = a->right;
    a->right = p;
    p->height = getMax(getHeight(p->left),getHeight(p->right)) + 1;
    a->height = getMax(getHeight(a->left),getHeight(a->right)) + 1;
    return a;

}

// left rotation
Node * lR(Node * p){
    Node *a = p->right;
    p->right = a->left;
    a->left = p;
    p->height = getMax(getHeight(p->left),getHeight(p->right)) + 1;
    a->height = getMax(getHeight(a->left),getHeight(a->right)) + 1;
    return a;

}
// create new node
Node * createNode(int id, int age){
    Node * p = new Node();
    p->left = p->right = NULL;
    p->id = id;
    p->age = age; 
    p->height = 1;
    return p;
}
// insert node and check if balance, not balance then perform operation
Node * insert(Node * root, int id, int age){
    if (root == NULL ){
        return(createNode(id, age));
    }
    if (id > root->id ){
        root->right = insert(root->right, id, age);
    }else if(id < root->id ){
        root->left = insert(root->left, id, age);
    }else{
        return root;
    }

    root->height = getMax( getHeight(root->left) , getHeight(root->right) ) + 1;

    int balance = getBalance(root);
    // perform rotation operation 
    if(balance > 1 && id < root->left->id){
        return rR(root);
    }
    if(balance < -1 && id > root->right->id){
        return lR(root);
    }
    if(balance > 1 && id > root->left->id){
        root->left = lR(root->left);
        return rR(root);
    }
    if(balance < -1 && id < root->right->id){
        root->right = rR(root->right);
        return lR(root);
    }
    return root;
}

// remove the node and check if balance, if not balance then choose rotation to perform
Node * remove(Node * root, int id){
    if(root == NULL){
        return root;
    }else{
        if(id == root->id){
            if(root->left == NULL && root->right == NULL){
                free(root);
                root = NULL;
            }else if(root->left == NULL){
                Node *p = root;
                root = root->right;
                free(p);
            }else if(root->right == NULL){
                Node *p = root;
                root = root->left;
                free(p);
            }else{
                //find min node in right sub tree
                Node *p = root->right;
                while (p->left != NULL){
                    p = p->left;
                }
                //replace the deleted node with min node
                root -> id = p -> id;
                root -> age = p -> age;
                //delele the min node
                root->right = remove(root->right, p->id);

            }
        }else if(id > root->id){
                root->right = remove(root->right, id);
        }else{
                root->left = remove(root->left, id);
        }
    }
    if(root==NULL){
        return root;
    }
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    int balance = getBalance(root);
    // perform rotation operation 
    if(balance > 1 && getBalance(root->left)>=0){
        return rR(root);
    }
    if(balance < -1 && getBalance(root->right)<=0){
        return lR(root);
    }
    if(balance > 1 && getBalance(root->left)<0){
        root->left = lR(root->left);
        return rR(root);
    }
    if(balance < -1 && getBalance(root->right)>0){
        root->right = rR(root->right);
        return lR(root);
    }
    
    return root;
}
// search 
int search(Node * root, int id){
    if (root == NULL){
        cout<< "return -1"<< endl;
        return -1;
    }
    if (root->id == id){
        cout<< "return answer"<< endl;
        return root->age;
    }else if(id > root->id){
        return search(root->right, id);
    }else{
        return search(root->left, id);
    }
}

int main() 
{ 
    // Q1 initialize the BST shown in Figure 1
    Node * root = NULL;
    root = insert(root, 8, 25);
    root = insert(root, 3, 10);
    root = insert(root, 10, 11);
    root = insert(root, 1, 20);
    root = insert(root, 6, 31);
    root = insert(root, 14, 28);
    root = insert(root, 4, 17);
    root = insert(root, 7, 17);
    root = insert(root, 13, 9);

    //Q2 Add <2,49> and <0,33>
    root = insert(root, 2, 49);
    root = insert(root, 0, 33);

    //Q3 Remove node with id 7
    root = remove(root, 7);

    // the BST will perform the rebalance function everytime when it insert node or delete node

    return 0; 
} 
