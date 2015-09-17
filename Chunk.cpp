#include "Chunk.hpp"

namespace png
{
	ChunkTypeBytes Chunk::typeToBytes(Type ct)
	{
		switch(ct)
		{
			case Type::IHDR:
				return {{'I', 'H', 'D', 'R'}};

			case Type::PLTE:
				return {{'P', 'L', 'T', 'E'}};

			case Type::IDAT:
				return {{'I', 'D', 'A', 'T'}};

			case Type::IEND:
				return {{'I', 'E', 'N', 'D'}};

			case Type::bKGD:
				return {{'b', 'K', 'G', 'D'}};

			case Type::cHRM:
				return {{'c', 'H', 'R', 'M'}};

			case Type::gAMA:
				return {{'g', 'A', 'M', 'A'}};

			case Type::hIST:
				return {{'h', 'I', 'S', 'T'}};

			case Type::iCCP:
				return {{'i', 'C', 'C', 'P'}};

			case Type::iTXt:
				return {{'i', 'T', 'X', 't'}};

			case Type::pHYs:
				return {{'p', 'H', 'Y', 's'}};

			case Type::sBIT:
				return {{'s', 'B', 'I', 'T'}};

			case Type::sPLT:
				return {{'s', 'P', 'L', 'T'}};

			case Type::sRGB:
				return {{'s', 'R', 'G', 'B'}};

			case Type::sTER:
				return {{'s', 'T', 'E', 'R'}};

			case Type::tEXt:
				return {{'t', 'E', 'X', 't'}};

			case Type::tIME:
				return {{'t', 'I', 'M', 'E'}};

			case Type::tRNS:
				return {{'t', 'R', 'N', 'S'}};

			case Type::zTXt:
				return {{'z', 'T', 'X', 't'}};

			default:
				return {{0, 0, 0, 0}};
		}
	}

	Chunk::Type Chunk::bytesToType(ChunkTypeBytes ctb)
	{
		switch(ctb[0])
		{
			case 'I':
				switch(ctb[1])
				{
					case 'D':
						return Type::IDAT;

					case 'E':
						return Type::IEND;

					case 'H':
						return Type::IHDR;

					default:
						break;
				}
				break;

			case 'P':
				return Type::PLTE;

			case 'b':
				return Type::bKGD;

			case 'c':
				return Type::cHRM;

			case 'g':
				return Type::gAMA;

			case 'h':
				return Type::hIST;

			case 'i':
				switch(ctb[1])
				{
					case 'C':
						return Type::iCCP;

					case 'T':
						return Type::iTXt;

					default:
						break;
				}
				break;

			case 's':
				switch(ctb[1])
				{
					case 'B':
						return Type::sBIT;

					case 'P':
						return Type::sPLT;

					case 'R':
						return Type::sRGB;

					case 'T':
						return Type::sTER;

					default:
						break;
				}
				break;

			case 't':
				switch(ctb[1])
				{
					case 'E':
						return Type::tEXt;

					case 'I':
						return Type::tIME;

					case 'R':
						return Type::tRNS;

					default:
						break;
				}
				break;

			case 'z':
				return Type::zTXt;

			default:
				break;
		}

		return Type::Unknown;
	}

	Chunk::Chunk(Type ct)
	:	length(0),
		type(ct),
		data(nullptr),
		owns(false),
		crc(0)
	{}

	Chunk::Chunk(ChunkTypeBytes ctb)
	:	length(0),
		type(bytesToType(ctb)),
		data(nullptr),
		owns(false),
		crc(0)
	{}

	Chunk::~Chunk()
	{
		if(owns)
		{
			delete data;
		}
	}

	void Chunk::setData(byte* d, unsigned int len, bool alloc)
	{
		if(d)
		{
			if(alloc)
			{
				data = new byte[len];
				std::copy(d, d + len, data);
				length = len;
				owns = true;
			}
			else
			{
				data = d;
				length = len;
				owns = false;
			}
		}
	}
}
