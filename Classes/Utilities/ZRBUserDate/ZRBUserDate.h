

#ifndef __ZRBUserDate_H__
#define __ZRBUserDate_H__


#include <sstream>
#include <string>
#include "cocos2d.h"


USING_NS_CC;


enum ZRB_DATE_KEY
{
	// 用户选择
	KEY_CHECK_SOUND = 0x1001 ,
	KEY_CHECK_MUSIC ,
	KEY_CHECK_ROLE ,
	KEY_CHECK_MATERIAL ,
	KEY_CHECK_MODEL ,
	// 用户金币成绩
	KEY_DATA_GOLDNUM ,
	KEY_DATA_SCORE ,
	// 道具拥有
	KEY_PROP_DEATHFLIGHT ,
	KEY_PROP_MAGNET ,
	KEY_PROP_SOAR ,
	KEY_PROP_RESURGENCE ,
	// 角色拥有
	KEY_ROLE_ONE ,
	KEY_ROLE_TWO ,
	KEY_ROLE_THREE,
	KEY_ROLE_FOUR,
	KEY_ROLE_FIVE,
	// 场景解锁
	KEY_MATERIAL_SWEET ,
	KEY_MATERIAL_BLUESKY
};

class ZRBUserDate
{
private:

	// 文件 Key
	const char * _Music				= "Music";
	const char * _Sound				= "Sound";
	const char * _RoleOne			= "RoleOne";
	const char * _RoleTwo			= "RoleTwo";
	const char * _RoleThree			= "RoleThree";
	const char * _RoleFour			= "RoleFour";
	const char * _RoleFive			= "RoleFive";

	const char * _GoldNum			= "GoldNum";
	const char * _Score				= "Score";
	const char * _DeathFlight		= "DeathFlight";
	const char * _Magnet			= "Magnet";
	const char * _Resurgence		= "Resurgence";
	const char * _Soar				= "Soar";
	const char * _Model				= "CheckModel";
	const char * _CheckRole			= "CheckRole";
	const char * _CheckMaterial		= "CheckMaterial";
	const char * _MaterialSweet		= "MaterialSweet";
	const char * _MaterialBlueSky	= "MaterialBlueSky";

	// 常用值
	const std::string _true = "true";
	const std::string _false = "false";
	const int _trueLen = _true.length( );
	const int _falseLen = _false.length( );

	ZRBUserDate( ) { };

public:
	//  获取对象
	static ZRBUserDate * getInstance( );

	/**
	*  保存加密数据
	*
	*  @param key   key
	*  @param value 保存值 类型: int bool std::string 指针
	*/
	void saveData( ZRB_DATE_KEY key , void * value );
	/**
	*  读取文件 bool 数据
	*
	*  @param key key
	*
	*  @return 文件中保存的值
	*/
	bool getDateBool( ZRB_DATE_KEY key );
	/**
	*  读取文件 int 数据
	*
	*  @param key key
	*
	*  @return 文件中保存的值
	*/
	int getDateInt( ZRB_DATE_KEY key );
	//    /**
	//     *  读取文件 std::string 数据
	//     *
	//     *  @param key key
	//     *
	//     *  @return 文件中保存的值
	//     */
	//    std::string getDateString(ZRB_DATE_KEY key);


	// 判断是否在 dataChars
	static inline bool baseData( unsigned char c )
	{
		return ( isalnum( c ) || ( c == '+' ) || ( c == '/' ) );
	}
	//  加密数据
	std::string saveData( unsigned char const* bytes_to_encode , unsigned long in_len );
	// 解密数据
	std::string parseData( std::string const& encoded_string );

};



#endif
