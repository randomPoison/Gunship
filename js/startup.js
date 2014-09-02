Gunship.GameObject.prototype.gunship = Gunship;

Gunship.behaviors = [];

Gunship.AddBehavior = function( behavior )
{
	Gunship.behaviors.push( behavior );
};

Gunship.Update = function( delta )
{
	for ( var i = 0; i < Gunship.behaviors.length; i++ )
	{
		Gunship.behaviors[i]( delta );
	}
};

// add convenience methods
Gunship.GameObject.prototype.AddBehavior = Gunship.AddBehavior;