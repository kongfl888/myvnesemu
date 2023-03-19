#include "xBRZ/xbrz.h"

/***************************************************************************/
/* xBRZ C implementation */

/*
 * [K] 2023-03-19 Checked
 */


void xbrz2x32(euI32* srcPtr, euI32 srcPitch, euI32* dstPtr, euI32 dstPitch, int width, int height)
{
	xbrz::scale(2, (const uint32_t*)srcPtr, (uint32_t*)dstPtr, width, height, xbrz::ColorFormat::RGB);
}

void xbrz3x32(euI32* srcPtr, euI32 srcPitch, euI32* dstPtr, euI32 dstPitch, int width, int height)
{
	xbrz::scale(3, (const uint32_t*)srcPtr, (uint32_t*)dstPtr, width, height, xbrz::ColorFormat::RGB);
}

void xbrz4x32(euI32* srcPtr, euI32 srcPitch, euI32* dstPtr, euI32 dstPitch, int width, int height)
{
	xbrz::scale(4, (const uint32_t*)srcPtr, (uint32_t*)dstPtr, width, height, xbrz::ColorFormat::RGB);
}
