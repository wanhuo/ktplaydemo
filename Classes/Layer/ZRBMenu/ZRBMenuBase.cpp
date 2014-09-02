
#include "ZRBMenuBase.h"


bool ZRBMenuBase::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}
	// ͼƬ���ص��ڴ�
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "homeMenu.plist" , "homeMenu.png" );
	// ��ӱ���ͼƬ
	_backGround = Scale9Sprite::createWithSpriteFrameName( "flow_bg.png" , Rect( 26 , 26 , 58 , 12 ) );

	return true;
}


/**
*  ��������Ķ���
*/
void ZRBMenuBase::createAtionIn( )
{

	//  ��0.25�������ƶ�һ����Ļ�ĸ߶�
	auto moveDown = MoveBy::create( 0.15f , Vec2( 0 , -ZRB_VISIBLE_SIZE.height ) );

	// ���ö���
	setActionOut( moveDown );

}


void ZRBMenuBase::createAtionOut( )
{
	// ��ת15�� ʱ��0.15��
	auto rotate = RotateBy::create( 0.1f , 5 );

	// ��0.5�����½�һ����Ļ�ĸ߶�
	auto moveDown = MoveBy::create( 0.2f , Vec2( 0 , -ZRB_VISIBLE_SIZE.height ) );

	// ͬʱ�����ƶ�����ת
	auto moveRotate = Spawn::create( rotate , moveDown , NULL );
	// ���ö���
	setActionIn( moveRotate );
}

