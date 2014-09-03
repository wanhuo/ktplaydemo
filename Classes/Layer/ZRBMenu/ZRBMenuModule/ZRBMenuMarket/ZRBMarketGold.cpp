
// Undone: buy
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#include "IOSiAP_Bridge.h"
#endif

#include "ZRBMarketGold.h"

ZRBMarketGold::ZRBMarketGold( )
	: vircash( { 7888 , 18888 , 1888 , 3888 } )
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

	firstMes = false;

	cash.push_back( atof( ZRBLanguage::getValue( "Gold_price_3" ) ) );
	cash.push_back( atof( ZRBLanguage::getValue( "Gold_price_4" ) ) );
	cash.push_back( atof( ZRBLanguage::getValue( "Gold_price_1" ) ) );
	cash.push_back( atof( ZRBLanguage::getValue( "Gold_price_2" ) ) );


	productId.push_back( "" );
	productId.push_back( "" );
	productId.push_back( "com.zero.test" );
	productId.push_back( "" );

	// ���ô�С
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
	// ���� pageView
	pageView = ui::PageView::create( );
	pageView->setSize( size );
	pageView->setPosition( Vec2( 0 , 15 ) );
	pageView->setTouchEnabled( true );

	// ������ҳ1
	auto layout0 = ui::Layout::create( );
	layout0->addChild( goldLayer0( ) );
	//    // ������ҳ 2
	//    auto layout1 = ui::Layout::create();
	//    layout1->addChild(LayerColor::create(Color4B(214, 234, 255, 250), 410, 550));
	//��ӷ�ҳ
	pageView->addPage( layout0 );
	//    pageView->addPage(layout1);

	// ��� pageview
	this->addChild( pageView );

	return true;

}

/**
*  ������ҳ, �������
*
*  @return ���ط�ҳ
*/
Layer * ZRBMarketGold::goldLayer0( )
{
	// ����������
	auto layer = Layer::create( );
	// ��ӷ���ͼƬ��
	auto lay = Layer::create( );
	// ����ͼƬ��λ��
	lay->setPosition( 0 , 70 );
	// ���û���
	auto pos = Vec2( size.width / 2 , size.height / 2 );

	//ѭ������ĸ����ͼƬ, ��ֵ
	for ( int i = 0; i < 4; i++ )
	{
		// ������Ҿ���
		auto sprite = Sprite::createWithSpriteFrameName( "gold_number.png" );
		// ����ê��(0, 0)
		sprite->setAnchorPoint( Vec2( 0 , 0 ) );
		// ��������
		sprite->setScale( size.height / 535 );
		// ����λ�� ���� i ֵ�ͻ���, ���ò�ͬλ��
		sprite->setPosition( i % 2 * pos.x + ( pos.x - sprite->getContentSize( ).width ) / 2 , int( i >= 2 ) * pos.y + 10 );

		// ���������ֵ label ��ֵ�� vircash ��ȡ��
		auto goldNum = Label::createWithTTF( String::createWithFormat( "%d" , vircash [ i ] )->getCString( ) , "customfout.otf" , 30 );
		// ����λ��, ��ɫ
		goldNum->setPosition( sprite->getContentSize( ).width / 2 , sprite->getContentSize( ).height * 0.16 );
		goldNum->setColor( Color3B( 0 , 0 , 0 ) );

		// ��ֵ label ��ӵ� sprite
		sprite->addChild( goldNum );

		// ��ӵ�ͼƬ��
		lay->addChild( sprite );
	}

	// ���� menuitem * ����
	Vector<MenuItem *>item;

	//ѭ������ĸ���ť
	for ( int i = 0; i < 4; i++ )
	{
		// ������ť, ����ͼƬ, ê��
		auto menuItem = MenuItemImage::create( );
		menuItem->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "currency.png" ) );
		menuItem->setAnchorPoint( Vec2( 0 , 0 ) );
		// ��������
		menuItem->setScale( size.height / 535 );
		// ����λ�� ���� i ֵ�ͻ���, ���ò�ͬλ��
		menuItem->setPosition( i % 2 * pos.x + ( pos.x - menuItem->getContentSize( ).width ) / 2 , int( i >= 2 ) * pos.y + 10 );
		// ���ûص�����
		menuItem->setCallback( CC_CALLBACK_0( ZRBMarketGold::callBack , this , i ) );

		// �����ʵ���� label ��ֵ�� cash ��ȡ��
		auto money = Label::createWithTTF( String::createWithFormat( "%.2f%s" , cash [ i ] , ZRBLanguage::getValue( "USD" ) )->getCString( ) , "customfout.otf" , 30 );
		//����λ�� ��ɫ
		money->setPosition( menuItem->getContentSize( ).width / 2 , menuItem->getContentSize( ).height / 2 );
		money->setColor( Color3B( 0 , 0 , 0 ) );

		// ��ʵ����label ��Ӱ�ť menuItem ��
		menuItem->addChild( money );

		if ( i == 2 )
		{
			auto hot = Sprite::createWithSpriteFrameName( ZRBLanguage::getValue( "Pic_hot_sale" ) );
			hot->setPosition( menuItem->getContentSize( ).width , menuItem->getContentSize( ).height );
			menuItem->addChild( hot );
		}

		//  ��ť��ӵ�������
		item.pushBack( menuItem );

	}

	// �����˵� ����λ��
	auto menu = Menu::createWithArray( item );
	menu->setPosition( 0 , 0 );

	// ���ͼƬ��, �˵�
	layer->addChild( lay );
	layer->addChild( menu );

	return layer;

}


/**
*  ����ص�
*
*  @param x ��ù���Ŀ��, �շ�, ˢ�½��
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
	changeLoad( false );
	auto mes = ZRBMessageLayer::create( );
	mes->setMessageLabel( ZRBLanguage::getValue( "Message_market_success" ) );
	mes->setPosition( -this->convertToWorldSpace( Vec2::ZERO ) );
	mes->setGlobalZOrder( 200 );
	this->addChild( mes );
	// ��ȡԭ�н��
	auto gold = ZRBUserDate::getInstance( )->getDateInt( KEY_DATA_GOLDNUM );
	// ���ӽ��
	gold += vircash [ goldId ];
	// ����
	ZRBUserDate::getInstance( )->saveData( KEY_DATA_GOLDNUM , &gold );
	auto * nGole = Integer::create( gold );
	// ������Ϣ
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
	mes->setGlobalZOrder( 200 );
	this->addChild( mes );

}
