/*****************************************************************
				this code is created by 
				Farjana Yeasmin Omee & Shiam Shabbir Himel
				Shahjalal University of Science & Technology.
				date: 20th august, 2011 .
******************************************************************/
#include "stdafx.h"
#include "medianfilter.h"
#include "stdio.h"
#include "stdlib.h"
#include "List"
using namespace System;
using namespace System::Collections::Generic;

medianfilter::medianfilter()
{}


System::Drawing::Bitmap^ medianfilter::Median(System::Drawing::Bitmap^ Image, int Size)
{
	System::Drawing::Bitmap^ TempBitmap = Image;
	System::Drawing::Bitmap^ NewBitmap = gcnew System::Drawing::Bitmap(TempBitmap->Width, TempBitmap->Height);
	System::Drawing::Graphics^ NewGraphics =System::Drawing::Graphics::FromImage(NewBitmap);
	NewGraphics->DrawImage(TempBitmap,  System::Drawing::Rectangle(0, 0, TempBitmap->Width, TempBitmap->Height),System::Drawing::RectangleF(0, 0, TempBitmap->Width, TempBitmap->Height), System::Drawing::GraphicsUnit::Pixel);
	delete NewGraphics;
	int TempRandom =rand();
	int ApetureMin = -(Size / 2);
	int ApetureMax = (Size / 2);
	for (int x = 0; x < NewBitmap->Width; ++x)
	{
		for (int y = 0; y < NewBitmap->Height; ++y)
		{
			List<int>^ RValues = gcnew List<int>();
			List<int>^ GValues = gcnew List<int>();
			List<int>^ BValues = gcnew List<int>();

			for (int x2 = ApetureMin; x2 < ApetureMax; ++x2)
			{
				int TempX = x + x2;
				if (TempX >= 0 && TempX < NewBitmap->Width)
				{
					for (int y2 = ApetureMin; y2 < ApetureMax; ++y2)
					{
						int TempY = y + y2;
						if (TempY >= 0 && TempY < NewBitmap->Height)
						{
							System::Drawing::Color^ TempColor = TempBitmap->GetPixel(TempX, TempY);
							RValues->Add(TempColor->R);//Add();
							GValues->Add(TempColor->G);
							BValues->Add(TempColor->B);

						}
					}
				}
			}
			RValues->Sort();
			GValues->Sort();
			BValues->Sort();
			System::Drawing::Color MedianPixel = System::Drawing::Color::FromArgb(RValues[RValues->Count / 3],
				GValues[GValues->Count /3], 
				BValues[BValues->Count / 3]);
			NewBitmap->SetPixel(x, y, MedianPixel);
		}

	}

	return NewBitmap;

}

