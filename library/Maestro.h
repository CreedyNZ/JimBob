// Copyright (C) Pololu Corporation.  See LICENSE.txt for details.

/*! \file PololuMaestro.h
 *
 * This is the main header file for the Pololu Maestro Servo Controller library
 * for Arduino.
 *
 *
 * For an overview of the library's features, see
 * https://github.com/pololu/maestro-arduino. That is the main repository for
 * the library.
 */

#pragma once


class Maestro
{
  public:
    /** \brief The default device number, used to construct a MicroMaestro or
        MiniMaestro object that will use the compact protocol.
     */
    static const uint8_t deviceNumberDefault = 255;

    /** \brief The default reset pin is no reset pin, used to construct a
        MicroMaestro or MiniMaestro object that will not have a reset pin.
     */
    static const uint8_t noResetPin = 255;

    /** \brief Resets the Maestro by toggling the \p resetPin, if a \p resetPin
     * was given.
     *
     * By default this function will do nothing. If the \p resetPin was
     * specified while constructing the Maestro object, it will toggle that pin.
     * That pin needs to be wired to the Maestro's RST pin for it to reset the
     * servo controller.
     */
    void reset();

    /** \brief Sets the \a target of the servo on \a channelNumber using the
     * Mini SSC protocol.
     *
     * @param channelNumber A servo number from 0 to 254.
     *
     * @param target A target position from 0 to 254.
     *
     */
    
     */
    void setTarget(uint8_t channelNumber, uint16_t target);

    /** \brief Sets the \a speed limit of \a channelNumber.
     *
     * @param channelNumber A servo number from 0 to 127.
     *
     * @param speed A number from 0 to 16383.
     *
     * Limits the speed a servo channel’s output value changes.
     *
     * See the Serial Interface section in the [Maestro User's
     * Guide](http://www.pololu.com/docs/0J40) for more details.
     *
     * The compact protocol is used by default. If the %deviceNumber was given
     * to the constructor, it uses the Pololu protocol.
     */
    void setSpeed(uint8_t channelNumber, uint16_t speed);

     /** \brief Sets the \a acceleration limit of \a channelNumber.
     *
     * @param channelNumber A servo number from 0 to 127.
     *
     * @param acceleration A number from 0 to 16383.
     *
     * Limits the acceleration a servo channel’s output value changes.
     *
     * See the Serial Interface section in the [Maestro User's
     * Guide](http://www.pololu.com/docs/0J40) for more details.
     *
     * The compact protocol is used by default. If the %deviceNumber was given
     * to the constructor, it uses the Pololu protocol.
     */
    void setAcceleration(uint8_t channelNumber, uint16_t acceleration);

    /** \brief Sends the servos and outputs to home position.
     *
     * If the "On startup or error" setting for a servo or output channel is set
     * to "Ignore", the position will be unchanged.
     *
     * See the Serial Interface section in the [Maestro User's
     * Guide](http://www.pololu.com/docs/0J40) for more details.
     *
     * The compact protocol is used by default. If the %deviceNumber was given
     * to the constructor, it uses the Pololu protocol.
     */
    void goHome();

    /** \brief Stops the script.
     *
     * Stops the script, if it is currently running.
     *
     * See the Serial Interface section in the [Maestro User's
     * Guide](http://www.pololu.com/docs/0J40) for more details.
     *
     * The compact protocol is used by default. If the %deviceNumber was given
     * to the constructor, it uses the Pololu protocol.
     */
    
    uint16_t getPosition(uint8_t channelNumber);

    /** \brief Gets the moving state for all configured servo channels.
     *
     * @return 1 if at least one servo limited by speed or acceleration is still
     * moving, 0 if not.
     *
     * Determines if the servo outputs have reached their targets or are still
     * changing and will return 1 as as long as there is at least one servo that
     * is limited by a speed or acceleration setting.
     *
     * See the Serial Interface section in the [Maestro User's
     * Guide](http://www.pololu.com/docs/0J40) for more details.
     *
     * The compact protocol is used by default. If the %deviceNumber was given
     * to the constructor, it uses the Pololu protocol.
     */
    uint8_t getMovingState();

    /** \brief Gets if the script is running or stopped.
     *
     * @return 1 if script is stopped, 0 if running.
     *
     * The compact protocol is used by default. If the %deviceNumber was given
     * to the constructor, it uses the Pololu protocol.
     */
    
    uint16_t getErrors();

    /** \cond
    *
    * This should be considered a private implementation detail of the library.
    **/
  protected:
    Maestro(uint8_t resetPin,
            uint8_t deviceNumber,
            bool CRCEnabled);

    void writeByte(uint8_t dataByte);
    void writeCRC();
    void writeCommand(uint8_t commandByte);
    void write7BitData(uint8_t data);
    void write14BitData(uint16_t data);
  /** \endcond **/

  private:
    static const uint8_t CRC7Polynomial = 0x91;
    static const uint8_t baudRateIndication = 0xAA;

    static const uint8_t miniSscCommand = 0xFF;
    static const uint8_t setTargetCommand = 0x84;
    static const uint8_t setSpeedCommand = 0x87;
    static const uint8_t setAccelerationCommand = 0x89;
    static const uint8_t getPositionCommand = 0x90;
    static const uint8_t getMovingStateCommand = 0x93;
    static const uint8_t getErrorsCommand = 0xA1;
    static const uint8_t goHomeCommand = 0xA2;
    

    uint8_t _deviceNumber;
    uint8_t _resetPin;
    bool _CRCEnabled;
    uint8_t _CRCByte;
};




