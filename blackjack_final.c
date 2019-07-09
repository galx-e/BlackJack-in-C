#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

//function
void start();//enter the first setting(money,bet)(use one in start of the game)
void stadeck();//enter deck(52 cards)(use in beginig of the game)
void tor_bet();//let you choice how mach to bet
void tor_first();//make the firs move of the game
void add_first(char csuit[8],char rankk[6],int  value,int  id);//add card in first of the deck (in the end of the round)
void add_last(char csuit[8],char rankk[6],int  value,int  id);//add card in last of the deck (in the start of the game)
int value(char rankk[]);//get rankk return the value of single card
int randomcard();// return the id of card in random flace id the deck;
void move_to_player(int id);//move to *p to player
void move_to_dealer(int id);//move to *p to dealer
int valuehand(struct card* hand);//return the value of the hand you send
void return_to_deck();//return the dealer and player to the head of deck
void printhand(struct card* hand);
void game();

//global
char suit[4][8]={"spades","Hearts","Clubs","Diamond"};
char rankk[15][6]={"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","king"};
//////////////////////////////////////
int bet;
int cash;

struct card* deck=NULL;
struct card* hand_player=NULL;
struct card* hand_dealer=NULL;

struct card{
    char csuit[8];
    char rankk[6];
    int  value;
    int  id;
    struct card *next;
};

int main(){


    start();
    stadeck();
    game();

    free(deck);
    free(hand_dealer);
    free(hand_player);

return 0;
}

void start(){//enter the first setting(money,bet)(use one in start of the game)
    printf("start is rady\n");
    bet=0;
    cash=10000;
}

void stadeck(){//enter deck(52 cards)(use in beginig of the game)
    int s=0,r=0,id=1;    // s=suit,r=rankk
    for(s=0;s<4;s++)   //suit ...
        {
        for(r=0;r<13;r++) //rank...
            {
            add_last(suit[s],rankk[r],value(rankk[r]),id);
            id++;
            }
        }
     printf("deck is rady \n");
}

void add_first(char csuit[8],char rankk[6],int  value,int  id){//add card in first of the deck (in the end of the round)
    card *temp=NULL;
     if(deck==NULL) // if first is amptey
        {
        deck=(card*)malloc(sizeof(card));
        strcpy(deck->csuit,csuit);
        strcpy(deck->rankk,rankk);
        deck->value=value;
        deck->id=id;
        }

    else
        {
        temp=(card*)malloc(sizeof(card));
        strcpy(temp->csuit,csuit);
        strcpy(temp->rankk,rankk);
        temp->value=value;
        temp->id=id;
        temp->next=deck;
        deck=temp;
        }

}

void add_last(char csuit[8],char rankk[6],int  value,int  id){//add card in last of the deck (in the start of the game)
    card *temp=NULL;
    temp=deck;
    if(deck==NULL) // if first is amptey
        {
        deck=(card*)malloc(sizeof(card));
        strcpy(deck->csuit,csuit);
        strcpy(deck->rankk,rankk);
        deck->value=value;
        deck->id=id;
        }
    else
        {
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=(card*)malloc(sizeof(card));
        temp=temp->next;
        strcpy(temp->csuit,csuit);
        strcpy(temp->rankk,rankk);
        temp->value=value;
        temp->id=id;
        }

}

int value(char temp[]){//get rankk return the value of single card
    int i=0;
    for(i=0;i<10;i++)
        {
        if(temp==rankk[i])
            return i+1;
        }
    return 10;
}

void tor_bet(){//let you choice how mach to bet
    int temp,c=0;
    printf("you have %d\n",cash);

    while(1)
        {
        printf("how much do you wont to bet: ");
        scanf("%d",&temp);
        if(temp>cash)
            printf("enter again. you have only %d \n",cash);
        else if(temp%10!=0)
            printf("enter again.you can only enter bet that divided in 10 \n");
        else if(temp<=0)
            printf("more than 0 \n");
        else
            break;
        while((c =getchar() != '\n') && ( c!= EOF) );
        }
    bet=temp;
    cash=cash-bet;
}

void tor_first(){//make the firs move of the game
    int temp=0;
    temp=randomcard();
    move_to_dealer(temp);
    printf("value %d\n",valuehand(hand_player));
    printf("dealer--------------------------------------\n");
    //print_dealer();
    printhand(hand_dealer);
    printf("?????? of ???????\n");
    printf("value %d\n",valuehand(hand_dealer));

    temp=randomcard();
    move_to_player(temp);
    temp=randomcard();
    move_to_player(temp);
    printf("player-----------------------------------\n");
    //print_player();
    printhand(hand_player);
    printf("value %d\n",valuehand(hand_player));
}

int randomcard(){ // return the id of card in random flace id the deck;

    int i,a,sizeofdeck=0;
    srand(time(NULL));
    card *temp=NULL;
    temp=deck;
    while(temp->next!=NULL)
        {
        sizeofdeck++;
        temp=temp->next;
        }
    a=rand()%sizeofdeck;
    temp=deck;
    for(i=0;i<a;i++)
        temp=temp->next;
    a=temp->id;

    return a;
}

void move_to_player(int id){//move to *p to player
    card *temp=NULL;
    card *templayer=NULL;
    templayer=hand_player;
    temp=deck;
    if(temp->id==id) //if the first card was chose
        {
        if(templayer==NULL)
            {
            hand_player=temp;
            deck=deck->next;
            hand_player->next=NULL;
            }
        else
            {
            while(templayer->next!=NULL)
                templayer=templayer->next;
            templayer->next=temp;
            deck=temp->next;
            templayer->next->next=NULL;
            }
        }
    else//noramal case
        {
         while(temp->next->id!=id&&temp!=NULL)
            temp=temp->next;

        if(templayer==NULL)
            {
            hand_player=temp->next;
            temp->next=temp->next->next;
            hand_player->next=NULL;
            }
        else
            {
            while(templayer->next!=NULL)
                templayer=templayer->next;
            templayer->next=temp->next;
            temp->next=temp->next->next;
            templayer->next->next=NULL;
            }
        }
}

void move_to_dealer(int id){//move to *p to dealer
    card *temp=NULL;
    card *tempdealer=NULL;
    tempdealer=hand_dealer;
    temp=deck;
     if(temp->id==id) //if the first card was chose
        {
        if(tempdealer==NULL)
            {
            hand_dealer=temp;
            deck=deck->next;
            hand_dealer->next=NULL;
            }
        else
            {
            while(tempdealer->next!=NULL)
                tempdealer=tempdealer->next;
            tempdealer->next=temp;
            deck=temp->next;
            tempdealer->next->next=NULL;
            }
        }
    else//noramal case
        {
         while(temp->next->id!=id&&temp!=NULL)
            temp=temp->next;

        if(tempdealer==NULL)
            {
            hand_dealer=temp->next;
            temp->next=temp->next->next;
            hand_dealer->next=NULL;
            }
        else
            {
            while(tempdealer->next!=NULL)
                tempdealer=tempdealer->next;
            tempdealer->next=temp->next;
            temp->next=temp->next->next;
            tempdealer->next->next=NULL;
            }
        }
}

int valuehand(struct card* hand){ //return the value of the hand you send
    int val=0,ace=0;
    card *temp=NULL;
    temp=hand;
    while(temp!=NULL)
        {
        if(temp->id%13==1)
            ace=1;
        val=val+temp->value;
        temp=temp->next;
        }
    if(val<12&&ace==1)
        val=val+10;

    return val;
}

void return_to_deck(){ //return the dealer and player to the head of deck
    card *temp=NULL;
    temp=hand_player;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=deck;
    deck=hand_player;
    hand_player=NULL;
    temp=NULL;
    temp=hand_dealer;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=deck;
    deck=hand_dealer;
    hand_dealer=NULL;
}

void printhand(struct card* hand){
    card *temp=NULL;
    temp=hand;
    while(temp !=NULL)
        {
        //printf("%s of %s volue=%d id=%d",temp->csuit,temp->rankk,temp->value,temp->id);
        printf("%s of %s",temp->csuit,temp->rankk);
        printf("\n");
        temp=temp->next;
        }
        free(temp);
}


void game(){
    int burn=0,play=1,flag_bj=0;
    int sh=0,temp=0,c=0;

while(cash>10&&play==1)
        {
        burn=0;
        sh=0;
        tor_bet();  //2
        tor_first();  //3

        if(valuehand(hand_player)==21) {//if black jack in the first time
        cash=cash+(bet*2.5);
        bet=0;
        printf("BLACK JACK!!!!!");
        flag_bj=1;
        }

        while(valuehand(hand_player)<22&&flag_bj==0){ //4 stade hit&stand and burn player
            printf("hit or stand(hit=1,stand=2)\n");
            while(sh!=1&&sh!=2)
                {
                scanf("%d",&sh);
                printf("enter again \n");
                while((c =getchar() != '\n') && ( c!= EOF) );
                }

            if(sh==2)
                break;
            if(sh==1)
                {
                temp=randomcard();
                move_to_player(temp);
                printf("player cards\n");
                //print_player();
                printhand(hand_player);
                printf("!!!the valuo of the tor %d\n",valuehand(hand_player));
                }
            if(valuehand(hand_player)>21)
                {
                printf("burn you over 21\n");
                bet=0;
                burn=1;
                }
            sh=0;
            }

        if(burn==0){// 5 stade dealer moves

            while(valuehand(hand_dealer)<18){ //dealer take until he get 17
                temp=randomcard();
                move_to_dealer(temp);
                }

            printf("dealer card-------------------\n");
            //print_dealer();
            printhand(hand_dealer);
            printf("dealer value %d\n",valuehand(hand_dealer));

            if(valuehand(hand_dealer)>21){ // if dealer burn
                printf("the dealer burn\n");
                cash=cash+(bet*2);
                bet=0;
                }

            else if(valuehand(hand_dealer)==valuehand(hand_player)){ // if tie
                printf("tie\n");
                cash=cash+bet;
                bet=0;
                }

            else if(valuehand(hand_dealer)>valuehand(hand_player)){ // if dealer win
                printf("the dealer win\n");
                bet=0;
                }

            else if(valuehand(hand_dealer)<valuehand(hand_player)){//if player win
                printf("the player win\n");
                cash=cash+(bet*2);
                bet=0;
                }

            else { //else error
            printf("problem in stade 5");
            }
            }
        return_to_deck(); //return the dealer and player to the head of deck
        printf("do you wont to play again (1=yes,2=no) \n");
        scanf("%d",&play);
        }

}


//end

