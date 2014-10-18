
#include "ZRBUserDate.h"

static ZRBUserDate * _userdate = nullptr;

ZRBUserDate * ZRBUserDate::getInstance( )
{
	if ( !_userdate )
	{
		_userdate = new ZRBUserDate( );
	}

	return _userdate;
}


void ZRBUserDate::saveData( ZRB_DATE_KEY key , void *value )
{
	// 数据类型转换对象
	std::stringstream stream;

	// 根据 key 选择保存方式
	switch ( key )
	{
		// 直接保存
		case KEY_CHECK_MODEL:
		{
			// 转化形参
			bool * p = ( bool * ) value;
			// 保存
			UserDefault::getInstance( )->setBoolForKey( _Model , *p );
		}
			break;

		case KEY_CHECK_MUSIC:
		{
			bool * p = ( bool * ) value;
			UserDefault::getInstance( )->setBoolForKey( _Music , *p );
		}
			break;

		case KEY_CHECK_SOUND:
		{
			bool * p = ( bool * ) value;
			UserDefault::getInstance( )->setBoolForKey( _Sound , *p );
		}
			break;
			// 加密保存
		case KEY_ROLE_ONE:
		{
			bool * p = ( bool * ) value;
			if ( *p )
			{
				UserDefault::getInstance( )->setStringForKey( _RoleOne , saveData( ( unsigned char* ) _true.c_str( ) , _trueLen ) );
			}
			else
			{
				UserDefault::getInstance( )->setStringForKey( _RoleOne , saveData( ( unsigned char* ) _false.c_str( ) , _falseLen ) );
			}
		}
			break;

		case KEY_ROLE_TWO:
		{
			bool * p = ( bool * ) value;
			if ( *p )
			{
				UserDefault::getInstance( )->setStringForKey( _RoleTwo , saveData( ( unsigned char* ) _true.c_str( ) , _trueLen ) );
			}
			else
			{
				UserDefault::getInstance( )->setStringForKey( _RoleTwo , saveData( ( unsigned char* ) _false.c_str( ) , _falseLen ) );
			}
		}
			break;

		case KEY_ROLE_THREE:
		{
			bool * p = ( bool * ) value;
			if ( *p )
			{
				UserDefault::getInstance( )->setStringForKey( _RoleThree , saveData( ( unsigned char* ) _true.c_str( ) , _trueLen ) );
			}
			else
			{
				UserDefault::getInstance( )->setStringForKey( _RoleThree , saveData( ( unsigned char* ) _false.c_str( ) , _falseLen ) );
			}
		}
			break;

		case KEY_ROLE_FOUR:
		{
			bool * p = ( bool * ) value;
			if ( *p )
			{
				UserDefault::getInstance( )->setStringForKey( _RoleFour , saveData( ( unsigned char* ) _true.c_str( ) , _trueLen ) );
			}
			else
			{
				UserDefault::getInstance( )->setStringForKey( _RoleFour , saveData( ( unsigned char* ) _false.c_str( ) , _falseLen ) );
			}
		}
			break;

		case KEY_ROLE_FIVE:
		{
			bool * p = ( bool * ) value;
			if ( *p )
			{
				UserDefault::getInstance( )->setStringForKey( _RoleFive , saveData( ( unsigned char* ) _true.c_str( ) , _trueLen ) );
			}
			else
			{
				UserDefault::getInstance( )->setStringForKey( _RoleFive , saveData( ( unsigned char* ) _false.c_str( ) , _falseLen ) );
			}
		}
			break;

		case KEY_MATERIAL_SWEET:
		{
			bool * p = ( bool * ) value;
			if ( *p )
			{
				UserDefault::getInstance( )->setStringForKey( _MaterialSweet , saveData( ( unsigned char* ) _true.c_str( ) , _trueLen ) );
			}
			else
			{
				UserDefault::getInstance( )->setStringForKey( _MaterialSweet , saveData( ( unsigned char* ) _false.c_str( ) , _falseLen ) );
			}
		}
			break;

		case KEY_MATERIAL_BLUESKY:
		{
			bool * p = ( bool * ) value;
			if ( *p )
			{
				UserDefault::getInstance( )->setStringForKey( _MaterialBlueSky , saveData( ( unsigned char* ) _true.c_str( ) , _trueLen ) );
			}
			else
			{
				UserDefault::getInstance( )->setStringForKey( _MaterialBlueSky , saveData( ( unsigned char* ) _false.c_str( ) , _falseLen ) );
			}
		}
			break;

		case KEY_DATA_GOLDNUM:
		{
			int * p = ( int * ) value;
			// 转换数据为字符串
			std::string bte;
			stream << *p;
			stream >> bte;
			// 加密
			UserDefault::getInstance( )->setStringForKey( _GoldNum , saveData( ( unsigned char* ) bte.c_str( ) , bte.length( ) ) );
		}
			break;

		case KEY_DATA_SCORE:
		{
			int * p = ( int * ) value;
			std::string bte;
			stream << *p;
			stream >> bte;
			UserDefault::getInstance( )->setStringForKey( _Score , saveData( ( unsigned char* ) bte.c_str( ) , bte.length( ) ) );
		}
			break;

		case KEY_PROP_DEATHFLIGHT:
		{
			int * p = ( int * ) value;
			std::string bte;
			stream << *p;
			stream >> bte;
			UserDefault::getInstance( )->setStringForKey( _DeathFlight , saveData( ( unsigned char* ) bte.c_str( ) , bte.length( ) ) );
		}
			break;

		case KEY_PROP_MAGNET:
		{
			int * p = ( int * ) value;
			std::string bte;
			stream << *p;
			stream >> bte;
			UserDefault::getInstance( )->setStringForKey( _Magnet , saveData( ( unsigned char* ) bte.c_str( ) , bte.length( ) ) );
		}
			break;

		case KEY_PROP_RESURGENCE:
		{
			int * p = ( int * ) value;
			std::string bte;
			stream << *p;
			stream >> bte;
			UserDefault::getInstance( )->setStringForKey( _Resurgence , saveData( ( unsigned char* ) bte.c_str( ) , bte.length( ) ) );
		}
			break;

		case KEY_PROP_SOAR:
		{
			int * p = ( int * ) value;
			std::string bte;
			stream << *p;
			stream >> bte;
			UserDefault::getInstance( )->setStringForKey( _Soar , saveData( ( unsigned char* ) bte.c_str( ) , bte.length( ) ) );
		}
			break;

		case KEY_CHECK_ROLE:
		{
			int * p = ( int * ) value;
			UserDefault::getInstance( )->setIntegerForKey( _CheckRole , *p );
			//            std::string * name = (std::string *)value;
			//            UserDefault::getInstance()->setStringForKey(_CheckRole, *name);
		}
			break;

		case KEY_CHECK_MATERIAL:
		{
			int * p = ( int * ) value;
			UserDefault::getInstance( )->setIntegerForKey( _CheckMaterial , *p );
			//            std::string * name = (std::string *)value;
			//            UserDefault::getInstance()->setStringForKey(_CheckMaterial, *name);
		}

		default:
			break;
	}
	UserDefault::getInstance( )->flush( );

}


bool ZRBUserDate::getDateBool( ZRB_DATE_KEY key )
{
	bool b;
	// 通过 key 获取数据
	switch ( key )
	{
		// 直接使用
		case KEY_CHECK_MODEL:
			b = UserDefault::getInstance( )->getBoolForKey( _Model );
			break;

		case KEY_CHECK_MUSIC:
			b = UserDefault::getInstance( )->getBoolForKey( _Music , true);
			break;

		case KEY_CHECK_SOUND:
			b = UserDefault::getInstance( )->getBoolForKey( _Sound , true);
			break;

			// 解密后使用
		case KEY_ROLE_ONE:
		{
			if ( _true == parseData( UserDefault::getInstance( )->getStringForKey( _RoleOne ) ) )
			{
				b = true;
			}
			else
			{
				b = false;
			}
		}
			break;

		case KEY_ROLE_TWO:
		{
			if ( _true == parseData( UserDefault::getInstance( )->getStringForKey( _RoleTwo ) ) )
			{
				b = true;
			}
			else
			{
				b = false;
			}
		}
			break;

		case KEY_ROLE_THREE:
		{
			if ( _true == parseData( UserDefault::getInstance( )->getStringForKey( _RoleThree ) ) )
			{
				b = true;
			}
			else
			{
				b = false;
			}
		}
			break;
		case KEY_ROLE_FOUR:
		{
			if ( _true == parseData( UserDefault::getInstance( )->getStringForKey( _RoleFour ) ) )
			{
				b = true;
			}
			else
			{
				b = false;
			}
		}
			break;
		case KEY_ROLE_FIVE:
		{
			if ( _true == parseData( UserDefault::getInstance( )->getStringForKey( _RoleFive ) ) )
			{
				b = true;
			}
			else
			{
				b = false;
			}
		}
			break;

		case KEY_MATERIAL_SWEET:
		{
			if ( _true == parseData( UserDefault::getInstance( )->getStringForKey( _MaterialSweet ) ) )
			{
				b = true;
			}
			else
			{
				b = false;
			}
		}
			break;

		case KEY_MATERIAL_BLUESKY:
		{
			if ( _true == parseData( UserDefault::getInstance( )->getStringForKey( _MaterialBlueSky ) ) )
			{
				b = true;
			}
			else
			{
				b = false;
			}
		}
			break;

		default:
			break;
	}

	return b;
}


int ZRBUserDate::getDateInt( ZRB_DATE_KEY key )
{
	std::stringstream stream;

	int date = 0;
	std::string str;
	// 解密
	switch ( key )
	{
		case KEY_DATA_GOLDNUM:
		{
			// 初始金币 1000 “MTAwMA==” 解密后为 1000
			str = parseData( UserDefault::getInstance( )->getStringForKey( _GoldNum , "MTAwMA==") );
			stream << str;
			stream >> date;
		}
			break;

		case KEY_DATA_SCORE:
		{
			str = parseData( UserDefault::getInstance( )->getStringForKey( _Score ) );
			stream << str;
			stream >> date;
		}
			break;

		case KEY_PROP_DEATHFLIGHT:
		{
			str = parseData( UserDefault::getInstance( )->getStringForKey( _DeathFlight ) );
			stream << str;
			stream >> date;
		}
			break;

		case KEY_PROP_MAGNET:
		{
			str = parseData( UserDefault::getInstance( )->getStringForKey( _Magnet ) );
			stream << str;
			stream >> date;
		}
			break;

		case KEY_PROP_RESURGENCE:
		{
			str = parseData( UserDefault::getInstance( )->getStringForKey( _Resurgence ) );
			stream << str;
			stream >> date;
		}
			break;

		case KEY_PROP_SOAR:
		{
			str = parseData( UserDefault::getInstance( )->getStringForKey( _Soar ) );
			stream << str;
			stream >> date;
		}
			break;

		case KEY_CHECK_MATERIAL:
			date = UserDefault::getInstance( )->getIntegerForKey( _CheckMaterial );
			break;

		case KEY_CHECK_ROLE:
			date = UserDefault::getInstance( )->getIntegerForKey( _CheckRole );
			break;

		default:
			break;
	}
	return date;
}

/*
std::string UserDate::getDateString(ZRB_DATE_KEY key)
{
    std::string name;
    // 取数据
    switch (key)
    {
        case KEY_CHECK_ROLE:
            name = UserDefault::getInstance()->getStringForKey(_CheckRole);
            break;
            
        case KEY_CHECK_MATERIAL:
            name = UserDefault::getInstance()->getStringForKey(_CheckMaterial);
            break;
            
        default:
            break;
    }
    
    return name;
}
*/


// 密匙
static const std::string dataChars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


std::string ZRBUserDate::saveData( unsigned char const* bytes_to_encode , unsigned long in_len )
{
	// 保存结果
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3 [ 3 ];
	unsigned char char_array_4 [ 4 ];
	while ( in_len-- )
	{
		//保存传入字符串
		char_array_3 [ i++ ] = *( bytes_to_encode++ );
		// 每三位加密一次
		if ( i == 3 )
		{
			// char_array_3[0]最后两位设 0 右移两位
			// char_array_4[0] = 00 + char_array_3[0] 前六位
			char_array_4 [ 0 ] = ( char_array_3 [ 0 ] & 0xfc ) >> 2;
			// char_array_3[0] 前六位设0 左移四位  char_array_3[1]后四位设 0 右移四位
			// char_array_4[2] = 00 + char_array_3[0] 后两位 + char_array_3[1] 前四位
			char_array_4 [ 1 ] = ( ( char_array_3 [ 0 ] & 0x03 ) << 4 ) + ( ( char_array_3 [ 1 ] & 0xf0 ) >> 4 );
			// char_array_3[1] 前四位设 0 后两位左移两位  char_array_3[2]  前两位右移六位
			// char_array_4[2] = 00 + char_array_3[1] 后四位 + char_array_3[2] 前两位
			char_array_4 [ 2 ] = ( ( char_array_3 [ 1 ] & 0x0f ) << 2 ) + ( ( char_array_3 [ 2 ] & 0xc0 ) >> 6 );
			// char_array_3[2]  前两位设0
			// char_array_4[3] = 00 + char_array_3[2]  后六位位
			char_array_4 [ 3 ] = char_array_3 [ 2 ] & 0x3f;
			for ( i = 0; ( i < 4 ); i++ )
				// 连接密文
				ret += dataChars [ char_array_4 [ i ] ];
			i = 0;
		}
	}
	// 最后剩余不足三位
	if ( i )
	{
		// 加空格补足三位
		for ( j = i; j < 3; j++ )
			char_array_3 [ j ] = '\0';
		char_array_4 [ 0 ] = ( char_array_3 [ 0 ] & 0xfc ) >> 2;
		char_array_4 [ 1 ] = ( ( char_array_3 [ 0 ] & 0x03 ) << 4 ) + ( ( char_array_3 [ 1 ] & 0xf0 ) >> 4 );
		char_array_4 [ 2 ] = ( ( char_array_3 [ 1 ] & 0x0f ) << 2 ) + ( ( char_array_3 [ 2 ] & 0xc0 ) >> 6 );
		char_array_4 [ 3 ] = char_array_3 [ 2 ] & 0x3f;
		for ( j = 0; ( j < i + 1 ); j++ )
			ret += dataChars [ char_array_4 [ j ] ];
		// 密文后加上与补充空格数量相等的 =
		while ( ( i++ < 3 ) )
			ret += '=';
	}
	return ret;
}

std::string ZRBUserDate::parseData( std::string const& encoded_string )
{
	// 密文长度
	auto in_len = encoded_string.size( );
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4 [ 4 ] , char_array_3 [ 3 ];
	// 保存解密
	std::string ret;
	while ( in_len && ( encoded_string [ in_ ] != '=' ) && baseData( encoded_string [ in_ ] ) )
	{
		// 提取密文
		char_array_4 [ i++ ] = encoded_string [ in_ ];
		in_++;
		// 每四个密文解密一次
		if ( i == 4 )
		{
			// 转换
			for ( i = 0; i < 4; i++ )
				char_array_4 [ i ] = dataChars.find( char_array_4 [ i ] );
			// char_array_3[0] = char_array_4[0] 后六位 + char_array_4[1] 五六位
			char_array_3 [ 0 ] = ( char_array_4 [ 0 ] << 2 ) + ( ( char_array_4 [ 1 ] & 0x30 ) >> 4 );
			// char_array_3[1] = char_array_4[1] 后四位 + char_array_4[2] 中间四位
			char_array_3 [ 1 ] = ( ( char_array_4 [ 1 ] & 0xf ) << 4 ) + ( ( char_array_4 [ 2 ] & 0x3c ) >> 2 );
			// char_array_3[2] = char_array_4[2] + char_array_4[3] 后六位
			char_array_3 [ 2 ] = ( ( char_array_4 [ 2 ] & 0x3 ) << 6 ) + char_array_4 [ 3 ];
			// 连接明文
			for ( i = 0; ( i < 3 ); i++ )
				ret += char_array_3 [ i ];
			i = 0;
		}
	}
	// 密文
	if ( i )
	{
		// 补 0
		for ( j = i; j < 4; j++ )
			char_array_4 [ j ] = 0;
		for ( j = 0; j < 4; j++ )
			char_array_4 [ j ] = dataChars.find( char_array_4 [ j ] );
		char_array_3 [ 0 ] = ( char_array_4 [ 0 ] << 2 ) + ( ( char_array_4 [ 1 ] & 0x30 ) >> 4 );
		char_array_3 [ 1 ] = ( ( char_array_4 [ 1 ] & 0xf ) << 4 ) + ( ( char_array_4 [ 2 ] & 0x3c ) >> 2 );
		char_array_3 [ 2 ] = ( ( char_array_4 [ 2 ] & 0x3 ) << 6 ) + char_array_4 [ 3 ];
		for ( j = 0; ( j < i - 1 ); j++ )
			ret += char_array_3 [ j ];
	}
	return ret;
}

