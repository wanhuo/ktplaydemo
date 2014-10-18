
#ifndef __ZRBMarketGold_H__
#define __ZRBMarketGold_H__

#include "ui/UIPageView.h"

#include "Utilities/ZRBUserDate/ZRBUserDate.h"
#include "Layer/ZRBAuxiliary/ZRBLoadingLayer.h"
#include "Layer/ZRBAuxiliary/ZRBMessageLayer.h"


USING_NS_CC;

class ZRBLoadingLayer;

class BuyDelegate
{
public:
	virtual void changeLoad( bool isShow ) = 0;
	virtual void buyFild( ) = 0;
	virtual void buyFinish( ) = 0;
};


class ZRBMarketGold : public Layer , public BuyDelegate
{
	friend class ZRBLoadingLayer;
	friend class test;

public:

	ZRBMarketGold( );
	~ZRBMarketGold( );

private:

	// TODO: 添加两个容器存放现实货币兑换的虚拟金币
	std::vector<float>cash;
	const std::vector<int>vircash;
	std::vector <std::string> cashPic;
	std::vector<std::string> productId;
	// pageView
	ui::PageView * pageView;

	// pageView 大小
	cocos2d::Size size;

	int goldId;

public:

	virtual bool init( );

	// 金币购买页面1
	Layer * goldLayer0( );

	/**
	*  购买按钮的回调函数
	*
	*  @param x 获取购买的目标
	*/
	void callBack( int x );

	//    void changeLoading(bool visiable);
	bool firstMes;
	virtual void changeLoad( bool isShow );
	virtual void buyFild( );
	virtual void buyFinish( );

	CREATE_FUNC( ZRBMarketGold );
};

#endif
