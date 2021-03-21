/*
 * This is a generic AVL tree implementaion
 * Made by Saleem Elias
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H
int max(int a,int b){return a>b?a:b;}
template<typename T,typename V>
class avlnode{
    T key;
    V* data;
    avlnode *father,*rightson,*leftson;
    int height;
    void LLcase(){ //the right right case is when the balance of "this" is -2
                   // assuming that minus symbolizes that left side has more height
/*T1, T2, T3 and T4 are subtrees.
         z                                      y
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
 */
        if(!this)
            return;
        avlnode<T,V>* grandfather=this->father; //fetch the father of z(in drawing)
        if(grandfather){
            if(grandfather->leftson==this)
                grandfather->leftson=this->leftson;
            else
                grandfather->rightson=this->leftson;
        }
        avlnode<T,V>* templeftson=this->leftson; //backup leftson of z
        templeftson->father=this->father; //the father of leftson is the grandfather now
        this->leftson=templeftson->rightson;
        this->father=templeftson;
        if (templeftson->rightson) {
            templeftson->rightson->father = this;
        }
        templeftson->rightson=this;
        this->heightupdate();
        this->father->heightupdate();
    }
    void RRcase() { //the left left case is the exact opposite of right right case
/*
  z                                y
 /  \                            /   \
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
 */
        if (!this)
            return;
        avlnode<T, V> *grandfather = this->father; //fetch the father of z(in drawing)
        if (grandfather) {
            if (grandfather->leftson == this)
                grandfather->leftson = this->rightson;
            else
                grandfather->rightson = this->rightson;
        }
        avlnode<T, V> *temprightson = this->rightson; //backup leftson
        temprightson->father = this->father; //the father of leftson is the father now
        this->rightson = temprightson->leftson;
        this->father = temprightson;
        if (temprightson->leftson) {
            temprightson->leftson->father = this;
        }
        temprightson->leftson=this;
        this->heightupdate();
        this->father->heightupdate();
    }
    void LRcase(){
/*
      z                               z                           x
     / \                            /   \                        /  \
    y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
   / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
 T1   x                          y    T3                    T1  T2 T3  T4
     / \                        / \
   T2   T3                    T1   T2
 */
        if(!this)
            return;
        this->leftson->RRcase();
        this->LLcase();
    }
    void RLcase(){
/*
   z                            z                            x
  / \                          / \                          /  \
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4
 */
        if(!this)
            return;
        this->rightson->LLcase();
        this->RRcase();
    }
public:
    avlnode(T key,V& data,avlnode* left= nullptr,avlnode* right= nullptr,avlnode* dad= nullptr,int height = 0){
        this->key=key;
        this->data=&data;
        this->leftson=left;
        this->rightson=right;
        this->father=dad;
        this->height=0;
    }

    bool operator>(const avlnode<T,V> node)const{ //because key is generic.we defined bigger operator.
            return key>node.key;
    }
    ~avlnode(){
        delete this->data;
    }
    avlnode operator=(const avlnode& tocopy)=delete;
    //Getters here
    T getkey(){
        return this->key;
    }
    V* getdata(){
        return this->data;
    }
    avlnode* getfather(){
        return this->father;
    }
    avlnode* getrightson(){
        return this->rightson;
    }
    avlnode* getleftson(){
        return this->leftson;
    }
    int getheight(){
        return this?this->height:-1;
    }
    int getbalance(){
        int right=this->rightson?this->rightson->height+1:0;
        int left =this->leftson?this->leftson->height+1:0;
        return (right-left);
    }

    //Setters here
    void setkey(T newkey){
        this->key=newkey;
    }
    void setdata(V* newdata){
        *this->data=*newdata;
    }
    void setfather(avlnode<T,V>* newfather){
        this->father=newfather;
    }
    void setrightson(avlnode* newrightson){
        this->rightson=newrightson;
    }
    void setleftson(avlnode* newleftson) {
        this->leftson = newleftson;
    }

    void setheight(int newheight){
        this->height=newheight;
    }
    //end of getters and setters
    //other functions
    void heightupdate(){
        if(!this)
            return;
        if(this->leftson== nullptr && this->rightson== nullptr)
            height=0;
        else if(this->leftson!= nullptr&&this->rightson== nullptr)
            height=1+this->leftson->height;
        else if(this->leftson== nullptr&&this->rightson!= nullptr)
            height=1+this->rightson->height;
        else
            height=1+max(this->leftson->height,this->rightson->height);
    }
    bool correctbalance(avlnode<T,V>* root){ //checks if balance is bad(bigger than 2 or smaller than -2)
                                                                  // corrects it if it is
        this->heightupdate();
        int balancefactor=this->getbalance();
        if(balancefactor==-2){
            if(this->leftson->getbalance()<=-1)
                this->LLcase();
            else
                this->LRcase();
        }
        else if(balancefactor==2){
            if(this->rightson->getbalance()<=-1)
                this->RLcase();
            else
                this->RRcase();
        }
        return this == root;
    }
};
template<typename T,typename V>
class avltree{
    avlnode<T,V>* root;
    avlnode<T,V>* minnode;
    public:
    avltree(){
        this->root= nullptr;
        this->minnode= nullptr;
    }
    ~avltree(){
        deletetree(this->root);
    }
    void deletetree(avlnode<T,V>* todelete){
        if (!todelete)
            return;
        deletetree(todelete->getleftson());
        deletetree(todelete->getrightson());
        delete todelete;
    }
    avlnode<T,V>* searchnode(T key){
        T currentkey;
        avlnode<T,V>* currentnode= root;
        while(currentnode!= nullptr){
            currentkey=currentnode->getkey();
            if(key==currentkey)
                return currentnode;
            else if(key<currentkey){
                currentnode=currentnode->getleftson();
            }
            else{
                currentnode=currentnode->getrightson();
            }
        }
        return nullptr;
    }
    avlnode<T,V>* searchfather(T keytoinsert){
        avlnode<T,V>* currentnode;
        avlnode<T,V>* fathernode= root;
        if(root->getkey()<keytoinsert)
            currentnode=root->getrightson();
        else
            currentnode=root->getleftson();
        T currentkey;
        while(currentnode!=nullptr){
            currentkey=currentnode->getkey();
            if(keytoinsert==currentkey)
                return nullptr;
            else if(keytoinsert<currentkey){
                fathernode=currentnode;
                currentnode=currentnode->getleftson();

            }
            else{
                fathernode=currentnode;
                currentnode=currentnode->getrightson();
            }
        }
        return fathernode;
    }
    void Balancepath(avlnode<T,V>* insertednode){
        avlnode<T,V>* itr=insertednode;
        bool didwereachroot;
        while(itr!= nullptr){
            didwereachroot=itr->correctbalance(this->root);
            if(didwereachroot){
                if(this->root->getfather()) {
                    this->root = itr->getfather();
                }
            }
            itr=itr->getfather();
        }
    }
    void insertnode(T keytoinsert,V* datatoinsert){
        if(this->root== nullptr){
            auto nodetoinsert=new avlnode<T,V>(keytoinsert,*datatoinsert, nullptr, nullptr, nullptr);
            this->root=nodetoinsert;
            updateminnode();
            return;
        }
        avlnode<T,V>* fathernode=searchfather(keytoinsert);
        if(!fathernode) //if we found a node with identical key
            return;
        auto nodetoinsert=new avlnode<T,V>(keytoinsert,*datatoinsert, nullptr, nullptr,fathernode);
        if(fathernode->getkey()<keytoinsert)
            fathernode->setrightson(nodetoinsert);
        else
            fathernode->setleftson(nodetoinsert);
        Balancepath(nodetoinsert);
        updateminnode();
    }
    avlnode<T,V>* searchreplacement(avlnode<T,V>* toremove){
        avlnode<T,V>* replacementnode=toremove->getleftson();
        if(!replacementnode){
            return nullptr;
        }
        avlnode<T,V>* next=replacementnode->getrightson();
        while(next!= nullptr){
            replacementnode=replacementnode->getrightson();
            next=replacementnode->getrightson();
        }
        return replacementnode;
    }
    void removerootnode(){
        avlnode<T,V>* toreplace=searchreplacement(this->root);
        if(!toreplace){ //if there is no leftson for the node we want to remove
            //then we replace it with the rightson
            toreplace=this->root->getrightson();
            toreplace->setfather(nullptr);
            delete this->root;
            this->root=toreplace;
            Balancepath(toreplace);
            updateminnode();
            return;
        }
        else if(toreplace->getfather()==this->root){ //if there is no rightson for the leftson
                                                     //of the node we want to remove then we
                                                     //replace that node with its leftson
            toreplace->setfather(nullptr);
            toreplace->setrightson(this->root->getrightson());
            if(this->root->getrightson()) {
                this->root->getrightson()->setfather(toreplace);
            }
            delete this->root;
            this->root=toreplace;
            Balancepath(toreplace);
            updateminnode();
            return;
        }
        else{ //if there is a right son for the leftson of the node we want to remove
            //then we replace that node with the utmost right son of the leftson
            avlnode<T,V>* fatheroftoreplace=toreplace->getfather();
            fatheroftoreplace->setrightson(toreplace->getleftson());
            if(toreplace->getleftson())
                toreplace->getleftson()->setfather(fatheroftoreplace);
            toreplace->setfather(nullptr);
            toreplace->setleftson(this->root->getleftson());
            toreplace->setrightson(this->root->getrightson());
            this->root->getrightson()->setfather(toreplace);
            this->root->getleftson()->setfather(toreplace);
            if(this->root->getrightson()) {
                this->root->getrightson()->setfather(toreplace);
            }
            delete this->root;
            this->root=toreplace;
            toreplace->heightupdate();
            Balancepath(fatheroftoreplace);
            updateminnode();
            return;
        }
    }
    void removenode(T key){
        avlnode<T,V>* toremove=searchnode(key);
        if(!this||!toremove)
            return;
        avlnode<T,V>* toreplace=searchreplacement(toremove);
        avlnode<T,V>* father=toremove->getfather();
        if(!father&&!toremove->getleftson()&&!toremove->getrightson()){
            //if toremove is the root and there are no sons , simply delete it
            this->root= nullptr;
            delete toremove;
            this->minnode= nullptr;
            return;
        }
        if(toremove==this->root){
            removerootnode();
            updateminnode();
            return;
        }
        if(!toreplace){ //if there is no leftson for the node we want to remove
                        //then we replace it with the rightson , if in addition there
                        //isn't a rightson then we simply delete it
            if(father->getleftson()==toremove){
                if(!toremove->getrightson()){
                    delete toremove;
                    father->setleftson(nullptr);
                    Balancepath(father);
                    updateminnode();
                    return;
                }
                father->setleftson(toremove->getrightson());
                toremove->getrightson()->setfather(father);
                delete toremove;
            }
            else if(father->getrightson()==toremove){
                if(!toremove->getrightson()){
                    delete toremove;
                    father->setrightson(nullptr);
                    Balancepath(father);
                    updateminnode();
                    return;
                }
                father->setrightson(toremove->getrightson());
                toremove->getrightson()->setfather(father);
                delete toremove;
            }
            Balancepath(father);
            updateminnode();
            return;
        }
        else if(toreplace->getfather()==toremove){ //if there is no rightson for the leftson
                                                   //of the node we want to remove then we
                                                   //replace that node with its leftson
            if(toremove==father->getleftson()){
                father->setleftson(toreplace);
            }
            if(toremove==father->getrightson()){
                father->setrightson(toreplace);
            }
            toreplace->setfather(father);
            toreplace->setrightson(toremove->getrightson());
            if(toremove->getrightson()) {
                toremove->getrightson()->setfather(toreplace);
            }
            delete toremove;
            toreplace->heightupdate();
            Balancepath(father);
            updateminnode();
            return;
        }
        else{ //if there is a right son for the leftson of the node we want to remove
              //then we replace that node with the utmost right son of the leftson
            avlnode<T,V>* fatheroftoreplace=toreplace->getfather();
            if(toremove==father->getleftson()){
                father->setleftson(toreplace);
            }
            if(toremove==father->getrightson()){
                father->setrightson(toreplace);
            }
            toreplace->setfather(father);
            fatheroftoreplace->setrightson(toreplace->getleftson());
            if(toreplace->getleftson())
                toreplace->getleftson()->setfather(fatheroftoreplace);
            toreplace->setleftson(toremove->getleftson());
            toreplace->setrightson(toremove->getrightson());
            if(toremove->getrightson()) {
                toremove->getrightson()->setfather(toreplace);
            }
            toremove->getleftson()->setfather(toreplace);
            delete toremove;
            toreplace->heightupdate();
            Balancepath(fatheroftoreplace);
            updateminnode();
            return;
        }
    }
    void PrintTreeInOrder(){
        printInOrder(root);
    }
    void printInOrder(avlnode<T,V>* rootoftree)const{
        if(!rootoftree)
            return;
        printInOrder(rootoftree->getleftson());
        std::cout<< rootoftree->getkey() <<std::endl;
        printInOrder(rootoftree->getrightson());
    }
    int nodecount(){
        int a=0;
        countnodesintree(root,&a);
        return a;
    }
    void countnodesintree(avlnode<T,V>* rootoftree,int* counter)const{
        if(!rootoftree)
            return;
        countnodesintree(rootoftree->getleftson(),counter);
        *counter+=1;
        countnodesintree(rootoftree->getrightson(),counter);
    }

    avlnode<T,V>* getRoot() {
        return  this->root;
    }
    bool updateminnode(){
        if(!root)
            return false;
        auto node=root;
        auto leftnode=node->getleftson();
        while(leftnode!= nullptr){
            node=leftnode;
            leftnode=leftnode->getleftson();
        }
        if(node==this->minnode)
            return false;
        this->minnode=node;
        return true;
    }
    avlnode<T,V>* getminnode(){
        return minnode;
    }
};







#endif //AVLTREE_AVLTREE_H
