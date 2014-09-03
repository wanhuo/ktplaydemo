
#include "ZRBMenuSet.h"


bool ZRBMenuSet::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}


	// �����������β� ��ӵ��˵��������²㴥��
	auto l = LayerColor::create( Color4B( 170 , 228 , 250 , 80 ) );
	auto mi = MenuItemSprite::create( l , l );
	auto m = Menu::create( mi , NULL );
	this->addChild( m );


	// Add spriteframecache
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "homeMenu.plist" );
	setBatchNode( SpriteBatchNode::create( "homeMenu.png" ) );
	this->addChild( getBatchNode( ) );

	// ��� ZRBMenuBase
	auto layer = ZRBMenuBase::create( );

	// ��� �˵�����
	_backboard = layer->getBackGround( );
	// ���ñ����С
	_backboard->setPreferredSize( ZRB_VISIBLE_SIZE * 0.7 );
	// ���ñ���λ��
	_backboard->setPosition( ZRB_VISIBLE_SIZE.width / 2 , ZRB_VISIBLE_SIZE.height * 3 / 2 );
	// ��ӱ���
	this->addChild( _backboard , 10 );

	// ����������ֵĶ���
	createAtionIn( );
	// ִ�ж���
	_backboard->runAction( getActionOut( ) );

	// �򱳰�����Ӳ˵�
	_backboard->addChild( setSetting( ) );


	return true;
}

/**
*  ���� Setting ��ť�ĵ���
*
*  @return ���� Menu
*/
Menu * ZRBMenuSet::setSetting( )
{

	// ��ȡ����ͼƬ��С
	auto size = _backboard->getContentSize( );

	//������ӷָ���
	for ( int i = 4; i > 1; i-- )
	{
		auto line = Sprite::createWithSpriteFrameName( "line.png" );
		line->setPosition( size.width / 2 , size.height / 5 * i );
		_backboard->addChild( line );
	}

	// ���������������
	auto fontSet = Label::createWithTTF( ZRBLanguage::getValue( "Set_set" ) , "customfout.otf" , 60 );
	fontSet->setColor( Color3B( 69 , 193 , 255 ) );
	fontSet->setPosition( Vec2( size.width / 2 , size.height * 0.9 ) );
	_backboard->addChild( fontSet );


	// ���� about ��ť
	auto about = MenuItemImage::create( );
	about->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "about.png" ) );
	about->setPosition( size.width / 2 , size.height * 0.5 );
	about->setAnchorPoint( Vec2( 0.5 , 0 ) );

	// about ��ť��� "��������" ����
	auto fontAbout = Label::createWithTTF( ZRBLanguage::getValue( "Set_about" ) , "customfout.otf" , 30 );
	fontAbout->setColor( Color3B( 69 , 193 , 255 ) );
	fontAbout->setAnchorPoint( Vec2( 0.5 , 1 ) );
	fontAbout->setPosition( about->getContentSize( ).width / 2 , 0 );
	about->addChild( fontAbout );

	// ���� sound ��ť
	auto sound_on = MenuItemImage::create( );
	sound_on->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "sound.png" ) );

	auto sound_off = MenuItemImage::create( );
	sound_off->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "sound_close.png" ) );

	auto sound = MenuItemToggle::createWithCallback( CC_CALLBACK_0( ZRBMenuSet::call_sound , this ) , sound_on , sound_off , NULL );
	sound->setPosition( size.width * 0.3 , size.height * 0.7 );

	// Todo : sound check
	//if ( !ZRBManager::getEffectMusicState( ) )
	//{
	//	sound->setSelectedIndex( 1 );
	//}
	// sound ��ť ��� "��Ч" ����
	auto fontSound = Label::createWithTTF( ZRBLanguage::getValue( "Set_sound" ) , "customfout.otf" , 25 );
	fontSound->setColor( Color3B( 69 , 193 , 255 ) );
	fontSound->setAnchorPoint( Vec2( 0.5 , 1 ) );
	fontSound->setPosition( sound->getContentSize( ).width / 2 , 0 );
	sound->addChild( fontSound );

	// ���� music  ��ť
	auto music_on = MenuItemImage::create( );
	music_on->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "music.png" ) );
	auto music_off = MenuItemImage::create( );
	music_off->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "music_close.png" ) );

	auto music = MenuItemToggle::createWithCallback( CC_CALLBACK_0( ZRBMenuSet::call_music , this ) , music_on , music_off , nullptr );
	music->setPosition( size.width * 0.7 , size.height * 0.7 );
	
	//TODO : ����״̬
	//if ( !ZRBManager::getBgMusicState( ) )
	//{
	//	music->setSelectedIndex( 1 );
	//}

	// music ��ť��� " ����" ����
	auto fontMusic = Label::createWithTTF( ZRBLanguage::getValue( "Set_music" ) , "customfout.otf" , 25 );
	fontMusic->setColor( Color3B( 69 , 193 , 255 ) );
	fontMusic->setAnchorPoint( Vec2( 0.5 , 1 ) );
	fontMusic->setPosition( music->getContentSize( ).width / 2 , 0 );
	music->addChild( fontMusic );

	// ���� evaluate ��ť�� label
	auto evaluateLable = Label::createWithTTF( ZRBLanguage::getValue( "Set_appreciate" ) , "customfout.otf" , 30 );
	evaluateLable->setAnchorPoint( Vec2( 0.5 , 1 ) );
	evaluateLable->setColor( Color3B( 69 , 193 , 255 ) );

	// ����evaluate ��ť
	auto evaluate = MenuItemImage::create( );
	evaluate->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "star.png" ) );
	evaluate->setPosition( size.width * 0.5 , size.height * 0.35 );
	evaluate->setAnchorPoint( Vec2( 0.5 , 1 ) );
	evaluate->addChild( evaluateLable );

	evaluateLable->setPosition( evaluate->getContentSize( ).width / 2 , 0 );

	// ���� back ��ť
	auto backLabel = Label::createWithTTF( ZRBLanguage::getValue( "Back" ) , "customfout.otf" , 50 );
	backLabel->setColor( Color3B( 69 , 193 , 255 ) );
	auto back = MenuItemLabel::create( backLabel );
	//    auto back = MenuItemImage::create();
	//    back->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back_button_set.png"));
	back->setCallback( CC_CALLBACK_0( ZRBMenuSet::call_back , this ) );
	back->setPosition( size.width / 2 , size.height * 0.1 );

	// ������� menuLayer, back, about, sound, music, evaluate ��ť�Ĳ˵�
	auto menu = Menu::create( back , about , music , sound , evaluate , NULL );
	menu->setPosition( 0 , 0 );

	return menu;

}


/**
*  Setting
*
*  music ��ť�ص�����
*/
void ZRBMenuSet::call_music( )
{
	// todo music callback
	// ��ȡ��ǰ����Ч״̬ ����
	//if ( ZRBManager::getBgMusicState( ) )
	//{
	//	ZRBManager::stopBgMusic( );
	//}
	//else
	//{
	//	ZRBManager::openBgMusic( );
	//}

	//bool _music = ZRBManager::getBgMusicState( );
	//ZRBUserDate::getInstance( )->saveData( KEY_CHECK_MUSIC , &_music );
}

/**
*  Setting
*
*  about ��ť�ص�����
*/
void ZRBMenuSet::call_about( )
{
}

/**
*  Setting
*
*  sound ��ť�ص�����
*/
void ZRBMenuSet::call_sound( )
{

	// Todo:��ȡ��ǰ����Ч״̬ ����
	//if ( ZRBManager::getEffectMusicState( ) )
	//{
	//	ZRBManager::stopEffectMusic( );
	//}
	//else
	//{
	//	ZRBManager::openEffectMusic( );
	//}

	//bool _sound = ZRBManager::getEffectMusicState( );
	//ZRBUserDate::getInstance( )->saveData( KEY_CHECK_SOUND , &_sound );
}


/**
*  back ��ť�ص�����
*/
void ZRBMenuSet::call_back( )
{
	//�����˵��Ƴ��Ķ���
	createAtionOut( );
	//ִ�ж���������������
	_backboard->runAction( Sequence::create( dynamic_cast<FiniteTimeAction *>( getActionIn( ) ) ,
		CallFunc::create( CC_CALLBACK_0( ZRBMenuSet::call_clear , this ) ) , NULL ) );

}

// ���غ�����
void ZRBMenuSet::call_clear( )
{
	// �Ƴ��˵� ����
	this->removeFromParentAndCleanup( true );

}
