
#ifndef __ZRBMenuBase_H__
#define __ZRBMenuBase_H__


#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#include "Utilities/ZRBConfig.h"
#include "Utilities/ZRBUserDate/ZRBUserDate.h"
#include "Utilities/ZRBLanguage/ZRBLanguage.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ZRBMenuBase : public Layer
{
private:

	// �������ı���ͼƬ
	CC_SYNTHESIZE_READONLY( Scale9Sprite * , _backGround , BackGround );

	// ��Ӳ˵�����Ķ���
	CC_SYNTHESIZE_RETAIN( Action * , _actionOut , ActionOut );

	// ��Ӳ˵��˳��Ķ���
	CC_SYNTHESIZE_RETAIN( Action * , _actionIn , ActionIn );

public:

	virtual bool init( );

	// �����˳��Ķ���
	void createAtionOut( );

	// ��������Ķ���
	void createAtionIn( );

	// ��������
	void createBackGroud( );

	CREATE_FUNC( ZRBMenuBase );

};


#endif
