


#include "ZRBHeroSprite.h"

#define DEFAULT_CAPACITY 29

ZRBHeroSprite* ZRBHeroSprite::create( sHero* hero )
{
	ZRBHeroSprite *batchNode = new ZRBHeroSprite;
	batchNode->initWithFile( hero->png , DEFAULT_CAPACITY );
	batchNode->autorelease( );
	batchNode->initThis( hero );
	return batchNode;
}


// ���� ���� �� ����
void ZRBHeroSprite::initThis( sHero* hero )
{
	pHeroMaterial = hero;
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( hero->plist );
	pHero = Sprite::createWithSpriteFrameName( "hero" + pHeroMaterial->NameAfter + ".png" );
	pHero->setAnchorPoint( Point( 0.5 , 0 ) );
	pHero->retain( );
	//climb
	if ( pHeroMaterial->climbAnimationImageNum >= 1 )
	{
		// ����֡����
		Vector<SpriteFrame *> frames;
		for ( int i = 1; i <= pHeroMaterial->climbAnimationImageNum; i++ )
		{
			SpriteFrame *frame = SpriteFrameCache::getInstance( )->getSpriteFrameByName( String::createWithFormat( "hero_climb_%d%s.png" , i , pHeroMaterial->NameAfter.c_str( ) )->getCString( ) );
			frames.pushBack( frame );
		}
		//��������
		Animation *animation = Animation::createWithSpriteFrames( frames );
		animation->setDelayPerUnit( 0.3 );
		Animate* climbAnimate = Animate::create( animation );
		// �ظ�����
		pClimbAction = RepeatForever::create( climbAnimate );
		pClimbAction->retain( );
	}
	else
	{
		pClimbAction = NULL;
	}


	//jumpTo
	if ( pHeroMaterial->jumpAnimationImageNum >= 1 )
	{
		Vector<SpriteFrame *> frames;
		for ( int i = 1; i <= pHeroMaterial->jumpAnimationImageNum; i++ )
		{
			SpriteFrame *frame = SpriteFrameCache::getInstance( )->getSpriteFrameByName( String::createWithFormat( "hero_jump_%d%s.png" , i , pHeroMaterial->NameAfter.c_str( ) )->getCString( ) );
			frames.pushBack( frame );
		}
		Animation *animation = Animation::createWithSpriteFrames( frames );
		animation->setDelayPerUnit( 0.3 );
		Animate* jumpAnimate = Animate::create( animation );
		pJumpAction = RepeatForever::create( jumpAnimate );
		pJumpAction->retain( );
	}
	else
	{
		pJumpAction = NULL;
	}

	this->addChild( pHero );

}

// ���� X ��λ��
void ZRBHeroSprite::setHeroPositionX( float x )
{
	pHero->setPositionX( x );
}

// ���� Y ��λ��
void ZRBHeroSprite::setHeroPositionY( float y )
{
	pHero->setPositionY( y );
}

// ����λ��
void ZRBHeroSprite::setHeroPosition( Point pos )
{
	pHero->cocos2d::Node::setPosition( pos );
}

// ��ȡλ��
float ZRBHeroSprite::getHeroPositionX( )
{
	return pHero->getPositionX( );
}

float ZRBHeroSprite::getHeroPositionY( )
{
	return pHero->getPositionY( );
}

/// ��ȡ��С
Size ZRBHeroSprite::getHeroContentSize( )
{
	return pHero->getContentSize( );
}

// ���� ����
void ZRBHeroSprite::setHeroScaleX( float scaleX )
{
	pHero->setScaleX( scaleX );
}

// �����ڸ��ڵ��еĴ�С
Rect ZRBHeroSprite::getHeroBoundingBox( )
{
	return pHero->getBoundingBox( );
}

// ��Ծ����
void ZRBHeroSprite::jumpTo( Point p , float time , float timboWidth )
{
	// ֹͣ����
	if ( pClimbAction != NULL )
	{
		if ( !pClimbAction->isDone( ) )
		{
			pHero->stopAction( pClimbAction );
		}
	}
	// ִ����Ծ
	if ( pJumpAction != NULL )
	{
		pHero->runAction( pJumpAction );
	}
	// �ƶ�λ��
	MoveTo *move = MoveTo::create( time , p );
	CallFunc *func = CallFunc::create( CC_CALLBACK_0( ZRBHeroSprite::climb , this ) );
	// �����ĵ��ڵ�ǰ�����
	if ( p.x - pHero->getPositionX( )>0 )
	{
		// �Ƿ���Ҫ���ķ���
		if ( pHero->getScaleX( ) == 1 )
		{
			pHero->setScaleX( -1 );
			pHero->runAction( Sequence::create( move , func , NULL ) );
		}
		else
		{

			pHero->runAction( Sequence::create( CallFunc::create( CC_CALLBACK_0( ZRBHeroSprite::heroFaceRight , this ) ) , move , func , NULL ) );
		}
	}
	else if ( p.x - pHero->getPositionX( )<0 )
	{
		if ( pHero->getScaleX( ) == 1 )
		{
			pHero->runAction( Sequence::create( CallFunc::create( CC_CALLBACK_0( ZRBHeroSprite::heroFaceLeft , this ) ) , move , func , NULL ) );
		}
		else
		{
			pHero->setScaleX( 1 );
			pHero->runAction( Sequence::create( move , func , NULL ) );
		}
	}
	else
	{
		pHero->runAction( move );
	}
}

// ����
void ZRBHeroSprite::climb( )
{
	// ��ת
	pHero->setRotation( 0 );
	// ֹͣ��Ծ����
	if ( pJumpAction != NULL )
	{
		if ( !pJumpAction->isDone( ) )
		{
			pHero->stopAction( pJumpAction );
		}
	}
	// ִ�����ж���
	if ( pClimbAction != NULL )
	{
		pHero->runAction( pClimbAction );
	}
}

// ���鳯��
void ZRBHeroSprite::heroFaceRight( )
{
	pHero->setScaleX( -1 );
}

void ZRBHeroSprite::heroFaceLeft( )
{
	pHero->setScaleX( 1 );
}
