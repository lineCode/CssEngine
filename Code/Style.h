/*
 *  Style.h
 *
 *  Created on: 2011-6-23
 *      Author: yanbo
 */

#ifndef Style_h
#define Style_h

#include "LGdi.h"
#include "KRef.h"

namespace util
{

class Border
{
public:
	Border();
	Border(const Border& border);
	~Border();
	const Border& operator=(const Border& border);
	void init();

public:
	LInt                          m_topColor;
	LInt                          m_leftColor;
	LInt                          m_rightColor;
	LInt                          m_bottomColor;
	LInt                          m_topWidth;
	LInt                          m_leftWidth;
	LInt                          m_rightWidth;
	LInt                          m_bottomWidth;
	LInt                          m_topStyle;
	LInt                          m_leftStyle;
	LInt                          m_rightStyle;
	LInt                          m_bottomStyle;
};

class Style : public KRef
{
public:
	typedef enum PositionType
	{
		ABSOLUTEPOSITION,
		FIXEDPOSITION,
		STATICPOSITION,
		RELATIVEPOSITION
	} PositionType;
	
	typedef enum FloatType
	{
		FLOAT_LEFT,
		FLOAT_RIGHT,
		FLOAT_NONE,
		FLOAT_POSITION,
		FLOAT_INHERIT
	} FloatType;
	
	typedef enum DisplayType
	{
		DISPLAY_NONE,
		DISPLAY_BLOCK,
		DISPLAY_INLINE,
		DIPLAY_ANY
	} DisplayType;	

	typedef enum WritingMode 
	{
		TopToBottomWritingMode,
		RightToLeftWritingMode,
		LeftToRightWritingMode,
		BottomToTopWritingMode
	} WritingMode;

	typedef enum EMarginCollapse 
	{ 
		MCOLLAPSE, 
		MSEPARATE, 
		MDISCARD 
	} EMarginCollapse;

	enum EClear
	{
        CNONE = 0, 
		CLEFT = 1, 
		CRIGHT = 2, 
		CBOTH = 3
    };

	enum TextDirection { RTL, LTR };
	
//	typedef enum TextAlignType
//	{
//		TEXTALIGN_LEFT,
//		TEXTALIGN_RIGHT,
//		TEXTALIGN_CENTER,
//		TEXTALIGN_JUSTIFY,
//		TEXTALIGH_INHERIT
//	} TextAlignType;

public:
	Style();
	Style(LFont::FontStyle font);
	Style(LInt foregroundColor, LInt backgroundColor, LFont font);
	Style(const Style& style);
	const Style& operator = (const Style& style);
	void init();
	void copyStyle(Style* style);
	WritingMode writingMode() const { return static_cast<WritingMode>(m_writingMode); }
	LBool hasAutoColumnCount() const { return m_autoCount; }
	LBool hasAutoColumnWidth() const { return m_autoWidth; }
	LBool columnSpan() const { return m_columnSpan; }

	void setMarginBeforeCollapse(EMarginCollapse c) { m_marginBeforeCollapse = c; }
	EMarginCollapse marginBeforeCollapse() const { return static_cast<EMarginCollapse>(m_marginBeforeCollapse); }
	EMarginCollapse marginAfterCollapse() const { return static_cast<EMarginCollapse>(m_marginAfterCollapse); }
	bool isHorizontalWritingMode() const { return writingMode() == TopToBottomWritingMode || writingMode() == BottomToTopWritingMode; }

	LInt top() const { return m_top; }
	LInt left() const { return m_left; }

	LInt width() const { return m_width; }
	LInt height() const { return m_height; }

	LInt marginBottom() const { return m_bottomMargin; }
	LInt marginTop() const { return m_topMargin; }
	LInt marginLeft() const { return m_leftMargin; }
	LInt marginRight() const { return m_rightMargin; }

	LInt borderBeforeWidth() const;
	LInt borderAfterWidth() const;
	LInt borderStartWidth() const;
	LInt borderLeftWidth() const; 
	LInt borderRightWidth() const; 
	LInt borderTopWidth() const;
	LInt borderBottomWidth() const;
	LInt paddingBefore() const;
	LInt paddingAfter() const;

	LInt paddingStart() const;

	LInt paddingLeft() const;
	LInt paddingRight() const;
	LInt paddingTop() const;
	LInt paddingBottom() const;
	TextDirection direction() const { return static_cast<TextDirection>(m_direction); }
	LBool isLeftToRightDirection() const { return direction() == LTR; }

	LInt backgroundColor() const;

	FloatType getFloating() const;

	EClear clear() const { return  static_cast<EClear>(m_clear); }
	
public:
	void setBorder(const Border& border);
	const Border& getBorder() const;

public:
	LInt                          m_color; // foreground color
	LInt                          m_bgColor; // background color
	StringA                       m_bgImageUrl;
	LFont                         m_font;
	LBool                         m_transparent; // if transparent
	LBool                         m_autoCount;
	LBool                         m_autoWidth;
	LBool                         m_columnSpan;
	LInt                          m_positionType;
	LInt                          m_floatType;
	LInt                          m_displayType;
	LInt                          m_left;
	LInt                          m_top;
	LInt                          m_width;
	LInt                          m_height;
	LInt                          m_leftMargin;
	LInt                          m_rightMargin;
	LInt                          m_topMargin;
	LInt                          m_bottomMargin;
	LInt                          m_textAlignement;
	LInt                          m_topPadding;
	LInt                          m_bottomPadding;
	LInt                          m_leftPadding;
	LInt                          m_rightPadding;
	Border                        m_border;
	LInt                          m_writingMode;
	LInt                          m_marginBeforeCollapse;
	LInt                          m_marginAfterCollapse;
	LInt                          m_direction;
	LInt                          m_clear;
};
}
#endif
