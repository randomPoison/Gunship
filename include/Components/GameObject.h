#pragma once

class GameObject final : public ComponentLocator
{
public:
	GameObject( Scene* scene = nullptr, Ogre::SceneNode* node = nullptr, component_id id = 0, size_t index = 0 );

	Camera AddCamera();
	void AddMesh( const char* name, const char* mesh );
	Behavior AddBehavior( BehaviorFunction behavior );
	Collider AddCollider( float radius );
	void AddChild( GameObject& gameObject );

	void LookAt( float x, float y, float z );
	void LookAt( GameObject& target );
	void Translate( float x, float y, float z );
	void Translate( Ogre::Vector3 translation );
	void SetPosition( float x, float y, float z );
	void SetPosition( Ogre::Vector3 pos );
	void SetScale( float x, float y, float z );

	void Destroy() override;

	Ogre::Vector3 Position();
	std::vector<Collider> Collisions();
	size_t LastIndex() const;

private:
	Ogre::SceneNode* node;
};
