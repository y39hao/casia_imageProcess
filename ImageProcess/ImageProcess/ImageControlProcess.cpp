#include "stdafx.h"
#include "ImageControlProcess.h"



ImageHelper::ImageControlProcess::ImageControlProcess(void){
	begin_x = 0;
	begin_y = 0;
	width = 0;
	heigth = 0;

}

cv::Mat ImageHelper::ImageControlProcess::BitmapToMat(System::Drawing::Bitmap^ bitmap)
{
	IplImage* tmp;

	System::Drawing::Imaging::BitmapData^ bmData = bitmap->LockBits(System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height), System::Drawing::Imaging::ImageLockMode::ReadWrite, bitmap->PixelFormat);
	if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format8bppIndexed)
	{
		tmp = cvCreateImage(cvSize(bitmap->Width, bitmap->Height), IPL_DEPTH_8U, 1);
		tmp->imageData = (char*)bmData->Scan0.ToPointer();
	}

	else if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format24bppRgb)
	{
		tmp = cvCreateImage(cvSize(bitmap->Width, bitmap->Height), IPL_DEPTH_8U, 3);
		tmp->imageData = (char*)bmData->Scan0.ToPointer();
	}

	bitmap->UnlockBits(bmData);

	return cv::Mat(tmp);
}

System::Drawing::Bitmap^  ImageHelper::ImageControlProcess::MatToBitmap(cv::Mat srcImg){

	System::Drawing::Bitmap^ output;

	if (srcImg.channels() == 1)
	{
		cv::imwrite(imgProcess.tempFilePath, srcImg);
		srcImg = cv::imread(imgProcess.tempFilePath);
	}
	
	int stride = srcImg.size().width * srcImg.channels();//calc the srtide
	int hDataCount = srcImg.size().height;

	System::Drawing::Bitmap^ retImg;

	System::IntPtr ptr(srcImg.data);

	//create a pointer with Stride
	if (stride % 4 != 0){
		//is not stride a multiple of 4?
		//make it a multiple of 4 by fiiling an offset to the end of each row

		//to hold processed data
		uchar *dataPro = new uchar[((srcImg.size().width * srcImg.channels() + 3) & -4) * hDataCount];

		uchar *data = srcImg.ptr();

		//current position on the data array
		int curPosition = 0;
		//current offset
		int curOffset = 0;

		int offsetCounter = 0;

		//itterate through all the bytes on the structure
		for (int r = 0; r < hDataCount; r++){
			//fill the data
			for (int c = 0; c < stride; c++){
				curPosition = (r * stride) + c;

				dataPro[curPosition + curOffset] = data[curPosition];
			}

			//reset offset counter
			offsetCounter = stride;

			//fill the offset
			do{
				curOffset += 1;
				dataPro[curPosition + curOffset] = 0;

				offsetCounter += 1;
			} while (offsetCounter % 4 != 0);
		}

		ptr = (System::IntPtr)dataPro;//set the data pointer to new/modified data array

			//calc the stride to nearest number which is a multiply of 4
			stride = (srcImg.size().width * srcImg.channels() + 3) & -4;

			

	}
	array<unsigned char>^ imageData;

	
	retImg = gcnew System::Drawing::Bitmap(srcImg.size().width, srcImg.size().height,
		stride,
		System::Drawing::Imaging::PixelFormat::Format24bppRgb,
		ptr);




 
	 	// Create the byte array.

	 {
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream();
		retImg->Save(ms, System::Drawing::Imaging::ImageFormat::Jpeg);
		


		imageData = ms->ToArray();
		delete ms;
	}

	// Convert back to bitmap
	{
		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(imageData);
		output = (System::Drawing::Bitmap^)System::Drawing::Bitmap::FromStream(ms);
	}
 



	return output;

}

void ImageHelper::ImageControlProcess::ZoomImage(int sizeValue, Panel ^pbox) { 
	try
	{
		System::Drawing::Rectangle Rect_Pb1_ZoomSize ;

		Rect_Pb1_ZoomSize.Width  = pbox->Width;
		Rect_Pb1_ZoomSize.Height = pbox->Height;

		width = Rect_Pb1_ZoomSize.Width * sizeValue / 100;    // 将指定的值转换为32位元带正负号的整数。
		heigth = Rect_Pb1_ZoomSize.Height * sizeValue / 100;

		if (width < 1 || heigth < 1)
			return;

		Bitmap ^resizedBmp = gcnew Bitmap(width, heigth);
		Graphics ^g = Graphics::FromImage(resizedBmp);

		System::Drawing::Bitmap^ tempBitMap;
		cv::Mat showImg = imgProcess.originalImg.clone();
		imgProcess.originalImg.copyTo(showImg);
		tempBitMap = MatToBitmap(showImg);

		g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;  //插值模式设置：临近取样
		g->SmoothingMode     = System::Drawing::Drawing2D::SmoothingMode::None;                 //渲染图像质量，更平滑柔和

		RectangleF rectDst = RectangleF(0,0,width,heigth);
		RectangleF rectSrc = RectangleF(0,0,tempBitMap->Width,tempBitMap->Height);
		// 在指定位置并且按指定大小绘制指定的Image的指定部分.
		// srcRect 参数指定要绘制的 image 对象的矩形部分。 将此部分进行缩放以适合 destRect 参数所指定的矩形。
		g->DrawImage(tempBitMap, rectDst, rectSrc, GraphicsUnit::Pixel);
		// GraphicsUnit：指定给定数据的度量单位。以设备像素为单位。 

		int ww, hh;
		ww = width;
		hh = heigth;

		if (pbox->Width < ww)    // 显示空间宽度不够
		{
			ww = pbox->Width;
			hh = heigth * ww / width;
		}

		if(pbox->Height < hh)    // 显示空间长度不够
		{
			hh = pbox->Height;
			ww = hh * width / heigth;
		}

		RectangleF rectClone = RectangleF(begin_x, begin_y, ww, hh);

		Bitmap ^backgroundBmp = resizedBmp->Clone(rectClone,System::Drawing::Imaging::PixelFormat::Format24bppRgb);//在图片框上显示区域图片,指定格式24位

		pbox->BackgroundImage = backgroundBmp; 

		

		imgProcess.oprationState["scale"]  = true;
		imgProcess.lastChange = "缩放 ";

		imgProcess.lastChangeIndex.name = "scale";
		imgProcess.lastChangeIndex.detail = imgProcess.ConvertToString(sizeValue);

	}
	catch (System::Exception^ e)
	{
		return;
	}
}

void ImageHelper::ImageControlProcess::SaveOriginalImg(Panel^ panel){
	width = imgProcess.unchangeImg.cols;
	heigth = imgProcess.unchangeImg.rows;
    changeIndex tempChangeIndex;
	tempChangeIndex = imgProcess.changeIndexVec[imgProcess.changeIndexVec.size()-1];
	changeDetail currentChangeDetail;
	while(!(tempChangeIndex.currentImg == 0))//把从原图到当前图片的所有变化都压入栈中
	{
		currentChangeDetail.name = tempChangeIndex.name;
		currentChangeDetail.detail = tempChangeIndex.detail;
		changeDetailStack.push(currentChangeDetail);
		tempChangeIndex = imgProcess.changeIndexVec[tempChangeIndex.lastImg];
	}
	imgProcess.originalImg = imgProcess.unchangeImg.clone();
	imgProcess.unchangeImg.copyTo(imgProcess.originalImg);
	imgProcess.oprateImg = imgProcess.unchangeImg.clone();
	imgProcess.unchangeImg.copyTo(imgProcess.oprateImg);

	while(!changeDetailStack.empty())  //把所进行的变化依次出栈，对原图进行相应变化
	{
		currentChangeDetail = changeDetailStack.top();
		changeDetailStack.pop();
		if(currentChangeDetail.name == "contrast_bright"){
			
			SplitStr(currentChangeDetail.detail);
			imgProcess.imageState["contrast"] = atof(tempStr[0].c_str());
            imgProcess.imageState["bright"] = atof(tempStr[1].c_str());
			imgProcess.ContrastBrightChange();
		}
		else if(currentChangeDetail.name ==  "angle"){
			double angle =  atof(currentChangeDetail.detail.c_str());
			imgProcess.AngleChange(angle);
		}
		else if(currentChangeDetail.name == "gray"){
			imgProcess.GrayProcessing();
		}
		else if(currentChangeDetail.name == "canny"){
            double lowThreshold = atof(currentChangeDetail.detail.c_str());
			imgProcess.EdgeDetection(lowThreshold,0);
		}
		else if(currentChangeDetail.name == "laplace"){
            imgProcess.EdgeDetection(0,1);
		}
		else if(currentChangeDetail.name == "blur"){
			kernelLength = atof(currentChangeDetail.detail.c_str());
			imgProcess.Smoothing(0,kernelLength);
		}
		else if(currentChangeDetail.name == "gaussian"){
			kernelLength = atof(currentChangeDetail.detail.c_str());
			imgProcess.Smoothing(1,kernelLength);
		}
		else if(currentChangeDetail.name == "median"){
			kernelLength = atof(currentChangeDetail.detail.c_str());
			imgProcess.Smoothing(2,kernelLength);
		}

		else if(currentChangeDetail.name == "bilateral"){
			kernelLength = atof(currentChangeDetail.detail.c_str());
			imgProcess.Smoothing(3,kernelLength);
		}

		else if(currentChangeDetail.name == "binary"){
			threshold = atof(currentChangeDetail.detail.c_str());
			imgProcess.Threshold(0,threshold);
		}

		else if(currentChangeDetail.name == "antibinary"){
			threshold = atof(currentChangeDetail.detail.c_str());
			imgProcess.Threshold(1,threshold);
		}

		else if(currentChangeDetail.name == "interceptive"){
			threshold = atof(currentChangeDetail.detail.c_str());
			imgProcess.Threshold(2,threshold);
		}

		else if(currentChangeDetail.name == "zero"){
			threshold = atof(currentChangeDetail.detail.c_str());
			imgProcess.Threshold(3,threshold);
		}


		else if(currentChangeDetail.name == "antizero"){
			threshold = atof(currentChangeDetail.detail.c_str());
			imgProcess.Threshold(4,threshold);
		}

		else if(currentChangeDetail.name == "scale"){
			int sizeValue;
			
			sizeValue = atof(currentChangeDetail.detail.c_str());
			width = width * sizeValue / 100;
			heigth = heigth * sizeValue / 100;

		}


		
		imgProcess.originalImg = imgProcess.oprateImg.clone();
		imgProcess.oprateImg.copyTo(imgProcess.originalImg);

	}
	cv::Mat dst;
	cv::resize(imgProcess.originalImg,dst,cv::Size(width,heigth),0,0);
	cv::imwrite(unchangedImgPath,dst);
}

void ImageHelper::ImageControlProcess::SplitStr(std::string& src){
	tempStr.clear();
	int lastPosition = 0, index = -1;  
	while (-1 != (index = src.find(",", lastPosition)))  
	{  
		tempStr.push_back(src.substr(lastPosition, index - lastPosition));  
		lastPosition = index + 1;  
	}  
	std::string lastString = src.substr(lastPosition);  
	if (!lastString.empty())  
		tempStr.push_back(lastString);  
	return ; 
} 



