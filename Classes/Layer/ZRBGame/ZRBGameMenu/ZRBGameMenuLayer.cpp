
#include "ZRBGameMenuLayer.h"

bool ZRBGameMenuLayer::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}
	times = 3;
	initObject( );
	return true;
}

void ZRBGameMenuLayer::initObject( )
{
	// ����ͼƬ
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "game_menuItem.plist" );
	pMenu = Menu::create( );

	//bg ��ֹ�²㴥����Ӧ
	LayerColor *bg1Layer = LayerColor::create( Color4B( 155 , 177 , 188 , 178 ) , ZRB_SCREEN_SIZE.width , ZRB_SCREEN_SIZE.height );
	LayerColor *bg2Layer = LayerColor::create( Color4B( 155 , 177 , 188 , 178 ) , ZRB_SCREEN_SIZE.width , ZRB_SCREEN_SIZE.height );
	MenuItemSprite *bgItem = MenuItemSprite::create( bg1Layer , bg2Layer );
	bgItem->setAnchorPoint( Vec2( 0 , 0 ) );
	bgItem->setPosition( Vec2( 0 , 0 ) );

	//logo
	Sprite *logo1Sp = Sprite::createWithSpriteFrameName( "logo_GameMenuItem.png" );
	Sprite *logo2Sp = Sprite::createWithSpriteFrameName( "logo_GameMenuItem.png" );
	MenuItemSprite *logoItem = MenuItemSprite::create( logo1Sp , logo2Sp );
	logoItem->setPosition( Point( ZRB_SCREEN_SIZE.width*0.42 , ZRB_SCREEN_SIZE.height*0.7 ) );

	//������Ϸ
	Sprite *backGame1Sp = Sprite::createWithSpriteFrameName( ZRBLanguage::getValue( "Pic_pause_backgame" ) );
	Sprite *backGame2Sp = Sprite::createWithSpriteFrameName( ZRBLanguage::getValue( "Pic_pause_backgame" ) );
	backGame2Sp->setOpacity( 150 );
	MenuItemSprite *backGameItem = MenuItemSprite::create( backGame1Sp , backGame2Sp , CC_CALLBACK_1( ZRBGameMenuLayer::backGameItemClick , this ) );
	backGameItem->setAnchorPoint( Point( 0.5 , 1 ) );
	backGameItem->setPosition( Point( ZRB_SCREEN_SIZE.width*0.5 , logoItem->getBoundingBox( ).getMinY( ) - 20 ) );

	//������Ϸ
	Sprite *restartGame1Sp = Sprite::createWithSpriteFrameName( ZRBLanguage::getValue( "Pic_pause_resume" ) );
	Sprite *restartGame2Sp = Sprite::createWithSpriteFrameName( ZRBLanguage::getValue( "Pic_pause_resume" ) );
	restartGame2Sp->setOpacity( 150 );
	MenuItemSprite *restartGameItem = MenuItemSprite::create( restartGame1Sp , restartGame2Sp , CC_CALLBACK_1( ZRBGameMenuLayer::restartGameItemClick , this ) );
	restartGameItem->setAnchorPoint( Point( 0.5 , 1 ) );
	restartGameItem->setPosition( Point( ZRB_SCREEN_SIZE.width*0.5 , backGameItem->getBoundingBox( ).getMinY( ) - 20 ) );

	//����������
	Sprite *backHome1Sp = Sprite::createWithSpriteFrameName( ZRBLanguage::getValue( "Pic_pause_backhome" ) );
	Sprite *backHome2Sp = Sprite::createWithSpriteFrameName( ZRBLanguage::getValue( "Pic_pause_backhome" ) );
	backHome2Sp->setOpacity( 150 );
	MenuItemSprite *backHomeItem = MenuItemSprite::create( backHome1Sp , backHome2Sp , CC_CALLBACK_1( ZRBGameMenuLayer::backHomeItemClick , this ) );
	backHomeItem->setAnchorPoint( Point( 0.5 , 1 ) );
	backHomeItem->setPosition( Point( ZRB_SCREEN_SIZE.width*0.5 , restartGameItem->getBoundingBox( ).getMinY( ) - 20 ) );

	//��������
	Sprite *musicOpen1Sp = Sprite::createWithSpriteFrameName( "music_GameMenuItem.png" );
	Sprite *musicOpen2Sp = Sprite::createWithSpriteFrameName( "music_GameMenuItem.png" );
	musicOpen2Sp->setOpacity( 150 );
	MenuItemSprite *musicOpenItem = MenuItemSprite::create( musicOpen1Sp , musicOpen2Sp );
	Sprite *musicClose1Sp = Sprite::createWithSpriteFrameName( "music_close_GameMenuItem.png" );
	Sprite *musicClose2Sp = Sprite::createWithSpriteFrameName( "music_close_GameMenuItem.png" );
	musicClose2Sp->setOpacity( 150 );
	MenuItemSprite *musicCloseItem = MenuItemSprite::create( musicClose1Sp , musicClose2Sp );
	MenuItemToggle *musicItem = MenuItemToggle::createWithCallback( CC_CALLBACK_1( ZRBGameMenuLayer::musicItemClick , this ) , musicOpenItem , musicCloseItem , NULL );
	musicItem->setAnchorPoint( Point( 0 , 1 ) );
	musicItem->setPosition( Point( backHomeItem->getBoundingBox( ).getMinX( ) , backHomeItem->getBoundingBox( ).getMinY( ) - 20 ) );

	// Todo :������ʾͼƬ
	//if ( !ZRBManager::getBgMusicState( ) )
	//{
	//	musicItem->setSelectedIndex( 1 );
	//}

	//��Ч
	Sprite *soundEffectOpen1Sp = Sprite::createWithSpriteFrameName( "soundEffect_GameMenuItem.png" );
	Sprite *soundEffectOpen2Sp = Sprite::createWithSpriteFrameName( "soundEffect_GameMenuItem.png" );
	soundEffectOpen2Sp->setOpacity( 150 );
	MenuItemSprite *soundEffectOpenItem = MenuItemSprite::create( soundEffectOpen1Sp , soundEffectOpen2Sp );
	Sprite *soundEffectClose1Sp = Sprite::createWithSpriteFrameName( "soundEffect_close_GameMenuItem.png" );
	Sprite *soundEffectClose2Sp = Sprite::createWithSpriteFrameName( "soundEffect_close_GameMenuItem.png" );
	soundEffectClose2Sp->setOpacity( 150 );
	MenuItemSprite *soundEffectCloseItem = MenuItemSprite::create( soundEffectClose1Sp , soundEffectClose2Sp );
	MenuItemToggle *soundEffectItem = MenuItemToggle::createWithCallback( CC_CALLBACK_1( ZRBGameMenuLayer::soundEffectItemClick , this ) , soundEffectOpenItem , soundEffectCloseItem , NULL );
	soundEffectItem->setAnchorPoint( Point( 1 , 1 ) );
	soundEffectItem->setPosition( Point( backHomeItem->getBoundingBox( ).getMaxX( ) , backHomeItem->getBoundingBox( ).getMinY( ) - 20 ) );
	/* Todo : music pic
	if ( !ZRBManager::getEffectMusicState( ) )
	{
		soundEffectItem->setSelectedIndex( 1 );
	}*/

	// ��Ӳ˵�
	pMenu->addChild( bgItem );
	pMenu->addChild( logoItem );
	pMenu->addChild( backGameItem );
	pMenu->addChild( backHomeItem );
	pMenu->addChild( restartGameItem );
	pMenu->addChild( musicItem );
	pMenu->addChild( soundEffectItem );

	this->addChild( pMenu );

}

void ZRBGameMenuLayer::setScene( ZRBSceneManager _manager )
{
	pSceneManager = _manager;
}

// ������Ϸ
void ZRBGameMenuLayer::backGameItemClick( Ref *ref )
{
	Director::getInstance( )->resume( );
	this->getParent( )->pause( );
	countdown = Label::createWithTTF( "3" , "customfout.otf" , 60 );
	countdown->setColor( Color3B( 255 , 0 , 255 ) );
	countdown->setPosition( ZRB_VISIBLE_SIZE );
	this->addChild( countdown );
	pMenu->setVisible( false );
	auto loading = ZRBLoadingLayer::create( );
	loading->setPosition( ZRB_VISIBLE_SIZE / 2 );
	loading->setLoading( 50 , 1 , 0.75 );
	this->addChild( loading );

	schedule( schedule_selector( ZRBGameMenuLayer::scheduleCall ) , 1 , 2 , 0 );
	// �Ƴ�
	//    this->removeFromParentAndCleanup(true);
}

// ������ҳ
void ZRBGameMenuLayer::backHomeItemClick( Ref *ref )
{
	// ����
	Director::getInstance( )->resume( );
	// Todo: ��ת����ҳ
	//ZRBManager::go( ZRBSceneManager::homeScene );
}

// ���¿�ʼ��Ϸ
void ZRBGameMenuLayer::restartGameItemClick( Ref *ref )
{
	//����
	//    Director::getInstance()->resume();
	// ���¿�ʼ
	//    ZRBManager::go(pSceneManager);
	NotificationCenter::getInstance( )->postNotification( "NOTIFICATION_Resume" , __Bool::create( true ) );
}

//�л�����״̬
void ZRBGameMenuLayer::musicItemClick( Ref *ref )
{
	// Todo: ��ȡ��ǰ����Ч״̬ ����
	/*if ( ZRBManager::getBgMusicState( ) )
	{
		ZRBManager::stopBgMusic( );
	}
	else
	{
		ZRBManager::openBgMusic( );
	}

	bool _music = ZRBManager::getBgMusicState( );
	ZRBUserDate::getInstance( )->saveData( KEY_CHECK_MUSIC , &_music );*/
}

// �л���Ч״̬
void ZRBGameMenuLayer::soundEffectItemClick( Ref *ref )
{
	// Todo : ��ȡ��ǰ����Ч״̬ ����
	/*if ( ZRBManager::getEffectMusicState( ) )
	{
		ZRBManager::stopEffectMusic( );
	}
	else
	{
		ZRBManager::openEffectMusic( );
	}

	bool _sound = ZRBManager::getEffectMusicState( );
	ZRBUserDate::getInstance( )->saveData( KEY_CHECK_SOUND , &_sound );*/
}


void ZRBGameMenuLayer::scheduleCall( float dt )
{
	countdown->setString( String::createWithFormat( "%d" , --times )->getCString( ) );
	if ( !times )
	{
		this->getParent( )->resume( );
		this->removeFromParentAndCleanup( true );
	}
}
