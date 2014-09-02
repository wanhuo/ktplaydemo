
#ifndef __ZRBConfig_H__
#define __ZRBConfig_H__


/**
*  Size
*/
#define ZRB_SCREEN_SIZE Director::getInstance()->getWinSize()
#define ZRB_VISIBLE_SIZE Director::getInstance()->getVisibleSize()

enum ZRBSceneManager { homeScene , gameScene , timeGameScene };

enum ZRB_DATE_KEY
{
	// �û�ѡ��
	KEY_CHECK_SOUND = 0x1001 ,
	KEY_CHECK_MUSIC ,
	KEY_CHECK_ROLE ,
	KEY_CHECK_MATERIAL ,
	KEY_CHECK_MODEL ,
	// �û���ҳɼ�
	KEY_DATA_GOLDNUM ,
	KEY_DATA_SCORE ,
	// ����ӵ��
	KEY_PROP_DEATHFLIGHT ,
	KEY_PROP_MAGNET ,
	KEY_PROP_SOAR ,
	KEY_PROP_RESURGENCE ,
	// ��ɫӵ��
	KEY_ROLE_ONE ,
	KEY_ROLE_TWO ,
	// ��������
	KEY_MATERIAL_SWEET ,
	KEY_MATERIAL_BLUESKY
};

#endif