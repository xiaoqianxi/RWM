#include "JointFactory.h"


JointFactory::JointFactory(void)
{
}


JointFactory::~JointFactory(void)
{
}

void JointFactory::init()
{
	

}

float JointFactory::radian_to_degree(double radians)
{
	double Pi = 3.14159265;
    float degrees = (radians * 180) / Pi;
    return degrees;
}

float JointFactory::degree_to_radian(double degrees)
{
	double Pi = 3.14159265;
    float radians = (degrees * Pi)/ 180.0; 
    return radians;
}

void JointFactory::CreateWeldJoint(b2World *world, b2Body* body1,  b2Body* body2)
{
	
	b2Vec2 anchor(body1->GetPosition().x,body2->GetPosition().y); 
	b2WeldJointDef* weldJointDef = new b2WeldJointDef(); 
	weldJointDef->Initialize(body1,body2,anchor); 
	weldJointDef->frequencyHz = 1; 
	
    m_weldJoint = (b2WeldJoint*)world->CreateJoint(weldJointDef); 
}


void JointFactory::CreatePrismaticJoint(b2World *world, b2Body* body1,  b2Body* body2, bool enableLimit, float lower, float upper,
										b2Vec2 anchor, b2Vec2 axis)
{
	b2PrismaticJointDef* prismaticJointDef;
	prismaticJointDef->Initialize(body1, body2, anchor, axis); // set up anchor point and axis

    prismaticJointDef->enableLimit = enableLimit;
    prismaticJointDef->lowerTranslation = lower;
    prismaticJointDef->upperTranslation = upper;
	

	m_prismaticJoint = (b2PrismaticJoint*)world->CreateJoint( prismaticJointDef );

}

void JointFactory::CreateRevoluteJoint(b2World *world, b2Body* body1,  b2Body* body2, b2Vec2 anchorA, b2Vec2 anchorB,
									   bool enableLimit, float lowerDegrees, float upperDegrees,
									   bool enableMotor, float maxTorque, float motorSpeed)
{
	b2RevoluteJointDef* revoluteJointDef;
	revoluteJointDef->bodyA = body1;
	revoluteJointDef->bodyB = body2;
	revoluteJointDef->collideConnected = false;

	revoluteJointDef->localAnchorA.Set(anchorA.x, anchorA.y);
    revoluteJointDef->localAnchorB.Set(anchorB.x, anchorB.y);
	revoluteJointDef->referenceAngle = 0;

	//Setup angular move limit
	revoluteJointDef->enableLimit = enableLimit;
	revoluteJointDef->lowerAngle = degree_to_radian(lowerDegrees);//limite for the angular movement
    revoluteJointDef->upperAngle = degree_to_radian(upperDegrees);

	//apply torque or angular impulse to rotate them if needed
	revoluteJointDef->enableMotor = enableMotor;
    revoluteJointDef->maxMotorTorque = 5;
    revoluteJointDef->motorSpeed = degree_to_radian(motorSpeed); //angular speed per second

	m_revoluteJoint = (b2RevoluteJoint*)world->CreateJoint( revoluteJointDef );


}

void JointFactory::CreateRopeJoint(b2World *world, b2Body* body1,  b2Body* body2)
{
}

