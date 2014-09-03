
#ifndef __ZRBPageView_H__
#define __ZRBPageView_H__


#include "Layer/ZRBViewLayer/ZRB_PageView.h"
#include "Layer/ZRBMenu/ZRBMenu.h"
#include "ZRBHomeLayer.h"
//#include "ZRBGameLayer.h"

USING_NS_CC;

class ZRBMenu;

/**
*  Pageview
*/

class ZRBPageView : public Layer
{
private:
	// �����Ƿ����
	bool page1;
	bool page2;
	bool page3;
	bool page4;
	// TODO: ��������۸�
	const std::vector<int>PagePrice;

	// ��Ӽ���
	void pageEventListener( Ref* ref , ui::PageView::EventType type );
	// Add menu in pageview
	ZRBMenu * pMenu;

	//������С
	Size size;
	// ����
	Scale9Sprite * backGrond;
	// ��Ϸ��
	//ZRBGameLayer * gameLayer;
	// ͸���ڵ���
	LayerColor * opacityLayer;

public:
	ZRBPageView( );
	~ZRBPageView( );
	// Create pageview
	ZRB_PageView * pageView;

	virtual void onEnter( );

	// Save page number
	// ssize_t long
	long ssize;

	//  Init
	virtual bool init( );

	// Set pageview
	void setPageView( );

	// ��ӵ���
	void popup( LayerColor * layer , int idx );

	// ������
	void callBuyGold( );

	// ����
	void callBuy( LayerColor * layer , int idx );
	// ��ʼ��Ϸ
	void gameBegain( Ref * sender );
	// ���½����ʾ
	void updataGold( Ref * sender );
	// ����͸����
	void setOpacityLayer( float p );
	// Set schedule callback function
	void schedulecallback( float dt );

	CREATE_FUNC( ZRBPageView );

};


#endif