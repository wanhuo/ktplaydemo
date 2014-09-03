
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

	// TODO: ����������������ʵ���Ҷһ���������
	std::vector<float>cash;
	const std::vector<int>vircash;
	std::vector<std::string> productId;
	// pageView
	ui::PageView * pageView;

	// pageView ��С
	Size size;

	int goldId;
public:

	virtual bool init( );

	// ��ҹ���ҳ��1
	Layer * goldLayer0( );

	/**
	*  ����ť�Ļص�����
	*
	*  @param x ��ȡ�����Ŀ��
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