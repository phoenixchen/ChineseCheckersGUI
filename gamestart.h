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

#define WINDOW_NAME "中國跳棋對戰程式"

class GameStart {

public:
	GameStart();

void DrawLineCircle(cv::Mat* frame,cv::Mat* BG,char * chess,Data coordinate);

void DrawControlComponent(cv::Mat* frame,int* thinkingtime,bool* MCTScheck,bool *RuleBasecheck, \
                          bool *NeuralNetworkcheck,int *turncount,int *undoturn);

#ifdef WIN32
void WinINITServer(SOCKET *sServer,int max_clients,SOCKET client_socket[]);
SOCKET WinConnectClient(SOCKET *sServer,int max_clients,SOCKET client_socket[],int *socket_order_with_array);
#endif

#ifdef __linux__
void LinINITServer(int * sServer);
int LinConnectClient(int * sServer);
#endif


bool printUI(char *chess,int thinkingtime,bool MCTScheck,bool RuleBasecheck,bool NeuralNetworkcheck,cv::Mat* frame,cv::Mat* BG,int PlayWithHuman,int playercount);
};
