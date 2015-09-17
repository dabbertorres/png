#ifndef PNG_TYPES_HPP
#define PNG_TYPES_HPP

#include <array>

namespace png
{
	using byte = unsigned char;

	using ChunkTypeBytes = std::array<char, 4>;

	enum class ColorType
	{
		Indexed,
		Grayscale,
		GrayscaleAlpha,
		RGB,
		RGBA,
	};
}

#endif
