#include <Arduino.h>

/**
 * Button helper class that provides functionality to check
 * if a button was JUST pressed (is only true the moment the button is pressed),
 * if a button was JUST released (is only true the moment the button is released), and
 * the amount of time the button is currently/was previously held.
 */
class Button {
  private:
    // Whether the button was pressed just before this moment.
    bool m_previouslyPressed = false;
    // The time the button was last released, in milliseconds
    long long int m_lastReleased = 0;
    // The time the button was last pressed, in milliseconds
    long long int m_lastPressed = 0;

    int m_port;
    int m_allowance;
    
    /**
     * Updates the values of justPressed and justReleased.
     *
     * @param currentlyPressed the current state of the button's port
     */
    void updatePressedValues(bool currentlyPressed);

    /**
     * Updates the value of holdTime.
     *
     * @param currentlyPressed the current state of the button's port
     */
    void updateHoldTime(bool currentlyPressed);

  public:
    // If the button has JUST been pressed.
    bool justPressed = false;
    // If the button has JUST been released.
    bool justReleased = false;
    // The amount of time the button is currently/was previously held.
    int holdTime = 0;

    /**
     * Initializer for a new Button instance
     * 
     * @param p the port the button is connected to
     * @param a the amount of time between the last release and press to not be considered a fluctuation, in milliseconds
     */
    Button(int p, int a) : m_port(p), m_allowance(a) {}

    /**
     * Updates all of the values in this button. Should be called every loop iteration,
     * BEFORE any variables are accessed.
     */
    void update();

    /**
     * Prints debug information about this button to the serial monitor.
     */
    void print_debug();
};
