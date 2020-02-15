#include <iostream>
#include <iomanip>
#include <queue> 
#include <thread>
#include <mutex> 
using namespace std;

mutex mtx;
struct Node
{
    int id;
	int age;
	Node * left;
    Node * right;
};

int numberOfNodes = 0;
queue<Node *> myqueue;
queue<thread> allThread;
int searchedAge = -1;
// new node
Node * createNode(int id, int age){
    Node * p = new Node();
    p->left = p->right = NULL;
    p->id = id;
    p->age = age; 
    numberOfNodes++;
    return p;
}
// add node
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
// remove node
Node * remove(Node * root, int id){
    if(root == NULL){
        return root;
    }else{
        if(id == root->id){
            numberOfNodes --;
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

// parent thread search function
void BST(Node*root, int id){
    mtx.lock();
    if(root->id == id){
        searchedAge = root->age;
    }
    if(root->left!= NULL){
        myqueue.push(root->left);
    }
    if(root->right!= NULL){
        myqueue.push(root->right);
    }
    mtx.unlock();
}
// child thread serach function
void BSTchild(int id){
    mtx.lock();
    Node * temp = myqueue.front();
    myqueue.pop();
    if(temp->id == id){
        searchedAge = temp->age;
    }
    if(temp->left!= NULL){
        myqueue.push(temp->left);
    }
    if(temp->right!= NULL){
        myqueue.push(temp->right);
    }
    mtx.unlock();
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

    //task3  change serach_id to obtain the age of that id
    // create parent thread when first called
    // create child thread once ->left or -> right is not null
    // join all thread and return the age of that id if found
    int counter = 0;
    int search_id = 6;
    thread mythread[numberOfNodes];
    mythread[0] = thread(BST, root, search_id);
    for(int i = 1; i<numberOfNodes; i++){
        if(searchedAge != -1){
            break;
        }

        mythread[i] = thread(BSTchild,search_id);
        counter = i;
    }

    for(int i = 1; i<counter; i++){
        mythread[i].join();
    }
    if(searchedAge != -1){
        cout <<"Age of id " << search_id << " is "<< searchedAge <<endl;
    }else{
        cout << "dont have such id"<<endl;
    }


    return 0; 
} 
