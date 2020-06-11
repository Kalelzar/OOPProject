#include <fstream>
#include <iostream>

#include "src/HotelState.hpp"
#include "src/parser/HTLInterpreter.hpp"
#include "src/parser/Scanner.hpp"

int main() {

  // Register all commands used by the interpreter
  // As of now you need to pass the help description directly
  // But baking in the strings directly is not only ugly
  // but loading them dynamically from a file would
  // allow for translations and the like

  const char *addHelp =
      " <room> <beds> : Add a new room to the database. (File only)";
  const char *removeHelp = " <room> : Remove room from database. (File only)";
  const char *checkinHelp = " <room> <from> <to> <note> : Marks <room> as taken"
                            "for the period <from> <to>. Also attaches a "
                            "<note> to the check-in event.";
  const char *checkoutHelp =
      " <room> [date]: If the room is marked taken for a period that includes "
      "[date] (defaults to today)\n"
      " then mark the room as free from <date> until the end of the period.";
  const char *unavailableHelp =
      " <room> <from> <to> <note> : Marks <room> as unavailable for the period "
      "<from> <to>. Also attaches a <note> to the unavailable event.";
  const char *reportHelp =
      " <from> <to> : Display when rooms are taken or unavailable for the "
      "period <from> <to> (Console only)";
  const char *findHelp = " <beds> <from> <to> : Find a room with at least "
                         "<beds> beds that is free <from> <to> (Console only)";
  const char *findFHelp =
      " <beds> <from> <to> : Find a room with at least <beds> beds that can be "
      "free <from> <to> if the occupants of at most two rooms are moved "
      "(Console only)";
  const char *availabilityHelp = " [date] : show all rooms that are free on "
                                 "[date] (defaults to today) (Console only)";
  const char *openHelp = " <filepath> : Open file at <filepath> (Console only)";
  const char *closeHelp =
      " : Close currently opened file. Does not save the file. (Console only)";
  const char *helpHelp = " : Displays this message (Console only)";
  const char *exitHelp = " : Exits the program. (Console only)";
  const char *saveHelp = " : Saves the file if necessary. (Console only)";
  const char *saveasHelp = " <filepath> : Saves the file to <filepath>. Also "
                           "sets the currently active file to <filepath>";

  const char *listHelp =
      " [filepath] : lists all .htl files in the provided directory or the "
      "working directory if none is provided.";

  Hotel::CommandList cl;

  cl.registerCommand("add", TokenType::ADD, ScannerContext::FILE, addHelp);
  cl.registerCommand("remove", TokenType::REMOVE, ScannerContext::FILE,
                     removeHelp);

  cl.registerCommand("checkin", TokenType::CHECKIN, ScannerContext::ALL,
                     checkinHelp);
  cl.registerCommand("checkout", TokenType::CHECKOUT, ScannerContext::ALL,
                     checkoutHelp);
  cl.registerCommand("unavailable", TokenType::UNAVAILABLE, ScannerContext::ALL,
                     unavailableHelp);

  cl.registerCommand("list", TokenType::LIST, ScannerContext::CONSOLE,
                     listHelp);

  cl.registerCommand("report", TokenType::REPORT, ScannerContext::CONSOLE,
                     reportHelp);
  cl.registerCommand("find", TokenType::FIND, ScannerContext::CONSOLE,
                     findHelp);
  cl.registerCommand("find!", TokenType::FIND_F, ScannerContext::CONSOLE,
                     findFHelp);
  cl.registerCommand("availability", TokenType::AVAILABILITY,
                     ScannerContext::CONSOLE, availabilityHelp);

  cl.registerCommand("open", TokenType::OPEN, ScannerContext::CONSOLE,
                     openHelp);
  cl.registerCommand("close", TokenType::CLOSE, ScannerContext::CONSOLE,
                     closeHelp);
  cl.registerCommand("help", TokenType::HELP, ScannerContext::CONSOLE,
                     helpHelp);
  cl.registerCommand("exit", TokenType::EXIT, ScannerContext::CONSOLE,
                     exitHelp);
  cl.registerCommand("save", TokenType::SAVE, ScannerContext::CONSOLE,
                     saveHelp);
  cl.registerCommand("saveas", TokenType::SAVE_AS, ScannerContext::CONSOLE,
                     saveasHelp);

  // Mark the command list as global so it isn't necessary to lug it around
  // everywere
  Hotel::CommandList::setCommandList(cl);

  Hotel::HotelState state;

  Hotel::Scanner scanner{ScannerContext::CONSOLE, &std::cin, cl};
  bool run = true;

  // Run until the user tells you not to
  while (run) {
    if (strlen(state.getFile()) != 0) {
      std::cout << "[" << state.getFile()
                << "]"; // Print out the name of the opened file if any
    }
    std::cout << "$ ";
    std::shared_ptr<ArrayList<Token>> tokens = scanner.scanNext();
    Hotel::HTLInterpreter ci(tokens);
    run = ci.parse(state);
  }

  return 0;
}
