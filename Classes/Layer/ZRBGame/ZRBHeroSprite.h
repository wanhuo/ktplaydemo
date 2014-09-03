

#ifndef __ZRBHeroSprite_H__
#define __ZRBHeroSprite_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Utilities/ZRBTheme/ZRBTheme.h"

class ZRBHeroSprite : public SpriteBatchNode
{
public:

	static ZRBHeroSprite* create( sHero* hero );
	// ��Ծ
	void jumpTo( Point p , float time , float timboWidth );
	// ����
	void climb( );
	// �������� ����
	void initThis( sHero* hero );

	//hero
	void setHeroPositionX( float x );
	void setHeroPositionY( float y );
	float getHeroPositionX( );
	/// return pHero->getPositionY();
	float getHeroPositionY( );
	Size getHeroContentSize( );
	void setHeroScaleX( float scaleX );
	void setHeroPosition( Point pos );
	Rect getHeroBoundingBox( );
private:
	// ���÷���
	void heroFaceRight( );
	void heroFaceLeft( );
	sHero* pHeroMaterial;
	Sprite *pHero;
	// ����
	Action *pClimbAction;
	Action *pJumpAction;
};


#endif