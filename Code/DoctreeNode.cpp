/*
 * DoctreeNode.cpp
 *
 *  Created on: 2011-6-29
 *      Author: yanbo
 */
#include "DoctreeNode.h"
namespace util
{

DoctreeNode::DoctreeNode()
{	
}

DoctreeNode::DoctreeNode(const StringA& tagId, 
		const ClassArray& tagClassArray, 
		const StringA& tagName)
    : m_tagName(tagName, LFalse)
    , m_tagId(tagId, LFalse)
    , m_classArray(tagClassArray, LFalse)
{
}

DoctreeNode::~DoctreeNode()
{	
}

}
