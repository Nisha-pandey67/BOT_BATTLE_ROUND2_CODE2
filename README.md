# BOT_BATTLE_ROUND2_CODE2
## To enhance the smart irrigation system as per the tasks specified, we'll make several modifications to the given Arduino code:

## Modifications Required:
1.Custom Threshold Using Potentiometer:

Connect a potentiometer to analog pin A1 to allow the user to set a custom threshold for soil moisture.
Read the potentiometer value and adjust the moisture threshold dynamically.

2.Feedback Mechanism:

Add a buzzer and an LED for feedback when watering starts and stops.
Buzzer emits a short beep and LED blinks briefly during these events.

3.Power Efficiency with Sleep Mode:

Implement a sleep mode feature to conserve power when the system is not actively checking soil moisture.
Use a button connected to digital pin 2 to manually activate the system from sleep mode.
