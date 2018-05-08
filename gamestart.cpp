#include "cvui.h"
#include "DataStructure.h"
#include "gamestart.h"

#ifdef WIN32
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#endif

#ifdef __linux__
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

GameStart::GameStart(){
}

bool GameStart::printUI(char *chess,int thinkingtime,bool MCTScheck,bool RuleBasecheck,bool NeuralNetworkcheck,cv::Mat* frame,cv::Mat* BG,int PlayWithHuman,int playercount){

    cv::Point mouse;

    Data coordinate;
    coordinate.GUItoCMD();

    char AIfrom = -127;
    char GUIfrom = -127;
    struct multijump * current = NULL;
    struct multijump * prev = NULL;
    struct multijump * head = NULL;
    bool IsMouseClick = false;

    int LinuxRenderTimes = 1;

    bool IsFirstView = true;

    bool InvalidTo = false;
    bool InvalidFrom = false;
    int mouseclickchess = -1;
    bool jumpfinish = false;
    bool movefinish = false;
    bool JumpNeedUpdate = false;

    int turncount = 1;

    #ifdef WIN32

    if(playercount==2)
        initchessTEST1v1(chess);
    if(playercount==3)
        initchessTEST1v1v1(chess);

    int socket_order_with_array = 0;
    int max_clients = 6;
    SOCKET sServer,sClient,client_socket[max_clients];

    WinINITServer(&sServer,max_clients,client_socket);

    int order[max_clients];
    for(int i=0;i<max_clients;i++)
        order[i] = 0;

    if(PlayWithHuman !=0)
        order[(PlayWithHuman-1)] = -1;

    sClient = NULL;
    while(sClient==NULL){
        sClient = WinConnectClient(&sServer,max_clients,client_socket,&socket_order_with_array);
    };
    TurnOrderSort(max_clients,socket_order_with_array,order);

    if(playercount == 2)
        if(PlayWithHuman ==0){
            sClient = NULL;
            while(sClient==NULL){
                sClient = WinConnectClient(&sServer,max_clients,client_socket,&socket_order_with_array);
            };
            TurnOrderSort(max_clients,socket_order_with_array,order);
        }

    if(playercount == 3){
        sClient = NULL;
        while(sClient==NULL){
            sClient = WinConnectClient(&sServer,max_clients,client_socket,&socket_order_with_array);
        };
        TurnOrderSort(max_clients,socket_order_with_array,order);
        if(PlayWithHuman ==0){
            sClient = NULL;
            while(sClient==NULL){
                sClient = WinConnectClient(&sServer,max_clients,client_socket,&socket_order_with_array);
            };
            TurnOrderSort(max_clients,socket_order_with_array,order);
        }
    }

    FirstSendStandby(max_clients,client_socket,order,PlayWithHuman,playercount);

    #endif

    #ifdef __linux__
        int sServer;
        int sClient1;
        int sClient2;
        int sClient3;
        LinINITSocket(&sServer);
        sClient1 = LinConnectClient(&sServer);
    if(playercount ==2)
        if(PlayWithHuman ==0)
            sClient2 = LinConnectClient(&sServer);
    if(playercount ==3){
        sClient2 = LinConnectClient(&sServer);
        if(PlayWithHuman ==0)
            sClient3 = LinConnectClient(&sServer);
    }
    #endif

int turn =0;
int undoturn=0;

	while (true){

        DrawLineCircle(frame,BG,chess,coordinate);

        if (cvui::mouse(cvui::CLICK)) {
            IsFirstView = false;
			mouse.x = cvui::mouse().x;
			mouse.y = cvui::mouse().y;
			IsMouseClick = true;
		}

        if(!IsFirstView)
            if(mouseclickchess!= -1)
                cvui::printf(*frame, 175, 80, 0.4, 0xff0000, "mouse = (%d,%d) ; (%d)=> (%d,%d)", \
                mouse.x,mouse.y,locatetransformrevers(mouseclickchess),coordinate.x[mouseclickchess],coordinate.y[mouseclickchess]);


        if(IsMouseClick)
            MouseClickAction(mouse,&IsMouseClick,&InvalidTo,&InvalidFrom,&jumpfinish,&mouseclickchess,coordinate,chess, \
                             &head,&prev,&current,&GUIfrom,&movefinish,&JumpNeedUpdate);

        DrawControlComponent(frame,&thinkingtime,&MCTScheck,&RuleBasecheck,&NeuralNetworkcheck,&turncount,&undoturn);

        if(InvalidFrom == true)
            cvui::printf(*frame, 175, 60, 0.4, 0xff0000, "Invalid StartingPoint");
        if(InvalidTo == true)
            cvui::printf(*frame, 175, 60, 0.4, 0xff0000, "Invalid destination");

		if (cvui::button(*frame, 1100 , 10 ,50, 50, "&Quit")) {
		    break;
		}

/**************************************************************/

        GUIJumpUpdate(&movefinish,&JumpNeedUpdate,chess,&prev,&current,&GUIfrom);

        cvui::update();
		cvui::imshow(WINDOW_NAME, *frame);
        if (cv::waitKey(20) == 27)
			return true;

        LinuxRenderTimes++;

        if(LinuxRenderTimes>1000)
            LinuxRenderTimes = 10;

        if(LinuxRenderTimes >5){

            if(order[turn]==-1){
                if(GUIfrom != -127 && head != NULL)
                    if( movefinish == true || jumpfinish == true ){
                        if(jumpfinish && GUIfrom == prev->node){//�_�l�I�P�����I�ۦP�A���X�k���B
                            jumpfinish = false;
                            InvalidTo = true;
                            continue;
                        }

                        for(int j=0;j<max_clients;j++){
                            if(client_socket[j]!=0)
                                GUISendString(&GUIfrom,&current,&head,client_socket[j]);
                        }
                        turncount++;
                        turn++;
                    }
            }
            if(order[turn]==0){
                //do nothing
                turn++;
            }
            if(order[turn]!=-1 && order[turn]!=0){
                if(!AISendString(&AIfrom,&current,&head,&prev,chess,max_clients,client_socket,(order[turn]-1)+2))
                    return true;
                for(int j=0;j<max_clients;j++){
                    if(client_socket[j]!=0 && j!=(order[turn]-1))
                        GUISendString(&AIfrom,&current,&head,client_socket[j]);
                }
                AIAfterSendStringINIT(&AIfrom,&current,&head,&prev);
                turncount++;
                turn++;
            }

            if(turn==6)
                turn = 0;
        }


        if( jumpfinish || movefinish ){

            current = head;
            while(current!=NULL){
                prev = current;
                current = current->next;
                free(prev);
            }
            GUIfrom = -127;
            current = NULL;
            head = NULL;
            prev = NULL;
            jumpfinish = false;
            movefinish = false;
        }


	}

#ifdef WIN32
    closesocket(sServer);
    WSACleanup();
#endif

#ifdef __linux__
    close(sClient1);
    close(sServer);
#endif

}

void GameStart::DrawLineCircle(cv::Mat* frame,cv::Mat* BG,char * chess,Data coordinate){
        int x0,y0,x1,y1;

		*frame = (*BG).clone();

        //���e���T����(��)�������u�]�ѤW��U�^
        //�C�Ӥp�T���Ϊ��������40
        //�C�Ӥp�T���Ϊ�������30 ���Ӥj��35
        x0 = 290;
        y0 = 140;
        x1 = 330;
        y1 = 140;
        for(int row=1;row<13;row++){
            cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ));
            x0=x0-20;
            x1=x1+20;
            y0=y0+30;
            y1=y1+30;
        }

        //�e�ˤT�����k�W�쥪�U���׽u�]�ѥ��W��k�U�^
        x0=110;
        y0=230;
        x1=90;
        y1=260;
        for(int row=1;row<13;row++){
            cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ));
            x0=x0+40;
      		x1=x1+20;
      		y1=y1+30;
        }


        //�e�ˤT�������W��k�U���׽u�]�ѥk�W�쥪�U�^
        x0=510;
        y0=230;
        x1=530;
        y1=260;
        for(int row=1;row<13;row++){
            cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ));
            x0=x0-40;
            x1=x1-20;
            y1=y1+30;
        }


        //�e���T�������U��k�W���׽u�]�ѥk�U�쥪�W�^
        x0=510;
        y0=470;
        x1=530;
        y1=440;

        for(int row=1;row<13;row++){
            cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ));
            x0=x0-40;
            x1=x1-20;
            y1=y1-30;
        }

        //�e���T�����k�U�쥪�W���׽u�]���U��k�W�^
        x0=110;
        y0=470;
        x1=90;
        y1=440;
        for(int row=1;row<13;row++){
            cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ));
            x0=x0+40;
            x1=x1+20;
            y1=y1-30;
        }


        //�e�ˤT���Ϊ������u�]�ѤU��W�^
        x0=290;
        y0=560;
        x1=330;
        y1=560;
        for(int row=1;row<13;row++){
            cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ));
            x0=x0-20;
            x1=x1+20;
            y0=y0-30;
            y1=y1-30;
        }


        //�}�l�e���
        for(int i=0;i<256;i++){
            if(chess[i]!=-1 && chess[i]!=0)
                switch(chess[i]){
                    case 1:
                    cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),10,cv::Scalar( 0, 0, 255 ),-1,1 );break;
                    case 2:
                    cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),10,cv::Scalar( 0, 165, 255 ),-1,1 );break;
                    case 3:
                    cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),10,cv::Scalar( 0, 255, 0 ),-1,1 );break;
                }
        }

}

void GameStart::DrawControlComponent(cv::Mat* frame,int* thinkingtime,bool* MCTScheck,bool *RuleBasecheck, \
                          bool *NeuralNetworkcheck,int *turncount,int *undoturn){

        int playercount = 2;

        if (cvui::button(*frame, 600 , 10 ,50, 50, "Undo")) {
		}

        cvui::window(*frame, 670, 10, 400, 50, "notice:");
        cvui::rect(*frame, 671, 31 , 398, 28, 0xff0000);
		cvui::text(*frame, 680 , 35, "Undo can only use one time every step.", 0.5);

        cvui::printf(*frame , 20, 35, 0.6, 0xff0000, "ThinkingTime");
        cvui::printf(*frame , 80, 55, 0.4, 0xff0000, "(second)");
        cvui::trackbar(*frame , 150, 20, 400 ,thinkingtime, 10, 30);

        cvui::counter(*frame, 560, 80, undoturn);

        if(*undoturn > (*turncount)-1)
            *undoturn = (*turncount)-1;
        if(*undoturn < 0)
            *undoturn = 0;

        cvui::rect(*frame, 670, 78 , 400, 20,0x0000ff, 0x2f2f2f);
        cvui::checkbox(*frame, 900, 80, "Neural Network", NeuralNetworkcheck);
		cvui::checkbox(*frame, 800, 80, "Rule Base", RuleBasecheck);
		cvui::checkbox(*frame, 700, 80, "Monti Carlo", MCTScheck);

        cvui::printf(*frame, (*frame).cols - 140, (*frame).rows - 20, 0.4, 0xCECECE, "Made by Phoenix");
}

#ifdef WIN32
void GameStart::WinINITServer(SOCKET *sServer,int max_clients,SOCKET client_socket[]){

    WSADATA wsa;
    struct sockaddr_in server;

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    if((*sServer = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET){
        printf("Could not create socket : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 894 );

    if( bind(*sServer ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    listen(*sServer , 3);

    for(int i = 0 ; i < max_clients;i++)
        client_socket[i] = 0;

}


SOCKET GameStart::WinConnectClient(SOCKET *sServer,int max_clients,SOCKET client_socket[],int *socket_order_with_array){

    printf("���ݳs��...\n");

    int tempint;
    fd_set readfds;
    SOCKET sClient = NULL;
    struct sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);

    FD_ZERO(&readfds);
    FD_SET(*sServer, &readfds);

    for (int i =0;i<max_clients;i++){
        sClient = client_socket[i];
        if(sClient > 0)
            FD_SET(sClient,&readfds);
    }

    tempint = select(0,&readfds,NULL,NULL,NULL);

    if (tempint == SOCKET_ERROR){
        printf("select call failed with error code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    if (FD_ISSET(*sServer,&readfds)){
        if ((sClient = accept(*sServer , (struct sockaddr *)&remoteAddr, (int *)&nAddrlen))<0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("������@�ӳs���Gsocket_fd:%d ,ip %s:%d\n",sClient,inet_ntoa(remoteAddr.sin_addr),ntohs(remoteAddr.sin_port));

        for (*socket_order_with_array = 0; *socket_order_with_array < max_clients; (*socket_order_with_array)++){
            if (client_socket[*socket_order_with_array] == 0){
                client_socket[*socket_order_with_array] = sClient;
                break;
            }
        }
    }

    return sClient;
}
#endif

#ifdef __linux__
void GameStart::LinINITServer(int * sServer){

    struct sockaddr_in my_addr;   //�A�Ⱦ������a�}���p��
    memset(&my_addr,0,sizeof(my_addr)); //�ƾڪ�l��--�M�s
    my_addr.sin_family=AF_INET; //�]�m��IP�q�H
    my_addr.sin_addr.s_addr=INADDR_ANY;//�A�Ⱦ�IP�a�}--���\�s����Ҧ����a�a�}�W
    my_addr.sin_port=htons(894); //�A�Ⱦ��ݤf��

            /*�ЫتA�Ⱦ��ݮM���r--IPv4��ĳ�A���V�s���q�H�ATCP��ĳ*/
        if((*sServer=socket(PF_INET,SOCK_STREAM,0))<0)
        {
            perror("socket");
            //return 1;
        }

            /*�N�M���r�j�w��A�Ⱦ��������a�}�W*/
        if (bind(*sServer,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
        {
            perror("bind");
            //return 1;
        }

        /*��ť�s���ШD--��ť���C���׬�3*/
        listen(*sServer,3);

}

int GameStart::LinConnectClient(int * sServer){

    struct sockaddr_in remote_addr; //�Ȥ�ݺ����a�}���p��
    socklen_t sin_size;
    int len;
    int sClient;//�Ȥ�ݮM���r

        sin_size=sizeof(struct sockaddr_in);

        printf("���ݳs��...\n");

        /*���ݫȤ�ݳs���ШD��F*/
        if((sClient=accept(*sServer,(struct sockaddr *)&remote_addr,&sin_size))<0)
        {
            perror("accept");
            return 1;
        }
        printf("������@�ӳs���G%s\n",inet_ntoa(remote_addr.sin_addr));

    rutern sClient;
}
#endif
