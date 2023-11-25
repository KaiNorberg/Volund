#include "PCH/PCH.h"
#include "BitMask.h"

namespace Volund
{
	class BitMask
	{
	public:

		void SetBit(uint8_t index, bool value);

		bool GetBit(uint8_t index);

	private:

		uint64_t m_Bits = 0;
	};
}