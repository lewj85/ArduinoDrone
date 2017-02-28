// general layout of balanced flight program
// by Jesse Lew

int main()
{
	// parallel float arrays hold pitch, roll, yaw, altitude in that order
	float oldValues[4];
	float newValues[4];
	bool balanced = false;     // initialize to false

	while(1) 			// constant loop
	{
		// timer with millis()
		if(interval we set)
		{
			getNewValues(oldValues, newValues);

			compareValues(oldValues, newValues);

			if(balanced == false)
			{
				balanceMath(newValues);
				compensate();
			}
		}
	}

	return 0;
}



void getNewValues(float* oldValues[], float* newValues[])
{
	// first save old values
	oldValues[0] = newValues[0];
	oldValues[1] = newValues[1];
	oldValues[2] = newValues[2];
	oldValues[3] = newValues[3];

	// then get new values
	newValues[0] = pitchData;
	newValues[1] = rollData;
	newValues[2] = yawData;
	newValues[3] = altitudeData;
}


void compareValues(float* oldValues[], float* newValues[])
{
	if(oldValues[0] != newValues[0] ||
	   oldValues[1] != newValues[1] ||
	   oldValues[2] != newValues[2] ||
	   oldValues[3] != newValues[3])
	{
		balanced = false;
	}
}
