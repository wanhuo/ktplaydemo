
#ifndef __ZRBPageView_H__
#define __ZRBPageView_H__

#include "ZRBHomeLayer.h"

#include "../ZRBGame/ZRBGameLayer/ZRBGameLayer.h"
#include "../ZRBViewLayer/ZRB_PageView.h"
#include "../ZRBMenu/ZRBMenu.h"

USING_NS_CC;

class ZRBMenu;

/**
*  Pageview
*/

class ZRBPageView : public Layer
{
private:
	// 主题是否解锁
	bool page1;
	bool page2;
	bool page3;
	bool page4;
	// TODO: 保存主题价格
	const std::vector<int>PagePrice;

	// 添加监听
	void pageEventListener( Ref* ref , ui::PageView::EventType type );
	// Add menu in pageview
	ZRBMenu * pMenu;

	//弹窗大小
	cocos2d::Size size;
	// 背板
	Scale9Sprite * backGrond;
	// 游戏层
	ZRBGameLayer * gameLayer;
	// 透明遮挡层
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

	// 添加弹窗
	void popup( LayerColor * layer , int idx );

	// 购买金币
	void callBuyGold( );

	// 购买
	void callBuy( LayerColor * layer , int idx );
	// 开始游戏
	void gameBegain( Ref * sender );
	// 更新金币显示
	void updataGold( Ref * sender );
	// 设置透明度
	void setOpacityLayer( float p );
	// Set schedule callback function
	void schedulecallback( float dt );

	CREATE_FUNC( ZRBPageView );

};


#endif