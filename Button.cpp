#include "Button.h"

void Button::updatePressedValues(bool currentlyPressed) {
  if (currentlyPressed) {
    // Guard for fluctuations
    if (millis() - m_lastReleased < m_allowance) return;

    m_lastPressed = millis();

    // If the button was pressed just a moment ago, then
    // the button should NOT be considered "just pressed". Otherwise,
    // it should.
    if (!m_previouslyPressed) {
      justPressed = true;
    } else {
      justPressed = false;
    }
  } else {
    // Guard for fluctuations
    if (millis() - m_lastPressed < m_allowance) return;

    m_lastReleased = millis();

    // If the button was pressed just a moment ago, then
    // the button SHOULD be considered "just released". Otherwise,
    // it should not.
    if (m_previouslyPressed) {
      justReleased = true;
    } else {
      justReleased = false;
    }
  }

  // Update m_previouslyPressed for the next call of updatePressedValues
  m_previouslyPressed = currentlyPressed;
}

void Button::updateHoldTime(bool currentlyPressed) {
  if (currentlyPressed) {
    // check if this is just a fluctuation
    if (millis() - m_lastReleased < m_allowance) return;

    // IF NOT: update m_lastPressed
    m_lastPressed = millis();

    holdTime = millis() - m_lastReleased;
  } else {
    // check if this is just a flucturation
    if (millis() - m_lastPressed < m_allowance) return;

    // IF NOT: update m_lastReleased
    m_lastReleased = millis();
  }
}

void Button::update() {
  bool currentlyPressed = !digitalRead(m_port);

  updatePressedValues(currentlyPressed);
  updateHoldTime(currentlyPressed);
}

void Button::print_debug() {
  Serial.println("--- BUTTON INFORMATION ---");
  Serial.println("PORT: " + String(m_port));
  Serial.println("justPressed: " + String(justPressed));
  Serial.println("justReleased: " + String(justReleased));
  Serial.println("holdTime: " + String(holdTime) + " ms");
  Serial.println();
}