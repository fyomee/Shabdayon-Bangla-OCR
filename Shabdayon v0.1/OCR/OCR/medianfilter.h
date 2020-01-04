#pragma once

ref class medianfilter
{
private:
	int Size;

	System::Drawing::Bitmap^ ImageFile;

	

public:
	 medianfilter();
	//~ThresholedValue();

	 System::Drawing::Bitmap^ Median(System::Drawing::Bitmap^ , int);
	
};
