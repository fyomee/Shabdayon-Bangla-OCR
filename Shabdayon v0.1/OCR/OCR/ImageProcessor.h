#pragma once
#include <vector>
#include "UnitInformation.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace std;

ref class ImageProcessor
{
private:
	int ht;
	int wd;

public:
	ImageProcessor(bool** BArray, int height, int width, vector<UnitInformation> infoUnits, int temporaryFileNumber);
	bool Save_UC_TIF_ImageFromSegmentedInformation(vector<vector<bool>> Img, int temporaryFileNumber);
	void ImageProcessor::SetIndexedPixel(int x,int y, System::Drawing::Imaging::BitmapData^ bmd, bool pixel);
	ImageCodecInfo^ GetEncoderInfo(System::Drawing::Imaging::ImageFormat^ imgFmt);
};