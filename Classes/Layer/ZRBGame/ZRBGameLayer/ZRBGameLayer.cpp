
#include "ZRBGameLayer.h"

// Todo : ktplay
//void ZRBGameLayer::reportScoreCallBack( bool isSuccess , const char *leaderboardId , long long score , KTErrorC *error )
//{
//	if ( isSuccess )
//	{
//		CCLOG( "++-%s---%lld-++" , leaderboardId , score );
//	}
//	else
//	{
//		CCLOG( "+--%d---%s-++" , error->code , error->description );
//	}
//}

ZRBGameLayer::ZRBGameLayer( )
{
	pCurrentTimbo = nullptr;
	_begainGame = false;
	count = 0;
	curHeight = 0;
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
	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBGameLayer::pauseItemClick ) , "Background" , nullptr );

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
	// ʵʱ�߶�
	auto upHeight = delta * pUpSpeed;
	curHeight += upHeight;
	// ���¾��� , ��ťλ��
	pHero->setHeroPositionY( pHero->getHeroPositionY( ) + upHeight );
	pMenu->setPositionY( pMenu->getPositionY( ) + upHeight );
	// ��������
	this->setPositionY( this->getPositionY( ) - upHeight );
	// �ɼ����� λ�ø���
	pScoreLabel->setString( String::createWithFormat( "%dm" , ( int ) ( pCurrentHeight / standard ) )->getCString( ) );
	pScoreLabel->setPositionY( pScoreLabel->getPositionY( ) + upHeight );
	// ���λ�ø���
	pGoldNumLabel->setPositionY( pGoldNumLabel->getPositionY( ) + upHeight );

	//    CCLOG("%f,  %f,  %f,  ", curHeight, pCurrentHeight, pBegainHeight);
	//���ƶ�bg
	pBg1->setPositionY( pBg1->getPositionY( ) + upHeight );

	//ɾ������ ���¾����λ��
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
	// ��ǰ�߶ȸ���
	pCurrentHeight = pCurrentHeight + upHeight;
	if ( pCurrentHeight / standard > 400 && pUpSpeed <= 400 )
	{
		pUpSpeed += 100;
		if ( pCurrentHeight / standard > 500 && pUpSpeed <= 500 )
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
	// ��Ӱ�ť
	replenishtimbosAndAddItem( );
	//�ƶ�������������ʧ����Ϸ
	if ( !pIsLost && pCanJump && pCurrentTimbo->getChildByTag( top ) )
	{
		if ( pHero->getHeroPositionY( ) >= pCurrentTimbo->getPositionY( ) + pCurrentTimbo->getContentSize( ).height )
		{
			// ʧ��
			pIsLost = true;
			// ����
			pHero->jumpTo( Point( pHero->getHeroPositionX( ) , pHero->getHeroPositionY( ) - ZRB_VISIBLE_SIZE.height - pHero->getHeroContentSize( ).height ) , 1 , 0 );
			this->runAction( Sequence::create( DelayTime::create( 1 ) , CallFunc::create( CC_CALLBACK_0( ZRBGameLayer::showGameFinish , this ) ) , NULL ) );
		}
	}

	//�Խ��
	for ( int i = pGolds.size( ) - 1; i >= 0; i-- )
	{
		//��Һ;�����ײ
		if ( pGolds.at( i )->getBoundingBox( ).intersectsRect( pHero->getHeroBoundingBox( ) ) && !pIsLost )
		{
			// Todo : effect music
			//ZRBManager::playEffectMusic( "gem.wav" );
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


Sprite * ZRBGameLayer::createTimbo( float length , Point pos )
{
	auto sp = ZRBBaseGameLayer::createTimbo( length , pos );
	// ����ٵĶ���
	auto sp1 = Sprite::createWithSpriteFrameName( "timbo_start" + pNameAfterStr + ".png" );
	sp1->setColor( sp->getColor( ) );
	sp1->setPosition( Point( sp->getContentSize( ).width / 2 , length - sp1->getContentSize( ).height / 2 ) );
	sp1->setTag( top );
	sp->addChild( sp1 );

	return sp;
}

Sprite * ZRBGameLayer::createTimboRandomPosHaveGold( )
{
	// ��ȡ 0~3 ֮�������
	uniform_int_distribution<unsigned> dis_4( 0 , 3 );
	
	int ran = dis_4(engine);
	/// ��������
	float spLength;
	// ������200~300, 300~1000��ĸ��ʱ�Ϊ3 : 1
	if ( ran == 0 )
	{
		uniform_int_distribution<unsigned> tem1( 1 , 100 );
		spLength = tem1( engine ) + 200;
	}
	else
	{
		uniform_int_distribution<unsigned> tem7( 1 , 700 );
		spLength = tem7( engine ) + 300;
	}


	Sprite *sp;
	/// ȡ�����������һ����
	Sprite *preSp = pTimbos.back( );
	///  ��������
	float posY = preSp->getPositionY( ) + preSp->getContentSize( ).height - pBegainHeight;

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

	// ���λ��
	int x , y;
	//x��3��λ�����
	// �������ƫ����
	uniform_int_distribution<unsigned> width(0 , ZRB_VISIBLE_SIZE.width * 0.1);
	int ran1 = width( engine );
	// ˫�����ƫ����
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
	if ( sp->getContentSize( ).height > preSp->getContentSize( ).height )
	{
		// ��, ��ӵ�������� height * 0.7 - height
		uniform_int_distribution<unsigned> heigh( 0 , preSp->getContentSize( ).height * 0.3 );
		y = preSp->getContentSize( ).height*0.7 + heigh( engine ) + preSp->getPositionY( );
	}
	else
	{
		// ��, ��ӵ�������������������ȵ� 0.3 ֮��
		uniform_int_distribution<unsigned> heigh( 0 , preSp->getContentSize( ).height * 0.3 );
		y = preSp->getContentSize( ).height - heigh( engine ) + preSp->getPositionY( );
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

	return sp;
}

// ��ʱ�������
void ZRBGameLayer::addTimboCall( float dt )
{
	ZRBBaseGameLayer::createTimbo( 250 , Vec2( ZRB_VISIBLE_SIZE.width / 2 , curHeight + ZRB_VISIBLE_SIZE.height * 3 / 2 ) );
	// ��ȡ��ǰ��������
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
		// ����ٵĶ���
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
		// �������߶��ۼ�
		pUpdateHeight = pUpdateHeight + ZRB_VISIBLE_SIZE.height;
		//����menu
		if ( pUpdateHeight / pDisplayItemHeight >= pColorNum&&pColorNum<5 )
		{
			createMenuItem( );
		}

		// �ڿ������߶����������
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
	// ȡ���ĸ�������ѡ����
	pause( );
	pIsLost = true;
	ZRBGameFinishLayer *layer = ZRBGameFinishLayer::create( );
	layer->setPosition( 0 , curHeight );
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

	// Todo : ktplay
	//if ( KTAccountManagerC::isLoggedIn( ) )
	//{
	//	KTLeaderboardC::reportScore( int( pCurrentHeight / standard ) , "1234" , KTReportScoreCallBack( ZRBGameLayer::reportScoreCallBack ) );
	//}
}


void ZRBGameLayer::pauseItemClick( cocos2d::Ref *ref )
{
	// ���������ͣ��
	ZRBGameMenuLayer *layer = ZRBGameMenuLayer::create( );
	layer->setPosition( Point( -ZRB_VISIBLE_SIZE.width / 2 , curHeight - ZRB_VISIBLE_SIZE.height / 2 ) );
	layer->setScene( pSceneManager );
	this->addChild( layer , layerBatchNodeBaseGame::menuItem , 1000 );
	// ��Ϸ��ͣ
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


