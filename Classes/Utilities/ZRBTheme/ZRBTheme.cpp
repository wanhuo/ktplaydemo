
#include "ZRBTheme.h"

static sHero *gCurrentHero;
static sMaterial *gCurrrentMaterial;

sMaterial* ZRBTheme::getMaterialSummer( )
{
	vector<Color3B> _colors;
	_colors.push_back( Color3B( 84 , 145 , 105 ) );
	_colors.push_back( Color3B( 244 , 106 , 136 ) );
	_colors.push_back( Color3B( 212 , 185 , 124 ) );
	_colors.push_back( Color3B( 219 , 143 , 116 ) );
	_colors.push_back( Color3B( 87 , 154 , 183 ) );
	return new sMaterial { "summer_material.plist" , "summer_material.png" , "_summer" , 7 , false , _colors };
};

sMaterial* ZRBTheme::getMaterialSweet( )
{
	vector<Color3B> _colors;
	_colors.push_back( Color3B( 255 , 64 , 94 ) );
	_colors.push_back( Color3B( 254 , 156 , 153 ) );
	_colors.push_back( Color3B( 251 , 205 , 172 ) );
	_colors.push_back( Color3B( 200 , 199 , 168 ) );
	_colors.push_back( Color3B( 132 , 175 , 155 ) );
	return new sMaterial { "sweet_material.plist" , "sweet_material.png" , "_sweet" , 5 , false , _colors };
};

sMaterial* ZRBTheme::getMaterialBlueSky( )
{
	vector<Color3B> _colors;
	//    _colors.push_back(Color3B(178, 154, 189));
	//    _colors.push_back(Color3B( 98, 141, 164));
	//    _colors.push_back(Color3B(219, 146, 112));
	//    _colors.push_back(Color3B(122, 170, 154));
	//    _colors.push_back(Color3B(214, 212, 122));

	_colors.push_back( Color3B( 230 , 170 , 160 ) );
	_colors.push_back( Color3B( 235 , 230 , 190 ) );
	_colors.push_back( Color3B( 180 , 130 , 150 ) );
	_colors.push_back( Color3B( 115 , 190 , 205 ) );
	_colors.push_back( Color3B( 170 , 220 , 190 ) );

	return new sMaterial { "blueSky_material.plist" , "blueSky_material.png" , "_blueSky" , 1 , true , _colors };
}

sHero * ZRBTheme::getHeroGrotle( )
{
	return new sHero { "grotle_hero.plist" , "grotle_hero.png" , "_grotle" , 4 , 5 , 1 };
}


sHero * ZRBTheme::getHeroHoot( )
{
	return new sHero { "hoot_hero.plist" , "hoot_hero.png" , "_hoot" , 8 , 0 , 3 };
}

sHero * ZRBTheme::getHeroMagcargo( )
{
	return  new sHero { "magcargo_hero.plist" , "magcargo_hero.png" , "_magcargo" , 5 , 0 , 4 };
}

sHero * ZRBTheme::getHeroSpoink( )
{
	return  new sHero { "spoink_hero.plist" , "spoink_hero.png" , "_spoink" , 4 , 0 , 5 };
}

sHero * ZRBTheme::getHeroTropius( )
{
	return  new sHero { "tropius_hero.plist" , "tropius_hero.png" , "_tropius" , 6 , 0 , 2 };
}

sHero * ZRBTheme::getHeroSpinarak( )
{
	return  new sHero { "spinarak_hero.plist" , "spinarak_hero.png" , "_spinarak" , 4 , 0 , 2 };
}

void ZRBTheme::setCurrentMaterial( sMaterial *_material )
{
	gCurrrentMaterial = _material;
};

sMaterial* ZRBTheme::getCurrentMaterial( )
{
	return gCurrrentMaterial;
};

void ZRBTheme::setCurrentHero( sHero *_hero )
{
	gCurrentHero = _hero;
};

sHero* ZRBTheme::getCurrentHero( )
{
	return gCurrentHero;
};
