#pragma once

#include "stdafx.h"  
#include <string>   
#include <iostream> 
#include "ShowImage.h"
#include "ImageProcess.h"
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stack>
#include "ChangeIndex.h"
#include <vector>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace System::Text;
using namespace System::IO;
using namespace System::Diagnostics;


namespace ImageHelper{
	public class ImageControlProcess{

	public:
		float begin_x; //放大图片左上角点的横坐标
		float begin_y; //放大图片左上角点的纵坐标

		float width; //放大图片的宽
		float heigth;//放大图片的长

		char* unchangedImgPath; //保存原图的路径
		struct changeDetail{
			std::string name;
			std::string detail;
		};                     //堆栈中保存变化的结构体
		int kernelLength;     //保存changeIndex.detail的局部变量（有好几个判断都需要声明）
		int threshold;
		std::stack<changeDetail> changeDetailStack; //保存进行的所有变化的堆栈
		std::vector<std::string> tempStr;           //保存用“，”隔开的参数
		ImageProcess imgProcess;


		ImageControlProcess(void);

		void ZoomImage(int sizeValue, Panel^ panel);//放大图片

		System::Drawing::Bitmap^ MatToBitmap(cv::Mat srcImg); //Mat转Bitmap

		cv::Mat BitmapToMat(System::Drawing::Bitmap^ bitmap); //Bitmap转Mat

		void SaveOriginalImg(Panel^ panel); //把变化保存下来并应用于原图

       void SplitStr(std::string& src);  //分离用“，”隔开的参数
	};
}