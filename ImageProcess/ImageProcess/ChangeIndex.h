
#pragma once
namespace ImageHelper {

struct changeIndex{
	int currentImg;//目前图片的编号
	int lastImg;//上一张图片的编号（标示当前图片是从哪一张图片变来的）
	std::string  name;//变化的名字
	std::string  detail;//变化的细节

};
}