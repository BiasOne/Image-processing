#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

class pixelData
{
private:
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	
public:
	pixelData()
	{
		blue = 0;
		green = 0;
		red = 0;
	}

	pixelData(unsigned char blue, unsigned char green, unsigned char red)
	{
		this->blue = blue;
		this->green = green;
		this->red = red;	
	}	
	
	void setBlue(unsigned char blue)
	{
		this->blue = blue;
	}
	
	void setGreen(unsigned char green)
	{
		this->green = green;
	}

	void setRed(unsigned char red)
	{
		this->red = red;
	}

	unsigned char getBlue()
	{
		return blue;
	}

	unsigned char getGreen()
	{
		return green;
	}

	unsigned char getRed()
	{
		return red;
	}
};


struct imageData
{
	char  idLength;
	char  colorMapType;
	char  dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char  colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char  bitsPerPixel;
	char  imageDescriptor;
};

void doStuff(string fileName, vector<vector<pixelData>>& vect, imageData& imageDataOBJ,char operation)
{
	pixelData pixelOBJ;

	ifstream file(fileName, ios_base::binary);

	if (file.is_open())
	{
		vect.clear();
		//cout << "file is open" << endl;
		file.read((char*)&imageDataOBJ.idLength, sizeof(imageDataOBJ.idLength));
		file.read((char*)&imageDataOBJ.colorMapType, sizeof(imageDataOBJ.colorMapType));
		file.read((char*)&imageDataOBJ.dataTypeCode, sizeof(imageDataOBJ.dataTypeCode));
		file.read((char*)&imageDataOBJ.colorMapOrigin, sizeof(imageDataOBJ.colorMapOrigin));
		file.read((char*)&imageDataOBJ.colorMapLength, sizeof(imageDataOBJ.colorMapLength));
		file.read((char*)&imageDataOBJ.colorMapDepth, sizeof(imageDataOBJ.colorMapDepth));
		file.read((char*)&imageDataOBJ.xOrigin, sizeof(imageDataOBJ.xOrigin));
		file.read((char*)&imageDataOBJ.yOrigin, sizeof(imageDataOBJ.yOrigin));
		file.read((char*)&imageDataOBJ.width, sizeof(imageDataOBJ.width));
		file.read((char*)&imageDataOBJ.height, sizeof(imageDataOBJ.height));
		file.read((char*)&imageDataOBJ.bitsPerPixel, sizeof(imageDataOBJ.bitsPerPixel));
		file.read((char*)&imageDataOBJ.imageDescriptor, sizeof(imageDataOBJ.imageDescriptor));
		vect.resize(imageDataOBJ.height, vector<pixelData>(imageDataOBJ.width));
		//cout << imageDataOBJ.height << " " << imageDataOBJ.width << endl;
		//add pixels to vector
		unsigned char blue;
		unsigned char green;
		unsigned char red;

		for (int i = 0; i < imageDataOBJ.height; i++)
		{
			for (int j = 0; j < imageDataOBJ.width; j++)
			{
				file.read((char*)&blue, sizeof(blue));
				file.read((char*)&green, sizeof(green));
				file.read((char*)&red, sizeof(red));
				if (operation =='r')
				{
					vect[i][j] = pixelData(red, red, red);
				}
				else if (operation == 'g')
				{
					vect[i][j] = pixelData(green, green, green);
				}
				else if (operation == 'b')
				{
					vect[i][j] = pixelData(blue, blue, blue);
				}
				else
				{
					vect[i][j] = pixelData(blue, green, red);
				}
			}
		}
	}

	else
	{
		cout << "could not open file" << endl;
	}
}

void ReadAndRotate(string fileName, vector<vector<pixelData>>& vect, imageData& imageDataOBJ)
{

	ifstream file(fileName, ios_base::binary);

	if (file.is_open())
	{
		//cout << "file is open" << endl;
		file.read((char*)&imageDataOBJ.idLength, sizeof(imageDataOBJ.idLength));
		file.read((char*)&imageDataOBJ.colorMapType, sizeof(imageDataOBJ.colorMapType));
		file.read((char*)&imageDataOBJ.dataTypeCode, sizeof(imageDataOBJ.dataTypeCode));
		file.read((char*)&imageDataOBJ.colorMapOrigin, sizeof(imageDataOBJ.colorMapOrigin));
		file.read((char*)&imageDataOBJ.colorMapLength, sizeof(imageDataOBJ.colorMapLength));
		file.read((char*)&imageDataOBJ.colorMapDepth, sizeof(imageDataOBJ.colorMapDepth));
		file.read((char*)&imageDataOBJ.xOrigin, sizeof(imageDataOBJ.xOrigin));
		file.read((char*)&imageDataOBJ.yOrigin, sizeof(imageDataOBJ.yOrigin));
		file.read((char*)&imageDataOBJ.width, sizeof(imageDataOBJ.width));
		file.read((char*)&imageDataOBJ.height, sizeof(imageDataOBJ.height));
		file.read((char*)&imageDataOBJ.bitsPerPixel, sizeof(imageDataOBJ.bitsPerPixel));
		file.read((char*)&imageDataOBJ.imageDescriptor, sizeof(imageDataOBJ.imageDescriptor));
		vect.resize(imageDataOBJ.height, vector<pixelData>(imageDataOBJ.width));

		//add pixels to vector
		unsigned char blue;
		unsigned char green;
		unsigned char red;

		for (int i = imageDataOBJ.height-1; i >=0 ; i--)
		{
			for (int j = imageDataOBJ.width-1; j >=0 ; j--)
			{
				file.read((char*)&blue, sizeof(blue));
				file.read((char*)&green, sizeof(green));
				file.read((char*)&red, sizeof(red));
				vect[i][j] = pixelData(blue, green, red);
			}
		}
	}

	else
	{
		cout << "could not open file" << endl;
	}
}

void writeStuff(string fileName, vector<vector<pixelData>>& vect, imageData& imageDataOBJ)
{
	ofstream file(fileName, ios_base::binary);

	if (file.is_open())
	{
		//cout << "file is open" << endl;
		file.write((char*)&imageDataOBJ.idLength, sizeof(imageDataOBJ.idLength));
		file.write((char*)&imageDataOBJ.colorMapType, sizeof(imageDataOBJ.colorMapType));
		file.write((char*)&imageDataOBJ.dataTypeCode, sizeof(imageDataOBJ.dataTypeCode));
		file.write((char*)&imageDataOBJ.colorMapOrigin, sizeof(imageDataOBJ.colorMapOrigin));
		file.write((char*)&imageDataOBJ.colorMapLength, sizeof(imageDataOBJ.colorMapLength));
		file.write((char*)&imageDataOBJ.colorMapDepth, sizeof(imageDataOBJ.colorMapDepth));
		file.write((char*)&imageDataOBJ.xOrigin, sizeof(imageDataOBJ.xOrigin));
		file.write((char*)&imageDataOBJ.yOrigin, sizeof(imageDataOBJ.yOrigin));
		file.write((char*)&imageDataOBJ.width, sizeof(imageDataOBJ.width));
		file.write((char*)&imageDataOBJ.height, sizeof(imageDataOBJ.height));
		file.write((char*)&imageDataOBJ.bitsPerPixel, sizeof(imageDataOBJ.bitsPerPixel));
		file.write((char*)&imageDataOBJ.imageDescriptor, sizeof(imageDataOBJ.imageDescriptor));

		for (int i = 0; i < imageDataOBJ.height; i++)
		{
			for (int j = 0; j < imageDataOBJ.width; j++)
			{
				unsigned char temp = vect[i][j].getBlue();
				file.write((char*)&temp, sizeof(temp));
				temp = vect[i][j].getGreen();
				file.write((char*)&temp, sizeof(temp));
				temp = vect[i][j].getRed();
				file.write((char*)&temp, sizeof(temp));
			}
		}
	}

	else
	{
		cout << "could not open file" << endl;
	}
}

void multiply(short width, short height, vector<vector<pixelData>>& vectOne, vector<vector<pixelData>>& vectTwo)
{
	//C=A*B
	int tempColor;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float temp = ((vectOne[i][j].getBlue() * vectTwo[i][j].getBlue()) / 255.0f) + .5f;

			if ((int)temp > 255)
				tempColor = 255;
			else if ((int)temp < 0)
				tempColor = 0;
			else
				tempColor = (int)temp;

			vectOne[i][j].setBlue(tempColor);

			temp = ((vectOne[i][j].getGreen() * vectTwo[i][j].getGreen()) / 255.0f) + .5f;

			if ((int)temp > 255)
				tempColor = 255;
			else if ((int)temp < 0)
				tempColor = 0;
			else
				tempColor = (int)temp;

			vectOne[i][j].setGreen(tempColor);

			temp = ((vectOne[i][j].getRed() * vectTwo[i][j].getRed()) / 255.0f) + .5f;

			if ((int)temp > 255)
				tempColor = 255;
			else if ((int)temp < 0)
				tempColor = 0;
			else
				tempColor = (int)temp;

			vectOne[i][j].setRed(tempColor);
		}
	}
}

void subtract(short width, short height, vector<vector<pixelData>>& vectOne, vector<vector<pixelData>>& vectTwo)
{
	//C=B1-B2
	int tempColor;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int temp = vectOne[i][j].getBlue() - vectTwo[i][j].getBlue();

			if (temp > 255)
				tempColor = 255;
			else if (temp < 0)
				tempColor = 0;
			else
				tempColor = temp;

			vectOne[i][j].setBlue(tempColor);

			temp = vectOne[i][j].getGreen() - vectTwo[i][j].getGreen();

			if (temp > 255)
				tempColor = 255;
			else if (temp < 0)
				tempColor = 0;
			else
				tempColor = temp;

			vectOne[i][j].setGreen(tempColor);

			temp = vectOne[i][j].getRed() - vectTwo[i][j].getRed();

			if (temp > 255)
				tempColor = 255;
			else if (temp < 0)
				tempColor = 0;
			else
				tempColor = temp;

			vectOne[i][j].setRed(tempColor);
		}
	}
}

void screen(short width, short height, vector<vector<pixelData>>& vectOne, vector<vector<pixelData>>& vectTwo)
{
	//C=1-(1-A)(1-B)
	//oder(1-C)=(1-A)*(1-B)
	int tempColor;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float temp = ((1.0f - ( 1.0f - vectOne[i][j].getBlue()/255.0f) * (1-vectTwo[i][j].getBlue()/255.0f))*255.0f) + .5f;
			

			if ((int)temp > 255)
				tempColor = 255;
			else if ((int)temp < 0)
				tempColor = 0;
			else
				tempColor = (int)temp;

			vectOne[i][j].setBlue(tempColor);

			temp = ((1.0f - (1.0f - vectOne[i][j].getGreen() / 255.0f) * (1 - vectTwo[i][j].getGreen() / 255.0f)) * 255.0f)+.5f;
			
			if ((int)temp > 255)
				tempColor = 255;
			else if ((int)temp < 0)
				tempColor = 0;
			else
				tempColor = (int)temp;

			vectOne[i][j].setGreen(tempColor);

			temp = ((1.0f - (1.0f - vectOne[i][j].getRed() / 255.0f) * (1 - vectTwo[i][j].getRed() / 255.0f)) * 255.0f) + .5f;
			

			if ((int)temp > 255)
				tempColor = 255+.5f;
			else if ((int)temp < 0)
				tempColor = 0;
			else
				tempColor = (int)temp;

			vectOne[i][j].setRed(tempColor);
		}
	}
}

void overlay(short width, short height, vector<vector<pixelData>>& vectOne, vector<vector<pixelData>>& vectTwo)
{
	//B<=0,5: C=2*A*B
	//B>0,5: C=1-2*(1-A)*(1-B)
	int tempColor;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float comparing = vectTwo[i][j].getBlue() / 255.0f;
			float temp;

			if (comparing <= 0.5f)
			{
				temp = (2*(vectOne[i][j].getBlue() * vectTwo[i][j].getBlue()) / 255.0f) + .5f;
				
				if ((int)temp > 255)
					tempColor = 255;
				else if ((int)temp < 0)
					tempColor = 0;
				else
					tempColor = (int)temp;

				vectOne[i][j].setBlue(tempColor);	
			}

			else if (comparing > 0.5f)
			{
				temp = ((1.0f - 2*(1.0f - vectOne[i][j].getBlue() / 255.0f) * (1 - vectTwo[i][j].getBlue() / 255.0f)) * 255.0f) + .5f;
				
				if ((int)temp > 255)
					tempColor = 255;
				else if ((int)temp < 0)
					tempColor = 0;
				else
					tempColor = (int)temp;

				vectOne[i][j].setBlue(tempColor);				
			}


			comparing = vectTwo[i][j].getGreen() / 255.0f;

			if (comparing <= 0.5f)
			{
				 temp = (2 * (vectOne[i][j].getGreen() * vectTwo[i][j].getGreen()) / 255.0f) + .5f;

				if ((int)temp > 255)
					tempColor = 255;
				else if ((int)temp < 0)
					tempColor = 0;
				else
					tempColor = (int)temp;

				vectOne[i][j].setGreen(tempColor);
			}

			else if (comparing > 0.5f)
			{
				 temp = ((1.0f - 2*(1.0f - vectOne[i][j].getGreen() / 255.0f) * (1 - vectTwo[i][j].getGreen() / 255.0f)) * 255.0f) + .5f;

				if ((int)temp > 255)
					tempColor = 255;
				else if ((int)temp < 0)
					tempColor = 0;
				else
					tempColor = (int)temp;

				vectOne[i][j].setGreen(tempColor);
			}


			comparing = vectTwo[i][j].getRed() / 255.0f;

			if (comparing <= 0.5f)
			{
				temp = (2 * (vectOne[i][j].getRed() * vectTwo[i][j].getRed()) / 255.0f) + .5f;

				if ((int)temp > 255)
					tempColor = 255;
				else if ((int)temp < 0)
					tempColor = 0;
				else
					tempColor = (int)temp;

				vectOne[i][j].setRed(tempColor);
			}

			else if (comparing > 0.5f)
			{
				temp = ((1.0f - 2*(1.0f - vectOne[i][j].getRed() / 255.0f) * (1 - vectTwo[i][j].getRed() / 255.0f)) * 255.0f) + .5f;

				if ((int)temp > 255)
					tempColor = 255;
				else if ((int)temp < 0)
					tempColor = 0;
				else
					tempColor = (int)temp;

				vectOne[i][j].setRed(tempColor);
			}	
		}
	}
}

void add(short width, short height, vector<vector<pixelData>>& vectOne)
{
	//C=B1-B2
	int tempColor;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float temp = (((vectOne[i][j].getGreen() / 255.0f) +(200.0f / 255.0f))*255.0f)+.5f;

			if ((int)temp > 255)
				tempColor = 255;
			else if ((int)temp < 0)
				tempColor = 0;
			else
				tempColor = (int)temp;

			vectOne[i][j].setGreen(tempColor);			
		}
	}
}

void seperateRed(short width, short height, vector<vector<pixelData>>& vectOne)
{
	//C=B1-B2
	//cout << "just entered separate red" << endl;
	for (int i = 0; i < 398; i++)
	{
		//cout << "just entered first for loop red - I = " << i << endl;
		for (int j = 0; j < 600; j++)
		{
			//cout << "just entered second for loop red- j = "<< j << endl;
			vectOne[i][j].setGreen(0);
			vectOne[i][j].setBlue(0);
		}
	}
}
void seperateGreen(short width, short height, vector<vector<pixelData>>& vectOne)
{
	//C=B1-B2
	for (int i = 0; i < 398; i++)
	{
		for (int j = 0; j < 600; j++)
		{
			vectOne[i][j].setRed(0);
			vectOne[i][j].setBlue(0);
		}
	}
}
void seperateBlue(short width, short height, vector<vector<pixelData>>& vectOne)
{
	//C=B1-B2
	for (int i = 0; i < 398; i++)
	{
		for (int j = 0; j < 600; j++)
		{
			vectOne[i][j].setRed(0);
			vectOne[i][j].setGreen(0);
		}
	}
}
void combine(short width, short height, vector<vector<pixelData>>& vectOne, vector<vector<pixelData>>& vectTwo)
{
	int tempColor;
	for (int i = 0; i < 398; i++)
	{
		for (int j = 0; j < 600; j++)		{
			

			vectOne[i][j].setBlue(vectTwo[i][j].getBlue()+ vectOne[i][j].getBlue());
			vectOne[i][j].setGreen(vectTwo[i][j].getGreen() + vectOne[i][j].getGreen());
			vectOne[i][j].setRed(vectTwo[i][j].getRed() + vectOne[i][j].getRed());

		}
	}
}
void scale(short width, short height, vector<vector<pixelData>>& vectOne)
{
	//C=B1-B2
	int tempColor;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float temp = ((vectOne[i][j].getRed() / 255.0f) * (4.0f)) * 255.0f;

			if ((int)temp > 255)
				tempColor = 255;
			else if ((int)temp < 0)
				tempColor = 0;
			else
				tempColor = (int)temp;

			vectOne[i][j].setRed(tempColor);

			temp = ((vectOne[i][j].getBlue() / 255.0f) * (0.0f / 255.0f)) * 255.0f;

			if ((int)temp > 255)
				tempColor = 255;
			else if ((int)temp < 0)
				tempColor = 0;
			else
				tempColor = (int)temp;

			vectOne[i][j].setBlue(tempColor);
		}
	}
}

void test(short width, short height, vector<vector<pixelData>>& vectOne, vector<vector<pixelData>>& vectTwo)
{
	//C=A*B
	int count = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			if (vectOne[i][j].getBlue() != vectTwo[i][j].getBlue())
			{
				cout << "pixels do not match" << endl;;
				count++;
			}

			if (vectOne[i][j].getGreen() != vectTwo[i][j].getGreen())
			{
				cout << "pixels do not match" << endl;;
				count++;
			}

			if (vectOne[i][j].getRed() != vectTwo[i][j].getRed())
			{
				cout << "pixels do not match" << endl;;
				count++;
			}			
		}
	}
	if (count == 0)
		cout << "Test Passed" << endl;
	else
		cout << "Test Failed" << endl;
}
int main()
{
	imageData imageDataMain;
	vector<vector<pixelData>> image;
	vector<vector<pixelData>> image2;
	vector<vector<pixelData>> image3;
	vector<vector<pixelData>> testImage;

	//Part 1
	doStuff("input/layer1.tga", image, imageDataMain,'a');
	doStuff("input/pattern1.tga", image2, imageDataMain, 'a');
	multiply(imageDataMain.height, imageDataMain.width, image, image2);
	writeStuff("output/part1.tga", image, imageDataMain);

	//part 1 test
	cout << "Task 1" << endl;
	doStuff("examples/EXAMPLE_part1.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	//Part 2 
	doStuff("input/car.tga", image, imageDataMain, 'a');
	doStuff("input/layer2.tga", image2, imageDataMain, 'a');
	subtract(imageDataMain.height, imageDataMain.width, image, image2);
	writeStuff("output/part2.tga", image, imageDataMain);

	//part 2 test
	cout << "Task 2" << endl;
	doStuff("examples/EXAMPLE_part2.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	//Part 3
	doStuff("input/layer1.tga", image, imageDataMain, 'a');
	doStuff("input/pattern2.tga", image2, imageDataMain, 'a');
	multiply(imageDataMain.height, imageDataMain.width, image, image2);
	doStuff("input/text.tga", image2, imageDataMain, 'a');
	screen(imageDataMain.height, imageDataMain.width, image, image2);
	writeStuff("output/part3.tga", image, imageDataMain);

	//part 3 test
	cout << "Task 3" << endl;
	doStuff("examples/EXAMPLE_part3.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	//Part 4
	doStuff("input/layer2.tga", image, imageDataMain, 'a');
	doStuff("input/circles.tga", image2, imageDataMain, 'a');
	multiply(imageDataMain.height, imageDataMain.width, image, image2);
	doStuff("input/pattern2.tga", image2, imageDataMain, 'a');
	subtract(imageDataMain.height, imageDataMain.width, image, image2);
	writeStuff("output/part4.tga", image, imageDataMain);

	//part 4 test
	cout << "Task 4" << endl;
	doStuff("examples/EXAMPLE_part4.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	//part 5
	doStuff("input/layer1.tga", image, imageDataMain, 'a');
	doStuff("input/pattern1.tga", image2, imageDataMain, 'a');
	overlay(imageDataMain.height, imageDataMain.width, image, image2);
	writeStuff("output/part5.tga", image, imageDataMain);

	//part 5 test
	cout << "Task 5" << endl;
	doStuff("examples/EXAMPLE_part5.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	//part 6
	doStuff("input/car.tga", image, imageDataMain, 'a');
	add(imageDataMain.height, imageDataMain.width, image);
	writeStuff("output/part6.tga", image, imageDataMain);

	//part 6 test
	cout << "Task 6" << endl;
	doStuff("examples/EXAMPLE_part6.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	//part 7
	doStuff("input/car.tga", image, imageDataMain, 'a');
	scale(imageDataMain.height, imageDataMain.width, image);
	writeStuff("output/part7.tga", image, imageDataMain);

	//part 7 test
	cout << "Task 7" << endl;
	doStuff("examples/EXAMPLE_part7.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	//part 8
	doStuff("input/car.tga", image, imageDataMain,'r');
	writeStuff("output/part8_r.tga", image, imageDataMain);

	//part 8 test R
	cout << "Task 8_R" << endl;
	doStuff("examples/EXAMPLE_part8_r.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	doStuff("input/car.tga", image, imageDataMain,'g');
	writeStuff("output/part8_g.tga", image, imageDataMain);

	//part 8 test G
	cout << "Task 8_G" << endl;
	doStuff("examples/EXAMPLE_part8_g.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	doStuff("input/car.tga", image, imageDataMain,'b');
	writeStuff("output/part8_b.tga", image, imageDataMain);

	//part 8 test B
	cout << "Task 8_B" << endl;
	doStuff("examples/EXAMPLE_part8_b.tga", testImage, imageDataMain, 'a');
	test(512, 512, image, testImage);

	//part 9 
	doStuff("input/layer_blue.tga", image, imageDataMain, 'a');
	seperateBlue(imageDataMain.height, imageDataMain.width, image);
	
	doStuff("input/layer_green.tga", image2, imageDataMain, 'a');
	seperateGreen(imageDataMain.height, imageDataMain.width, image2);
	
	doStuff("input/layer_red.tga", image3, imageDataMain, 'a');
	seperateRed(imageDataMain.height, imageDataMain.width, image3);
	
	combine(imageDataMain.height, imageDataMain.width, image, image2);
	combine(imageDataMain.height, imageDataMain.width, image, image3);
	writeStuff("output/part9.tga", image, imageDataMain);

	//part 9 test 
	cout << "Task 9" << endl;
	doStuff("examples/EXAMPLE_part9.tga", testImage, imageDataMain, 'a');
	test(600, 398, image, testImage);

	//part 10
	ReadAndRotate("input/text2.tga", image, imageDataMain);
	writeStuff("output/part10.tga", image, imageDataMain);

	//part 10 test 
	cout << "Task 10" << endl;
	doStuff("examples/EXAMPLE_part10.tga", testImage, imageDataMain, 'a');
	test(184, 384, image, testImage);

	return 0;
}