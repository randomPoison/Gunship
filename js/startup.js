Gunship.GameObject.prototype.gunship = Gunship;

Gunship.behaviors = [];

Gunship.GameObject.prototype.AddBehavior = function( behavior )
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