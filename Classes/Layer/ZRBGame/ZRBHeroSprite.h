

#ifndef __ZRBHeroSprite_H__
#define __ZRBHeroSprite_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Utilities/ZRBTheme/ZRBTheme.h"

class ZRBHeroSprite : public SpriteBatchNode
{
public:

	static ZRBHeroSprite* create( sHero* hero );
	// 跳跃
	void jumpTo( Vec2 p , float time , float timboWidth );
	// 爬行
	void climb( );
	// 创建精灵 动作
	void initThis( sHero* hero );

	//hero
	void setHeroPositionX( float x );
	void setHeroPositionY( float y );
	float getHeroPositionX( );
	/// return pHero->getPositionY();
	float getHeroPositionY( );
	cocos2d::Size getHeroContentSize( );
	void setHeroScaleX( float scaleX );
	void setHeroPosition( Vec2 pos );
	cocos2d::Rect getHeroBoundingBox( );
private:
	// 设置方向
	void heroFaceRight( );
	void heroFaceLeft( );
	sHero* pHeroMaterial;
	Sprite *pHero;
	// 动作
	Action *pClimbAction;
	Action *pJumpAction;
	Action * pDieAction;
};


#endif
