

#include "ZRBMessageLayer.h"


bool ZRBMessageLayer::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}

	auto layer = LayerColor::create( Color4B( 255 , 255 , 255 , 120 ) );

	width = ZRB_VISIBLE_SIZE.width * 2 / 3;
	auto parent = ZRBMenuBase::create( );
	parent->createAtionIn( );
	parent->createAtionOut( );
	this->setActionIn( parent->getActionOut( ) );
	this->setActionOut( parent->getActionIn( ) );

	_backGround = parent->getBackGround( );
	_backGround->setContentSize( Size( width , width * 0.618 ) );
	_backGround->setPosition( ZRB_VISIBLE_SIZE.width / 2 , ZRB_VISIBLE_SIZE.height * 3 / 2 );


	menu = Menu::create( );
	menu->setPosition( Vec2::ZERO );
	menu->setGlobalZOrder( 300 );
	menu->setLocalZOrder( 10 );
	_backGround->addChild( menu );

	auto listener = EventListenerTouchOneByOne::create( );
	listener->setSwallowTouches( true );
	listener->onTouchBegan = [ ] ( Touch* , Event* ) { return true; };
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listener , this );

	this->addChild( layer );
	this->addChild( _backGround );

	_backGround->runAction( this->getActionIn( ) );
	return true;
}

void ZRBMessageLayer::setMessageLabel( std::string mes )
{
	auto label = Label::createWithTTF( ZRBLanguage::getValue( "Back" ) , "customfout.otf" , 50 );
	label->setColor( Color3B( 69 , 193 , 255 ) );
	auto callBack = MenuItemLabel::create( label , CC_CALLBACK_0( ZRBMessageLayer::callback , this ) );
	callBack->setPosition( width / 2 , label->getContentSize( ).height * 4 / 7 );
	menu->addChild( callBack );

	messageLabel = Label::createWithTTF( mes , "customfout.otf" , 40 );
	messageLabel->setColor( Color3B( 69 , 193 , 255 ) );
	messageLabel->setAnchorPoint( Vec2( 0.5 , 0.2 ) );
	messageLabel->setAlignment( TextHAlignment::CENTER );
	messageLabel->setPosition( _backGround->getContentSize( ) / 2 );
	_backGround->addChild( messageLabel );
}


void ZRBMessageLayer::setMessageLabel( std::string mes , std::string item , const std::function<void( )> &func )
{
	auto label = Label::createWithTTF( ZRBLanguage::getValue( "Back" ) , "customfout.otf" , 50 );
	label->setColor( Color3B( 69 , 193 , 255 ) );
	auto callBack = MenuItemLabel::create( label , CC_CALLBACK_0( ZRBMessageLayer::callback , this ) );
	callBack->setPosition( width * 3 / 4 , label->getContentSize( ).height * 4 / 7 );
	menu->addChild( callBack );

	auto itemlabel = Label::createWithTTF( item , "customfout.otf" , 50 );
	itemlabel->setColor( Color3B( 69 , 193 , 255 ) );
	auto custom = MenuItemLabel::create( itemlabel , [ = ] ( Ref* )
	{
		label->runAction( CallFunc::create( CC_CALLBACK_0( ZRBMessageLayer::callback , this ) ) );
		func( );

	} );
	custom->setPosition( width / 4 , label->getContentSize( ).height * 4 / 7 );
	menu->addChild( custom );

	messageLabel = Label::createWithTTF( mes , "customfout.otf" , 40 );
	messageLabel->setColor( Color3B( 69 , 193 , 255 ) );
	messageLabel->setAnchorPoint( Vec2( 0.5 , 0.2 ) );
	messageLabel->setAlignment( TextHAlignment::CENTER );
	messageLabel->setPosition( _backGround->getContentSize( ) / 2 );
	_backGround->addChild( messageLabel );
}

void ZRBMessageLayer::callback( )
{
	_backGround->runAction( Sequence::create( dynamic_cast<FiniteTimeAction *>( this->getActionOut( ) ) ,
		CallFunc::create( [ &] ( )
	{
		_eventDispatcher->removeEventListenersForTarget( this );
		this->removeFromParentAndCleanup( true );
	} ) ,
		NULL ) );

}