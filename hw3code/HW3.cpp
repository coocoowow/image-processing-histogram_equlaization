#define _CRT_SECURE_NO_DEPRECATE //去除fopen報警告
#include <stdio.h> 
#include <cv.h> 
#include <highgui.h> 
#include <iostream>
#include <fstream>
#include <string>
using namespace cv;
using namespace std;
# define size 512*512

cv::Mat histogram(Mat gray)
{
	int c=0,b=0;

	int pixel[256]={0};
	cv::Mat out(600,260,CV_8UC1);
	for(int i=1;i<gray.rows-1;i++)
		{
			for(int j=1;j<gray.cols-1;j++)
				{
					c=gray.at<uchar>(i,j);
					pixel[c]++;
				}
		}
	for(int i=0;i<=255;i++)
    {
        cv::line(out,cv::Point(i,(600-pixel[i]/10)),cv::Point(i,600),CV_RGB(255,128,0));
       
    }

	
	return out;
}



cv::Mat equalization(Mat gray)
{
	cv::Mat out(gray.rows, gray.cols, CV_8UC1);
	int c = 0,n=0;
	int pixel[256] = { 0 };
	for (int i = 0; i<gray.rows; i++)
	{
		for (int j = 0; j<gray.cols; j++)
		{
			c = gray.at<uchar>(i,j);
			pixel[c]++;
		}
	}
	for (c = 0; c<256; c++)
	{  
		n = n + pixel[c];
		for (int i = 0; i < gray.rows; i++)
		{
			for (int j = 0; j < gray.cols; j++)
			{
  
				if (gray.at<uchar>(i,j)==c)
				out.at<uchar>(i, j) = 255 * n / (gray.rows*gray.cols);
			}
		}
	}

	return out;
}






void main()
{

unsigned char *lenai ,*lenai512 ,*lenaibright ,*lenaidark ,*earth512;
char FileNameOri[]="lena_512.raw";
char FileNamebright[]="lena_bright_512.raw";
char FileNamedark[]="lena_dark_512.raw";
char FileNameearth[]="earth_512.raw";
lenai = new unsigned char[size]; 
lenai512 = new unsigned char[size]; 
lenaibright = new unsigned char[size]; 
lenaidark = new unsigned char[size];
earth512 = new unsigned char[size]; 
CvMat *lenamat = cvCreateMat(512,512, CV_8UC1);
CvMat *lenamatbright = cvCreateMat(512,512, CV_8UC1);
CvMat *lenamatdark = cvCreateMat(512,512, CV_8UC1);
CvMat *earthmat = cvCreateMat(512,512, CV_8UC1);
FILE *lena;
	lena = fopen(FileNameOri,"rb");
FILE *lenabright;
	lenabright = fopen(FileNamebright,"rb");
FILE *lenadark;
	lenadark = fopen(FileNamedark,"rb");
FILE *earth;
	earth = fopen(FileNameearth,"rb");

		fread(lenai,1,size,lena);
		cvSetData(lenamat,lenai,lenamat->step);
		fread(lenaibright,1,size,lenabright);
		cvSetData(lenamatbright,lenaibright,lenamatbright->step);
		fread(lenaidark,1,size,lenadark);
		cvSetData(lenamatdark,lenaidark,lenamatdark->step);
		fread(earth512,1,size,earth);
		cvSetData(earthmat,earth512,earthmat->step);


cv::Mat dst;
dst = Mat(lenamat->rows,lenamat ->cols,lenamat->type,lenamat->data.fl);//轉換格式
cv::Mat dstbright;
dstbright = Mat(lenamatbright->rows,lenamatbright ->cols,lenamatbright->type,lenamatbright->data.fl);//轉換格式
cv::Mat dstdark;
dstdark = Mat(lenamatdark->rows,lenamatdark ->cols,lenamatdark->type,lenamatdark->data.fl);//轉換格式
cv::Mat dstearth;
dstearth = Mat(earthmat->rows,earthmat ->cols,earthmat->type,earthmat->data.fl);//轉換格式				
	int number1=0;
	cout<<"輸入題號:例如1_a小題為11 2_a小題為21";
	cin>> number1;
	if( number1 ==21)
	{
		imshow("lena512",histogram(dst));
		imshow("bright",histogram(dstbright));
		imshow("dark",histogram(dstdark));
		imshow("earth",histogram(dstearth));
		cvWaitKey(0);
	}	
	if(number1==22)
	{
		Mat output512,equ512,outputbright,equbright,outputdark,equdark,outputearth,equearth;
		equ512=equalization(dst);
		output512=histogram(equ512);

		equbright=equalization(dstbright);
		outputbright=histogram(equbright);
		
		equdark=equalization(dstdark);
		outputdark=histogram(equdark);
		
		equearth=equalization(dstearth);
		outputearth=histogram(equearth);
		
		imshow("lena512",output512);
		imshow("lenaequbright",equbright);
		imshow("lenaequdark",equdark);
				imshow("lenaequearth",equearth);
		imshow("lenabright",outputbright);
		imshow("lenadark",outputdark);
		imshow("lenaearth",outputearth);
		cvWaitKey(0);
	}


	}
