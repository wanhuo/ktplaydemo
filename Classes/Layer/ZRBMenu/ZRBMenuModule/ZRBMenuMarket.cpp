

#include "ZRBMenuMarket.h"

bool ZRBMenuMarket::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}

	// �����������β� ��ӵ��˵��������²㴥��
	auto l = LayerColor::create( Color4B( 170 , 228 , 250 , 80 ) );
	auto mi = MenuItemSprite::create( l , l );
	auto m = Menu::create( mi , NULL );
	this->addChild( m , 2 , 11 );

	paging = Layer::create( );


	// Add spriteframecache
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "homeMenu.plist" );
	setBatchNode( SpriteBatchNode::create( "homeMenu.png" ) );
	this->addChild( getBatchNode( ) );

	// ��� ZRBMenuBase
	auto layer = ZRBMenuBase::create( );

	// ��� �˵�����
	_backboard = layer->getBackGround( );
	// ���ñ����С
	_backboard->setPreferredSize( ZRB_VISIBLE_SIZE * 0.8 );
	// ���ñ���λ��
	_backboard->setPosition( ZRB_VISIBLE_SIZE.width / 2 + 40 , ZRB_VISIBLE_SIZE.height * 3 / 2 );
	// ��ӱ���
	this->addChild( _backboard , 10 );


	// ����������ֵĶ���
	createAtionIn( );
	// ִ�ж���
	_backboard->runAction( getActionOut( ) );

	// �򱳰�����Ӳ˵�
	_backboard->addChild( setMarket( ) );
	_backboard->addChild( paging );

	// ���֪ͨ
	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBMenuMarket::setGoldNum ) , "NOTIFICATION_Gold" , nullptr );

	return true;
}



Menu * ZRBMenuMarket::setMarket( )
{

	// ��ȡ����ͼƬ��С
	size = _backboard->getContentSize( );

	// �����̳Ƿ�ҳ����
	pTitle = Label::createWithTTF( "����" , "customfout.otf" , 60 );
	pTitle->setPosition( size.width / 2 , size.height * 0.94 );
	pTitle->setColor( Color3B( 69 , 193 , 255 ) );
	_backboard->addChild( pTitle , 10 );


	// ��ӽ�ҵ���
	auto bg_gold = Sprite::createWithSpriteFrameName( "gold_bg.png" );
	bg_gold->setAnchorPoint( Vec2( 0 , 0 ) );
	bg_gold->setPosition( -190 , 0 );

	// ���ý������
	pGoldNum = Label::createWithTTF( String::createWithFormat( "%d" , ZRBUserDate::getInstance( )->getDateInt( KEY_DATA_GOLDNUM ) )->getCString( ) , "customfout.otf" , 30 );
	pGoldNum->setPosition( bg_gold->getContentSize( ).width * 0.5 , bg_gold->getContentSize( ).height * 0.5 );
	pGoldNum->setColor( Color3B( 0 , 0 , 0 ) );
	bg_gold->addChild( pGoldNum );

	// ��ӹ����Ұ�ť
	auto btGold = MenuItemImage::create( );
	btGold->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gold_add.png" ) );
	btGold->setPosition( ( size.width + bg_gold->getContentSize( ).width - btGold->getContentSize( ).width / 2 ) / 2 , size.height * 0.84 );
	btGold->setCallback( CC_CALLBACK_0( ZRBMenuMarket::call_buy , this ) );
	btGold->addChild( bg_gold , -1 );

	// ���ù�����߰�ť
	//    pProp = MenuItemImage::create();
	//    pProp->setAnchorPoint(Vec2(1, 0));
	//    pProp->setCallback(CC_CALLBACK_0(ZRBMenuMarket::call_prop, this));

	// ���ù������ﰴť
	pRole = MenuItemImage::create( );
	pRole->setAnchorPoint( Vec2( 1 , 1 ) );
	pRole->setCallback( CC_CALLBACK_0( ZRBMenuMarket::call_role , this ) );

	// ���ù����Ұ�ť
	pGold_buy = MenuItemImage::create( );
	pGold_buy->setAnchorPoint( Vec2( 1 , 1 ) );
	pGold_buy->setCallback( CC_CALLBACK_0( ZRBMenuMarket::call_gold_buy , this ) );



	// ���� back ��ť
	auto backLabel = Label::createWithTTF( ZRBLanguage::getValue( "Back" ) , "customfout.otf" , 70 );
	backLabel->setColor( Color3B( 69 , 193 , 255 ) );
	auto back = MenuItemLabel::create( backLabel );
	//    back->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back_button_set.png"));
	//    back->setScale(1.8);
	back->setCallback( CC_CALLBACK_0( ZRBMenuMarket::call_back , this ) );
	back->setPosition( size.width / 2 , size.height * 0.1 );


	// ��Ӳ˵�
	pMenuMarker = Menu::create( back , btGold , pRole , pGold_buy , NULL );
	pMenuMarker->setPosition( 0 , 0 );

	//��ʼ����ť����λ��, ���߷�ҳ����
	//    call_prop();
	call_role( );


	return pMenuMarker;

}



//void ZRBMenuMarket::call_prop()
//{
//    // ���Ĳ�߰�ť��С �л������߹���ҳ��
//    pProp->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_chack.png"));
//    pProp->setPosition(buttonRevise, size.height * 0.8);
//    
//    pRole->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role.png"));
//    pRole->setPosition(buttonRevise, size.height * 0.8);
//    
//    pGold_buy->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gold_buy.png"));
//    pGold_buy->setPosition(buttonRevise, size.height * 0.8 - pRole->getContentSize().height);
//    
//    // ���ñ���Ϊ"����"
//    pTitle->setString("����");
//    
//    // �Ƴ��ֲ�����ԭ������
//    paging->removeAllChildren();
//    // �������߹����ҳ
//    auto layer = ZRBMarketProp::create();
//    // ���ô�С
//    layer->setPosition(size.width * 0.1, size.height * 0.18);
//    // ��ӷ�ҳ
//    paging->addChild(layer);
//    
//
//}


void ZRBMenuMarket::call_role( )
{
	// ���Ĳ�߰�ť��С �л������ﹺ��ҳ��
	//    pProp->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop.png"));
	//    pProp->setPosition(buttonRevise, size.height * 0.8);

	pRole->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "role_chack.png" ) );
	pRole->setPosition( buttonRevise , size.height * 0.9 );

	pGold_buy->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gold_buy.png" ) );
	pGold_buy->setPosition( buttonRevise , size.height * 0.9 - pRole->getContentSize( ).height + 2 );

	// ���ñ���Ϊ"����"
	pTitle->setString( ZRBLanguage::getValue( "Market_role" ) );

	// �Ƴ��ֲ�����ԭ������
	paging->removeAllChildren( );

	// �������ﹺ���ҳ
	auto layer = ZRBMarketRole::create( );
	// ���ô�С
	layer->setPosition( size.width * 0.1 , size.height * 0.18 );
	// ��ӷ�ҳ
	paging->addChild( layer );


}


// ���Ĳ�߰�ť��С �л�����ҹ���ҳ��
void ZRBMenuMarket::call_gold_buy( )
{
	// ���Ĳ�߰�ť��С �л�����ҹ���ҳ��
	//    pProp->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop.png"));
	//    pProp->setPosition(buttonRevise, size.height * 0.8);

	pRole->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "role.png" ) );
	pRole->setPosition( buttonRevise , size.height * 0.9 );

	pGold_buy->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gold_buy_chack.png" ) );
	pGold_buy->setPosition( buttonRevise , size.height * 0.9 - pRole->getContentSize( ).height + 2 );

	// ���ñ���Ϊ"���"
	pTitle->setString( ZRBLanguage::getValue( "Market_gold" ) );

	// �Ƴ��ֲ�����ԭ������
	paging->removeAllChildren( );

	// ������ҹ����ҳ
	auto layer = ZRBMarketGold::create( );
	// ���ô�С
	layer->setPosition( size.width * 0.1 , size.height * 0.18 );
	// ��ӷ�ҳ
	paging->addChild( layer );

}


// ��ӽ�һص�
void ZRBMenuMarket::call_buy( )
{
	// ���ù����һص�
	call_gold_buy( );
}


// ���ػص�
void ZRBMenuMarket::call_back( )
{
	// �����˵��˳�����
	createAtionOut( );
	//ִ�ж���������������
	_backboard->runAction( Sequence::create( dynamic_cast<FiniteTimeAction *>( getActionIn( ) ) ,
		CallFunc::create( CC_CALLBACK_0( ZRBMenuMarket::call_clear , this ) ) , NULL ) );
}


// ���غ�����
void ZRBMenuMarket::call_clear( )
{
	// �Ƴ��˵� ����
	this->removeAllChildrenWithCleanup( true );
}

void ZRBMenuMarket::setGoldNum( cocos2d::Ref *sender )
{
	if ( this->getChildByTag( 11 ) != nullptr )
	{
		// ��ȡ���� ���� ��ʾ
		auto x = dynamic_cast<__Integer *>( sender );
		pGoldNum->setString( String::createWithFormat( "%d" , x->getValue( ) )->getCString( ) );
	}
}

ZRBMenuMarket::~ZRBMenuMarket( )
{
	// �Ƴ�֪ͨ
	NotificationCenter::getInstance( )->removeObserver( this , "NOTIFICATION_Gold" );
}
