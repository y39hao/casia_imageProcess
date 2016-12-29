#include "stdafx.h"
#include "ShowImage.h"
#include <stdlib.h>

CImageShow::CImageShow(void)
{
}


CImageShow::~CImageShow(void)
{
}

void CImageShow::ShowMat(cv::Mat img, HWND hWndDisplay,int channels){

	RECT rect;
	int   screenHeight = 0;
	int   screenWidth = 0;
	float screenRatio = 0;

	int   imgHeight  = 0;
	int   imgWidth = 0;
	float imgRatio = 0;

	int imgShowWidth = 0;
	int imgShowHeight = 0;
	int showPosX = 0;
	int showPosY = 0;

	ATL::CImage CI; 
	HDC dcHandel; 

	GetClientRect(hWndDisplay, &rect);  
	screenHeight = abs(rect.top - rect.bottom);
	screenWidth  = abs(rect.right - rect.left);
	screenRatio  = (float)screenHeight / screenWidth;

	imgHeight = img.rows;
	imgWidth  = img.cols;
	imgRatio  = (float)imgHeight / imgWidth;

	if (screenRatio > imgRatio)
	{
		imgShowWidth  = screenWidth;
		imgShowHeight = ((float)imgHeight / imgWidth) * screenWidth ;
		showPosX = 0;
		showPosY = (screenHeight - imgShowHeight) / 2;
	}
	else
	{
		imgShowWidth = ((float)imgWidth / imgHeight) * screenHeight;
		imgShowHeight = screenHeight;
		showPosX = (screenWidth - imgShowWidth) / 2;
		showPosY = 0;
	}

	cv::Mat imgShow;
	if (channels == 3)
	{
		imgShow = cv::Mat(imgShowHeight, imgShowWidth, CV_8UC3 ); 
	}
	else if (channels == 1)
	{
		imgShow = cv::Mat(imgShowHeight, imgShowWidth, CV_8UC1 ); 

	}
	resize(img, imgShow, imgShow.size(),0,0,CV_INTER_LINEAR );
	
	CI.Create(imgShowWidth, imgShowHeight, 8 * channels);  
  
	uchar *pImg = (uchar *)CI.GetBits();      //得到CImage数据区地址 
	uchar *pS; 
	int step = CI.GetPitch();  
	for(int i = 0;i < imgShowHeight; i++)  
	{  
		pS = imgShow.ptr<uchar>(i);  
		for(int j = 0;j < imgShowWidth; j++)  
		{  
			for(int k = 0; k < channels; k++)  
				*(pImg + i * step + j * channels + k) = pS[j * channels + k];  
		}  
	}

	dcHandel = GetDC( hWndDisplay );

	CI.Draw( dcHandel, showPosX, showPosY ); 
	ReleaseDC( hWndDisplay, dcHandel);  
	CI.Destroy(); 
}

