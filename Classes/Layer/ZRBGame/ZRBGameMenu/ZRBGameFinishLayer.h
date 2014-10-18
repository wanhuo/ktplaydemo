

#ifndef __ZRBGameFinishLayer_H__
#define __ZRBGameFinishLayer_H__

#include "../../ZRBMenu/ZRBMenuModule/ZRBMenuChars.h"

class ZRBGameFinishLayer : public Layer
{
public:

	ZRBGameFinishLayer( );
	~ZRBGameFinishLayer( );

	virtual bool init( );
	CREATE_FUNC( ZRBGameFinishLayer );
	// Todo: 跳转的场景 void setSceneManager( ZRBSceneManager _manager );
	// 设置成绩和金币
	void setInfo( int _distance , int _glod );

	void rankingClick( Ref *ref );
	void restartClick( Ref *ref );
	void homeClick( Ref *ref );

private:

	void initLayer( );


	std::vector<float>addition;
	//todo : 跳转场景
	// ZRBSceneManager pManager;
	/// 距离 成绩
	Label *pDistanceLabel;
	Label *pHeighScore;

	/// 基础金币
	Label *pBaseGoldNumLabel;
	/// 人物奖励
	Label *pRoleGoldNumLabel;
	/// 全部金币
	Label *pSummaryGoldNumLabel;
	Label *pNoLabel;
};


#endif
