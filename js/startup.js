'use strict';

Gunship.GameObject.prototype.gunship = Gunship;

Gunship.behaviors = [];

Gunship.keyDownEvents = [];
Gunship.keyUpEvents = [];
Gunship.keyPressedEvents = [];
Gunship.keyReleasedEvents = [];

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

Gunship.UpdateInput = function( keys )
{
	keys.forEach( function( key )
	{
		var callbacks = this.keyDownEvents[key] || []; // ensure that the callback array exists
		callbacks.forEach( function( callback )
		{
			callback();
		}, this );
	}, this );
};

// add convenience methods
Gunship.GameObject.prototype.AddBehavior = function( func )
{
	Gunship.AddBehavior( this, func );
};

Gunship.OnKeyDown = function( key, func )
{
	if ( !this.keyDownEvents[key] )
	{
		this.keyDownEvents[key] = []
	}
	this.keyDownEvents[key].push( func );
};

Gunship.OnKeyPressed = function( key, func )
{
	if ( !this.keyPressedEvents[key] )
	{
		this.keyPressedEvents[key] = [];
	}
	this.keyPressedEvents[key].push( key, func );
};