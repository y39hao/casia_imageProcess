#pragma once

#include "stdafx.h"  
#include <sstream>
#include <string>  
#include <msclr\marshal_cppstd.h>  
#include <iostream> 
#include <windows.h>
#include "ShowImage.h"
#include "ImageControlProcess.h"
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ChangeIndex.h"
#include "LoadingForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace System::Text;
using namespace ImageHelper;
using namespace System::Threading;
using namespace System::Diagnostics;
//using namespace System::Runtime::InteropServices;
using namespace System::IO;

using namespace msclr::interop;  

static CImageShow imgShow;
static ImageHelper::ImageControlProcess imgProcessor;

namespace ImageProcess {

	/// <summary>
	/// Summary for ImageProcessControl
	/// </summary>
	public ref class ImageProcessControl : public System::Windows::Forms::UserControl
	{
	public:
		ImageProcessControl(void)
		{
			InitializeComponent();
			pnl_showImg->GetType()->GetProperty("DoubleBuffered",
				System::Reflection::BindingFlags::Instance | 
				System::Reflection::BindingFlags::NonPublic)->SetValue(pnl_showImg,true,nullptr);
			isApplyInitialChange = true; 
			imgProcessor.begin_x = 0;
			imgProcessor.begin_y = 0;
			isStarMove  = false;
			middle_x = pnl_showImg->Width/2;
			middle_y = pnl_showImg->Height/2;
			sizeWheelNum = 0;
			sizeSliderValue = 0;
			angleWheelNum = 0;
			contrastWheelNum = 100;
			brightWheelNum = 0;

			clickLock = gcnew Mutex();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ImageProcessControl()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  txtbx_thred;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: DevComponents::DotNetBar::LabelX^  labelX23;
	private: DevComponents::DotNetBar::Controls::ComboBoxEx^  combo_smoothingMethod;
	private: DevComponents::Editors::ComboItem^  Blur;
	private: DevComponents::Editors::ComboItem^  gaussianblur;
	private: DevComponents::Editors::ComboItem^  medianBlur;



	private: DevComponents::Editors::ComboItem^  bilateralFilter;
	private: System::Windows::Forms::Panel^  pnl_smooth;
	private: DevComponents::DotNetBar::Controls::TextBoxX^  txtbx_kernekLength;
	private: DevComponents::DotNetBar::LabelX^  labelX20;
	private: DevComponents::DotNetBar::SuperTabControlPanel^  superTabControlPanel8;
	private: DevComponents::DotNetBar::SuperTabItem^  tab_smooth;
	private: DevComponents::DotNetBar::SuperTabItem^  tab_threadhold;
	private: DevComponents::DotNetBar::SuperTabControlPanel^  superTabControlPanel9;
	private: System::Windows::Forms::Panel^  pnl_thred;
	private: DevComponents::DotNetBar::LabelX^  labelX22;
	private: DevComponents::DotNetBar::LabelX^  labelX21;
	private: DevComponents::DotNetBar::LabelX^  labelX19;
	private: DevComponents::DotNetBar::LabelX^  labelX18;
	private: DevComponents::DotNetBar::Controls::Slider^  slider_threshold;
	private: DevComponents::DotNetBar::Controls::ComboBoxEx^  combo_thresholdMethod;
	private: DevComponents::Editors::ComboItem^  comboItem1;
	private: DevComponents::Editors::ComboItem^  comboItem2;
	private: DevComponents::Editors::ComboItem^  comboItem3;
	private: DevComponents::Editors::ComboItem^  comboItem4;
	private: DevComponents::Editors::ComboItem^  comboItem5;
	private: System::Windows::Forms::Panel^  pnl_showHstgrm;
	private: DevComponents::DotNetBar::SuperTabItem^  superTabItem1;
	private: DevComponents::DotNetBar::SuperTabControlPanel^  superTabControlPanel2;
	private: DevComponents::DotNetBar::SuperTabItem^  superTabItem2;
	private: DevComponents::DotNetBar::SuperTabControlPanel^  superTabControlPanel3;
	private: System::Windows::Forms::Panel^  panel_fft;
	private: DevComponents::DotNetBar::SuperTabControl^  superTabControl1;
	private: DevComponents::DotNetBar::SuperTabItem^  tab_edgeDetctiom;
	private: DevComponents::DotNetBar::SuperTabControlPanel^  superTabControlPanel7;
	private: System::Windows::Forms::Panel^  pnl_edgeDect;
	private: System::Windows::Forms::Label^  label1;
	private: DevComponents::DotNetBar::LabelX^  labelX24;
	private: DevComponents::DotNetBar::Controls::ComboBoxEx^  combo_EdgeDtcMethod;
	private: DevComponents::Editors::ComboItem^  Canny;
	private: DevComponents::Editors::ComboItem^  LapLace;
	private: DevComponents::DotNetBar::Controls::TextBoxX^  txtbx_lowThreshold;
	private: DevComponents::DotNetBar::LabelX^  labelX25;
	private: System::Windows::Forms::Panel^  pnl_size;
	private: DevComponents::DotNetBar::LabelX^  labelX12;
	private: System::Windows::Forms::TextBox^  txtbx_size;
	private: DevComponents::DotNetBar::LabelX^  labelX16;
	private: DevComponents::DotNetBar::LabelX^  labelX13;
	private: DevComponents::DotNetBar::Controls::Slider^  slider_size;
	private: DevComponents::DotNetBar::SuperTabControl^  tabControl;
	private: DevComponents::DotNetBar::SuperTabControlPanel^  superTabControlPanel6;
	private: DevComponents::DotNetBar::SuperTabItem^  tab_size;
	private: DevComponents::DotNetBar::SuperTabControlPanel^  superTabControlPanel10;
	private: System::Windows::Forms::Panel^  pnl_contrastBright;
	private: System::Windows::Forms::TextBox^  txtbx_bright;
	private: System::Windows::Forms::TextBox^  txtbx_contrast;
	private: DevComponents::DotNetBar::LabelX^  labelX11;
	private: DevComponents::DotNetBar::LabelX^  labelX10;
	private: DevComponents::DotNetBar::LabelX^  labelX9;
	private: DevComponents::DotNetBar::LabelX^  labelX8;
	private: DevComponents::DotNetBar::LabelX^  labelX7;
	private: DevComponents::DotNetBar::LabelX^  labelX6;
	private: DevComponents::DotNetBar::Controls::Slider^  slider_bright;
	private: DevComponents::DotNetBar::Controls::Slider^  slider_contrast;
	private: DevComponents::DotNetBar::SuperTabItem^  tab_contrastBringht;
	private: DevComponents::DotNetBar::SuperTabControlPanel^  superTabControlPanel1;
	private: System::Windows::Forms::Panel^  pnl_angle;
	private: System::Windows::Forms::TextBox^  txtBx_ang;
	private: DevComponents::DotNetBar::LabelX^  labelX15;
	private: DevComponents::DotNetBar::Controls::Slider^  slider_angle;
	private: DevComponents::DotNetBar::LabelX^  labelX17;
	private: DevComponents::DotNetBar::LabelX^  labelX14;
	private: DevComponents::DotNetBar::SuperTabItem^  tab_angle;
	private: System::Windows::Forms::Button^  btn_gray;
	private: System::Windows::Forms::Button^  btn_apply;
	private: System::Windows::Forms::ListView^  lstView_historyList;
	private: System::Windows::Forms::ImageList^  historyImgList;

	private: System::Windows::Forms::Panel^  pnl_showImg;
	private: System::Windows::Forms::Button^  btn_save;
	private: System::Windows::Forms::Button^  btn_open;
	private: System::Windows::Forms::Panel^  pnl_MainPanel;
	private: System::ComponentModel::IContainer^  components;

	public:  
		bool isApplyInitialChange;//清空txtbox,slider归位标志
		bool  isStarMove; //光标是否拖动图片标志
		System::Drawing::Point moveStarPoint ;//光标拖动图片移动的起始点
		System::Drawing::Point m_CurrentPoint ;//光标现在所处的位置

		float middle_x;//显示图片区域中心点的横坐标
		float middle_y;//显示图片区域中心点的纵坐标
		int sizeWheelNum;//调整大小时滚轮滚动的值

		int sizeSliderValue;//slider_size的值
		int angleWheelNum; //调整角度时滚轮滚动的值
		int contrastWheelNum;//调整对比度时滚轮滚动的值
		LoadingForm loadingForm;
		bool isClick;

		Mutex^ clickLock;    // 打开图片图片时防止Panel点击事件触发的锁
	private: DevComponents::DotNetBar::LabelX^  labelX2;
	public: 
	private: DevComponents::DotNetBar::Controls::Line^  line2;
	private: DevComponents::DotNetBar::LabelX^  labelX1;
	private: DevComponents::DotNetBar::Controls::Line^  line1;
	private: DevComponents::DotNetBar::Controls::Line^  line4;
	private: DevComponents::DotNetBar::Controls::Line^  line3;
	private: DevComponents::DotNetBar::Controls::Line^  line6;
	private: DevComponents::DotNetBar::Controls::Line^  line5;
	private: DevComponents::DotNetBar::LabelX^  labelX3;
	private: DevComponents::DotNetBar::LabelX^  labelX4;
	private: DevComponents::DotNetBar::LabelX^  labelX5;
	private: DevComponents::DotNetBar::LabelX^  labelX26;
	private: DevComponents::DotNetBar::ExpandablePanel^  exPnl_showHistory;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  btn_export;
	private: System::ComponentModel::BackgroundWorker^  BGW_export;


			 int brightWheelNum;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ImageProcessControl::typeid));
			this->historyImgList = (gcnew System::Windows::Forms::ImageList(this->components));
			this->btn_open = (gcnew System::Windows::Forms::Button());
			this->btn_save = (gcnew System::Windows::Forms::Button());
			this->pnl_showImg = (gcnew System::Windows::Forms::Panel());
			this->pnl_angle = (gcnew System::Windows::Forms::Panel());
			this->labelX3 = (gcnew DevComponents::DotNetBar::LabelX());
			this->line4 = (gcnew DevComponents::DotNetBar::Controls::Line());
			this->txtBx_ang = (gcnew System::Windows::Forms::TextBox());
			this->labelX15 = (gcnew DevComponents::DotNetBar::LabelX());
			this->slider_angle = (gcnew DevComponents::DotNetBar::Controls::Slider());
			this->labelX17 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX14 = (gcnew DevComponents::DotNetBar::LabelX());
			this->panel_fft = (gcnew System::Windows::Forms::Panel());
			this->lstView_historyList = (gcnew System::Windows::Forms::ListView());
			this->btn_apply = (gcnew System::Windows::Forms::Button());
			this->btn_gray = (gcnew System::Windows::Forms::Button());
			this->tabControl = (gcnew DevComponents::DotNetBar::SuperTabControl());
			this->superTabControlPanel8 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->pnl_smooth = (gcnew System::Windows::Forms::Panel());
			this->labelX26 = (gcnew DevComponents::DotNetBar::LabelX());
			this->line6 = (gcnew DevComponents::DotNetBar::Controls::Line());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->labelX23 = (gcnew DevComponents::DotNetBar::LabelX());
			this->combo_smoothingMethod = (gcnew DevComponents::DotNetBar::Controls::ComboBoxEx());
			this->Blur = (gcnew DevComponents::Editors::ComboItem());
			this->gaussianblur = (gcnew DevComponents::Editors::ComboItem());
			this->medianBlur = (gcnew DevComponents::Editors::ComboItem());
			this->bilateralFilter = (gcnew DevComponents::Editors::ComboItem());
			this->txtbx_kernekLength = (gcnew DevComponents::DotNetBar::Controls::TextBoxX());
			this->labelX20 = (gcnew DevComponents::DotNetBar::LabelX());
			this->tab_smooth = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->superTabControlPanel9 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->pnl_thred = (gcnew System::Windows::Forms::Panel());
			this->labelX5 = (gcnew DevComponents::DotNetBar::LabelX());
			this->line3 = (gcnew DevComponents::DotNetBar::Controls::Line());
			this->txtbx_thred = (gcnew System::Windows::Forms::TextBox());
			this->labelX22 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX21 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX19 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX18 = (gcnew DevComponents::DotNetBar::LabelX());
			this->slider_threshold = (gcnew DevComponents::DotNetBar::Controls::Slider());
			this->combo_thresholdMethod = (gcnew DevComponents::DotNetBar::Controls::ComboBoxEx());
			this->comboItem1 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem2 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem3 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem4 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem5 = (gcnew DevComponents::Editors::ComboItem());
			this->tab_threadhold = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->superTabControlPanel6 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->pnl_size = (gcnew System::Windows::Forms::Panel());
			this->labelX2 = (gcnew DevComponents::DotNetBar::LabelX());
			this->line2 = (gcnew DevComponents::DotNetBar::Controls::Line());
			this->labelX12 = (gcnew DevComponents::DotNetBar::LabelX());
			this->txtbx_size = (gcnew System::Windows::Forms::TextBox());
			this->labelX16 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX13 = (gcnew DevComponents::DotNetBar::LabelX());
			this->slider_size = (gcnew DevComponents::DotNetBar::Controls::Slider());
			this->tab_size = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->superTabControlPanel7 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->pnl_edgeDect = (gcnew System::Windows::Forms::Panel());
			this->labelX1 = (gcnew DevComponents::DotNetBar::LabelX());
			this->line1 = (gcnew DevComponents::DotNetBar::Controls::Line());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labelX24 = (gcnew DevComponents::DotNetBar::LabelX());
			this->combo_EdgeDtcMethod = (gcnew DevComponents::DotNetBar::Controls::ComboBoxEx());
			this->Canny = (gcnew DevComponents::Editors::ComboItem());
			this->LapLace = (gcnew DevComponents::Editors::ComboItem());
			this->txtbx_lowThreshold = (gcnew DevComponents::DotNetBar::Controls::TextBoxX());
			this->labelX25 = (gcnew DevComponents::DotNetBar::LabelX());
			this->tab_edgeDetctiom = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->superTabControlPanel1 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->tab_angle = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->superTabControlPanel10 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->pnl_contrastBright = (gcnew System::Windows::Forms::Panel());
			this->labelX4 = (gcnew DevComponents::DotNetBar::LabelX());
			this->line5 = (gcnew DevComponents::DotNetBar::Controls::Line());
			this->txtbx_bright = (gcnew System::Windows::Forms::TextBox());
			this->txtbx_contrast = (gcnew System::Windows::Forms::TextBox());
			this->labelX11 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX10 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX9 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX8 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX7 = (gcnew DevComponents::DotNetBar::LabelX());
			this->labelX6 = (gcnew DevComponents::DotNetBar::LabelX());
			this->slider_bright = (gcnew DevComponents::DotNetBar::Controls::Slider());
			this->slider_contrast = (gcnew DevComponents::DotNetBar::Controls::Slider());
			this->tab_contrastBringht = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->superTabControl1 = (gcnew DevComponents::DotNetBar::SuperTabControl());
			this->superTabControlPanel2 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->pnl_showHstgrm = (gcnew System::Windows::Forms::Panel());
			this->superTabItem1 = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->superTabControlPanel3 = (gcnew DevComponents::DotNetBar::SuperTabControlPanel());
			this->superTabItem2 = (gcnew DevComponents::DotNetBar::SuperTabItem());
			this->pnl_MainPanel = (gcnew System::Windows::Forms::Panel());
			this->btn_export = (gcnew System::Windows::Forms::Button());
			this->exPnl_showHistory = (gcnew DevComponents::DotNetBar::ExpandablePanel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->BGW_export = (gcnew System::ComponentModel::BackgroundWorker());
			this->pnl_angle->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tabControl))->BeginInit();
			this->tabControl->SuspendLayout();
			this->superTabControlPanel8->SuspendLayout();
			this->pnl_smooth->SuspendLayout();
			this->superTabControlPanel9->SuspendLayout();
			this->pnl_thred->SuspendLayout();
			this->superTabControlPanel6->SuspendLayout();
			this->pnl_size->SuspendLayout();
			this->superTabControlPanel7->SuspendLayout();
			this->pnl_edgeDect->SuspendLayout();
			this->superTabControlPanel1->SuspendLayout();
			this->superTabControlPanel10->SuspendLayout();
			this->pnl_contrastBright->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->superTabControl1))->BeginInit();
			this->superTabControl1->SuspendLayout();
			this->superTabControlPanel2->SuspendLayout();
			this->superTabControlPanel3->SuspendLayout();
			this->pnl_MainPanel->SuspendLayout();
			this->exPnl_showHistory->SuspendLayout();
			this->SuspendLayout();
			// 
			// historyImgList
			// 
			this->historyImgList->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
			this->historyImgList->ImageSize = System::Drawing::Size(100, 75);
			this->historyImgList->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// btn_open
			// 
			this->btn_open->BackColor = System::Drawing::Color::SteelBlue;
			this->btn_open->ForeColor = System::Drawing::Color::Transparent;
			this->btn_open->Location = System::Drawing::Point(14, 685);
			this->btn_open->Name = L"btn_open";
			this->btn_open->Size = System::Drawing::Size(139, 59);
			this->btn_open->TabIndex = 1;
			this->btn_open->Text = L"打开";
			this->btn_open->UseVisualStyleBackColor = false;
			this->btn_open->Click += gcnew System::EventHandler(this, &ImageProcessControl::btn_open_Click);
			// 
			// btn_save
			// 
			this->btn_save->BackColor = System::Drawing::Color::SteelBlue;
			this->btn_save->Enabled = false;
			this->btn_save->ForeColor = System::Drawing::Color::Transparent;
			this->btn_save->Location = System::Drawing::Point(207, 684);
			this->btn_save->Name = L"btn_save";
			this->btn_save->Size = System::Drawing::Size(139, 59);
			this->btn_save->TabIndex = 2;
			this->btn_save->Text = L"保存";
			this->btn_save->UseVisualStyleBackColor = false;
			this->btn_save->Click += gcnew System::EventHandler(this, &ImageProcessControl::btn_save_Click);
			// 
			// pnl_showImg
			// 
			this->pnl_showImg->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pnl_showImg->Location = System::Drawing::Point(396, 87);
			this->pnl_showImg->Name = L"pnl_showImg";
			this->pnl_showImg->Size = System::Drawing::Size(994, 728);
			this->pnl_showImg->TabIndex = 7;
			this->pnl_showImg->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::pnl_showImg_MouseDown);
			this->pnl_showImg->MouseHover += gcnew System::EventHandler(this, &ImageProcessControl::pnl_showImg_MouseHover);
			this->pnl_showImg->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::pnl_showImg_MouseMove);
			this->pnl_showImg->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::pnl_showImg_MouseUp);
			this->pnl_showImg->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::pnl_showImg_MouseWheel);
			// 
			// pnl_angle
			// 
			this->pnl_angle->BackColor = System::Drawing::Color::SteelBlue;
			this->pnl_angle->Controls->Add(this->labelX3);
			this->pnl_angle->Controls->Add(this->line4);
			this->pnl_angle->Controls->Add(this->txtBx_ang);
			this->pnl_angle->Controls->Add(this->labelX15);
			this->pnl_angle->Controls->Add(this->slider_angle);
			this->pnl_angle->Controls->Add(this->labelX17);
			this->pnl_angle->Controls->Add(this->labelX14);
			this->pnl_angle->Location = System::Drawing::Point(1, 0);
			this->pnl_angle->Name = L"pnl_angle";
			this->pnl_angle->Size = System::Drawing::Size(262, 315);
			this->pnl_angle->TabIndex = 0;
			// 
			// labelX3
			// 
			// 
			// 
			// 
			this->labelX3->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX3->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15));
			this->labelX3->ForeColor = System::Drawing::Color::White;
			this->labelX3->Location = System::Drawing::Point(21, 14);
			this->labelX3->Name = L"labelX3";
			this->labelX3->Size = System::Drawing::Size(75, 23);
			this->labelX3->TabIndex = 14;
			this->labelX3->Text = L"旋转";
			// 
			// line4
			// 
			this->line4->Location = System::Drawing::Point(0, 40);
			this->line4->Name = L"line4";
			this->line4->Size = System::Drawing::Size(262, 23);
			this->line4->TabIndex = 13;
			this->line4->Text = L"line4";
			// 
			// txtBx_ang
			// 
			this->txtBx_ang->Enabled = false;
			this->txtBx_ang->Location = System::Drawing::Point(215, 178);
			this->txtBx_ang->Name = L"txtBx_ang";
			this->txtBx_ang->Size = System::Drawing::Size(36, 21);
			this->txtBx_ang->TabIndex = 12;
			this->txtBx_ang->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ImageProcessControl::txtBx_ang_KeyDown);
			// 
			// labelX15
			// 
			// 
			// 
			// 
			this->labelX15->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX15->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX15->ForeColor = System::Drawing::Color::White;
			this->labelX15->Location = System::Drawing::Point(3, 154);
			this->labelX15->Name = L"labelX15";
			this->labelX15->Size = System::Drawing::Size(54, 23);
			this->labelX15->TabIndex = 7;
			this->labelX15->Text = L"-180";
			// 
			// slider_angle
			// 
			// 
			// 
			// 
			this->slider_angle->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->slider_angle->Enabled = false;
			this->slider_angle->Location = System::Drawing::Point(-26, 178);
			this->slider_angle->Maximum = 180;
			this->slider_angle->Minimum = -180;
			this->slider_angle->Name = L"slider_angle";
			this->slider_angle->Size = System::Drawing::Size(227, 26);
			this->slider_angle->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->slider_angle->TabIndex = 1;
			this->slider_angle->Value = 0;
			this->slider_angle->ValueChanged += gcnew System::EventHandler(this, &ImageProcessControl::slider_angle_ValueChanged);
			this->slider_angle->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::slider_angle_MouseWheel);
			// 
			// labelX17
			// 
			// 
			// 
			// 
			this->labelX17->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX17->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX17->ForeColor = System::Drawing::Color::White;
			this->labelX17->Location = System::Drawing::Point(12, 104);
			this->labelX17->Name = L"labelX17";
			this->labelX17->Size = System::Drawing::Size(104, 23);
			this->labelX17->TabIndex = 9;
			this->labelX17->Text = L"旋转角度：";
			// 
			// labelX14
			// 
			// 
			// 
			// 
			this->labelX14->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX14->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX14->ForeColor = System::Drawing::Color::White;
			this->labelX14->Location = System::Drawing::Point(174, 154);
			this->labelX14->Name = L"labelX14";
			this->labelX14->Size = System::Drawing::Size(44, 23);
			this->labelX14->TabIndex = 6;
			this->labelX14->Text = L"180";
			// 
			// panel_fft
			// 
			this->panel_fft->Location = System::Drawing::Point(1, -1);
			this->panel_fft->Name = L"panel_fft";
			this->panel_fft->Size = System::Drawing::Size(331, 264);
			this->panel_fft->TabIndex = 14;
			this->panel_fft->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ImageProcessControl::panel_fft_Paint);
			// 
			// lstView_historyList
			// 
			this->lstView_historyList->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->lstView_historyList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lstView_historyList->ForeColor = System::Drawing::Color::White;
			this->lstView_historyList->LabelWrap = false;
			this->lstView_historyList->LargeImageList = this->historyImgList;
			this->lstView_historyList->Location = System::Drawing::Point(0, 35);
			this->lstView_historyList->MultiSelect = false;
			this->lstView_historyList->Name = L"lstView_historyList";
			this->lstView_historyList->Size = System::Drawing::Size(35, 778);
			this->lstView_historyList->TabIndex = 0;
			this->lstView_historyList->UseCompatibleStateImageBehavior = false;
			this->lstView_historyList->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::lstView_historyList_MouseClick);
			// 
			// btn_apply
			// 
			this->btn_apply->BackColor = System::Drawing::Color::SteelBlue;
			this->btn_apply->Enabled = false;
			this->btn_apply->ForeColor = System::Drawing::Color::Transparent;
			this->btn_apply->Location = System::Drawing::Point(13, 749);
			this->btn_apply->Name = L"btn_apply";
			this->btn_apply->Size = System::Drawing::Size(139, 59);
			this->btn_apply->TabIndex = 13;
			this->btn_apply->Text = L"应用变化";
			this->btn_apply->UseVisualStyleBackColor = false;
			this->btn_apply->Click += gcnew System::EventHandler(this, &ImageProcessControl::applyChange_Click);
			// 
			// btn_gray
			// 
			this->btn_gray->BackColor = System::Drawing::Color::SteelBlue;
			this->btn_gray->Enabled = false;
			this->btn_gray->ForeColor = System::Drawing::Color::White;
			this->btn_gray->Location = System::Drawing::Point(208, 749);
			this->btn_gray->Name = L"btn_gray";
			this->btn_gray->Size = System::Drawing::Size(139, 59);
			this->btn_gray->TabIndex = 6;
			this->btn_gray->Text = L"灰度图";
			this->btn_gray->UseVisualStyleBackColor = false;
			this->btn_gray->Click += gcnew System::EventHandler(this, &ImageProcessControl::grayProcess_Click);
			// 
			// tabControl
			// 
			// 
			// 
			// 
			// 
			// 
			// 
			this->tabControl->ControlBox->CloseBox->Name = L"";
			// 
			// 
			// 
			this->tabControl->ControlBox->MenuBox->Name = L"";
			this->tabControl->ControlBox->Name = L"";
			this->tabControl->ControlBox->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->tabControl->ControlBox->MenuBox, 
				this->tabControl->ControlBox->CloseBox});
			this->tabControl->Controls->Add(this->superTabControlPanel6);
			this->tabControl->Controls->Add(this->superTabControlPanel8);
			this->tabControl->Controls->Add(this->superTabControlPanel9);
			this->tabControl->Controls->Add(this->superTabControlPanel7);
			this->tabControl->Controls->Add(this->superTabControlPanel1);
			this->tabControl->Controls->Add(this->superTabControlPanel10);
			this->tabControl->Location = System::Drawing::Point(13, 48);
			this->tabControl->Name = L"tabControl";
			this->tabControl->ReorderTabsEnabled = true;
			this->tabControl->SelectedTabFont = (gcnew System::Drawing::Font(L"SimSun", 9, System::Drawing::FontStyle::Bold));
			this->tabControl->SelectedTabIndex = 4;
			this->tabControl->Size = System::Drawing::Size(333, 315);
			this->tabControl->TabAlignment = DevComponents::DotNetBar::eTabStripAlignment::Left;
			this->tabControl->TabFont = (gcnew System::Drawing::Font(L"SimSun", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->tabControl->TabIndex = 8;
			this->tabControl->Tabs->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(6) {this->tab_size, this->tab_angle, 
				this->tab_contrastBringht, this->tab_threadhold, this->tab_smooth, this->tab_edgeDetctiom});
			this->tabControl->SelectedTabChanged += gcnew System::EventHandler<DevComponents::DotNetBar::SuperTabStripSelectedTabChangedEventArgs^ >(this, &ImageProcessControl::tabControl_SelectedTabChanged);
			// 
			// superTabControlPanel8
			// 
			this->superTabControlPanel8->Controls->Add(this->pnl_smooth);
			this->superTabControlPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->superTabControlPanel8->Location = System::Drawing::Point(68, 0);
			this->superTabControlPanel8->Name = L"superTabControlPanel8";
			this->superTabControlPanel8->Size = System::Drawing::Size(265, 315);
			this->superTabControlPanel8->TabIndex = 0;
			this->superTabControlPanel8->TabItem = this->tab_smooth;
			// 
			// pnl_smooth
			// 
			this->pnl_smooth->BackColor = System::Drawing::Color::SteelBlue;
			this->pnl_smooth->Controls->Add(this->labelX26);
			this->pnl_smooth->Controls->Add(this->line6);
			this->pnl_smooth->Controls->Add(this->label2);
			this->pnl_smooth->Controls->Add(this->labelX23);
			this->pnl_smooth->Controls->Add(this->combo_smoothingMethod);
			this->pnl_smooth->Controls->Add(this->txtbx_kernekLength);
			this->pnl_smooth->Controls->Add(this->labelX20);
			this->pnl_smooth->Location = System::Drawing::Point(1, 0);
			this->pnl_smooth->Name = L"pnl_smooth";
			this->pnl_smooth->Size = System::Drawing::Size(262, 315);
			this->pnl_smooth->TabIndex = 2;
			// 
			// labelX26
			// 
			// 
			// 
			// 
			this->labelX26->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX26->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15));
			this->labelX26->ForeColor = System::Drawing::Color::White;
			this->labelX26->Location = System::Drawing::Point(21, 14);
			this->labelX26->Name = L"labelX26";
			this->labelX26->Size = System::Drawing::Size(104, 23);
			this->labelX26->TabIndex = 8;
			this->labelX26->Text = L"图像平滑";
			// 
			// line6
			// 
			this->line6->Location = System::Drawing::Point(0, 40);
			this->line6->Name = L"line6";
			this->line6->Size = System::Drawing::Size(262, 23);
			this->line6->TabIndex = 7;
			this->line6->Text = L"line6";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(76, 230);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(167, 12);
			this->label2->TabIndex = 6;
			this->label2->Text = L"* kernellength的范围是0到50";
			// 
			// labelX23
			// 
			// 
			// 
			// 
			this->labelX23->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX23->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX23->ForeColor = System::Drawing::Color::White;
			this->labelX23->Location = System::Drawing::Point(15, 126);
			this->labelX23->Name = L"labelX23";
			this->labelX23->Size = System::Drawing::Size(110, 23);
			this->labelX23->TabIndex = 5;
			this->labelX23->Text = L"处理方法 ：";
			// 
			// combo_smoothingMethod
			// 
			this->combo_smoothingMethod->DisplayMember = L"Text";
			this->combo_smoothingMethod->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
			this->combo_smoothingMethod->Enabled = false;
			this->combo_smoothingMethod->FormattingEnabled = true;
			this->combo_smoothingMethod->ItemHeight = 15;
			this->combo_smoothingMethod->Items->AddRange(gcnew cli::array< System::Object^  >(4) {this->Blur, this->gaussianblur, this->medianBlur, 
				this->bilateralFilter});
			this->combo_smoothingMethod->Location = System::Drawing::Point(143, 126);
			this->combo_smoothingMethod->Name = L"combo_smoothingMethod";
			this->combo_smoothingMethod->Size = System::Drawing::Size(100, 21);
			this->combo_smoothingMethod->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->combo_smoothingMethod->TabIndex = 0;
			this->combo_smoothingMethod->SelectedIndexChanged += gcnew System::EventHandler(this, &ImageProcessControl::smoothingMethod_SelectedIndexChanged);
			// 
			// Blur
			// 
			this->Blur->Text = L"均值滤波";
			// 
			// gaussianblur
			// 
			this->gaussianblur->Text = L"高斯滤波";
			// 
			// medianBlur
			// 
			this->medianBlur->Text = L"中值滤波";
			// 
			// bilateralFilter
			// 
			this->bilateralFilter->Text = L"双边滤波";
			// 
			// txtbx_kernekLength
			// 
			// 
			// 
			// 
			this->txtbx_kernekLength->Border->Class = L"TextBoxBorder";
			this->txtbx_kernekLength->Border->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->txtbx_kernekLength->Enabled = false;
			this->txtbx_kernekLength->Location = System::Drawing::Point(143, 186);
			this->txtbx_kernekLength->Name = L"txtbx_kernekLength";
			this->txtbx_kernekLength->Size = System::Drawing::Size(100, 21);
			this->txtbx_kernekLength->TabIndex = 1;
			this->txtbx_kernekLength->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ImageProcessControl::kernekLength_KeyDown);
			// 
			// labelX20
			// 
			// 
			// 
			// 
			this->labelX20->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX20->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX20->ForeColor = System::Drawing::Color::White;
			this->labelX20->Location = System::Drawing::Point(15, 186);
			this->labelX20->Name = L"labelX20";
			this->labelX20->Size = System::Drawing::Size(122, 23);
			this->labelX20->TabIndex = 4;
			this->labelX20->Text = L"KernelLength :";
			// 
			// tab_smooth
			// 
			this->tab_smooth->AttachedControl = this->superTabControlPanel8;
			this->tab_smooth->Description = L"图象平滑";
			this->tab_smooth->GlobalItem = false;
			this->tab_smooth->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tab_smooth.Image")));
			this->tab_smooth->Name = L"tab_smooth";
			this->tab_smooth->Tooltip = L"图像平滑";
			// 
			// superTabControlPanel9
			// 
			this->superTabControlPanel9->Controls->Add(this->pnl_thred);
			this->superTabControlPanel9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->superTabControlPanel9->Location = System::Drawing::Point(68, 0);
			this->superTabControlPanel9->Name = L"superTabControlPanel9";
			this->superTabControlPanel9->Size = System::Drawing::Size(265, 315);
			this->superTabControlPanel9->TabIndex = 0;
			this->superTabControlPanel9->TabItem = this->tab_threadhold;
			// 
			// pnl_thred
			// 
			this->pnl_thred->BackColor = System::Drawing::Color::SteelBlue;
			this->pnl_thred->Controls->Add(this->labelX5);
			this->pnl_thred->Controls->Add(this->line3);
			this->pnl_thred->Controls->Add(this->txtbx_thred);
			this->pnl_thred->Controls->Add(this->labelX22);
			this->pnl_thred->Controls->Add(this->labelX21);
			this->pnl_thred->Controls->Add(this->labelX19);
			this->pnl_thred->Controls->Add(this->labelX18);
			this->pnl_thred->Controls->Add(this->slider_threshold);
			this->pnl_thred->Controls->Add(this->combo_thresholdMethod);
			this->pnl_thred->Location = System::Drawing::Point(1, 0);
			this->pnl_thred->Name = L"pnl_thred";
			this->pnl_thred->Size = System::Drawing::Size(262, 315);
			this->pnl_thred->TabIndex = 3;
			// 
			// labelX5
			// 
			// 
			// 
			// 
			this->labelX5->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX5->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15));
			this->labelX5->ForeColor = System::Drawing::Color::White;
			this->labelX5->Location = System::Drawing::Point(21, 14);
			this->labelX5->Name = L"labelX5";
			this->labelX5->Size = System::Drawing::Size(103, 23);
			this->labelX5->TabIndex = 11;
			this->labelX5->Text = L"阈值变换";
			// 
			// line3
			// 
			this->line3->Location = System::Drawing::Point(0, 40);
			this->line3->Name = L"line3";
			this->line3->Size = System::Drawing::Size(262, 23);
			this->line3->TabIndex = 10;
			this->line3->Text = L"line3";
			// 
			// txtbx_thred
			// 
			this->txtbx_thred->Enabled = false;
			this->txtbx_thred->Location = System::Drawing::Point(214, 230);
			this->txtbx_thred->Name = L"txtbx_thred";
			this->txtbx_thred->Size = System::Drawing::Size(36, 21);
			this->txtbx_thred->TabIndex = 9;
			this->txtbx_thred->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ImageProcessControl::txtbx_thred_KeyDown);
			// 
			// labelX22
			// 
			// 
			// 
			// 
			this->labelX22->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX22->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX22->ForeColor = System::Drawing::Color::White;
			this->labelX22->Location = System::Drawing::Point(15, 126);
			this->labelX22->Name = L"labelX22";
			this->labelX22->Size = System::Drawing::Size(98, 23);
			this->labelX22->TabIndex = 7;
			this->labelX22->Text = L"处理方法 ：";
			// 
			// labelX21
			// 
			// 
			// 
			// 
			this->labelX21->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX21->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX21->ForeColor = System::Drawing::Color::White;
			this->labelX21->Location = System::Drawing::Point(18, 174);
			this->labelX21->Name = L"labelX21";
			this->labelX21->Size = System::Drawing::Size(48, 23);
			this->labelX21->TabIndex = 6;
			this->labelX21->Text = L"阈值 :";
			// 
			// labelX19
			// 
			// 
			// 
			// 
			this->labelX19->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX19->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->labelX19->ForeColor = System::Drawing::Color::White;
			this->labelX19->Location = System::Drawing::Point(180, 212);
			this->labelX19->Name = L"labelX19";
			this->labelX19->Size = System::Drawing::Size(40, 23);
			this->labelX19->TabIndex = 5;
			this->labelX19->Text = L"255";
			// 
			// labelX18
			// 
			// 
			// 
			// 
			this->labelX18->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX18->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->labelX18->ForeColor = System::Drawing::Color::White;
			this->labelX18->Location = System::Drawing::Point(15, 211);
			this->labelX18->Name = L"labelX18";
			this->labelX18->Size = System::Drawing::Size(22, 23);
			this->labelX18->TabIndex = 4;
			this->labelX18->Text = L"0";
			// 
			// slider_threshold
			// 
			// 
			// 
			// 
			this->slider_threshold->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->slider_threshold->Enabled = false;
			this->slider_threshold->Location = System::Drawing::Point(-24, 233);
			this->slider_threshold->Maximum = 255;
			this->slider_threshold->Name = L"slider_threshold";
			this->slider_threshold->Size = System::Drawing::Size(227, 23);
			this->slider_threshold->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->slider_threshold->TabIndex = 1;
			this->slider_threshold->Value = 0;
			this->slider_threshold->ValueChanged += gcnew System::EventHandler(this, &ImageProcessControl::threshold_slider_ValueChanged);
			// 
			// combo_thresholdMethod
			// 
			this->combo_thresholdMethod->DisplayMember = L"Text";
			this->combo_thresholdMethod->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
			this->combo_thresholdMethod->Enabled = false;
			this->combo_thresholdMethod->FormattingEnabled = true;
			this->combo_thresholdMethod->ItemHeight = 15;
			this->combo_thresholdMethod->Items->AddRange(gcnew cli::array< System::Object^  >(5) {this->comboItem1, this->comboItem2, 
				this->comboItem3, this->comboItem4, this->comboItem5});
			this->combo_thresholdMethod->Location = System::Drawing::Point(119, 126);
			this->combo_thresholdMethod->Name = L"combo_thresholdMethod";
			this->combo_thresholdMethod->Size = System::Drawing::Size(109, 21);
			this->combo_thresholdMethod->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->combo_thresholdMethod->TabIndex = 0;
			this->combo_thresholdMethod->SelectedIndexChanged += gcnew System::EventHandler(this, &ImageProcessControl::thresholdMethod_SelectedIndexChanged);
			// 
			// comboItem1
			// 
			this->comboItem1->Text = L"二进制阈值";
			// 
			// comboItem2
			// 
			this->comboItem2->Text = L"反二进制阈值";
			// 
			// comboItem3
			// 
			this->comboItem3->Text = L"阶段阈值";
			// 
			// comboItem4
			// 
			this->comboItem4->Text = L"零阈值";
			// 
			// comboItem5
			// 
			this->comboItem5->Text = L"反零阈值";
			// 
			// tab_threadhold
			// 
			this->tab_threadhold->AttachedControl = this->superTabControlPanel9;
			this->tab_threadhold->Description = L"阈值";
			this->tab_threadhold->GlobalItem = false;
			this->tab_threadhold->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tab_threadhold.Image")));
			this->tab_threadhold->Name = L"tab_threadhold";
			this->tab_threadhold->Tooltip = L"阈值变换";
			// 
			// superTabControlPanel6
			// 
			this->superTabControlPanel6->Controls->Add(this->pnl_size);
			this->superTabControlPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->superTabControlPanel6->Location = System::Drawing::Point(68, 0);
			this->superTabControlPanel6->Name = L"superTabControlPanel6";
			this->superTabControlPanel6->Size = System::Drawing::Size(265, 315);
			this->superTabControlPanel6->TabIndex = 1;
			this->superTabControlPanel6->TabItem = this->tab_size;
			// 
			// pnl_size
			// 
			this->pnl_size->BackColor = System::Drawing::Color::SteelBlue;
			this->pnl_size->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pnl_size->Controls->Add(this->labelX2);
			this->pnl_size->Controls->Add(this->line2);
			this->pnl_size->Controls->Add(this->labelX12);
			this->pnl_size->Controls->Add(this->txtbx_size);
			this->pnl_size->Controls->Add(this->labelX16);
			this->pnl_size->Controls->Add(this->labelX13);
			this->pnl_size->Controls->Add(this->slider_size);
			this->pnl_size->Location = System::Drawing::Point(1, 0);
			this->pnl_size->Name = L"pnl_size";
			this->pnl_size->Size = System::Drawing::Size(262, 315);
			this->pnl_size->TabIndex = 0;
			// 
			// labelX2
			// 
			// 
			// 
			// 
			this->labelX2->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX2->ForeColor = System::Drawing::Color::White;
			this->labelX2->Location = System::Drawing::Point(12, 104);
			this->labelX2->Name = L"labelX2";
			this->labelX2->Size = System::Drawing::Size(136, 23);
			this->labelX2->TabIndex = 13;
			this->labelX2->Text = L"放大倍数：";
			// 
			// line2
			// 
			this->line2->Location = System::Drawing::Point(0, 40);
			this->line2->Name = L"line2";
			this->line2->Size = System::Drawing::Size(265, 23);
			this->line2->TabIndex = 12;
			this->line2->Text = L"line2";
			// 
			// labelX12
			// 
			// 
			// 
			// 
			this->labelX12->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX12->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX12->ForeColor = System::Drawing::Color::White;
			this->labelX12->Location = System::Drawing::Point(12, 151);
			this->labelX12->Name = L"labelX12";
			this->labelX12->Size = System::Drawing::Size(21, 23);
			this->labelX12->TabIndex = 4;
			this->labelX12->Text = L"1";
			// 
			// txtbx_size
			// 
			this->txtbx_size->Enabled = false;
			this->txtbx_size->Location = System::Drawing::Point(211, 178);
			this->txtbx_size->Name = L"txtbx_size";
			this->txtbx_size->Size = System::Drawing::Size(36, 21);
			this->txtbx_size->TabIndex = 11;
			this->txtbx_size->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ImageProcessControl::txtbx_size_KeyDown);
			// 
			// labelX16
			// 
			// 
			// 
			// 
			this->labelX16->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX16->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15));
			this->labelX16->ForeColor = System::Drawing::Color::White;
			this->labelX16->Location = System::Drawing::Point(21, 14);
			this->labelX16->Name = L"labelX16";
			this->labelX16->Size = System::Drawing::Size(75, 23);
			this->labelX16->TabIndex = 8;
			this->labelX16->Text = L"缩放 ";
			// 
			// labelX13
			// 
			// 
			// 
			// 
			this->labelX13->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX13->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX13->ForeColor = System::Drawing::Color::White;
			this->labelX13->Location = System::Drawing::Point(178, 154);
			this->labelX13->Name = L"labelX13";
			this->labelX13->Size = System::Drawing::Size(36, 23);
			this->labelX13->TabIndex = 5;
			this->labelX13->Text = L"10";
			// 
			// slider_size
			// 
			// 
			// 
			// 
			this->slider_size->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->slider_size->Enabled = false;
			this->slider_size->Location = System::Drawing::Point(-26, 178);
			this->slider_size->Maximum = 1000;
			this->slider_size->Minimum = 100;
			this->slider_size->Name = L"slider_size";
			this->slider_size->Size = System::Drawing::Size(227, 23);
			this->slider_size->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->slider_size->TabIndex = 0;
			this->slider_size->Value = 100;
			this->slider_size->ValueChanged += gcnew System::EventHandler(this, &ImageProcessControl::slider_size_ValueChanged);
			// 
			// tab_size
			// 
			this->tab_size->AttachedControl = this->superTabControlPanel6;
			this->tab_size->Description = L"缩放";
			this->tab_size->GlobalItem = false;
			this->tab_size->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tab_size.Image")));
			this->tab_size->Name = L"tab_size";
			this->tab_size->Tooltip = L"缩放";
			// 
			// superTabControlPanel7
			// 
			this->superTabControlPanel7->Controls->Add(this->pnl_edgeDect);
			this->superTabControlPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->superTabControlPanel7->Location = System::Drawing::Point(68, 0);
			this->superTabControlPanel7->Name = L"superTabControlPanel7";
			this->superTabControlPanel7->Size = System::Drawing::Size(265, 315);
			this->superTabControlPanel7->TabIndex = 0;
			this->superTabControlPanel7->TabItem = this->tab_edgeDetctiom;
			// 
			// pnl_edgeDect
			// 
			this->pnl_edgeDect->BackColor = System::Drawing::Color::SteelBlue;
			this->pnl_edgeDect->Controls->Add(this->labelX1);
			this->pnl_edgeDect->Controls->Add(this->line1);
			this->pnl_edgeDect->Controls->Add(this->label1);
			this->pnl_edgeDect->Controls->Add(this->labelX24);
			this->pnl_edgeDect->Controls->Add(this->combo_EdgeDtcMethod);
			this->pnl_edgeDect->Controls->Add(this->txtbx_lowThreshold);
			this->pnl_edgeDect->Controls->Add(this->labelX25);
			this->pnl_edgeDect->Location = System::Drawing::Point(1, 0);
			this->pnl_edgeDect->Name = L"pnl_edgeDect";
			this->pnl_edgeDect->Size = System::Drawing::Size(262, 315);
			this->pnl_edgeDect->TabIndex = 4;
			// 
			// labelX1
			// 
			// 
			// 
			// 
			this->labelX1->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->labelX1->ForeColor = System::Drawing::Color::White;
			this->labelX1->Location = System::Drawing::Point(21, 14);
			this->labelX1->Name = L"labelX1";
			this->labelX1->Size = System::Drawing::Size(108, 23);
			this->labelX1->TabIndex = 12;
			this->labelX1->Text = L"边缘检测";
			// 
			// line1
			// 
			this->line1->Location = System::Drawing::Point(0, 40);
			this->line1->Name = L"line1";
			this->line1->Size = System::Drawing::Size(262, 23);
			this->line1->TabIndex = 11;
			this->line1->Text = L"line1";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(97, 233);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(131, 12);
			this->label1->TabIndex = 10;
			this->label1->Text = L"* 低阈值的范围是0到85";
			// 
			// labelX24
			// 
			// 
			// 
			// 
			this->labelX24->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX24->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX24->ForeColor = System::Drawing::Color::White;
			this->labelX24->Location = System::Drawing::Point(15, 126);
			this->labelX24->Name = L"labelX24";
			this->labelX24->Size = System::Drawing::Size(84, 23);
			this->labelX24->TabIndex = 4;
			this->labelX24->Text = L"检测方法 :";
			// 
			// combo_EdgeDtcMethod
			// 
			this->combo_EdgeDtcMethod->DisplayMember = L"Text";
			this->combo_EdgeDtcMethod->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
			this->combo_EdgeDtcMethod->Enabled = false;
			this->combo_EdgeDtcMethod->FormattingEnabled = true;
			this->combo_EdgeDtcMethod->ItemHeight = 15;
			this->combo_EdgeDtcMethod->Items->AddRange(gcnew cli::array< System::Object^  >(2) {this->Canny, this->LapLace});
			this->combo_EdgeDtcMethod->Location = System::Drawing::Point(105, 126);
			this->combo_EdgeDtcMethod->Name = L"combo_EdgeDtcMethod";
			this->combo_EdgeDtcMethod->Size = System::Drawing::Size(100, 21);
			this->combo_EdgeDtcMethod->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->combo_EdgeDtcMethod->TabIndex = 0;
			this->combo_EdgeDtcMethod->SelectedIndexChanged += gcnew System::EventHandler(this, &ImageProcessControl::edgeDtcMethod_SelectedIndexChanged);
			// 
			// Canny
			// 
			this->Canny->Text = L"Canny";
			// 
			// LapLace
			// 
			this->LapLace->Text = L"LapLace";
			// 
			// txtbx_lowThreshold
			// 
			// 
			// 
			// 
			this->txtbx_lowThreshold->Border->Class = L"TextBoxBorder";
			this->txtbx_lowThreshold->Border->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->txtbx_lowThreshold->Enabled = false;
			this->txtbx_lowThreshold->Location = System::Drawing::Point(105, 186);
			this->txtbx_lowThreshold->Name = L"txtbx_lowThreshold";
			this->txtbx_lowThreshold->Size = System::Drawing::Size(100, 21);
			this->txtbx_lowThreshold->TabIndex = 1;
			this->txtbx_lowThreshold->WatermarkColor = System::Drawing::Color::White;
			this->txtbx_lowThreshold->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ImageProcessControl::lowThreshold_KeyDown);
			// 
			// labelX25
			// 
			// 
			// 
			// 
			this->labelX25->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX25->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX25->ForeColor = System::Drawing::Color::White;
			this->labelX25->Location = System::Drawing::Point(15, 186);
			this->labelX25->Name = L"labelX25";
			this->labelX25->Size = System::Drawing::Size(66, 23);
			this->labelX25->TabIndex = 5;
			this->labelX25->Text = L"低阈值 :";
			// 
			// tab_edgeDetctiom
			// 
			this->tab_edgeDetctiom->AttachedControl = this->superTabControlPanel7;
			this->tab_edgeDetctiom->Description = L"边缘检测";
			this->tab_edgeDetctiom->GlobalItem = false;
			this->tab_edgeDetctiom->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tab_edgeDetctiom.Image")));
			this->tab_edgeDetctiom->Name = L"tab_edgeDetctiom";
			this->tab_edgeDetctiom->Tooltip = L"边缘检测";
			// 
			// superTabControlPanel1
			// 
			this->superTabControlPanel1->Controls->Add(this->pnl_angle);
			this->superTabControlPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->superTabControlPanel1->Location = System::Drawing::Point(68, 0);
			this->superTabControlPanel1->Name = L"superTabControlPanel1";
			this->superTabControlPanel1->Size = System::Drawing::Size(265, 315);
			this->superTabControlPanel1->TabIndex = 0;
			this->superTabControlPanel1->TabItem = this->tab_angle;
			// 
			// tab_angle
			// 
			this->tab_angle->AttachedControl = this->superTabControlPanel1;
			this->tab_angle->Description = L"旋转";
			this->tab_angle->GlobalItem = false;
			this->tab_angle->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tab_angle.Image")));
			this->tab_angle->Name = L"tab_angle";
			this->tab_angle->Tooltip = L"旋转";
			// 
			// superTabControlPanel10
			// 
			this->superTabControlPanel10->Controls->Add(this->pnl_contrastBright);
			this->superTabControlPanel10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->superTabControlPanel10->Location = System::Drawing::Point(68, 0);
			this->superTabControlPanel10->Name = L"superTabControlPanel10";
			this->superTabControlPanel10->Size = System::Drawing::Size(265, 315);
			this->superTabControlPanel10->TabIndex = 0;
			this->superTabControlPanel10->TabItem = this->tab_contrastBringht;
			// 
			// pnl_contrastBright
			// 
			this->pnl_contrastBright->BackColor = System::Drawing::Color::SteelBlue;
			this->pnl_contrastBright->Controls->Add(this->labelX4);
			this->pnl_contrastBright->Controls->Add(this->line5);
			this->pnl_contrastBright->Controls->Add(this->txtbx_bright);
			this->pnl_contrastBright->Controls->Add(this->txtbx_contrast);
			this->pnl_contrastBright->Controls->Add(this->labelX11);
			this->pnl_contrastBright->Controls->Add(this->labelX10);
			this->pnl_contrastBright->Controls->Add(this->labelX9);
			this->pnl_contrastBright->Controls->Add(this->labelX8);
			this->pnl_contrastBright->Controls->Add(this->labelX7);
			this->pnl_contrastBright->Controls->Add(this->labelX6);
			this->pnl_contrastBright->Controls->Add(this->slider_bright);
			this->pnl_contrastBright->Controls->Add(this->slider_contrast);
			this->pnl_contrastBright->Location = System::Drawing::Point(0, 0);
			this->pnl_contrastBright->Name = L"pnl_contrastBright";
			this->pnl_contrastBright->Size = System::Drawing::Size(262, 315);
			this->pnl_contrastBright->TabIndex = 1;
			// 
			// labelX4
			// 
			// 
			// 
			// 
			this->labelX4->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX4->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15));
			this->labelX4->ForeColor = System::Drawing::Color::White;
			this->labelX4->Location = System::Drawing::Point(21, 14);
			this->labelX4->Name = L"labelX4";
			this->labelX4->Size = System::Drawing::Size(180, 23);
			this->labelX4->TabIndex = 14;
			this->labelX4->Text = L"对比度  亮度调节";
			// 
			// line5
			// 
			this->line5->Location = System::Drawing::Point(0, 40);
			this->line5->Name = L"line5";
			this->line5->Size = System::Drawing::Size(262, 23);
			this->line5->TabIndex = 13;
			this->line5->Text = L"line5";
			// 
			// txtbx_bright
			// 
			this->txtbx_bright->Enabled = false;
			this->txtbx_bright->Location = System::Drawing::Point(219, 239);
			this->txtbx_bright->Name = L"txtbx_bright";
			this->txtbx_bright->Size = System::Drawing::Size(36, 21);
			this->txtbx_bright->TabIndex = 12;
			this->txtbx_bright->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ImageProcessControl::txtbx_bright_KeyDown);
			// 
			// txtbx_contrast
			// 
			this->txtbx_contrast->Enabled = false;
			this->txtbx_contrast->Location = System::Drawing::Point(218, 138);
			this->txtbx_contrast->Name = L"txtbx_contrast";
			this->txtbx_contrast->Size = System::Drawing::Size(36, 21);
			this->txtbx_contrast->TabIndex = 11;
			this->txtbx_contrast->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ImageProcessControl::txtbx_contrast_KeyDown);
			// 
			// labelX11
			// 
			// 
			// 
			// 
			this->labelX11->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX11->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX11->ForeColor = System::Drawing::Color::White;
			this->labelX11->Location = System::Drawing::Point(7, 184);
			this->labelX11->Name = L"labelX11";
			this->labelX11->Size = System::Drawing::Size(75, 23);
			this->labelX11->TabIndex = 9;
			this->labelX11->Text = L"亮度   ：";
			// 
			// labelX10
			// 
			// 
			// 
			// 
			this->labelX10->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX10->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX10->ForeColor = System::Drawing::Color::White;
			this->labelX10->Location = System::Drawing::Point(8, 85);
			this->labelX10->Name = L"labelX10";
			this->labelX10->Size = System::Drawing::Size(78, 23);
			this->labelX10->TabIndex = 8;
			this->labelX10->Text = L"对比度 ：";
			// 
			// labelX9
			// 
			// 
			// 
			// 
			this->labelX9->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX9->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX9->ForeColor = System::Drawing::Color::White;
			this->labelX9->Location = System::Drawing::Point(177, 212);
			this->labelX9->Name = L"labelX9";
			this->labelX9->Size = System::Drawing::Size(43, 23);
			this->labelX9->TabIndex = 7;
			this->labelX9->Text = L"100";
			// 
			// labelX8
			// 
			// 
			// 
			// 
			this->labelX8->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX8->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX8->ForeColor = System::Drawing::Color::White;
			this->labelX8->Location = System::Drawing::Point(177, 118);
			this->labelX8->Name = L"labelX8";
			this->labelX8->Size = System::Drawing::Size(43, 23);
			this->labelX8->TabIndex = 6;
			this->labelX8->Text = L"300";
			// 
			// labelX7
			// 
			// 
			// 
			// 
			this->labelX7->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX7->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX7->ForeColor = System::Drawing::Color::White;
			this->labelX7->Location = System::Drawing::Point(3, 213);
			this->labelX7->Name = L"labelX7";
			this->labelX7->Size = System::Drawing::Size(44, 23);
			this->labelX7->TabIndex = 5;
			this->labelX7->Text = L"100";
			// 
			// labelX6
			// 
			// 
			// 
			// 
			this->labelX6->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX6->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12));
			this->labelX6->ForeColor = System::Drawing::Color::White;
			this->labelX6->Location = System::Drawing::Point(3, 114);
			this->labelX6->Name = L"labelX6";
			this->labelX6->Size = System::Drawing::Size(44, 23);
			this->labelX6->TabIndex = 4;
			this->labelX6->Text = L"-100";
			// 
			// slider_bright
			// 
			// 
			// 
			// 
			this->slider_bright->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->slider_bright->Enabled = false;
			this->slider_bright->Location = System::Drawing::Point(-24, 237);
			this->slider_bright->Minimum = -100;
			this->slider_bright->Name = L"slider_bright";
			this->slider_bright->Size = System::Drawing::Size(227, 23);
			this->slider_bright->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->slider_bright->TabIndex = 1;
			this->slider_bright->Value = 0;
			this->slider_bright->ValueChanged += gcnew System::EventHandler(this, &ImageProcessControl::slider_bright_ValueChanged);
			this->slider_bright->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::slider_bright_MouseUp);
			this->slider_bright->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::slider_bright_MouseWheel);
			// 
			// slider_contrast
			// 
			// 
			// 
			// 
			this->slider_contrast->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->slider_contrast->Enabled = false;
			this->slider_contrast->Location = System::Drawing::Point(-24, 138);
			this->slider_contrast->Maximum = 300;
			this->slider_contrast->Minimum = -100;
			this->slider_contrast->Name = L"slider_contrast";
			this->slider_contrast->Size = System::Drawing::Size(227, 26);
			this->slider_contrast->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->slider_contrast->TabIndex = 0;
			this->slider_contrast->Value = 100;
			this->slider_contrast->ValueChanged += gcnew System::EventHandler(this, &ImageProcessControl::slider_contrast_ValueChanged);
			this->slider_contrast->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::slider_contrast_MouseUp);
			this->slider_contrast->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &ImageProcessControl::slider_contrast_MouseWheel);
			// 
			// tab_contrastBringht
			// 
			this->tab_contrastBringht->AttachedControl = this->superTabControlPanel10;
			this->tab_contrastBringht->Description = L"对比度与亮度调节";
			this->tab_contrastBringht->GlobalItem = false;
			this->tab_contrastBringht->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tab_contrastBringht.Image")));
			this->tab_contrastBringht->Name = L"tab_contrastBringht";
			this->tab_contrastBringht->Tooltip = L"对比度&亮度调节";
			// 
			// superTabControl1
			// 
			// 
			// 
			// 
			// 
			// 
			// 
			this->superTabControl1->ControlBox->CloseBox->Name = L"";
			// 
			// 
			// 
			this->superTabControl1->ControlBox->MenuBox->Name = L"";
			this->superTabControl1->ControlBox->Name = L"";
			this->superTabControl1->ControlBox->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->superTabControl1->ControlBox->MenuBox, 
				this->superTabControl1->ControlBox->CloseBox});
			this->superTabControl1->Controls->Add(this->superTabControlPanel2);
			this->superTabControl1->Controls->Add(this->superTabControlPanel3);
			this->superTabControl1->Location = System::Drawing::Point(13, 369);
			this->superTabControl1->Name = L"superTabControl1";
			this->superTabControl1->ReorderTabsEnabled = true;
			this->superTabControl1->SelectedTabFont = (gcnew System::Drawing::Font(L"SimSun", 9, System::Drawing::FontStyle::Bold));
			this->superTabControl1->SelectedTabIndex = 0;
			this->superTabControl1->Size = System::Drawing::Size(333, 310);
			this->superTabControl1->TabFont = (gcnew System::Drawing::Font(L"SimSun", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->superTabControl1->TabIndex = 15;
			this->superTabControl1->Tabs->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->superTabItem1, 
				this->superTabItem2});
			this->superTabControl1->Text = L"superTabControl1";
			// 
			// superTabControlPanel2
			// 
			this->superTabControlPanel2->Controls->Add(this->pnl_showHstgrm);
			this->superTabControlPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->superTabControlPanel2->Location = System::Drawing::Point(0, 46);
			this->superTabControlPanel2->Name = L"superTabControlPanel2";
			this->superTabControlPanel2->Size = System::Drawing::Size(333, 264);
			this->superTabControlPanel2->TabIndex = 1;
			this->superTabControlPanel2->TabItem = this->superTabItem1;
			// 
			// pnl_showHstgrm
			// 
			this->pnl_showHstgrm->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pnl_showHstgrm->Location = System::Drawing::Point(1, -1);
			this->pnl_showHstgrm->Name = L"pnl_showHstgrm";
			this->pnl_showHstgrm->Size = System::Drawing::Size(331, 264);
			this->pnl_showHstgrm->TabIndex = 10;
			this->pnl_showHstgrm->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ImageProcessControl::pnl_showHstgrm_Paint);
			// 
			// superTabItem1
			// 
			this->superTabItem1->AttachedControl = this->superTabControlPanel2;
			this->superTabItem1->Description = L"直方图";
			this->superTabItem1->GlobalItem = false;
			this->superTabItem1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"superTabItem1.Image")));
			this->superTabItem1->Name = L"superTabItem1";
			this->superTabItem1->Tooltip = L"直方图";
			// 
			// superTabControlPanel3
			// 
			this->superTabControlPanel3->Controls->Add(this->panel_fft);
			this->superTabControlPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->superTabControlPanel3->Location = System::Drawing::Point(0, 0);
			this->superTabControlPanel3->Name = L"superTabControlPanel3";
			this->superTabControlPanel3->Size = System::Drawing::Size(333, 310);
			this->superTabControlPanel3->TabIndex = 0;
			this->superTabControlPanel3->TabItem = this->superTabItem2;
			// 
			// superTabItem2
			// 
			this->superTabItem2->AttachedControl = this->superTabControlPanel3;
			this->superTabItem2->Description = L"傅里叶变换";
			this->superTabItem2->GlobalItem = false;
			this->superTabItem2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"superTabItem2.Image")));
			this->superTabItem2->Name = L"superTabItem2";
			this->superTabItem2->Tooltip = L"傅里叶变换";
			// 
			// pnl_MainPanel
			// 
			this->pnl_MainPanel->Controls->Add(this->btn_export);
			this->pnl_MainPanel->Controls->Add(this->exPnl_showHistory);
			this->pnl_MainPanel->Controls->Add(this->pnl_showImg);
			this->pnl_MainPanel->Controls->Add(this->panel1);
			this->pnl_MainPanel->Controls->Add(this->superTabControl1);
			this->pnl_MainPanel->Controls->Add(this->tabControl);
			this->pnl_MainPanel->Controls->Add(this->btn_gray);
			this->pnl_MainPanel->Controls->Add(this->btn_apply);
			this->pnl_MainPanel->Controls->Add(this->btn_save);
			this->pnl_MainPanel->Controls->Add(this->btn_open);
			this->pnl_MainPanel->Location = System::Drawing::Point(0, 0);
			this->pnl_MainPanel->Name = L"pnl_MainPanel";
			this->pnl_MainPanel->Size = System::Drawing::Size(1500, 900);
			this->pnl_MainPanel->TabIndex = 0;
			// 
			// btn_export
			// 
			this->btn_export->BackColor = System::Drawing::Color::SteelBlue;
			this->btn_export->Enabled = false;
			this->btn_export->ForeColor = System::Drawing::Color::White;
			this->btn_export->Location = System::Drawing::Point(14, 814);
			this->btn_export->Name = L"btn_export";
			this->btn_export->Size = System::Drawing::Size(139, 59);
			this->btn_export->TabIndex = 18;
			this->btn_export->Text = L"导出原图";
			this->btn_export->UseVisualStyleBackColor = false;
			this->btn_export->Click += gcnew System::EventHandler(this, &ImageProcessControl::btn_export_Click);
			// 
			// exPnl_showHistory
			// 
			this->exPnl_showHistory->CollapseDirection = DevComponents::DotNetBar::eCollapseDirection::LeftToRight;
			this->exPnl_showHistory->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::Office2010;
			this->exPnl_showHistory->Controls->Add(this->lstView_historyList);
			this->exPnl_showHistory->Expanded = false;
			this->exPnl_showHistory->ExpandedBounds = System::Drawing::Rectangle(1278, 52, 200, 813);
			this->exPnl_showHistory->ExpandOnTitleClick = true;
			this->exPnl_showHistory->HideControlsWhenCollapsed = true;
			this->exPnl_showHistory->Location = System::Drawing::Point(1443, 52);
			this->exPnl_showHistory->Name = L"exPnl_showHistory";
			this->exPnl_showHistory->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->exPnl_showHistory->Size = System::Drawing::Size(35, 813);
			this->exPnl_showHistory->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->exPnl_showHistory->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::PanelBackground;
			this->exPnl_showHistory->Style->BackColor2->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::PanelBackground2;
			this->exPnl_showHistory->Style->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"exPnl_showHistory.Style.BackgroundImage")));
			this->exPnl_showHistory->Style->Border = DevComponents::DotNetBar::eBorderType::SingleLine;
			this->exPnl_showHistory->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarDockedBorder;
			this->exPnl_showHistory->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->exPnl_showHistory->Style->GradientAngle = 90;
			this->exPnl_showHistory->TabIndex = 16;
			this->exPnl_showHistory->TitleHeight = 35;
			this->exPnl_showHistory->TitleStyle->Alignment = System::Drawing::StringAlignment::Center;
			this->exPnl_showHistory->TitleStyle->BackColor1->Color = System::Drawing::Color::SteelBlue;
			this->exPnl_showHistory->TitleStyle->BackColor2->Color = System::Drawing::Color::White;
			this->exPnl_showHistory->TitleStyle->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"exPnl_showHistory.TitleStyle.BackgroundImage")));
			this->exPnl_showHistory->TitleStyle->BackgroundImagePosition = DevComponents::DotNetBar::eBackgroundImagePosition::TopLeft;
			this->exPnl_showHistory->TitleStyle->Border = DevComponents::DotNetBar::eBorderType::RaisedInner;
			this->exPnl_showHistory->TitleStyle->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::PanelBorder;
			this->exPnl_showHistory->TitleStyle->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::PanelText;
			this->exPnl_showHistory->TitleStyle->GradientAngle = 90;
			this->exPnl_showHistory->TitleStyleMouseDown->BackColor1->Color = System::Drawing::Color::SteelBlue;
			this->exPnl_showHistory->TitleStyleMouseDown->BackColor2->Color = System::Drawing::Color::SteelBlue;
			this->exPnl_showHistory->TitleStyleMouseDown->Border = DevComponents::DotNetBar::eBorderType::Sunken;
			this->exPnl_showHistory->TitleStyleMouseOver->BackColor1->Color = System::Drawing::Color::SteelBlue;
			this->exPnl_showHistory->TitleStyleMouseOver->BackColor2->Color = System::Drawing::Color::SteelBlue;
			this->exPnl_showHistory->TitleStyleMouseOver->BorderDashStyle = System::Drawing::Drawing2D::DashStyle::DashDot;
			this->exPnl_showHistory->TitleStyleMouseOver->ForeColor->Color = System::Drawing::Color::White;
			this->exPnl_showHistory->TitleStyleMouseOver->WordWrap = true;
			this->exPnl_showHistory->TitleText = L"历史图片";
			this->exPnl_showHistory->ExpandedChanged += gcnew DevComponents::DotNetBar::ExpandChangeEventHandler(this, &ImageProcessControl::exPnl_showHistory_ExpandedChanged);
			this->exPnl_showHistory->Leave += gcnew System::EventHandler(this, &ImageProcessControl::exPnl_showHistory_Leave);
			// 
			// panel1
			// 
			this->panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"panel1.BackgroundImage")));
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel1->Location = System::Drawing::Point(367, 48);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1053, 807);
			this->panel1->TabIndex = 17;
			// 
			// BGW_export
			// 
			this->BGW_export->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ImageProcessControl::BGW_export_DoWork);
			this->BGW_export->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &ImageProcessControl::BGW_export_RunWorkerCompleted);
			// 
			// ImageProcessControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->Controls->Add(this->pnl_MainPanel);
			this->Name = L"ImageProcessControl";
			this->Size = System::Drawing::Size(1500, 900);
			this->pnl_angle->ResumeLayout(false);
			this->pnl_angle->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tabControl))->EndInit();
			this->tabControl->ResumeLayout(false);
			this->superTabControlPanel8->ResumeLayout(false);
			this->pnl_smooth->ResumeLayout(false);
			this->pnl_smooth->PerformLayout();
			this->superTabControlPanel9->ResumeLayout(false);
			this->pnl_thred->ResumeLayout(false);
			this->pnl_thred->PerformLayout();
			this->superTabControlPanel6->ResumeLayout(false);
			this->pnl_size->ResumeLayout(false);
			this->pnl_size->PerformLayout();
			this->superTabControlPanel7->ResumeLayout(false);
			this->pnl_edgeDect->ResumeLayout(false);
			this->pnl_edgeDect->PerformLayout();
			this->superTabControlPanel1->ResumeLayout(false);
			this->superTabControlPanel10->ResumeLayout(false);
			this->pnl_contrastBright->ResumeLayout(false);
			this->pnl_contrastBright->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->superTabControl1))->EndInit();
			this->superTabControl1->ResumeLayout(false);
			this->superTabControlPanel2->ResumeLayout(false);
			this->superTabControlPanel3->ResumeLayout(false);
			this->pnl_MainPanel->ResumeLayout(false);
			this->exPnl_showHistory->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		//字符串变换函数
		char * ManagedStr2UnmanagedChar(System::String^ strIn)
		{  
			System::IntPtr ip = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(strIn);
			const char* pTemp = static_cast<const char*>(ip.ToPointer());
			char *pOut = new char[strlen(pTemp)+1];  
			strcpy_s(pOut,strlen(pTemp)+1,pTemp);
			System::Runtime::InteropServices::Marshal::FreeHGlobal(ip);
			return pOut;
		}

		// 选择pnl_showImg显示图片的模式，长度或宽度小于panel的使用center模式，大于的使用zoom模式
	public: void ChoosePanelIndex(cv::Mat img){
				int   imgHeight  = 0;
				int   imgWidth = 0;
				imgHeight = img.rows;
				imgWidth  = img.cols;

				if (( imgHeight < pnl_showImg->Height ) && ( imgWidth < pnl_showImg->Width ))
				{
					pnl_showImg->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
				} 
				else
				{
					pnl_showImg->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
				}

			}

			//应用改变（改变tab和点击“应用改变”的按钮都会使用）
	public: void ChangeApply(){
				if ( imgProcessor.imgProcess.oprationState["scale"] == true )
				{
					System::Drawing::Rectangle Rect_Pb1_ZoomSize ;

					Rect_Pb1_ZoomSize.Width  = pnl_showImg->Width;
					Rect_Pb1_ZoomSize.Height = pnl_showImg->Height;

					imgProcessor.width = Rect_Pb1_ZoomSize.Width * slider_size->Value / 100;    // 将指定的值转换为32位元带正负号的整数。
					imgProcessor.heigth = Rect_Pb1_ZoomSize.Height * slider_size->Value / 100;


					Bitmap ^resizedBmp = gcnew Bitmap(imgProcessor.width, imgProcessor.heigth);
					Graphics ^g = Graphics::FromImage(resizedBmp);

					System::Drawing::Bitmap^ tempBitMap;
					cv::Mat showImg = imgProcessor.imgProcess.originalImg.clone();
					imgProcessor.imgProcess.originalImg.copyTo(showImg);
					tempBitMap = imgProcessor.MatToBitmap(showImg);

					g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;  //插值模式设置：临近取样
					g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::None;                 //渲染图像质量，更平滑柔和

					RectangleF rectDst = RectangleF(0,0,imgProcessor.width,imgProcessor.heigth);
					RectangleF rectSrc = RectangleF(0,0,tempBitMap->Width,tempBitMap->Height);
					// 在指定位置并且按指定大小绘制指定的Image的指定部分.
					// srcRect 参数指定要绘制的 image 对象的矩形部分。 将此部分进行缩放以适合 destRect 参数所指定的矩形。
					g->DrawImage(tempBitMap, rectDst, rectSrc, GraphicsUnit::Pixel);
					// GraphicsUnit：指定给定数据的度量单位。以设备像素为单位。 

					int ww, hh;
					ww = imgProcessor.width;
					hh = imgProcessor.heigth;

					if (pnl_showImg->Width < ww)    // 显示空间宽度不够
					{
						ww = pnl_showImg->Width;
						hh = imgProcessor.heigth * ww / imgProcessor.width;
					}

					if(pnl_showImg->Height < hh)    // 显示空间长度不够
					{
						hh = pnl_showImg->Height;
						ww = hh *imgProcessor.width / imgProcessor.heigth;
					}

					RectangleF rectClone;
					RectangleF rect;
					Bitmap ^ shownBitmap = gcnew Bitmap(pnl_showImg->Width, pnl_showImg->Height,System::Drawing::Imaging::PixelFormat::Format24bppRgb);
					Graphics ^dstG = Graphics::FromImage(shownBitmap);
					try{

						rectClone = RectangleF((int)imgProcessor.begin_x,(int)imgProcessor.begin_y, ww, hh);
						rect = RectangleF(0, 0, pnl_showImg->Width, pnl_showImg->Height);
						dstG->DrawImage(resizedBmp,rect,rectClone,GraphicsUnit::Pixel);

					}
					catch(System::Exception^ e)
					{
						String ^ i = e->ToString();
						MessageBox::Show(i);
						txtbx_size->Clear();
					}

					imgProcessor.imgProcess.oprateImg = imgProcessor.BitmapToMat( shownBitmap ).clone();
					imgProcessor.BitmapToMat(shownBitmap).copyTo( imgProcessor.imgProcess.oprateImg );

					delete shownBitmap;
				}


				cv::Mat temp = imgProcessor.imgProcess.oprateImg.clone();
				imgProcessor.imgProcess.oprateImg.copyTo( temp );
				imgProcessor.imgProcess.imgHistoryVec.push_back( temp );
				imgProcessor.imgProcess.lastChangeVec.push_back(imgProcessor.imgProcess.lastChange);
				imgProcessor.imgProcess.lastChangeIndex.lastImg = imgProcessor.imgProcess.lastChangeIndex.currentImg;
				imgProcessor.imgProcess.lastChangeIndex.currentImg++;
				imgProcessor.imgProcess.changeIndexVec.push_back (imgProcessor.imgProcess.lastChangeIndex);





				imgProcessor.imgProcess.originalImg = imgProcessor.imgProcess.oprateImg.clone();
				imgProcessor.imgProcess.oprateImg.copyTo( imgProcessor.imgProcess.originalImg );
				try{
					UpdateImgList();
					imgProcessor.imgProcess.SavePicture( imgProcessor.imgProcess.tempFilePath );
					imgProcessor.imgProcess.ReLoadPicture();
				}
				catch(System::Exception^ e)
				{
					String ^ i = e->ToString();
					MessageBox::Show(i);
					txtbx_size->Clear();
				}

				if ( imgProcessor.imgProcess.oprateImg.channels() == 1 )
				{
					pnl_showHstgrm->Refresh();
					panel_fft->Refresh();
				}
				else{
					imgProcessor.imgProcess.Histogram();
					imgShow.ShowMat( imgProcessor.imgProcess.histogram,(HWND)this->pnl_showHstgrm->Handle.ToInt32() ,3 );
					imgProcessor.imgProcess.FourierTransform();
					char* fftPath = "C:\\Users\\Public\\Pictures\\Sample Pictures\\Fourier.jpg";
					cv::Mat fftImage = cv::imread( fftPath );
					panel_fft->Refresh();
					imgShow.ShowMat( fftImage,(HWND)this->panel_fft->Handle.ToInt32() ,3 );

				}

			}

			//在tabControl控件变换tab时询问是否应用改变
	private: System::Void tabControl_SelectedTabChanged(System::Object^  sender, DevComponents::DotNetBar::SuperTabStripSelectedTabChangedEventArgs^  e) {

				 if(imgProcessor.imgProcess.loadFlag){

					 if(imgProcessor.imgProcess.oprationState["angle"]
					 ||imgProcessor.imgProcess.oprationState["contrast_bright"]
					 ||imgProcessor.imgProcess.oprationState["edgeDetection"]
					 ||imgProcessor.imgProcess.oprationState["smoothing"]
					 ||imgProcessor.imgProcess.oprationState["threshold"]
					 ||imgProcessor.imgProcess.oprationState["gray"]
					 ||imgProcessor.imgProcess.oprationState["scale"]){
						 String^ message = "真的要应用改变吗？";
						 String^ caption = "  ";
						 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
						 System::Windows::Forms::DialogResult result;


						 // Displays the MessageBox.
						 result = MessageBox::Show( this, message, caption, buttons );
						 if ( result == ::DialogResult::Yes )
						 { 
							 ChangeApply();

						 }
						 if(result == ::DialogResult::No)
						 {
							 imgProcessor.imgProcess.originalImg = imgProcessor.imgProcess.imgHistoryVec[imgProcessor.imgProcess.imgHistoryVec.size()-1].clone();
							 imgProcessor.imgProcess.imgHistoryVec[imgProcessor.imgProcess.imgHistoryVec.size()-1].copyTo(imgProcessor.imgProcess.originalImg);
							 imgProcessor.imgProcess.lastChange = imgProcessor.imgProcess.lastChangeVec[imgProcessor.imgProcess.lastChangeVec.size()-1];
							 imgProcessor.imgProcess.lastChangeIndex = imgProcessor.imgProcess.changeIndexVec[imgProcessor.imgProcess.changeIndexVec.size()-1];


							 System::Drawing::Bitmap^ tempBitMap;
							 cv::Mat showImg = imgProcessor.imgProcess.originalImg.clone();
							 imgProcessor.imgProcess.originalImg.copyTo(showImg);
							 tempBitMap = imgProcessor.MatToBitmap(showImg);
							 pnl_showImg->BackgroundImage = tempBitMap;

						 }
						 imgProcessor.imgProcess.Reset();
					 } 

					 else{
						 /* cv::Mat temp =imgControl->oprateImg.clone();
						 imgControl->oprateImg.copyTo(temp);
						 imgControl->shownPic.push(temp);*/
					 }
				 }
				 BacktoIntialState();
				 btn_apply->Enabled = false;
			 }

			 //载入图片后控件变为可使用
	public: void ControlEnable(){
				btn_save->Enabled = true;
				btn_gray->Enabled = true;
				btn_apply->Enabled = true;
				slider_size->Enabled = true;
				slider_angle->Enabled = true;
				slider_contrast->Enabled = true;
				slider_bright->Enabled = true;
				slider_threshold->Enabled = true;
				combo_EdgeDtcMethod->Enabled = true;
				combo_smoothingMethod->Enabled = true;
				combo_thresholdMethod->Enabled = true;
				txtbx_size->Enabled = true;
				txtBx_ang->Enabled = true;
				txtbx_contrast->Enabled = true;
				txtbx_contrast->Enabled = true;
				txtbx_bright->Enabled = true;
				txtbx_thred->Enabled = true;
				txtbx_kernekLength->Enabled = true;
				txtbx_lowThreshold->Enabled = true;
				btn_export->Enabled = true;

			}
			/************************************************************************/
			/*    说明：图像的打开、保存、slider等恢复原位                          */                                     
			/************************************************************************/

			//使各种控件恢复初始状态
	public: void BacktoIntialState(){
				isApplyInitialChange = false;
				slider_size->Value = 0;
				slider_angle->Value = 0;
				slider_contrast->Value = 100;
				slider_bright->Value = 0;
				combo_EdgeDtcMethod->SelectedIndex = -1;
				combo_smoothingMethod->SelectedIndex = -1;
				combo_thresholdMethod->SelectedIndex = -1;
				txtbx_kernekLength->Clear();
				slider_threshold->Value=0;
				txtbx_lowThreshold->Clear();
				txtbx_size->Clear();
				txtBx_ang->Clear();
				txtbx_bright->Clear();
				txtbx_contrast->Clear();
				txtbx_thred->Clear();
				txtbx_lowThreshold->Enabled = false;
				txtbx_kernekLength->Enabled = false;
				slider_threshold->Enabled = false;
				txtbx_thred->Enabled = false;
				isApplyInitialChange = true;
			}

			//打开图片
	public: void OpenImgFile(){
				imgProcessor.imgProcess.imgHistoryVec.clear();
				imgProcessor.imgProcess.lastChangeVec.clear();
				imgProcessor.imgProcess.changeIndexVec.clear();
				imgProcessor.imgProcess.lastChangeIndex.currentImg=0;
				imgProcessor.imgProcess.lastChangeIndex.lastImg=0;
				imgProcessor.imgProcess.lastChangeIndex.name  = "";
				imgProcessor.imgProcess.lastChangeIndex.detail = "";

				imgProcessor.imgProcess.Reset();
				BacktoIntialState();
				GC::Collect();


				Stream^ myStream;
				System::Windows::Forms::OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
				openFileDialog1->Filter = "图片文件(jpg,jpeg,bmp,gif,ico,pen,tif)|*.jpg;*.jpeg;*.bmp;*.gif;*.ico;*.png;*.tif;*.wmf";
				openFileDialog1->FilterIndex = 2;
				openFileDialog1->RestoreDirectory = true;

				clickLock->WaitOne();
				isClick = true;
				if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				{					
					if ( (myStream = openFileDialog1->OpenFile()) != nullptr )
					{
						pnl_showImg->Refresh();
						String^ picPath = openFileDialog1->FileName;
						std::string newPicPath = marshal_as<std::string>(picPath);  
						imgProcessor.imgProcess.fileName=newPicPath;
						imgProcessor.imgProcess.LoadPicture(pnl_showImg->Width,pnl_showImg->Height);	

						System::Drawing::Bitmap^ tempBitMap;
						cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
						imgProcessor.imgProcess.oprateImg.copyTo(showImg);
						tempBitMap =imgProcessor.MatToBitmap(showImg);
						ChoosePanelIndex(imgProcessor.imgProcess.oprateImg);

						pnl_showImg->BackgroundImage = tempBitMap;
						imgProcessor.imgProcess.SavePicture(imgProcessor.imgProcess.tempFilePath);


						myStream->Close();
					}
					else{
						isClick = false;
						clickLock->ReleaseMutex();
						return;
					}
				}

				cv::Mat temp =imgProcessor.imgProcess.oprateImg.clone();
				imgProcessor.imgProcess.oprateImg.copyTo(temp);
				imgProcessor.imgProcess.imgHistoryVec.push_back(temp);
				imgProcessor.imgProcess.lastChangeVec.push_back(imgProcessor.imgProcess.lastChange);
				imgProcessor.imgProcess.changeIndexVec.push_back (imgProcessor.imgProcess.lastChangeIndex);

				UpdateImgList();

				imgProcessor.imgProcess.Histogram();

				imgShow.ShowMat( imgProcessor.imgProcess.histogram,(HWND)this->pnl_showHstgrm->Handle.ToInt32() ,3 );//显示直方图

				imgProcessor.imgProcess.FourierTransform();


				char* fftPath="C:\\Users\\Public\\Pictures\\Sample Pictures\\Fourier.jpg";
				cv::Mat ttfImage = cv::imread(fftPath);
				panel_fft->Refresh();
				imgShow.ShowMat( ttfImage,(HWND)this->panel_fft->Handle.ToInt32() ,3 );//显示弗洛伊德图

				imgProcessor.imgProcess.loadFlag = true;
				ControlEnable();
				isClick = true;
				clickLock->ReleaseMutex();
			}

			//保存图片
	public:	void SaveImgFile(){
				SaveFileDialog ^ saveFileDialog1 = gcnew SaveFileDialog();
				saveFileDialog1->Filter = 
					"JPeg Image|*.jpg|Bitmap Image|*.bmp|Gif Image|*.gif";
				saveFileDialog1->Title = "Save an Image File";
				saveFileDialog1->ShowDialog();

				if(saveFileDialog1->FileName != "")
				{

					String^ picPath = saveFileDialog1->FileName;
					std::string newPicPath = marshal_as<std::string>(picPath); 
					imgProcessor.imgProcess.finalPath = newPicPath;
					imgProcessor.imgProcess.SavePicture( imgProcessor.imgProcess.finalPath );
				}
				else{
					return;
				}
			}

			//点击打开按钮
	private: System::Void btn_open_Click(System::Object^  sender, System::EventArgs^  e) {

				 if ((imgProcessor.imgProcess.loadFlag == true) && (imgProcessor.imgProcess.imgHistoryVec.size() > 1))
				 {

					 System::Windows::Forms::DialogResult result = MessageBox::Show(this , "是否保存当前图像？", "",MessageBoxButtons::YesNo);
					 if ( result == ::DialogResult::Yes )
					 {
						 SaveImgFile();
					 }
				 }

				 OpenImgFile();
				 btn_apply->Enabled = false;
				 imgProcessor.imgProcess.Reset();
			 }

			 //点击保存按钮
	private: System::Void btn_save_Click(System::Object^  sender, System::EventArgs^  e) {
				 SaveImgFile();
			 }


			 /************************************************************************/
			 /*    说明：放大操作                                                    */                                     
			 /************************************************************************/
			 //滑动slider
	private: System::Void slider_size_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

				 if(isApplyInitialChange == true){
					 int i=slider_size->Value ;
					 double j = i / 250;
					 double size = std::pow(2,j);

					 if (i < 0)
					 {

						 txtbx_size->Text = size.ToString();
						 imgProcessor.imgProcess.ScaleChange(i);
						 System::Drawing::Bitmap^ tempBitMap;
						 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
						 imgProcessor.imgProcess.oprateImg.copyTo(showImg);
						 tempBitMap = imgProcessor.MatToBitmap(showImg);
						 ChoosePanelIndex(imgProcessor.imgProcess.oprateImg);
						 pnl_showImg->BackgroundImage = tempBitMap;
					 }
					 else if(i>0){

						 float multi = (float)slider_size->Value/100;
						 float x_unit = Math::Abs(pnl_showImg->Width / 2 - middle_x) * 12/ (slider_size->Value - 90) ;
						 float y_unit = Math::Abs(pnl_showImg->Height / 2 - middle_y) * 12 / (slider_size->Value - 90) ;



						 if (((slider_size->Value - sizeSliderValue) < 0)
							 &&((middle_x != pnl_showImg->Width / 2)&&(middle_y != pnl_showImg->Height / 2)))//如果缩小图片且中心不在原始图片正中心
						 {
							 if (middle_x <= (pnl_showImg->Width / 2) / multi )//靠近左边界
							 {
								 middle_x += x_unit;
							 }
							 else if ((pnl_showImg->Width - middle_x) <= (pnl_showImg->Width / 2) / multi)//靠近右边界
							 {
								 middle_x -= x_unit;
							 }

							 if (middle_y <= (pnl_showImg->Height/2)/multi )//靠近上边界
							 {
								 middle_y += y_unit;
							 }
							 else if ((pnl_showImg->Height - middle_y) <= (pnl_showImg->Height / 2) / multi)//靠近下边界
							 {
								 middle_y -= y_unit;
							 }

							 if (Math::Abs(pnl_showImg->Width / 2 - middle_x) < x_unit)//与图片中心点左右距离小于unit_x
							 {
								 middle_x = pnl_showImg->Width / 2;
							 }

							 if (Math::Abs(pnl_showImg->Height / 2 - middle_y) < y_unit)//与图片中心点上下距离小于unit_y
							 {
								 middle_y = pnl_showImg->Height / 2;
							 }





						 }
						 imgProcessor.begin_x = middle_x * multi - pnl_showImg->Width/2;
						 imgProcessor.begin_y =  middle_y * multi - pnl_showImg->Height/2;

						 imgProcessor.ZoomImage(slider_size->Value, pnl_showImg);



					 }

					 sizeSliderValue = slider_size->Value;
				 }
				 float i = (float)slider_size->Value / 100;
				 txtbx_size->Text = i.ToString();
				 btn_apply->Enabled = true;
			 }

			 //在框中输入放大值并输入回车
	private: System::Void txtbx_size_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

				 if (e->KeyCode == Keys::Enter && !e->Control)
				 {
					 try{
						 double sizeValue = Convert::ToDouble(txtbx_size->Text);
						 if ((sizeValue > 10) || (sizeValue < 1))
						 {
							 MessageBox::Show("输入无效，请输入1至10之间的数");
						 }
						 else{
							 slider_size->Value = sizeValue * 100 ;
						 }
					 }
					 catch(System::Exception^ e)
					 {
						 String ^ i = e->ToString();
						 MessageBox::Show(i);
						 txtbx_size->Clear();
					 }
				 }
			 }

			 //记录拖动到起始位置
	private: System::Void pnl_showImg_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 isStarMove  = true;
				 moveStarPoint = e->Location;

			 }

	private: System::Void pnl_showImg_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

				 isStarMove = true; 
			 }

			 //记录拖动的终止位置，并计算移动向量
	private: System::Void pnl_showImg_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 clickLock->WaitOne();
				 if (isClick == true || isStarMove == false)
				 {
					 clickLock->ReleaseMutex();
					 return;
				 }
				 clickLock->ReleaseMutex();

				 float move_x, move_y;
				 move_x = e->X - moveStarPoint.X;    // 初始 - 停止
				 move_y = e->Y - moveStarPoint.Y;
				 if ((move_x == 0)&&(move_y == 0))
				 {
					 middle_x = e->X;
					 middle_y = e->Y;
				 }
				 else{

					 float multi = ((float)slider_size->Value/100);

					 float real_x, real_y;

					 real_x = move_x/multi;
					 real_y = move_y/multi;



					 if (move_x > 0)    // 右到左
					 {
						 if (multi * middle_x - move_x >= pnl_showImg->Width/2)    // 挪动距离不超出原图范围
							 middle_x -= real_x;
						 else 
							 middle_x = (pnl_showImg->Width/2)/multi;
					 }
					 else          // 左到右
					 {
						 if (multi * middle_x - move_x <= multi * pnl_showImg->Width - pnl_showImg->Width/2)
							 middle_x -= real_x;
						 else 
							 middle_x = pnl_showImg->Width - (pnl_showImg->Width/2)/multi;
					 }
					 if (move_y > 0)    //下到上
					 {
						 if (multi * middle_y - move_y >= pnl_showImg->Height/2)    // 挪动距离不超出原图范围
							 middle_y -= real_y;
						 else 
							 middle_y = (pnl_showImg->Height/2) / multi;
					 }
					 else          // 上到下
					 {
						 if (multi * middle_y - move_y <= multi * pnl_showImg->Height - pnl_showImg->Height/2)
							 middle_y -= real_y;
						 else 
							 middle_y = pnl_showImg->Height - (pnl_showImg->Height/2)/multi;
					 }

					 imgProcessor.begin_x = middle_x * ((float)slider_size->Value/100) - pnl_showImg->Width/2;
					 imgProcessor.begin_y = middle_y * ((float)slider_size->Value/100) - pnl_showImg->Height/2;
					 imgProcessor.ZoomImage(slider_size->Value, pnl_showImg);
				 }
				 isStarMove = false;

			 }

			 //滚轮滑动控制放大缩小
	private: System::Void pnl_showImg_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
				 if (tabControl->SelectedPanel == superTabControlPanel6)
				 {


					 sizeWheelNum = slider_size->Value;
					 sizeWheelNum += e->Delta /12;

					 if (sizeWheelNum < 100)
					 {
						 sizeWheelNum = 100;
					 }
					 if (sizeWheelNum > 1000) 
					 {
						 sizeWheelNum = 1000;
					 }
					 slider_size->Value = sizeWheelNum;}

			 }

			 //光标停止位置确定焦点
	private: System::Void pnl_showImg_MouseHover(System::Object^  sender, System::EventArgs^  e) {
				 this->pnl_showImg->Focus();
				 // m_CurrentPoint = e->Location;
				 // middle_x = m_CurrentPoint.X;
				 // middle_y = m_CurrentPoint.Y;
			 } 

			 /************************************************************************/
			 /*    说明：旋转操作                                                    */                                     
			 /************************************************************************/
			 //滑动Slider
	private: System::Void slider_angle_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

				 if (isApplyInitialChange == true)
				 {

					 int i=slider_angle->Value;
					 txtBx_ang->Text = i.ToString();
					 imgProcessor.imgProcess.AngleChange(i);
					 System::Drawing::Bitmap^ tempBitMap;
					 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
					 imgProcessor.imgProcess.oprateImg.copyTo(showImg);
					 tempBitMap = imgProcessor.MatToBitmap(showImg);
					 ChoosePanelIndex(imgProcessor.imgProcess.oprateImg);
					 pnl_showImg->BackgroundImage = tempBitMap;
				 }

				 this->slider_angle->Focus();
				 btn_apply->Enabled = true;

			 }

			 //用鼠标滚轮控制滑块移动	
	private: System::Void slider_angle_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){


				 angleWheelNum =  slider_angle->Value;

				 angleWheelNum += e->Delta /24;

				 if (angleWheelNum<-180)
				 {
					 angleWheelNum = -180;
				 }
				 if (angleWheelNum > 180) 
				 {
					 angleWheelNum = 180;
				 }

				 slider_angle->Value = angleWheelNum;
			 }

			 //在框中输入旋转值并输入回车
	private: System::Void txtBx_ang_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

				 if (e->KeyCode == Keys::Enter && !e->Control)
				 {
					 try
					 {

						 int angleValue = Convert::ToInt32(txtBx_ang->Text);
						 if ((angleValue>180) || (angleValue<-180))
						 {
							 MessageBox::Show("输入无效，请输入-180到180之间的整数");
						 }
						 else
						 {   
							 slider_angle->Value = angleValue;
						 }
					 }
					 catch(System::Exception^ e)
					 {
						 String ^ i = e->ToString();
						 MessageBox::Show(i);
						 txtBx_ang->Clear();
					 }
				 }
			 }


			 /************************************************************************/
			 /*    说明：对比度调节                                                   */                                     
			 /************************************************************************/
			 //滑动Slider判断是否为灰度图。灰度图不适合调整对比度
	private: System::Void slider_contrast_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

				 if( imgProcessor.imgProcess.oprateImg.channels() == 1){
					 MessageBox::Show("该图片不适合调整对比度");
				 }
			 }

			 //鼠标松开时修改对比度
	private: System::Void slider_contrast_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if (isApplyInitialChange == true){
					 if( imgProcessor.imgProcess.oprateImg.channels() == 1){

					 }
					 else{
						 int i = slider_contrast->Value;
						 txtbx_contrast->Text = i.ToString();
						 imgProcessor.imgProcess.ContrastChange(i);
						 System::Drawing::Bitmap^ tempBitMap;
						 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
						 imgProcessor.imgProcess.oprateImg.copyTo(showImg);
						 tempBitMap = imgProcessor.MatToBitmap(showImg);
						 ChoosePanelIndex(imgProcessor.imgProcess.oprateImg);
						 pnl_showImg->BackgroundImage = tempBitMap;
					 }
				 }
				 btn_apply->Enabled = true;

			 }		

			 //框中输入对比度，按回车应用
	private: System::Void txtbx_contrast_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyCode == Keys::Enter && !e->Control)
				 {
					 try{
						 int contrastValue = Convert::ToInt32(txtbx_contrast->Text);
						 if ((contrastValue>300) || (contrastValue<-100))
						 {
							 MessageBox::Show("输入无效，请输入-100到300之间的整数");
						 }
						 else
						 {
							 slider_contrast->Value = contrastValue;
							 if (isApplyInitialChange == true){
								 if( imgProcessor.imgProcess.oprateImg.channels() == 1){

								 }
								 else{
									 int i = slider_contrast->Value;
									 imgProcessor.imgProcess.ContrastChange(i);
									 System::Drawing::Bitmap^ tempBitMap;
									 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
									 imgProcessor.imgProcess.oprateImg.copyTo(showImg);
									 tempBitMap = imgProcessor.MatToBitmap(showImg);
									 ChoosePanelIndex(imgProcessor.imgProcess.oprateImg);
									 pnl_showImg->BackgroundImage = tempBitMap;
								 }
							 }
							 btn_apply->Enabled = true;






						 }
					 }
					 catch(System::Exception^ e)
					 {
						 String ^ i = e->ToString();
						 MessageBox::Show(i);
						 txtbx_contrast->Clear();
					 }
				 }
			 }	

			 //鼠标滚轮控制滑块调整对比度
	private: System::Void slider_contrast_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){

				 contrastWheelNum = slider_contrast->Value;
				 contrastWheelNum += e->Delta /12;

				 if (contrastWheelNum < -100)
				 {
					 contrastWheelNum = -100;
				 }
				 if (contrastWheelNum > 300) 
				 {
					 contrastWheelNum = 300;
				 }

				 slider_contrast->Value = contrastWheelNum;
				 slider_contrast_MouseUp(this->slider_contrast, e );
			 }


			 /************************************************************************/
			 /*    说明：亮度调节                                                    */                                    
			 /************************************************************************/
			 //滑动Slider判断是否为灰度图
	private: System::Void slider_bright_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 if( imgProcessor.imgProcess.oprateImg.channels() == 1 ){
					 MessageBox::Show("该图片不适合调整对亮度");
				 }
			 }

			 //鼠标松开时修改亮度
	private: System::Void slider_bright_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if (isApplyInitialChange == true)
				 {


					 if ( imgProcessor.imgProcess.oprateImg.channels() == 1)
					 {

					 }
					 else{
						 int i = slider_bright->Value;
						 txtbx_bright->Text = i.ToString();
						 imgProcessor.imgProcess.BrightChange(i);
						 System::Drawing::Bitmap^ tempBitMap;
						 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
						 imgProcessor.imgProcess.oprateImg.copyTo( showImg );
						 tempBitMap = imgProcessor.MatToBitmap( showImg );
						 ChoosePanelIndex( imgProcessor.imgProcess.oprateImg );

						 pnl_showImg->BackgroundImage = tempBitMap;
					 }
				 }
				 btn_apply->Enabled = true;
			 }

			 //框中输入亮度，按回车应用
	private: System::Void txtbx_bright_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyCode == Keys::Enter && !e->Control)
				 {
					 try{
						 int brightValue = Convert::ToInt32( txtbx_bright->Text );
						 if ((brightValue > 100) || (brightValue <- 100))
						 {
							 MessageBox::Show("输入无效，请输入-100到100之间的整数");
						 }
						 else
						 {
							 slider_bright->Value = brightValue;
							 if (isApplyInitialChange == true)
							 {


								 if ( imgProcessor.imgProcess.oprateImg.channels() == 1)
								 {

								 }
								 else{
									 int i = slider_bright->Value;
									 txtbx_bright->Text = i.ToString();
									 imgProcessor.imgProcess.BrightChange(i);
									 System::Drawing::Bitmap^ tempBitMap;
									 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
									 imgProcessor.imgProcess.oprateImg.copyTo( showImg );
									 tempBitMap = imgProcessor.MatToBitmap( showImg );
									 ChoosePanelIndex( imgProcessor.imgProcess.oprateImg );

									 pnl_showImg->BackgroundImage = tempBitMap;
								 }
							 }
							 btn_apply->Enabled = true;
						 }
					 }
					 catch(System::Exception^ e)
					 {
						 String ^ i = e->ToString();
						 MessageBox::Show(i);
						 txtbx_bright->Clear();
					 }
				 }
			 }

			 //鼠标滚轮控制滑块调整亮度
	private: System::Void slider_bright_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){

				 brightWheelNum = slider_bright->Value;
				 brightWheelNum += e->Delta /12;

				 if ( brightWheelNum < -100)
				 {
					 brightWheelNum = -100;
				 }
				 if ( brightWheelNum > 100) 
				 {
					 brightWheelNum = 100;
				 }

				 slider_bright->Value =  brightWheelNum;
				 slider_bright_MouseUp(this->slider_bright, e );

			 }


			 /************************************************************************/
			 /*    说明：边缘检测                                                    */                                     
			 /************************************************************************/
			 //选择边缘检测方法
	private: System::Void edgeDtcMethod_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

				 if (isApplyInitialChange == true)
				 {

					 txtbx_lowThreshold->Clear();


					 if(combo_EdgeDtcMethod->SelectedIndex == 1){

						 txtbx_lowThreshold->Enabled = false;
						 int method = combo_EdgeDtcMethod->SelectedIndex;
						 imgProcessor.imgProcess.EdgeDetection( 0,method );
						 System::Drawing::Bitmap^ tempBitMap;
						 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
						 imgProcessor.imgProcess.oprateImg.copyTo( showImg );
						 tempBitMap = imgProcessor.MatToBitmap(showImg);
						 pnl_showImg->BackgroundImage = tempBitMap;
						 btn_apply->Enabled = true;

					 }
					 if (combo_EdgeDtcMethod->SelectedIndex == 0){
						 txtbx_lowThreshold->Enabled = true;} 
				 }
			 }

			 //输入低阈值
	private: System::Void lowThreshold_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {



				 if (e->KeyCode == Keys::Enter && !e->Control)
				 {
					 int method = combo_EdgeDtcMethod->SelectedIndex;
					 try{

						 int low=Convert::ToInt32(txtbx_lowThreshold->Text);
						 if(low>85){
							 MessageBox::Show("输入无效，请输入小于85的数");
						 }
						 else{
							 imgProcessor.imgProcess.EdgeDetection(low,method);
							 System::Drawing::Bitmap^ tempBitMap;
							 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
							 imgProcessor.imgProcess.oprateImg.copyTo(showImg);
							 tempBitMap = imgProcessor.MatToBitmap(showImg);
							 ChoosePanelIndex(imgProcessor.imgProcess.oprateImg);
							 pnl_showImg->BackgroundImage = tempBitMap;
							 btn_apply->Enabled = true;
						 }
					 }

					 catch(System::Exception^ e)
					 {
						 String ^ i = e->ToString();
						 MessageBox::Show(i);
						 txtbx_lowThreshold->Clear();
					 }



				 }}


			 /************************************************************************/
			 /*    说明：图像平滑                                                    */                                     
			 /************************************************************************/
			 //输入kernelLength
	private: System::Void kernekLength_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyCode == Keys::Enter && !e->Control)
				 {
					 try{
						 int kernelValue=Convert::ToInt32(txtbx_kernekLength->Text);
						 int method = combo_smoothingMethod->SelectedIndex;
						 if(kernelValue>50){
							 MessageBox::Show("无效的输入，请输入小于50的正整数");
						 }
						 else{
							 imgProcessor.imgProcess.Smoothing(method,kernelValue);
							 System::Drawing::Bitmap^ tempBitMap;
							 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
							 imgProcessor.imgProcess.oprateImg.copyTo(showImg);
							 tempBitMap = imgProcessor.MatToBitmap(showImg);
							 pnl_showImg->BackgroundImage = tempBitMap;
							 btn_apply->Enabled = true;
						 }
					 }
					 catch(System::Exception^ e)
					 {
						 String ^ i = e->ToString();
						 MessageBox::Show(i);
						 txtbx_kernekLength->Clear();
					 }
				 }

			 }

			 //选择平滑处理的方法
	private: System::Void smoothingMethod_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 txtbx_kernekLength->Clear();
				 if ((combo_smoothingMethod->SelectedIndex >= 0)&&(combo_smoothingMethod->SelectedIndex <= 3))
				 {
					 txtbx_kernekLength->Enabled = true;
				 }
			 }


			 /************************************************************************/
			 /*    说明：阈值                                                        */                                     
			 /************************************************************************/
			 //选择阈值方法
	private: System::Void thresholdMethod_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 slider_threshold->Value = 0;
				 if ((combo_thresholdMethod->SelectedIndex >= 0)&&(combo_thresholdMethod->SelectedIndex <= 4))
				 {
					 slider_threshold->Enabled = true;
					 txtbx_thred->Enabled = true;
				 }
			 }

			 //改变阈值
	private: System::Void threshold_slider_ValueChanged(System::Object^  sender, System::EventArgs^  e) {


				 if (isApplyInitialChange == true)
				 {
					 try{
						 int thresholdValue=slider_threshold->Value;

						 txtbx_thred->Text = thresholdValue.ToString();
						 int method = combo_thresholdMethod->SelectedIndex;
						 imgProcessor.imgProcess.Threshold(method,thresholdValue);
						 //cv::Mat normalImg = cv::Mat::zeros(imgProcessor.imgProcess.oprateImg.size(), imgProcessor.imgProcess.oprateImg.type() );
						 //cv::normalize(normalImg, imgProcessor.imgProcess.oprateImg, 0, 255, CV_MINMAX);
						 // imgShow.ShowMat(imgProcessor.imgProcess.oprateImg,(HWND)this->pnl_showImg->Handle.ToInt32() ,3);
						 System::Drawing::Bitmap^ tempBitMap;
						 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
						 imgProcessor.imgProcess.oprateImg.copyTo(showImg);
						 tempBitMap = imgProcessor.MatToBitmap(showImg);
						 pnl_showImg->BackgroundImage = tempBitMap;
						 btn_apply->Enabled = true;
					 }
					 catch(System::Exception ^e)
					 {
						 String ^ i = e->ToString();
						 MessageBox::Show(i);
						 slider_threshold->Value = 0;
					 }
				 }

			 }

			 //框中输入阈值
	private: System::Void txtbx_thred_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyCode == Keys::Enter && !e->Control)
				 {
					 try{
						 int thresholdValue = Convert::ToInt32(txtbx_thred->Text);
						 if ((thresholdValue<0)||(thresholdValue>255))
						 {
							 MessageBox::Show("输入无效，请输入0到255之间的整数");
						 }
						 else
						 {
							 slider_threshold->Value = thresholdValue;
						 }
					 }
					 catch(System::Exception^ e)
					 {
						 String ^ i = e->ToString();
						 MessageBox::Show(i);
						 txtbx_thred->Clear();
					 }
				 }
			 }


			 /************************************************************************/
			 /*    说明：list保存、选择图片，更新历史记录                            */                                     
			 /************************************************************************/
			 //每次应用改变后修改list
	public: void UpdateImgList(){

				lstView_historyList->Items->Clear();
				historyImgList->Images->Clear();
				BacktoIntialState();
				if(imgProcessor.imgProcess.imgHistoryVec.size() == 0){
					return;
				}
				std::vector<cv::Mat>::iterator itrMat = imgProcessor.imgProcess.imgHistoryVec.end();
				std::vector<std::string>::iterator itrString = imgProcessor.imgProcess.lastChangeVec.end();
				do{
					itrMat--;
					itrString--;
					cv::Mat histortyMat = *itrMat;
					System::Drawing::Bitmap^ tempBitMap;
					tempBitMap=imgProcessor.MatToBitmap(histortyMat);
					historyImgList->Images->Add(tempBitMap);
					std::string tempStdString = *itrString;
					String ^ tempString = marshal_as<String^>(tempStdString);



					lstView_historyList->Items->Add(tempString);
					lstView_historyList->Items[lstView_historyList->Items->Count-1]->ImageIndex = lstView_historyList->Items->Count-1;
				}while(itrMat != imgProcessor.imgProcess.imgHistoryVec.begin());                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             

			}

			//点击应用变化按钮，变化后图片显示在listView中
	private: System::Void applyChange_Click(System::Object^  sender, System::EventArgs^  e) {


				 ChangeApply();
				 imgProcessor.imgProcess.Reset();
				 btn_apply->Enabled = false;

			 }

			 //选择list上的图片，并显示在panel上
	private: System::Void lstView_historyList_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

				 System::Drawing::Bitmap^ itemBitMap; 
				 cv::Mat itemMat;
				 int itemIndex;
				 String^ itemName;

				 for each(ListViewItem^ item in lstView_historyList->SelectedItems){

					 // if(lstView_historyList->SelectedItems->Count <= 0){return;}


					 if (lstView_historyList->SelectedItems->Count!=0)
					 {

						 itemIndex = item->Index;
						 itemName = item->Name;

					 }			

				 }
				 int vectorIndex = imgProcessor.imgProcess.imgHistoryVec.size() - itemIndex - 1;
				 imgProcessor.imgProcess.oprateImg = imgProcessor.imgProcess.imgHistoryVec[vectorIndex].clone();
				 imgProcessor.imgProcess.imgHistoryVec[vectorIndex].copyTo(imgProcessor.imgProcess.oprateImg);
				 imgProcessor.imgProcess.lastChange = imgProcessor.imgProcess.lastChangeVec[vectorIndex];
				 imgProcessor.imgProcess.lastChangeIndex.currentImg++;
				 imgProcessor.imgProcess.lastChangeIndex.lastImg = imgProcessor.imgProcess.changeIndexVec[vectorIndex].lastImg;
				 imgProcessor.imgProcess.lastChangeIndex.name = imgProcessor.imgProcess.changeIndexVec[vectorIndex].name;
				 imgProcessor.imgProcess.lastChangeIndex.detail = imgProcessor.imgProcess.changeIndexVec[vectorIndex].detail;

				 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
				 imgProcessor.imgProcess.oprateImg.copyTo(showImg);
				 itemBitMap = imgProcessor.MatToBitmap(showImg);
				 pnl_showImg->BackgroundImage = itemBitMap;

				 //弹出对话框询问是否应用改变
				 String^ message = "真的要应用改变吗？";
				 String^ caption = "  ";
				 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				 System::Windows::Forms::DialogResult result;
				 imgProcessor.imgProcess.Reset();


				 result = MessageBox::Show( this, message, caption, buttons );
				 if ( result == ::DialogResult::Yes )
				 { 							 
					 cv::Mat temp =imgProcessor.imgProcess.oprateImg.clone();
					 imgProcessor.imgProcess.oprateImg.copyTo(temp);
					 imgProcessor.imgProcess.imgHistoryVec.push_back(temp);
					 imgProcessor.imgProcess.lastChangeVec.push_back(imgProcessor.imgProcess.lastChange);
					 imgProcessor.imgProcess.changeIndexVec.push_back(imgProcessor.imgProcess.lastChangeIndex);


					 imgProcessor.imgProcess.originalImg = imgProcessor.imgProcess.oprateImg.clone();
					 imgProcessor.imgProcess.oprateImg.copyTo(imgProcessor.imgProcess.originalImg);


					 imgProcessor.imgProcess.SavePicture(imgProcessor.imgProcess.tempFilePath);
					 //imgProcessor.imgProcess.ReLoadPicture();
					 if (imgProcessor.imgProcess.oprateImg.channels() == 1)
					 {
						 pnl_showHstgrm->Refresh();
						 panel_fft->Refresh();
					 }
					 else{
						 imgProcessor.imgProcess.Histogram();
						 imgShow.ShowMat(imgProcessor.imgProcess.histogram,(HWND)this->pnl_showHstgrm->Handle.ToInt32() ,3);
						 imgProcessor.imgProcess.FourierTransform();
						 char* fftPath = "C:\\Users\\Public\\Pictures\\Sample Pictures\\Fourier.jpg";
						 cv::Mat fftImage = cv::imread(fftPath);
						 panel_fft->Refresh();
						 imgShow.ShowMat(fftImage,(HWND)this->panel_fft->Handle.ToInt32() ,3);

					 }
					 // UpdateLstView = false;

					 UpdateImgList();
				 } 
				 //lstView_historyList->SelectedItems->Clear();
				 //UpdateLstView = true;
				 if(result == ::DialogResult::No)
				 {
					 imgProcessor.imgProcess.originalImg = imgProcessor.imgProcess.imgHistoryVec[imgProcessor.imgProcess.imgHistoryVec.size()-1].clone();
					 imgProcessor.imgProcess.imgHistoryVec[imgProcessor.imgProcess.imgHistoryVec.size()-1].copyTo(imgProcessor.imgProcess.originalImg);
					 imgProcessor.imgProcess.lastChange = imgProcessor.imgProcess.lastChangeVec[imgProcessor.imgProcess.lastChangeVec.size()-1];
					 imgProcessor.imgProcess.lastChangeIndex = imgProcessor.imgProcess.changeIndexVec[imgProcessor.imgProcess.changeIndexVec.size()-1];
					 System::Drawing::Bitmap^ tempBitMap;
					 cv::Mat showImg = imgProcessor.imgProcess.originalImg.clone();
					 imgProcessor.imgProcess.originalImg.copyTo(showImg);
					 tempBitMap = imgProcessor.MatToBitmap(showImg);
					 pnl_showImg->BackgroundImage = tempBitMap;

				 }



			 }

			 //鼠标离开时expandblePanel收回
	private: System::Void exPnl_showHistory_Leave(System::Object^  sender, System::EventArgs^  e) {
				 this->exPnl_showHistory->Expanded = false;
			 }

	private: System::Void exPnl_showHistory_ExpandedChanged(System::Object^  sender, DevComponents::DotNetBar::ExpandedChangeEventArgs^  e) {
				 this->exPnl_showHistory->Focus();
			 }
			 /************************************************************************/
			 /*    说明：灰度图                                                      */                                     
			 /************************************************************************/	

	private: System::Void grayProcess_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (imgProcessor.imgProcess.oprateImg.channels() == 1)
				 {
					 MessageBox::Show("这张图片不适合转换为灰度图");
				 }
				 else{
					 if(imgProcessor.imgProcess.oprationState["angle"]
					 ||imgProcessor.imgProcess.oprationState["contrast_bright"]
					 ||imgProcessor.imgProcess.oprationState["edgeDetection"]
					 ||imgProcessor.imgProcess.oprationState["smoothing"]
					 ||imgProcessor.imgProcess.oprationState["threshold"]
					 ||imgProcessor.imgProcess.oprationState["scale"]){
						 String^ message = "是否应用当前变化？";
						 String^ caption = "  ";
						 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
						 System::Windows::Forms::DialogResult result;


						 // Displays the MessageBox.
						 result = MessageBox::Show( this, message, caption, buttons );
						 if ( result == ::DialogResult::Yes )
						 { 
							 ChangeApply();
						 }
						 if(result == ::DialogResult::No)
						 {
							 imgProcessor.imgProcess.originalImg = imgProcessor.imgProcess.imgHistoryVec[imgProcessor.imgProcess.imgHistoryVec.size()-1].clone();
							 imgProcessor.imgProcess.imgHistoryVec[imgProcessor.imgProcess.imgHistoryVec.size()-1].copyTo(imgProcessor.imgProcess.originalImg);
							 imgProcessor.imgProcess.lastChange = imgProcessor.imgProcess.lastChangeVec[imgProcessor.imgProcess.lastChangeVec.size()-1];
							 imgProcessor.imgProcess.lastChangeIndex = imgProcessor.imgProcess.changeIndexVec[imgProcessor.imgProcess.changeIndexVec.size()-1];
							 System::Drawing::Bitmap^ tempBitMap;
							 cv::Mat showImg = imgProcessor.imgProcess.originalImg.clone();
							 imgProcessor.imgProcess.originalImg.copyTo(showImg);
							 tempBitMap = imgProcessor.MatToBitmap(showImg);
							 pnl_showImg->BackgroundImage = tempBitMap;

						 }
						 imgProcessor.imgProcess.Reset();
					 } 
					 String^ message = "真的要进行灰度处理吗？";
					 String^ caption = "  ";
					 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
					 System::Windows::Forms::DialogResult result;


					 // Displays the MessageBox.
					 result = MessageBox::Show( this, message, caption, buttons );
					 if ( result == ::DialogResult::Yes )
					 {  
						 imgProcessor.imgProcess.GrayProcessing();
						 System::Drawing::Bitmap^ tempBitMap;
						 cv::Mat showImg = imgProcessor.imgProcess.oprateImg.clone();
						 imgProcessor.imgProcess.oprateImg.copyTo(showImg);
						 tempBitMap = imgProcessor.MatToBitmap(showImg);
						 ChoosePanelIndex(imgProcessor.imgProcess.oprateImg);

						 /*	 imgProcessor.imgProcess.oprateImg = imgProcessor.imgProcess.grayImg.clone();
						 imgProcessor.imgProcess.grayImg.copyTo(imgProcessor.imgProcess.oprateImg);*/

						 pnl_showImg->BackgroundImage = tempBitMap;
						 cv::Mat temp = imgProcessor.imgProcess.oprateImg.clone();
						 imgProcessor.imgProcess.oprateImg.copyTo(temp);
						 imgProcessor.imgProcess.imgHistoryVec.push_back(temp);
						 imgProcessor.imgProcess.lastChangeVec.push_back(imgProcessor.imgProcess.lastChange);
						 imgProcessor.imgProcess.lastChangeIndex.lastImg = imgProcessor.imgProcess.lastChangeIndex.currentImg;
						 imgProcessor.imgProcess.lastChangeIndex.currentImg++;
						 imgProcessor.imgProcess.changeIndexVec.push_back(imgProcessor.imgProcess.lastChangeIndex);

						 UpdateImgList();
						 imgProcessor.imgProcess.SavePicture(imgProcessor.imgProcess.tempFilePath);
						 imgProcessor.imgProcess.ReLoadPicture();
						 pnl_showHstgrm->Refresh();
						 panel_fft->Refresh();
						 btn_apply->Enabled = false;
					 }
				 }
			 }

			 /************************************************************************/
			 /*    说明：傅里叶图                                                    */                                     
			 /************************************************************************/

	private: System::Void panel_fft_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

				 if ((imgProcessor.imgProcess.loadFlag == true)&&(imgProcessor.imgProcess.imgHistoryVec.empty()==false))
				 {
					 imgProcessor.imgProcess.loadFlag = false;
					 if(imgProcessor.imgProcess.oprateImg.channels() == 3){
						 char* fftPath="C:\\Users\\Public\\Pictures\\Sample Pictures\\Fourier.jpg";
						 cv::Mat ttfImage = cv::imread(fftPath);

						 imgShow.ShowMat(ttfImage,(HWND)this->panel_fft->Handle.ToInt32() ,3);//显示傅里叶图				
					 }
					 else if (imgProcessor.imgProcess.oprateImg.channels() == 1)
					 {
						 panel_fft->Refresh();
					 }
					 imgProcessor.imgProcess.loadFlag = true;
				 }
			 }

			 /************************************************************************/
			 /*    说明：直方图                                                      */                                     
			 /************************************************************************/

	private: System::Void pnl_showHstgrm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 if ((imgProcessor.imgProcess.loadFlag == true)&&(imgProcessor.imgProcess.imgHistoryVec.empty() == false)){
					 imgProcessor.imgProcess.loadFlag = false;
					 if(imgProcessor.imgProcess.oprateImg.channels() == 3){
						 imgShow.ShowMat(imgProcessor.imgProcess.histogram,(HWND)this->pnl_showHstgrm->Handle.ToInt32() ,3);//显示直方图

					 }
					 else if (imgProcessor.imgProcess.oprateImg.channels() == 1)
					 {
						 pnl_showHstgrm->Refresh();
					 }
					 imgProcessor.imgProcess.loadFlag = true;
				 }

			 }



			 /************************************************************************/
			 /*    说明：点击导出原图按钮，选择保存路径                              */                                     
			 /************************************************************************/

	private: System::Void btn_export_Click(System::Object^  sender, System::EventArgs^  e) {

				 changeIndex tempChangeIndex;
				 SaveFileDialog ^ saveFileDialog1 = gcnew SaveFileDialog();
				 saveFileDialog1->Filter = 
					 "JPeg Image|*.jpg|Bitmap Image|*.bmp|Gif Image|*.gif";
				 saveFileDialog1->Title = "Save an Image File";
				 saveFileDialog1->ShowDialog();
				 if (String::IsNullOrEmpty(saveFileDialog1->FileName))
				 {
					 return;
				 }

				 else
				 { 
					 if(imgProcessor.imgProcess.oprationState["angle"]
					 ||imgProcessor.imgProcess.oprationState["contrast_bright"]
					 ||imgProcessor.imgProcess.oprationState["edgeDetection"]
					 ||imgProcessor.imgProcess.oprationState["smoothing"]
					 ||imgProcessor.imgProcess.oprationState["threshold"]
					 ||imgProcessor.imgProcess.oprationState["gray"]
					 ||imgProcessor.imgProcess.oprationState["scale"]){

						 ChangeApply();
					 }
					 tempChangeIndex = imgProcessor.imgProcess.lastChangeIndex;
					 imgProcessor.imgProcess.tempExportMat = imgProcessor.imgProcess.oprateImg.clone();
					 imgProcessor.imgProcess.oprateImg.copyTo(imgProcessor.imgProcess.tempExportMat);

					 String^ picPath = saveFileDialog1->FileName;
					 imgProcessor.unchangedImgPath = ManagedStr2UnmanagedChar(picPath); 

				 }

				 BGW_export->RunWorkerAsync();
				 loadingForm.ShowDialog();
				 MessageBox::Show("完成！");

				 imgProcessor.imgProcess.Reset();
				 imgProcessor.imgProcess.lastChangeIndex = tempChangeIndex;
				 imgProcessor.imgProcess.originalImg = imgProcessor.imgProcess.tempExportMat.clone();
				 imgProcessor.imgProcess.tempExportMat.copyTo(imgProcessor.imgProcess.originalImg);
				 imgProcessor.imgProcess.oprateImg = imgProcessor.imgProcess.tempExportMat.clone();
				 imgProcessor.imgProcess.tempExportMat.copyTo(imgProcessor.imgProcess.oprateImg);

				 System::Drawing::Bitmap^ tempBitMap;
				 cv::Mat showImg = imgProcessor.imgProcess.originalImg.clone();
				 imgProcessor.imgProcess.originalImg.copyTo(showImg);
				 tempBitMap = imgProcessor.MatToBitmap(showImg);
				 pnl_showImg->BackgroundImage = tempBitMap;
			 }

	private: System::Void BGW_export_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

				 imgProcessor.SaveOriginalImg(pnl_showImg);
			 }

	private: System::Void BGW_export_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
				 loadingForm.Close();
			 }
	};
}
