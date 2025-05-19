#include <iostream>
#include <chrono>
#include <filesystem>
#include <sstream>
#include <string>

std::string executeCommand(const std::string& command, const std::string& workDir) {
  std::string result;
  char buffer[128];

  auto currentPath = std::filesystem::current_path();
  std::filesystem::current_path(workDir);

  FILE* pipe = popen(command.c_str(), "r");
  if(!pipe) {
    std::filesystem::current_path(currentPath);
    throw std::runtime_error("popen() failed!");
  }

  while(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    result += buffer;
  }

  pclose(pipe);
  std::filesystem::current_path(currentPath);
  return result;
}

void compileAndRun(const std::string& year, const std::string& day, const std::string& part) {
  const std::string workDir = "./" + year + "/Day" + day;
  const std::string outputName = "part" + part;

  std::cout << "Compiling..." << std::endl;
  std::string compileCommand = "g++ -std=c++20 part" + part + ".cpp -o " + outputName;

  try {
    std::string compileOutput = executeCommand(compileCommand, workDir);
    if (!compileOutput.empty()) {
      std::cout << "Compilation output:\n" << compileOutput << std::endl;
    }

    if (!std::filesystem::exists(workDir + "/" + outputName)) {
      std::cout << "Compilation failed!" << std::endl;
      return;
    }

    std::cout << "\nExecuting solution...\n" << std::endl;

    std::string runCommand = "./" + outputName;
    #ifdef _WIN32
      runCommand += ".exe";
    #endif

    std::string output = executeCommand(runCommand, workDir);
    std::cout << output;

    std::filesystem::remove(workDir + "/" + outputName);
  } catch (const std::exception& e) {
    std::cout << "Error occurred: " << e.what() << std::endl;
  }
}

bool fileIsInvalid(const std::string& year, const std::string& day, const std::string& part) {
  auto now = std::chrono::system_clock::now();
  std::time_t t = std::chrono::system_clock::to_time_t(now);
  std::tm tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y");
  std::string current_year = oss.str();

  int input_year;
  try {
    input_year = std::stoi(year);
  } catch (...) {
    return true;
  }
  if (input_year > std::stoi(current_year)) {
    return true;
  }

  const std::string path = "./" + year + "/Day" + day + "/part" + part + ".cpp";
  return !std::filesystem::exists(path) || !std::filesystem::is_regular_file(path);
}

int main() {
  std::string year = "";
  std::string day = "";
  std::string part = "";

  std::cout << "\033[1;31m ________\033[0m  ________  \033[1;32m________\033[0m\n";
  std::cout << "\033[1;31m|\\   __  \\\033[0m|\\   __  \\\033[1;32m|\\   ____\\\033[0m\n";
  std::cout << "\033[1;31m\\ \\  \\|\\  \\\033[0m \\  \\|\\  \\ \033[1;32m\\  \\___|\033[0m\n";
  std::cout << "\033[1;31m \\ \\   __  \\\033[0m \\  \\\\\\  \\ \033[1;32m\\  \\\033[0m\n";
  std::cout << "\033[1;31m  \\ \\  \\ \\  \\\033[0m \\  \\\\\\  \\ \033[1;32m\\  \\____\033[0m\n";
  std::cout << "\033[1;31m   \\ \\__\\ \\__\\\033[0m \\_______\\ \033[1;32m\\_______\\\033[0m\n";
  std::cout << "\033[1;31m    \\|__|\\|__|\033[0m\\|_______|\033[1;32m\\|_______|\033[0m by Shayan1503\n";

  std::cout << "Welcome! I have tried my hand at solving Advent of Code problems throughout the years.\n";
  std::cout << "This interface is a way to navigate through my solutions.You can press <CTRL + c> anytime to close this interface.\n\n";

  while(true) {
    std::cout << "Enter year (Eg 2023): ";
    std::cin >> year;
    std::cout << "Enter day (Eg 2): ";
    std::cin >> day;
    std::cout << "Enter part (Eg 1): ";
    std::cin >> part;

    if(fileIsInvalid(year, day, part)) {
      std::cout << "Solution to the particular problem you are looking for either does not exist or there was something wrong with the configurations you set. Please try again.\n";
    } else {
      compileAndRun(year, day, part);

      std::cout << "\nWould you like to run another solution? (y/n): ";
      char response;
      std::cin >> response;
      if (response != 'y' && response != 'Y') {
        break;
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
