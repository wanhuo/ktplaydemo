
#include "ZRBPageView.h"

ZRBPageView::ZRBPageView( ) : PagePrice({ 0 , 4000 , 4000 , 4000 , 16000 })
{

}


ZRBPageView::~ZRBPageView( )
{
	NotificationCenter::getInstance( )->removeAllObservers( this );
}

/**
*  Initialize
*
*  @return Pageview layer
*/
bool ZRBPageView::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}

	ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialBlueSky( ) );

	// 获取场景解锁状态
	page1 = ZRBUserDate::getInstance( )->getDateBool( KEY_MATERIAL_SWEET );
	page2 = ZRBUserDate::getInstance( )->getDateBool( KEY_MATERIAL_BLUESKY );

	// 初始化为未解锁
	//    page1 = false;
	//    page2 = false;
	//    page3 = false;
	//    page4 = false;

	// 设置弹窗大小
	size = Size( 400 , 300 );

	// 添加菜单
	pMenu = ZRBMenu::create( );
	pMenu->setButtonColor0( );
	this->addChild( pMenu , 10 );
	// 添加游戏层
	gameLayer = ZRBGameLayer::create( );
	this->addChild( gameLayer , 3 );
	// 添加透明遮挡层
	opacityLayer = LayerColor::create( Color4B( 0 , 0 , 0 , 0 ) , ZRB_VISIBLE_SIZE.width , ZRB_VISIBLE_SIZE.height );
	this->addChild( opacityLayer , 4 );
	// Set pageview
	ZRBPageView::setPageView( );

	// Add pageview
	// TODO: 层级 背景
	addChild( pageView , 5 );
	// Add schedule
	schedule( schedule_selector( ZRBPageView::schedulecallback ) );
	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBPageView::gameBegain ) , "Game" , nullptr );
	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBPageView::updataGold ) , "NOTIFICATION_Gold" , nullptr );

	return true;
}

/**
*  Set pageview
*/
void ZRBPageView::setPageView( )
{

	/**
	*   Create pageview
	*   Set touch enable
	*   Set  size pageview
	*   Set position
	*/
	pageView = ZRB_PageView::create( );
	pageView->setTouchEnabled( true );
	pageView->setSize( ZRB_VISIBLE_SIZE );
	pageView->setPosition( Point::ZERO );
	pageView->addEventListener( CC_CALLBACK_2( ZRBPageView::pageEventListener , this ) );

	// 创建分页 1
	auto gBG0 = Layer::create( );
	// 获取背景信息
	auto pMaterial0 = ZRBTheme::getMaterialBlueSky( );
	// 添加到内存池
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( pMaterial0->plist , pMaterial0->png );
	// 创建背景


	// 创建分页二
	auto gBG1 = Layer::create( );
	auto pMaterial1 = ZRBTheme::getMaterialSummer( );
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( pMaterial1->plist , pMaterial1->png );

	// 创建分页三
	auto gBG2 = Layer::create( );
	auto pMaterial2 = ZRBTheme::getMaterialSweet( );
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( pMaterial2->plist , pMaterial2->png );


	// Set view with meun background
	auto layout0 = ui::Layout::create( );
	layout0->addChild( gBG0 );

	auto layout1 = ui::Layout::create( );
	layout1->addChild( gBG1 );

	auto layout2 = ui::Layout::create( );
	layout2->addChild( gBG2 );


	if ( !page1 )
	{
		// 创建弹窗层
		auto layer = LayerColor::create( Color4B( 0 , 0 , 0 , 120 ) );
		popup( layer , 1 );
		layer->setTag( 11 );
		layout1->addChild( layer );
	}

	if ( !page2 )
	{
		// 创建弹窗层
		auto layer = LayerColor::create( Color4B( 255 , 255 , 255 , 120 ) );
		popup( layer , 2 );
		layer->setTag( 11 );
		layout2->addChild( layer );
	}


	//  Add body view in pageview
	pageView->addPage( layout0 );
	pageView->addPage( layout1 );
	pageView->addPage( layout2 );

}


/**
*  Get pageview position Set menu position
*
*  @param dt useless
*/
void ZRBPageView::schedulecallback( float dt )
{
	// Get pageview index(number)
	ssize = pageView->getCurPageIndex( );
	// Get body view
	auto layout = pageView->getPage( ssize );
	// Get view position
	auto point = layout->getPositionX( );

	/**
	*   NOTICE:
	*   on touch the view index is at present view
	*   touch exit the view index is will be presented
	*   the point could change the sign
	*/

	if ( ssize == 0 )
	{
		/**
		*    First view
		*/

		//  Passing first view index to the menu
		pMenu->setSsize( ssize );

		/**
		*  If view position less than half the scene width of
		*  present menu move down
		*  If view position more than half the scene width of
		*  next menu move up
		*/
		if ( point > -ZRB_VISIBLE_SIZE.width / 2 )
		{
			pMenu->setButtonColor0( );
			pMenu->SetButtenPointDown( point );
			setOpacityLayer( point );
		}
		else if ( point < -ZRB_VISIBLE_SIZE.width / 2 )
		{
			pMenu->setButtonColor1( );
			pMenu->SetButtenPointUp( ZRB_VISIBLE_SIZE.width + point );
			setOpacityLayer( ZRB_VISIBLE_SIZE.width + point );
			ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSummer( ) );
			gameLayer->changePic( 0 );
		}
		else
		{
			ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialBlueSky( ) );
			gameLayer->changePic( 0 );
		}
	}
	else if ( ssize == 1 )
	{
		/**
		*  Second
		*/

		//  Passing first view index to the menu
		pMenu->setSsize( ssize );

		//  When point change sign, Init menu point
		if ( point == 0 )
		{
			pMenu->setButtonColor1( );
			pMenu->SetButtenPointDown( 0 );
			ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSummer( ) );
			gameLayer->changePic( 1 );
		}
		else if ( point > 0 )
		{
			/**
			*   Move to left
			*/

			/**
			*  If view position more than half the scene width of
			*  last menu move up
			*  If view position less than half the scene width of
			*  present menu move down
			*/
			if ( point > ZRB_VISIBLE_SIZE.width / 2 )
			{
				pMenu->setButtonColor0( );
				pMenu->SetButtenPointUp( ZRB_VISIBLE_SIZE.width - point );
				setOpacityLayer( ZRB_VISIBLE_SIZE.width - point );
				ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialBlueSky( ) );
				gameLayer->changePic( 0 );
			}
			else
			{
				pMenu->setButtonColor1( );
				pMenu->SetButtenPointUp( point );
				setOpacityLayer( point );
				ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSummer( ) );
				gameLayer->changePic( 1 );
			}
		}
		else
		{
			/**
			*   Move to right
			*/

			/**
			*  If view position less than half the scene width of
			*  present menu move down
			*  If view position more than half the scene width of
			*  next menu move up
			*/
			if ( -point < ZRB_VISIBLE_SIZE.width / 2 )
			{
				pMenu->setButtonColor1( );
				pMenu->SetButtenPointDown( point );
				setOpacityLayer( point );
				ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSummer( ) );
				gameLayer->changePic( 1 );
			}
			else
			{
				pMenu->setButtonColor2( );
				pMenu->SetButtenPointUp( ZRB_VISIBLE_SIZE.width + point );
				setOpacityLayer( ZRB_VISIBLE_SIZE.width + point );
				ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSweet( ) );
				gameLayer->changePic( 2 );
			}
		}
	}
	else if ( ssize == 2 )
	{
		/**
		*  Third (the last)
		*/

		//  Passing first view index to the menu
		pMenu->setSsize( ssize );

		//  When point change sign, Init menu point
		if ( point == 0 )
		{
			pMenu->setButtonColor2( );
			pMenu->SetButtenPointDown( 0 );
			ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSweet( ) );
			gameLayer->changePic( 2 );
		}
		else if ( point < ZRB_VISIBLE_SIZE.width / 2 )
		{
			// Leave last view
			// Present menu move douw
			pMenu->setButtonColor2( );
			pMenu->SetButtenPointDown( -point );
			setOpacityLayer( -point );
			ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSweet( ) );
			gameLayer->changePic( 2 );
		}
		else if ( point > ZRB_VISIBLE_SIZE.width / 2 )
		{
			// Pass into last view
			// last menu move up
			pMenu->setButtonColor1( );
			pMenu->SetButtenPointUp( ZRB_VISIBLE_SIZE.width - point );
			setOpacityLayer( ZRB_VISIBLE_SIZE.width - point );
			ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSummer( ) );
			gameLayer->changePic( 1 );
		}
	}
}


void ZRBPageView::pageEventListener( Ref* ref , ui::PageView::EventType type )
{
	auto idx = pageView->getCurPageIndex( );
	ZRBUserDate::getInstance( )->saveData( KEY_CHECK_MATERIAL , &idx );

	switch ( type )
	{
		case ui::PageView::EventType::TURNING:

			switch ( idx )
			{
				case 0:
				{
					// 设置主题
					ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialBlueSky( ) );

					pMenu->pMenuDown->setEnabled( true );
					pMenu->pMenuUp->setEnabled( true );
					pMenu->pMenuDown->setOpacity( 255 );
					pMenu->pMenuUp->setOpacity( 255 );

					break;
				}
				case 1:
				{
					ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSummer( ) );

					// 是否解锁
					if ( page1 )
					{
						pMenu->pMenuDown->setEnabled( true );
						pMenu->pMenuUp->setEnabled( true );
						pMenu->pMenuDown->setOpacity( 255 );
						pMenu->pMenuUp->setOpacity( 255 );
					}
					else
					{
						pMenu->pMenuDown->setEnabled( false );
						pMenu->pMenuUp->setEnabled( false );
						pMenu->pMenuDown->setOpacity( 100 );
						pMenu->pMenuUp->setOpacity( 100 );
					}

					break;
				}
				case 2:
				{
					ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSweet( ) );

					if ( page2 )
					{
						pMenu->pMenuDown->setEnabled( true );
						pMenu->pMenuUp->setEnabled( true );
						pMenu->pMenuDown->setOpacity( 255 );
						pMenu->pMenuUp->setOpacity( 255 );
					}
					else
					{
						pMenu->pMenuDown->setEnabled( false );
						pMenu->pMenuUp->setEnabled( false );
						pMenu->pMenuDown->setOpacity( 100 );
						pMenu->pMenuUp->setOpacity( 100 );
					}

					break;
				}
				case 3:
				{
					ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSweet( ) );

					if ( page3 )
					{
						pMenu->pMenuDown->setEnabled( true );
						pMenu->pMenuUp->setEnabled( true );
						pMenu->pMenuDown->setOpacity( 255 );
						pMenu->pMenuUp->setOpacity( 255 );
					}
					else
					{
						pMenu->pMenuDown->setEnabled( false );
						pMenu->pMenuUp->setEnabled( false );
						pMenu->pMenuDown->setOpacity( 100 );
						pMenu->pMenuUp->setOpacity( 100 );
					}

					break;
				}
				case 4:
				{
					ZRBTheme::setCurrentMaterial( ZRBTheme::getMaterialSummer( ) );

					if ( page4 )
					{
						pMenu->pMenuDown->setEnabled( true );
						pMenu->pMenuUp->setEnabled( true );
						pMenu->pMenuDown->setOpacity( 255 );
						pMenu->pMenuUp->setOpacity( 255 );
					}
					else
					{
						pMenu->pMenuDown->setEnabled( false );
						pMenu->pMenuUp->setEnabled( false );
						pMenu->pMenuDown->setOpacity( 100 );
						pMenu->pMenuUp->setOpacity( 100 );
					}

					break;
				}

				default:
					break;
			}
			break;

		default:
			break;
	}
}

/**
*  未解锁弹窗
*
*  @param idx 当前页
*/
void ZRBPageView::popup( LayerColor * layer , int idx )
{

	layer->setOpacity( 100 );

	// 获得背景图层 设置大小 位置
	backGrond = ZRBMenuBase::create( )->getBackGround( );
	backGrond->setPreferredSize( size );
	backGrond->setPosition( ZRB_VISIBLE_SIZE.width / 2 , ZRB_VISIBLE_SIZE.height / 2 );

	// 添加弹窗提示信息
	auto massage = Label::createWithTTF( String::createWithFormat( "%s\n%d" , ZRBLanguage::getValue( "Lock_true" ) , PagePrice [ idx ] )->getCString( ) , "customfout.otf" , 30 );
	massage->setPosition( size.width / 2 , size.height / 2 );
	massage->setColor( Color3B( 69 , 193 , 255 ) );
	// 文本对齐方式
	massage->setAlignment( TextHAlignment::CENTER );
	backGrond->addChild( massage );

	auto btBuy = MenuItemImage::create( );
	btBuy->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gold_bg.png" ) );
	btBuy->setPosition( size.width / 2 , size.height - btBuy->getContentSize( ).height );
	btBuy->setCallback( CC_CALLBACK_0( ZRBPageView::callBuyGold , this ) );
	btBuy->setTag( 14 );
	// 按钮添加金币
	auto price = Label::createWithTTF( String::createWithFormat( "%d" , ZRBUserDate::getInstance( )->getDateInt( KEY_DATA_GOLDNUM ) )->getCString( ) , "customfout.otf" , 25 );
	price->setPosition( btBuy->getContentSize( ).width / 2 , btBuy->getContentSize( ).height / 2 );
	price->setColor( Color3B( 0 , 0 , 0 ) );
	price->setTag( 15 );
	btBuy->addChild( price );
	// 添加金币背景
	auto addPic = Sprite::createWithSpriteFrameName( "gold_add.png" );
	addPic->setPosition( btBuy->getContentSize( ).width - 20 , btBuy->getContentSize( ).height / 2 );
	btBuy->addChild( addPic );

	// 添加购买按钮
	auto buy = MenuItemImage::create( );
	buy->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "flow_bg.png" ) );
	buy->setCallback( CC_CALLBACK_0( ZRBPageView::callBuy , this , layer , idx ) );
	buy->setPosition( size.width / 2 , buy->getContentSize( ).height );

	auto buyLabel = Label::createWithTTF( ZRBLanguage::getValue( "Buy" ) , "customfout.otf" , 37 );
	buyLabel->setPosition( buy->getContentSize( ).width / 2 , buy->getContentSize( ).height / 2 );
	buyLabel->setColor( Color3B( 69 , 193 , 255 ) );
	buy->addChild( buyLabel );

	// 添加菜单
	auto menu = Menu::create( buy , btBuy , NULL );
	menu->setPosition( 0 , 0 );
	menu->setTag( 13 );
	backGrond->addChild( menu );

	// 添加弹窗到背景层
	layer->addChild( backGrond , 10 , 12 );
}

/**
*  购买回调
*
*  @param idx 购买那个主题
*/
void ZRBPageView::callBuy( LayerColor * layer , int idx )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
	// 购买 主题
	auto gold = ZRBUserDate::getInstance( )->getDateInt( KEY_DATA_GOLDNUM );
	if ( gold < PagePrice [ idx ] )
	{
		auto mes = ZRBMessageLayer::create( );
		mes->setMessageLabel( ZRBLanguage::getString( "Message_market_fail_1" ) + "\n" + ZRBLanguage::getString( "Message_market_fail_2" ) ,
							  ZRBLanguage::getValue( "BuyGold" ) , [ &] ( )
		{
			auto market = ZRBMenuMarket::create( );
			this->addChild( market , 10 );
			market->call_buy( );
		} );
		mes->setGlobalZOrder( 200 );
		pageView->addChild( mes );

		return;
	}
	gold -= PagePrice [ idx ];
	ZRBUserDate::getInstance( )->saveData( KEY_DATA_GOLDNUM , &gold );
	// 发送通知
	NotificationCenter::getInstance( )->postNotification( "NOTIFICATION_Gold" , Integer::create( gold ) );
	// 解锁购买的主题
	switch ( idx )
	{
		case 0:
			break;

		case 1:
			//  保存
			page1 = true;
			ZRBUserDate::getInstance( )->saveData( KEY_MATERIAL_SWEET , &page1 );
			break;

		case 2:

			page2 = true;
			ZRBUserDate::getInstance( )->saveData( KEY_MATERIAL_BLUESKY , &page2 );
			break;

		case 3:

			page3 = true;
			break;

		default:

			break;
	}

	auto mes = ZRBMessageLayer::create( );
	mes->setMessageLabel( ZRBLanguage::getValue( "Unlock_success" ) );
	mes->setGlobalZOrder( 200 );
	pageView->addChild( mes );

	// 解锁后可以游戏
	pMenu->pMenuDown->setEnabled( true );
	pMenu->pMenuUp->setEnabled( true );
	pMenu->pMenuDown->setOpacity( 255 );
	pMenu->pMenuUp->setOpacity( 255 );
	// 清理
	layer->removeAllChildren( );
	layer->setOpacity( 0 );

}

// 添加金币
void ZRBPageView::callBuyGold( )
{
	auto market = ZRBMenuMarket::create( );
	this->addChild( market , 10 );
	market->call_buy( );
}

void ZRBPageView::onEnter( )
{
	Layer::onEnter( );
	auto layer = LayerColor::create( Color4B( 255 , 255 , 255 , 150 ) , ZRB_VISIBLE_SIZE.width , ZRB_VISIBLE_SIZE.height );

	this->addChild( layer , 102 );
	layer->runAction( FadeOut::create( 0.2f ) );

	pageView->scrollToPage( ZRBUserDate::getInstance( )->getDateInt( KEY_CHECK_MATERIAL ) );
}

void ZRBPageView::gameBegain( cocos2d::Ref *sender )
{
	if ( dynamic_cast<__Bool*>( sender )->getValue( ) )
	{
		pageView->setLocalZOrder( 0 );
		pageView->setEnabled( false );
		this->unschedule( schedule_selector( ZRBPageView::schedulecallback ) );
	}
}

void ZRBPageView::updataGold( cocos2d::Ref *sender )
{
	for ( int i = 1; i < 3; i++ )
	{
		auto page = pageView->getPage( i )->getChildByTag( 11 );
		if ( page != nullptr )
		{
			auto menu = page->getChildByTag( 12 );
			if ( menu != nullptr )
			{
				auto item = menu->getChildByTag( 13 );
				if ( item != nullptr )
				{
					auto laber = dynamic_cast<Label *>( item->getChildByTag( 14 )->getChildByTag( 15 ) );
					laber->setString( String::createWithFormat( "%d" , dynamic_cast<__Integer *>( sender )->getValue( ) )->getCString( ) );
				}
			}
		}
	}
}


void ZRBPageView::setOpacityLayer( float p )
{
	opacityLayer->setOpacity( fabs( p / 2 ) );
}
