#include <opencv2/opencv.hpp>
// One (and only one) of your C++ files must define CVUI_IMPLEMENTATION
// before the inclusion of cvui.h to ensure its implementaiton is compiled.
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "DataStructure.h"
#include "gamestart.h"
#define WINDOW_NAME "中國跳棋對戰程式"

#include <sstream>

void DrawControlComponent(cv::Mat* frame,int* thinkingtime,bool* MCTScheck, \
                          bool *RuleBasecheck,bool *NeuralNetworkcheck, \
                          int *playercount,cv::Mat *Hout,cv::Mat *Cout,int *PlayWithHuman,bool *GameStart);

int printUI(char * chess){

	cv::Mat frame = cv::Mat(675, 1200, CV_8UC3);
	cv::Mat BG = cv::imread("BG.png");

    cv::Mat mayoi = cv::imread("mayoi.png");
    cv::Mat imgMayoi(385, 315, CV_8UC3, cv::Scalar(0,0,0));
    imgMayoi = mayoi.clone();

    cv::Mat BubbleDialog = cv::imread("BubbleDialog.png");
    cv::Mat imgDialog(226, 137, CV_8UC3, cv::Scalar(0,0,0));
    imgDialog = BubbleDialog.clone();

    bool AIturn = true;

    int LinuxRenderTimes = 1;

	cvui::init(WINDOW_NAME);
    int thinkingtime = 15;
    bool MCTScheck = true;
    bool RuleBasecheck = false;
    bool NeuralNetworkcheck = false;
    int playercount = 2;
    int PlayWithHuman = 0;

    GameStart gamestart;

	cv::Mat Cout = cv::imread("./computer.png", cv::IMREAD_COLOR);
	cv::Mat Hout = cv::imread("./human.png", cv::IMREAD_COLOR);

    bool GameStart = false;
    bool GameFinish = false;
	while (true){

        frame = BG.clone();

        DrawControlComponent(&frame,&thinkingtime,&MCTScheck,&RuleBasecheck,&NeuralNetworkcheck, \
                             &playercount,&Hout,&Cout,&PlayWithHuman,&GameStart);

        for(int i=0;i<385;i++){
            for(int j=0;j<315;j++){

                if(imgMayoi.at<cv::Vec3b>(i,j)[0] ==255 && imgMayoi.at<cv::Vec3b>(i,j)[1] ==255 && imgMayoi.at<cv::Vec3b>(i,j)[2] ==255){
                }
                else
                    cv::circle( frame,cv::Point(150+j,200+i),0,cv::Scalar( imgMayoi.at<cv::Vec3b>(i,j)[0], \
                                                                          imgMayoi.at<cv::Vec3b>(i,j)[1], \
                                                                          imgMayoi.at<cv::Vec3b>(i,j)[2] ),-1,1 );

            }
        }

        for(int i=0;i<137;i++){
            for(int j=0;j<226;j++){

                if(imgDialog.at<cv::Vec3b>(i,j)[0] ==255 && imgDialog.at<cv::Vec3b>(i,j)[1] ==255 && imgDialog.at<cv::Vec3b>(i,j)[2] ==255){
                }
                else
                    cv::circle( frame,cv::Point(420+j,170+i),0,cv::Scalar( imgDialog.at<cv::Vec3b>(i,j)[0], \
                                                                          imgDialog.at<cv::Vec3b>(i,j)[1], \
                                                                          imgDialog.at<cv::Vec3b>(i,j)[2] ),-1,1 );

            }
        }

		if (cvui::button(frame, 1100 , 10 ,50, 50, "&Quit")) {
		    break;
		}
		cvui::update();
		cvui::imshow(WINDOW_NAME, frame);
		if (cv::waitKey(20) == 27) {
			break;
		}

/**************************************************************/

        if(GameStart){
            GameFinish = gamestart.printUI(chess,thinkingtime,MCTScheck,RuleBasecheck,NeuralNetworkcheck,&frame,&BG,PlayWithHuman,playercount);
        }

        if(GameFinish)
            break;

	}

}

void DrawControlComponent(cv::Mat* frame,int* thinkingtime,bool* MCTScheck, \
                          bool *RuleBasecheck,bool *NeuralNetworkcheck, \
                          int *playercount,cv::Mat *Hout,cv::Mat *Cout,int *PlayWithHuman,bool *GameStart){
/*
        if (cvui::button(*frame, 600 , 10 ,50, 50, "Undo")) {
		}
*/
        cvui::text(*frame, 600 , 110, "Player:", 1.0);
		if (cvui::button(*frame, 710 , 110 ,30, 30, " ")) {
            switch(*playercount){
            case 2: *playercount = 3; break;
            case 3: *playercount = 2; break;
            }
		}
        cvui::printf(*frame , 715, 115, 0.8, 0xf0f0f0, "%d",*playercount);

        switch(*playercount){

            case 3:
            cv::line( *frame,cv::Point(725,140),cv::Point(725,520),cv::Scalar( 75, 75, 75 ),2.0);
            cv::line( *frame,cv::Point(725,220),cv::Point(800,220),cv::Scalar( 75, 75, 75 ),2.0);
            cv::line( *frame,cv::Point(725,370),cv::Point(800,370),cv::Scalar( 75, 75, 75 ),2.0);
            cv::line( *frame,cv::Point(725,520),cv::Point(800,520),cv::Scalar( 75, 75, 75 ),2.0);

            cvui::window(*frame, 800, 150, 120, 140, " ");

            switch(*PlayWithHuman){
                case 0:
                    cvui::window(*frame, 800, 150, 120, 140, " ");
                    cvui::printf(*frame ,815, 152, 0.6, 0xf0f0f0, "computer");
                    cvui::window(*frame, 800, 300, 120, 140, " ");
                    cvui::printf(*frame ,815, 302, 0.6, 0xf0f0f0, "computer");
                    cvui::window(*frame, 800, 450, 120, 140, " ");
                    cvui::printf(*frame ,815, 452, 0.6, 0xf0f0f0, "computer");
                    if(cvui::button(*frame, 800, 170, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 1;
                    if(cvui::button(*frame, 800, 320, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 2;
                    if(cvui::button(*frame, 800, 470, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 3;
                break;
                case 1:
                    cvui::window(*frame, 800, 150, 120, 140, " ");
                    cvui::printf(*frame ,825, 152, 0.6, 0xf0f0f0, "human");
                    cvui::window(*frame, 800, 300, 120, 140, " ");
                    cvui::printf(*frame ,815, 302, 0.6, 0xf0f0f0, "computer");
                    cvui::window(*frame, 800, 450, 120, 140, " ");
                    cvui::printf(*frame ,815, 452, 0.6, 0xf0f0f0, "computer");
                    if(cvui::button(*frame, 800, 170, *Hout, *Hout, *Hout))
                        *PlayWithHuman = 0;
                    if(cvui::button(*frame, 800, 320, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 1;
                    if(cvui::button(*frame, 800, 470, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 1;
                break;
                case 2:
                    cvui::window(*frame, 800, 150, 120, 140, " ");
                    cvui::printf(*frame ,815, 152, 0.6, 0xf0f0f0, "computer");
                    cvui::window(*frame, 800, 300, 120, 140, " ");
                    cvui::printf(*frame ,825, 302, 0.6, 0xf0f0f0, "human");
                    cvui::window(*frame, 800, 450, 120, 140, " ");
                    cvui::printf(*frame ,815, 452, 0.6, 0xf0f0f0, "computer");
                    if(cvui::button(*frame, 800, 170, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 2;
                    if(cvui::button(*frame, 800, 320, *Hout, *Hout, *Hout))
                        *PlayWithHuman = 0;
                    if(cvui::button(*frame, 800, 470, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 2;
                break;
                case 3:
                    cvui::window(*frame, 800, 150, 120, 140, " ");
                    cvui::printf(*frame ,815, 152, 0.6, 0xf0f0f0, "computer");
                    cvui::window(*frame, 800, 300, 120, 140, " ");
                    cvui::printf(*frame ,815, 302, 0.6, 0xf0f0f0, "computer");
                    cvui::window(*frame, 800, 450, 120, 140, " ");
                    cvui::printf(*frame ,825, 452, 0.6, 0xf0f0f0, "human");
                    if(cvui::button(*frame, 800, 170, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 3;
                    if(cvui::button(*frame, 800, 320, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 3;
                    if(cvui::button(*frame, 800, 470, *Hout, *Hout, *Hout))
                        *PlayWithHuman = 0;
                break;
            }
            break;
            case 2:
            cv::line( *frame,cv::Point(725,140),cv::Point(725,370),cv::Scalar( 75, 75, 75 ),2.0);
            cv::line( *frame,cv::Point(725,220),cv::Point(800,220),cv::Scalar( 75, 75, 75 ),2.0);
            cv::line( *frame,cv::Point(725,370),cv::Point(800,370),cv::Scalar( 75, 75, 75 ),2.0);

            cvui::window(*frame, 800, 150, 120, 140, " ");

            switch(*PlayWithHuman){
                case 0:
                    cvui::window(*frame, 800, 150, 120, 140, " ");
                    cvui::printf(*frame ,815, 152, 0.6, 0xf0f0f0, "computer");
                    cvui::window(*frame, 800, 300, 120, 140, " ");
                    cvui::printf(*frame ,815, 302, 0.6, 0xf0f0f0, "computer");
                    if(cvui::button(*frame, 800, 170, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 1;
                    if(cvui::button(*frame, 800, 320, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 2;
                break;
                case 1:
                    cvui::window(*frame, 800, 150, 120, 140, " ");
                    cvui::printf(*frame ,825, 152, 0.6, 0xf0f0f0, "human");
                    cvui::window(*frame, 800, 300, 120, 140, " ");
                    cvui::printf(*frame ,815, 302, 0.6, 0xf0f0f0, "computer");
                    if(cvui::button(*frame, 800, 170, *Hout, *Hout, *Hout))
                        *PlayWithHuman = 0;
                    if(cvui::button(*frame, 800, 320, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 1;
                break;
                case 2:
                    cvui::window(*frame, 800, 150, 120, 140, " ");
                    cvui::printf(*frame ,815, 152, 0.6, 0xf0f0f0, "computer");
                    cvui::window(*frame, 800, 300, 120, 140, " ");
                    cvui::printf(*frame ,825, 302, 0.6, 0xf0f0f0, "human");
                    if(cvui::button(*frame, 800, 170, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 2;
                    if(cvui::button(*frame, 800, 320, *Hout, *Hout, *Hout))
                        *PlayWithHuman = 0;
                break;
                case 3:
                    cvui::window(*frame, 800, 150, 120, 140, " ");
                    cvui::printf(*frame ,815, 152, 0.6, 0xf0f0f0, "computer");
                    cvui::window(*frame, 800, 300, 120, 140, " ");
                    cvui::printf(*frame ,815, 302, 0.6, 0xf0f0f0, "computer");
                    *PlayWithHuman = 0;
                    if(cvui::button(*frame, 800, 170, *Cout, *Cout, *Cout))
                        *PlayWithHuman = 1;
                    if(cvui::button(*frame, 800, 320, *Hout, *Hout, *Hout))
                        *PlayWithHuman = 2;
                break;
            }
            break;
        }

        if(*GameStart == false){
            if (cvui::button(*frame, 50 , 110 ,500, 50, " ")) {
                *GameStart = true;
            }
            cvui::printf(*frame , 250, 123, 1.0, 0xf0f0f0, "START");
        }

        cvui::window(*frame, 670, 10, 400, 50, "notice:");
        cvui::rect(*frame, 671, 31 , 398, 28, 0xff0000);
		cvui::text(*frame, 680 , 35, "Look before you leap.", 0.5);
/*
        cvui::printf(*frame , 20, 35, 0.6, 0xff0000, "ThinkingTime");
        cvui::printf(*frame , 80, 55, 0.4, 0xff0000, "(second)");
        cvui::trackbar(*frame , 150, 20, 400 ,thinkingtime, 10, 30);
*/
        cvui::rect(*frame, 670, 78 , 400, 20,0x0000ff, 0x2f2f2f);
        cvui::checkbox(*frame, 900, 80, "Neural Network", NeuralNetworkcheck);
		cvui::checkbox(*frame, 800, 80, "Rule Base", RuleBasecheck);
		cvui::checkbox(*frame, 700, 80, "Monti Carlo", MCTScheck);

        cvui::printf(*frame, (*frame).cols - 140, (*frame).rows - 20, 0.4, 0xCECECE, "Made by Phoenix");
}
