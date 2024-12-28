#ifndef LW09_DALI_H
#define LW09_DALI_H
#include <cstdint>

/**
 * @enum DALICommand
 * @brief Represents various DALI (Digital Addressable Lighting Interface) commands used for controlling lighting systems.
 *
 * The enum defines specific commands that can be sent as part of the DALI protocol
 * for controlling lights, including turning them on, off, adjusting brightness, and setting limits.
 */
enum DALICommand {
    OFF = 0x00,
    UP = 0x01,
    DOWN = 0x02,
    STEP_UP = 0x03,
    STEP_DOWN = 0x04,
    MAX = 0x05,
    MIN = 0x06,
    STEP_DOWN_OFF = 0x07,
    ON_STEP_UP = 0x08
};

/**
 * @enum DALISceneCommand
 * @brief Defines scene commands for a DALI (Digital Addressable Lighting Interface) system.
 *
 * This enumeration represents various scene commands that can be sent
 * in a DALI lighting control system. Each command corresponds to a specific
 * scene number with its respective hexadecimal value.
 *
 * @var SCENE_0
 * Represents Scene 0 with value 0x10.
 *
 * @var SCENE_1
 * Represents Scene 1 with value 0x11.
 *
 * @var SCENE_2
 * Represents Scene 2 with value 0x12.
 *
 * @var SCENE_3
 * Represents Scene 3 with value 0x13.
 *
 * @var SCENE_4
 * Represents Scene 4 with value 0x14.
 *
 * @var SCENE_5
 * Represents Scene 5 with value 0x15.
 *
 * @var SCENE_6
 * Represents Scene 6 with value 0x16.
 *
 * @var SCENE_7
 * Represents Scene 7 with value 0x17.
 *
 * @var SCENE_8
 * Represents Scene 8 with value 0x18.
 *
 * @var SCENE_9
 * Represents Scene 9 with value 0x19.
 *
 * @var SCENE_10
 * Represents Scene 10 with value 0x1A.
 *
 * @var SCENE_11
 * Represents Scene 11 with value 0x1B.
 *
 * @var SCENE_12
 * Represents Scene 12 with value 0x1C.
 *
 * @var SCENE_13
 * Represents Scene 13 with value 0x1D.
 *
 * @var SCENE_14
 * Represents Scene 14 with value 0x1E.
 *
 * @var SCENE_15
 * Represents Scene 15 with value 0x1F.
 */
enum DALISceneCommand {
    SCENE_0 = 0x10,
    SCENE_1 = 0x11,
    SCENE_2 = 0x12,
    SCENE_3 = 0x13,
    SCENE_4 = 0x14,
    SCENE_5 = 0x15,
    SCENE_6 = 0x16,
    SCENE_7 = 0x17,
    SCENE_8 = 0x18,
    SCENE_9 = 0x19,
    SCENE_10 = 0x1A,
    SCENE_11 = 0x1B,
    SCENE_12 = 0x1C,
    SCENE_13 = 0x1D,
    SCENE_14 = 0x1E,
    SCENE_15 = 0x1F
};

namespace LW09DaliConstants {
    /**
     * @brief Represents the status register address for the LW09Dali device.
     *
     * Used as a register address to query or interact with the device's status.
     * This constant is utilized in I2C communication when accessing the status
     * of the LW09Dali device.
     */
    static constexpr uint8_t REG_STATUS = 0x00;
    /**
     * @brief Static constant representing the command register address.
     *
     * This constant defines the register to which commands for controlling
     * the LW09Dali device are written. It is used within methods to specify
     * the target I2C register during communication.
     */
    static constexpr uint8_t REG_COMMAND = 0x01;
    /**
     * @brief Static constant representing the configuration register address.
     *
     * This constant defines the register address used for configuration settings
     * in the LW09Dali I2C communication. The value of REG_CONFIG is 0x02,
     * which corresponds to the specific configuration register within the
     * LW09Dali device.
     */
    static constexpr uint8_t REG_CONFIG = 0x02;
    /**
     * @brief Constant representing the STATUS_BUSY bit in the status register.
     *
     * This constant is used to verify if the LW09Dali device is busy.
     * A non-zero value in the STATUS_BUSY bit indicates the device is busy.
     */
    static constexpr uint8_t STATUS_BUSY = 0x40;
    /**
     * @brief A constant representing the broadcast address for DALI (Digital Addressable Lighting Interface) communication.
     *
     * This constant is used to send a command to all devices on the DALI bus, as opposed to a specific addressable device.
     * It is assigned the value 0xFF, which is the standard broadcast address in DALI systems.
     */
    static constexpr uint8_t DALI_BROADCAST = 0xFF;
};


/**
 * @class LW09Dali
 * @brief LW09Dali class provides an interface for controlling DALI-compatible LEDs and devices via an I2C bus.
 *
 * The LW09Dali class simplifies the interaction with DALI-based lighting systems. It includes utilities for
 * sending commands, reading data, controlling brightness, assigning addresses, and managing device configurations.
 */
class LW09Dali {
    /**
     * @brief Constructor for the LW09Dali class.
     *
     * Initializes an instance of the LW09Dali object with the specified I2C address.
     *
     * @param i2cAddress The I2C address of the LW09Dali device.
     */
public:
    explicit LW09Dali(uint8_t i2cAddress);

    /**
     * Sends a command to the LED Warrior device over the I2C interface.
     *
     * This method transmits a command to a specific register address of the LED Warrior
     * chip using the I2C protocol. The command consists of the target address within the
     * device and a value that specifies the action or data to be sent.
     *
     * @param address The register address within the LED Warrior device to which
     *                the command is directed. For example, this may represent a
     *                control or configuration register.
     * @param value   The value to be sent to the specified address. This value
     *                typically represents data or a specific command instruction.
     */
    void sendCommand(uint8_t address, uint8_t value) const;

    /**
     * @brief Reads the status register from the LED Warrior module.
     *
     * This function communicates with the LED Warrior device over the I2C interface
     * to fetch the current status register. The returned value contains specific
     * status flags indicating the operational state of the device.
     *
     * @return uint8_t The value of the status register from the LED Warrior module.
     *         The bits in the register provide state information as defined by the
     *         device's documentation.
     *
     * @note This function assumes that the I2C communication has been properly
     *       initialized elsewhere in the application.
     */
    uint8_t readStatus() const;

    /**
     * Reads a single byte of data from the I2C device at the current register.
     *
     * This method starts a transmission to the I2C device using the stored
     * I2C address and requests one byte of data from the device. The transmitted
     * register address is defined by LW09DaliConstants::REG_COMMAND. The method
     * then reads the single byte of data provided by the device and returns it.
     *
     * @return The byte of data read from the I2C device.
     */
    uint8_t readData() const;

    /**
     * Executes a query operation by sending a command with a specified address
     * and value, waits for the device to be ready, and then reads the response data.
     *
     * @param address The address of the command to be sent to the I2C device.
     * @param value The value associated with the command to be sent.
     * @return The data read from the device as the result of the query.
     *
     * This function internally sends a command to the device using the specified
     * address and value. It then waits until the device's status indicates that it
     * is ready to provide data. Finally, it reads and returns the response data
     * from the device.
     *
     * This method assumes the `waitForReady` function ensures that the device is
     * not busy before reading data, and `sendCommand`, `readData`, and `readStatus`
     * handle the hardware-specific I2C communication.
     */
    uint8_t readQuery(uint8_t address, uint8_t value) const;

    /**
     * Sets the DALI (Digital Addressable Lighting Interface) address for a specified device.
     *
     * This method constructs a DALI address by combining the provided group bit, address,
     * and mode bit into a single address byte. It then sends the constructed address to
     * the appropriate device.
     *
     * The DALI address is constructed as follows:
     * - `address`: The base address, shifted left by one bit.
     * - `groupBit`: Logical OR operation with the group bit (0 or 1).
     * - `modeBit`: Logical OR operation with the mode bit (0 or 1).
     *
     * The valid range for the parameters is:
     * - `groupBit`: Must be 0 or 1.
     * - `address`: Must be in the range 0-63.
     * - `modeBit`: Must be 0 or 1.
     *
     * If any parameter is outside the valid range, the function exits without performing any action.
     *
     * @param groupBit The bit indicating whether the address is a group or an individual address (0 for individual, 1 for group).
     * @param address The base address value, ranging from 0 to 63.
     * @param modeBit The mode bit, specifying additional configuration (e.g., short address or broadcast) as 0 or 1.
     */
    void setDALIAddress(uint8_t groupBit, uint8_t address, uint8_t modeBit) const;

    /**
     * Waits until the LED Warrior device is ready to process new commands.
     * This method continuously checks the device's status register, waiting
     * for the busy flag to clear.
     *
     * The method directly interacts with the device via I2C to read
     * the status register. It ensures that the device is not busy before
     * allowing further operations.
     *
     * The primary use of this method is to pause execution until the
     * device has completed its current operation, ensuring synchronous
     * behavior for subsequent commands.
     */
    void waitForReady() const;

    /**
     * Sets the brightness level of a lamp at the specified address.
     * The brightness level must be between 0 (off) and 254 (maximum brightness).
     *
     * @param address The DALI short address of the lamp. Valid range is 0x00 to 0x3F.
     * @param level The desired brightness level for the lamp. Valid range is 0 to 254.
     */
    void setLampLevel(uint8_t address, uint8_t level) const;

    /**
     * Configures a switch input for the LW09Dali device.
     *
     * This method sets the mode and address for a specific switch input on the
     * LW09Dali device. It uses the I2C protocol to communicate with the device.
     *
     * @param switchIndex The index of the switch to configure (0 or 1).
     * @param mode The mode to set the switch to (range: 0 to 6).
     * @param address The I2C address to associate with the switch (range: 0 to 127).
     *
     * @return None.
     *
     * Note:
     * - If the `switchIndex` is greater than 1, `mode` is greater than 6, or
     *   `address` is greater than 127, the method will return immediately without
     *   making any changes to the device.
     * - For `switchIndex` 0, only the provided `mode` and `address` are written.
     * - For `switchIndex` 1, default values (0x00) are set for switch 0, and the
     *   provided `mode` and `address` are written for switch 1.
     *
     * Dependencies:
     * - The method uses the `Wire` library for I2C communication.
     *
     * Usage:
     * - This method should be used to configure the device's switches following
     *   initialization and before setting the intended operational parameters.
     */
    void configureSwitchInput(uint8_t switchIndex, uint8_t mode, uint8_t address) const;

    /**
     * Sends a DALI (Digital Addressable Lighting Interface) command to a specific address.
     *
     * This method sends a DALI command over an I²C interface by leveraging the LED Warrior controller.
     * The function ensures the addressed device is within the permissible address range or broadcasts
     * the command if the address is set to broadcast.
     *
     * @param command The DALI command to be sent. This value determines the specific action
     *                requested from the DALI-enabled lighting device.
     * @param address The target DALI address of the device. The value should be in the range
     *                of 0 to 63 for individual addresses or a special broadcast address.
     */
    void sendDALICommand(DALICommand command, uint8_t address) const;

    /**
     * @brief Stores the I2C address of the LW09Dali device.
     *
     * This variable is used as the target address for I2C communication when sending
     * commands or reading data from the LW09Dali device.
     *
     * It is initialized during the construction of the LW09Dali object and remains
     * constant throughout its lifetime.
     */
private:
    uint8_t _i2cAddress;
};
#endif
