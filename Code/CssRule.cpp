/*
 * CssRule.cpp
 *
 *  Created on: 2011-6-23
 *      Author: yanbo
 */

#include "CssRule.h"
#include "CssTags.h"
#include "LGdi.h"
#include "SalLog.h"

namespace util
{

SimpleSelector::SimpleSelector()
	: m_relation(Descendant)
	, m_pseudoType(PseudoNotParsed)
{
}

SimpleSelector::~SimpleSelector()
{
}

void SimpleSelector::setSelectorText(const StringA& selectorText)
{
	m_selectorText = selectorText;

	int index = m_selectorText.FindNoCase(_CS(":"));
    if (index > 0)
    {
		setMatch(SimpleSelector::PseudoClass);
		 // such as a:active
        StringA pseudoName = m_selectorText.Left(index);
        StringA pseudoClass = m_selectorText.Right(m_selectorText.GetLength()-index-1);

        if (pseudoClass == _CS("active"))
        {					
			setPseudoType(SimpleSelector::PseudoActive);
        }
        else if (pseudoClass == _CS("visited"))
        {
			setPseudoType(SimpleSelector::PseudoVisited);
        }
        else if (pseudoClass == _CS("link"))
        {
			setPseudoType(SimpleSelector::PseudoLink);
        }
        else if (pseudoClass == _CS("hover"))
		{
			setPseudoType(SimpleSelector::PseudoHover);
        }
        else
        {
		    setPseudoType(SimpleSelector::PseudoNotParsed);
        }

		return;
	}

	if (m_selectorText.StartWith(_CS("#")))
	{
		setMatch(SimpleSelector::Id);
	}
	else if (m_selectorText.StartWith(_CS(".")))
	{
		setMatch(SimpleSelector::Class);
	}
	else
	{
		setMatch(SimpleSelector::Tag);
	}
}

void SimpleSelector::setMatch(LUint match)
{
	m_match = match;
}

SimpleSelector::Match SimpleSelector::getMatch() const
{
	return static_cast<SimpleSelector::Match>(m_match);
}

const StringA& SimpleSelector::getSelectorText() const
{
	return m_selectorText;
}

void SimpleSelector::setRelation(LUint relation)
{
	m_relation = relation;
}

SimpleSelector::Relation SimpleSelector::getRelation() const
{
	return static_cast<SimpleSelector::Relation>(m_relation);
}

void SimpleSelector::setPseudoType(LUint pseudoType)
{
    m_pseudoType = pseudoType;
}

SimpleSelector::PseudoType SimpleSelector::getPseudoType() const
{
	return static_cast<SimpleSelector::PseudoType>(m_pseudoType);
}

CssPropertyValue::CssPropertyValue()
    : intVal(0)
{
	resetSpecificity();
}

CssPropertyValue::CssPropertyValue(const CssPropertyValue& proValue)
{
	intVal = proValue.intVal;
	strVal = proValue.strVal;

	m_specificity.m_id = proValue.m_specificity.m_id;
	m_specificity.m_important = proValue.m_specificity.m_important;
	m_specificity.m_classOrPseudo = proValue.m_specificity.m_classOrPseudo;
	m_specificity.m_tag = proValue.m_specificity.m_tag;
}


CssPropertyValue::~CssPropertyValue()
{	
}

const CssPropertyValue& CssPropertyValue::operator = (const CssPropertyValue& proValue)
{
	intVal = proValue.intVal;
	strVal = proValue.strVal;

	m_specificity.m_id = proValue.m_specificity.m_id;
	m_specificity.m_important = proValue.m_specificity.m_important;
	m_specificity.m_classOrPseudo = proValue.m_specificity.m_classOrPseudo;
	m_specificity.m_tag = proValue.m_specificity.m_tag;
	return *this;
}

void CssPropertyValue::resetSpecificity()
{
	m_specificity.m_important = 0;
	m_specificity.m_id = 0;
	m_specificity.m_tag = 0;
	m_specificity.m_classOrPseudo = 0;
}

void CssPropertyValue::computeSpecificity(const Selector* selector)
{
	CssPropertyValue::computeSpecificity(selector, m_specificity);
}

void CssPropertyValue::computeSpecificity(const Selector* selector, PropertySpecificity& specificity)
{
	LInt num = selector->size();
	for (LInt i = 0; i < num; i++)
	{
		switch (selector->elementAt(i).getMatch())
		{
		case SimpleSelector::Id:
			{
			    specificity.m_id += 1;
			}
			break;
		case SimpleSelector::Class:
		case SimpleSelector::PseudoClass:
			{
			    specificity.m_classOrPseudo += 1;
			}
			break;
		case SimpleSelector::Tag:
			{
				specificity.m_tag += 1;
			}
			break;
		default:
			break;
		}
	}
}

LBool CssPropertyValue::compareSpecificity(const PropertySpecificity& specificity1, const PropertySpecificity& specificity2)
{
	KLOG("CssPropertyValue::compareSpecificity");
	if (specificity1.m_important > 0)
		return LTrue;
	else if (specificity2.m_important > 0)
		return LFalse;
	KLOG("CssPropertyValue::compareSpecificity1");
	if (specificity1.m_id > specificity2.m_id)
	{
		KLOG("CssPropertyValue::compareSpecificity");
		return LTrue;
	}
	else if (specificity1.m_id == specificity2.m_id)
	{
		KLOG("CssPropertyValue::compareSpecificity");
		if (specificity1.m_classOrPseudo > specificity2.m_classOrPseudo)
		{
		    return LTrue;
		}
	    else if (specificity1.m_classOrPseudo == specificity2.m_classOrPseudo)
		{
			KLOG("CssPropertyValue::compareSpecificity");
			if (specificity1.m_tag > specificity2.m_tag) 
		        return LTrue;
	        else
		        return LFalse;	
		}
		else
		{
		    return LFalse;
		}
	}
	else
	{
		return LFalse;
	}

}

void CssPropertyValue::setSpecificity(const CssPropertyValue::PropertySpecificity& specificity)
{
	m_specificity.m_id = specificity.m_id;
	m_specificity.m_important = specificity.m_important;
	m_specificity.m_tag = specificity.m_tag;
	m_specificity.m_classOrPseudo = m_specificity.m_classOrPseudo;
}

const CssPropertyValue::PropertySpecificity& CssPropertyValue::getSpecificity() const
{
	return m_specificity;
}

CssRule::CssRule()
    : m_selectorGroup(NULL)
{	
}

CssRule::~CssRule()
{	
	KLOG("CssRule::~CssRule()");
	if (m_selectorGroup)
	{
	    delete m_selectorGroup;
	    m_selectorGroup = NULL;
	}
}

void CssRule::construct()
{
}

CssRule* CssRule::New()
{
	CssRule* rule = new CssRule();
    if (rule)
    {
        rule->construct();
    }
    return rule;
}

CssRule* CssRule::New(CssRule& rule)
{
	CssRule* newRule = new CssRule();
    if (newRule)
    {
        newRule->construct(rule);
    }
    
    return newRule;
}

void CssRule::construct(CssRule& rule)
{
	m_properties = rule.getProperties();
	m_selectorGroup = rule.getSelectorGroup();
}

void CssRule::addProperty(LInt property, LInt value)
{
	CssPropertyValue v;
	v.intVal = value;
	m_properties.put(property, v);
}

void CssRule::addProperty(LInt property, const StringA& value)
{
	CssPropertyValue v;
	v.intVal = 0;
	v.strVal = value;
	m_properties.put(property, v);
}

CssPropertyValue& CssRule::getPropertyValue(LInt property)
{
	return m_properties[property];
}

const AttributeMap& CssRule::getProperties() const
{
    return m_properties;
}

void CssRule::copyPropertiesFrom(const CssRule* rule)
{
	if (NULL != rule)
	{
		AttributeMap::Iterator iter = rule->getProperties().begin();
		AttributeMap::Iterator iterEnd = rule->getProperties().end();
		for (; iter != iterEnd; ++iter)
		{
			KFORMATLOG("CssRule::copyPropertiesFrom key=%d prop size=%d", (*iter)->getKey(), m_properties.size());
			m_properties[(*iter)->getKey()].getSpecificity();
			KLOG("CssRule::copyPropertiesFrom 1");
			(*iter)->getValue().getSpecificity();
			KLOG("CssRule::copyPropertiesFrom 2");
			if (!CssPropertyValue::compareSpecificity(m_properties[(*iter)->getKey()].getSpecificity(), (*iter)->getValue().getSpecificity()))
			{
				KLOG("CssRule::copyPropertiesFrom 3");
				m_properties.put((*iter)->getKey(), (*iter)->getValue());
				KLOG("CssRule::copyPropertiesFrom 4");
			}


			KLOG("CssRule::copyPropertiesFrom end");
		}
	}

}

// last style will be send to htmlitem object
void CssRule::createStyle(Style& style, LFont::FontStyle currentFont)
{
	style.m_transparent = LTrue;
	
	AttributeMap::Iterator iter = m_properties.begin();
	AttributeMap::Iterator iterEnd = m_properties.end();
	for(; iter != iterEnd; ++iter)
	{
	    setStyleProperties(style, (*iter)->getKey(), (*iter)->getValue());
	}
}

SelectorGroup* CssRule::getSelectorGroup() const
{
	return m_selectorGroup;
}

const AttributeMap* CssRule::getPropertiesPtr() const
{
	return &m_properties;
}

void CssRule::setStyleProperties(Style& style, LInt property,
		const CssPropertyValue& value)
{
	switch(property)
	{
	case CssTags::BACKGROUND_COLOR:
		{
		    style.m_bgColor = value.intVal;
		    style.m_transparent = LFalse;
		    KFORMATLOG("style.m_bgColor=%x", value.intVal);
		}
		break;
	case CssTags::BACKGROUND_IMAGE:
		{
		    style.m_bgImageUrl = value.strVal;
		    style.m_transparent = LFalse;
		}
		break;
	case CssTags::COLOR:
		{
		    style.m_color = value.intVal;
		}
		break;
	case CssTags::FONT_STYLE:
		{
		    style.m_font.setFontStyle((LFont::FontStyle)value.intVal);
		}
		break;
	case CssTags::FONT_WEIGHT:
		{
		    style.m_font.setFontStyle((LFont::FontStyle)value.intVal);
		}
		break;
	case CssTags::LEFT:
		{
		    style.m_left = value.intVal;
		}
		break;
	case CssTags::TOP:
		{
		    style.m_top = value.intVal;
		}
		break;
	case CssTags::POSITION:
		{
		    style.m_positionType = value.intVal;
		}
		break;
	case CssTags::FONT_SIZE:
		{
		    style.m_font.setFontSize(value.intVal);
		}
		break;
	case CssTags::BORDER_STYLE:
		{
		    if(value.intVal == LGraphicsContext::SolidPen)
		    {
				style.m_border.m_topWidth = 1;
				style.m_border.m_leftWidth = 1;
				style.m_border.m_bottomWidth = 1;
				style.m_border.m_rightWidth = 1;
		    }
		}
		break;
	case CssTags::TEXT_ALIGN:
		{
		    style.m_textAlignement = value.intVal;
		}
		break;
	case CssTags::MARGIN_LEFT:
		{
		    style.m_leftMargin = value.intVal;
		}
		break;
	case CssTags::MARGIN_TOP:
		{
		    style.m_topMargin = value.intVal;
		}
		break;
	case CssTags::MARGIN_RIGHT:
		{
		    style.m_rightMargin = value.intVal;
		}
		break;
	case CssTags::MARGIB_BOTTOM:
		{
		    style.m_bottomMargin = value.intVal;
		}
		break;
	case CssTags::PADDING_LEFT:
		{
		    style.m_leftPadding = value.intVal;
		}
		break;
	case CssTags::PADDING_TOP:
		{
		    style.m_topPadding = value.intVal;
		}
		break;
	case CssTags::PADDING_RIGHT:
		{
		    style.m_rightPadding = value.intVal;
		}
		break;
	case CssTags::PADDING_BOTTOM:
		{
		    style.m_bottomPadding = value.intVal;
		}
		break;
	case CssTags::BORDER_TOP_STYLE:
		{
		    style.m_border.m_topStyle = value.intVal;
		    if(value.intVal == LGraphicsContext::SolidPen)
		    {
		        style.m_border.m_topWidth = 1;
		    }
		}
		break;
	case CssTags::BORDER_BOTTOM_STYLE:
		{
		    style.m_border.m_bottomStyle = value.intVal;
		    if(value.intVal == LGraphicsContext::SolidPen)
		    {
		        style.m_border.m_bottomWidth = 1;
		    }
		}
		break;
	case CssTags::BORDER_LEFT_STYLE:
		{
		    style.m_border.m_leftStyle = value.intVal;
		    if(value.intVal == LGraphicsContext::SolidPen)
		    {
		        style.m_border.m_leftWidth = 1;
		    }
		}
		break;	
	case CssTags::BORDER_RIGHT_STYLE:
		{
		    style.m_border.m_rightStyle = value.intVal;
		    if(value.intVal == LGraphicsContext::SolidPen)
		    {
		        style.m_border.m_rightWidth = 1;
		    }
		}
		break;	
	case CssTags::BORDER_COLOR:
		{
		    style.m_border.m_leftColor = value.intVal;
		    style.m_border.m_topColor = value.intVal;
		    style.m_border.m_bottomColor = value.intVal;
		    style.m_border.m_rightColor = value.intVal;
		}
		break;
	case CssTags::BORDER_LEFT_COLOR:
		{
		    style.m_border.m_leftColor = value.intVal;
		}
		break;
	case CssTags::BORDER_TOP_COLOR:
		{
		    style.m_border.m_topColor = value.intVal;
		}
		break;	
	case CssTags::BORDER_BOTTOM_COLOR:
		{
		    style.m_border.m_bottomColor = value.intVal;
		}
		break;
	case CssTags::BORDER_RIGHT_COLOR:
		{
		    style.m_border.m_rightColor = value.intVal;
		}
		break;
	case CssTags::DISPLAY:
		{
		    style.m_displayType = value.intVal;
		}
		break;
	case CssTags::FLOAT:
		{
		    style.m_floatType = value.intVal;
		}
		break;
	case CssTags::WIDTH:
		{
		    style.m_width = value.intVal;
		}
		break;
	case CssTags::HEIGHT:
		{
		    style.m_height = value.intVal;
		}
		break;
	default:
		{
		}
		break;
	}
}


LBool CssRule::isPropertyEmpty()
{
    return m_properties.isEmpty();
}

void CssRule::setSelectorGroup(SelectorGroup* group)
{
	m_selectorGroup = group;
}

}
