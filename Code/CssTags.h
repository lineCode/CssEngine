/*
 * CSSParser.h
 *
 *  Created on: 2011-6-23
 *      Author: yanbo
 */

#ifndef CssTags_h
#define CssTags_h

#include "kmap.h"
#include "UtilString.h"

namespace util
{

typedef KMap<LUint, LInt> CssTypeMap;
/**
 * Objects of this class holds the symbol table for CSS tags.
 * See this class for more info.
 */
class CssTags
{
public:
	//properties
	//properties that are inherited has value > 0.
	//properties that is not inherited has value < 0
	enum CssType
	{
	    WIDTH = -37,
	    HEIGHT,
	    DISPLAY,
	    FLOAT,		
		BACKGROUND_IMAGE,
		PADDING,
		PADDING_TOP,
		PADDING_LEFT,
		PADDING_BOTTOM,
		PADDING_RIGHT,
		BORDER_TOP,
		BORDER_TOP_WIDTH,
		BORDER_BOTTOM,
		BORDER_BOTTOM_WIDTH,
		MARGIN,
		MARGIN_RIGHT,
		MARGIB_BOTTOM,
		MARGIN_TOP,
		MARGIN_LEFT,
		BORDER,
		BORDER_STYLE,
		BORDER_COLOR,
		BORDER_TOP_STYLE,
		BORDER_TOP_COLOR,
		BORDER_LEFT_STYLE,
		BORDER_LEFT_COLOR,
		BORDER_LEFT_WIDTH,
		BORDER_RIGHT_STYLE,
		BORDER_RIGHT_COLOR,
		BORDER_RIGHT_WIDTH,
		BORDER_BOTTOM_COLOR,
		BORDER_BOTTOM_STYLE,
		POSITION,
		LEFT,
		TOP,
		BACKGROUND,
		BACKGROUND_COLOR,
		STYLE_NULL,               // 0
		COLOR,                    // 1
		FONT_SIZE,
		FONT_STYLE,
		FONT_WEIGHT,
		TEXT_ALIGN,
	};
	
public:
	static CssTags* getInstance();
	static void destroyInstance();
	
	void defineInitialSymbol(const StringA& cssText, LInt cssType);
	~CssTags();
	
	int symbolAsInt(LUint inSymbol);
	void clear();
	
private:
	CssTags();	
	
private:
	static CssTags* s_cssTags;
	CssTypeMap m_map;	
};
}
#endif
