#include <sys/wait.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <vector>
using std::cout;
using std::endl;

//时钟
static int c=0;
void Clock(){
    printf("%03d",c++);
    sleep(1);
}

//司令部
class Command
{
public:
    Command(const char * commandName,const int commandLifeValue)
        :_commandName(new char[strlen(commandName)+1]())
         ,_commandLifeValue(commandLifeValue)
    {strcpy(_commandName,commandName);}

    ~Command(){delete [] _commandName;}
    //获取现在司令部生命值
    int  getCommandLifeValue(){return _commandLifeValue;}
    //获取司令部名称
    char * getcommandName(){return _commandName;}
    //司令部减少生命值制造武士
    void decrLifeValue(int decrValue){
        _commandLifeValue-=decrValue;
    }
private:
    char * _commandName;
    int _commandLifeValue;
};

//展示武器
void  showWeapons(int i){
    if(i==0){cout<<"sword";}
    if(i==1){cout<<"bomb";}
    if(i==2){cout<<"arrow";}
}

class Warrior
{
public:
    Warrior(const int number,const int lifeValue,Command & commandName)
        :_number(number)
         ,_lifeValue(lifeValue)
         ,_commandName(commandName)
    {commandName.decrLifeValue(lifeValue);}
    int getNumber(){return _number;}
    int getlifeValue(){return _lifeValue;}
    Command & getCommandName(){return _commandName;}
private:
    int _number;
    int _lifeValue;
    Command & _commandName;
};

class Dragon
:public Warrior
{
public:
    Dragon(const int number,const int lifeValue,Command & commandName)
        :Warrior(number,lifeValue,commandName)
         ,_weapons(DragonNumber%3)
         ,_morale(commandName.getCommandLifeValue()/lifeValue)
    {DragonNumber++;}

    void show(){
        Clock();
        cout<<" "<<getCommandName().getcommandName()<<" dragon "<<getNumber()<<" born with strength "<<getlifeValue();
        cout<<" ,"<<DragonNumber<<" dragon "<<" in "<<getCommandName().getcommandName()<<" headquarter"<<endl;
        cout<<"It's has a ";
        showWeapons(_weapons);
        cout<<" and it's morale is "<<_morale<<endl;
    }
private:
    static int DragonNumber;
    int _weapons;
    double _morale;
};
int Dragon::DragonNumber=0;

class Ninja
:public Warrior
{
public:
    Ninja(const int number,const int lifeValue,Command & commandName)
        :Warrior(number,lifeValue,commandName)
         ,_weaponsOne(number%3)
         ,_weaponsTwo((number+1)%3)
    {NinjaNumber++;}

    void show(){
        Clock();
        cout<<" "<<getCommandName().getcommandName()<<" ninja "<<getNumber()<<" born with strength "<<getlifeValue();
        cout<<" ,"<<NinjaNumber<<" ninja "<<" in "<<getCommandName().getcommandName()<<" headquarter"<<endl;
        cout<<"It's has a ";
        showWeapons(_weaponsOne);
        cout<<" and ";
        showWeapons(_weaponsTwo);
        cout<<endl;
    }
private:
    static int NinjaNumber;
    int _weaponsOne;
    int _weaponsTwo;
};
int Ninja::NinjaNumber=0;

class Iceman
:public Warrior
{
public:
    Iceman(const int number,const int lifeValue,Command & commandName)
        :Warrior(number,lifeValue,commandName)
         ,_weapons(number%3)
    {IcemanNumber++;}

    void show(){
        Clock();
        cout<<" "<<getCommandName().getcommandName()<<" iceman "<<getNumber()<<" born with strength "<<getlifeValue();
        cout<<" ,"<<IcemanNumber<<" iceman "<<" in "<<getCommandName().getcommandName()<<" headquarter"<<endl;
        cout<<"It's has a ";
        showWeapons(_weapons);
        cout<<endl;
    }
private:
    static int IcemanNumber;
    int _weapons;
};
int Iceman::IcemanNumber=0;

class Lion
:public Warrior
{
public:
    Lion(const int number,const int lifeValue,Command & commandName)
        :Warrior(number,lifeValue,commandName)
         ,_loyalty(getCommandName().getCommandLifeValue())
    {LionNumber++;}

    void show(){
        Clock();
        cout<<" "<<getCommandName().getcommandName()<<" lion "<<getNumber()<<" born with strength "<<getlifeValue();
        cout<<" ,"<<LionNumber<<" lion "<<" in "<<getCommandName().getcommandName()<<" headquarter"<<endl;
        cout<<"It's loyalty is "<<_loyalty<<endl;
    }
private:
    static int LionNumber;
    int _loyalty;
};
int Lion::LionNumber=0;

class Wolf
:public Warrior
{
public:
    Wolf(const int number,const int lifeValue,Command & commandName)
        :Warrior(number,lifeValue,commandName)
    {WolfNumber++;}
    void show(){
        Clock();
        cout<<" "<<getCommandName().getcommandName()<<" Wolf "<<getNumber()<<" born with strength "<<getlifeValue();
        cout<<" ,"<<WolfNumber<<" Wolf "<<" in "<<getCommandName().getcommandName()<<" headquarter"<<endl;
    }
private:
    static int WolfNumber;
};
int Wolf::WolfNumber=0;

int main()
{   
    int health;
    int numberBlue=1;
    int numberRed=1;
    std::cin>>health;
    int d,i,l,n,w;
    int x=0,y=0;
    std::cin>>d>>n>>i>>l>>w;
    Command red("red",health);
    Command blue("blue",health);
    if(fork()==0){
        int tag=0;
        while(1){
            if(tag==5){
                break;
            }
            x=x%5;
            switch(x){
            case 0:{
                       if(red.getCommandLifeValue()>=i){
                           Iceman x(numberRed,i,red);
                           x.show();
                           tag=0;
                       }else{
                           tag++;   
                       }
                   }
                   break;
            case 1:{
                       if(red.getCommandLifeValue()>=l){
                           Lion x(numberRed,l,red);
                           x.show();
                           tag=0;
                       }else{
                           tag++;
                       }
                   }
                   break;
            case 2:{
                       if(red.getCommandLifeValue()>=w){
                           Wolf x(numberRed,w,red);
                           x.show();
                           tag=0;
                       }else{
                           tag++;
                       }
                   }
                   break;
            case 3:{
                       if(red.getCommandLifeValue()>=n){
                           Ninja x(numberRed,n,red);
                           x.show();
                           tag=0;
                       }else{
                           tag++;
                       }
                   }
                   break;
            case 4:{
                       if(red.getCommandLifeValue()>=d){
                           Dragon x(numberRed,d,red);
                           x.show();
                           tag=0;
                       }else{
                           tag++;
                       }
                   }
                   break;
            }
            numberRed++;
            x++;
        }
        Clock();
        cout<<" red headquarter stop making warrior"<<endl;
        exit(0);
    }else{
        int tag1=0;
        while(1){
            if(tag1==5){
                break;
            }
            y=y%5;
            switch(y){
            case 0:{
                       if(blue.getCommandLifeValue()>=l){
                           Lion y(numberBlue,l,blue);
                           y.show();
                           tag1=0;
                       }else{
                           tag1++;   
                       }
                   }
                   break;
            case 1:{
                       if(blue.getCommandLifeValue()>=d){
                           Dragon y(numberBlue,d,blue);
                           y.show();
                           tag1=0;
                       }else{
                           tag1++;
                       }
                   }
                   break;
            case 2:{
                       if(blue.getCommandLifeValue()>=n){
                           Ninja y(numberBlue,n,blue);
                           y.show();
                           tag1=0;
                       }else{
                           tag1++;
                       }
                   }
                   break;
            case 3:{
                       if(blue.getCommandLifeValue()>=i){
                           Iceman y(numberBlue,i,blue);
                           y.show();
                           tag1=0;
                       }else{
                           tag1++;
                       }
                   }
                   break;
            case 4:{
                       if(blue.getCommandLifeValue()>=w){
                           Wolf y(numberBlue,w,blue);
                           y.show();
                           tag1=0;
                       }else{
                           tag1++;
                       }
                   }
                   break;
            }
            numberBlue++;
            y++;
        }
        Clock();
        cout<<" blue headquarter stop making warrior"<<endl;
        wait(NULL);
    }
    return 0;
}
