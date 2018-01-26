/*
 * CssManager.cpp
 *
 *  Created on: 2011-6-29
 *      Author: yanbo
 */

#include "CssManager.h"
#include "CssTags.h"
#include "SalLog.h"

namespace util
{

CssManager::CssManager()
{
}

CssManager::~CssManager()
{
	RuleList::Iterator iter = m_ruleList.begin();
	RuleList::Iterator endIter = m_ruleList.end();
	
	for (; iter != endIter; ++iter)
	{
	    delete *iter;
	}
	
	m_ruleList.clear();
	
	LInt size = m_doctree.size();
	for (LInt i = 0; i < size; i++)
	{
	    DoctreeNode* node = m_doctree.elementAt(i);
	    delete node;
	}
}

void CssManager::addCssRule(CssRule* rule)
{
	m_ruleList.push_back(rule);
}

// get Specified htmitem's cssrule
CssRule* CssManager::getCssRule()
{
	CssRule* cssStyle = CssRule::New();
	
	RuleList::Iterator iter = m_ruleList.begin();
	RuleList::Iterator endIter = m_ruleList.end();
	
	LBool isNull = LTrue;
	KLOG("CssManager::getCssRule1");
	for (; iter != endIter; ++iter)
	{
	    CssRule* rule = *iter;

	    CssRule* newRule = matchRule(rule);
	    if (newRule != NULL)
	    {
	        isNull = LFalse;
	        cssStyle->copyPropertiesFrom(newRule);
	    }
	}

	KLOG("CssManager::getCssRule2");
	if (isNull)
	{
	    delete cssStyle;
	    cssStyle = NULL;
	}
	
	return cssStyle;
}

CssRule* CssManager::matchRule(CssRule* rule)
{
	CssRule* newCssStyle = NULL;
	if (rule != NULL)
	{
	    SelectorGroup* selectorGroup = rule->getSelectorGroup();

		Selector* targetSelector = NULL;
		CssPropertyValue::PropertySpecificity specificity;

		LInt selectorIndex = 0;
		Selector* sel = selectorGroup->elementAt(selectorIndex);
		while (sel)
		{
			LInt simpleSelectorNum = sel->size();
			LInt doctreeNodeNum = m_doctree.size();
	    
			LBool find = LFalse;
			LInt docIndex = doctreeNodeNum-1;
			for (LInt i = simpleSelectorNum-1; i >= 0; i--)
	   		{
				StringA elem = sel->elementAt(i).getSelectorText();
				find = LFalse;	        
        		for (LInt j = docIndex; j >= 0; j--)
				{            		
        			DoctreeNode* docElem = m_doctree.elementAt(j);
        			if ((elem.CompareNoCase(docElem->m_tagId) && !elem.CompareNoCase(_CS("#")))
        					|| elem.CompareNoCase(docElem->m_tagName)
        					|| (docElem->m_classArray.contains(elem) && !elem.CompareNoCase(_CS(".")))
        					)
        			{
        				// find one
        				find = LTrue;
        				docIndex = --j;
        				break;
        			}
        			else 
					{     		    
						continue;
        			}
        		}
        	
        		if (find) 
				{
        			// 如果找到了继续对selector的下一个元素进行查找
        			continue; 
        		}
        		else 
				{
        			// 如果找不到则直接调出循环，find代表查找失败，后续程序根据这个来判断
        			break;    
        		}
			}
	    
			if (!find) 
			{
				++selectorIndex;
				if (selectorIndex >= selectorGroup->size())
				{
					newCssStyle = NULL;
					break;
				}
				else
				{
					sel = selectorGroup->elementAt(selectorIndex);
				}
			}
			else
			{
				// have found!!!
				targetSelector = sel;
				
				CssPropertyValue::PropertySpecificity tmpSpecificity;
				CssPropertyValue::computeSpecificity(sel, tmpSpecificity);
				LBool result = CssPropertyValue::compareSpecificity(specificity, tmpSpecificity);
				if (!result)
				{
					specificity = tmpSpecificity;
				}

				++selectorIndex;
				if (selectorIndex >= selectorGroup->size()) // 查找完毕
				{
					break;
				}
				else
				{
					sel = selectorGroup->elementAt(selectorIndex); // 继续找优先级更高的可以匹配的selector
				}
			}

		}

		KLOG("CssManager::matchRule 1");

		if (specificity.m_id != 0 || specificity.m_tag != 0 || specificity.m_classOrPseudo != 0)
		{
			newCssStyle = rule;

			AttributeMap::Iterator iter = newCssStyle->getProperties().begin();
	        AttributeMap::Iterator iterEnd = newCssStyle->getProperties().end();
	        for (; iter != iterEnd; ++iter)
	        {
				(*iter)->getValue().setSpecificity(specificity);
	        }
		}

		KLOG("CssManager::matchRule 2");
       
	}
	
	return newCssStyle;
}

void CssManager::pushDoctreeNode(DoctreeNode* node)
{
	m_doctree.push(node);
}

void CssManager::pushDoctreeNode(const StringA& tagId, const ClassArray& tagClass, const StringA& tagName)
{
	DoctreeNode* node = new DoctreeNode(tagId, tagClass, tagName);
	m_doctree.push(node);
}

void CssManager::popDoctreeNode()
{
	DoctreeNode* node = m_doctree.pop();
	delete node;
}

// inherited parent style
CssRule* CssManager::createNewCssRule(const CssRule* parentRule, CssRule* childRule)
{
	KLOG("CssManager::createNewCssRule");
	CssRule* newCssRule =  CssRule::New();
    if (NULL != parentRule)
    {    	
		const AttributeMap* properties = parentRule->getPropertiesPtr();
		AttributeMap::Iterator iter = properties->begin();
		AttributeMap::Iterator iterEnd = properties->end();
		for (; iter != iterEnd; ++iter)
		{
			if (((LInt)(*iter)->getKey()) > CssTags::STYLE_NULL) //  iter.getKey() > 0 can be inherited
			{
			    KLOG("inherited1");
			    KDESLOG((LInt)(*iter)->getKey());
				if ((*iter)->getValue().strVal.GetLength() > 0)
				{
				    newCssRule->addProperty((*iter)->getKey(), (*iter)->getValue().strVal);
				}
				else
				{
				    newCssRule->addProperty((*iter)->getKey(), (*iter)->getValue().intVal);
				}
			}
		}
    }
    
    if (NULL != childRule)
    {    	
		const AttributeMap* properties = childRule->getPropertiesPtr();
		AttributeMap::Iterator iter = properties->begin();
		AttributeMap::Iterator iterEnd = properties->end();
		for (; iter != iterEnd; ++iter)
		{
			KLOG("inherited1");
			KDESLOG((LInt)(*iter)->getKey());
		    if ((*iter)->getValue().strVal.GetLength() > 0)
			{
				newCssRule->addProperty((*iter)->getKey(), (*iter)->getValue().strVal);
			}
			else
			{
				newCssRule->addProperty((*iter)->getKey(), (*iter)->getValue().intVal);
			}
		}

		delete childRule;
		childRule = NULL;
    }

	return newCssRule;
}

}
