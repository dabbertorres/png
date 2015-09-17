#ifndef PNG_WRITER_HPP
#define PNG_WRITER_HPP

#include <vector>

#include "Types.hpp"
#include "Chunk.hpp"

namespace png
{
	class Writer
	{
		public:
			Writer();
			Writer(unsigned int w, unsigned int h);
			Writer(unsigned int w, unsigned int h, byte bd, ColorType ct);
			~Writer();

			bool toFile(byte* data, const std::string& file);

			void setSize(unsigned int w, unsigned int h);
			void setBitDepth(byte bd);
			void setColorType(ColorType f);

			bool pushChunk(const Chunk& c);

			bool hasIHDR() const;
			bool hasPLTE() const;
			bool hasIDAT() const;
			bool hasIEND() const;

		private:
			std::vector<Chunk> chunks;

			unsigned int width;
			unsigned int height;
			byte bitDepth;
			ColorType colorType;

			bool hasIHDRVal;
			bool hasPLTEVal;
			bool hasIDATVal;
			bool hasIENDVal;
	};
}

#endif
