#pragma once



#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>
#include <cmath>
#include <map> 
#include <time.h> 
#include "ChangeIndex.h"



namespace ImageHelper{

	public class ImageProcess{




	private:

		void ScaleAngleChange();
		
	public:

		std::string fileName ;//文件路径
		std::string tempFilePath; //临时文件存储路径
		std::string finalPath; //修改后保存文件路径
		cv::Mat originalImg ;//加背景后原始图片
		cv::Mat oprateImg ;//处理后图片
		cv::Mat tempImg;//每次执行后未进行ImageChange的图
		cv::Mat unchangeImg;//没加背景的原始图片
		cv::Mat histogram;//直方图
		cv::Mat fourierImg;//傅里叶变换后的图
		cv::Mat grayImg;
		cv::Mat tempExportMat;
		bool loadFlag;//指示是否加载成功
		bool grayFlag;//是否为灰度图
		std::map<std::string,double> imageState;
		std::map<std::string,bool> oprationState;
		std::vector<cv::Mat> imgHistoryVec;
		std::vector<std::string> lastChangeVec;//保存图片进行的变化
		std::string lastChange;//记录图片进行的变化

		changeIndex lastChangeIndex;//记录变化的详细信息
		std::vector<changeIndex> changeIndexVec;//记录所有变化


		ImageProcess(void);
        void ContrastBrightChange();
		void LoadPicture(int pnlWidth,int pnlHeigth );//载入图片
		void SavePicture(std::string filePath);//保存图片
		void ReLoadPicture();//重新载入图片
		void Reset();//重置标志位
		void ScaleChange(double scale);//修改尺寸
		void AngleChange(double angle);//旋转图片
		void ContrastChange(double contrast);//修改对比度
		void BrightChange(double bright);//修改亮度
		void GrayProcessing();//生成灰度图
		void Histogram();//生成直方图
		void FourierTransform();//傅里叶变换
		void EdgeDetection(double lowThreshold,int method);//边缘检测
		void Smoothing(int method,int kernelLength);//图像平滑处理
		void Threshold(int method, int thresholdValue );//阈值
		void SaturationAdjuest(double i);//饱和度
		std::string ConvertToString( double i);//将数字转换成字符串


	};
}