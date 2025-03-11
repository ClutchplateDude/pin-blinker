#include <Arduino.h>

int newPin;
int currentPin = -1;

int convertPinName(String s)
{
    if (s.startsWith("A") || s.startsWith("D"))
    {
        if (s == "A0")
            return A0;
        if (s == "A1")
            return A1;
        if (s == "A2")
            return A2;
        if (s == "A3")
            return A3;
        if (s == "A4")
            return A4;
        if (s == "A5")
            return A5;
        if (s == "A6")
            return A6;
        if (s == "A7")
            return A7;
        if (s == "A8")
            return A8;
        if (s == "A9")
            return A9;
        if (s == "A10")
            return A10;
        if (s == "A11")
            return A11;
        if (s == "A12")
            return A12;
        if (s == "A13")
            return A13;
        if (s == "A14")
            return A14;
        if (s == "A15")
            return A15;
        return s.substring(1).toInt();
    }
    return s.toInt();
}

void serialEvent()
{
    static char buffer[32];
    static unsigned int index = 0;
    while (Serial.available() > 0)
    {
        char ch;
        if (Serial.readBytes(&ch, 1) == 1)
        {
            if (((ch >= '0') && (ch <= '9')) || ch == 'A' || ch == 'D')
            {
                buffer[index++] = ch;
                if (index > 30)
                {
                    index = 0;
                }
            }
            if ((ch == '\n') || (ch == '\r'))
            {
                buffer[index] = '\0';
                String s(buffer);

                newPin = convertPinName(s);
                index  = 0;
                Serial.println(String(newPin));
            }
        }
    }
}

void printMenu()
{
    Serial.println();
    Serial.println(F("*************************"));
    Serial.println(F("** Pin Pulse Test Menu **"));
    Serial.println(F("*************************"));
    Serial.println();
    if (currentPin != -1)
    {
        Serial.println("Current pin: " + String(currentPin));
    }
    else
    {
        Serial.println("No pin selected");
    }
    Serial.println();
    Serial.print(F("Enter pin to toggle:"));
}

void setup()
{
    Serial.begin(19200);
    printMenu();
}

int state     = HIGH;
long lastTime = 0;

void loop()
{
    if (newPin != currentPin)
    {
        Serial.println();
        if (currentPin != -1)
        {
            digitalWrite(currentPin, LOW);
            pinMode(currentPin, INPUT);
        }
        currentPin = newPin;
        if (currentPin != -1)
        {
            pinMode(currentPin, OUTPUT);
            state = HIGH;
            digitalWrite(currentPin, state);
            lastTime = millis();
            printMenu();
        }
    }

    long curTime = millis();
    if (currentPin != -1)
    {
        if (lastTime + 250 < curTime)
        {
            lastTime = curTime;
            digitalWrite(currentPin, state);
            state = state == HIGH ? LOW : HIGH;
        }
    }
}