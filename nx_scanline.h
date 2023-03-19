
static void Scanlines(uint8_t* srcPtr, uint32_t srcPitch, uint8_t* dstPtr, uint32_t dstPitch, int width, int height)
{
	uint8_t* nextLine, * finish;

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
			uint32_t _colorA, _colorB;

#ifdef WORDS_BIGENDIAN
			_colorA = currentPixel >> 16;
			_colorB = currentPixel & 0xffff;
#else
			_colorA = currentPixel & 0xffff;
			_colorB = currentPixel >> 16;
#endif

			* (dP) = _colorA | _colorA << 16;
			*(nL) = 0;

#ifdef WORDS_BIGENDIAN
			_colorA = nextPixel >> 16;
#else
			_colorA = nextPixel & 0xffff;
#endif

			* (dP + 1) = _colorB | (_colorB << 16);
			*(nL + 1) = 0;

			dP += 2;
			nL += 2;
		} while ((uint8_t*)bP < finish);

		srcPtr += srcPitch;
		dstPtr += dstPitch << 1;
		nextLine += dstPitch << 1;
	} while (--height);
}

static void Scanlines32(uint8_t* srcPtr, uint32_t srcPitch, uint8_t* dstPtr, uint32_t dstPitch, int width, int height)
{
	uint8_t* nextLine, * finish;

	nextLine = dstPtr + dstPitch;

	uint32_t _colorA, _colorB;

	do {
		uint32_t* bP = (uint32_t*)srcPtr;
		uint32_t* dP = (uint32_t*)dstPtr;
		uint32_t* nL = (uint32_t*)nextLine;
		uint32_t currentPixel;
		uint32_t nextPixel;

		finish = (uint8_t*)bP + ((width + 1) << 2);
		nextPixel = *bP++;

		do {
			currentPixel = nextPixel;
			nextPixel = *bP++;

			_colorA = currentPixel;
			_colorB = nextPixel;

			*(dP) = _colorA;
			*(dP + 1) = _colorA;
			*(nL) = 0;
			*(nL + 1) = 0;

			*(dP + 2) = _colorB;
			*(dP + 3) = _colorB;
			*(nL + 2) = 0;
			*(nL + 3) = 0;

			nextPixel = *bP++;

			dP += 4;
			nL += 4;
		} while ((uint8_t*)bP < finish);

		srcPtr += srcPitch;
		dstPtr += dstPitch << 1;
		nextLine += dstPitch << 1;
	} while (--height);
}

static void ScanlinesTV(uint8_t* srcPtr, uint32_t srcPitch, uint8_t* dstPtr, uint32_t dstPitch, int width, int height)
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

			uint32_t _colorA, _colorB;

#ifdef WORDS_BIGENDIAN
			_colorA = currentPixel >> 16;
			_colorB = currentPixel & 0xFFFF;
#else
			_colorA = currentPixel & 0xFFFF;
			_colorB = currentPixel >> 16;
#endif

			* (dP) = _colorA = _colorA | ((((_colorA & colorMask) >> 1) +
				((colorB & colorMask) >> 1))) << 16;
			_colorA = ((_colorA & colorMask) >> 1);
			_colorA += ((_colorA & colorMask) >> 1);
			*(nL) = _colorA;

			_colorA = nextPixel & 0xFFFF;

			*(dP + 1) = _colorB = colorB | ((((_colorA & colorMask) >> 1) +
				((_colorB & colorMask) >> 1))) << 16;
			_colorB = ((_colorB & colorMask) >> 1);
			_colorB += ((_colorB & colorMask) >> 1);

			*(nL + 1) = _colorB;

			dP += 2;
			nL += 2;
		} while ((uint8_t*)bP < finish);

		srcPtr += srcPitch;
		dstPtr += dstPitch << 1;
		nextLine += dstPitch << 1;
	} while (--height);
}

static void ScanlinesTV32(uint8_t* srcPtr, uint32_t srcPitch, uint8_t* dstPtr, uint32_t dstPitch, int width, int height)
{
	int RGB_LOW_BITS_MASK = 0x010101;
	uint8_t* nextLine, * finish;
	uint32_t colorMask = ~RGB_LOW_BITS_MASK;

	nextLine = dstPtr + dstPitch;

	do {
		uint32_t* bP = (uint32_t*)srcPtr;
		uint32_t* dP = (uint32_t*)dstPtr;
		uint32_t* nL = (uint32_t*)nextLine;
		uint32_t currentPixel;
		uint32_t nextPixel;

		finish = (uint8_t*)bP + ((width + 1) << 2);
		nextPixel = *bP++;

		do {
			currentPixel = nextPixel;
			nextPixel = *bP++;

			uint32_t _colorA, _colorB, temp;

			_colorA = currentPixel;
			_colorB = nextPixel;

			*(dP) = _colorA;
			*(dP + 1) = temp = ((_colorA & colorMask) >> 1) +
				((_colorB & colorMask) >> 1);
			temp = ((temp & colorMask) >> 1);
			temp += ((temp & colorMask) >> 1);
			_colorA = ((_colorA & colorMask) >> 1);
			_colorA += ((_colorA & colorMask) >> 1);

			*(nL) = _colorA;
			*(nL + 1) = temp;

			dP += 2;
			nL += 2;
		} while ((uint8_t*)bP < finish);

		srcPtr += srcPitch;
		dstPtr += dstPitch << 1;
		nextLine += dstPitch << 1;
	} while (--height);
}
