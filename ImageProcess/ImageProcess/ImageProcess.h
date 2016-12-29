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

		std::string fileName ;//�ļ�·��
		std::string tempFilePath; //��ʱ�ļ��洢·��
		std::string finalPath; //�޸ĺ󱣴��ļ�·��
		cv::Mat originalImg ;//�ӱ�����ԭʼͼƬ
		cv::Mat oprateImg ;//�����ͼƬ
		cv::Mat tempImg;//ÿ��ִ�к�δ����ImageChange��ͼ
		cv::Mat unchangeImg;//û�ӱ�����ԭʼͼƬ
		cv::Mat histogram;//ֱ��ͼ
		cv::Mat fourierImg;//����Ҷ�任���ͼ
		cv::Mat grayImg;
		cv::Mat tempExportMat;
		bool loadFlag;//ָʾ�Ƿ���سɹ�
		bool grayFlag;//�Ƿ�Ϊ�Ҷ�ͼ
		std::map<std::string,double> imageState;
		std::map<std::string,bool> oprationState;
		std::vector<cv::Mat> imgHistoryVec;
		std::vector<std::string> lastChangeVec;//����ͼƬ���еı仯
		std::string lastChange;//��¼ͼƬ���еı仯

		changeIndex lastChangeIndex;//��¼�仯����ϸ��Ϣ
		std::vector<changeIndex> changeIndexVec;//��¼���б仯


		ImageProcess(void);
        void ContrastBrightChange();
		void LoadPicture(int pnlWidth,int pnlHeigth );//����ͼƬ
		void SavePicture(std::string filePath);//����ͼƬ
		void ReLoadPicture();//��������ͼƬ
		void Reset();//���ñ�־λ
		void ScaleChange(double scale);//�޸ĳߴ�
		void AngleChange(double angle);//��תͼƬ
		void ContrastChange(double contrast);//�޸ĶԱȶ�
		void BrightChange(double bright);//�޸�����
		void GrayProcessing();//���ɻҶ�ͼ
		void Histogram();//����ֱ��ͼ
		void FourierTransform();//����Ҷ�任
		void EdgeDetection(double lowThreshold,int method);//��Ե���
		void Smoothing(int method,int kernelLength);//ͼ��ƽ������
		void Threshold(int method, int thresholdValue );//��ֵ
		void SaturationAdjuest(double i);//���Ͷ�
		std::string ConvertToString( double i);//������ת�����ַ���


	};
}