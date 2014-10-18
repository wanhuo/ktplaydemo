


#include "ZRBHeroSprite.h"

#define DEFAULT_CAPACITY 29

ZRBHeroSprite* ZRBHeroSprite::create( sHero* hero )
{
	ZRBHeroSprite *batchNode = new ZRBHeroSprite;
    batchNode->initWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey( hero->png ), DEFAULT_CAPACITY);
//	batchNode->initWithFile( hero->png , DEFAULT_CAPACITY );
	batchNode->autorelease( );
	batchNode->initThis( hero );
	return batchNode;
}


// 创建 精灵 和 动画
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
		// 动作帧序列
		Vector<SpriteFrame *> frames;
		for ( int i = 0; i < pHeroMaterial->climbAnimationImageNum; i++ )
		{
			SpriteFrame *frame = SpriteFrameCache::getInstance( )->getSpriteFrameByName( String::createWithFormat( "hero_climb_%d%s.png" , i , pHeroMaterial->NameAfter.c_str( ) )->getCString( ) );
			frames.pushBack( frame );
		}
		//创建动作
		Animation *animation = Animation::createWithSpriteFrames( frames );
		animation->setDelayPerUnit( 0.08 );
		Animate* climbAnimate = Animate::create( animation );
		// 重复播放
		pClimbAction = RepeatForever::create( climbAnimate );
		pClimbAction->retain( );
	}
	else
	{
		pClimbAction = NULL;
	}


	//jumpTo
	if ( pHeroMaterial->jumpAnimationImageNum > 0 )
	{
		Vector<SpriteFrame *> frames;
		for ( int i = 0; i < pHeroMaterial->jumpAnimationImageNum; i++ )
		{
			SpriteFrame *frame = SpriteFrameCache::getInstance( )->getSpriteFrameByName( String::createWithFormat( "hero_jump_%d%s.png" , i , pHeroMaterial->NameAfter.c_str( ) )->getCString( ) );
			frames.pushBack( frame );
		}
		Animation *animation = Animation::createWithSpriteFrames( frames );
		animation->setDelayPerUnit( 0.1 );
		Animate* jumpAnimate = Animate::create( animation );
		pJumpAction = RepeatForever::create( jumpAnimate );
		pJumpAction->retain( );
	}
	else
	{
		pJumpAction = NULL;
	}

	// die
	if ( pHeroMaterial->jumpAnimationImageNum > 0 )
	{
		Vector<SpriteFrame *> frames;
		for ( int i = 0; i < pHeroMaterial->jumpAnimationImageNum; i++ )
		{
			SpriteFrame *frame = SpriteFrameCache::getInstance( )->getSpriteFrameByName( String::createWithFormat( "hero_jump_%d%s.png" , i , pHeroMaterial->NameAfter.c_str( ) )->getCString( ) );
			frames.pushBack( frame );
		}
		Animation *animation = Animation::createWithSpriteFrames( frames );
		animation->setDelayPerUnit( 0.4 / pHeroMaterial->dieAnimationImageNum );
		Animate* jumpAnimate = Animate::create( animation );
		pDieAction = RepeatForever::create( jumpAnimate );
		pDieAction->retain( );
	}
	else
	{
		pDieAction = NULL;
	}

	this->addChild( pHero );

}

// 设置 X 轴位置
void ZRBHeroSprite::setHeroPositionX( float x )
{
	pHero->setPositionX( x );
}

// 设置 Y 轴位置
void ZRBHeroSprite::setHeroPositionY( float y )
{
	pHero->setPositionY( y );
}

// 设置位置
void ZRBHeroSprite::setHeroPosition( Point pos )
{
	pHero->cocos2d::Node::setPosition( pos );
}

// 获取位置
float ZRBHeroSprite::getHeroPositionX( )
{
	return pHero->getPositionX( );
}

float ZRBHeroSprite::getHeroPositionY( )
{
	return pHero->getPositionY( );
}

/// 获取大小
Size ZRBHeroSprite::getHeroContentSize( )
{
	return pHero->getContentSize( );
}

// 设置 方向
void ZRBHeroSprite::setHeroScaleX( float scaleX )
{
	pHero->setScaleX( scaleX );
}

// 返回在父节点中的大小
Rect ZRBHeroSprite::getHeroBoundingBox( )
{
	return pHero->getBoundingBox( );
}

// 跳跃动作
void ZRBHeroSprite::jumpTo( Point p , float time , float timboWidth )
{
	// 停止爬行
	if ( pClimbAction != NULL )
	{
		if ( !pClimbAction->isDone( ) )
		{
			pHero->stopAction( pClimbAction );
		}
	}
	if ( timboWidth == 0 )
	{
		if ( pDieAction != nullptr )
		{
			pHero->runAction( pDieAction );
		}
	}
	else
	{
		// 执行跳跃
		if ( pJumpAction != NULL )
		{
			pHero->runAction( pJumpAction );
		}
	}
	// 移动位置
	MoveTo *move = MoveTo::create( time , p );
	CallFunc *func = CallFunc::create( CC_CALLBACK_0( ZRBHeroSprite::climb , this ) );
	// 跳到的点在当前点左侧
	if ( p.x - pHero->getPositionX( )>0 )
	{
		// 是否需要更改方向
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

// 爬行
void ZRBHeroSprite::climb( )
{
	// 旋转
	pHero->setRotation( 0 );
	// 停止跳跃动作
	if ( pJumpAction != NULL )
	{
		if ( !pJumpAction->isDone( ) )
		{
			pHero->stopAction( pJumpAction );
		}
	}
	// 执行爬行动作
	if ( pClimbAction != NULL )
	{
		pHero->runAction( pClimbAction );
	}
}

// 精灵朝向
void ZRBHeroSprite::heroFaceRight( )
{
	pHero->setScaleX( -1 );
}

void ZRBHeroSprite::heroFaceLeft( )
{
	pHero->setScaleX( 1 );
}
