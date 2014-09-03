
#include "ZRBHomeLayer.h"

ZRBHomeLayer::ZRBHomeLayer( )
{
}

ZRBHomeLayer::~ZRBHomeLayer( )
{
}


bool ZRBHomeLayer::init( )
{
	if ( !Layer::init() )
	{
		return false;
	}

	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "homeMenu.plist" , "homeMenu.png" );


	this->addChild( ZRBPageView::create( ) );


	auto keyboard = EventListenerKeyboard::create( );
	keyboard->onKeyReleased = [ ] ( EventKeyboard::KeyCode key , Event * )
	{
		if ( EventKeyboard::KeyCode::KEY_ESCAPE == key )
		{
			Director::getInstance( )->end( );
		}
	};
	_eventDispatcher->addEventListenerWithFixedPriority( keyboard , 1 );


	return true;
}