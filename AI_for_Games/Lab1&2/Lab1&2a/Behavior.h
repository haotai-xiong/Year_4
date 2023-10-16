#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#define PI 3.1415926535

struct Kinematic {
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	float m_orientation;
	float m_rotation;
};

struct Steering {
	sf::Vector2f m_linear;
	float m_angular;
	float m_maxRotation = 60.0f;
	float m_maxSpeed = 1.0f;
	float m_maxAcceleration = 1.0f;
	float degree = 22.5f;
	float m_visionConeLength = 250.0f;
	float m_slowingRadius = 300.0f;
};

enum class Type {
	wander,
	seeker,
	arriveSlow,
	arriveFast,
	pursue
};

class Behavior {
public:
	void process(Type t_type, Kinematic& t_kinematic, Steering& t_steering, sf::Vector2f& t_targetPos, Kinematic& t_targetKinematic) {
		if (Type::wander == t_type) {
			wander(t_kinematic, t_steering, t_targetPos);
		}
		else if (Type::seeker == t_type) {
			seek(t_kinematic, t_steering, t_targetPos);
		}
		else if (Type::arriveSlow == t_type) {
			arriveSlow(t_kinematic, t_steering, t_targetPos);
		}
		else if (Type::arriveFast == t_type) {
			arriveFast(t_kinematic, t_steering, t_targetPos);
		}
		else if (Type::pursue == t_type) {
			pursue(t_kinematic, t_steering,t_targetKinematic, 1.0f);
		}
	}

protected:

	void wander(Kinematic& t_kinematic, Steering& t_steering, sf::Vector2f& t_pos) {
		static sf::Clock wanderClock;
		static sf::Clock seekClock;
		static float wanderAngle = rand() % 60;

		if (wanderClock.getElapsedTime().asSeconds() >= 0.2f) {
			float randomRotation = (static_cast<float>(rand()) / RAND_MAX) * 60.0f - 30.0f;
			wanderAngle += randomRotation;
			t_kinematic.m_velocity = sf::Vector2f(std::sin(wanderAngle * PI / 180.0f),
				-std::cos(wanderAngle * PI / 180.0f)) * t_steering.m_maxSpeed;

			wanderClock.restart();
		}

		if (seekClock.getElapsedTime().asSeconds() >= 5.0f) {
			getNewSteering(t_kinematic, t_steering, t_pos);
			seekClock.restart();
		}

		float desiredOrientation = std::atan2(-t_kinematic.m_velocity.y, t_kinematic.m_velocity.x) * 180.0f / PI;
		float orientationDifference = desiredOrientation - t_kinematic.m_orientation;
		if (orientationDifference > 180.0f) orientationDifference -= 180.0f;
		if (orientationDifference < -180.0f) orientationDifference += 180.0f;

		t_kinematic.m_orientation += orientationDifference * 0.001f;
	}


	void seek(Kinematic& t_kinematic, Steering& t_steering, sf::Vector2f& t_pos) {
		sf::Vector2f toTarget = t_pos - t_kinematic.m_pos;
		float distanceToTarget = std::sqrtf(toTarget.x * toTarget.x + toTarget.y * toTarget.y);
		sf::Vector2f desiredVelocity = toTarget / distanceToTarget;
		t_kinematic.m_velocity = desiredVelocity * t_steering.m_maxSpeed;

		// New steering behavior
		getNewSteering(t_kinematic, t_steering, t_pos);

		// Ensure we're not exceeding the maximum speed
		float speed = std::sqrt(t_kinematic.m_velocity.x * t_kinematic.m_velocity.x + t_kinematic.m_velocity.y * t_kinematic.m_velocity.y);
		if (speed > t_steering.m_maxSpeed) {
			t_kinematic.m_velocity /= speed; // Normalize velocity
			t_kinematic.m_velocity *= t_steering.m_maxSpeed; // Apply max speed
		}
	}

	void arriveSlow(Kinematic& t_kinematic, Steering& t_steering, sf::Vector2f& targetPos) {
		sf::Vector2f direction = targetPos - t_kinematic.m_pos;
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance < t_steering.m_slowingRadius) {
			float targetSpeed = t_steering.m_maxSpeed * (distance / t_steering.m_slowingRadius);
			t_kinematic.m_velocity = direction * (targetSpeed / distance);
		}
		else {
			t_kinematic.m_velocity = direction * (t_steering.m_maxSpeed / distance);
		}
	}

	void arriveFast(Kinematic& t_kinematic, Steering& t_steering, sf::Vector2f& targetPos) {
		sf::Vector2f direction = targetPos - t_kinematic.m_pos;
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance < t_steering.m_slowingRadius / 4.0f) {
			t_kinematic.m_velocity = sf::Vector2f(0.1f, 0.1f);
		}
		else {
			t_kinematic.m_velocity = direction * (t_steering.m_maxSpeed * 2.0f / distance);
		}
	}

	void pursue(Kinematic& t_kinematic, Steering& t_steering, Kinematic& targetKinematic, float maxTimePrediction) {
		sf::Vector2f direction = targetKinematic.m_pos - t_kinematic.m_pos;
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		float speed = std::sqrt(t_kinematic.m_velocity.x * t_kinematic.m_velocity.x + t_kinematic.m_velocity.y * t_kinematic.m_velocity.y);
		float timePrediction;
		if (speed <= distance / maxTimePrediction) {
			timePrediction = maxTimePrediction;
		}
		else {
			timePrediction = distance / speed;
		}

		// Predict the future position of the target
		sf::Vector2f futureTargetPos = targetKinematic.m_pos + targetKinematic.m_velocity * timePrediction;

		// Delegate to the seek function
		seek(t_kinematic, t_steering, futureTargetPos);
	}

	void getNewSteering(Kinematic& t_kinematic, Steering& t_steering, sf::Vector2f& t_pos) {
		t_steering.m_linear = t_pos - t_kinematic.m_pos;
		t_steering.m_linear /= sqrt(t_steering.m_linear.x * t_steering.m_linear.x
			+ t_steering.m_linear.y * t_steering.m_linear.y);
		t_steering.m_linear *= t_steering.m_maxAcceleration;
		t_steering.m_angular = 0.0f;
	}
};

#endif
// !BEHAVIOR
