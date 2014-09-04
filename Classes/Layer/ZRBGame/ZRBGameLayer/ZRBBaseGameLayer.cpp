

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
	*  TODO: �޸���Ӱ�ťʱ��
	*/
	pDisplayItemHeight = ZRB_VISIBLE_SIZE.height * 5;

	// �����ز�
	sHero* heroMaterial = ZRBTheme::getCurrentHero( );
	// �����ز�
	sMaterial* material = ZRBTheme::getCurrentMaterial( );
	// ��������
	pHero = ZRBHeroSprite::create( heroMaterial );
	// ���ر����ز�
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( material->plist );
	pBatchNode = SpriteBatchNode::create( material->png );
	pBatchNode->retain( );
	// �ز���
	pNameAfterStr = material->NameAfter;
	this->addChild( pBatchNode , layerBatchNodeBaseGame::batchNode2 );
	this->addChild( pHero , layerBatchNodeBaseGame::batchNode3 );

	Color3B colors [ 5 ];
	for ( int i = 0; i<5; i++ )
	{
		colors [ i ] = material->colors.at( i );
	}
	//��ɫ
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
			// ��ȡ����� 0-4
			uniform_int_distribution<unsigned>tem( 0 , num - 1 );
			ran = tem( engine );
		}
		// ������ɫ���Ϊ ran
		pAllColors [ 5 - num ] = colors [ ran ];

		//  �� ran ֮�����ɫǰ��, ���� ran
		for ( int i = ran; i<num - 1; i++ )
		{
			colors [ i ] = colors [ i + 1 ];
		}
		num = num - 1;
	}

	// ��Ӳ˵�
	pMenu = Menu::create( );
	this->addChild( pMenu , layerBaseGame::itemBaseGame );
	pMenu->setPosition( Point( 0 , 0 ) );
	pMenu->retain( );

	Sprite *pauseSp1 = Sprite::createWithSpriteFrameName( "pause" + pNameAfterStr + ".png" );
	Sprite *pauseSp2 = Sprite::createWithSpriteFrameName( "pause" + pNameAfterStr + ".png" );
	pauseSp2->setOpacity( 100 );
	//pauseItem ��ͣ
	MenuItemSprite *pauseItem = MenuItemSprite::create( pauseSp1 , pauseSp2 , CC_CALLBACK_1( ZRBBaseGameLayer::pauseItemClick , this ) );
	pauseItem->setAnchorPoint( Point( 0.5 , 0.5 ) );
	pauseItem->setPosition( Point( ZRB_VISIBLE_SIZE.width - pauseItem->getContentSize( ).width / 2 , ZRB_VISIBLE_SIZE.height - pauseItem->getContentSize( ).height / 2 ) );

	pauseItem->setTag( 0x1000 );

	//scoreLabel �ɼ�
	pScoreLabel = Label::createWithTTF( "0" , "customfout.otf" , 40 );
	pScoreLabel->setAnchorPoint( Point( 0 , 0.5 ) );
	pScoreLabel->setColor( Color3B( 96 , 96 , 96 ) );
	pScoreLabel->setPosition( Point( 20 , pauseItem->getBoundingBox( ).getMidY( ) ) );
	this->addChild( pScoreLabel , layerBaseGame::labelBaseGame );

	//goldNum ���
	pGoldNumLabel = Label::createWithTTF( "0" , "customfout.otf" , 40 );
	pGoldNumLabel->setAnchorPoint( Point( 0 , 0.5 ) );
	pGoldNumLabel->setColor( Color3B( 96 , 96 , 96 ) );
	pGoldNumLabel->setPosition( Point( ZRB_VISIBLE_SIZE.width*0.7 , pauseItem->getBoundingBox( ).getMidY( ) ) );
	this->addChild( pGoldNumLabel , layerBaseGame::labelBaseGame );
	// ���
	Sprite *goldSp = Sprite::createWithSpriteFrameName( "gold" + pNameAfterStr + ".png" );
	goldSp->setAnchorPoint( Point( 1 , 0.5 ) );
	goldSp->setPosition( Point( pGoldNumLabel->getBoundingBox( ).getMidX( ) - 20 , pauseItem->getBoundingBox( ).getMidY( ) ) );
	goldSp->setTag( GOLD_ICON_TAG );
	// ��ӵ��ڴ����                                  
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
	// ʵʱ�߶�
	float upHeight = delta*pUpSpeed;
	// ���¾��� , ��ťλ��
	pHero->setHeroPositionY( pHero->getHeroPositionY( ) + upHeight );
	pMenu->setPositionY( pMenu->getPositionY( ) + upHeight );
	// ��������
	this->setPositionY( this->getPositionY( ) - upHeight );
	// ��ǰ�߶ȸ���
	pCurrentHeight = pCurrentHeight + upHeight;
	// �ɼ����� λ�ø���
	pScoreLabel->setString( String::createWithFormat( "%d��" , ( int ) ( pCurrentHeight / standard ) )->getCString( ) );
	pScoreLabel->setPositionY( pScoreLabel->getPositionY( ) + upHeight );
	// ���λ�ø���
	pGoldNumLabel->setPositionY( pGoldNumLabel->getPositionY( ) + upHeight );

	// ����ѶȰ�ť
	replenishtimbosAndAddItem( );

	//���ƶ�bg
	pBg1->setPositionY( pBg1->getPositionY( ) + upHeight );

	//ɾ������ ���¾����λ��
	Vector<Node *> nodes = pBatchNode->getChildren( );
	for ( int i = nodes.size( ) - 1; i >= 0; i-- )
	{
		if ( nodes.at( i )->getTag( ) == GOLD_ICON_TAG )
		{
			nodes.at( i )->setPositionY( nodes.at( i )->getPositionY( ) + upHeight );
			continue;
		}
		/// ��������������ϵ�е�λ��
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
		// �Ƶ���Ļ�µ��Ƴ�
		if ( p.y<0 )
		{
			pBatchNode->removeChild( nodes.at( i ) , true );
		}
	}
	//�ƶ�������������ʧ����Ϸ
	if ( !pIsLost&&pCanJump )
	{
		if ( pHero->getHeroPositionY( ) >= pCurrentTimbo->getPositionY( ) + pCurrentTimbo->getContentSize( ).height )
		{
			// ʧ��
			pIsLost = true;
			// ����
			pHero->jumpTo( Point( pHero->getHeroPositionX( ) , pHero->getHeroPositionY( ) - ZRB_VISIBLE_SIZE.height - pHero->getHeroContentSize( ).height ) , 1 , 0 );
			this->runAction( Sequence::create( DelayTime::create( 1 ) , CallFunc::create( CC_CALLBACK_0( ZRBBaseGameLayer::showGameFinish , this ) ) , NULL ) );
		}
	}

	//�Խ��
	for ( int i = pGolds.size( ) - 1; i >= 0; i-- )
	{
		//��Һ;�����ײ
		if ( pGolds.at( i )->getBoundingBox( ).intersectsRect( pHero->getHeroBoundingBox( ) ) && !pIsLost )
		{
			// �����ʧ
			FadeOut *fade = FadeOut::create( 0.5 );
			ScaleTo *scale = ScaleTo::create( 1 , 3 );
			pGolds.at( i )->runAction( Spawn::create( fade , scale , NULL ) );
			// ɾ�����
			pGolds.erase( i );
			// ��Ҹ���
			pGoldNum = pGoldNum + 1;
			pGoldNumLabel->setString( String::createWithFormat( "%d" , pGoldNum )->getCString( ) );
		}
	}
}


Sprite * ZRBBaseGameLayer::createTimbo( float length , Point p )
{
	/// �����ɫ
	uniform_int_distribution<unsigned> colnum(0, pColorNum - 1);
	int num = colnum( engine );
	//�����ٽ�������
	Sprite *sp = Sprite::createWithSpriteFrameName( "timbo_end" + pNameAfterStr + ".png" );
	if ( p != Point::ZERO )
	{
		sp->setPosition( p );
	}
	int startTimboHeight = Sprite::createWithSpriteFrameName( "timbo_start" + pNameAfterStr + ".png" )->getContentSize( ).height;
	//  ����ģʽ ,  ������� ����ڱ�
	sp->getTexture( )->setAliasTexParameters( );
	// ��������
	Sprite *sp1 = Sprite::createWithSpriteFrameName( "timbo_center" + pNameAfterStr + ".png" );
	sp1->setAnchorPoint( Vec2( 0.5 , 0 ) );
	sp1->setPosition( Point( sp->getContentSize( ).width / 2 , sp->getContentSize( ).height / 2 ) );
	sp1->setColor( pAllColors [ num ] );
	sp1->getTexture( )->setAliasTexParameters( );
	sp->addChild( sp1 );
	///  ���� �ӳ���
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
	// �ж��ٳ����Ƿ�ﵽ��������
	if ( length - preSp1->getBoundingBox( ).getMaxY( ) - startTimboHeight*0.8 > 0 )
	{
		// ���������һ������
		sp1 = Sprite::createWithSpriteFrameName( "timbo_center" + pNameAfterStr + ".png" );
		// �趨�����Ϊȱ�ٵĳ���
		sp1->setTextureRect( Rect( sp1->getTextureRect( ).getMinX( ) , sp1->getTextureRect( ).getMinY( ) , sp1->getContentSize( ).width , length - preSp1->getBoundingBox( ).getMaxY( ) - startTimboHeight*0.7 ) , true , Size( sp1->getContentSize( ).width , length - preSp1->getBoundingBox( ).getMaxY( ) - startTimboHeight*0.7 ) );
		sp1->setAnchorPoint( Vec2( 0.5 , 0 ) );
		sp1->setPosition( Point( sp->getContentSize( ).width / 2 , preSp1->getBoundingBox( ).getMaxY( ) ) );
		sp1->setColor( pAllColors [ num ] );
		sp1->getTexture( )->setAliasTexParameters( );
		sp->addChild( sp1 );
	}


	// �����ٵ�λ��
	sp->setContentSize( Size( sp->getContentSize( ).width , length ) );
	sp->setColor( pAllColors [ num ] );
	sp->setAnchorPoint( Point( 0.5 , 0 ) );
	// ����ٵ� ������
	pBatchNode->addChild( sp , layerBaseGame::TimboBaseGame );
	pTimbos.pushBack( sp );
	return sp;

}

void ZRBBaseGameLayer::createTimboRandomPosHaveGoldOtherFunc( Sprite *preSp , Sprite *sp )
{
}

Sprite* ZRBBaseGameLayer::createTimboRandomPosHaveGold( )
{
	// ��ȡ 0~3 ֮�������
	uniform_int_distribution<unsigned> dis_0_3( 0 , 3 );
	unsigned ran = dis_0_3( engine );
	/// ��������
	float spLength;
	// ������200~300, 300~1000��ĸ��ʱ�Ϊ3 : 1
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
	/// ȡ�����������һ����
	Sprite *preSp = pTimbos.back( );
	///  ��������
	float posY = preSp->getPositionY( ) + preSp->getContentSize( ).height;
	//    pUpdateHeight/pDisplayItemHeight>=pColorNum;
	if ( posY <= pDisplayItemHeight * pColorNum - ZRB_VISIBLE_SIZE.height - 200 && posY + 1000 >= pDisplayItemHeight *pColorNum - ZRB_VISIBLE_SIZE.height - 200 )
	{
		// ������������ĳ��ȳ���һ������ʱȡ�෴����
		int l = pDisplayItemHeight * pColorNum - ZRB_VISIBLE_SIZE.height - 200 - posY;
		sp = createTimbo( l + pUpSpeed * 2 , Point::ZERO );
	}
	else
	{
		sp = createTimbo( spLength , Point::ZERO );
	}

	/// ���λ��
	int x , y;
	//x��3��λ�����
	/// �������ƫ����
	uniform_int_distribution<unsigned> dis_1_width( 0 , ZRB_VISIBLE_SIZE.width * 0.1 );
	int ran1 = dis_1_width( engine );
	/// ˫�����ƫ����
	int ranOffsetX = -ran1 + ZRB_VISIBLE_SIZE.width * 0.05;
	// �����������λ�����ò�ͬλ��
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
	// ���� X ��λ��
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
	// �ж����������Ƿ������������
	if ( sp->getContentSize( ).height>preSp->getContentSize( ).height )
	{
		// ��, ��ӵ�������� height * 0.7 - height
		y = preSp->getContentSize( ).height*0.7 + 0 /* arc4random( )*/ % ( ( int ) ( preSp->getContentSize( ).height*0.3 ) ) + preSp->getPositionY( );
	}
	else
	{
		// ��, ��ӵ�������������������ȵ� 0.3 ֮��
		y = preSp->getContentSize( ).height - 0 /* arc4random( ) */% ( ( int ) ( sp->getContentSize( ).height*0.3 ) ) + preSp->getPositionY( );
	}
	sp->setPosition( Point( x , y ) );

	// ������
	//gold  ����
	ran = dis_gold( engine ); 
	if ( ran == 0 )
	{

		for ( int i = 0; i<sp->getContentSize( ).height / 45 / 3; i++ )
		{
			// ��ӽ��
			Sprite *gold = Sprite::createWithSpriteFrameName( "gold" + pNameAfterStr + ".png" );
			// ��תȡ��
			//            RotateBy *rotate=RotateBy::create(2, 360);
			//            gold->runAction(RepeatForever::create(rotate));
			// �ж���ӵ�����������������Ǳ�
			if ( sp->getPositionX( ) - preSp->getPositionX( )>0 )
			{
				// ���ұ� ��ӽ�����������
				gold->setPosition( Point( sp->getPositionX( ) - sp->getContentSize( ).width / 2 - gold->getContentSize( ).width / 2 , sp->getPositionY( ) + 45 * i + sp->getContentSize( ).height*0.3 ) );
			}
			else
			{
				// ����� ��ӽ���������ұ�
				gold->setPosition( Point( sp->getPositionX( ) + sp->getContentSize( ).width / 2 + gold->getContentSize( ).width / 2 , sp->getPositionY( ) + 45 * i + sp->getContentSize( ).height*0.3 ) );
			}
			// ������
			pBatchNode->addChild( gold , 5000 );
			pGolds.pushBack( gold );
		}
	}
	// �ĸ�����
	if ( preSp != pCurrentTimbo )
	{
		// ����
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
					// �������������������м�λ��
					Point centerPos = Point( ( sp->getPositionX( ) + preSp->getPositionX( ) ) / 2 - gold->getContentSize( ).width / 2 , ( preSp->getBoundingBox( ).getMaxY( ) + sp->getBoundingBox( ).getMinY( ) ) / 2 - gold->getContentSize( ).height / 2 );
					// ���ý��λ��
					gold->setPosition( Point( centerPos.x + ( i*gold->getContentSize( ).width + 5 ) , centerPos.y + ( j*gold->getContentSize( ).height + 5 ) ) );
					// ������
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
	//��һ����
	pCurrentTimbo = createTimbo( ZRB_VISIBLE_SIZE.height*1.3 , Point( ZRB_VISIBLE_SIZE.width / 2 , 60 ) );
	//������
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
		// �������߶��ۼ�
		pUpdateHeight = pUpdateHeight + ZRB_VISIBLE_SIZE.height;
		//����menu
		if ( pUpdateHeight / pDisplayItemHeight >= pColorNum&&pColorNum<5 )
		{
			createMenuItem( );
		}
		// �ڿ������߶����������
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
	// �ж��Ƿ����Ծ
	if ( !pCanJump || pIsLost )
	{
		return;
	}
	MenuItemSprite * item = dynamic_cast<MenuItemSprite *>( ref );
	Sprite *nextTimbo;
	// �ڵ�ǰ�������ҵ����ڽӴ���
	for ( int i = 0; i<pTimbos.size( ); i++ )
	{
		if ( pCurrentTimbo == pTimbos.at( i ) )
		{
			nextTimbo = pTimbos.at( i + 1 );
			break;
		}
	}
	// ��ǰ�ٵ���ɫ�Ͱ�ť����ɫ�Ƿ���ͬ
	if ( nextTimbo->getColor( ) == item->getNormalImage( )->getColor( ) )
	{
		// ��ͬ��Ծ
		heroJumpNext( );
	}
}

void ZRBBaseGameLayer::pauseItemClick( Ref *ref )
{
	// ���������ͣ��
	ZRBGameMenuLayer *layer = ZRBGameMenuLayer::create( );
	layer->setPosition( Point( -ZRB_VISIBLE_SIZE.width / 2 , pCurrentHeight - ZRB_VISIBLE_SIZE.height / 2 ) );
	layer->setScene( pSceneManager );
	this->addChild( layer , layerBatchNodeBaseGame::menuItem );
	// ��Ϸ��ͣ
	Director::getInstance( )->pause( );
}

void ZRBBaseGameLayer::setModeScene( ZRBSceneManager _manager )
{
	pSceneManager = _manager;
}

void ZRBBaseGameLayer::heroJumpNext( )
{
	// Todo : effect music
	//ZRBManager::playEffectMusic( "background.caf" );
	/// �ڵ�ǰ�������ҵ����ڽӴ���
	Sprite *nextTimbo;
	for ( int i = 0; i<pTimbos.size( ); i++ )
	{
		if ( pCurrentTimbo == pTimbos.at( i ) )
		{
			nextTimbo = pTimbos.at( i + 1 );
			break;
		}
	}

	/// ��ǰλ��
	Point nextPos;
	// �жϵ�ǰ���ٵ��Ǳ�
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
	// ��ǰ��ɫ����һ
	pColorNum = pColorNum + 1;

	// ������ť
	Scale9Sprite *spColor1 = Scale9Sprite::createWithSpriteFrameName( "button" + pNameAfterStr + ".png" , Rect( 20 , 20 , 1 , 1 ) );
	spColor1->setColor( pAllColors [ pColorNum - 1 ] );
	// ����ʱ
	Scale9Sprite *spColor2 = Scale9Sprite::createWithSpriteFrameName( "button" + pNameAfterStr + ".png" , Rect( 30 , 30 , 1 , 1 ) );
	spColor2->setColor( pAllColors [ pColorNum - 1 ] );
	spColor2->setOpacity( 150 );

	MenuItemSprite *item = MenuItemSprite::create( spColor1 , spColor2 , CC_CALLBACK_1( ZRBBaseGameLayer::colorItemClick , this ) );
	// ���水ť
	pItems.pushBack( item );
	item->setAnchorPoint( Point( 0 , 0 ) );
	pMenu->addChild( item );
	item->setPosition( Point( 0 , -item->getContentSize( ).height ) );
	// ������ɫ�����ð�ťλ�� ��С
	switch ( pColorNum )
	{
		case 1:
		{
			// ��ȡԭʼ��С
			item->setTag( COLOR_ITEM_1_TAG );
			pItemDefaultSize = item->getContentSize( );
			item->getNormalImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*0.5 , item->getContentSize( ).height ) );
			item->getSelectedImage( )->setContentSize( Size( ZRB_VISIBLE_SIZE.width*0.5 , item->getContentSize( ).height ) );
			// ���ð�ťʵ�ʵ����С
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
			// ��ť�˳����� ����ִ��
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
	// ��������
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
		// �����زĶ�������������ָ���
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
		// �����������
		Sprite *sp = Sprite::createWithSpriteFrameName( String::createWithFormat( "decoration_%d%s.png" , ran , pNameAfterStr.c_str( ) )->getCString( ) );
		sp->setAnchorPoint( Point( 0.5 , 0 ) );

		if ( _isRanPos )
		{
			// ���λ��
			uniform_int_distribution<unsigned> dis_width( 0 , ZRB_VISIBLE_SIZE.width );
			ran = dis_width( engine );
			sp->setPosition( Point( ran , ZRB_VISIBLE_SIZE.height * 3 / 10 * i ) );
		}
		else
		{
			// �ԳƳ���������
			if ( i % 2 == 1 )
			{
				sp->setPosition( Point( -sp->getContentSize( ).width*0.25 , ZRB_VISIBLE_SIZE.height * 3 / 10 * i ) );
			}
			else
			{
				sp->setPosition( Point( ZRB_VISIBLE_SIZE.width + sp->getContentSize( ).width*0.25 , ZRB_VISIBLE_SIZE.height * 3 / 10 * i ) );
			}
		}
		// ���澫�� 
		pBatchNode->addChild( sp );
		sp->setTag( BG2_TAG );
	}
}


void ZRBBaseGameLayer::resetItemPos( )
{
	// ������ɫ�������ð�ť��С��ɫ
	// ��������
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
	// ȡ���ĸ�������ѡ����
	this->unscheduleUpdate( );
	pIsLost = true;
	ZRBGameFinishLayer *layer = ZRBGameFinishLayer::create( );
	layer->setPosition( 0 , pCurrentHeight );
	layer->setSceneManager( pSceneManager );
	layer->setInfo( ( int ) ( pCurrentHeight / standard ) , pGoldNum );
	this->addChild( layer , layerBatchNodeBaseGame::menuItem );
}

ZRBHeroSprite* ZRBBaseGameLayer::getHero( )
{
	return pHero;
}


