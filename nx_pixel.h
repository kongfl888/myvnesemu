
void Pixelate16(uint8_t* srcPtr, uint32_t srcPitch, uint8_t* dstPtr, uint32_t dstPitch, int width, int height)
{
	int RGB_LOW_BITS_MASK = 0x0821;
	uint8_t* nextLine, * finish;
	uint32_t colorMask = ~(RGB_LOW_BITS_MASK | (RGB_LOW_BITS_MASK << 16));

	nextLine = dstPtr + dstPitch;

	do {
		uint32_t* bP = (uint32_t*)srcPtr;
		uint32_t* dP = (uint32_t*)dstPtr;
		uint32_t* nL = (uint32_t*)nextLine;
		uint32_t currentPixel;
		uint32_t nextPixel;

		finish = (uint8_t*)bP + ((width + 2) << 1);
		nextPixel = *bP++;

		do {
			currentPixel = nextPixel;
			nextPixel = *bP++;

			if (1) {
				uint32_t _colorA, _colorB, product;

#ifdef WORDS_BIGENDIAN
				_colorA = currentPixel >> 16;
				_colorB = currentPixel & 0xffff;
#else
				_colorA = currentPixel & 0xffff;
				_colorB = currentPixel >> 16;
#endif
				product = (((_colorA & colorMask) >> 1) & colorMask) >> 1;

#ifdef WORDS_BIGENDIAN
				* (nL) = (product << 16) | (product);
				*(dP) = (_colorA << 16) | product;
#else
				* (nL) = product | (product << 16);
				*(dP) = _colorA | (product << 16);
#endif

#ifdef WORDS_BIGENDIAN
				_colorA = nextPixel >> 16;
#else
				_colorA = nextPixel & 0xffff;
#endif
				product = (((_colorB & colorMask) >> 1) & colorMask) >> 1;
#ifdef WORDS_BIGENDIAN
				* (nL + 1) = (product << 16) | (product);
				*(dP + 1) = (_colorB << 16) | (product);
#else
				* (nL + 1) = (product) | (product << 16);
				*(dP + 1) = (_colorB) | (product << 16);
#endif
			}

			dP += 2;
			nL += 2;
			} while ((uint8_t*)bP < finish);

			srcPtr += srcPitch;
			dstPtr += dstPitch << 1;
			nextLine += dstPitch << 1;
		} while (--height);
	}

void Pixelate32(uint8_t* srcPtr, uint32_t srcPitch, uint8_t* dstPtr, uint32_t dstPitch, int width, int height)
{
	int RGB_LOW_BITS_MASK = 0x010101;
	uint8_t* nextLine, * finish;
	uint32_t colorMask = ~RGB_LOW_BITS_MASK;

	nextLine = dstPtr + dstPitch;

	do {
		uint32_t* bP = (uint32_t*)srcPtr;
		//    uint32_t *xP = (uint32_t *) deltaPtr;
		uint32_t* dP = (uint32_t*)dstPtr;
		uint32_t* nL = (uint32_t*)nextLine;
		uint32_t currentPixel;
		uint32_t nextPixel;

		finish = (uint8_t*)bP + ((width + 1) << 2);
		nextPixel = *bP++;

		do {
			currentPixel = nextPixel;
			nextPixel = *bP++;

			uint32_t _colorA, _colorB, product;

			_colorA = currentPixel;
			_colorB = nextPixel;

			product = (((_colorA & colorMask) >> 1) & colorMask) >> 1;
			*(nL) = product;
			*(nL + 1) = product;
			*(dP) = _colorA;
			*(dP + 1) = product;

			nextPixel = *bP++;
			_colorA = nextPixel;
			product = (((_colorB & colorMask) >> 1) & colorMask) >> 1;
			*(nL + 2) = product;
			*(nL + 3) = product;
			*(dP + 2) = _colorB;
			*(dP + 3) = product;

			dP += 4;
			nL += 4;
		} while ((uint8_t*)bP < finish);

		srcPtr += srcPitch;
		dstPtr += dstPitch << 1;
		nextLine += dstPitch << 1;
	} while (--height);
}
