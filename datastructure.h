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

#include <opencv2/opencv.hpp>

class Data {
public:
    int x[256];
    int y[256];

    void GUItoCMD();
};

struct multijump{
    char node;
    struct multijump * next;
};

void initchess1v1(char * chess) ;
void initchess1v1v1(char * chess) ;
void initchessTEST1v1(char * chess);
void initchessTEST1v1v1(char * chess);
int locatetransform(char locate);
char locatetransformrevers(int locate);


void MouseClickAction(cv::Point mouse,bool *IsMouseClick,bool *InvalidTo,bool *InvalidFrom,bool *jumpfinish, \
                      int *mouseclickchess,Data coordinate,char *chess,struct multijump ** head, \
                      struct multijump ** prev,struct multijump ** current,char *GUIfrom,bool *movefinish,bool *JumpNeedUpdate);

void GUIJumpUpdate(bool *movefinish,bool *JumpNeedUpdate,char *chess,struct multijump ** prev, \
                   struct multijump ** current,char *GUIfrom);

void GUISendString(char * GUIfrom,struct multijump ** current,struct multijump ** head,SOCKET sClient);

bool AISendString(char * AIfrom,struct multijump ** current,struct multijump ** head, \
                  struct multijump ** prev,char *chess,int max_clients,SOCKET client_socket[],int chesscolor);

SOCKET AutoSelect(int max_clients,SOCKET client_socket[]);

void TurnOrderSort(int max_clients,int socket_order_with_array,int order[]);

void AIAfterSendStringINIT(char * AIfrom,struct multijump ** current,struct multijump ** head,struct multijump ** prev);

void FirstSendStandby(int max_clients,SOCKET client_socket[],int order[],int PlayWithHuman,int playercount);
