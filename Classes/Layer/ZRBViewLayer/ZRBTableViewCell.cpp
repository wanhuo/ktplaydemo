
#include "ZRBTableViewCell.h"

// ��Ա��������ʼֵ
ZRBTableViewCell::ZRBTableViewCell( )
{
	_partFirst = 0;
	_partSecond = 0;
	_partThree = 0;
	_partFour = 0;

	_foutRanking = { };
	_foutName = { };
	_foutScorer = { };

	_ranking = nullptr;
	_pic = nullptr;
	_name = nullptr;
	_scorer = nullptr;
}

/**
*  �ͷ���Դ
*/
ZRBTableViewCell::~ZRBTableViewCell( )
{
}


// ��ʼ����Ա
bool ZRBTableViewCell::init( )
{
	if ( !TableViewCell::init( ) )
	{
		return false;
	}

	setFoutRanking( );
	setFoutName( );
	setFoutScorer( );

	setpartFirst( 1 );
	setpartSecond( 1 );
	setpartThree( 2 );
	setpartFour( 1 );

	_ranking->Label::create( );
	_pic->Sprite::create( );
	_name->Label::create( );
	_scorer->Label::create( );

	// �����ԴͼƬ���ڴ�
	cocos2d::SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "homeMenu.plist" , "homeMenu.png" );

	//�����ָ��� ����ê��Ϊ�±�Ե����
	line = cocos2d::Sprite::createWithSpriteFrameName( "line.png" );
	line->setAnchorPoint( cocos2d::Vec2( 0.5 , 0 ) );
	this->addChild( line , 10 );

	// ��������
	bg_layer = cocos2d::LayerColor::create( cocos2d::Color4B( 255 , 255 , 255 , 255 ) , 0 , 0 );
	this->addChild( bg_layer );

	return true;
}


// ������������� foutInfo
void ZRBTableViewCell::setFoutRanking( int x , std::string fout , cocos2d::Color3B color )
{
	_foutRanking.foutSize = x;
	_foutRanking.fout = fout;
	_foutRanking.foutColor = color;
}

// ���������������� foutInfo
void ZRBTableViewCell::setFoutName( int x , std::string fout , cocos2d::Color3B color )
{
	_foutName.foutSize = x;
	_foutName.fout = fout;
	_foutName.foutColor = color;
}

// ���óɼ������ foutInfo
void ZRBTableViewCell::setFoutScorer( int x , std::string fout , cocos2d::Color3B color )
{
	_foutScorer.foutSize = x;
	_foutScorer.fout = fout;
	_foutScorer.foutColor = color;
}


// �������� label
void ZRBTableViewCell::setRanking( )
{

	// ��ȡλ��
	auto pos = cocos2d::Vec2( getSize( ).height * getpartFirst( ) / 2 , getSize( ).height / 2 );

	if ( !_ranking )
	{
		// ���� _ranking label
		_ranking = cocos2d::Label::createWithTTF( "" , _foutRanking.fout , _foutRanking.foutSize );

		//����ê��  ����
		_ranking->setAnchorPoint( cocos2d::Vec2( 0.5 , 0.5 ) );
		// ����λ��
		_ranking->setPosition( pos );
		// ������ɫ
		_ranking->setColor( _foutRanking.foutColor );
		// ���� Tag
		_ranking->setTag( frist );

	}

}

// ����ͷ�� sprite
void ZRBTableViewCell::setPic( )
{
	// ��ȡλ��
	auto pos = cocos2d::Vec2( getSize( ).height * ( getpartFirst( ) + getpartSecond( ) / 2 ) , getSize( ).height / 2 );

	if ( !_pic )
	{

		// ���� _pic spiter
		_pic = cocos2d::Sprite::create( );

		// ����ê��  ����
		_pic->setAnchorPoint( cocos2d::Vec2( 0.5 , 0.5 ) );
		// ����λ��
		_pic->setPosition( pos );
		// ���� Tag
		_pic->setTag( scound );
	}


}

// �������� label
void ZRBTableViewCell::setName( )
{
	// ��ȡλ��
	auto pos = cocos2d::Vec2( getSize( ).height * ( getpartFirst( ) + getpartSecond( ) ) , getSize( ).height / 2 );

	if ( !_name )
	{
		// ���� _name label
		_name = cocos2d::Label::createWithTTF( "" , _foutName.fout , _foutName.foutSize );

		//����ê��  ����� ˮƽ����
		_name->setAnchorPoint( cocos2d::Vec2( 0 , 0.5 ) );
		// ����λ��
		_name->setPosition( pos );
		// ������ɫ
		_name->setColor( _foutName.foutColor );
		// ���� Tag
		_name->setTag( three );
	}

}

// ���óɼ� label
void ZRBTableViewCell::setScorer( )
{

	// ��ȡλ��
	auto pos = cocos2d::Vec2( getSize( ).height * ( getpartFirst( ) + getpartSecond( ) + getpartThree( ) ) , getSize( ).height / 2 );

	if ( !_scorer )
	{
		// ���� _scorer label
		_scorer = cocos2d::Label::createWithTTF( "" , _foutScorer.fout , _foutScorer.foutSize );

		//����ê��  ����� ��ֱ����
		_scorer->setAnchorPoint( cocos2d::Vec2( 0 , 0.5 ) );
		// ����λ��
		_scorer->setPosition( pos );
		// ������ɫ
		_scorer->setColor( _foutScorer.foutColor );
		// ���� Tag
		_scorer->setTag( four );
	}
}

// ���ñ�����ɫ
void ZRBTableViewCell::setBackgroundColor( cocos2d::Color3B color )
{
	bg_layer->setColor( color );
}


/**
*  ����ʱ����
*  ���� ZRBTableViewCell �и��ӽڵ������
*  ��һ�μ���ʱ��ӵ� ZRBTableViewCell ��
*/
void ZRBTableViewCell::onEnter( )
{
	Node::onEnter( );

	// ���÷ָ����� ZRBTableViewCell �·���Ե
	line->setPosition( getSize( ).width / 2 , 0 );

	//  ZRBTableViewCell �������ô�С
	bg_layer->setContentSize( getSize( ) );

	//���� ���ӽڵ������
	setRanking( );
	setPic( );
	setName( );
	setScorer( );

	// �ж�  ZRBTableViewCell ���Ƿ�������ӽڵ�,    û�������
	if ( getRanking( ) && !this->getChildByTag( frist ) )
	{
		this->addChild( getRanking( ) );
	}

	if ( getPic( ) && !this->getChildByTag( scound ) )
	{
		this->addChild( getPic( ) );
	}

	if ( getname( ) && !this->getChildByTag( three ) )
	{
		this->addChild( getname( ) );
	}

	if ( getScorer( ) && !this->getChildByTag( four ) )
	{
		this->addChild( getScorer( ) );
	}
}

void ZRBTableViewCell::onEixt( )
{
	Node::onExit( );

}