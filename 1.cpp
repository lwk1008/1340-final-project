#include <iostream>
#include <iomanip>
using namespace std;

struct Node
{
    int id;
	int age;
	Node * left;
    Node * right;
};

// create a node
Node * createNode(int id, int age){
    Node * p = new Node();
    p->left = p->right = NULL;
    p->id = id;
    p->age = age; 
    return p;
}
// add node to the BST
Node * insert(Node * root, int id, int age){
    if (root == NULL ){
        root = createNode(id, age);
    }else{
        if (id > root->id ){
            root->right = insert(root->right, id, age);
        }else{
            root->left = insert(root->left, id, age);
        }
    }
    return root;
}
// remove node from the BST
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
    return root;
}
// loop through and search if id exist
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

    //Q4 Search node with id 13
    int search_age = search(root, 13);
    if(search_age == -1){
        cout << "no such person with identity is found" <<endl;
    }else{
        cout << "The age is " << search_age <<endl;
    }

    return 0; 
} 
