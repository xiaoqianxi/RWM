#pragma once
#include <SDL.h>
#include <Box2D\Box2D.h>
#include <string>

using namespace std;

class JointFactory
{
private:
	b2WeldJoint* m_weldJoint;
	b2PrismaticJoint* m_prismaticJoint;
	b2RevoluteJoint* m_revoluteJoint;


public:
	

	JointFactory(void);
	~JointFactory(void);

	void init();

	float radian_to_degree(double radians);

	float degree_to_radian(double degree);

	void CreateWeldJoint(b2World *world, b2Body* body1,  b2Body* body2);

	void CreatePrismaticJoint(b2World *world, b2Body* body1,  b2Body* body2 , bool enableLimit, float lower, float upper,
		                      b2Vec2 anchor, b2Vec2 axis);

	void CreateRevoluteJoint(b2World *world, b2Body* body1,  b2Body* body2, b2Vec2 anchorA, b2Vec2 anchorB,
		                     bool enableLimit, float lower, float upper,
							 bool enableMotor, float maxTorque, float motorSpeed);

	void CreateRopeJoint(b2World *world, b2Body* body1,  b2Body* body2);



};