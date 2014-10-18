

#include "ZRBMarketGold.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Utilities/ios.h"
#endif

ZRBMarketGold::ZRBMarketGold( )
	: vircash( { 3888 , 1888 , 18888 , 7888 } )
{
}


ZRBMarketGold::~ZRBMarketGold( )
{
}

bool ZRBMarketGold::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}

	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "Gold_pic.plist" , "Gold_pic.png" );
	
	firstMes = false;

	cash.push_back( atof( ZRBLanguage::getValue( "Gold_price_2" ) ) );
	cash.push_back( atof( ZRBLanguage::getValue( "Gold_price_1" ) ) );
	cash.push_back( atof( ZRBLanguage::getValue( "Gold_price_4" ) ) );
	cash.push_back( atof( ZRBLanguage::getValue( "Gold_price_3" ) ) );

	cashPic.push_back( "gold_3888.png" );
	cashPic.push_back( "gold_1888.png" );
	cashPic.push_back( "gold_18888.png" );
	cashPic.push_back( "gold_7888.png" );

	productId.push_back( "" );					// 3888
	productId.push_back( "" );					// 1888	
	productId.push_back( "com.zero.test" );		// 18888
	productId.push_back( "" );					// 7888

	// 设置大小
	if ( ZRB_VISIBLE_SIZE.height > 1100 )
	{
		size = Size( 410 , 535 );
	}
	else if ( ZRB_VISIBLE_SIZE.height > 950 )
	{
		size = Size( 410 , 455 );
	}
	else
	{
		size = Size( 410 , 400 );
	}
	// 创建 pageView
	pageView = ui::PageView::create( );
	pageView->setSize( size );
	pageView->setPosition( Vec2( 0 , 15 ) );
	pageView->setTouchEnabled( true );

	// 创建分页1
	auto layout0 = ui::Layout::create( );
	layout0->addChild( goldLayer0( ) );
	//    // 创建分页 2
	//    auto layout1 = ui::Layout::create();
	//    layout1->addChild(LayerColor::create(Color4B(214, 234, 255, 250), 410, 550));
	//添加分页
	pageView->addPage( layout0 );
	//    pageView->addPage(layout1);

	// 添加 pageview
	this->addChild( pageView );

	return true;

}

/**
*  创建分页, 添加内容
*
*  @return 返回分页
*/
Layer * ZRBMarketGold::goldLayer0( )
{
	// 创建基础层
	auto layer = Layer::create( );
	// 添加放置图片层
	auto lay = Layer::create( );
	// 设置图片层位置
	lay->setPosition( 0 , 70 );
	// 设置基点
	auto pos = Vec2( size.width / 2 , size.height / 2 );

	//循环添加四个金币图片, 数值
	for ( int i = 0; i < 4; i++ )
	{
		// 创建金币精灵
		auto sprite = Sprite::createWithSpriteFrameName( cashPic.at(i) );
		// 设置锚点(0, 0)
		sprite->setAnchorPoint( Vec2( 0 , 0 ) );
		// 缩放适配
		sprite->setScale( size.height / 535 );
		// 设置位置 跟据 i 值和基点, 设置不同位置
		sprite->setPosition( i % 2 * pos.x + ( pos.x - sprite->getContentSize( ).width ) / 2 , int( i >= 2 ) * pos.y + 10 );

		//// 创建金币数值 label 数值从 vircash 中取得
		//auto goldNum = Label::createWithTTF( String::createWithFormat( "%d" , vircash [ i ] )->getCString( ) , "customfout.otf" , 30 );
		//// 设置位置, 颜色
		//goldNum->setPosition( sprite->getContentSize( ).width / 2 , sprite->getContentSize( ).height * 0.16 );
		//goldNum->setColor( Color3B( 0 , 0 , 0 ) );

		//// 数值 label 添加到 sprite
		//sprite->addChild( goldNum );

		// 添加到图片层
		lay->addChild( sprite );
	}

	// 创建 menuitem * 容器
	Vector<MenuItem *>item;

	//循环添加四个按钮
	for ( int i = 0; i < 4; i++ )
	{
		// 创建按钮, 设置图片, 锚点
		auto menuItem = MenuItemImage::create( );
		menuItem->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "currency.png" ) );
		menuItem->setAnchorPoint( Vec2( 0 , 0 ) );
		// 缩放适配
		menuItem->setScale( size.height / 535 );
		// 设置位置 跟据 i 值和基点, 设置不同位置
		menuItem->setPosition( i % 2 * pos.x + ( pos.x - menuItem->getContentSize( ).width ) / 2 , int( i >= 2 ) * pos.y + 10 );
		// 设置回调函数
		menuItem->setCallback( CC_CALLBACK_0( ZRBMarketGold::callBack , this , i ) );

		// 添加现实货币 label 数值从 cash 中取得
		auto money = Label::createWithTTF( String::createWithFormat( "%.2f%s" , cash [ i ] , ZRBLanguage::getValue( "USD" ) )->getCString( ) , "customfout.otf" , 30 );
		//设置位置 颜色
		money->setPosition( menuItem->getContentSize( ).width / 2 , menuItem->getContentSize( ).height / 2 );
		money->setColor( Color3B( 0 , 0 , 0 ) );

		// 现实货币label 添加按钮 menuItem 上
		menuItem->addChild( money );

		if ( i == 2 )
		{
			auto hot = Sprite::createWithSpriteFrameName( ZRBLanguage::getValue( "Pic_hot_sale" ) );
			hot->setPosition( menuItem->getContentSize( ).width , menuItem->getContentSize( ).height );
			menuItem->addChild( hot );
		}

		//  按钮添加到容器中
		item.pushBack( menuItem );

	}

	// 创建菜单 设置位置
	auto menu = Menu::createWithArray( item );
	menu->setPosition( 0 , 0 );

	// 添加图片层, 菜单
	layer->addChild( lay );
	layer->addChild( menu );

	return layer;

}


/**
*  购买回调
*
*  @param x 获得购买目标, 收费, 刷新金币
*/
void ZRBMarketGold::callBack( int x )
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	firstMes = false;
	auto buy = new IOSiAP_Bridge( );
	buy->delegate = this;
	changeLoad( true );
	buy->requestProducts( productId.at( x ) );
#endif
	goldId = x;
}


void ZRBMarketGold::changeLoad( bool isShow )
{
	if ( isShow )
	{
		auto loading = ZRBLoadingLayer::create( );
		loading->setLoading( 50 , 2 , 1.5 );
		loading->setPosition( -this->convertToWorldSpace( Vec2::ZERO ) );
		this->addChild( loading , 10 , 11 );
	}
	else
	{
		_eventDispatcher->removeEventListenersForTarget( this->getChildByTag( 11 ) );
		this->removeChildByTag( 11 );
	}
}

void ZRBMarketGold::buyFinish( )
{
	if ( firstMes )
	{
		return;
	}
	firstMes = true;
	changeLoad( false );
	auto mes = ZRBMessageLayer::create( );
	mes->setMessageLabel( ZRBLanguage::getValue( "Message_market_success" ) );
	mes->setPosition( -this->convertToWorldSpace( Vec2::ZERO ) );
	mes->setGlobalZOrder( 200 );
	mes->setName( "mk_r_mes" );
	this->addChild( mes );
	// 获取原有金币
	auto gold = ZRBUserDate::getInstance( )->getDateInt( KEY_DATA_GOLDNUM );
	// 增加金币
	gold += vircash [ goldId ];
	// 保存
	ZRBUserDate::getInstance( )->saveData( KEY_DATA_GOLDNUM , &gold );
	auto * nGole = Integer::create( gold );
	// 发送消息
	NotificationCenter::getInstance( )->postNotification( "NOTIFICATION_Gold" , nGole );
}

void ZRBMarketGold::buyFild( )
{
	if ( firstMes )
	{
		return;
	}
	firstMes = true;
	changeLoad( false );
	auto mes = ZRBMessageLayer::create( );
	mes->setMessageLabel( ZRBLanguage::getString( "Message_itunes_fail_1" ) + "\n" + ZRBLanguage::getString( "Message_itunes_fail_2" ) );
	mes->setPosition( -this->convertToWorldSpace( Vec2::ZERO ) );
	mes->setName( "mk_r_mes" );
	mes->setGlobalZOrder( 200 );
	this->addChild( mes );

}
