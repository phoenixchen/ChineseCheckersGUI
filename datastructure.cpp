#include "DataStructure.h";
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <sstream>

void initchess1v1(char * chess) {

    int i = 0;
	for (i = 0; i < 256; i++) {
		chess[i] = 0;
	}

	char wall[26] = { 5,15,22,25,29,35,36,43,50,52,67,69,84,85,86,92,95,99,101,103,105,106,113,115,118,125 };
	for (i = 0; i < 26; i++) {
		chess[wall[i]] = -1;
		chess[(wall[i]+128)] = -1;		//正的為該值+128，負的為該值取絕對值
	}

	char init1v1[10] = {75,65,55,45,82,72,62,89,79,96};
    for (i = 0; i < 10; i++) {
		chess[init1v1[i]] = 1;
		chess[(init1v1[i]+128)] = 2;		//正的為該值+128，負的為該值取絕對值
	}

}

void initchess1v1v1(char * chess) {

    int i = 0;
	for (i = 0; i < 256; i++) {
		chess[i] = 0;
	}

	char wall[26] = { 5,15,22,25,29,35,36,43,50,52,67,69,84,85,86,92,95,99,101,103,105,106,113,115,118,125 };
	for (i = 0; i < 26; i++) {
		chess[wall[i]] = -1;
		chess[(wall[i]+128)] = -1;		//正的為該值+128，負的為該值取絕對值
	}

	char init1v1v1[30] = {-75,-65,-55,-45,-82,-72,-62,-89,-79,-96,-12,-2,8, \
	18,-19,-9,1,-26,-16,-33,78,88,98,108,71,81,91,64,74,57};
    for (i = 0; i < 10; i++) {
        chess[locatetransform(init1v1v1[i])] = 1;
	}
    for (i = 10; i < 20; i++) {
        chess[locatetransform(init1v1v1[i])] = 2;
	}
    for (i = 20; i < 30; i++) {
        chess[locatetransform(init1v1v1[i])] = 3;
	}

}

void initchessTEST1v1(char * chess) {

    int i = 0;
	for (i = 0; i < 256; i++) {
		chess[i] = 0;
	}

	char wall[26] = { 5,15,22,25,29,35,36,43,50,52,67,69,84,85,86,92,95,99,101,103,105,106,113,115,118,125 };
	for (i = 0; i < 26; i++) {
		chess[wall[i]] = -1;
		chess[(wall[i]+128)] = -1;		//正的為該值+128，負的為該值取絕對值
	}

	char init1v1v1[20] = {96,89,72,62,45,58,51,24,7,21, \
	-17,-14,-31,-41,-51,-58,-75,-55,-45,-89};
    for (i = 0; i < 10; i++) {
        chess[locatetransform(init1v1v1[i])] = 2;
	}
    for (i = 10; i < 20; i++) {
        chess[locatetransform(init1v1v1[i])] = 1;
	}

}


void initchessTEST1v1v1(char * chess) {

    int i = 0;
	for (i = 0; i < 256; i++) {
		chess[i] = 0;
	}

	char wall[26] = { 5,15,22,25,29,35,36,43,50,52,67,69,84,85,86,92,95,99,101,103,105,106,113,115,118,125 };
	for (i = 0; i < 26; i++) {
		chess[wall[i]] = -1;
		chess[(wall[i]+128)] = -1;		//正的為該值+128，負的為該值取絕對值
	}

	char init1v1v1[30] = {-33,-16,-9,-6,11,4,28,38,14,7, \
	-75,-65,-72,-38,-41,-24,-14,-17,0,34   ,17,27,44,54,61,68,78,81,40,23};
    for (i = 0; i < 10; i++) {
        chess[locatetransform(init1v1v1[i])] = 2;
	}
    for (i = 10; i < 20; i++) {
        chess[locatetransform(init1v1v1[i])] = 1;
	}
	for (i = 20; i < 30; i++) {
        chess[locatetransform(init1v1v1[i])] = 3;
	}
}


void Data::GUItoCMD(){

    for(int i=0;i<255;i++){
        x[i] = -1;
        y[i] = -1;
    }

    int tmpointx = 310;
    int tmpointy = 110;
    int tmpchar= 96;

    for(int i=1;i<=13;i++){
        for(int j=1;j<=i;j++){
            x[locatetransform(tmpchar)]=tmpointx;
            y[locatetransform(tmpchar)]=tmpointy;
            tmpchar = tmpchar + 10;
            tmpointx = tmpointx + 40;
        }
        tmpchar = tmpchar -10 -7 - i*10;
        tmpointx = tmpointx -40 - (i-1)*40 -20;
        tmpointy = tmpointy + 30;
    }

    tmpointx = 310;
    tmpointy = 590;
    tmpchar = -96;
    for(int i=1;i<=13;i++){
        for(int j=1;j<=i;j++){
            x[locatetransform(tmpchar)]=tmpointx;
            y[locatetransform(tmpchar)]=tmpointy;
            tmpchar = tmpchar + 10;
            tmpointx = tmpointx + 40;
        }
        tmpchar = tmpchar -10 + 17 - i*10;
        tmpointx = tmpointx -40 - (i-1)*40 -20;
        tmpointy = tmpointy -30;
    }

}

int locatetransform(char locate) {

    int after = 0;
	if (locate > 0)
		after = locate + 128;
	if (locate <= 0)
		after = abs(locate);
	return after;
}

char locatetransformrevers(int locate){

    int before = 0;
	if (locate > 128)
		before = locate - 128;
	if (locate <= 128)
		before = 0 - locate;
	return before;
}


void MouseClickAction(cv::Point mouse,bool *IsMouseClick,bool *InvalidTo,bool *InvalidFrom,bool *jumpfinish, \
                      int *mouseclickchess,Data coordinate,char *chess,struct multijump ** head, \
                      struct multijump ** prev,struct multijump ** current,char *GUIfrom,bool *movefinish,bool *JumpNeedUpdate){

    char temp;

    *mouseclickchess = -1;

    for(int i=0;i<256;i++){
        if(abs(coordinate.x[i]-mouse.x)<10 && abs(coordinate.y[i]-mouse.y)<10 )
           if(sqrt(pow((coordinate.x[i]-mouse.x),2)+pow((coordinate.y[i]-mouse.y),2))<=10){

                *mouseclickchess = i;

                if(*prev != NULL)
                    if((*prev)->node == locatetransformrevers(i)){
                        *IsMouseClick = false;
                        *InvalidTo = false;
                        *jumpfinish = true;
                        break;
                    }

                if(*GUIfrom == -127){
                    if(chess[i]==1){    /*如果是自己的棋子*/
                        *GUIfrom = locatetransformrevers(i);
                        *IsMouseClick = false;
                        *InvalidFrom = false;
                    }
                    else{
                        *InvalidFrom = true;
                    }
                }
                else{
                    if(*current == NULL){

                        if(abs(locatetransformrevers(i) - *GUIfrom)==17 | abs(locatetransformrevers(i) - *GUIfrom)==10 \
                           | abs(locatetransformrevers(i) - *GUIfrom)==7){
                            if(chess[i]==0){
                                *current = (struct multijump *)malloc(sizeof(struct multijump));
                                if(*head == NULL)
                                    *head = *current;
                                (*current)->node = locatetransformrevers(i);
                                (*current)->next = NULL;
                                *IsMouseClick = false;
                                *InvalidTo = false;
                                *movefinish = true;
                            }
                            else{
                                *InvalidTo = true;
                            }
                        }
                        else{
                            *InvalidTo = true;
                        }

                        if(*InvalidTo){

                            if(*prev==NULL)
                                temp = *GUIfrom;
                            else
                                temp = (*prev)->node;

                            //若跳躍的間格正確
                            if(abs(locatetransformrevers(i) - temp)==34 | abs(locatetransformrevers(i) - temp)==20 \
                               | abs(locatetransformrevers(i) - temp)==14){
                                //若有旁邊有人可以當跳板
                                if((chess[locatetransform(temp + (locatetransformrevers(i) - temp)/2)] == 1) || \
                                   (chess[locatetransform(temp + (locatetransformrevers(i) - temp)/2)] == 2) ||
                                   (chess[locatetransform(temp + (locatetransformrevers(i) - temp)/2)] == 3)){
                                        //若跳躍的目的地沒有其他人
                                        if(chess[i] == 0){
                                            *current = (struct multijump *)malloc(sizeof(struct multijump));

                                            if(*head == NULL)
                                                *head = *current;

                                            if(*prev!=NULL)
                                                (*prev)->next = *current;

                                            (*current)->node = locatetransformrevers(i);
                                            (*current)->next = NULL;
                                            *IsMouseClick = false;
                                            *InvalidTo = false;
                                            *JumpNeedUpdate = true;
                                        }
                                        else{
                                            *InvalidTo = true;
                                        }
                                }
                                else{
                                    *InvalidTo = true;
                                }
                            }
                            else{
                                *InvalidTo = true;
                            }
                        }




                    }
                }
           }
    }

}


void GUIJumpUpdate(bool *movefinish,bool *JumpNeedUpdate,char *chess,struct multijump ** prev, \
                   struct multijump ** current,char *GUIfrom){

    char temp;

    if(*movefinish){
        temp = chess[locatetransform(*GUIfrom)];
        chess[locatetransform(*GUIfrom)] = 0;
        chess[locatetransform((*current)->node)] = temp;
        *prev = *current;
        *current = (*current)->next;
    }
    if(*JumpNeedUpdate){       //每次jump都更新，包含jumpfinish時

        if(*prev == NULL){
            temp = chess[locatetransform(*GUIfrom)];
            chess[locatetransform(*GUIfrom)] = 0;
            chess[locatetransform((*current)->node)] = temp;
            *prev = *current;
            *current = (*current)->next;
        }
        else{
            temp = chess[locatetransform((*prev)->node)];
            chess[locatetransform((*prev)->node)] = 0;
            chess[locatetransform((*current)->node)] = temp;
            *prev = *current;
            *current = (*current)->next;
        }
        *JumpNeedUpdate = false;
    }
}


void GUISendString(char * GUIfrom,struct multijump ** current,struct multijump ** head,SOCKET sClient){

    //發送資料
    char * sendData;
    int i = *GUIfrom;
    std::stringstream stringfrom;
    std::stringstream stringto;
    std::string stringfinal;
    stringfrom << i;
    stringfinal = stringfrom.str() + ",";

    *current = *head;

    while(*current!=NULL){
        i = (*current)->node;
        stringto << i;
        stringfinal = stringfinal + stringto.str();
        stringto.str("");
        if((*current)->next!=NULL)
            stringfinal = stringfinal + ",";
        *current = (*current)->next;
    }

    sendData = new char[stringfinal.length() + 1];
    strcpy(sendData, stringfinal.c_str());
    send(sClient,sendData,strlen(sendData),0);
}


bool AISendString(char * AIfrom,struct multijump ** current,struct multijump ** head, \
                  struct multijump ** prev,char *chess,int max_clients,SOCKET client_socket[],int chesscolor){

    bool IsDigital = true;
    int CheckAscii;

    char *token = ",";
    char *stringtok;
    char buf[255];
    bool AIInvalidFlag = false;

    //接收資料

    int len = recv(AutoSelect(max_clients,client_socket),buf,255,0);
    buf[len] = '\0';

    if(len > 0)
    {
        for(int i=0;buf[i]!='\0';i++){

            CheckAscii = buf[i];

            if( (CheckAscii < 48) || (CheckAscii > 57) )
              IsDigital = false;

            if(CheckAscii == '-' || CheckAscii == ',')
                IsDigital = true;

            if(!IsDigital)
                return false;
        }

        if(!IsDigital){
            printf("輸入錯誤，程式結束\n");
            return false;
        }

        stringtok = strtok(buf,token);

        *head = NULL;
        *prev = NULL;
        *current = NULL;
        char temp;

        while(stringtok!= NULL){

            if(*AIfrom== -127){
                *AIfrom = (char)atoi(stringtok);
                if(chess[locatetransform(*AIfrom)]!=chesscolor){
                    printf("起始點並非可操作的棋子，程式結束\n");
                    AIInvalidFlag = true;
                    return false;
                }
            }
            else{

                *current = (struct multijump *)malloc(sizeof(struct multijump));

                if( *head==NULL ){
                    *head = *current;
                }

                if(*prev!=NULL)
                    (*prev)->next = *current;

                (*current)->node = (char)atoi(stringtok);
                (*current)->next = NULL;
                *prev = *current;
                *current = (*current)->next;
            }

            stringtok = strtok(NULL, token);
        }

        if(AIInvalidFlag == true)
            return false;

        if( (*prev)->node == *AIfrom ){
            printf("走步頭尾相同，程式結束\n");
            return false;
        }

        *current = *head;
        int length = 0;

        while( *current!=NULL ){
            length++;
            *current = (*current)->next;
        }

        *current = *head;

        if(length==1 && (abs(*AIfrom - (*current)->node)<14 || abs(*AIfrom - (*current)->node)==17)){
            *current = *head;

            if(abs(*AIfrom - (*current)->node)==17 | abs(*AIfrom - (*current)->node)==10 \
                       | abs(*AIfrom - (*current)->node)==7){
                        if(chess[locatetransform((*current)->node)]==0){
                            temp = chess[locatetransform(*AIfrom)];
                            chess[locatetransform(*AIfrom)] = 0;
                            chess[locatetransform((*current)->node)] = temp;
                        }
                        else{
                            printf("不合法走步(目的地已有其他棋子)，程式結束\n");
                            return false;
                        }
            }
            else{
                printf("不合法走步(跳躍的間格不正確)，程式結束\n");
                return false;
            }

        }
        else{
            *current = *head;

            if(*current!=NULL){
                if(abs(*AIfrom - (*current)->node)==34 | abs(*AIfrom - (*current)->node)==20 \
                           | abs(*AIfrom - (*current)->node)==14){
                    if((chess[locatetransform(*AIfrom + ((*current)->node - *AIfrom)/2)] == 1) || \
                       (chess[locatetransform(*AIfrom + ((*current)->node - *AIfrom)/2)] == 2) ||
                       (chess[locatetransform(*AIfrom + ((*current)->node - *AIfrom)/2)] == 3)){
                            if(chess[locatetransform((*current)->node)]==0){
                                temp = chess[locatetransform(*AIfrom)];
                                chess[locatetransform(*AIfrom)] = 0;
                                chess[locatetransform((*current)->node)] = temp;
                            }
                            else{
                                printf("不合法走步(目的地已有其他棋子)，程式結束\n");
                                return false;
                            }
                    }
                    else{
                        printf("不合法走步(旁邊沒有棋子可以當跳板)，程式結束\n");
                        return false;
                    }
                }
                else{
                    printf("不合法走步(跳躍的間格不正確)，程式結束\n");
                    return false;
                }
            }

            *prev = *current;
            *current = (*current)->next;

            while( *current!=NULL ){

                //若跳躍的間格正確
                if(abs((*prev)->node - (*current)->node)==34 | abs((*prev)->node - (*current)->node)==20 \
                   | abs((*prev)->node - (*current)->node)==14){
                    //若有旁邊有人可以當跳板
                    if((chess[locatetransform((*prev)->node + ((*current)->node - (*prev)->node)/2)] == 1) || \
                       (chess[locatetransform((*prev)->node + ((*current)->node - (*prev)->node)/2)] == 2) ||
                       (chess[locatetransform((*prev)->node + ((*current)->node - (*prev)->node)/2)] == 3)){
                            //若跳躍的目的地沒有其他人
                            if(chess[locatetransform((*current)->node)] == 0){
                                temp = chess[locatetransform((*prev)->node)];
                                chess[locatetransform((*prev)->node)] = 0;
                                chess[locatetransform((*current)->node)] = temp;
                            }
                            else{
                                AIInvalidFlag = true;
                                printf("不合法走步(目的地已有其他棋子)，程式結束\n");
                                return false;
                            }
                    }
                    else{
                        AIInvalidFlag = true;
                        printf("不合法走步(旁邊沒有棋子可以當跳板)，程式結束\n");
                        return false;
                    }
                }
                else{
                    AIInvalidFlag = true;
                    printf("不合法走步(跳躍的間格不正確)，程式結束\n");
                    return false;
                }

                *prev = *current;
                *current = (*current)->next;

            }

            if(AIInvalidFlag == true)
                return false;

        }
    }

    return true;
}

SOCKET AutoSelect(int max_clients,SOCKET client_socket[]){

    fd_set readfds;
    FD_ZERO(&readfds);
    SOCKET tempsocket;
    int tempint;
    for (int i=0;i<max_clients;i++){
        tempsocket =client_socket[i];
        if(tempsocket> 0)
            FD_SET(tempsocket,&readfds);
    }

/*****************************************************/
    tempint = select(0,&readfds,NULL,NULL,NULL);
/*****************************************************/

    if ( tempint == SOCKET_ERROR ){
        printf("select call failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);

    for(int i=0;i<max_clients;i++){

        tempsocket = client_socket[i];

        if (FD_ISSET(tempsocket,&readfds)){
            getpeername(tempsocket , (struct sockaddr*)&remoteAddr , (int*)&nAddrlen);
            return tempsocket;
        }
    }
    return NULL;
}

void TurnOrderSort(int max_clients,int socket_order_with_array,int order[]){

    for(int i=0;i<max_clients;i++){
        if(order[i]==0){
            order[i]=(socket_order_with_array+1);
            break;
        }
    }
}

void AIAfterSendStringINIT(char * AIfrom,struct multijump ** current,struct multijump ** head,struct multijump ** prev){

    *AIfrom = -127;

    *current = *head;
    while(*current!=NULL){
        *prev = *current;
        *current = (*current)->next;
        free(*prev);
    }
    *current = NULL;
    *head = NULL;
    *prev = NULL;
}

void FirstSendStandby(int max_clients,SOCKET client_socket[],int order[],int PlayWithHuman,int playercount){

    //發送資料
    char * sendData;
    std::stringstream stringcount;
    std::stringstream stringhuman;
    std::stringstream stringorder;
    std::string stringfinal;
    stringcount << playercount;
    stringhuman << PlayWithHuman;

    for(int i=0;i<max_clients;i++){
            if(order[i]!=0 && order[i]!=-1){
                stringorder << (i+1);
                stringfinal = stringcount.str() + "," +stringhuman.str() + "," +stringorder.str();
                stringorder.str("");
                sendData = new char[stringfinal.length() + 1];
                strcpy(sendData, stringfinal.c_str());
                send(client_socket[(order[i]-1)],sendData,strlen(sendData),0);
            }
    }
}
