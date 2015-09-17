#ifndef PNG_CHUNK_HPP
#define PNG_CHUNK_HPP

#include "Types.hpp"

namespace png
{
	class Chunk
	{
		public:
			enum class Type
			{
				// Critical
				IHDR,
				PLTE,
				IDAT,
				IEND,

				// Ancillary
				bKGD,
				cHRM,
				gAMA,
				hIST,
				iCCP,
				iTXt,
				pHYs,
				sBIT,
				sPLT,
				sRGB,
				sTER,
				tEXt,
				tIME,
				tRNS,
				zTXt,

				// ?
				Unknown,
			};

			static ChunkTypeBytes typeToBytes(Type ct);
			static Type bytesToType(ChunkTypeBytes ctb);

			Chunk(Type ct);
			Chunk(ChunkTypeBytes ctb);

			~Chunk();

			// d is a pointer to all of the memory you want assigned as data to this Chunk
			// len is the length (in bytes) of the d
			// alloc is for whether you want the Chunk to copy the values of what you give it and own the memory (true),
			// or if you want to handle the lifetime of the data and have the Chunk only point to the memory (false)
			void setData(byte* d, unsigned int len, bool alloc = true);

			const Type type;

		private:
			unsigned int length;
			byte* data;
			bool owns;
			unsigned int crc;
	};
}

#endif
