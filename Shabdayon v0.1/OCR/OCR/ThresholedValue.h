#pragma once

ref class ThresholedValue
{
private:
	static int num_bins = 256; 
	int xsize;
	int ysize;
	float *counts;
    float sum_counts;
    float *p;
    float *omega;
    float *mu;
    float mu_t;

	System::Drawing::Bitmap^ ImageFile;

	void ImHist();

public:
	ThresholedValue(System::Drawing::Bitmap^);
	~ThresholedValue();
	float GetThresholed();
	void calculateValue();
};
