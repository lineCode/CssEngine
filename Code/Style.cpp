/*
 *  Style.cpp
 *
 *  Created on: 2011-6-29
 *      Author: yanbo
 */

#include "Style.h"

#include "LColor.h"

namespace util
{

Border::Border()
    : m_topColor(0)
    , m_leftColor(0)
    , m_rightColor(0)
    , m_bottomColor(0)
    , m_topWidth(0)
    , m_leftWidth(0)
    , m_rightWidth(0)
    , m_bottomWidth(0)
{	
	m_topStyle    = LGraphicsContext::SolidPen;
	m_leftStyle   = LGraphicsContext::SolidPen;
	m_rightStyle  = LGraphicsContext::SolidPen;
	m_bottomStyle = LGraphicsContext::SolidPen;
}

Border::~Border()
{
}

void Border::init()
{
	m_topColor    = 0;
    m_leftColor   = 0;
	m_rightColor  = 0;
	m_bottomColor = 0;
	m_topWidth    = 0;
	m_leftWidth   = 0;
	m_rightWidth  = 0;
	m_bottomWidth = 0;
	m_topStyle    = LGraphicsContext::SolidPen;
	m_leftStyle   = LGraphicsContext::SolidPen;
	m_rightStyle  = LGraphicsContext::SolidPen;
	m_bottomStyle = LGraphicsContext::SolidPen;
}

Border::Border(const Border& border)
{
    m_topColor       = border.m_topColor;
    m_leftColor      = border.m_leftColor;
    m_rightColor     = border.m_rightColor;
    m_bottomColor    = border.m_bottomColor;
    m_topWidth       = border.m_topWidth;
    m_leftWidth      = border.m_leftWidth;
    m_rightWidth     = border.m_rightWidth;
    m_bottomWidth    = border.m_bottomWidth;
    m_topStyle       = border.m_topStyle;
    m_leftStyle      = border.m_leftStyle;
    m_rightStyle     = border.m_rightStyle;
    m_bottomStyle    = border.m_bottomStyle;
}

const Border& Border::operator=(const Border& border)
{
    m_topColor       = border.m_topColor;
    m_leftColor      = border.m_leftColor;
    m_rightColor     = border.m_rightColor;
    m_bottomColor    = border.m_bottomColor;
    m_topWidth       = border.m_topWidth;
    m_leftWidth      = border.m_leftWidth;
    m_rightWidth     = border.m_rightWidth;
    m_bottomWidth    = border.m_bottomWidth;
    m_topStyle       = border.m_topStyle;
    m_leftStyle      = border.m_leftStyle;
    m_rightStyle     = border.m_rightStyle;
    m_bottomStyle    = border.m_bottomStyle;
    
    return *this;
}

Style::Style()
{
    init();
	m_border.init();
}

Style::Style(LFont::FontStyle font)
{
	m_font.setFontStyle(font);
	init();
	m_border.init();
}

Style::Style(LInt foregroundColor, LInt backgroundColor, LFont font)
{
	m_color              = foregroundColor;
	m_bgColor            = backgroundColor;
	m_font               = font;
    m_positionType       = STATICPOSITION ;
    m_left               = 0;
    m_top                = 0;
    m_width              = 0;
    m_height             = 0;
    m_leftMargin         = 0;
    m_rightMargin        = 0;
    m_topMargin          = 0;
    m_bottomMargin       = 0;
    m_transparent        = LTrue;
    m_textAlignement     = LGraphicsContext::TextLeft;
    m_topPadding         = 0;
    m_bottomPadding      = 0;
    m_leftPadding        = 0;
    m_rightPadding       = 0;
    m_floatType          = FLOAT_NONE;
    m_displayType        = DIPLAY_ANY;
	m_autoCount          = LFalse;
	m_autoWidth          = LFalse;
	m_columnSpan         = LFalse;
	m_writingMode        = LeftToRightWritingMode;
	m_marginBeforeCollapse = MDISCARD;
	m_marginAfterCollapse  = MDISCARD;
	m_direction            = LTR;
    m_border.init();
}

Style::Style(const Style& style)
{
    m_color              = style.m_color;
    m_bgColor            = style.m_bgColor;
    m_font               = style.m_font;
    m_positionType       = style.m_positionType ;
    m_left               = style.m_left;
    m_top                = style.m_top;
    m_width              = style.m_width;
    m_height             = style.m_height;
    m_leftMargin         = style.m_leftMargin;
    m_rightMargin        = style.m_rightMargin;
    m_topMargin          = style.m_topMargin;
    m_bottomMargin       = style.m_bottomMargin;
    m_transparent        = style.m_transparent;
    m_textAlignement     = style.m_textAlignement;
    m_topPadding         = style.m_topPadding;
    m_bottomPadding      = style.m_bottomPadding;
    m_leftPadding        = style.m_leftPadding;
    m_rightPadding       = style.m_rightPadding;
    m_floatType          = style.m_floatType;
    m_displayType        = style.m_displayType;
	m_writingMode        = style.m_writingMode;
	m_autoCount          = style.m_autoCount;
	m_autoWidth          = style.m_autoWidth;
	m_columnSpan         = style.m_columnSpan;
	m_marginBeforeCollapse = style.m_marginBeforeCollapse;
	m_marginAfterCollapse  = style.m_marginAfterCollapse;
	m_direction            = style.m_direction;
    //mBgImg              = style.getBgImage();
    //copy border
    m_border              = style.getBorder();
}

void Style::setBorder(const Border& border)
{
	m_border = border;
}

const Border& Style::getBorder() const
{
	return m_border;
}

const Style& Style::operator=(const Style& style)
{
    m_color              = style.m_color;
    m_bgColor            = style.m_bgColor;
    m_font               = style.m_font;
    m_positionType       = style.m_positionType ;
    m_left               = style.m_left;
    m_top                = style.m_top;
    m_width              = style.m_width;
    m_height             = style.m_height;
    m_leftMargin         = style.m_leftMargin;
    m_rightMargin        = style.m_rightMargin;
    m_topMargin          = style.m_topMargin;
    m_bottomMargin       = style.m_bottomMargin;
    m_transparent        = style.m_transparent;
    m_textAlignement     = style.m_textAlignement;
    m_topPadding         = style.m_topPadding;
    m_bottomPadding      = style.m_bottomPadding;
    m_leftPadding        = style.m_leftPadding;
    m_rightPadding       = style.m_rightPadding;
    m_floatType          = style.m_floatType;
    m_displayType        = style.m_displayType;
    //mBgImg              = style.getBgImage();
    //copy border
    m_border             = style.getBorder();
	m_writingMode        = style.m_writingMode;
	m_autoCount          = style.m_autoCount;
	m_autoWidth          = style.m_autoWidth;
    m_columnSpan         = style.m_columnSpan;
	m_marginBeforeCollapse = style.m_marginBeforeCollapse;
	m_marginAfterCollapse  = style.m_marginAfterCollapse;
	m_direction            = style.m_direction;
    return *this;
}

void Style::init()
{
    m_color              = COLOR_BLACK;
    m_bgColor            = COLOR_WHITE;
    m_positionType       = STATICPOSITION;
    m_floatType          = FLOAT_NONE;
    m_displayType        = DIPLAY_ANY;
    m_left               = 0;
    m_top                = 0;
    m_width              = 0;
    m_height             = 0;
    m_leftMargin         = 0;
    m_rightMargin        = 0;
    m_topMargin          = 0;
    m_bottomMargin       = 0;
    m_transparent        = LTrue;// ͸�����ʹ�ø����background-color
    m_textAlignement     = LGraphicsContext::TextLeft;
    m_topPadding         = 0;
    m_bottomPadding      = 0;
    m_leftPadding        = 0;
    m_rightPadding       = 0;
	m_writingMode        = LeftToRightWritingMode;
	m_marginBeforeCollapse = MDISCARD;
	m_marginAfterCollapse  = MDISCARD;
	m_autoCount          = LFalse;
	m_autoWidth          = LFalse;
	m_columnSpan         = LFalse;
	m_direction          = LTR;
}

LInt Style::borderBeforeWidth() const
{
	switch (writingMode()) 
    {
    case TopToBottomWritingMode:
		return m_border.m_topWidth;

	case BottomToTopWritingMode:
		return m_border.m_bottomWidth;

	case LeftToRightWritingMode:
		return m_border.m_leftWidth;

	case RightToLeftWritingMode:
		return m_border.m_rightWidth;
	}

	return m_border.m_topWidth;
}

LInt Style::borderAfterWidth() const
{
    
	switch (writingMode()) 
	{
	case TopToBottomWritingMode:
	    return m_border.m_bottomWidth;

	case BottomToTopWritingMode:
	    return m_border.m_topWidth;
    
	case LeftToRightWritingMode:
	    return m_border.m_rightWidth;
    
	case RightToLeftWritingMode:
	    return m_border.m_leftWidth;
	}

    return m_border.m_bottomWidth;
}

LInt Style::paddingBefore() const

{
    
	switch (writingMode()) 
	{
	case TopToBottomWritingMode:
	    return m_topPadding;
    
	case BottomToTopWritingMode:
	    return m_bottomPadding;
    
	case LeftToRightWritingMode:
	    return m_leftPadding;
    
	case RightToLeftWritingMode:
	    return m_rightPadding;
	}

    return m_topPadding;
}

LInt Style::paddingAfter() const
{
	switch (writingMode()) 
	{
	case TopToBottomWritingMode:
	    return m_bottomPadding;
    
	case BottomToTopWritingMode:
	    return m_topPadding;
   
	case LeftToRightWritingMode:
	    return m_rightPadding;
    
	case RightToLeftWritingMode:
	    return m_leftPadding;
	}

    return m_bottomPadding;
}

LInt Style::borderStartWidth() const
{
	if (isHorizontalWritingMode())
	    return isLeftToRightDirection() ? borderLeftWidth() : borderRightWidth();
    
	return isLeftToRightDirection() ? borderTopWidth() : borderBottomWidth();
}

LInt Style::borderLeftWidth() const 
{ 
	return m_border.m_leftWidth; 
}

LInt Style::borderRightWidth() const 
{ 
	return m_border.m_rightWidth; 
}

LInt Style::borderTopWidth() const 
{ 
	return m_border.m_topWidth; 
}

LInt Style::borderBottomWidth() const 
{ 
	return m_border.m_bottomWidth; 
}

LInt Style::paddingLeft() const
{
	return m_leftPadding;
}

LInt Style::paddingRight() const
{
	return m_rightPadding;
}

LInt Style::paddingTop() const
{
	return m_topPadding;
}

LInt Style::paddingBottom() const
{
	return m_bottomPadding;
}

LInt Style::paddingStart() const
{
	if (isHorizontalWritingMode())
	    return isLeftToRightDirection() ? paddingLeft() : paddingRight();
    
	return isLeftToRightDirection() ? paddingTop() : paddingBottom();
}


LInt Style::backgroundColor() const
{
    return m_bgColor;
}

Style::FloatType Style::getFloating() const
{
	return static_cast<FloatType>(m_floatType);
}

}
