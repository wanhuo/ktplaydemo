
#include "ZRBGameLayer.h"




#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
// Todo : ktplay
void ZRBGameLayer::reportScoreCallBack( bool isSuccess , const char *leaderboardId , long long score , KTErrorC *error )
{
	if ( isSuccess )
	{
		CCLOG( "++-%s---%lld-++" , leaderboardId , score );
	}
	else
	{
		CCLOG( "+--%d---%s-++" , error->code , error->description );
	}
}
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


ZRBGameLayer::ZRBGameLayer( )
	: ZRBBaseGameLayer()
	, _begainGame( false )
	, pBegainHeight(0)
	, curHeight(0)
	, count(0)
	, _idx()
{
}

ZRBGameLayer::~ZRBGameLayer( )
{
	NotificationCenter::getInstance( )->removeAllObservers( this );
}

bool ZRBGameLayer::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}
	
	ZRBBaseGameLayer::initObject( );

	pGoldNumLabel->setVisible( false );
	pScoreLabel->setVisible( false );
	pBatchNode->getChildByTag( GOLD_ICON_TAG )->setVisible( false );
	pMenu->setEnabled( false );
	pMenu->setVisible( false );

	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBGameLayer::gameBegain ) ,
													 "Game" , nullptr );
	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBGameLayer::resume ) ,
													 "NOTIFICATION_Resume" , nullptr );
	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBGameLayer::changeHero ) ,
													 "NOTIFICATION_Hero" , nullptr );
	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBGameLayer::pauseItemClick ) , "EnterBackground" , nullptr );

	this->scheduleUpdate( );
	schedule( schedule_selector( ZRBGameLayer::addTimboCall ) , 0.5 );

	return true;
}

void ZRBGameLayer::onEnter( )
{
	ZRBBaseGameLayer::onEnter( );
}



void ZRBGameLayer::update( float delta )
{
	// 实时高度
	auto upHeight = delta * pUpSpeed;
	curHeight += upHeight;
	// 更新精灵 , 按钮位置
	pHero->setHeroPositionY( pHero->getHeroPositionY( ) + upHeight );
	pMenu->setPositionY( pMenu->getPositionY( ) + upHeight );
	// 背景后退
	this->setPositionY( this->getPositionY( ) - upHeight );
	// 成绩更新 位置更新
	pScoreLabel->setString( String::createWithFormat( "%dm" , ( int ) ( pCurrentHeight / standard ) )->getCString( ) );
	pScoreLabel->setPositionY( pScoreLabel->getPositionY( ) + upHeight );
	// 金币位置更新
	pGoldNumLabel->setPositionY( pGoldNumLabel->getPositionY( ) + upHeight );

	//不移动bg
	pBg1->setPositionY( pBg1->getPositionY( ) + upHeight );

	//删除精灵 更新精灵的位置
	Vector<Node *> nodes = pBatchNode->getChildren( );
	for ( auto node : nodes )
	{
		auto p = convertToWorldSpace( node->getPosition( ) );

		if ( node->getTag( ) == BG2_TAG )
		{
			node->setPositionY( node->getPositionY( ) + upHeight * 0.7 );
			if ( p.y + node->getContentSize( ).height < 0 )
			{
				node->setPositionY( node->getPositionY( ) + ZRB_VISIBLE_SIZE.height * 3 );
				continue;
			}
		}

		if ( p.y + node->getContentSize( ).height < 0 )
		{
			pTimbos.eraseObject( dynamic_cast<Sprite *>( node ) );
			pBatchNode->removeChild( node , true );
		}

		if ( node->getTag( ) == GOLD_ICON_TAG )
		{
			node->setPositionY( node->getPositionY( ) + upHeight );
			continue;
		}
	}

	if ( !_begainGame )
	{
		return;
	}
	// 当前高度更新
	pCurrentHeight = pCurrentHeight + upHeight;
	if ( pCurrentHeight / standard > 450 && pUpSpeed <= 400 )
	{
		pUpSpeed += 100;
		if ( pCurrentHeight / standard > 520 && pUpSpeed <= 500 )
		{
			pUpSpeed += 100;
			if ( pCurrentHeight / standard > 600 && pUpSpeed <= 600 )
			{
				pUpSpeed += 100;
				if ( pCurrentHeight / standard > 700 && pUpSpeed <= 700 )
				{
					pUpSpeed += 100;
					if ( pCurrentHeight / standard > 800 && pUpSpeed <= 800 )
					{
						pUpSpeed += 100;
						if ( pCurrentHeight / standard > 900 && pUpSpeed <= 900 )
						{
							pUpSpeed += 100;
						}
					}
				}
			}
		}
	}
	// 添加按钮
	replenishtimbosAndAddItem( );
	//移动到藤条顶部，失败游戏
	if ( !pIsLost && pCanJump && pCurrentTimbo->getChildByTag( top ) )
	{
		if ( pHero->getHeroPositionY( ) >= pCurrentTimbo->getPositionY( ) + pCurrentTimbo->getContentSize( ).height )
		{
			// 失败
			pIsLost = true;
			// 掉落
			pHero->jumpTo( Point( pHero->getHeroPositionX( ) , pHero->getHeroPositionY( ) - ZRB_VISIBLE_SIZE.height - pHero->getHeroContentSize( ).height ) , 1 , 0 );
			
			if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
			{
				CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Die" ) );
			}

			this->runAction( Sequence::create( DelayTime::create( 1 ) , CallFunc::create( CC_CALLBACK_0( ZRBGameLayer::showGameFinish , this ) ) , NULL ) );
		}
	}

	//吃金币
	for ( int i = pGolds.size( ) - 1; i >= 0; i-- )
	{
		//金币和精灵碰撞
		if ( pGolds.at( i )->getBoundingBox( ).intersectsRect( pHero->getHeroBoundingBox( ) ) && !pIsLost )
		{
			if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
			{
				CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Gold" ) );
			}
			// 金币消失
			FadeOut *fade = FadeOut::create( 0.5 );
			ScaleTo *scale = ScaleTo::create( 1 , 3 );
			pGolds.at( i )->runAction( Spawn::create( fade , scale , NULL ) );
			// 删除金币
			pGolds.erase( i );
			// 金币更新
			pGoldNum = pGoldNum + 1;
			pGoldNumLabel->setString( String::createWithFormat( "%d" , pGoldNum )->getCString( ) );
		}
	}
}


Sprite * ZRBGameLayer::createTimbo( float length , Point pos )
{
	auto sp = ZRBBaseGameLayer::createTimbo( length , pos );
	// 添加藤的顶部
	auto sp1 = Sprite::createWithSpriteFrameName( "timbo_start" + pNameAfterStr + ".png" );
	sp1->setColor( sp->getColor( ) );
	sp1->setPosition( Point( sp->getContentSize( ).width / 2 , length - sp1->getContentSize( ).height / 2 ) );
	sp1->setTag( top );
	sp->addChild( sp1 );

	return sp;
}

Sprite * ZRBGameLayer::createTimboRandomPosHaveGold( )
{
	// 获取 0~3 之间随机数
	uniform_int_distribution<unsigned> dis_4( 0 , 3 );
	int ran = dis_4(engine);
	// 藤条长度
	float spLength;
	// 长度在200~300, 300~1000间的概率比为3 : 1
	if ( ran == 0 )
	{
		uniform_int_distribution<unsigned> tem1( 0 , 99 );
		spLength = tem1( engine ) + 200;
	}
	else
	{
		uniform_int_distribution<unsigned> tem7( 0 , 699 );
		spLength = tem7( engine ) + 300;
	}


	Sprite *sp;
	// 取出容器中最后一条藤
	Sprite * preSp = pTimbos.back( );
	//  藤条顶部
	float posY = preSp->getPositionY( ) + preSp->getContentSize( ).height - pBegainHeight;

	if ( posY <= pDisplayItemHeight * pColorNum - ZRB_VISIBLE_SIZE.height - 200 && posY + 1000 >= pDisplayItemHeight *pColorNum - ZRB_VISIBLE_SIZE.height - 200 )
	{
		// 如果再有藤条的长度超过一定长度时取相反长度
		int l = pDisplayItemHeight * pColorNum - ZRB_VISIBLE_SIZE.height - 200 - posY;
		sp = createTimbo( l + pUpSpeed * 2 , Point::ZERO );
	}
	else
	{
		sp = createTimbo( spLength , Point::ZERO );
	}

	// 添加位置
	int x , y;
	//x轴3个位置随机
	// 单向随机偏移量
	uniform_int_distribution<unsigned> width(0 , ZRB_VISIBLE_SIZE.width * 0.1);
	int ran1 = width( engine );
	// 双向随机偏移量
	int ranOffsetX = -ran1 + ZRB_VISIBLE_SIZE.width * 0.05;
	// 跟据最后藤条位置设置不同位置
	if ( preSp->getPositionX( ) <= ZRB_VISIBLE_SIZE.width * 0.25 )
	{
		ran = dis_0_1( engine ) + 1;
	}
	else if ( preSp->getPositionX( ) <= ZRB_VISIBLE_SIZE.width * 0.55 )
	{
		ran = dis_0_1( engine );
		if ( ran == 1 )
		{
			ran = 2;
		}
	}
	else
	{
		ran = dis_0_1( engine );
	}
	// 设置 X 轴位置
	switch ( ran )
	{
		case 0:
			x = ZRB_VISIBLE_SIZE.width*0.2 + ranOffsetX;
			break;
		case 1:
			x = ZRB_VISIBLE_SIZE.width*0.5 + ranOffsetX;
			break;
		case 2:
			x = ZRB_VISIBLE_SIZE.width*0.8 + ranOffsetX;
			break;
		default:
			break;
	}
	// 判断藤条长度是否大于最后的藤条
	if ( sp->getContentSize( ).height > preSp->getContentSize( ).height )
	{
		// 是, 添加到最后藤条 height * 0.7 - height
		uniform_int_distribution<unsigned> heigh( 0 , preSp->getContentSize( ).height * 0.3 );
		y = preSp->getContentSize( ).height * 0.7 + heigh( engine ) + preSp->getPositionY( );
	}
	else
	{
		// 否, 添加到最后藤条的上面自身长度的 0.3 之内
		uniform_int_distribution<unsigned> heigh( 0 , sp->getContentSize( ).height * 0.3 );
		y = preSp->getContentSize( ).height - heigh( engine ) + preSp->getPositionY( );
	}
	sp->setPosition( Point( x , y ) );

	// 纵向单列
	//gold  概率
	ran = dis_gold( engine );
	if ( ran == 0 )
	{

		for ( int i = 0; i<sp->getContentSize( ).height / 45 / 3; i++ )
		{
			// 添加金币
			Sprite *gold = Sprite::createWithSpriteFrameName( "gold" + pNameAfterStr + ".png" );
			// 旋转取消
			//            RotateBy *rotate=RotateBy::create(2, 360);
			//            gold->runAction(RepeatForever::create(rotate));
			// 判断添加的藤条在最后藤条的那边
			if ( sp->getPositionX( ) - preSp->getPositionX( )>0 )
			{
				// 在右边 添加金币在藤条左边
				gold->setPosition( Point( sp->getPositionX( ) - sp->getContentSize( ).width / 2 - gold->getContentSize( ).width / 2 , sp->getPositionY( ) + 45 * i + sp->getContentSize( ).height*0.3 ) );
			}
			else
			{
				// 在左边 添加金币在藤条右边
				gold->setPosition( Point( sp->getPositionX( ) + sp->getContentSize( ).width / 2 + gold->getContentSize( ).width / 2 , sp->getPositionY( ) + 45 * i + sp->getContentSize( ).height*0.3 ) );
			}
			// 保存金币
			pBatchNode->addChild( gold , 5000 );
			pGolds.pushBack( gold );
		}
	}
	// 四个方阵
	if ( preSp != pCurrentTimbo )
	{
		// 概率
		ran = dis_gold( engine );
		if ( ran == 2 )
		{
			for ( int i = 0; i<2; i++ )
			{
				for ( int j = 0; j<2; j++ )
				{
					Sprite *gold = Sprite::createWithSpriteFrameName( "gold" + pNameAfterStr + ".png" );
					//                    RotateBy *rotate=RotateBy::create(2, 360);
					//                    gold->runAction(RepeatForever::create(rotate));
					// 添加藤条和最后藤条的中间位置
					Point centerPos = Point( ( sp->getPositionX( ) + preSp->getPositionX( ) ) / 2 - gold->getContentSize( ).width / 2 , ( preSp->getBoundingBox( ).getMaxY( ) + sp->getBoundingBox( ).getMinY( ) ) / 2 - gold->getContentSize( ).height / 2 );
					// 设置金币位置
					gold->setPosition( Point( centerPos.x + ( i*gold->getContentSize( ).width + 5 ) , centerPos.y + ( j*gold->getContentSize( ).height + 5 ) ) );
					// 保存金币
					pBatchNode->addChild( gold , 5000 );
					pGolds.pushBack( gold );
				}
			}
		}
	}

	return sp;
}

// 定时添加藤条
void ZRBGameLayer::addTimboCall( float dt )
{
	ZRBBaseGameLayer::createTimbo( 250 , Vec2( ZRB_VISIBLE_SIZE.width / 2 , curHeight + ZRB_VISIBLE_SIZE.height * 3 / 2 ) );
	// 获取当前所在藤条
	for ( auto timbo : pTimbos )
	{
		if ( fabs( timbo->getPositionY( ) - pHero->getPositionY( ) ) < 250 )
		{
			pCurrentTimbo = timbo;
		}
	}
}

void ZRBGameLayer::initTimbos( )
{


	if ( _begainGame )
	{
		if ( pTimbos.empty( ) )
		{
			ZRBBaseGameLayer::createTimbo( ZRB_VISIBLE_SIZE.height * 1.7 , Vec2( ZRB_VISIBLE_SIZE.width / 2 , 60 + curHeight ) );
		}
		pCurrentTimbo = pTimbos.back( );
		// 添加藤的顶部
		auto sp1 = Sprite::createWithSpriteFrameName( "timbo_start" + pNameAfterStr + ".png" );
		sp1->setColor( pCurrentTimbo->getColor( ) );
		sp1->setPosition( Point( pCurrentTimbo->getContentSize( ).width / 2 , pCurrentTimbo->getContentSize( ).height - sp1->getContentSize( ).height / 2 ) );
		sp1->setTag( top );
		pCurrentTimbo->addChild( sp1 );
		pUpdateHeight = ZRB_VISIBLE_SIZE.height * 1;
	}
	else
	{
		ZRBBaseGameLayer::createTimbo( ZRB_VISIBLE_SIZE.height * 1.7 , Vec2( ZRB_VISIBLE_SIZE.width / 2 , 60 ) );
	}
}

void ZRBGameLayer::replenishtimbosAndAddItem( )
{
	if ( pCurrentHeight + ZRB_VISIBLE_SIZE.height >= pUpdateHeight )
	{
		// 可升级高度累加
		pUpdateHeight = pUpdateHeight + ZRB_VISIBLE_SIZE.height;
		//增加menu
		if ( pUpdateHeight / pDisplayItemHeight >= pColorNum&&pColorNum<5 )
		{
			createMenuItem( );
		}

		// 在可升级高度内添加藤条
		while ( pTimbos.back( )->getPositionY( ) - pBegainHeight < pUpdateHeight )
		{
			createTimboRandomPosHaveGold( );
		}
	}
}

void ZRBGameLayer::gameBegain( cocos2d::Ref *sender )
{
	pBegainHeight = curHeight - pCurrentHeight;
	_begainGame = dynamic_cast<__Bool*>( sender )->getValue( );

	auto gold = pBatchNode->getChildByTag( GOLD_ICON_TAG );

	if ( _begainGame )
	{
		if ( gold != nullptr )
		{
			gold->setVisible( true );
			gold->setPositionY( pGoldNumLabel->getPositionY( ) );

		}
		createMenuItem( );

		auto move = MoveBy::create( 0.2f , Vec2( 0 , 200 ) );
		pItems.at( 0 )->runAction( Sequence::create( move->reverse( ) , DelayTime::create( 0.2 ) , move , NULL ) );
		pItems.at( 1 )->runAction( Sequence::create( move->reverse( ) , DelayTime::create( 0.3 ) , move->clone( ) , NULL ) );

		pGoldNumLabel->setVisible( true );
		pScoreLabel->setVisible( true );
		pMenu->setVisible( true );
		pMenu->setEnabled( true );

		if ( isScheduled( schedule_selector( ZRBGameLayer::addTimboCall ) ) )
		{
			this->unschedule( schedule_selector( ZRBGameLayer::addTimboCall ) );
		}
		initTimbos( );
	}
	else
	{
		if ( gold != nullptr )
		{
			gold->setVisible( false );
		}
		pGoldNumLabel->setVisible( false );
		pScoreLabel->setVisible( false );
		pMenu->setVisible( false );
		pMenu->setEnabled( false );
	}
	if ( this->getChildByTag( 1000 ) )
	{
		this->removeChildByTag( 1000 );
	}
}

void ZRBGameLayer::showGameFinish( )
{

	// 取消的更新日期选择器
	pause( );
	pIsLost = true;
	ZRBGameFinishLayer *layer = ZRBGameFinishLayer::create( );
	layer->setPosition( 0 , curHeight );
	layer->setName("finish");
	layer->setInfo( ( int ) ( pCurrentHeight / standard ) , pGoldNum );
	this->addChild( layer , layerBatchNodeBaseGame::menuItem , 1000 );

	auto gold = pBatchNode->getChildByTag( GOLD_ICON_TAG );
	if ( gold != nullptr )
	{
		gold->setVisible( false );
	}

	pGoldNumLabel->setVisible( false );
	pScoreLabel->setVisible( false );
	pMenu->setVisible( false );
	pMenu->setEnabled( false );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	// Todo : ktplay
	if ( KTAccountManagerC::isLoggedIn( ) )
	{
		KTLeaderboardC::reportScore( int( pCurrentHeight / standard ) , "1234" , KTReportScoreCallBack( ZRBGameLayer::reportScoreCallBack ) );
	}
#endif 

}


void ZRBGameLayer::pauseItemClick( cocos2d::Ref *ref )
{
	if ( !_begainGame || pIsLost || this->getChildByTag(1000) != nullptr )
	{
		return;
	}
	// 创建添加暂停层
	ZRBGameMenuLayer *layer = ZRBGameMenuLayer::create( );
	layer->setPosition( Point( -ZRB_VISIBLE_SIZE.width / 2 , curHeight - ZRB_VISIBLE_SIZE.height / 2 ) );
	this->addChild( layer , layerBatchNodeBaseGame::menuItem , 1000 );
	layer->setName("pause");
	// 游戏暂停
	Director::getInstance( )->pause( );
}

void ZRBGameLayer::changePic( int idx )
{
	if ( idx != _idx || idx == 0 )
	{
		_idx = idx;
		this->removeAllChildrenWithCleanup( true );
		pItems.clear( );
		ZRBBaseGameLayer::initObject( );

		pBg1->setPosition( ZRB_VISIBLE_SIZE.width / 2 , curHeight + ZRB_VISIBLE_SIZE.height / 2 );
		ZRBBaseGameLayer::createTimbo( ZRB_VISIBLE_SIZE.height * 1.7 , Vec2( ZRB_VISIBLE_SIZE.width / 2 , 60 + curHeight ) );
		pHero->setHeroPositionY( pHero->getHeroPositionY( ) + curHeight );

		auto gold = pBatchNode->getChildByTag( GOLD_ICON_TAG );
		if ( gold != nullptr )
		{
			gold->setVisible( false );
			gold->setPositionY( gold->getPositionY( ) + curHeight );
		}
		pGoldNumLabel->setVisible( false );
		pGoldNumLabel->setPositionY( pGoldNumLabel->getPositionY( ) + curHeight );
		pScoreLabel->setVisible( false );
		pScoreLabel->setPositionY( pScoreLabel->getPositionY( ) + curHeight );
		pMenu->setPositionY( curHeight );
		pMenu->setEnabled( false );
		pMenu->setVisible( false );
	}
}

void ZRBGameLayer::resume( cocos2d::Ref *ref )
{
	this->removeAllChildrenWithCleanup( true );
	pItems.clear( );
	pTimbos.clear( );
	ZRBBaseGameLayer::initObject( );
	pBg1->setPosition( ZRB_VISIBLE_SIZE.width / 2 , curHeight + ZRB_VISIBLE_SIZE.height / 2 );
	pHero->setHeroPosition( Vec2( ZRB_VISIBLE_SIZE.width* 0.5 + pHero->getHeroContentSize( ).width / 2 + 7.5 ,
		pHero->getHeroPositionY( ) + curHeight ) );
	pGoldNumLabel->setPositionY( pGoldNumLabel->getPositionY( ) + curHeight );
	pScoreLabel->setPositionY( pScoreLabel->getPositionY( ) + curHeight );
	pMenu->setPositionY( curHeight );
	pCurrentHeight = 0;
	pUpdateHeight = 0;

	gameBegain( __Bool::create( true ) );
	if ( dynamic_cast<__Bool *>( ref )->getValue( ) )
	{
		Director::getInstance( )->resume( );
	}
	else
	{
		this->cocos2d::Node::resume( );
	}
}

void ZRBGameLayer::changeHero( cocos2d::Ref *sender )
{
	auto hero = ZRBTheme::getCurrentHero( );
	pHero->removeFromParentAndCleanup( true );
	pHero = ZRBHeroSprite::create( hero );
	pHero->setHeroPosition( Vec2( ZRB_VISIBLE_SIZE.width * 0.5 + pHero->getHeroContentSize( ).width / 2 + 7.5 ,
		ZRB_VISIBLE_SIZE.height / 2 + curHeight ) );
	this->addChild( pHero , 10 );
	pHero->climb( );
}


