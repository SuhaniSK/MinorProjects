#include<iostream>
using namespace std;
struct node{
    int data;
    struct node* llink;
    struct node* rlink;
};
class dlist{
    int count;
    node* first;
    node* last;
    public:dlist(){
        first=last=NULL;
        count=0;
    }
    void insertfirst(int data);
    void insertnode(int data,int pos);
    void delnode(int pos);
    void show();
};
void dlist::insertfirst(int data){
    node* newnode=new node;
    newnode->data=data;
    newnode->llink=NULL;
    newnode->rlink=NULL;
    if(first==NULL){
        first =last =newnode;
    }
    else{
        newnode->rlink=first;
        first->llink=newnode;
        first=newnode;
    }
    cout<<"inserted successfully\n";
     count++;
}
void dlist::insertnode(int data,int pos){
    if(pos<1||pos>count+1){
        cout<<"invalid pos\n";
        return;
    }
    node* newnode=new node;
    newnode->data=data;

    if(pos==count+1){
       last->rlink=newnode;
       newnode->llink=last;
       newnode->rlink=NULL;
       last=newnode;
    }
    else{
        node* temp=first;
        for(int i=1;i<pos;i++){
            temp=temp->rlink;
        }
    newnode->rlink=temp->rlink;
    newnode->llink=temp;
        if(temp->rlink!=NULL){
            temp->rlink->llink=newnode;
        }
        temp->rlink=newnode;
    }
    count++;
    cout<<"inserted successfully\n";
}
void dlist:: delnode(int pos){
    if(pos<1||pos>count){
        cout<<"invalid position\n";
        return;
    }
    node *temp;
    int data;
    if(pos==count){
        temp=last;
        last=last->llink;
        if(last!=NULL){
            last->rlink=NULL;
        }
        data=temp->data;
        delete temp;
        if(count==1){
            first=NULL;
        }
    }
    else if(pos==1){
        temp=first;
        first=first->rlink;
        if(first!=NULL){
            first->llink=NULL;
        }
        data=temp->data;
        delete temp;
        if(count==1){
            last=NULL;
        }
    }
    else{
        temp=first;
        for(int i=1;i<pos;i++){
            temp=temp->rlink;
        }
        temp->llink->rlink=temp->rlink;
        if(temp->rlink!=NULL){
            temp->rlink->llink=temp->llink;
        }
        data=temp->data;
        delete temp;
    }
    cout<<"deleted successfully:"<<data<<endl;
    count--;
}
void dlist::show(){
    node *temp=first;
    if(temp==NULL){
        cout<<"the list is empty\n";
    }
    else{
        cout<<"the contents in the list are:\n";
        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->rlink;
        }
        cout<<endl;
    }
}
int main(){
    dlist d;
    int choice,ele,pos;
    do{
        cout<<"menu\n1.inser\n2.delete\n3.display\n4.exit\nenter ur choice:\n";
        cin>>choice;
        switch(choice){
            case 1:cout<<"enter element to insert:\n";
            cin>>ele;
            cout<<"enter position :\n";
            cin>>pos;
            if(pos==1){
                d.insertfirst(ele);
            }
            else
            d.insertnode(ele,pos);
            d.show();
            break;
            case 2:cout<<"enter position to delete :\n";
            cin>>pos;
            
            d.delnode(pos);
            d.show();
            break;
            case 3:cout<<"exiting the program\n";
            break;
        }
    }while(choice!=3);
    return 0;
}