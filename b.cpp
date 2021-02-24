#include<iostream>
#include<random>
#include<chrono>
#include<fstream>
#include<cmath>
int max(int a,int b){
    if(a>b)
        return a;
    return b;
}
struct node
{
    int value;
    node* left;
    node* right;
    signed char balance;
    node *parent;
    node(int x):value(x),left(nullptr),right(nullptr),balance(0),parent(nullptr){}
};
void delete_tree(node *root){
    if(root!=nullptr){
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}
int height(node *nd){
    int h=0;
    if(nd!=nullptr)
        h=max(height(nd->left),height(nd->right))+1;
    return h;
}
int gimmeBalance(node *nd) {
   if(nd!=nullptr){
       return height(nd->right)-height(nd->left);
   }
   return -123;
}
void draw_tree(node* root,int k=0){
    if(root!=nullptr){
        draw_tree(root->right,k+4);
        for(int i=0;i<k;i++)
                std::cout<<" ";
        std::cout<<"->"<<root->value<<"\n";
        draw_tree(root->left,k+4);
    }
    else{
        for(int i=0;i<k;i++)
            std::cout<<" ";
        std::cout<<",->nullptr\n";    
    }
}   
node *left_rot(node *root){
    node* temp=root;
    root->right->parent=root->parent;
    if(root->parent!=nullptr){
        if(root->parent->right==root){
            root->parent->right=root->right;
        }
        else if(root->parent->left==root){
            root->parent->left=root->right;
        }
    }
    root=root->right;
    //child of THE RIGHT ELEMENT CONNECT PARENT AND CHILD
    temp->right=root->left;
    if(root->left!=nullptr)
        root->left->parent=temp;
    root->left=temp;
    root->left->parent=root;
    return root;
}
node *right_rot(node *root){
     node* temp=root;
    root->left->parent=root->parent;
    if(root->parent!=nullptr){
        if(root->parent->right==root){
            root->parent->right=root->left;
        }
        else if(root->parent->left==root){
            root->parent->left=root->left;
        }
    }
    root=root->left;
    //child of THE RIGHT ELEMENT CONNECT PARENT AND CHILD
    temp->left=root->right;
    if(root->right!=nullptr)
        root->right->parent=temp;
    root->right=temp;
    root->right->parent=root;
    return root;
}
node *rl_rot(node *r){
    left_rot(r->left);
    right_rot(r);
    return r;
}
node *lr_rot(node *r){
    right_rot(r->right);
    left_rot(r);
    return r;
}
void update_balances(node *r){
    if(r->left!=nullptr){
        r->left->balance=gimmeBalance(r->left);
    }
    if(r->right!=nullptr){
        r->right->balance=gimmeBalance(r->right);
    }
    r->balance=gimmeBalance(r);
}
node* rotate(node *prt){
    if(prt->balance>1){
            if(prt->right->balance>0){
                prt=left_rot(prt);
            }
            else{
                prt=lr_rot(prt);
            }
        }
        else if(prt->balance<-1){
            if(prt->left->balance>0){
                prt=rl_rot(prt);
            }
            else{
                prt=right_rot(prt);
            }
    }
    return prt;
}

struct AVL
{
    node * root;
    AVL():root(nullptr){}
    ~AVL(){
        delete_tree(root);
    }
    void clean(){
         if(root!=nullptr){
            delete_tree(root);
            root=nullptr;
         }
    }
   	
        

    node *insert(node *ptr,int x){
        node *temp=ptr;
        while(temp != nullptr){
            ptr=temp;
            if(x<temp->value){
                temp=temp->left;
            }
            else{
                temp=temp->right;
            }
        }
        
        if(ptr==nullptr){
            ptr=new node(x);
        }
        else{
            if(x<ptr->value){
                ptr->left = new node(x);
                ptr->left->parent=ptr;
            }
            else{
                ptr->right = new node(x);
                ptr->right->parent=ptr;
            }
        }
        temp=ptr;
        bool once= true;
        while(temp!=nullptr || once == true){
                //update balances
                update_balances(ptr);
                //rotate if necessary
                ptr=rotate(ptr);
                //update balances
                update_balances(ptr);     
                if(ptr->parent!=nullptr){
                    ptr=ptr->parent;
                }
                if(ptr->parent==nullptr && temp==nullptr){
                    once=false;
                }
                temp=ptr->parent;
        }
        return ptr;
    }

    void ins(int x) {
        if (root == nullptr) {
            root = new node(x);
        } else {
            root=insert(root, x);
        }
	}

    node *search(int x){
        node *nd=root;
        while(nd!=nullptr){
            if(nd->value==x){
                return nd;
            }
            else if(x<nd->value){
                nd=nd->left;
            }
            else{
                nd=nd->right;
            }
        }
        return nullptr;
    }
};
struct BST{
    node *root;
    BST():root(nullptr){}
    ~BST(){
        delete_tree(root);
    }
    void clean(){
        if(root!=nullptr){
        delete_tree(root);
        root=nullptr;
        }
    }
    void insert(int x){
        node *parent=nullptr;
        node *ptr = root;
        node *newbee = new node(x);
        while(ptr != nullptr){
            parent=ptr;
            if(x<ptr->value){
                ptr=ptr->left;
            }
            else{
                ptr=ptr->right;
            }
        }
        if(parent==nullptr){
            root=newbee;
        }
        else{
            if(x<parent->value){
                parent->left = newbee;
            }
            else{
                parent->right = newbee;
            }
        }
    }
    //searches bst for a number
    //if found - returns the node with the value
    //if not found returns nullptr
    node *search(int x){
        node *nd=root;
        while(nd!=nullptr){
            if(nd->value==x){
                return nd;
            }
            else if(x<nd->value){
                nd=nd->left;
            }
            else{
                nd=nd->right;
            }
        }
        return nullptr;
    }
};
void slightly(int *arr,int n,std::mt19937 &gen){
    std::uniform_int_distribution<int> stopper(0,(int)sqrt(n));
    std::uniform_int_distribution<int> small_dist(1,10);
    int sum=0;

    for(int i=0;i<n;i++){
        int stop=stopper(gen);
        int r=small_dist(gen);
        if(stop==0){
            sum=r;
        }
        else{
            sum+=r;
        }
        arr[i]=sum;
    }
}
bool isInArray(int value,int *arr,int n){
    for(int i=0;i<n;i++){
        if(arr[i]==value)
            return true;
    }
    return false;
}
int main(){
   
    std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::fstream f("C:\\data.csv");
    f<<"size,AVL_RAND_INSERT,AVL_RAND_PRESENT,AVL_RAND_NON_PRESENT,";
    f<<"AVL_ORD_INSERT,AVL_ORD_PRESENT,AVL_ORD_NON";
    f<<"AVL_SLIGH_INSERT,AVL_SL_PRESENT,AVL_SL_NON";
    f<<"BST_RAND_INSERT,BST_RAND_PRESENT,BST_RAND_NON_PRESENT,";
    f<<"BST_ORD_INSERT,BST_ORD_PRESENT,BST_ORD_NON";
    f<<"BST_SLIGH_INSERT,BST_SL_PRESENT,BST_SL_NON";
    f<<"\n";
    


    int max_times=10;
    for(int size=10;size<10100;size+=103){
        std::cout<<size<<",";
        f<<size<<",";
        std::chrono::nanoseconds total(0);
        std::uniform_int_distribution<int> inside(0,size-1);
        //initialize arrays
        //random
        int *myarr1 = new int[size]; 
        //slightly
        int *myarr3 = new int[size];
        //generate random nums
        slightly(myarr3,size,gen);
        for(int i=0;i<size;i++){
            myarr1[i]=gen();
        }
        AVL av;
        //random insertion
        for(int k=0;k<max_times;k++){
            av.clean();
            for(int i=0;i<size;i++){    
                auto start=std::chrono::steady_clock::now();
                    av.ins(myarr1[i]);
                auto end=std::chrono::steady_clock::now();
                std::chrono::nanoseconds current(end-start);
                total+=current;
            }
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //present search
        for(int i=0;i<max_times;i++){
            auto start=std::chrono::steady_clock::now();
                av.search(myarr1[inside(gen)]);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //non-present search
        for(int i=0;i<max_times;i++){
            int temp=gen();
            while(isInArray(temp,myarr1,size)){
                temp=gen();
            }
            auto start=std::chrono::steady_clock::now();
                av.search(temp);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        av.clean();

        //ordered insertion
        for(int k=0;k<max_times;k++){
            av.clean();
            for(int i=0;i<size;i++){
                auto start=std::chrono::steady_clock::now();
                    av.ins(i);
                auto end=std::chrono::steady_clock::now();
                std::chrono::nanoseconds current(end-start);
                total+=current;
            }
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //present search
        for(int i=0;i<max_times;i++){
            auto start=std::chrono::steady_clock::now();
                av.search(inside(gen));
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //non-present search
        for(int i=0;i<max_times;i++){
            int temp=(size+i);
            if(i%2==0){
                temp=temp*(-1);
            }
            auto start=std::chrono::steady_clock::now();
                av.search(temp);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        av.clean();
        //slightly insertion
        for(int k=0;k<max_times;k++){
            av.clean();
            for(int i=0;i<size;i++){ 
                auto start=std::chrono::steady_clock::now();
                    av.ins(myarr3[i]);
                auto end=std::chrono::steady_clock::now();
                std::chrono::nanoseconds current(end-start);
                total+=current;
            }
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //present search
        for(int i=0;i<max_times;i++){
            auto start=std::chrono::steady_clock::now();
                av.search(myarr3[inside(gen)]);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //non-present search
        for(int i=0;i<max_times;i++){
            int temp=gen();
            while(isInArray(temp,myarr3,size)){
                temp=gen();
            }
            auto start=std::chrono::steady_clock::now();
                av.search(temp);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        av.clean();
        BST bs;
        //random insertion
        for(int k=0;k<max_times;k++){
            av.clean();
            for(int i=0;i<size;i++){ 
                auto start=std::chrono::steady_clock::now();
                    bs.insert(myarr1[i]);
                auto end=std::chrono::steady_clock::now();
                std::chrono::nanoseconds current(end-start);
                total+=current;
            }
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //present search
        for(int i=0;i<max_times;i++){
            auto start=std::chrono::steady_clock::now();
                bs.search(myarr1[inside(gen)]);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current=end-start;
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //non-present search
        for(int i=0;i<max_times;i++){
            int temp=gen();
            while(isInArray(temp,myarr1,size)){
                temp=gen();
            }
            auto start=std::chrono::steady_clock::now();
                bs.search(temp);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        bs.clean();

        //ordered insertion
        for(int k=0;k<max_times;k++){
            av.clean();
            for(int i=0;i<size;i++){ 
                auto start=std::chrono::steady_clock::now();
                bs.insert(i);
                auto end=std::chrono::steady_clock::now();
                std::chrono::nanoseconds current(end-start);
                total+=current;
            }
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //present search
        for(int i=0;i<max_times;i++){
            auto start=std::chrono::steady_clock::now();
                bs.search(inside(gen));
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //non-present search
        for(int i=0;i<max_times;i++){
            int temp=(size+i);
            if(i%2==0){
                temp=temp*(-1);
            }
            auto start=std::chrono::steady_clock::now();
                bs.search(temp);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        bs.clean();

        //slightly insertion
        for(int k=0;k<max_times;k++){
            bs.clean();
            for(int i=0;i<size;i++){
                auto start=std::chrono::steady_clock::now();
                    bs.insert(myarr3[i]);
                auto end=std::chrono::steady_clock::now();
                std::chrono::nanoseconds current(end-start);
                total+=current;
            }
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //present search
        for(int i=0;i<max_times;i++){
            auto start=std::chrono::steady_clock::now();
                bs.search(myarr3[inside(gen)]);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times<<",";
        std::cout<<total.count()/max_times<<",";
        total=std::chrono::nanoseconds::zero();
        //non-present search
        for(int i=0;i<max_times;i++){
            int temp=gen();
            while(isInArray(temp,myarr3,size)){
                temp=gen();
            }
            auto start=std::chrono::steady_clock::now();
                bs.search(temp);
            auto end=std::chrono::steady_clock::now();
            std::chrono::nanoseconds current(end-start);
            total+=current;
        }
        f<<total.count()/max_times;
        std::cout<<total.count()/max_times;
        total=std::chrono::nanoseconds::zero();
        bs.clean();
        delete []myarr1;
        delete []myarr3;
        
        f<<"\n";
        std::cout<<"\n";
    }
}