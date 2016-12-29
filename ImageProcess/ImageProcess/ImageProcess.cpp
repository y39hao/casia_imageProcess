#include "stdafx.h"
#include "ImageProcess.h"
using namespace System::Threading;


ImageHelper::ImageProcess::ImageProcess(void){
	fileName="";
	tempFilePath="C:\\Users\\Public\\Pictures\\Sample Pictures\\temp.jpg";
	loadFlag=false;
	grayFlag=false;
	imageState.insert(std::pair<std::string,double> ("scale",1) );
	imageState.insert(std::pair<std::string,double> ("angle",0));
	imageState.insert(std::pair<std::string,double> ("contrast",1));
	imageState.insert(std::pair<std::string,double> ("bright",0));
	imageState.insert(std::pair<std::string,double> ("lowThreshold",0));

	oprationState.insert(std::pair<std::string,bool> ("scale",false));
    oprationState.insert(std::pair<std::string,bool> ("angle",false));
	oprationState.insert(std::pair<std::string,bool> ("contrast_bright",false));
	oprationState.insert(std::pair<std::string,bool> ("edgeDetection",false));
	oprationState.insert(std::pair<std::string,bool> ("smoothing",false));
	oprationState.insert(std::pair<std::string,bool> ("threshold",false));
	oprationState.insert(std::pair<std::string,bool> ("gray",false));
	lastChangeIndex.currentImg = 0;
	lastChangeIndex.lastImg = 0;
	lastChangeIndex.detail = "";
	lastChangeIndex.name = "";


}



std::string ImageHelper::ImageProcess::ConvertToString( double i) {
		std::stringstream ss;
		ss << i;
		return ss.str();
}

void ImageHelper::ImageProcess::ScaleAngleChange( ){


	cv::Point2f center = cv::Point2f(originalImg.cols / 2, originalImg.rows / 2);  // 旋转中心
	cv::Mat rotateMat;                                                 // 变换矩阵 
	rotateMat = cv::getRotationMatrix2D(center, imageState["angle"],imageState["scale"]);
	cv::warpAffine(originalImg, oprateImg, rotateMat, oprateImg.size());
	oprationState["angle"]=true;

}

void ImageHelper::ImageProcess::ContrastBrightChange(){
	for(int y = 0; y < originalImg.rows; y++ )  
	{  
		for(int x = 0; x <originalImg.cols; x++ )  
		{  
			for(int c = 0; c < 3; c++ )  
			{  
				oprateImg.at<cv::Vec3b>(y,x)[c] = 
					cv::saturate_cast<uchar>( imageState["contrast"] * (originalImg.at<cv::Vec3b>(y,x)[c] ) + imageState["bright"] );  
			}  
		}  
	}
	oprationState["contrast_bright"]=true;
	lastChange = "对比度和亮度调节 ";
	std::string contrast = ConvertToString(imageState["contrast"]);
	std::string bright = ConvertToString(imageState["bright"]);
	lastChangeIndex.name = "contrast_bright";
	lastChangeIndex.detail = contrast + "," + bright;
}

void ImageHelper::ImageProcess::LoadPicture(int pnlWidth,int pnlHeigth){
	char * picName = const_cast<char*>(fileName.c_str());
	unchangeImg = cv::imread(picName);


	originalImg = cv::Mat(cv::Size(pnlWidth,pnlHeigth),unchangeImg.type());
	oprateImg = cv::Mat(cv::Size(pnlWidth,pnlHeigth),unchangeImg.type());


	int fx,fy;

	int aftChangeRows = unchangeImg.rows;
	int aftChangeCols = unchangeImg.cols;


	if ((pnlWidth < unchangeImg.cols)||(pnlHeigth < unchangeImg.rows))
	{
		if (((float)unchangeImg.cols/unchangeImg.rows) > ((float)pnlWidth/pnlHeigth))
		{
			aftChangeRows = (unchangeImg.rows * pnlWidth)/(float)unchangeImg.cols;
			aftChangeCols = pnlWidth;
			
		}
		else
		{
			aftChangeCols = (unchangeImg.cols * pnlHeigth)/(float)unchangeImg.rows;
			aftChangeRows = pnlHeigth;
		}

	}

	cv::Mat resizedMat;
	cv::resize( unchangeImg,resizedMat, cv::Size(aftChangeCols,aftChangeRows), 0, 0, cv::INTER_LINEAR );

	fx = (pnlWidth - aftChangeCols)/2;
	fy = (pnlHeigth - aftChangeRows)/2;

	cv::Rect imgRange = cv::Rect(fx,fy,aftChangeCols,aftChangeRows );


	cv::Mat imageROI;

	imageROI = originalImg(imgRange);
	resizedMat.copyTo(imageROI); 

	oprateImg = originalImg.clone();
	originalImg.copyTo(oprateImg);
    
	lastChange = "原图" ;
	lastChangeIndex.name = "original";
	lastChangeIndex.detail = "0";
}

void ImageHelper::ImageProcess::SavePicture(std::string filePath){
	char * fileName = const_cast<char*>(filePath.c_str());
	imwrite(fileName, oprateImg);
}

void ImageHelper::ImageProcess::ReLoadPicture(){
	char * fileName = const_cast<char*>(tempFilePath.c_str());
	originalImg = cv::imread(fileName);
}

void ImageHelper::ImageProcess::Reset(){
	oprationState["angle"]=false;
    oprationState["contrast_bright"]=false;
    oprationState["edgeDetection"]=false;
    oprationState["smoothing"]=false;
    oprationState["threshold"]=false;
    oprationState["gray"]=false;
    oprationState["scale"]=false;

}

void ImageHelper::ImageProcess::ScaleChange(double scale){
	//设置值在【-100,100】之间，默认值为0
	double i = scale/250;
	double size = std::pow(2,i);
	imageState["scale"]=size;
	ScaleAngleChange();
}

void ImageHelper::ImageProcess::AngleChange(double angle){
	//设置值在【-180，180】之间，默认值为0
	imageState["angle"]=angle;
	ScaleAngleChange();
	lastChange = "旋转 ";
	lastChangeIndex.name = "angle";
	lastChangeIndex.detail = ConvertToString(angle);
}

void ImageHelper::ImageProcess::ContrastChange(double contrast){
	//设置值在【-100,300】之间，默认值100
	double i=contrast/100;
	imageState["contrast"]=i;
	ContrastBrightChange();
	
}

void ImageHelper::ImageProcess::BrightChange(double bright){
	//设置值在【-150,150】之间，默认值0
	imageState["bright"]=bright;
	ContrastBrightChange();
}

void ImageHelper::ImageProcess::GrayProcessing(){
	//grayImg= cv::Mat::zeros(oprateImg.size(), oprateImg.type() );
	cv::cvtColor(oprateImg,oprateImg,CV_RGB2GRAY); 
	//oprationState["gray"]=true;
	lastChange = "灰度处理 ";
	lastChangeIndex.name = "gray";
	lastChangeIndex.detail = "0";

}

void ImageHelper::ImageProcess::Histogram(){
	cv::Mat gray;   

	cv::cvtColor(oprateImg,gray,CV_RGB2GRAY);  
	int bins = 256;  
	int hist_size[] = {bins};  
	float range[] = { 0, 256 };  
	const float* ranges[] = { range};  
	cv::MatND hist;  
	int channels[] = {0};  

	cv::calcHist( &gray, 1, channels,cv::Mat(), // do not use mask  
		hist, 1, hist_size, ranges,  
		true, // the histogram is uniform  
		false );  

	double max_val;  
	cv::minMaxLoc(hist, 0, &max_val, 0, 0);  
	int scale = 2;  
	int hist_height=256;  
	histogram =cv::Mat::zeros(hist_height,bins*scale, CV_8UC3);  
	for(int i=0;i<bins;i++)  
	{  
		float bin_val = hist.at<float>(i);   
		int intensity = cvRound(bin_val*hist_height/max_val);  //要绘制的高度  
		cv::rectangle(histogram,cv::Point(i*scale,hist_height-1),  
			cv::Point((i+1)*scale - 1, hist_height - intensity),  
			CV_RGB(255,255,255));  
	}  


}

void ImageHelper::ImageProcess::FourierTransform(){
	cv::Mat destinImage= cv::Mat::zeros(oprateImg.size(), oprateImg.type() );
	cv::cvtColor(oprateImg,destinImage,CV_RGB2GRAY);
	cv::Mat padded;                            //放大图片到合适尺寸
	int m = cv::getOptimalDFTSize( destinImage.rows );
	int n = cv::getOptimalDFTSize( destinImage.cols ); // on the border add zero values
	cv::copyMakeBorder(destinImage, padded, 0, m - destinImage.rows, 0, n - destinImage.cols,cv::BORDER_CONSTANT, cv::Scalar::all(0));

	cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
	cv::Mat complexI;
	cv::merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	cv::dft(complexI, complexI);            // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	cv::split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude  
	cv::Mat magI = planes[0];

	magI += cv::Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center        
	int cx = magI.cols/2;
	int cy = magI.rows/2;

	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant 
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

	cv::Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	cv::normalize(magI, fourierImg, 0, 255, CV_MINMAX); // Transform the matrix with float values into a 
	// viewable image form (float between values 0 and 1).
	std::string fftPath = "C:\\Users\\Public\\Pictures\\Sample Pictures\\Fourier.jpg";
	char * picName = const_cast<char*>(fftPath.c_str());
	imwrite(picName, fourierImg);
}

void ImageHelper::ImageProcess::EdgeDetection(double lowThreshold, int method){

	cv::Mat  src_gray,dst;
	int ratio = 3;
	int kernel_size = 3;
	int scale = 1;  
	int delta = 0;  
	int ddepth = CV_16S;  

	cvtColor( originalImg, src_gray, CV_BGR2GRAY );

	/// 使用 3x3内核降噪
	cv::blur( src_gray, dst, cv::Size(3,3) );
	switch(method){
	case 0:

		/// 运行Canny算子
		cv::Canny( dst, dst, lowThreshold, lowThreshold*ratio, kernel_size );

		//originalImg.copyTo( oprateImg, dst);
		oprateImg=dst.clone();
		dst.copyTo(oprateImg);
		lastChange = "Canny算子边缘检测 ";
		lastChangeIndex.name = "canny";
		lastChangeIndex.detail = ConvertToString(lowThreshold);
		break;

	case 1:

		cv:: Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT );  
		convertScaleAbs( dst, oprateImg );  
		lastChange = "Laplace算子边缘检测 ";
		lastChangeIndex.name = "laplace";
		lastChangeIndex.detail = "0";

		break;

	}
	oprationState["edgeDetection"]=true;

}

void ImageHelper::ImageProcess::Smoothing(int method ,int kernelLength){

	int DELAY_CAPTION = 1500;  
	int DELAY_BLUR = 100;  
	switch(method){
	case 0:
		/// Applying Homogeneous blur   
		for ( int i = 1; i < kernelLength; i = i + 2 )  
		{ 
			cv::blur( oprateImg, oprateImg, cv::Size( i, i ), cv::Point(-1,-1) ); 
		}  
		lastChange = "均值滤波平滑 ";
		lastChangeIndex.name = "blur";
		lastChangeIndex.detail = ConvertToString(kernelLength);
		break;

	case 1:
		/// Applying Gaussian blur 

		for ( int i = 1; i < kernelLength; i = i + 2 )  
		{ 
			cv::GaussianBlur( oprateImg, oprateImg, cv::Size( i, i ), 0, 0 ); 
		}  
		lastChange = "高斯滤波平滑 ";
		lastChangeIndex.name = "gaussian";
		lastChangeIndex.detail = ConvertToString(kernelLength);
		break;

	case 2 :

		/// Applying Median blur  

		for ( int i = 1; i < kernelLength; i = i + 2 )  
		{ 
			cv::medianBlur ( oprateImg, oprateImg, i ); } 
		lastChange = "中值滤波平滑 ";
		lastChangeIndex.name = "median";
		lastChangeIndex.detail = ConvertToString(kernelLength);
		break;

	case 3:
		/// Applying Bilateral Filter    
		for ( int i = 1; i < kernelLength; i = i + 2 )  
		{ 
			cv::bilateralFilter ( oprateImg, oprateImg, i, i*2, i/2 ); 
		}
		lastChange = "双边滤波平滑 ";
		lastChangeIndex.name = "bilateral";
		lastChangeIndex.detail = ConvertToString(kernelLength);
		break;

	}
    oprationState["smoothing"]=true;
}

void  ImageHelper::ImageProcess::Threshold(int method, int thresholdValue ){

	int const max_BINARY_value = 255;
	cv::Mat grayImg;
	/// 将图片转换成灰度图片
	cv::cvtColor(originalImg, grayImg, CV_RGB2GRAY );
	cv::threshold( grayImg, oprateImg, thresholdValue, max_BINARY_value,method );
	oprationState["threshold"]=true;
    switch(method){
	case 0:
		lastChange = "二进制阈值变换 ";
		lastChangeIndex.name = "binary";
		lastChangeIndex.detail = ConvertToString(thresholdValue);
		break;
	case 1:
		lastChange = "反二进制阈值变换 ";
		lastChangeIndex.name = "antibinary";
		lastChangeIndex.detail = ConvertToString(thresholdValue);
		break;
	case 2:
		lastChange = "截断阈值变换 ";
		lastChangeIndex.name = "interceptive";
		lastChangeIndex.detail = ConvertToString(thresholdValue);
		break;
	case 3:
		lastChange = "0阈值变换 ";
		lastChangeIndex.name = "zero";
		lastChangeIndex.detail = ConvertToString(thresholdValue);
		break;
	case 4:
		lastChange = "反0阈值变换 ";
		lastChangeIndex.name = "antizero";
		lastChangeIndex.detail = ConvertToString(thresholdValue);
		break;
	}

}



/**void ImageProcess::ImageControl::SaturationAdjuest(double increment){



cv::Mat Img_out(originalImg.size(), CV_32FC3);  
originalImg.convertTo(Img_out, CV_32FC3);  
cv::Mat Img_in(originalImg.size(), CV_32FC3);  
originalImg.convertTo(Img_in, CV_32FC3);  
// define the iterator of the input image  
cv::MatIterator_<cv::Vec3f> inp_begin, inp_end;  
inp_begin=Img_in.begin<cv::Vec3f>();  
inp_end =Img_in.end<cv::Vec3f>();  

// define the iterator of the output image  
cv::MatIterator_<cv::Vec3f> out_begin, out_end;  
out_begin=Img_out.begin<cv::Vec3f>();  
out_end =Img_out.end<cv::Vec3f>();  


float delta=0;  
float minVal, maxVal;  
float t1, t2, t3;  
float L,S;  
float alpha;  

for(; inp_begin!=inp_end; inp_begin++, out_begin++)  
{  
t1=(*inp_begin)[0];  
t2=(*inp_begin)[1];  
t3=(*inp_begin)[2];  

minVal=std::min(std::min(t1,t2),t3);  
maxVal=std::max(std::max(t1,t2),t3);  
delta=(maxVal-minVal)/255.0;  
L=0.5*(maxVal+minVal)/255.0;  
S=std::max(0.5*delta/L, 0.5*delta/(1-L));  

if (increment>0)  
{  
alpha=S>(1-increment)?S:(1-increment);  
alpha=1.0/alpha-1;  
(*out_begin)[0]=(*inp_begin)[0]+((*inp_begin)[0]-L*255.0)*alpha;  
(*out_begin)[1]=(*inp_begin)[1]+((*inp_begin)[1]-L*255.0)*alpha;  
(*out_begin)[2]=(*inp_begin)[2]+((*inp_begin)[2]-L*255.0)*alpha;  
}  
else  
{  
alpha=increment;  
(*out_begin)[0]=L*255.0+((*inp_begin)[0]-L*255.0)*(1+alpha);  
(*out_begin)[1]=L*255.0+((*inp_begin)[1]-L*255.0)*(1+alpha);  
(*out_begin)[2]=L*255.0+((*inp_begin)[2]-L*255.0)*(1+alpha);  

}  
}  
oprateImg=Img_out/255.0;  



}
**/