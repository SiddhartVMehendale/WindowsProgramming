#define NUMLINES ((int) (sizeof devcaps / sizeof devcaps[0]))

struct
{
	int iIndex;
	const wchar_t* szLabel;
	const wchar_t* szDesc;
}

devcaps[] =
{
	HORZSIZE, TEXT("HORSIZE"), TEXT("Widht in Millimeters:"),
	VERTSIZE, TEXT("VERTSIZE"), TEXT("Height in Milimeters:"),
	HORZRES, TEXT("HORZRES"),	TEXT("Width in Pixels:"),
	VERTRES, TEXT("VERTREZ"),	TEXT("Height in raster lines:"),
	BITSPIXEL, TEXT("BITSPIXEL"), TEXT("Color bits per pixel:"),
	PLANES, TEXT("PLANES"), TEXT("Number or color planes:"),
	NUMBRUSHES, TEXT("NUMBRESHES"), TEXT("Number of device brushes:"),
	NUMPENS, TEXT("NUMPENS"), TEXT("Number of device pens:"),
	NUMMARKERS, TEXT("NUMARKERS"), TEXT("Number of device markers:"),
	NUMFONTS, TEXT("NUMFONTS"), TEXT("Number of device fonts:"),
	NUMCOLORS, TEXT("NUMCOLORS"), TEXT("Numver of device color:"),
	PDEVICESIZE, TEXT("PDEVSIZE"), TEXT("Size of device structure"),
	ASPECTX, TEXT("ASPECTX"), TEXT("Relative widht of the pixel"),
	ASPECTXY, TEXT("ASPECTXY"), TEXT("Relative diagonal of pixel"),
	ASPECTY, TEXT("ASPECTY"), TEXT("Relative height of the pixel"),
	LOGPIXELSX, TEXT("LOGIPIXELX"), TEXT("Horizantal dots per inches"),
	LOGPIXELSY, TEXT("LOGIPIXELY"), TEXT("Vertical dots per inches"),
	SIZEPALETTE, TEXT("SIZEPALETTE"), TEXT("Number of pallete entries"),
	NUMRESERVED, TEXT("NUMRESERVED"), TEXT("Reserved pallete entries"),
	COLORRES, TEXT("COLORES"), TEXT("Actual color resolution")
};
