
#ifndef __ZRBMenuChars_H__
#define __ZRBMenuChars_H__

#include "../../ZRBViewLayer/ZRBTableViewCell.h"
#include "../ZRBMenuBase.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Utilities/Android.h"
#endif


class ZRBMenuChars : public ZRBMenuBase , public TableViewDelegate , public TableViewDataSource
{
private:

	CC_SYNTHESIZE( int , _nameLen , NameLen );
	CC_SYNTHESIZE_RETAIN( Label * , _leaderboard , Leaderboard );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// Todo: add ktplay
	static void leaderboardCallback( bool isSuccess , const char *leaderboardId ,
									 KTLeaderboardPaginatorC *leaderboard , KTErrorC *error );
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

private:
	//保存 charts 弹窗大小
	cocos2d::Size size_charts;
	///  初始可见tableViewCell 数量
	int pCellNum;

	// 添加 TableView
	CC_SYNTHESIZE_RETAIN( TableView * , pTableView , tableView );

	// 创建 当前排名 label
	CC_SYNTHESIZE_RETAIN( Label * , _curRank , CurRank );

	// 创建 当前成绩 label
	CC_SYNTHESIZE_RETAIN( Label * , _curScore , CurScore );

	// 创建 _backboard 接收 menubase中的点九图
	CC_SYNTHESIZE_RETAIN( Scale9Sprite * , _backboard , Backboard );

public:

	virtual bool init( );
	virtual void scrollViewDidScroll( ScrollView * View ) { };
	virtual void scrollViewDidZoom( ScrollView* view ) { };
	virtual void tableCellTouched( TableView* table , TableViewCell* cell ) { };
	virtual cocos2d::Size tableCellSizeForIndex( TableView *table , ssize_t idx );
	virtual TableViewCell* tableCellAtIndex( TableView *table , ssize_t idx );
	virtual ssize_t numberOfCellsInTableView( TableView *table );


	// 设置各个按钮对应弹窗菜单
	void setCharts( );

	void setRanking( Ref * ref );

	void call_back( );

	void call_clear( );
	CREATE_FUNC( ZRBMenuChars );
};



#endif
