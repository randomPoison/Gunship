'use strict';

Gunship.GameObject.prototype.gunship = Gunship;

Gunship.behaviors = [];

Gunship.keyDownEvents = {};
Gunship.keyUpEvents = {};
Gunship.keyPressedEvents = {};
Gunship.keyReleasedEvents = {};

Gunship.AddBehavior = function( gameObject, func )
{
	Gunship.behaviors.push( function( delta ) {
		func.call( gameObject, delta );
	} );
};

Gunship.Update = function( delta )
{
	for ( var i = 0; i < Gunship.behaviors.length; i++ )
	{
		Gunship.behaviors[i]( delta );
	}
};

// add convenience methods
Gunship.GameObject.prototype.AddBehavior = function( func )
{
	Gunship.AddBehavior( this, func );
};

Gunship.OnKeyDown = function( key, func )
{
	if ( !keyDownEvents[key] )
	{
		keyDownEvents[key] = []
	}
	keyDownEvents[key].push( func );
};

Gunship.OnKeyPressed = function( key, func )
{
	if ( !keyPressedEvents[key] )
	{
		keyPressedEvents[key] = [];
	}
	keyPressedEvents[key].push( key, func );
};