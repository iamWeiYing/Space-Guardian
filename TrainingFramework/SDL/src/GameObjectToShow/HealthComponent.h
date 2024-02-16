#pragma once

class Health {
protected:
	float maxHealth = 30.0f;
	float currentHealth = 30.0f;
public:
	Health() {
		currentHealth = maxHealth;
	}
	virtual void TakeDamage(float damage) = 0;
	virtual void Die() = 0;
};