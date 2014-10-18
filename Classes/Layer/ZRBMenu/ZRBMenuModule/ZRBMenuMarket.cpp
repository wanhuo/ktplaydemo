

#include "ZRBMenuMarket.h"

bool ZRBMenuMarket::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}

	// 创建背景屏蔽层 添加到菜单中屏蔽下层触摸
	auto l = LayerColor::create( Color4B( 170 , 228 , 250 , 80 ) );
	auto mi = MenuItemSprite::create( l , l );
	auto m = Menu::create( mi , NULL );
	this->addChild( m , 2 , 11 );

	paging = Layer::create( );
	paging->setName( "mk_p" );

	// Add spriteframecache
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "homeMenu.plist" );
	setBatchNode( SpriteBatchNode::create( "homeMenu.png" ) );
	this->addChild( getBatchNode( ) );

	// 添加 ZRBMenuBase
	auto layer = ZRBMenuBase::create( );

	// 添加 菜单背景
	_backboard = layer->getBackGround( );
	// 设置背板大小
	_backboard->setPreferredSize( ZRB_VISIBLE_SIZE * 0.8 );
	// 设置背板位置
	_backboard->setPosition( ZRB_VISIBLE_SIZE.width / 2 + 40 , ZRB_VISIBLE_SIZE.height * 3 / 2 );
	
	// 添加背板
	this->addChild( _backboard , 10 );


	// 创建背板出现的动作
	createAtionIn( );
	// 执行动作
	_backboard->runAction( getActionOut( ) );

	// 向背板上添加菜单
	_backboard->addChild( setMarket( ) );
	_backboard->addChild( paging );

	// 添加通知
	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBMenuMarket::setGoldNum ) , "NOTIFICATION_Gold" , nullptr );

	return true;
}



Menu * ZRBMenuMarket::setMarket( )
{

	// 获取背板图片大小
	size = _backboard->getContentSize( );

	// 设置商城分页标题
	pTitle = Label::createWithTTF( "道具" , "customfout.otf" , 60 );
	pTitle->setPosition( size.width / 2 , size.height * 0.94 );
	pTitle->setColor( Color3B( 69 , 193 , 255 ) );
	_backboard->addChild( pTitle , 10 );


	// 添加金币底纹
	auto bg_gold = Sprite::createWithSpriteFrameName( "gold_bg.png" );
	bg_gold->setAnchorPoint( Vec2( 0 , 0 ) );
	bg_gold->setPosition( -190 , 0 );

	// 设置金币字样
	pGoldNum = Label::createWithTTF( String::createWithFormat( "%d" , ZRBUserDate::getInstance( )->getDateInt( KEY_DATA_GOLDNUM ) )->getCString( ) , "customfout.otf" , 30 );
	pGoldNum->setPosition( bg_gold->getContentSize( ).width * 0.5 , bg_gold->getContentSize( ).height * 0.5 );
	pGoldNum->setColor( Color3B( 0 , 0 , 0 ) );
	bg_gold->addChild( pGoldNum );

	// 添加购买金币按钮
	auto btGold = MenuItemImage::create( );
	btGold->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gold_add.png" ) );
	btGold->setPosition( ( size.width + bg_gold->getContentSize( ).width - btGold->getContentSize( ).width / 2 ) / 2 , size.height * 0.84 );
	btGold->setCallback( CC_CALLBACK_0( ZRBMenuMarket::call_buy , this ) );
	btGold->addChild( bg_gold , -1 );

	// 设置购买道具按钮
	//    pProp = MenuItemImage::create();
	//    pProp->setAnchorPoint(Vec2(1, 0));
	//    pProp->setCallback(CC_CALLBACK_0(ZRBMenuMarket::call_prop, this));

	// 设置购买人物按钮
	pRole = MenuItemImage::create( );
	pRole->setAnchorPoint( Vec2( 1 , 1 ) );
	pRole->setCallback( CC_CALLBACK_0( ZRBMenuMarket::call_role , this ) );

	// 设置购买金币按钮
	pGold_buy = MenuItemImage::create( );
	pGold_buy->setAnchorPoint( Vec2( 1 , 1 ) );
	pGold_buy->setCallback( CC_CALLBACK_0( ZRBMenuMarket::call_gold_buy , this ) );



	// 设置 back 按钮
	auto backLabel = Label::createWithTTF( ZRBLanguage::getValue( "Back" ) , "customfout.otf" , 70 );
	backLabel->setColor( Color3B( 69 , 193 , 255 ) );
	auto back = MenuItemLabel::create( backLabel );
	//    back->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back_button_set.png"));
	//    back->setScale(1.8);
	back->setCallback( CC_CALLBACK_0( ZRBMenuMarket::call_back , this ) );
	back->setPosition( size.width / 2 , size.height * 0.1 );


	// 添加菜单
	pMenuMarker = Menu::create( back , btGold , pRole , pGold_buy , NULL );
	pMenuMarker->setPosition( 0 , 0 );

	//初始化按钮纹理位置, 道具分页内容
	//    call_prop();
	call_role( );


	return pMenuMarker;

}



//void ZRBMenuMarket::call_prop()
//{
//    // 更改侧边按钮大小 切换到道具购买页面
//    pProp->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_chack.png"));
//    pProp->setPosition(buttonRevise, size.height * 0.8);
//    
//    pRole->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("role.png"));
//    pRole->setPosition(buttonRevise, size.height * 0.8);
//    
//    pGold_buy->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gold_buy.png"));
//    pGold_buy->setPosition(buttonRevise, size.height * 0.8 - pRole->getContentSize().height);
//    
//    // 设置标题为"道具"
//    pTitle->setString("道具");
//    
//    // 移除分布层上原有内容
//    paging->removeAllChildren();
//    // 创建道具购买分页
//    auto layer = ZRBMarketProp::create();
//    // 设置大小
//    layer->setPosition(size.width * 0.1, size.height * 0.18);
//    // 添加分页
//    paging->addChild(layer);
//    
//
//}


void ZRBMenuMarket::call_role( )
{
	//if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	//{
	//	CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	//}
	// 更改侧边按钮大小 切换到人物购买页面
	//    pProp->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop.png"));
	//    pProp->setPosition(buttonRevise, size.height * 0.8);

	pRole->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "role_chack.png" ) );
	pRole->setPosition( buttonRevise , size.height * 0.9 );

	pGold_buy->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gold_buy.png" ) );
	pGold_buy->setPosition( buttonRevise , size.height * 0.9 - pRole->getContentSize( ).height + 2 );

	// 设置标题为"人物"
	pTitle->setString( ZRBLanguage::getValue( "Market_role" ) );

	// 移除分布层上原有内容
	paging->removeAllChildren( );

	// 创建人物购买分页
	auto layer = ZRBMarketRole::create( );
	layer->setName( "mk_p_c" );
	// 设置大小
	layer->setPosition( size.width * 0.1 , size.height * 0.18 );
	// 添加分页
	paging->addChild( layer );


}


// 更改侧边按钮大小 切换到金币购买页面
void ZRBMenuMarket::call_gold_buy( )
{
	// 更改侧边按钮大小 切换到金币购买页面
	//    pProp->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop.png"));
	//    pProp->setPosition(buttonRevise, size.height * 0.8);

	pRole->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "role.png" ) );
	pRole->setPosition( buttonRevise , size.height * 0.9 );

	pGold_buy->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gold_buy_chack.png" ) );
	pGold_buy->setPosition( buttonRevise , size.height * 0.9 - pRole->getContentSize( ).height + 2 );

	// 设置标题为"金币"
	pTitle->setString( ZRBLanguage::getValue( "Market_gold" ) );

	// 移除分布层上原有内容
	paging->removeAllChildren( );

	// 创建金币购买分页
	auto layer = ZRBMarketGold::create( );
	layer->setName( "mk_p_c" );
	// 设置大小
	layer->setPosition( size.width * 0.1 , size.height * 0.18 );
	// 添加分页
	paging->addChild( layer );

}


// 添加金币回调
void ZRBMenuMarket::call_buy( )
{
	// 调用购买金币回调
	call_gold_buy( );
}


// 返回回调
void ZRBMenuMarket::call_back( )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
	// 创建菜单退出动作
	createAtionOut( );
	//执行动作并调用清理函数
	_backboard->runAction( Sequence::create( dynamic_cast<FiniteTimeAction *>( getActionIn( ) ) ,
		CallFunc::create( CC_CALLBACK_0( ZRBMenuMarket::call_clear , this ) ) , NULL ) );
}


// 返回后清理
void ZRBMenuMarket::call_clear( )
{
	// 移除菜单 清理
	this->removeFromParentAndCleanup( true );
}

void ZRBMenuMarket::setGoldNum( cocos2d::Ref *sender )
{
	if ( this->getChildByTag( 11 ) != nullptr )
	{
		// 获取数据 设置 显示
		auto x = dynamic_cast<__Integer *>( sender );
		pGoldNum->setString( String::createWithFormat( "%d" , x->getValue( ) )->getCString( ) );
	}
}

ZRBMenuMarket::~ZRBMenuMarket( )
{
	// 移除通知
	NotificationCenter::getInstance( )->removeObserver( this , "NOTIFICATION_Gold" );
}
