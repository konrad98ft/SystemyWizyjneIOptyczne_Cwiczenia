#include <opencv2/highgui/highgui.hpp> 
#include "opencv2/imgproc/imgproc.hpp" 
#include <string> 
#include <iostream> 
#include <algorithm>

using namespace cv;
using namespace std;

#define IMG_PATH "Test Image Resolution.png"
#define STEP 12
#if STEP==6
void onSuwak(int poz, void* userData)
{
	cv::Mat* pimg = (cv::Mat*)userData;
	cv::Mat tmp;
	cv::threshold(*pimg, tmp, poz, 255, cv::THRESH_BINARY);
	cv::imshow("Test", tmp);
}
#endif
#if STEP==7
void onSuwak(int poz, void* userData)
{
	cv::Mat* param = (cv::Mat*)userData;
	cv::threshold(param[0], param[1], poz, 255, cv::THRESH_BINARY);
	cv::imshow("Test", param[1]);
}
#endif
#if STEP==9
struct SDaneSuwak
{
	cv::Mat imgIn, imgOut;
	int poz;
};

void onSuwak(int poz, void* userData)
{
	SDaneSuwak* param = (SDaneSuwak*)userData;
	param->poz = poz;
	cv::threshold(param->imgIn, param->imgOut, poz, 255, cv::THRESH_BINARY);
	cv::imshow("Test", param->imgOut);
}
#endif
#if STEP==9
void onMouse(int event, int x, int y, int flags, void* userdata)
{
	cv::Mat* pimg = (cv::Mat*)userdata;
	std::cout << "x:" << x << " y:" << y << " e:" << event << " f:" << flags << std::endl;
	std::cout << pimg->at<cv::Vec3b>(y, x) << std::endl;
}
#endif
#if STEP==10
void onMouse(int event, int x, int y, int flags, void* userdata) //przyk�ad akcji po klikni�ciu 
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		cv::Mat* pimg = (cv::Mat*)userdata;
		std::cout << pimg->at<cv::Vec3b>(y, x) << std::endl;
		cv::circle(*pimg, cv::Point(x, y), 10, cv::Scalar(0, 0, 255), 2); //czerwone wieksze kolko
		cv::imshow("Test", *pimg);
	}
}
#endif
#if STEP==11 
void onMouse(int event, int x, int y, int flags, void* userdata) //rysowanie - przeci�gani� przy naci�ni�tym przycisku, SHIFT zmiana koloru
{
	if (flags & cv::EVENT_FLAG_LBUTTON)
	{
		cv::Mat* pimg = (cv::Mat*)userdata;
		if (flags & cv::EVENT_FLAG_SHIFTKEY)
			cv::circle(*pimg, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 2);
		else
			cv::circle(*pimg, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 2);
		cv::imshow("Test", *pimg);
	}
}
#endif
#if STEP==12 
struct SDaneMysz
{
	cv::Mat imgIn, imgOut;
	int xp,yp,xk,yk;
	bool leftIsPressed;
};


void onMouse(int event, int x, int y, int flags, void* userData) //rysowanie - przeci�gani� przy naci�ni�tym przycisku
{
	SDaneMysz* myszka = (SDaneMysz*)userData;
	myszka->imgOut=myszka->imgIn.clone();
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		cv::Mat* pimg = (cv::Mat*)myszka;
		myszka->xp = x;
		myszka->yp = y;
		myszka->leftIsPressed = true;
	}
	if (event == cv::EVENT_LBUTTONUP)
	{
		cv::Mat* pimg = (cv::Mat*)myszka;
		myszka->xk = x;
		myszka->yk = y;
		line(myszka->imgIn, Point(myszka->xp, myszka->yp), Point(myszka->xk, myszka->yk), Scalar(255, 0, 0), 2);	
		myszka->leftIsPressed = false;
	}
	cout<<"x: "<<x<<" y: "<<y << " xp: " << myszka->xp << " yp: " << myszka->yp << "xk: " << myszka->xk << " yk: " << myszka->yk<< endl;
	if(myszka->leftIsPressed) line(myszka->imgOut, Point(myszka->xp, myszka->yp), Point(x, y), Scalar(0, 0, 255), 2);
	cv::imshow("Test", myszka->imgOut);
}
#endif




int main()
{
#if STEP==0 //Test konfiguracji
	cv::Mat loadedImg = cv::imread(IMG_PATH,0);
	cv::imshow("Test", loadedImg);
	cv::waitKey();
#endif
#if STEP==1 //Tworzenie macierzy obrazu
	cv::Mat img = cv::Mat(300, 400, CV_8UC3); //opm�wi� parametry i zasady tworzenia definicji typu np: CV_16SC1, CV_32FC3, CV_64FC1 .....
	cv::imshow("Test", img); //obraz szary niezainicjalizowany
	cv::waitKey();
#endif
#if STEP==2 //Inicjalizacja danych macierzy obrazu
	cv::Mat img = cv::Mat(300, 400, CV_8UC3); //opm�wi� parametry i zasady tworzenia definicji typu np: CV_16SC1, CV_32FC3, CV_64FC1 .....
	img = Scalar(60,180,44); //Inicjalizacja na zielony
	//1: img = 255; //Inicjalizacja na 255 ale tylko w kanale 1 (niebieskim);
	//2: img = cv::Scalar(0,255,128); //Wpisywanie dowolnej warto�ci wielo kanalowej;
	cv::imshow("Test", img);
	cv::waitKey();
#endif
#if STEP==3 //Kopiowanie obrazu (uchwytu i klonowanie)
	cv::Mat loadedImg = cv::imread(IMG_PATH);
	//cv::Mat img = loadedImg;
	cv::Mat img = loadedImg.clone();	//fakt otwierają się różne 
	img = cv::Scalar(0, 255, 128);
	cv::imshow("Test", img);
	cv::waitKey();
	cv::imshow("Test2", loadedImg);
	cv::waitKey();
#endif
#if STEP==4 //ROI
	cv::Mat loadedImg = cv::imread(IMG_PATH);
	cv::Mat img(loadedImg, cv::Rect(loadedImg.cols/3, loadedImg.rows/3, loadedImg.cols/3, loadedImg.rows/3)); //2: cv::Mat img=cv::Mat(loadedImg, cv::Rect(50, 175, 150, 100)).clone();
	img = cv::Scalar(0,255,128); 
	cv::imshow("Test", img); //Wycinek ROI
	cv::waitKey();
	cv::imshow("Test", loadedImg); //Po uruchomieniu odblokowa� przypisanie i pokaza� �e dzia�amy ca� czas na tych samych danych. Potem mo�na ewewntualnie zmodyfikowa� na klonowanie.
	cv::waitKey();
#endif
#if STEP==5 //Interfejs u�ytkownika - suwak ver1
	cv::Mat loadedImg = cv::imread(IMG_PATH);
	cv::imshow("Test", loadedImg);
	int val = 120;
	cv::createTrackbar("Prog", "Test", &val, 255);
	cv::Mat tmp;
	do
	{
		cv::threshold(loadedImg, tmp, val, 255, cv::THRESH_BINARY);
		cv::imshow("Test", tmp);
	} while (cv::waitKey() != 'q');
	//s�aba interakcja od�wie�enie widoku po naci�ni�ciu przycisku.
#endif
#if STEP==6 //Interfejs u�ytkownika - suwak ver2
	cv::Mat loadedImg = cv::imread(IMG_PATH);
	cv::imshow("Test", loadedImg);
	int val = 120;
	cv::createTrackbar("Prog", "Test", &val, 255, onSuwak, &loadedImg);
	cv::waitKey(); //interakcja OK ale po doborze pozycji trzeba jeszcze raz przeliczy� bo przes�ali�my tylko obraz wej�ciowy a brak danych wyj�ciowych.
#endif
#if STEP==7 //Interfejs u�ytkownika - suwak ver3
	cv::Mat loadedImg = cv::imread(IMG_PATH);
	cv::imshow("Test", loadedImg);
	int val = 120;
	cv::Mat param[2] = { loadedImg, loadedImg.clone() };
	cv::createTrackbar("Prog", "Test", &val, 255, onSuwak, (void*)param);
	cv::waitKey(); //interakcja OK ale ograniczamy si� do przekazania tablicy jednego typu.
	cv::imshow("Test2", param[1]);
	cv::waitKey();
#endif
#if STEP==8 //Interfejs u�ytkownika - suwak ver4
	cv::Mat loadedImg = cv::imread(IMG_PATH);
	cv::imshow("Test", loadedImg);
	int val = 120;
	SDaneSuwak param = { loadedImg, loadedImg.clone(), 120 };
	cv::createTrackbar("Prog", "Test", &val, 255, onSuwak, &param);
	cv::waitKey(); //interakcja OK i mo�na wszystko i przejrzy�cie
	cv::imshow("Test2", param.imgOut);
	cv::waitKey();
#endif
#if STEP==9 || STEP==10 || STEP==11 || STEP==12 //obs�uga myszki
	cv::Mat loadedImg = cv::imread(IMG_PATH);
	cv::imshow("Test", loadedImg);
	SDaneMysz myszka = { loadedImg,loadedImg.clone(),0,0,0,0,false };
	cv::setMouseCallback("Test", onMouse, &myszka);
	cv::waitKey();
#endif
	return 0;
}


