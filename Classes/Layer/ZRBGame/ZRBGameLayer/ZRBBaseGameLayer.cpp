

#include "ZRBBaseGameLayer.h"


ZRBBaseGameLayer::ZRBBaseGameLayer( )
	: dis_gold (    0 , 6 )
	, dis_0_1 (     0 , 1 )
{
	pUpSpeed = 0;
	pDisplayItemHeight = 0;
}

ZRBBaseGameLayer::~ZRBBaseGameLayer( )
{
}

bool ZRBBaseGameLayer::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}
	
	this->scheduleUpdate( );
	initObject( );
	return true;
}


void ZRBBaseGameLayer::initObject( )
{
	pColorNum = 0;
	pCurrentHeight = 0;
	pIsLost = false;
	pCanJump = true;
	pUpSpeed = 400;
	pGoldNum = 0;
	/**
	*  TODO: 修改添加按钮时间
	*/
	pDisplayItemHeight = ZRB_VISIBLE_SIZE.height * 5;

	// 精灵素材
	sHero* heroMaterial = ZRBTheme::getCurrentHero( );
	// 背景素材
	sMaterial* material = ZRBTheme::getCurrentMaterial( );
	// 创建精灵
	pHero = ZRBHeroSprite::create( heroMaterial );
	// 加载背景素材
	//SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( material->plist );
	//pBatchNode = SpriteBatchNode::create( material->png );
	pBatchNode = SpriteBatchNode::createWithTexture( Director::getInstance( )->getTextureCache()->getTextureForKey( material->png ) );
	pBatchNode->retain( );
	// 素材名
	pNameAfterStr = material->NameAfter;
	this->addChild( pBatchNode , layerBatchNodeBaseGame::batchNode2 );
	this->addChild( pHero , layerBatchNodeBaseGame::batchNode3 );

	Color3B colors [ 5 ];
	for ( int i = 0; i<5; i++ )
	{
		colors [ i ] = material->colors.at( i );
	}
	//颜色
	int num = 5;
	while ( num>0 )
	{
		int ran;
		if ( num == 1 )
		{
			ran = 0;
		}
		else
		{
			// 获取随机数 0-4
			uniform_int_distribution<unsigned>tem( 0 , num - 1 );
			ran = tem( engine );
		}
		// 保存颜色序号为 ran
		pAllColors [ 5 - num ] = colors [ ran ];

		//  将 ran 之后的颜色前移, 覆盖 ran
		for ( int i = ran; i<num - 1; i++ )
		{
			colors [ i ] = colors [ i + 1 ];
		}
		num = num - 1;
	}

	// 添加菜单
	pMenu = Menu::create( );
	this->addChild( pMenu , layerBaseGame::itemBaseGame );
	pMenu->setPosition( Point( 0 , 0 ) );
	pMenu->retain( );

	Sprite *pauseSp1 = Sprite::createWithSpriteFrameName( "pause" + pNameAfterStr + ".png" );
	Sprite *pauseSp2 = Sprite::createWithSpriteFrameName( "pause" + pNameAfterStr + ".png" );
	pauseSp2->setOpacity( 100 );
	//pauseItem 暂停
	MenuItemSprite *pauseItem = MenuItemSprite::create( pauseSp1 , pauseSp2 , CC_CALLBACK_1( ZRBBaseGameLayer::pauseItemClick , this ) );
	pauseItem->setAnchorPoint( Point( 0.5 , 0.5 ) );
	pauseItem->setPosition( Point( ZRB_VISIBLE_SIZE.width - pauseItem->getContentSize( ).width / 2 , ZRB_VISIBLE_SIZE.height - pauseItem->getContentSize( ).height / 2 ) );

	pauseItem->setTag( 0x1000 );

	//scoreLabel 成绩
	pScoreLabel = Label::createWithTTF( "0" , "customfout.otf" , 40 );
	pScoreLabel->setAnchorPoint( Point( 0 , 0.5 ) );
	pScoreLabel->setColor( Color3B( 96 , 96 , 96 ) );
	pScoreLabel->setPosition( Point( 20 , pauseItem->getBoundingBox( ).getMidY( ) ) );
	this->addChild( pScoreLabel , layerBaseGame::labelBaseGame );

	//goldNum 金币
	pGoldNumLabel = Label::createWithTTF( "0" , "customfout.otf" , 40 );
	pGoldNumLabel->setAnchorPoint( Point( 0 , 0.5 ) );
	pGoldNumLabel->setColor( Color3B( 96 , 96 , 96 ) );
	pGoldNumLabel->setPosition( Point( ZRB_VISIBLE_SIZE.width*0.7 , pauseItem->getBoundingBox( ).getMidY( ) ) );
	this->addChild( pGoldNumLabel , layerBaseGame::labelBaseGame );
	// 金币
	Sprite *goldSp = Sprite::createWithSpriteFrameName( "gold" + pNameAfterStr + ".png" );
	goldSp->setAnchorPoint( Point( 1 , 0.5 ) );
	goldSp->setPosition( Point( pGoldNumLabel->getBoundingBox( ).getMidX( ) - 20 , pauseItem->getBoundingBox( ).getMidY( ) ) );
	goldSp->setTag( GOLD_ICON_TAG );
	// 添加到内存池中                                  
	pBatchNode->addChild( goldSp , layerBaseGame::labelBaseGame );

	pMenu->addChild( pauseItem );

	createMenuItem( );
	//hero
	pHero->setHeroPosition( Point( ZRB_VISIBLE_SIZE.width*0.5 + pHero->getHeroContentSize( ).width / 2 + 7.5 , ZRB_VISIBLE_SIZE.height / 2 ) );

	initTimbos( );

	setBg1( "bg" + pNameAfterStr + ".png" );
	setBg2( material->bg2ImageNum , material->isRanPos );
	pHero->climb( );
}

void ZRBBaseGameLayer::onEnter( )
{
	Layer::onEnter( );
}

void ZRBBaseGameLayer::update( float delta )
{
	// 实时高度
	float upHeight = delta*pUpSpeed;
	// 更新精灵 , 按钮位置
	pHero->setHeroPositionY( pHero->getHeroPositionY( ) + upHeight );
	pMenu->setPositionY( pMenu->getPositionY( ) + upHeight );
	// 背景后退
	this->setPositionY( this->getPositionY( ) - upHeight );
	// 当前高度更新
	pCurrentHeight = pCurrentHeight + upHeight;
	// 成绩更新 位置更新
	pScoreLabel->setString( String::createWithFormat( "%m" , ( int ) ( pCurrentHeight / standard ) )->getCString( ) );
	pScoreLabel->setPositionY( pScoreLabel->getPositionY( ) + upHeight );
	// 金币位置更新
	pGoldNumLabel->setPositionY( pGoldNumLabel->getPositionY( ) + upHeight );

	// 添加难度按钮
	replenishtimbosAndAddItem( );

	//不移动bg
	pBg1->setPositionY( pBg1->getPositionY( ) + upHeight );

	//删除精灵 更新精灵的位置
	Vector<Node *> nodes = pBatchNode->getChildren( );
	for ( int i = nodes.size( ) - 1; i >= 0; i-- )
	{
		if ( nodes.at( i )->getTag( ) == GOLD_ICON_TAG )
		{
			nodes.at( i )->setPositionY( nodes.at( i )->getPositionY( ) + upHeight );
			continue;
		}
		/// 精灵在世界坐标系中的位置
		Point p = convertToWorldSpace( Point( nodes.at( i )->getPositionX( ) , nodes.at( i )->getBoundingBox( ).getMaxY( ) ) );
		if ( nodes.at( i )->getTag( ) == BG2_TAG )
		{
			nodes.at( i )->setPositionY( nodes.at( i )->getPositionY( ) + upHeight*0.7 );
			if ( p.y<0 )
			{
				nodes.at( i )->setPositionY( nodes.at( i )->getPositionY( ) + ZRB_VISIBLE_SIZE.height * 3 );
			}
			continue;
		}
		// 移到屏幕下的移除
		if ( p.y<0 )
		{
			pBatchNode->removeChild( nodes.at( i ) , true );
		}
	}
	//移动到藤条顶部，失败游戏
	if ( !pIsLost&&pCanJump )
	{
		if ( pHero->getHeroPositionY( ) >= pCurrentTimbo->getPositionY( ) + pCurrentTimbo->getContentSize( ).height )
		{
			// 失败
			pIsLost = true;
			// 掉落
			pHero->jumpTo( Point( pHero->getHeroPositionX( ) , pHero->getHeroPositionY( ) - ZRB_VISIBLE_SIZE.height - pHero->getHeroContentSize( ).height ) , 1 , 0 );
			this->runAction( Sequence::create( DelayTime::create( 1 ) , CallFunc::create( CC_CALLBACK_0( ZRBBaseGameLayer::showGameFinish , this ) ) , NULL ) );
		}
	}

	//吃金币
	for ( int i = pGolds.size( ) - 1; i >= 0; i-- )
	{
		//金币和精灵碰撞
		if ( pGolds.at( i )->getBoundingBox( ).intersectsRect( pHero->getHeroBoundingBox( ) ) && !pIsLost )
		{
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


Sprite * ZRBBaseGameLayer::createTimbo( float length , Point p )
{
	/// 随机颜色
	uniform_int_distribution<unsigned> colnum(0, pColorNum - 1);
	int num = colnum( engine );
	//创建藤结束精灵
	Sprite *sp = Sprite::createWithSpriteFrameName( "timbo_end" + pNameAfterStr + ".png" );
	if ( p != Point::ZERO )
	{
		sp->setPosition( p );
	}
	int startTimboHeight = Sprite::createWithSpriteFrameName( "timbo_start" + pNameAfterStr + ".png" )->getContentSize( ).height;
	//  正常模式 ,  不抗锯齿 解决黑边
	sp->getTexture( )->setAliasTexParameters( );
	// 创建藤条
	Sprite *sp1 = Sprite::createWithSpriteFrameName( "timbo_center" + pNameAfterStr + ".png" );
	sp1->setAnchorPoint( Vec2( 0.5 , 0 ) );
	sp1->setPosition( Point( sp->getContentSize( ).width / 2 , sp->getContentSize( ).height / 2 ) );
	sp1->setColor( pAllColors [ num ] );
	sp1->getTexture( )->setAliasTexParameters( );
	sp->addChild( sp1 );
	///  保存 延长藤
	Sprite *preSp1 = sp1;
	while ( preSp1->getBoundingBox( ).getMaxY( ) + preSp1->getContentSize( ).height<length - startTimboHeight*0.7 )
	{
		sp1 = Sprite::createWithSpriteFrameName( "timbo_center" + pNameAfterStr + ".png" );
		sp1->setPosition( Point( sp->getContentSize( ).width / 2 , preSp1->getBoundingBox( ).getMidY( ) + sp1->getContentSize( ).height - 1 ) );
		sp1->setColor( pAllColors [ num ] );
		sp1->getTexture( )->setAliasTexParameters( );
		sp->addChild( sp1 );
		preSp1 = sp1;
	}
	// 判断藤长度是否达到给定长度
	if ( length - preSp1->getBoundingBox( ).getMaxY( ) - startTimboHeight*0.8 > 0 )
	{
		// 不到则添加一个精灵
		sp1 = Sprite::createWithSpriteFrameName( "timbo_center" + pNameAfterStr + ".png" );
		// 设定精灵高为缺少的长度
		sp1->setTextureRect( Rect( sp1->getTextureRect( ).getMinX( ) , sp1->getTextureRect( ).getMinY( ) , sp1->getContentSize( ).width , length - preSp1->getBoundingBox( ).getMaxY( ) - startTimboHeight*0.7 ) , true , Size( sp1->getContentSize( ).width , length - preSp1->getBoundingBox( ).getMaxY( ) - startTimboHeight*0.7 ) );
		sp1->setAnchorPoint( Vec2( 0.5 , 0 ) );
		sp1->setPosition( Point( sp->getContentSize( ).width / 2 , preSp1->getBoundingBox( ).getMaxY( ) ) );
		sp1->setColor( pAllColors [ num ] );
		sp1->getTexture( )->setAliasTexParameters( );
		sp->addChild( sp1 );
	}


	// 设置藤的位置
	sp->setContentSize( Size( sp->getContentSize( ).width , length ) );
	sp->setColor( pAllColors [ num ] );
	sp->setAnchorPoint( Point( 0.5 , 0 ) );
	// 添加藤到 所有藤
	pBatchNode->addChild( sp , layerBaseGame::TimboBaseGame );
	pTimbos.pushBack( sp );
	return sp;

}

void ZRBBaseGameLayer::createTimboRandomPosHaveGoldOtherFunc( Sprite *preSp , Sprite *sp )
{
}

Sprite* ZRBBaseGameLayer::createTimboRandomPosHaveGold( )
{
	// 获取 0~3 之间随机数
	uniform_int_distribution<unsigned> dis_0_3( 0 , 3 );
	unsigned ran = dis_0_3( engine );
	/// 藤条长度
	float spLength;
	// 长度在200~300, 300~1000间的概率比为3 : 1
	if ( ran == 0 )
	{
		uniform_int_distribution<unsigned> dis_1_100( 1 , 100 );
		spLength = dis_1_100( engine ) + 200; 
	}
	else
	{
		uniform_int_distribution<unsigned> dis_1_700( 1 , 700 );
		spLength = dis_1_700( engine ) + 300;
	}


	Sprite *sp;
	/// 取出容器中最后一条藤
	Sprite *preSp = pTimbos.back( );
	///  藤条顶部
	float posY = preSp->getPositionY( ) + preSp->getContentSize( ).height;
	//    pUpdateHeight/pDisplayItemHeight>=pColorNum;
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

	/// 添加位置
	int x , y;
	//x轴3个位置随机
	/// 单向随机偏移量
	uniform_int_distribution<unsigned> dis_1_width( 0 , ZRB_VISIBLE_SIZE.width * 0.1 );
	int ran1 = dis_1_width( engine );
	/// 双向随机偏移量
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
	if ( sp->getContentSize( ).height>preSp->getContentSize( ).height )
	{
		// 是, 添加到最后藤条 height * 0.7 - height
		y = preSp->getContentSize( ).height*0.7 + 0 /* arc4random( )*/ % ( ( int ) ( preSp->getContentSize( ).height*0.3 ) ) + preSp->getPositionY( );
	}
	else
	{
		// 否, 添加到最后藤条的上面自身长度的 0.3 之内
		y = preSp->getContentSize( ).height - 0 /* arc4random( ) */% ( ( int ) ( sp->getContentSize( ).height*0.3 ) ) + preSp->getPositionY( );
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

	//    createTimboRandomPosHaveGoldOtherFunc(preSp,sp);
	return sp;
}
void ZRBBaseGameLayer::initTimbos( )
{
	//第一条藤
	pCurrentTimbo = createTimbo( ZRB_VISIBLE_SIZE.height*1.3 , Point( ZRB_VISIBLE_SIZE.width / 2 , 60 ) );
	//其他藤
	while ( pTimbos.at( pTimbos.size( ) - 1 )->getPositionY( )<ZRB_VISIBLE_SIZE.height * 1 )
	{
		createTimboRandomPosHaveGold( );
	}
	pUpdateHeight = ZRB_VISIBLE_SIZE.height * 1;
}

void ZRBBaseGameLayer::replenishtimbosAndAddItem( )
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
		while ( pTimbos.back( )->getPositionY( )<pUpdateHeight )
		{
			createTimboRandomPosHaveGold( );
		}
	}
}

void ZRBBaseGameLayer::setCanJump( )
{
	pCanJump = true;
}

void ZRBBaseGameLayer::colorItemClick( Ref *ref )
{
	// 判断是否可跳跃
	if ( !pCanJump || pIsLost )
	{
		return;
	}
	MenuItemSprite * item = dynamic_cast<MenuItemSprite *>( ref );
	Sprite *nextTimbo;
	// 在当前的藤上找到现在接触的
	for ( int i = 0; i<pTimbos.size( ); i++ )
	{
		if ( pCurrentTimbo == pTimbos.at( i ) )
		{
			nextTimbo = pTimbos.at( i + 1 );
			break;
		}
	}
	// 当前藤的颜色和按钮的颜色是否相同
	if ( nextTimbo->getColor( ) == item->getNormalImage( )->getColor( ) )
	{
		// 相同跳跃
		heroJumpNext( );
	}
}

void ZRBBaseGameLayer::pauseItemClick( Ref *ref )
{
	
	// 创建添加暂停层
	ZRBGameMenuLayer *layer = ZRBGameMenuLayer::create( );
	layer->setPosition( Point( -ZRB_VISIBLE_SIZE.width / 2 , pCurrentHeight - ZRB_VISIBLE_SIZE.height / 2 ) );
	//layer->setScene( pSceneManager );
	this->addChild( layer , layerBatchNodeBaseGame::menuItem );
	// 游戏暂停
	Director::getInstance( )->pause( );
}


void ZRBBaseGameLayer::heroJumpNext( )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Jump" ) );
	}
	/// 在当前的藤上找到现在接触的
	Sprite *nextTimbo;
	for ( int i = 0; i<pTimbos.size( ); i++ )
	{
		if ( pCurrentTimbo == pTimbos.at( i ) )
		{
			nextTimbo = pTimbos.at( i + 1 );
			break;
		}
	}

	/// 当前位置
	Point nextPos;
	// 判断当前在藤的那边
	if ( nextTimbo->getPositionX( ) - pCurrentTimbo->getPositionX( )>0 )
	{
		nextPos.x = nextTimbo->getBoundingBox( ).getMinX( ) - pHero->getHeroContentSize( ).width / 2;
	}
	else
	{
		nextPos.x = nextTimbo->getBoundingBox( ).getMaxX( ) + pHero->getHeroContentSize( ).width / 2;
	}
	nextPos.y = pHero->getHeroPositionY( );

	float time;
	time = ( nextPos.x - pHero->getHeroPositionX( ) ) / 800;
	if ( time<0 )
	{
		time = -time;
	}

	pCanJump = false;
	if ( pHero->getHeroBoundingBox( ).getMaxY( ) + time*pUpSpeed<nextTimbo->getPositionY( ) )
	{
		nextPos.y = pHero->getHeroPositionY( );
		if ( nextPos.x>pHero->getHeroPositionX( ) )
		{
			nextPos.x = ZRB_VISIBLE_SIZE.width + 100;
		}
		else
		{
			nextPos.x = -100;
		}
		time = ( nextPos.x - pHero->getHeroPositionX( ) ) / 800;
		if ( time<0 )
		{
			time = -time;
		}
		pHero->jumpTo( nextPos , time , pCurrentTimbo->getContentSize( ).width );
		this->runAction( Sequence::create( DelayTime::create( time ) , CallFunc::create( CC_CALLBACK_0( ZRBBaseGameLayer::showGameFinish , this ) ) , NULL ) );
		return ;
	}

	pHero->jumpTo( nextPos , time , pCurrentTimbo->getContentSize( ).width );
	this->runAction( Sequence::create( DelayTime::create( time ) , CallFunc::create( CC_CALLBACK_0( ZRBBaseGameLayer::setCanJump , this ) ) , NULL ) );
	pCurrentTimbo = nextTimbo;

}

void ZRBBaseGameLayer::createMenuItem( )
{
	// 当前颜色数加一
	pColorNum = pColorNum + 1;

	// 创建按钮
	Scale9Sprite *spColor1 = Scale9Sprite::createWithSpriteFrameName( "button" + pNameAfterStr + ".png" , Rect( 20 , 20 , 1 , 1 ) );
	spColor1->setColor( pAllColors [ pColorNum - 1 ] );
	// 按下时
	Scale9Sprite *spColor2 = Scale9Sprite::createWithSpriteFrameName( "button" + pNameAfterStr + ".png" , Rect( 30 , 30 , 1 , 1 ) );
	spColor2->setColor( pAllColors [ pColorNum - 1 ] );
	spColor2->setOpacity( 150 );

	MenuItemSprite *item = MenuItemSprite::create( spColor1 , spColor2 , CC_CALLBACK_1( ZRBBaseGameLayer::colorItemClick , this ) );
	// 保存按钮
	pItems.pushBack( item );
	item->setAnchorPoint( Point( 0 , 0 ) );
	pMenu->addChild( item );
	item->setPosition( Point( 0 , -item->getContentSize( ).height ) );
	// 跟据颜色数设置按钮位置 大小
	switch ( pColorNum )
	{
		case 1:
		{
			// 获取原始大小
			item->setTag( COLOR_ITEM_1_TAG );
			pItemDefaultSize = item->getContentSize( );
			item->getNormalImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*0.5 , item->getContentSize( ).height ) );
			item->getSelectedImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*0.5 , item->getContentSize( ).height ) );
			// 设置按钮实际点击大小
			item->setContentSize( Size( ZRB_VISIBLE_SIZE.width*0.5 , ZRB_VISIBLE_SIZE.height*0.8 ) );
			item->setPosition( Point( ZRB_VISIBLE_SIZE.width * 0 , 0 ) );
			break;
		}
		case 2:
		{
			item->setTag( COLOR_ITEM_2_TAG );
			item->getNormalImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*0.5 , item->getContentSize( ).height ) );
			item->getSelectedImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*0.5 , item->getContentSize( ).height ) );
			item->setContentSize( Size( ZRB_VISIBLE_SIZE.width*0.5 , ZRB_VISIBLE_SIZE.height*0.8 ) );
			item->setPosition( Point( ZRB_VISIBLE_SIZE.width*0.5 , 0 ) );
			break;
		}
		case 3:
		{
			// 按钮退出动作 依次执行
			item->setTag( COLOR_ITEM_3_TAG );
			MoveBy *move = MoveBy::create( 0.2 , Point( 0 , -pItemDefaultSize.height ) );
			for ( int i = 0; i<pItems.size( ) - 1; i++ )
			{
				pItems.at( i )->runAction( Sequence::create( DelayTime::create( 0.1*i ) , move->clone( ) , NULL ) );
			}

			item->runAction( Sequence::create( DelayTime::create( 0.2 ) , move->clone( ) , CallFunc::create( CC_CALLBACK_0( ZRBBaseGameLayer::resetItemPos , this ) ) , NULL ) );
			break;
		}
		case 4:
		{
			item->setTag( COLOR_ITEM_4_TAG );
			MoveBy *move = MoveBy::create( 0.2 , Point( 0 , -pItemDefaultSize.height ) );
			for ( int i = 0; i<pItems.size( ) - 1; i++ )
			{
				pItems.at( i )->runAction( Sequence::create( DelayTime::create( 0.1*i ) , move->clone( ) , NULL ) );
			}
			item->runAction( Sequence::create( DelayTime::create( 0.3 ) , move->clone( ) , CallFunc::create( CC_CALLBACK_0( ZRBBaseGameLayer::resetItemPos , this ) ) , NULL ) );
			break;
		}
		case 5:
		{
			item->setTag( COLOR_ITEM_5_TAG );
			MoveBy *move = MoveBy::create( 0.2 , Point( 0 , -item->getContentSize( ).height ) );
			for ( int i = 0; i<pItems.size( ) - 1; i++ )
			{
				pItems.at( i )->runAction( Sequence::create( DelayTime::create( 0.1*i ) , move->clone( ) , NULL ) );
			}
			item->runAction( Sequence::create( DelayTime::create( 0.4 ) , move->clone( ) , CallFunc::create( CC_CALLBACK_0( ZRBBaseGameLayer::resetItemPos , this ) ) , NULL ) );
			break;
		}
		default:
			break;
	}

}

void ZRBBaseGameLayer::setBg1( std::string fileNameOrFrameFileName )
{
	// 创建背景
	if ( fileNameOrFrameFileName == "" )
	{
		pBg1 = Sprite::create( );
		this->addChild( pBg1 , layerBatchNodeBaseGame::batchNode1 );
	}
	else
	{
		pBg1 = Sprite::createWithSpriteFrameName( fileNameOrFrameFileName );
		pBatchNode->addChild( pBg1 , layerBaseGame::bg1BaseGame );
	}
	pBg1->setPosition( Point( ZRB_VISIBLE_SIZE.width / 2 , ZRB_VISIBLE_SIZE.height / 2 ) );
	pBg1->retain( );

}

void ZRBBaseGameLayer::setBg2( int ImageNum , bool _isRanPos )
{
	for ( int i = 1; i <= 10; i++ )
	{
		// 跟据素材多少设置随机出现概率
		int ran;
		if ( ImageNum == 1 )
		{
			ran = 1;
		}
		else
		{
			uniform_int_distribution<unsigned> tem( 0 , ImageNum - 1 );
			ran = tem( engine ) + 1;
		}
		// 创建随机精灵
		Sprite *sp = Sprite::createWithSpriteFrameName( String::createWithFormat( "decoration_%d%s.png" , ran , pNameAfterStr.c_str( ) )->getCString( ) );
		sp->setAnchorPoint( Point( 0.5 , 0 ) );

		if ( _isRanPos )
		{
			// 随机位置
			uniform_int_distribution<unsigned> dis_width( 0 , ZRB_VISIBLE_SIZE.width );
			ran = dis_width( engine );
			sp->setPosition( Point( ran , ZRB_VISIBLE_SIZE.height * 3 / 10 * i ) );
		}
		else
		{
			// 对称出现在两侧
			if ( i % 2 == 1 )
			{
				sp->setPosition( Point( -sp->getContentSize( ).width*0.25 , ZRB_VISIBLE_SIZE.height * 3 / 10 * i ) );
			}
			else
			{
				sp->setPosition( Point( ZRB_VISIBLE_SIZE.width + sp->getContentSize( ).width*0.25 , ZRB_VISIBLE_SIZE.height * 3 / 10 * i ) );
			}
		}
		// 保存精灵 
		pBatchNode->addChild( sp );
		sp->setTag( BG2_TAG );
	}
}


void ZRBBaseGameLayer::resetItemPos( )
{
	// 根据颜色数量设置按钮大小颜色
	// 滑动出现
	switch ( pColorNum )
	{
		case 3:
		{

			MoveBy *move = MoveBy::create( 0.2 , Point( 0 , pItemDefaultSize.height ) );
			for ( int i = 0; i<pItems.size( ); i++ )
			{
				pItems.at( i )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*( 1 / 3.0 ) , ZRB_VISIBLE_SIZE.height * 0.8 ) );
				pItems.at( i )->getNormalImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*( 1 / 3.0 ) , pItemDefaultSize.height ) );
				pItems.at( i )->getSelectedImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*( 1 / 3.0 ) , pItemDefaultSize.height ) );
				pItems.at( i )->setPositionX( ZRB_VISIBLE_SIZE.width*( i / 3.0 ) );
				pItems.at( i )->stopAllActions( );
				pItems.at( i )->runAction( Sequence::create( DelayTime::create( 0.1*i ) , move->clone( ) , NULL ) );
			}
			pItems.at( 2 )->setPositionY( -pItemDefaultSize.height );
			break;
		}
		case 4:{
			MoveBy *move = MoveBy::create( 0.2 , Point( 0 , pItemDefaultSize.height ) );
			for ( int i = 0; i<pItems.size( ); i++ )
			{
				pItems.at( i )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*( 1 / 4.0 ) , ZRB_VISIBLE_SIZE.height * 0.8 ) );
				pItems.at( i )->getNormalImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*( 1 / 4.0 ) , pItemDefaultSize.height ) );
				pItems.at( i )->getSelectedImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*( 1 / 4.0 ) , pItemDefaultSize.height ) );
				pItems.at( i )->setPositionX( ZRB_VISIBLE_SIZE.width*( i / 4.0 ) );
				pItems.at( i )->stopAllActions( );
				pItems.at( i )->runAction( Sequence::create( DelayTime::create( 0.1*i ) , move->clone( ) , NULL ) );
			}
			pItems.at( 3 )->setPositionY( -pItemDefaultSize.height );

			break;
		}
		case 5:
		{
			MoveBy *move = MoveBy::create( 0.2 , Point( 0 , pItemDefaultSize.height ) );
			for ( int i = 0; i<pItems.size( ); i++ )
			{
				pItems.at( i )->setContentSize( Size( pItemDefaultSize.width , ZRB_VISIBLE_SIZE.height * 0.8 ) );
				pItems.at( i )->getNormalImage( )->setContentSize( pItemDefaultSize );
				pItems.at( i )->getSelectedImage( )->setContentSize( pItemDefaultSize );
				pItems.at( i )->setPositionX( ZRB_VISIBLE_SIZE.width*( i / 5.0 ) );
				pItems.at( i )->stopAllActions( );
				pItems.at( i )->runAction( Sequence::create( DelayTime::create( 0.1*i ) , move->clone( ) , NULL ) );
			}
			pItems.at( 4 )->setPositionY( -pItemDefaultSize.height );
			break;
		}
		default:
			break;
	}
}

void ZRBBaseGameLayer::showGameFinish( )
{
	// 取消的更新日期选择器
	this->unscheduleUpdate( );
	pIsLost = true;
	ZRBGameFinishLayer *layer = ZRBGameFinishLayer::create( );
	layer->setPosition( 0 , pCurrentHeight );
	layer->setInfo( ( int ) ( pCurrentHeight / standard ) , pGoldNum );
	this->addChild( layer , layerBatchNodeBaseGame::menuItem );
}

ZRBHeroSprite* ZRBBaseGameLayer::getHero( )
{
	return pHero;
}


