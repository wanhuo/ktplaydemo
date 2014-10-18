

#ifndef __ZRBMarketRole_H__
#define __ZRBMarketRole_H__

#include "ui/UIPageView.h"
#include "Layer/ZRBAuxiliary/ZRBMessageLayer.h"
#include "Utilities/ZRBUserDate/ZRBUserDate.h"
#include "Utilities/ZRBTheme/ZRBTheme.h"


USING_NS_CC;

class ZRBMarketRole : public Layer
{

public:

	ZRBMarketRole( );
	~ZRBMarketRole( );

private:

	// 角色是否购买
	bool pBuy[6];
	// 角色价格
	std::vector<int>pPrice;
	// 角色介绍
	std::vector<std::string>strName;
	std::vector<std::string>strChar;
	//    std::vector<std::string>strIntr;
	// 角色资料
	std::vector<sHero *> hero;
	// 购买按钮
	vector<MenuItemImage *>use_buy;
	// 选择图标
	vector<Sprite *>_check;

	vector<Color3B>_color;
	Vector<Animation *>heroAnimation;
	//    enum
	//    {
	//        Name = 0,
	//        Characteristic,
	//        Pic,
	//        Introduction,
	//        Check
	//        
	//    }flag;
	// pageView
	ui::PageView * pageView;

	// 标识当前页
	Vector<LayerColor *>curPage;

	// pageView 大小
    cocos2d::Size size;

public:

	virtual bool init( );

	// 道具页面1
	void roleLayer( );
	// 设置按钮为使用
	void setButtenUse( int idx );
	// 使用回调
	void callUse( );

	// 分页监听回调
	void pageSwith( Ref* ref , ui::PageView::EventType type );

	CREATE_FUNC( ZRBMarketRole );

};

#endif
