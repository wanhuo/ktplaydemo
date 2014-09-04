

#ifndef __ZRBGameMenuLayer_H__
#define __ZRBGameMenuLayer_H__

#include "cocos-ext.h"


#include "../../ZRBAuxiliary/ZRBLoadingLayer.h"
//#include "Scene/ZRBScene.h"

#include "Utilities/ZRBLanguage/ZRBLanguage.h"
#include "Utilities/ZRBUserDate/ZRBUserDate.h"

class ZRBGameMenuLayer :public Layer
{
public:

	virtual bool init( );
	CREATE_FUNC( ZRBGameMenuLayer );
	// Todo : ��ת�ĳ���
	void setScene( ZRBSceneManager _manager );

private:

	int times;
	Label * countdown;
	void scheduleCall( float dt );

	void initObject( );
	// ������Ϸ�ص�
	void backGameItemClick( Ref *ref );
	// ���ز˵��ص�
	void backHomeItemClick( Ref *ref );
	// ���¿�ʼ��Ϸ�ص�
	void restartGameItemClick( Ref *ref );
	// ���ֿ��ػص�
	void musicItemClick( Ref *ref );
	// ��Ч���ػص�
	void soundEffectItemClick( Ref *ref );
	// �˵�
	Menu *pMenu;
	// Todo: ��ת����
	ZRBSceneManager pSceneManager;

};

#endif