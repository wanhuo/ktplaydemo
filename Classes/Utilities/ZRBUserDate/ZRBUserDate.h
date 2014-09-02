

#ifndef __ZRBUserDate_H__
#define __ZRBUserDate_H__


#include <sstream>
#include <string>
#include "cocos2d.h"


USING_NS_CC;


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

class ZRBUserDate
{
private:

	// �ļ� Key
	const char * _Music = "Music";
	const char * _Sound = "Sound";
	const char * _RoleOne = "RoleOne";
	const char * _RoleTwo = "RoleTwo";
	const char * _GoldNum = "GoldNum";
	const char * _Score = "Score";
	const char * _DeathFlight = "DeathFlight";
	const char * _Magnet = "Magnet";
	const char * _Resurgence = "Resurgence";
	const char * _Soar = "Soar";
	const char * _Model = "CheckModel";
	const char * _CheckRole = "CheckRole";
	const char * _CheckMaterial = "CheckMaterial";
	const char * _MaterialSweet = "MaterialSweet";
	const char * _MaterialBlueSky = "MaterialBlueSky";

	// ����ֵ
	const std::string _true = "true";
	const std::string _false = "false";
	const int _trueLen = _true.length( );
	const int _falseLen = _false.length( );

	ZRBUserDate( ) { };

public:
	//  ��ȡ����
	static ZRBUserDate * getInstance( );

	/**
	*  �����������
	*
	*  @param key   key
	*  @param value ����ֵ ����: int bool std::string ָ��
	*/
	void saveData( ZRB_DATE_KEY key , void * value );
	/**
	*  ��ȡ�ļ� bool ����
	*
	*  @param key key
	*
	*  @return �ļ��б����ֵ
	*/
	bool getDateBool( ZRB_DATE_KEY key );
	/**
	*  ��ȡ�ļ� int ����
	*
	*  @param key key
	*
	*  @return �ļ��б����ֵ
	*/
	int getDateInt( ZRB_DATE_KEY key );
	//    /**
	//     *  ��ȡ�ļ� std::string ����
	//     *
	//     *  @param key key
	//     *
	//     *  @return �ļ��б����ֵ
	//     */
	//    std::string getDateString(ZRB_DATE_KEY key);


	// �ж��Ƿ��� dataChars
	static inline bool baseData( unsigned char c )
	{
		return ( isalnum( c ) || ( c == '+' ) || ( c == '/' ) );
	}
	//  ��������
	std::string saveData( unsigned char const* bytes_to_encode , unsigned long in_len );
	// ��������
	std::string parseData( std::string const& encoded_string );

};



#endif
