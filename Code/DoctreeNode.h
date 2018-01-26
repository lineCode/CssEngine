/*
 *  DoctreeNode.h
 *
 *  Created on: 2011-6-29
 *      Author: yanbo
 */

#ifndef DoctreeNode_h
#define DoctreeNode_h

#include "UtilString.h"
#include "kvector.h"
namespace util
{

typedef KVector<StringA> ClassArray;
class DoctreeNode
{
public:
	DoctreeNode();
	DoctreeNode(const StringA& tagId, 
			const ClassArray& tagClassArray, const StringA& tagName);
	
	~DoctreeNode();
	
public:
	StringA    m_tagName;     // such as input,html,body
	StringA    m_tagId;       // such as #id
	ClassArray m_classArray;  // such as .class
};

}
#endif /* DOCTREENODE_H_ */
