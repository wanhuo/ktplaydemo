

#ifndef __ZRBMenuSet_H__
#define __ZRBMenuSet_H__

#include <iostream>
#include "../ZRBMenuBase.h"


class ZRBMenuSet : public ZRBMenuBase
{

private:
	// ���� _backboard ���� menubase�еĵ��ͼ
	CC_SYNTHESIZE_RETAIN( Scale9Sprite * , _backboard , Backboard );

public:

	virtual bool init( );

	// ���ø�����ť��Ӧ�����˵�
	Menu * setSetting( );

	// Setting �ص�����
	void call_music( );
	void call_sound( );
	void call_about( );
	void call_back( );
	void call_clear( );


	CC_SYNTHESIZE( SpriteBatchNode * , pBatchNode , BatchNode );

	CREATE_FUNC( ZRBMenuSet );

};

#endif