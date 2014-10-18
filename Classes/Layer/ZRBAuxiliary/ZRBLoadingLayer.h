
#ifndef __ZRBLoadingLayer_H__
#define __ZRBLoadingLayer_H__

#include "cocos2d.h"
#include "Utilities/ZRBConfig.h"

USING_NS_CC;

class ZRBLoadingLayer : public Layer
{
public:
	/**
	旋转方向
	*/
	enum DirectionOfRotation
	{
		Clockwise ,
		CounterClockwise
	};

	//    CC_SYNTHESIZE(float, _liveTime, LiveTime);
	//    CC_SYNTHESIZE(float, _radius, Radius);
	//    CC_SYNTHESIZE(float, _cycle, Cycle);
	//    CC_SYNTHESIZE(DirectionOfRotation, _rotation, Rotation);

public:

	virtual bool init( );

	CREATE_FUNC( ZRBLoadingLayer );

	/**
	*  设置载入页面
	*
	*  @param radius    粒子半径
	*  @param cycle     周期
	*  @param livetime  粒子生命周期
	*  @param Direction 旋转方向
	*/
	void setLoading( float radius , float cycle = 1 , float livetime = 1 , DirectionOfRotation Direction = Clockwise );

	/**
	*  产生粒子
	*
	*  @param time 粒子生存时间
	*
	*  @return 产生的粒子
	*/
	ParticleSystem * particleInit( float time = 1 );

	/**
	*  返回圆形移动路径, 由下边缘开始
	*
	*  @param radius    圆的半径
	*  @param time      转一圈所需要时间
	*  @param Direction 旋转方向 默认顺时针
	*
	*  @return 循环旋转动作
	*/
	Sequence * bezierCircle( float radius , float time = 2 , DirectionOfRotation Direction = Clockwise );

};


#endif
