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
    : topColor(0)
    , leftColor(0)
    , rightColor(0)
    , bottomColor(0)
    , topWidth(0)
    , leftWidth(0)
    , rightWidth(0)
    , bottomWidth(0)
{	
	topStyle    = LGraphicsContext::SolidPen;
	leftStyle   = LGraphicsContext::SolidPen;
	rightStyle  = LGraphicsContext::SolidPen;
	bottomStyle = LGraphicsContext::SolidPen;
}

Border::~Border()
{
}

void Border::init()
{
	topColor    = 0;
    leftColor   = 0;
	rightColor  = 0;
	bottomColor = 0;
	topWidth    = 0;
	leftWidth   = 0;
	rightWidth  = 0;
	bottomWidth = 0;
	topStyle    = LGraphicsContext::SolidPen;
	leftStyle   = LGraphicsContext::SolidPen;
	rightStyle  = LGraphicsContext::SolidPen;
	bottomStyle = LGraphicsContext::SolidPen;
}

Border::Border(const Border& border)
{
    topColor       = border.topColor;
    leftColor      = border.leftColor;
    rightColor     = border.rightColor;
    bottomColor    = border.bottomColor;
    topWidth       = border.topWidth;
    leftWidth      = border.leftWidth;
    rightWidth     = border.rightWidth;
    bottomWidth    = border.bottomWidth;
    topStyle       = border.topStyle;
    leftStyle      = border.leftStyle;
    rightStyle     = border.rightStyle;
    bottomStyle    = border.bottomStyle;
}

const Border& Border::operator=(const Border& border)
{
    topColor       = border.topColor;
    leftColor      = border.leftColor;
    rightColor     = border.rightColor;
    bottomColor    = border.bottomColor;
    topWidth       = border.topWidth;
    leftWidth      = border.leftWidth;
    rightWidth     = border.rightWidth;
    bottomWidth    = border.bottomWidth;
    topStyle       = border.topStyle;
    leftStyle      = border.leftStyle;
    rightStyle     = border.rightStyle;
    bottomStyle    = border.bottomStyle;
    
    return *this;
}

Style::Style()
{
    init();
	border.init();
}

Style::Style(LFont::FontStyle style)
{
	font.setFontStyle(style);
	init();
	border.init();
}

Style::Style(LUint foregroundColor, LUint backgroundColor, LFont font)
{
	color              = foregroundColor;
	bgColor            = backgroundColor;
	font               = font;
    positionType       = STATICPOSITION ;
    left               = 0;
    top                = 0;
    width              = 0;
    height             = 0;
    leftMargin         = 0;
    rightMargin        = 0;
    topMargin          = 0;
    bottomMargin       = 0;
    transparent        = LTrue;
    textAlignement     = LGraphicsContext::TextLeft;
    topPadding         = 0;
    bottomPadding      = 0;
    leftPadding        = 0;
    rightPadding       = 0;
    displayType        = DIPLAY_ANY;
    scale                = 1;
    border.init();
}

Style::Style(const Style& style)
{
    color                = style.color;
    bgColor              = style.bgColor;
    font               = style.font;
    positionType       = style.positionType ;
    left               = style.left;
    top                = style.top;
    width              = style.width;
    height             = style.height;
    leftMargin         = style.leftMargin;
    rightMargin        = style.rightMargin;
    topMargin          = style.topMargin;
    bottomMargin       = style.bottomMargin;
    transparent        = style.transparent;
    textAlignement     = style.textAlignement;
    topPadding         = style.topPadding;
    bottomPadding      = style.bottomPadding;
    leftPadding        = style.leftPadding;
    rightPadding       = style.rightPadding;
    displayType        = style.displayType;
    scale              = style.scale;
    border             = style.getBorder();
}

void Style::setBorder(const Border& styleBorder)
{
	border = styleBorder;
}

const Border& Style::getBorder() const
{
	return border;
}

const Style& Style::operator=(const Style& style)
{
    color              = style.color;
    bgColor            = style.bgColor;
    font               = style.font;
    positionType       = style.positionType ;
    left               = style.left;
    top                = style.top;
    width              = style.width;
    height             = style.height;
    leftMargin         = style.leftMargin;
    rightMargin        = style.rightMargin;
    topMargin          = style.topMargin;
    bottomMargin       = style.bottomMargin;
    transparent        = style.transparent;
    textAlignement     = style.textAlignement;
    topPadding         = style.topPadding;
    bottomPadding      = style.bottomPadding;
    leftPadding        = style.leftPadding;
    rightPadding       = style.rightPadding;
    displayType        = style.displayType;
    //mBgImg              = style.getBgImage();
    //copy border
    border             = style.getBorder();
    return *this;
}

void Style::init()
{
    color                = COLOR_BLACK;
    bgColor            = 0;
    positionType       = STATICPOSITION;
    displayType        = DIPLAY_ANY;
    left               = 0;
    top                = 0;
    width              = 0;
    height             = 0;
    leftMargin         = 0;
    rightMargin        = 0;
    topMargin          = 0;
    bottomMargin       = 0;
    transparent        = LTrue;
    textAlignement     = LGraphicsContext::TextLeft;
    topPadding         = 0;
    bottomPadding      = 0;
    leftPadding        = 0;
    rightPadding       = 0;
    scale              = 1;
}

}
