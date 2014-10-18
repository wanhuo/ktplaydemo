
#include "ZRBMenu.h"


bool ZRBMenu::init( )
{

	if ( !Layer::init( ) )
	{
		return false;
	}

	// Add spriteframecache
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "homeMenu.plist" );
	setBatchNode( SpriteBatchNode::create( "homeMenu.png" ) );
	this->addChild( getBatchNode( ) );
	//  TODO: 模式取消
	// 获取用户选择模式
	//    pModel = UserDate::getInstance()->getDateBool(KEY_CHECK_MODEL);

	// Create button
	pSetbutten = MenuItemImage::create( );
	// Set picture
	pSetbutten->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "setbutten.png" ) );

	pKtplay = MenuItemImage::create( );
	pKtplay->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "regainbuy.png" ) );

	pBegin = MenuItemImage::create( );
	pBegin->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "begin.png" ) );

	pMarket = MenuItemImage::create( );
	pMarket->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "market.png" ) );

	pCharts = MenuItemImage::create( );
	pCharts->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "charts.png" ) );

	pAddGold = MenuItemImage::create( );
	pAddGold->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gold_add.png" ) );
	//  TODO: 模式取消    
	//    pModelEndless = MenuItemImage::create();
	//
	//    pModelTime = MenuItemImage::create();
	//    
	//    if (pModel)
	//    {
	//        pModelEndless->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("model_endless_checked.png"));
	//        pModelTime->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("model_time.png"));
	//
	//    }
	//    else
	//    {
	//        // Change the model button pictrue
	//        pModelEndless->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("model_endless.png"));
	//        
	//        pModelTime->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("model_time_checked.png"));
	//    }
	//

	// Get size of begin button
	size = pBegin->getContentSize( );

	// Set underlying menu anchorpoint (0.5, 0)
	pSetbutten->setAnchorPoint( Point( 0 , 0 ) );
	pKtplay->setAnchorPoint( Point( 0 , 0 ) );
	pBegin->setAnchorPoint( Point( 0 , 0 ) );
	pMarket->setAnchorPoint( Point( 0 , 0 ) );
	pCharts->setAnchorPoint( Point( 0 , 0 ) );
	// Set superincumbent menu anchorpoint (0.5, 1)
	//  TODO: 模式取消
	//    pModelEndless->setAnchorPoint(Point(0.5, 1));
	//    pModelTime->setAnchorPoint(Point(0.5, 1));


	// Set button posintion
	pSetbutten->setPosition( 0 , 0 );
	pKtplay->setPosition( pSetbutten->getContentSize( ).width , 0 );
	pBegin->setPosition( pKtplay->getContentSize( ).width + pKtplay->getPositionX( ) , 0 );
	pMarket->setPosition( pBegin->getContentSize( ).width + pBegin->getPositionX( ) , 0 );
	pCharts->setPosition( pMarket->getContentSize( ).width + pMarket->getPositionX( ) , 0 );
	//  TODO: 模式取消
	//    pModelEndless->setPosition(102, ZRB_VISIBLE_SIZE.height);
	//    pModelTime->setPosition(238.5, ZRB_VISIBLE_SIZE.height);
	pAddGold->setPosition( ZRB_VISIBLE_SIZE.width * 0.92 , ZRB_VISIBLE_SIZE.height * 0.95 );


	// Add sprite do for label background
	auto gold = Sprite::createWithSpriteFrameName( "gold_bg.png" );
	gold->setAnchorPoint( Vec2( 0 , 0 ) );
	gold->setPosition( -190 , 0 );

	// Create label 
	pGold = Label::createWithTTF( String::createWithFormat( "%d" , ZRBUserDate::getInstance( )->getDateInt( KEY_DATA_GOLDNUM ) )->getCString( ) , "customfout.otf" , 30 );
	pGold->setColor( Color3B( 0 , 0 , 0 ) );
	pGold->setPosition( 122 , 24 );

	// Add label to gold
	gold->addChild( pGold );
	// Add gold to  bautton 'pSddGold'
	pAddGold->addChild( gold , -1 );

	// Set menu button callback function
	pSetbutten->setCallback( CC_CALLBACK_0( ZRBMenu::setting , this ) );
	pKtplay->setCallback( CC_CALLBACK_0( ZRBMenu::Ktplay , this ) );
	pBegin->setCallback( CC_CALLBACK_1( ZRBMenu::begainGame , this ) );
	pMarket->setCallback( CC_CALLBACK_0( ZRBMenu::market , this ) );
	pCharts->setCallback( CC_CALLBACK_0( ZRBMenu::charts , this ) );
	//  TODO: 模式取消
	//    pModelEndless->setCallback(CC_CALLBACK_0(ZRBMenu::modelEndless, this));
	//    pModelTime->setCallback(CC_CALLBACK_0(ZRBMenu::modelTime, this));
	pAddGold->setCallback( CC_CALLBACK_0( ZRBMenu::addGold , this ) );


	// pSetbutten pKtplay pBegin pMarket pCharts  add the under menu
	pMenuDown = Menu::create( pSetbutten , pKtplay , pBegin , pMarket , pCharts , nullptr );
	pMenuDown->setPosition( 0 , -200 );
	this->addChild( pMenuDown , 100 );

	// pModelEndless pModelTime pAddGold  add the up menu
	pMenuUp = Menu::create( pAddGold , NULL );
	pMenuUp->setPosition( 0 , 200 );
	this->addChild( pMenuUp , 100 );

	// 注册通知
	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBMenu::setGold ) , "NOTIFICATION_Gold" , NULL );

	return true;
}




/**
*  Set First view button color
*/

void ZRBMenu::setButtonColor0( )
{

	pSetbutten->setColor( Color3B( 230 , 170 , 160 ) );

	pKtplay->setColor( Color3B( 235 , 230 , 190 ) );

	pBegin->setColor( Color3B( 180 , 130 , 150 ) );

	pMarket->setColor( Color3B( 115 , 190 , 205 ) );

	pCharts->setColor( Color3B( 170 , 220 , 190 ) );
	//  TODO: 模式取消
	//    pModelEndless->setColor(Color3B(219, 146, 112));
	//    
	//    pModelTime->setColor(Color3B(98, 141, 164));
}

/**
*  Set Second view button color
*/
void ZRBMenu::setButtonColor1( )
{
	pSetbutten->setColor( Color3B( 178 , 154 , 189 ) );

	pKtplay->setColor( Color3B( 98 , 141 , 164 ) );

	pBegin->setColor( Color3B( 219 , 146 , 112 ) );

	pMarket->setColor( Color3B( 122 , 170 , 154 ) );

	pCharts->setColor( Color3B( 214 , 212 , 122 ) );


	//  TODO: 模式取消
	//    pModelEndless->setColor(Color3B(141, 219, 254));
	//    
	//    pModelTime->setColor(Color3B(214, 141, 254));
}

/**
*  Set Third view button color
*/
void ZRBMenu::setButtonColor2( )
{
	pSetbutten->setColor( Color3B( 250 , 201 , 172 ) );

	pKtplay->setColor( Color3B( 254 , 156 , 153 ) );

	pBegin->setColor( Color3B( 255 , 64 , 94 ) );

	pMarket->setColor( Color3B( 200 , 200 , 168 ) );

	pCharts->setColor( Color3B( 132 , 175 , 155 ) );


	//  TODO: 模式取消
	//    pModelEndless->setColor(Color3B(254, 214, 112));
	//    
	//    pModelTime->setColor(Color3B(254, 141, 214));
}

/**
*  Set menu position ( move down )
*
*  @param p from pageview
*/
void ZRBMenu::SetButtenPointDown( float p )
{
	// Under menu move down
	pMenuDown->setPosition( 0 , size.height * p * 2 / ZRB_VISIBLE_SIZE.width );

	// Up menu move up
	pMenuUp->setPosition( 0 , -size.height * p * 2 / ZRB_VISIBLE_SIZE.width );
}

/**
*  Set menu position ( move up )
*
*  @param p from pageview
*/
void ZRBMenu::SetButtenPointUp( float p )
{
	// Under menu move up
	pMenuDown->setPosition( 0 , -size.height * p * 2 / ZRB_VISIBLE_SIZE.width );

	// Up menu move down
	pMenuUp->setPosition( 0 , size.height * p * 2 / ZRB_VISIBLE_SIZE.width );

}


/**
*  The function callback of menu pBegin
*/
void ZRBMenu::begainGame( Ref * ref )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
	auto move = MoveBy::create( 0.3f , Vec2( 0 , 200 ) );

	pAddGold->runAction( move );
	pBegin->runAction( Speed::create( Sequence::create( DelayTime::create( 0.4 ) , move->reverse( ) , NULL ) , 2 ) );
	pKtplay->runAction( move->reverse( ) );
	pMarket->runAction( move->reverse( ) );
	pSetbutten->runAction( Sequence::create( DelayTime::create( 0.1 ) , move->reverse( ) , NULL ) );
	pCharts->runAction( Sequence::create( DelayTime::create( 0.1 ) , move->reverse( ) , NULL ) );
	pMenuDown->setEnabled( false );
	pMenuUp->setEnabled( false );

	NotificationCenter::getInstance( )->postNotification( "Game" , __Bool::create( true ) );
	//  TODO: 模式取消
	//    if (pModel)
	//    {
	//        ZRBManager::go(ZRBSceneManager::gameScene);
	//    }
	//    else
	//    {
	//        ZRBManager::go(ZRBSceneManager::timeGameScene);
	//    }
}

/**
*  The function callback of pAddGold
*/
void ZRBMenu::addGold( )
{
	auto market = ZRBMenuMarket::create( );
	market->setName( "menu_market" );
	this->addChild( market , 101 );
	market->call_buy( );

}


/**
*  The function callback of pModelEndless
*/
void ZRBMenu::modelEndless( )
{
	//Determine whether endless model
	//  TODO: 模式取消
	//    if (!pModel)
	//    {
	//
	//        // Change the model button pictrue
	//        pModelEndless->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("model_endless_checked.png"));
	//        
	//        pModelTime->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("model_time.png"));
	//        
	//        // Set model is endless
	//        pModel = true;
	//        // 保存游戏模式
	//        UserDate::getInstance()->saveData(KEY_CHECK_MODEL, &pModel);
	//    }
}

/**
*  The function callback of pModelTime
*/
void ZRBMenu::modelTime( )
{

	//  TODO: 模式取消
	//    //Determine whether endless model
	//    if (pModel)
	//    {
	//        
	//        // Change the model button pictrue
	//        pModelEndless->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("model_endless.png"));
	//        
	//        pModelTime->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("model_time_checked.png"));
	//        
	//        // Set model is time
	//        pModel = false;
	//        // 保存游戏模式
	//        UserDate::getInstance()->saveData(KEY_CHECK_MODEL, &pModel);
	//    }
}

/**
*  The function callback of pSetbutten
*/
void ZRBMenu::setting( )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
	auto set = ZRBMenuSet::create( );
	set->setName("menu_set");
	this->addChild( set , 101 );
}


/**
*  The function callback of pKtplay
*/
void ZRBMenu::Ktplay( )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	// Undone : ktplay 社区
	if ( KTPlayC::isEnabled( ) )
	{
		KTPlayC::show( );
	}
	else
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	{
		auto mes = ZRBMessageLayer::create( );
		// UnresolvedMergeConflict 中文显示
		mes->setMessageLabel( "社区不可用" );
		mes->setGlobalZOrder( 200 );
		mes->setName("menu_mes");
		this->addChild( mes );
	}
}

/**
*  The function callback of pMarket
*/
void ZRBMenu::market( )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
	auto market = ZRBMenuMarket::create( );
	market->setName("menu_market");
	this->addChild( market , 101 );
}

/**
*  The function callback of pCharts
*/
void ZRBMenu::charts( )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
   
    IOSRanking::getInstance()->showLeaderboard();

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
 
    auto ranking = ZRBMenuChars::create( );
    ranking->setName("menu_ranking");
    this->addChild( ranking , 101 );
    
#endif

}

/**
*  Set pSsize  Save pageview index
*
*  @param x pagview index from pageview
*/
void ZRBMenu::setSsize( int x )
{
	pSsize = x;
}

/**
*  Set pGold
*
*  @param x Gold number
*/
void ZRBMenu::setGold( Ref * sender )
{
	// 获取数据 显示
	auto x = dynamic_cast<__Integer *>( sender );
	pGold->setString( String::createWithFormat( "%d" , x->getValue( ) )->getCString( ) );
}



ZRBMenu::ZRBMenu( )
{
	pSsize = 0;
	//  TODO: 模式取消
	//    pModel = true;
}

ZRBMenu::~ZRBMenu( )
{
	// 移除通知
	NotificationCenter::getInstance( )->removeAllObservers( this );
}
