
#ifndef __ZRBMessageLayer_H__
#define __ZRBMessageLayer_H__

#include "../ZRBMenu/ZRBMenuBase.h"

class ZRBMessageLayer : public ZRBMenuBase
{
private:

	CC_SYNTHESIZE_RETAIN( Label * , messageLabel , MessageLabel );
	CC_SYNTHESIZE_RETAIN( Menu * , menu , Menu );
	CC_SYNTHESIZE( float , width , Width );

public:
	virtual bool init( );

	void callback( );

	/**
	*  设置消息
	*
	*  @param mes 消息内容, 消息过长时在适当位置插入 '\n'
	*/
	void setMessageLabel( std::string mes );

	void setMessageLabel( std::string mes , std::string item , const std::function<void( )> &func );

	CREATE_FUNC( ZRBMessageLayer );
};


#endif
