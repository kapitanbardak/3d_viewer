#ifndef VIEWER_CONTROLLER_COMMANDS_INTERFACE_CONTROLLER_COMMAND_H
#define VIEWER_CONTROLLER_COMMANDS_INTERFACE_CONTROLLER_COMMAND_H

/**
 * @brief An interface for controller commands.
 *
 * This interface defines the common structure for controller commands.
 * Controller commands are used to encapsulate actions or operations that
 * can be executed by a controller in an application.
 */
class ICommand {
 public:
  /**
   * @brief Virtual destructor.
   *
   * This virtual destructor ensures proper cleanup when objects
   * implementing this interface are destroyed.
   */
  virtual ~ICommand() {}

  /**
   * @brief Executes the command.
   *
   * This pure virtual function must be implemented by derived classes.
   * It defines the action or operation that the command performs when executed.
   */
  virtual void execute() = 0;
};
#endif  // VIEWER_CONTROLLER_COMMANDS_INTERFACE_CONTROLLER_COMMAND_H
