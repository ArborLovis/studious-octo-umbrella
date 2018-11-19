
#include "Scramble_data.h"
#include "tiva_headers.h"

void Scramble_data(float* re, float*im, uint16_t len)
{
	float temp_re; // temporary storage complex variable swaps
	float temp_im;
	uint16_t i; // current sample index
	uint16_t j = 0; // bit reversed index
	uint16_t k; // used to propagate carryovers

	uint16_t N2 = len/2; // N2 = N >> 1

	// Bit-reversing algorithm. Since 0 -> 0 and N-1 -> N-1
	// under bit-reversal,these two reversals are skipped.

	for(i = 1; i < (len-1); i++)
	{
		k = N2; // k is 1 in msb, 0 elsewhere

		while( k <= j) // Propagate carry to the right if bit is 1
		{
			j = j - k; // Bit tested is 1, so clear it.
			k = k>>1; // Carryover binary 1to right one bit.
		}

		j = j+k; // current bit tested is 0, add 1 to that bit

		// Swap samples if current index is less than bit reversed index.
		if(i < j)
		{
			temp_re = re[j];
			temp_im = im[j];

			re[j] = re[i];
			im[j] = im[i];

			re[i] = temp_re;
			im[i] = temp_im;
		}	
	}
}
