

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

	// ��ɫ�Ƿ���
	std::vector<bool>pBuy;
	// ��ɫ�۸�
	std::vector<int>pPrice;
	// ��ɫ����
	std::vector<std::string>strName;
	std::vector<std::string>strChar;
	//    std::vector<std::string>strIntr;
	// ��ɫ����
	std::vector<sHero *> hero;
	// ����ť
	vector<MenuItemImage *>use_buy;
	// ѡ��ͼ��
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

	// ��ʶ��ǰҳ
	Vector<LayerColor *>curPage;

	// pageView ��С
	Size size;

public:

	virtual bool init( );

	// ����ҳ��1
	void roleLayer( );
	// ���ð�ťΪʹ��
	void setButtenUse( int idx );
	// ʹ�ûص�
	void callUse( );

	// ��ҳ�����ص�
	void pageSwith( Ref* ref , ui::PageView::EventType type );

	CREATE_FUNC( ZRBMarketRole );

};

#endif