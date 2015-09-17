#include "Writer.hpp"

#include "crc.hpp"

#include <fstream>

static void writeSignature(std::ofstream& fout);
static void writeIHDR(std::ofstream& fout, unsigned int w, unsigned int h, png::byte bd, png::ColorType ct);

namespace png
{
	Writer::Writer()
	:	width(0),
		height(0),
		bitDepth(0),
		colorType(ColorType::RGBA),
		hasIHDRVal(false),
		hasPLTEVal(false),
		hasIDATVal(false),
		hasIENDVal(false)
	{}

	Writer::Writer(unsigned int w, unsigned int h)
	:	width(w),
		height(h),
		bitDepth(8),
		colorType(ColorType::RGBA),
		hasIHDRVal(false),
		hasPLTEVal(false),
		hasIDATVal(false),
		hasIENDVal(false)
	{}

	Writer::Writer(unsigned int w, unsigned int h, byte bd, ColorType ct)
	:	width(w),
		height(h),
		bitDepth(bd),
		colorType(ct),
		hasIHDRVal(false),
		hasPLTEVal(false),
		hasIDATVal(false),
		hasIENDVal(false)
	{}

	Writer::~Writer()
	{}

	bool Writer::toFile(byte* data, const std::string& file)
	{
		std::ofstream fout(file, std::ios::binary);

		if (!fout)
			return false;
		
		writeSignature(fout);

		writeIHDR(fout, width, height, bitDepth, colorType);

		return true;
	}

	void Writer::setSize(unsigned int w, unsigned int h)
	{
		width = w;
		height = h;
	}

	void Writer::setBitDepth(byte bd)
	{
		bitDepth = bd;
	}

	void Writer::setColorType(ColorType f)
	{
		colorType = f;
	}

	bool Writer::pushChunk(const Chunk& c)
	{
		if(hasIHDRVal && c.type == Chunk::Type::IHDR)
			return false;

		if(hasPLTEVal && c.type == Chunk::Type::PLTE)
			return false;

		if(hasIENDVal && c.type == Chunk::Type::IEND)
			return false;

		return true;
	}

	bool Writer::hasIHDR() const
	{
		return hasIHDRVal;
	}

	bool Writer::hasPLTE() const
	{
		return hasPLTEVal;
	}

	bool Writer::hasIDAT() const
	{
		return hasIDATVal;
	}
	
	bool Writer::hasIEND() const
	{
		return hasIENDVal;
	}
}

void writeSignature(std::ofstream& fout)
{
	// non 8 bit transmission system detector and text file guard byte
	fout.put(0x89);

	// "PNG" format id
	fout.put('P');
	fout.put('N');
	fout.put('G');

	// DOS/Windows line ending
	fout.put(0x0D);
	fout.put(0x0A);

	// DOS end of file character (for the 'type' command)
	fout.put(0x1A);

	// Unix line ending
	fout.put(0x0A);
}

void writeIHDR(std::ofstream& fout, unsigned int w, unsigned int h, png::byte bd, png::ColorType ct)
{
	unsigned int length = sizeof(w) + sizeof(h) + 1 + 1;

	// write length of chunk data
	fout.write(reinterpret_cast<char*>(&length), 4);

	char* typeAndData = new char[4 + length];

	// copy over type
	auto typeBytes = png::Chunk::typeToBytes(png::Chunk::Type::IHDR);
	std::copy(typeBytes.begin(), typeBytes.end(), typeAndData);
	
	// add height and width to char array
	for(int i = 0; i < 4; ++i)
	{
		typeAndData[4 + i] = (w >> i * 8) & 0xFF;
		typeAndData[8 + i] = (h >> i * 8) & 0xFF;
	}

	typeAndData[12] = bd;

	switch(ct)
	{
		case png::ColorType::Indexed:
			typeAndData[13] = 3;
			break;
		case png::ColorType::Grayscale:
			typeAndData[13] = 0;
			break;
		case png::ColorType::GrayscaleAlpha:
			typeAndData[13] = 4;
			break;
		case png::ColorType::RGB:
			typeAndData[13] = 2;
			break;
		case png::ColorType::RGBA:
			typeAndData[13] = 6;
			break;
	}

	// write chunk type and data
	fout.write(typeAndData, 4 + length);

	auto crc = crc::get<unsigned int>(typeAndData, 4 + length);

	fout.write(reinterpret_cast<char*>(&crc), 4);
}
