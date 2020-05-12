#include <iostream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <dcm/data_dict.h>
#include <dcm/dicom_file.h>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;
string getTagType(const dcm::DataElement* element);
string getStringTagValue(unsigned int address, dcm::DicomFile* data);
unsigned short getUShortTagValue(unsigned int address, dcm::DicomFile* data);
short getShortTagValue(unsigned int address, dcm::DicomFile* data);
unsigned int getUIntTagValue(unsigned int address, dcm::DicomFile* data);
int getIntTagValue(unsigned int address, dcm::DicomFile* data);
float getFloatTagValue(unsigned int address, dcm::DicomFile* data);
double getDoubleTagValue(unsigned int address, dcm::DicomFile* data);
vector<unsigned short>* readPixels(dcm::DicomFile* data);

dcm::DicomFile* readFile(const char* filePath);
void displayPixels(vector<unsigned short>* pixels);