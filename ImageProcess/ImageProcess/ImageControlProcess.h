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
		float begin_x; //�Ŵ�ͼƬ���Ͻǵ�ĺ�����
		float begin_y; //�Ŵ�ͼƬ���Ͻǵ��������

		float width; //�Ŵ�ͼƬ�Ŀ�
		float heigth;//�Ŵ�ͼƬ�ĳ�

		char* unchangedImgPath; //����ԭͼ��·��
		struct changeDetail{
			std::string name;
			std::string detail;
		};                     //��ջ�б���仯�Ľṹ��
		int kernelLength;     //����changeIndex.detail�ľֲ��������кü����ж϶���Ҫ������
		int threshold;
		std::stack<changeDetail> changeDetailStack; //������е����б仯�Ķ�ջ
		std::vector<std::string> tempStr;           //�����á����������Ĳ���
		ImageProcess imgProcess;


		ImageControlProcess(void);

		void ZoomImage(int sizeValue, Panel^ panel);//�Ŵ�ͼƬ

		System::Drawing::Bitmap^ MatToBitmap(cv::Mat srcImg); //MatתBitmap

		cv::Mat BitmapToMat(System::Drawing::Bitmap^ bitmap); //BitmapתMat

		void SaveOriginalImg(Panel^ panel); //�ѱ仯����������Ӧ����ԭͼ

       void SplitStr(std::string& src);  //�����á����������Ĳ���
	};
}