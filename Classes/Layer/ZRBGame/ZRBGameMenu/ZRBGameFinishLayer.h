

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
	// Todo: ��ת�ĳ��� void setSceneManager( ZRBSceneManager _manager );
	// ���óɼ��ͽ��
	void setInfo( int _distance , int _glod );
private:

	void initLayer( );

	void rankingClick( Ref *ref );
	void restartClick( Ref *ref );
	void homeClick( Ref *ref );

	std::vector<float>addition;
	//todo : ��ת����
	// ZRBSceneManager pManager;
	/// ���� �ɼ�
	Label *pDistanceLabel;
	Label *pHeighScore;

	/// �������
	Label *pBaseGoldNumLabel;
	/// ���ｱ��
	Label *pRoleGoldNumLabel;
	/// ȫ�����
	Label *pSummaryGoldNumLabel;
	Label *pNoLabel;
};


#endif