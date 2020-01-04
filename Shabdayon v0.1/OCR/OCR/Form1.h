#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include "medianfilter.h"
#include "ThresholedValue.h"
#include "PostProcessor.h"
#include "SkewDetectionCorrection.h"
#include "ImageProcessor.h"
#include "CCAnalyzer.h"
#include "HSegmenter.h"
#include "ConnCompProperties.h"
#include "rgbConvert.h"
#include <iostream>
#include<fstream>

#pragma once
using namespace cv;
using namespace std;
namespace OCR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::IO;


	public ref class Form1 : public System::Windows::Forms::Form
	{
		//gui genereted codes.change may effect program run.
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			this->applicationPath = Application::StartupPath->ToString();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
		/*our variable*/
	private: int thresholdValue;
	private: bool isThValComputed;
	private: bool isGrayImageAvailable;
	private: bool BinaryDone;
	private: bool SkewDone;

	private: Bitmap^ im;
	private: Bitmap^ Image;
	private: Bitmap^ FinalImage;

	private: bool **BArray;
	private: bool **BlockImgArray;
	private: bool **SegImg;
	private: int** grayImageArr;

	private: System::String^ applicationPath;
			 private: System::String^ str; 

	private: int temporaryFileNumber;
	private: ThresholedValue^ ts;
	private: System::String^ recognizerOutput;
			 HSegmenter^ hsg;
			 ImageProcessor^ ip;
		 System::String^ str1;
			 System::String^ output;

private: static int scaleX = 654;
    private: static int scaleY = 464;
	private: int zoomHeight;
	private: int zoomWidth;


	private: rgbConvert^ rgbC;
	private: int xsize;
	private:int ysize;
			/*end of our variable*/

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  bt_Binarize;

	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::CheckBox^  checkBox1;



	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->bt_Binarize = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"open";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(12, 41);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(454, 399);
			this->panel1->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(3, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(448, 393);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// bt_Binarize
			// 
			this->bt_Binarize->Location = System::Drawing::Point(109, 12);
			this->bt_Binarize->Name = L"bt_Binarize";
			this->bt_Binarize->Size = System::Drawing::Size(75, 23);
			this->bt_Binarize->TabIndex = 2;
			this->bt_Binarize->Text = L"Recognize";
			this->bt_Binarize->UseVisualStyleBackColor = true;
			this->bt_Binarize->Click += gcnew System::EventHandler(this, &Form1::bt_Binarize_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button2->Location = System::Drawing::Point(438, 443);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Close";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->richTextBox1);
			this->panel2->Location = System::Drawing::Point(472, 41);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(456, 396);
			this->panel2->TabIndex = 7;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"SolaimanLipi", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(3, 3);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::ForcedHorizontal;
			this->richTextBox1->Size = System::Drawing::Size(450, 390);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->TabStop = false;
			this->richTextBox1->Text = L"";
			this->richTextBox1->ZoomFactor = 2;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(803, 12);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(86, 17);
			this->checkBox1->TabIndex = 8;
			this->checkBox1->Text = L"Multi Column";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(931, 479);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->bt_Binarize);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->panel2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void OpenImageFile ()//function for open image. 
			 {				 				 
				 this->Update();
				 System::Windows::Forms::DialogResult d = this->openFileDialog1->ShowDialog();
				 if (d == System::Windows::Forms::DialogResult::OK)
				 {			 
					 // if open an image
					 // this->panelText->Visible = false;
					 this->Height = 575;
					 this->Width = 705;					
					 SkewDone = false;
					 try{
						 // free image
						 delete im;

						 // creating a bitmap
						 im = gcnew Bitmap(this->openFileDialog1->OpenFile()); 
					 }catch(System::Exception^ ex){
						 System::Windows::Forms::MessageBox::Show("Invalid Image, Message: "+ex->Message,"Invalid Image file!",System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);	
						 return;
					 }					






					 //showing the image
					 this->pictureBox1->Image = im;

					 // Picture Box Related Information initialization
					 this->pictureBox1->Dock = System::Windows::Forms::DockStyle::None;
					 this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Normal;
					 this->pictureBox1->Height=im->Height;
					 this->pictureBox1->Width=im->Width;
					 this->pictureBox1->Update();

					 xsize = im->Height;
					 ysize = im->Width;	



this->pictureBox1->Dock = System::Windows::Forms::DockStyle::None;
			 
			 // Correct the image size based on aspect ratio
			 float aspRatioFactor;
			 if(this->im->Height > this->im->Width)
			 {
				 aspRatioFactor = (float)this->im->Height/scaleY;

				 this->pictureBox1->Height = scaleY;
				 this->pictureBox1->Width = this->im->Width / aspRatioFactor;
			 }else{
				 aspRatioFactor = (float)this->im->Width/scaleX;

				 this->pictureBox1->Height = this->im->Height / aspRatioFactor;
				 this->pictureBox1->Width = scaleX;
			 }

			 this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			 this->pictureBox1->Update();

			 // zoom factors
			 this->zoomHeight = this->pictureBox1->Height;
			 this->zoomWidth = this->pictureBox1->Width;




				 }// end of if()

				 // this->statusText->Text = "Image..";
				 this->Update();	
			 }




	private: bool performSkewCorrection(SkewDetectionCorrection^ skdc)
			 {
				 if (SkewDone)
					 return false;

				 try{
					 //// finding UpperEnvelope
					 skdc->findUpperEnvelope();	 

					 float angelSkew = skdc->GetSkewAngle();

					 // Skew Correction
					 int yIncrSingleSide = 0;
					 int rYsize;


					 float ang = 0 - angelSkew;
					 double angleRAD = Math::PI*ang/180.0;

					 float c = Math::Cos(angleRAD);
					 float s = Math::Sin(angleRAD);
					 rYsize  = (int)Math::Round(Math::Abs(xsize*s) + ysize*c);

					 yIncrSingleSide = (rYsize - ysize)/2;

					 if(yIncrSingleSide>0){
						 int ** grayArr;
						 grayArr = new int * [xsize];
						 for (int i = 0; i < xsize; i++)
						 {
							 grayArr[i] = new int [rYsize];
							 for (int j = 0; j < rYsize; j++)
							 {
								 grayArr[i][j] = 255;
							 }
						 }

						 for (int i = 0; i < xsize; i++)
						 {
							 for (int j = 0; j < ysize; j++)
							 {
								 grayArr[i][j+yIncrSingleSide] = grayImageArr[i][j];
							 }
						 }

						 this->grayImageArr = grayArr;
						 skdc->setYsize(rYsize);
						 this->ysize = rYsize;
					 }

					 // Show DeSkewed Image
					 if(angelSkew != 0.0){
						 skdc->setGrayImageArray(this->grayImageArr);

						 this->grayImageArr = skdc->RotateImgDirectInterpolate(angelSkew);

						 // Restore the binary array
						 ComputeBinaryArray();

						 // Re generate the binary image
						 this->getImage();

						 // Skew Correction
						 im = this->Image;
						 this->pictureBox1->Image = im;
						 im->Save("C:\\im2.jpg");
						 this->pictureBox1->Update();
					 }

					 SkewDone = true;
				 }catch(System::Exception^ ex){
					 System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to deskew the image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					 SkewDone = false;
					 return false;
				 }

				 return true;
			 }// end of function performSkewCorrection()


	private: bool computeThreshold()
			 {
				 try
				 {		 
					 // compute the threshold value
					 ThresholedValue^ ts = gcnew ThresholedValue(im);
					 float fLevel = ts->GetThresholed();			 
					 thresholdValue = int(fLevel*255);
					 return true;
				 }
				 catch(System::Exception^ ex)
				 {
					 System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to compute threshold value!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					 return false;
				 }
			 }

	private: bool makeBinary()
			 {
				 //if (this->BinaryDone)
				 //	 return false;

				 if(!isThValComputed)
				 {
					 isThValComputed = computeThreshold();
				 }

				 try
				 {
					 if(isThValComputed){
						 ///// convert grayscale to binary /////
						 rgbConvert^ rgb = gcnew rgbConvert(im);

						 // convert rgb to grayscale
						 grayImageArr = rgb->getGrayImageArray();
						 isGrayImageAvailable = true;

						 // convert grayscale to binary
						 BArray = rgb->GetBinaryArray(thresholdValue);
					 }else{
						 this->BinaryDone = false;
						 return false;
					 }
				 }
				 catch(System::Exception^ ex)
				 {
					 System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to binarize the image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					 this->BinaryDone = false;
					 return false;
				 }

				 //this->statusText->Text = "Binarization completed..";
				 this->Update();

				 return true;
			 }// end of function MakeBainary()

	private: void ComputeBinaryArray()
			 {
				 BArray = new bool * [xsize];
				 for (int i = 0; i < xsize; i++ )
				 {
					 BArray[i] = new bool[ysize];
				 }

				 int grayC;

				 for ( int xVal = 0; xVal < xsize; xVal++ )
				 {
					 for( int yVal = 0; yVal < ysize; yVal++ )
					 {
						 grayC = grayImageArr[xVal][yVal];

						 if ( grayC >= thresholdValue )
						 {
							 BArray[xVal][yVal] = true;
						 }
						 else
						 {
							 BArray[xVal][yVal] = false;
						 }

					 }// inner for*/
				 }
			 } 
	private: void getImage(){
				 Image = gcnew System::Drawing::Bitmap(ysize, xsize);
				 for (int x = 0; x < xsize; ++x)
				 {
					 for (int y = 0; y < ysize; ++y)
					 {
						 if(BArray[x][y]){
							 Image->SetPixel(y, x, Color::White);
						 }else{
							 Image->SetPixel(y, x, Color::Black);
						 }
					 }
				 }
			 }

	private: void saveBainaryImage(bool **tmpArray, int txs, int tys, int num){
				 System::Drawing::Bitmap^ tImage = gcnew System::Drawing::Bitmap(tys, txs);
				 for (int x = 0; x < txs; ++x)
				 {
					 for (int y = 0; y < tys; ++y)
					 {
						 if(tmpArray[x][y]){
							 tImage->SetPixel(y, x, Color::White);
						 }else{
							 tImage->SetPixel(y, x, Color::Black);
						 }
					 }
				 }

				 tImage->Save("test1.jpg");
			 }


	private:void SaveNoiseElimination(System::Drawing::Bitmap^ NEimage,int xsize,int ysize)
			{
				System::Drawing::Bitmap^ NEImage = NEimage;
				NEImage->Save("C:\\NEimage.tif");


			}


	private: System::String^ RecognizeWord(System::Drawing::Bitmap^ tessImg)
			 {
				 // Perform Recognition by Tesseract and store result
				 System::String^ result = PerformRecognitionByTesseractEXE(tessImg);
				 result = result->Trim();

				 return result;
			 }


	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 //System::Windows::Forms::MessageBox::Show("fghg","Show the image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Exclamation);
				 this->OpenImageFile();
			 }
	private: System::Void bt_Binarize_Click(System::Object^  sender, System::EventArgs^  e) {
				 	  str1 = "";
				 output="C:\\out.doc";
				 isThValComputed = computeThreshold();
				 bool binaryDoneStatus = makeBinary();
				 ComputeBinaryArray();
				 getImage();
				 this->pictureBox1->Image=Image;






				 SkewDetectionCorrection^ skdc = gcnew SkewDetectionCorrection(BArray, im->Height, im->Width);
				 bool skewDoneStatus = performSkewCorrection(skdc);

				 if(!skewDoneStatus){
					 System::Windows::Forms::MessageBox::Show("Unable to perform skew correction!!", "Failed to proceed on skew correction!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					 //return false;
				 }
				 getImage();

				 medianfilter^ mf = gcnew medianfilter();


				 System::Drawing::Bitmap^ noise= mf->Median(Image , 2);

				 this->pictureBox1->Image=noise;
				 saveBainaryImage(BArray, xsize, ysize , 2);
				 SaveNoiseElimination(noise,xsize,ysize);

				 if(checkBox1->Checked)

				 {

					 int i,j,k=0,d=0,x=0,y=0,width=0,height=0,space=0,space1=0,flag=0,l=0,n=0;
					 uchar*    ptr,*ptr1;
					 char name[100],name1[100];
					 IplImage* img,*img1,*img2,*img3;
					 FILE *out,*test;
					 int p[200],sum[200];

					 test=fopen("C:\\example1.txt","w");
					 //sprintf(name,path);
					 img = cvLoadImage("C:\\NEImage.tif");

					 int xsize2=img->height;
					 int ysize2=img->width;
					 for(i=0;i<xsize2;i++)
					 {
						 sum[k]=0;

						 for(j=0;j<ysize2;j++)
						 {
							 ptr = cvPtr2D(img, i,j, NULL);
							 if(ptr[0]==255)
								 sum[k]=sum[k]+0;
							 if(ptr[0]==0)
								 sum[k]=sum[k]+10;
						 }
						 //fprintf(test,"i = %d sum = %d xsize = %d\n",i,sum[k],xsize2);
						 if(sum[k]==0)
						 {
							 //fprintf(test,"i = %d j = %d \n",i,j);
							 p[d]=i;
							 if(d>1)
								 height=p[d]-p[d-1];

							 if(d>1 && height==1 && p[d]!=xsize2)
							 {
								 space++;
								 if(space>12 && p[d]-y>40)
								 {
									 CvRect rect=cvRect(x,y,ysize2, p[d]-x) ;
									 fprintf(test,"x = %d y = %d  Height = %d \n",x,y,height);
									 //CvRect rect=cvRect(x,y,ysize,height+40);
									 y=p[d];

									 img1=cvCloneImage(img);
									 cvSetImageROI(img1,rect);
									 sprintf(name,"C:\\out%d.tif",k);
									 cvSaveImage(name,img1);
									 k++;
									 space=0;
								 }
							 }

							 else
							 {

								 space=0;
							 }

							 d++;
						 }	
						 if(i==xsize2-1)
						 {

							 CvRect rect=cvRect(x,y,ysize2, i) ;

							 //CvRect rect=cvRect(x,y,ysize,height+40);
							 //y=p[d];

							 img1=cvCloneImage(img);
							 cvSetImageROI(img1,rect);
							 sprintf(name,"C:\\out%d.tif",k);
							 cvSaveImage(name,img1);
							 k++;
						 }
					 }
					 int m=k;
					 fprintf(test,"m=%d \n",m);
					 for(l=0;l<m;l++)
					 {
						 flag=0;
						 int x1=0;
						 int y1=0;
						 //n=0;
						 int t=0;
						 if(m>1 && l==0)
						 {
							 sprintf(name,"C:\\out%d.tif",l);
							 img2=cvLoadImage(name);
							 sprintf(name1,"C:\\page%d.tif",n);
							 cvSaveImage(name1,img2);
							 n++;
						 }
						 else{
							 sprintf(name,"C:\\out%d.tif",l);
							 img2=cvLoadImage(name);

							 int xsize1=img2->height;
							 int ysize1=img2->width;


							 for(i=0;i<ysize1;i++)
							 {
								 sum[n]=0;
								 for(j=0;j<xsize1;j++)
								 {
									 ptr1 = cvPtr2D(img2, j,i, NULL);
									 if(ptr1[0]==255)
										 sum[n]=sum[n]+0;
									 if(ptr1[0]==0)
										 sum[n]=sum[n]+10;
								 }
								 //fprintf(test,"i = %d sum = %d ysize1 = %d\n",i,sum[n],ysize1);

								 if(sum[n]<50)
								 { 

									 p[t]=i;
									 if(t>1)
										 width=p[t]-p[t-1];


									 if(t>1 && width<10 && i!=ysize1)
									 {

										 space1++;

										 fprintf(test,"space = %d p[t]-x1=%d\n",space1,p[t]-x1);
										 if(space1>=10 && p[t]-x1>60)
										 {


											 CvRect rect1=cvRect(x1,y1,p[t]-x1,xsize1);
											 if(ysize-p[t]<25)
												 flag=1;
											 x1=p[t];
											 img3=cvCloneImage(img2);
											 cvSetImageROI(img3,rect1);
											 sprintf(name1,"C:\\page%d.tif",n);
											 cvSaveImage(name1,img3);
											 n++;
											 space1=0;
										 }


									 }
									 else
									 {

										 space1=0;

									 }

									 t++;
								 }

								 if(i==ysize1-1 && flag==0)
								 {
									 //fprintf(test,"i = %d \n",i);
									 CvRect rect1=cvRect(x1,y1,i,xsize1);
									 img3=cvCloneImage(img2);
									 cvSetImageROI(img3,rect1);
									 sprintf(name1,"C:\\page%d.tif",n);
									 cvSaveImage(name1,img3);
									 n++;
								 }
							 }
						 }
					 }


					 for(int tn=0;tn<n;tn++)
					 {



						 try{
							 // free image
							 delete im;

							  str="C:\\page"+tn+".tif";
							 // creating a bitmap
							 im = gcnew Bitmap(str,true); 
						 }catch(System::Exception^ ex){
							 System::Windows::Forms::MessageBox::Show("Invalid Image, Message: "+ex->Message,"Invalid Image file!",System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);	
							 return;
						 }					

						 //showing the image
						 this->pictureBox1->Image = im;

						 // Picture Box Related Information initialization
						 this->pictureBox1->Dock = System::Windows::Forms::DockStyle::None;
						 this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Normal;
						 this->pictureBox1->Height=im->Height;
						 this->pictureBox1->Width=im->Width;
						 this->pictureBox1->Update();

						 xsize = im->Height;
						 ysize = im->Width;					 

			


						 isThValComputed = computeThreshold();
						 bool binaryDoneStatus = makeBinary();
						 ComputeBinaryArray();
						 getImage();
						 this->pictureBox1->Image=Image;

						 saveBainaryImage(BArray, xsize, ysize , 2);
						 //SaveNoiseElimination(noise,xsize,ysize);

						 FinalImage = gcnew Bitmap(ysize, xsize);
						 for (int i=0; i<xsize; i++)
						 {
							 for (int j=0; j<ysize; j++)
							 {

								 FinalImage->SetPixel(j, i, Color::White);
							 }
						 }




						 // Task 5 : Segmentation
						 hsg = gcnew HSegmenter(this->BArray, xsize, ysize);		
						 vector<UnitInformation> infoUnits = hsg->SegmentWords();

						 if(!hsg->segmentSuccess){
							 System::Windows::Forms::MessageBox::Show("Unable to perform segmentation!!", "Failed to proceed on segmentation!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
							 // return false;
						 }

						 // Save this image into the required image format of tesseract	using segmentation information

						 this->temporaryFileNumber = 1;
						 ip = gcnew ImageProcessor(this->BArray, xsize, ysize, infoUnits, this->temporaryFileNumber);



						 // Start Recognition (by tesseract)
						 im = gcnew System::Drawing::Bitmap(Application::StartupPath + "\\Tesseract\\temp"+ this->temporaryFileNumber +".tif");

						 //showing the image units
						 this->pictureBox1->Image = im;
						 this->pictureBox1->Update();


						 // Task 6 : Recognition
						 recognizerOutput = RecognizeWord(im);

						 // free resources
						 infoUnits.clear();
						 //}
						 this->PerformPostProcessing();

						 System::Windows::Forms::MessageBox::Show("Complete","recognige the image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Information);

						 //fprintf(test,"%d %d %d %d \n",x,y,width,xsize1);

						// System::IO::File::Delete(str);
					 

					 }


					 fclose(test);
					 cvReleaseImage(&img);


				 }

				 else{

					 FinalImage = gcnew Bitmap(ysize, xsize);
					 for (int i=0; i<xsize; i++)
					 {
						 for (int j=0; j<ysize; j++)
						 {

							 FinalImage->SetPixel(j, i, Color::White);
						 }
					 }




					 // Task 5 : Segmentation
					 hsg = gcnew HSegmenter(this->BArray, xsize, ysize);		
					 vector<UnitInformation> infoUnits = hsg->SegmentWords();

					 if(!hsg->segmentSuccess){
						 System::Windows::Forms::MessageBox::Show("Unable to perform segmentation!!", "Failed to proceed on segmentation!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
						 // return false;
					 }

					 // Save this image into the required image format of tesseract	using segmentation information

					 this->temporaryFileNumber = 1;
					 ip = gcnew ImageProcessor(this->BArray, xsize, ysize, infoUnits, this->temporaryFileNumber);



					 // Start Recognition (by tesseract)
					 im = gcnew System::Drawing::Bitmap(Application::StartupPath + "\\Tesseract\\temp"+ this->temporaryFileNumber +".tif");

					 //showing the image units
					 this->pictureBox1->Image = im;
					 this->pictureBox1->Update();


					 // Task 6 : Recognition
					 recognizerOutput = RecognizeWord(im);

					 // free resources
					 infoUnits.clear();
					 //}
					 this->PerformPostProcessing();
					 if(binaryDoneStatus)
						 System::Windows::Forms::MessageBox::Show("Complete","recognige the image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Information);
				 }
System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(output);
				 sw->WriteLine(str1);
				 sw->Close();
				 //return true;
			 }
	private: System::String^ PerformRecognitionByTesseractEXE(System::Drawing::Bitmap^ tessImg)
			 {
					 System::String^ strRes="";
				 //////
				 System::String^ execDir  = this->applicationPath + "\\Tesseract";
				 System::String^ execDrive = execDir->Substring(0,execDir->IndexOf(":")+1);
				 System::String^ outputFile  = this->applicationPath + "\\Tesseract\\out.txt";
				 System::String^ tempTessFile  = this->applicationPath + "\\Tesseract\\tesseract.log";
				 System::String^ batchFile  = this->applicationPath + "\\Tesseract\\bat.bat";

				 try
				 {
					 // build and execute the batch file
					 System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(batchFile);
					 System::String^ tempStr = "";

					 // building the associate command for the initialization
					 tempStr += execDrive + "\n";
					 tempStr += "cd " + execDir + "\n";			// required for training from single sample
					 tempStr += "tesseract " + "temp" + this->temporaryFileNumber + ".tif" + " " + "out" + " " + "-l" + " " + "ban";

					 sw->Write(tempStr);
					 sw->Close();

					 // create a process and execute 
					 System::Diagnostics::ProcessStartInfo^ psInfo = gcnew System::Diagnostics::ProcessStartInfo(batchFile);
					 psInfo->CreateNoWindow = true;
					 psInfo->WindowStyle = System::Diagnostics::ProcessWindowStyle::Hidden;
					 System::Diagnostics::Process^ p = gcnew System::Diagnostics::Process();
					 p->StartInfo = psInfo;
					 p->Start();
					 p->WaitForExit();					 
				 }
				 catch (System::Exception^ excp)
				 {
					 System::Windows::Forms::MessageBox::Show(excp->Message->ToString(),"Can't Create/Execute Viterbi Decoder!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					 exit(0);
				 }	

				 // read the outputfile
				 System::String^ tempStr = "";

				 try
				 {
					 System::IO::StreamReader^ sr = gcnew System::IO::StreamReader(outputFile);
					 while (!System::String::IsNullOrEmpty((tempStr = sr->ReadLine())))
					 {
						 strRes += " " + tempStr;
						 str1 += " " + tempStr+"\n";
					 }
					 sr->Close();
					 

					 // Delete the temporary files
					 System::IO::File::Delete(batchFile);
					 //System::IO::File::Delete(outputFile);
					 System::IO::File::Delete(tempTessFile);
				 }
				 catch(System::Exception^ ex)
				 {
					 System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Unable to delete the temporary files!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					 exit(0);
				 }
				 ///////
				 str1+="\n";
				 return strRes;
			 }

	private: void deleteTemporaryImageFilesUsingCMD(){
				 System::String^ batchFile  = this->applicationPath + "\\Tesseract\\tmfFileRemove.bat";
				 System::String^ execDir  = this->applicationPath + "\\Tesseract";
				 System::String^ execDrive = execDir->Substring(0,execDir->IndexOf(":")+1);
				 System::IO::StreamWriter^ sw;

				 try
				 {
					 // build and execute the batch file
					 sw = gcnew System::IO::StreamWriter(batchFile);
					 System::String^ tempStr = "";

					 // building the associate command for the initialization
					 tempStr += execDrive + "\n";
					 tempStr += "cd " + execDir + "\n";			// required for training from single sample
					 tempStr += "del " + "*.tif";

					 sw->Write(tempStr);
					 sw->Close();

					 // create a process and execute 
					 System::Diagnostics::ProcessStartInfo^ psInfo = gcnew System::Diagnostics::ProcessStartInfo(batchFile);
					 psInfo->CreateNoWindow = true;
					 psInfo->WindowStyle = System::Diagnostics::ProcessWindowStyle::Hidden;
					 System::Diagnostics::Process^ p = gcnew System::Diagnostics::Process();
					 p->StartInfo = psInfo;
					 p->Start();
					 p->WaitForExit();	
				 }
				 catch (System::Exception^ excp)
				 {
					 System::Windows::Forms::MessageBox::Show(excp->Message->ToString(),"Can't Create/Execute Viterbi Decoder!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					 exit(0);
				 }

				 // Delete the batch file
				 try{
					 if(File::Exists(batchFile)){
						 // File::Delete(batchFile);
					 }
				 }
				 catch (System::Exception^ excp){
				 }
			 }
	private: void deleteTemporaryImageFiles()
			 {	
				 try{
					 System::String^ tempFileName = "";

					 tempFileName = Application::StartupPath + "\\Tesseract\\temp1.tif";
					 if(File::Exists(tempFileName)){
						 //File::Delete(tempFileName);
						}

				 }
				 catch(System::Exception^ ex)
				 {
					 System::Windows::Forms::MessageBox::Show("Problem in deleting temporary image files. Please restart the application., Message: "+ex->Message,"Failed to Process the Image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					 return;
				 }
			 }


	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {



				 // delete previous temporary image files (this is a temporary solution as we are experiencing the problem : A generic error occured in GDI+)
				 //deleteTemporaryImageFiles();
			 }

	private: void PerformPostProcessing(){
				 // Perform Post Processing Task


				 PostProcessor^ pr = gcnew PostProcessor(this->recognizerOutput);

				  //ofstream* out;
			
				
					 
				 this->richTextBox1->Text = pr->TextPostProcessor2();




				 // free resources
				 pr->~PostProcessor();
				 delete pr;
			 }



	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }



};
}