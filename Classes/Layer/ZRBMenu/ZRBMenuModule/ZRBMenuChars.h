
#ifndef __ZRBMenuChars_H__
#define __ZRBMenuChars_H__

#include "../../ZRBViewLayer/ZRBTableViewCell.h"
#include "../ZRBMenuBase.h"

class ZRBMenuChars : public ZRBMenuBase , public TableViewDelegate , public TableViewDataSource
{
private:

	CC_SYNTHESIZE( int , _nameLen , NameLen );
	CC_SYNTHESIZE_RETAIN( Label * , _leaderboard , Leaderboard );
	// Todo: add ktplay
	//static void leaderboardCallback( bool isSuccess , const char *leaderboardId ,
	//								 KTLeaderboardPaginatorC *leaderboard , KTErrorC *error );
private:
	//���� charts ������С
	Size size_charts;
	///  ��ʼ�ɼ�tableViewCell ����
	int pCellNum;

	// ��� TableView
	CC_SYNTHESIZE_RETAIN( TableView * , pTableView , tableView );

	// ���� ��ǰ���� label
	CC_SYNTHESIZE_RETAIN( Label * , _curRank , CurRank );

	// ���� ��ǰ�ɼ� label
	CC_SYNTHESIZE_RETAIN( Label * , _curScore , CurScore );

	// ���� _backboard ���� menubase�еĵ��ͼ
	CC_SYNTHESIZE_RETAIN( Scale9Sprite * , _backboard , Backboard );

public:

	virtual bool init( );
	virtual void scrollViewDidScroll( ScrollView * View ) { };
	virtual void scrollViewDidZoom( ScrollView* view ) { };
	virtual void tableCellTouched( TableView* table , TableViewCell* cell ) { };
	virtual Size tableCellSizeForIndex( TableView *table , ssize_t idx );
	virtual TableViewCell* tableCellAtIndex( TableView *table , ssize_t idx );
	virtual ssize_t numberOfCellsInTableView( TableView *table );


	// ���ø�����ť��Ӧ�����˵�
	void setCharts( );

	void setRanking( Ref * ref );

	void call_back( );

	void call_clear( );
	CREATE_FUNC( ZRBMenuChars );
};



#endif