#define NUMLINES ((int)(sizeof sysmetrics / sizeof sysmetrics [0]))

struct
{
	int iIndex;
	const wchar_t* szLabel;
	const wchar_t* szDesc;
}
sysmetrics[] =
{
	SM_CXSCREEN,		TEXT("SM_CXSCREEN"),
						TEXT("Screen width in pixels"),
	SM_CYSCREEN,		TEXT("SM_CYSCREEN"),
						TEXT("Screen height in pixels"),
	SM_CXVSCROLL,		TEXT("SM_CXVSCROLL"),
						TEXT("Vertical scrool width"),
	SM_CYHSCROLL,		TEXT("SM_CYHSCROLL"),
						TEXT("Horizonal scroll height"),
	SM_CYCAPTION,		TEXT("SM_CAPTION"),
						TEXT("Caption bar height"),
	SM_CXBORDER,		TEXT("SM_CXBORDER"),
						TEXT("Window border widht"),
	SM_CYBORDER,		TEXT("SM_CYBORDER"),
						TEXT("Window border height"),
	SM_CXFIXEDFRAME,	TEXT("SM_CXFIXEDFRAME"),
						TEXT("Dialog box window frame widht"),
	SM_CYFIXEDFRAME,	TEXT("SM_CYFIXEDFRAME"),
						TEXT("Dialog box window frame height"),
	SM_CYVTHUMB,		TEXT("SM_CYVTHUMB"),
						TEXT("Vertical scroll thumb height"),
	SM_CXHTHUMB,		TEXT("SM_CYHTHUMB"),
						TEXT("Horizontal scroll thumb width"),
	SM_CXICON,			TEXT("SM_CXICON"),
						TEXT("Icon width"),
	SM_CYICON,			TEXT("SM_CYICON"),
						TEXT("Icon height"),
	SM_CXCURSOR,		TEXT("SM_CXCURSOR"),
						TEXT("Cursor widht"),
	SM_CYCURSOR,		TEXT("SM_CYCURSOR"),
						TEXT("Cursor height"),
	SM_CYMENU,			TEXT("SM_CYMENU"),
						TEXT("Menu bar Height"),
	SM_CXFULLSCREEN,	TEXT("SM_CXFULLSCREEN"),
						TEXT("Full screen client area widht"),
	SM_CYFULLSCREEN,	TEXT("SM_CYFULLSCREEN"),
						TEXT("Full screen client area height"),
	SM_CYKANJIWINDOW,	TEXT("SM_CYKANJIWINDOW"),
						TEXT("Kanji windows height"),
	SM_MOUSEPRESENT,	TEXT("SM_MOUSEPRESENT"),
						TEXT("Mouse present flag"),
	SM_CYVSCROLL,		TEXT("SM_CYVSCROLL"),
						TEXT("Vertical scroll arrow head"),
	SM_CYHSCROLL,		TEXT("SM_CYHSCROLL"),
						TEXT("Horizontal scroll arrow head"),
	SM_DEBUG,			TEXT("SM_DEBUG"),
						TEXT("Debug version flag"),
	SM_SWAPBUTTON,		TEXT("SM_SWAPBUTTON"),
						TEXT("Mouse button swapped flag"),
	SM_CXMIN,			TEXT("SM_CXMIN"),
						TEXT("Minimum window height"),
	SM_CYMIN,			TEXT("SM_CYMIN"),
						TEXT("Minumum windows widht"),
	SM_CXSIZE,			TEXT("SM_CXSIZE"),
						TEXT("Min/max/close button width"),
	SM_CYSIZE,			TEXT("SM_CYSIZE"),
						TEXT("Min/max/close button height"),
	SM_CXSIZEFRAME,		TEXT("SM_CXSIZEFRAME"),
						TEXT("Window sizing frame width"),
	SM_CYSIZEFRAME,		TEXT("SM_CYSIZEFRAME"),
						TEXT("Window sizing frame height"),
	SM_CXMINTRACK,		TEXT("SM_CXMINTRACK"),
						TEXT("Minimum window tracking width"),
	SM_CYMINTRACK,		TEXT("SM_CYMINTRACK"),
						TEXT("Minimum window tracking height"),
	SM_CXDOUBLECLK,		TEXT("SM_CXDOUBLECLICK"),
						TEXT("Double click X tolerence"),
	SM_CYDOUBLECLK,		TEXT("SM_CYDOUBLECLICK"),
						TEXT("Double click Y tolerence"),
	SM_CXICONSPACING,	TEXT("SM_CXICONSPACING"),
						TEXT("Horizantal icon spacing"),
	SM_CYICONSPACING,	TEXT("SM_CYICONSPACING"),
						TEXT("Vertical icon spacing"),
	SM_MENUDROPALIGNMENT,TEXT("SM_MENUDROPALIGNMNET"),
						TEXT("left or right menu drop"),
	SM_PENWINDOWS,		TEXT("SM_PENWINDOWS"),
						TEXT("Pen extentions installed"),
	SM_DBCSENABLED,		TEXT("SM_DBSENABLED"),
						TEXT("Double-Byte Char Set Enabled"),
	SM_CMOUSEBUTTONS,	TEXT("SM_CMOUSEBUTTONS"),
						TEXT("Number of mouse buttons"),
	SM_SECURE,			TEXT("SM_SECURE"),
						TEXT("Security present flag"),
	SM_CXEDGE,			TEXT("SM_CXEDGE"),
						TEXT("3-D border width"),
	SM_CYEDGE,			TEXT("SM_CYEDGE"),
						TEXT("3-D boreder height"),
	SM_CXMINSPACING,	TEXT("SM_CXMINSPACING"),
						TEXT("Minimized window spacing width"),
	SM_CYMINSPACING,	TEXT("SM_CYMINSPACING"),
						TEXT("Minimized window spacing height"),
	SM_CXSMICON,		TEXT("SM_CSMICON"),
						TEXT("Small icon width"),
	SM_CYSMICON,		TEXT("SM_CYMICON"),
						TEXT("Small icon height"),
	SM_CYSMCAPTION,		TEXT("SM_CYSMCAPTION"),
						TEXT("Small caption height"),
	SM_CXSMSIZE,		TEXT("SM_CXMSIZE"),
						TEXT("Small caption Button width"),
	SM_CYSMSIZE,		TEXT("SM_CYMSIZE"),
						TEXT("Small caption Button height"),
	SM_CXMENUSIZE,		TEXT("SM_CXMENUSIZE"),
						TEXT("Menu bar Button width"),
	SM_CYMENUSIZE,		TEXT("SM_CYMENUSIZE"),
						TEXT("Menu bar button height"),
	SM_ARRANGE,			TEXT("SM_ARRANGE"),
						TEXT("How minimized windows arranged"),
	SM_CXMINIMIZED,		TEXT("SM_CXMINIMIZED"),
						TEXT("Minimized window width"),
	SM_CYMINIMIZED,		TEXT("SM_CYMINIZED"),
						TEXT("Minimized window height"),
	SM_CXMAXTRACK,		TEXT("SM_CXMAXTRACK"),
						TEXT("Maximum dragable widht"),
	SM_CYMAXTRACK,		TEXT("SM_CYMAXTRACK"),
						TEXT("Maximum dragable height"),
	SM_CXMAXIMIZED,		TEXT("SM_CXMAXIMIZED"),
						TEXT("Width of maximized window"),
	SM_CYMAXIMIZED,		TEXT("SM_CYMAXIMIZED"),
						TEXT("Height of minimized window"),
	SM_NETWORK,			TEXT("SM_NETWORK"),
						TEXT("Network flag present"),
	SM_CLEANBOOT,		TEXT("SM_CLEANBOOT"),
						TEXT("How system was rebooted"),
	SM_CXDRAG,			TEXT("SM_CXDRAG"),
						TEXT("Avoid drag X tollerence"),
	SM_CYDRAG,			TEXT("SM_CYDRAG"),
						TEXT("Avoid drag Y tollerence"),
	SM_SHOWSOUNDS,		TEXT("SM_SHOWSOUNDS"),
						TEXT("Presents sounds visually"),
	SM_CXMENUCHECK,		TEXT("SM_CXMENUCHECK"),
						TEXT("Menu check-mark width"),
	SM_CYMENUCHECK,		TEXT("SM_CYMENUCHECK"),
						TEXT("Menu check-mark height"),
	SM_SLOWMACHINE,		TEXT("SM_SLOWMACHINE"),
						TEXT("Slow process flag"),
	SM_MIDEASTENABLED,	TEXT("SM_MISEASTENABLED"),
						TEXT("Hebrwe and aracbic flag enabled"),
	SM_MOUSEWHEELPRESENT,TEXT("SM_MOUSEWHEELPRESENT"),
						TEXT("MOUSE WHEEL PRESENT FLAG"),
	SM_XVIRTUALSCREEN,	TEXT("SM_XVIRTUALSCREEN"),
						TEXT("Virtual x screen enabled"),
	SM_YVIRTUALSCREEN,	TEXT("SM_YVIRTUALSCREEN"),
						TEXT("Virtual y screen enabled"),
	SM_CXVIRTUALSCREEN,	TEXT("SM_CXVIRTUALSCREEN"),
						TEXT("Virtual screen width"),
	SM_CYVIRTUALSCREEN,	TEXT("SM_CYVIRUALSCREEN"),
						TEXT("Virtual screen height"),
	SM_CMONITORS,		TEXT("SM_CMONITORS"),
						TEXT("Number of monitors"),
	SM_SAMEDISPLAYFORMAT,TEXT("SM_SAMEDISPLAYFORMAT"),
						TEXT("Same color formate flag")
};