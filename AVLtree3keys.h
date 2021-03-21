#include <iostream>
/*
 * This is a generic AVL rank tree with 3 key sorting implementaion
 * Made by Saleem Elias
 */
using std::cin;
using std::cout;
using std::endl;
#ifndef TEMPMIVNI_AVLTREE3KEYS_H
#define TEMPMIVNI_AVLTREE3KEYS_H
int max(int a,int b){return a>b?a:b;}
template<typename T>
class avlnode3key{
    T key1;
    T key2;
    T key3;
    avlnode3key *father,*rightson,*leftson;
    int height;
    int numofvertices;
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
        avlnode3key<T>* grandfather=this->father; //fetch the father of z(in drawing)
        if(grandfather){ //updating grandfather for new son, numofvertices does not change
            if(grandfather->leftson==this)
                grandfather->leftson=this->leftson;
            else
                grandfather->rightson=this->leftson;
        }
        avlnode3key<T>* templeftson=this->leftson; //backup leftson of z
        templeftson->father=this->father; //the father of leftson is the grandfather now
        templeftson->numofvertices=this->numofvertices; //y now has the number of vertices of z
        this->leftson=templeftson->rightson; // z leftson is now T3
        if(this->rightson)
            this->numofvertices = this->rightson->numofvertices+1; // update z numberofvertices without T3 (we will update it in a bit)
        else
            this->numofvertices = 1;
        this->father=templeftson; //update z father to be y
        if (templeftson->rightson) {
            this->numofvertices+=templeftson->rightson->numofvertices; //add T3 num of vertices to z
            templeftson->rightson->father = this;
        }
        templeftson->rightson=this; //update rightson of y
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
        avlnode3key<T> *grandfather = this->father; //fetch the father of z(in drawing)
        if (grandfather) {
            if (grandfather->leftson == this)
                grandfather->leftson = this->rightson;
            else
                grandfather->rightson = this->rightson;
        }
        avlnode3key<T> *temprightson = this->rightson; //backup leftson
        temprightson->father = this->father; //the father of leftson is the father now
        temprightson->numofvertices=this->numofvertices; //y now has the number of vertices of z
        this->rightson = temprightson->leftson;
        if(this->leftson)
            this->numofvertices=this->leftson->numofvertices+1; // update z numberofvertices without T2 (we will update it in a bit)
        else
            this->numofvertices = 1;
        this->father = temprightson;
        if (temprightson->leftson) {
            this->numofvertices+=temprightson->leftson->numofvertices; //add T2 num of vertices to z
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
    avlnode3key(T key1,T key2 ,T key3 ,avlnode3key* left= nullptr,
            avlnode3key* right= nullptr,avlnode3key* dad= nullptr,int height=0,int numofvertices=1){
        this->key1=key1;
        this->key2=key2;
        this->key3=key3;
        this->leftson=left;
        this->rightson=right;
        this->father=dad;
        this->height=height;
        this->numofvertices=numofvertices;
    }
    bool operator>(const avlnode3key<T> node)const{ //because key is generic.we defined bigger operator.
        if(key1<node.key1)
            return false;
        else if (key1>node.key1)
            return true;
        else
        {
            if(key2<node.key2)
                return true;
            else if(key2>node.key2)
                return false;
            else{
                if(key3<node.key3)
                    return true;
                else
                    return false;
            }
        }
    }
    bool operator<(const avlnode3key<T> node)const{ //because key is generic.we defined bigger operator.
    return !(*this>node);
    }
    bool operator==(const avlnode3key<T> node)const{
        if((key1==node.key1)&&(key2==node.key2)&&(key3==node.key3))
            return true;
        return false;
    }
    bool operator!=(const avlnode3key<T> node)const{
         return !(*this==node);
    }
    ~avlnode3key()=default;
    avlnode3key operator=(const avlnode3key& tocopy)=delete;
    //Getters here
    T getkey1(){
        return key1;
    }
    T getkey2(){
        return key2;
    }
    T getkey3(){
        return key3;
    }
    avlnode3key* getfather(){
        return this->father;
    }
    avlnode3key* getrightson(){
        return this->rightson;
    }
    avlnode3key* getleftson(){
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
    int getnumofvertices(){
        if(!this)
            return 0;
        return numofvertices;
    }

    //Setters here
    void setkey1(T newkey){
        this->key1=newkey;
    }
    void setkey2(T newkey){
        this->key2=newkey;
    }
    void setkey3(T newkey){
        this->key3=newkey;
    }
    void setfather(avlnode3key<T>* newfather){
        this->father=newfather;
    }
    void setrightson(avlnode3key* newrightson){
        this->rightson=newrightson;
    }
    void setleftson(avlnode3key* newleftson) {
        this->leftson = newleftson;
    }

    void setheight(int newheight){
        this->height=newheight;
    }
    void incrementnumofvertices(){
        this->numofvertices++;
    }
    void decrementnumofvertices(){
        this->numofvertices--;
    }
    void setnumofvertices(int num){
        this->numofvertices=num;
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
    bool correctbalance(avlnode3key<T>* root){ //checks if balance is bad(bigger than 2 or smaller than -2)
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
template<typename T>
class avlthreekeyranktree{
    avlnode3key<T>* root;
    avlnode3key<T>* minnode;
public:
    avlthreekeyranktree(){
        this->root= nullptr;
        this->minnode= nullptr;
    }
    ~avlthreekeyranktree(){
        deletetree(this->root);
    }
    void deletetree(avlnode3key<T>* todelete){
        if (!todelete)
            return;
        deletetree(todelete->getleftson());
        deletetree(todelete->getrightson());
        delete todelete;
    }
    avlnode3key<T>* searchnode(T key1,T key2,T key3) {
        avlnode3key<T> *currentnode = root;
        auto nodetocompare = new avlnode3key<T>(key1, key2, key3);
        while(currentnode!= nullptr){
            if(*currentnode==*nodetocompare) {
                delete nodetocompare;
                return currentnode;
            }
            else if(*currentnode<*nodetocompare){
                currentnode=currentnode->getrightson();
            }
            else{
                currentnode=currentnode->getleftson();
            }
        }
        delete nodetocompare;
        return nullptr;
    }
    avlnode3key<T>* searchfather(T key1,T key2,T key3){
        auto nodetoinsert = new avlnode3key<T>(key1, key2, key3);
        avlnode3key<T>* currentnode;
        avlnode3key<T>* fathernode= root;
        if(*root<*nodetoinsert)
            currentnode=root->getrightson();
        else
            currentnode=root->getleftson();
        while(currentnode!=nullptr){
            if(*currentnode==*nodetoinsert) {
                delete nodetoinsert;
                return nullptr;
            }
            else if(*nodetoinsert<*currentnode){
                fathernode=currentnode;
                currentnode=currentnode->getleftson();

            }
            else{
                fathernode=currentnode;
                currentnode=currentnode->getrightson();
            }
        }
        delete nodetoinsert;
        return fathernode;
    }
    void Balancepath(avlnode3key<T>* insertednode){
        avlnode3key<T>* itr=insertednode;
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
    void updatenumofverticespath(T key1,T key2,T key3,bool mode){ //if mode is 0 then decrement , if 1 then increment
        auto nodetoinsert = new avlnode3key<T>(key1, key2, key3);
        avlnode3key<T>* current = root;
        if(mode) {
            while (*current != *nodetoinsert) {
                current->incrementnumofvertices();
                if(*current<*nodetoinsert)
                    current = current->getrightson();
                else
                    current = current->getleftson();
            }
        }
        else{
            while (*current != *nodetoinsert) {
                current->decrementnumofvertices();
                if(*current<*nodetoinsert)
                    current = current->getrightson();
                else
                    current = current->getleftson();
            }
            current->decrementnumofvertices();
        }
        delete nodetoinsert;
    }
    void insertnode(T key1,T key2,T key3){
        if(this->root== nullptr){
            auto nodetoinsert=new avlnode3key<T>(key1,key2,key3,nullptr, nullptr, nullptr);
            this->root=nodetoinsert;
            updateminnode();
            return;
        }
        avlnode3key<T>* fathernode=searchfather(key1,key2,key3);
        if(!fathernode) //if we found a node with identical key
            return;
        auto nodetoinsert=new avlnode3key<T>(key1,key2,key3,nullptr, nullptr,fathernode);
        if(*fathernode<*nodetoinsert)
            fathernode->setrightson(nodetoinsert);
        else
            fathernode->setleftson(nodetoinsert);
        updatenumofverticespath(key1,key2,key3,true);
        Balancepath(nodetoinsert);
        updateminnode();
    }
    avlnode3key<T>* searchreplacement(avlnode3key<T>* toremove){
        avlnode3key<T>* replacementnode=toremove->getleftson();
        if(!replacementnode){
            return nullptr;
        }
        avlnode3key<T>* next=replacementnode->getrightson();
        while(next!= nullptr){
            replacementnode=replacementnode->getrightson();
            next=replacementnode->getrightson();
        }
        return replacementnode;
    }
    void removerootnode(){
        avlnode3key<T>* toreplace=searchreplacement(this->root);
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
            avlnode3key<T>* fatheroftoreplace=toreplace->getfather();
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
            updatenumofverticespath(fatheroftoreplace->getkey1(),fatheroftoreplace->getkey2(),fatheroftoreplace->getkey3(),false);
            Balancepath(fatheroftoreplace);
            updateminnode();
            return;
        }
    }
    void removenode(T key1,T key2,T key3){
        avlnode3key<T>* toremove=searchnode(key1,key2,key3);
        if(!this||!toremove)
            return;
        avlnode3key<T>* toreplace=searchreplacement(toremove);
        avlnode3key<T>* father=toremove->getfather();
        if(!father&&!toremove->getleftson()&&!toremove->getrightson()){
            //if toremove is the root and there are no sons , simply delete it
            this->root= nullptr;
            delete toremove;
            this->minnode= nullptr;
            return;
        }
        if(toremove==this->root){
            removerootnode();
            root->setnumofvertices(root->getrightson()->getnumofvertices()+root->getleftson()->getnumofvertices()+1);
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
                    updatenumofverticespath(father->getkey1(),father->getkey2(),father->getkey3(),false);
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
                    updatenumofverticespath(father->getkey1(),father->getkey2(),father->getkey3(),false);
                    Balancepath(father);
                    updateminnode();
                    return;
                }
                father->setrightson(toremove->getrightson());
                toremove->getrightson()->setfather(father);
                delete toremove;
            }
            updatenumofverticespath(father->getkey1(),father->getkey2(),father->getkey3(),false);
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
            updatenumofverticespath(father->getkey1(),father->getkey2(),father->getkey3(),false);
            toreplace->setnumofvertices(toreplace->getrightson()->getnumofvertices()+toreplace->getleftson()->getnumofvertices()+1);
            Balancepath(father);
            updateminnode();
            return;
        }
        else{ //if there is a right son for the leftson of the node we want to remove
            //then we replace that node with the utmost right son of the leftson
            avlnode3key<T>* fatheroftoreplace=toreplace->getfather();
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
            updatenumofverticespath(fatheroftoreplace->getkey1(),fatheroftoreplace->getkey2(),fatheroftoreplace->getkey3(),false);
            toreplace->setnumofvertices(toreplace->getrightson()->getnumofvertices()+toreplace->getleftson()->getnumofvertices()+1);
            Balancepath(fatheroftoreplace);
            updateminnode();
            return;
        }
    }
    void PrintTreeInOrder(){
        printInOrder(root);
    }
    void printInOrderkey1(avlnode3key<T>* rootoftree)const{
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
    void countnodesintree(avlnode3key<T>* rootoftree,int* counter)const{
        if(!rootoftree)
            return;
        countnodesintree(rootoftree->getleftson(),counter);
        *counter+=1;
        countnodesintree(rootoftree->getrightson(),counter);
    }

    avlnode3key<T>* getRoot() {
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
    avlnode3key<T>* getminnode(){
        return minnode;
    }
    avlnode3key<T>* searchrank(int rank){ //returns the node with the given rank, if rank>numberofnodes we return nullptr
        if(!root)
            return nullptr;
        avlnode3key<T>* current=root;
        int currentrank=current->getrightson()->getnumofvertices()+1;
        while(true){
            if(currentrank==rank)
                return current;
            else if(currentrank<rank){
                current=current->getleftson();
                if(current == nullptr)
                    return nullptr;
                currentrank+=current->getrightson()->getnumofvertices()+1;
            }
            else{
                current=current->getrightson();
                if(current == nullptr)
                    return nullptr;
                currentrank -= (current->getleftson()->getnumofvertices()+1);
            }
        }
    }
};

#endif //TEMPMIVNI_AVLTREE3KEYS_H
