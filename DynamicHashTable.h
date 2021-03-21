
#ifndef TEMPMIVNI_DYNAMICHASHTABLE_H
#define TEMPMIVNI_DYNAMICHASHTABLE_H
// This is a dynamic Hash Table implementation
// Uses chain hashing method
// Made by Saleem Elias
#define  MINIMUM_TABLE_SIZE 64
template <typename T>
struct Element{
    Element* next;
    int key;
    T* data;
    Element(int key,T* data,Element* next){
        this->next=next;
        this->key=key;
        this->data=data;
    }
    ~Element(){
        delete data;
    };
};
template<typename T>
class HashTable{
    Element<T>** Elementarray;
    int numofelements;
    int sizeoftable;
    int loadfactor;
    void doublearraysize(){
        auto newtable = new Element<T>*[sizeoftable*2];
        for (int j = 0; j < sizeoftable * 2; ++j) {
            newtable[j] = nullptr;
        }
        for (int i = 0; i < sizeoftable; i++) {
            while(Elementarray[i] != nullptr){ //remapping of elements in new table
                Element<T>* temp1;
                Element<T>* temp2=Elementarray[i]->next;
                temp1 = newtable[Elementarray[i]->key%(sizeoftable*2)];
                newtable[Elementarray[i]->key%(sizeoftable*2)]=Elementarray[i];
                Elementarray[i]->next=temp1;
                Elementarray[i]=temp2;
            }
        }
        delete[] Elementarray;
        Elementarray = newtable;
        sizeoftable=sizeoftable*2;
    }
    void halvearraysize(){
        auto newtable = new Element<T>*[sizeoftable/2];
        for (int j = 0; j < sizeoftable /2; ++j) {
            newtable[j] = nullptr;
        }
        for (int i = 0; i < sizeoftable; i++) {
            while(Elementarray[i] != nullptr){ //remapping of elements in new table
                Element<T>* temp1;
                Element<T>* temp2=Elementarray[i]->next;
                temp1 = newtable[Elementarray[i]->key%(sizeoftable/2)];
                newtable[Elementarray[i]->key%(sizeoftable/2)]=Elementarray[i];
                Elementarray[i]->next=temp1;
                Elementarray[i]=temp2;
            }
        }
        delete[] Elementarray;
        Elementarray = newtable;
        sizeoftable=sizeoftable/2;
    }
public:
    explicit HashTable(int newloadfactor=4){
        Elementarray = new Element<T>*[MINIMUM_TABLE_SIZE];
        for (int i = 0; i < MINIMUM_TABLE_SIZE; i++) {
            Elementarray[i] = nullptr;
        }
        numofelements = 0;
        sizeoftable = MINIMUM_TABLE_SIZE;
        loadfactor = newloadfactor;
    }
    ~HashTable(){
        for(int i=0;i<sizeoftable;i++) {
            Element<T>* current=Elementarray[i];
            if(!current)
                continue;
            Element<T>* next=current->next;
            while (next!=nullptr) {
                delete current;
                current=next;
                next=next->next;
            }
            delete current;
        }
        delete[] Elementarray;
    }
    bool InsertElement(int key,T* data){
        if(Find(key))
            return false;
        Element<T>* toinsert;
        try {
            toinsert = new Element<T>(key,data,Elementarray[key%sizeoftable]);
        }
        catch (std::bad_alloc& exeption){
            return false;
        }
        Elementarray[key%sizeoftable] = toinsert;
        numofelements++;
        if(numofelements>sizeoftable*loadfactor)
            doublearraysize();
        return true;
    }
    bool RemoveElement(int key){
        auto current = Elementarray[key%sizeoftable];
        if(current->key == key) {
            Elementarray[key%sizeoftable] = current->next;
            delete current;
            numofelements--;
            if(numofelements<(sizeoftable/loadfactor)&&sizeoftable!=MINIMUM_TABLE_SIZE)
                halvearraysize();
            return true;
        }
        auto previous = current;
        current = current->next;
        while(current != nullptr){
            if(current->key == key){
                previous->next=current->next;
                delete current;
                numofelements--;
                if(numofelements<(sizeoftable/loadfactor)&&sizeoftable!=MINIMUM_TABLE_SIZE)
                    halvearraysize();
                return true;
            }
        }
        return false;
    }
    Element<T>* Find(int key){
        auto tofind = Elementarray[key%sizeoftable];
        while(tofind != nullptr && tofind->key != key){
            tofind = tofind->next;
        }
        return tofind;
    }
};


#endif //TEMPMIVNI_DYNAMICHASHTABLE_H
