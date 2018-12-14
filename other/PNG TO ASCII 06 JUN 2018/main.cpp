#include "lodepng.h"
#include <iostream>
#include <fstream>

float getGrayMean(std::vector<std::vector<float>>& vec, unsigned& x, unsigned& y, int& w, int& h)
{
	int startX = x;
	int endX = x + w > vec[0].size() ? vec[0].size() : x + w;
	int startY = y;
	int endY = y + h > vec.size() ? vec.size() : y + h;

	float sum = 0;
	for (int i = startY; i < endY; ++i)
	{
		for (int j = startX; j < endX; ++j)
		{
			sum += vec[i][j];
		}
	}

	return (sum / (w * h));
}

int main(int argc, char** argv)
{
	struct Image
	{
		unsigned width;
		unsigned height;
		std::vector<unsigned char> data;
	};

	// Create and fill image.
	Image image;
	std::string path = argc > 1 ? argv[1] : "";
	unsigned error = lodepng::decode(image.data, image.width, image.height, path);

	// Print error (file error).
	if (error)
	{
		std::cout << "Decoder error " << error << ": " << lodepng_error_text(error) << ".\nPress enter to continue." << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}
	
	// Get 2D array.
	std::vector<float> buf;
	std::vector<std::vector<float>> array;
	for (unsigned i = 0; i < image.data.size(); ++i)
	{
		float sum = 0;
		for (int j = 0; j < 3; ++j)
		{
			sum += image.data[i];
			++i;
		}

		buf.push_back(sum / 3);

		if (buf.size() == image.width)
		{
			array.push_back(buf);
			buf.clear();
		}
	}
	
	// Calculate scale.
	int limit = 300;
	int w = 1, h = 1;
	if (image.width > limit || image.height > limit)
	{
		w = image.width / limit;
		h = image.height / limit;
	}

	// Convert to ASCII
	std::vector<std::vector<float>> table;
	
	for (unsigned i = 0; i < array.size(); i += h)
	{
		buf.clear();
		for (unsigned j = 0; j < array[i].size(); j += w)
		{
			
			buf.push_back(getGrayMean(array, j, i, w, h));
		}

		table.push_back(buf);
	}

	// Get output file name.
	std::string filename = "";
	for (unsigned i = path.size() - 1; i >= 0; --i)
	{
		if (path[i] == '.')
		{
			for (unsigned j = i - 1; j >= 0; --j)
			{
				if (path[j] == '\\' || path[j] == '/')
					break;
				filename += path[j];
			}
			break;
		}
	}
	std::reverse(filename.begin(), filename.end());

	// Create output file.
	std::fstream file(filename + ".txt", std::ios::in | std::ios::out | std::ios::app);
	if (file.bad())
	{
		std::cout << "Can not create output file.\nPress enter to continue." << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}

	// Write to file.
	std::string gray = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
	for (unsigned i = 0; i < table.size(); ++i)
	{
		for (unsigned j = 0; j < table[i].size(); ++j)
		{
			file << gray[static_cast<int>((table[i][j] / 0xFF) *gray.size())];
		}
		file << std::endl;
	}

	return 0;
}