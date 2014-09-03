
#ifndef __ZRBLoadingLayer_H__
#define __ZRBLoadingLayer_H__

#include "cocos2d.h"
#include "Utilities/ZRBConfig.h"

USING_NS_CC;

class ZRBLoadingLayer : public Layer
{
public:
	/**
	��ת����
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
	*  ��������ҳ��
	*
	*  @param radius    ���Ӱ뾶
	*  @param cycle     ����
	*  @param livetime  ������������
	*  @param Direction ��ת����
	*/
	void setLoading( float radius , float cycle = 1 , float livetime = 1 , DirectionOfRotation Direction = Clockwise );

	/**
	*  ��������
	*
	*  @param time ��������ʱ��
	*
	*  @return ����������
	*/
	ParticleSystem * particleInit( float time = 1 );

	/**
	*  ����Բ���ƶ�·��, ���±�Ե��ʼ
	*
	*  @param radius    Բ�İ뾶
	*  @param time      תһȦ����Ҫʱ��
	*  @param Direction ��ת���� Ĭ��˳ʱ��
	*
	*  @return ѭ����ת����
	*/
	Sequence * bezierCircle( float radius , float time = 2 , DirectionOfRotation Direction = Clockwise );

};


#endif