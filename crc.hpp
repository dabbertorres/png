#ifndef CRC_HPP
#define CRC_HPP

#include <type_traits>

namespace crc
{
	template<typename T, typename std::enable_if<std::is_unsigned<T>::value>::type* = nullptr>
	T get(const char* data, unsigned int numBytes)
	{
		static const unsigned int CRC_BIT_WIDTH = sizeof(T) * 8;
		static const T TOP_BIT = 1 << (CRC_BIT_WIDTH - 1);
		static T POLYNOMIAL = 0;

		if(!POLYNOMIAL)
		{
			switch(sizeof(T))
			{
				case 1:
					POLYNOMIAL = 0xD5;
					break;

				case 2:
					POLYNOMIAL = 0x1021;
					break;

				case 4:
					POLYNOMIAL = 0x04C11DB7;
					break;

				case 8:
					POLYNOMIAL = 0x42F0E1EBA9EA3693;
					break;

				default:
					return 0;
			}
		}

		T crcVal = 0;

		for(auto i = 0u; i < numBytes; ++i)
		{
			crcVal ^= data[i] << (CRC_BIT_WIDTH - 8);

			for(int i = 0; i < 8; ++i)
			{
				crcVal <<= 1;

				if(crcVal & TOP_BIT)
					crcVal ^= POLYNOMIAL;
			}
		}

		return crcVal;
	}
}

#endif
