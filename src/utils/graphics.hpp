#pragma once

#include "../utils/solution_registry.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

#include <atomic>
#include <chrono>
#include <thread>

class Aoi {
  inline ftxui::Element a_text(std::string s) {
    return ftxui::text(s) | ftxui::bold | ftxui::color(ftxui::Color::Red);
  }
  inline ftxui::Element o_text(std::string s) {
    return ftxui::text(s) | ftxui::bold | ftxui::color(ftxui::Color::White);
  }
  inline ftxui::Element c_text(std::string s) {
    return ftxui::text(s) | ftxui::bold | ftxui::color(ftxui::Color::Green);
  }

  // Frame counter for animation
  int tree_frame = 0;

  ftxui::Element getTreeElement() {
    using namespace ftxui;
    auto l = [&](int id, std::string c) {
      bool on = ((tree_frame + id) % 4 == 0);
      Color kColor = Color::Green3;
      if (on) {
        if (id % 3 == 0)
          kColor = Color::Red;
        else if (id % 3 == 1)
          kColor = Color::Gold1;
        else
          kColor = Color::SkyBlue1;
      }
      return text(c) | bold | color(kColor);
    };

    auto g = [&](std::string s) { return text(s) | color(Color::Green1); };
    auto s = [&](std::string s) {
      return text(s) | color(Color::Green3);
    }; // Darker green
    auto t = [&](std::string s) {
      return text(s) | color(Color::RGB(139, 69, 19));
    }; // SaddleBrown

    return vbox(
        hbox({text("           "), l(0, "*")}),
        hbox({text("          "), g("/"), l(1, "|"), g("\\")}),
        hbox(
            {text("         "), g("/"), l(2, "o"), g("."), l(3, "'"), g("\\")}),
        hbox({text("        "), g("/"), s("."), l(4, "@"), g("."), s("'"),
              l(5, "*"), g("\\")}),
        hbox({text("       "), g("/"), l(6, "&"), g("."), s("'"), l(7, "o"),
              g("."), s("~"), l(8, "+"), g("\\")}),
        hbox({text("      "), g("/"), s("."), l(9, "*"), g("."), s("'"),
              l(10, "@"), g("."), s("^"), l(11, "o"), g("."), g("\\")}),
        hbox({text("     "), g("/"), l(12, "o"), g("."), s("~"), l(13, "&"),
              g("."), s("*"), l(14, "+"), g("."), s("'"), l(15, "@"), s("'"),
              g("\\")}),
        hbox({text("    "), g("/"), s("."), l(16, "*"), g("."), s("'"),
              l(17, "o"), g("."), s("^"), l(18, "&"), g("."), s("~"),
              l(19, "*"), g("."), s("'"), g("\\")}),
        hbox({text("   "), g("/"), l(20, "&"), g("."), s("~"), l(21, "@"),
              g("."), s("*"), l(22, "o"), g("."), s("'"), l(23, "+"), g("."),
              s("^"), l(24, "&"), s("'"), l(44, "#"), g("\\")}),
        hbox({text("  "), g("/"),     s("."),     l(25, "o"), g("."),
              s("'"),     l(26, "*"), g("."),     s("^"),     l(27, "@"),
              g("."),     s("~"),     l(28, "o"), g("."),     s("'"),
              l(29, "*"), g("."),     s("~"),     s(","),     g("\\")}),
        hbox({text(" "), g("/"), l(30, "@"), g("."), s("~"), l(31, "&"),
              g("."),    s("*"), l(32, "+"), g("."), s("'"), l(33, "o"),
              g("."),    s("^"), l(34, "&"), g("."), s("~"), l(35, "@"),
              g("."),    s("'"), l(36, "*"), g("\\")}),
        hbox({text(""),   g("/"), s("."), l(37, "*"), g("."), s("'"),
              l(38, "o"), g("."), s("^"), l(39, "&"), g("."), s("~"),
              l(40, "*"), g("."), s("'"), l(41, "@"), g("."), s("^"),
              l(42, "o"), g("."), s("~"), l(43, "&"), g("."), g("\\")}),
        hbox({text("       "), t("[_______]")}),
        hbox({text("         "), t("\\___/")}));
  }

  ftxui::Element getBannerElement() {
    using namespace ftxui;
    return vbox({vbox({hbox({a_text(" ________  "), o_text("________  "),
                             c_text("________")}),
                       hbox({a_text("|\\   __  \\"), o_text("|\\   __  \\"),
                             c_text("|\\   ____\\")}),
                       hbox({a_text("\\ \\  \\|\\  \\ "),
                             o_text("\\  \\|\\  \\ "), c_text("\\  \\___|")}),
                       hbox({a_text(" \\ \\   __  \\"),
                             o_text(" \\  \\\\\\  \\"), c_text(" \\  \\")}),
                       hbox({a_text("  \\ \\  \\ \\  \\"),
                             o_text(" \\  \\\\\\  \\"), c_text(" \\  \\____")}),
                       hbox({a_text("   \\ \\__\\ \\__\\"),
                             o_text(" \\_______\\"), c_text(" \\_______\\")}),
                       hbox({a_text("    \\|__|\\|__|"), o_text("\\|_______|"),
                             c_text("\\|_______|")}),
                       separator(),
                       paragraph(
                           "Welcome! I have tried my hand at solving Advent of "
                           "Code problems throughout the years. This interface "
                           "is "
                           "a way to navigate through my solutions. You can "
                           "press "
                           "ESC anytime to close this interface.")}),
                 filler(), getTreeElement() | center,
                 text("Happy Holidays!") | bold | color(Color::Gold1) |
                     center}) |
           border | size(ftxui::WIDTH, ftxui::EQUAL, 40);
  }

public:
  void run(std::map<int, std::map<int, std::vector<int>>> solutions_map) {
    using namespace ftxui;

    int selected_year = -1, selected_day = -1, selected_part = -1;
    // ... (rest of run() variables) ...
    std::vector<std::string> years_str;
    for (auto &[year, _] : solutions_map)
      years_str.push_back(std::to_string(year));
    std::vector<std::string> days_str;
    std::vector<std::string> parts_str;

    auto menu_year = Menu(&years_str, &selected_year);
    auto menu_day = Menu(&days_str, &selected_day);
    auto menu_part = Menu(&parts_str, &selected_part);

    bool day_enabled = false;
    bool part_enabled = false;
    auto maybe_day = Maybe(menu_day, &day_enabled);
    auto maybe_part = Maybe(menu_part, &part_enabled);

    bool show_result = false;
    int result = 0;
    float time = 0.0;

    std::vector<std::string> modes_str = {"Test Input", "Real Input"};
    int selected_mode = 0;
    auto mode_toggle = Toggle(&modes_str, &selected_mode);

    auto verify_button = Button("Verify Selection", [&]() {
      if (selected_year != -1 && selected_day != -1 && selected_part != -1) {
        show_result = true;
        int year = std::stoi(years_str[selected_year]);
        int day = std::stoi(days_str[selected_day].substr(4));
        int part = std::stoi(parts_str[selected_part].substr(5));

        auto solution = makeSolution(year, day, part, selected_mode);

        if (solution) {
          std::pair<int, long long> output = solution->run();
          result = output.first;
          time = output.second / 1000.0f;
        }
      }
    });

    auto update_days = [&]() {
      // ... existing update_days logic ...
      days_str.clear();
      selected_day = -1;
      parts_str.clear();
      selected_part = -1;
      show_result = false;
      if (selected_year != -1) {
        int year = std::stoi(years_str[selected_year]);
        for (auto &[day, _] : solutions_map[year]) {
          days_str.push_back("Day " + std::to_string(day));
        }
        day_enabled = true;
      } else {
        day_enabled = false;
      }
    };

    auto update_parts = [&]() {
      // ... existing update_parts logic ...
      parts_str.clear();
      selected_part = -1;
      show_result = false;
      if (selected_day != -1) {
        int day = -1;
        sscanf(days_str[selected_day].c_str(), "Day %d", &day);
        auto &days_map = solutions_map[std::stoi(years_str[selected_year])];
        if (days_map.contains(day)) {
          for (int part : days_map[day]) {
            parts_str.push_back("Part " + std::to_string(part));
          }
          part_enabled = true;
        }
      } else {
        part_enabled = false;
      }
    };

    update_days();
    update_parts();

    // Main container
    auto main_container = Container::Horizontal({Container::Vertical(
        {menu_year, maybe_day, maybe_part, mode_toggle, verify_button})});

    // Main renderer
    auto renderer = Renderer(main_container, [&]() -> Element {
      // ... existing renderer logic ...
      day_enabled = (selected_year != -1);
      part_enabled = (selected_day != -1);

      std::string year_str =
          (selected_year == -1) ? "<YEAR>" : years_str[selected_year];
      std::string day_str =
          (selected_day == -1) ? "<DAY>" : days_str[selected_day];
      std::string part_str =
          (selected_part == -1) ? "<PART>" : parts_str[selected_part];

      auto year_status = (selected_year == -1)
                             ? text("← Select") | color(Color::Red)
                             : text("✓") | color(Color::Green);
      auto day_status = !day_enabled ? text("(disabled)") | dim
                        : (selected_day == -1)
                            ? text("← Select") | color(Color::Yellow)
                            : text("✓") | color(Color::Green);
      auto part_status = !part_enabled ? text("(disabled)") | dim
                         : (selected_part == -1)
                             ? text("← Select") | color(Color::Blue)
                             : text("✓") | color(Color::Green);

      auto menu_panel = vbox(
          {text("Selection Menu") | bold | center, separator(),

           hbox(
               {vbox({hbox({a_text("YEAR"), text(" "), year_status}),
                      separator(),
                      menu_year->Render() | frame |
                          size(HEIGHT, LESS_THAN, 6)}) |
                    border | flex,

                vbox({hbox({o_text("DAY"), text(" "), day_status}), separator(),
                      day_enabled ? maybe_day->Render() | frame |
                                        size(HEIGHT, LESS_THAN, 6)
                                  : text("Select year first") | dim | center}) |
                    border | flex,

                vbox({hbox({c_text("PART"), text(" "), part_status}),
                      separator(),
                      part_enabled ? maybe_part->Render() | frame |
                                         size(HEIGHT, LESS_THAN, 6)
                                   : text("Select day first") | dim | center}) |
                    border | flex}),

           separator(),
           text("Current: " + year_str + " " + day_str + " " + part_str) |
               bold | center,
           separator(),

           verify_button->Render() | center, separator(),
           text("Input Mode") | center, mode_toggle->Render() | center,
           separator(),

           show_result ? vbox({text("RESULT: " + std::to_string(result)) |
                                   bold | color(Color::Cyan),
                               separator(),
                               text("Took " + std::to_string(time) +
                                    " microsecond(s)") |
                                   color(Color::Green)}) |
                             border | color(Color::Blue)
                       : text("Press 'Verify Selection' to see result") | dim |
                             center | border});

      // Main layout: Banner on left, Menu on right
      return hbox({getBannerElement(), separator(), menu_panel | flex}) |
             size(WIDTH, GREATER_THAN, 100);
    });

    // Event loop with change detection
    auto screen = ScreenInteractive::Fullscreen();

    // Animation thread
    std::atomic<bool> running(true);
    std::thread animation_thread([&] {
      while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        screen.PostEvent(Event::Custom);
        tree_frame++;
      }
    });

    auto final_renderer =
        Renderer(Container::Vertical({renderer}), [&]() -> Element {
          static int prev_year = -2, prev_day = -2;

          if (prev_year != selected_year) {
            prev_year = selected_year;
            update_days();
          }
          if (prev_day != selected_day) {
            prev_day = selected_day;
            update_parts();
          }

          return renderer->Render();
        });

    auto event_handler = CatchEvent(final_renderer, [&](Event event) {
      if (event == Event::Escape) {
        screen.Exit();
        return true;
      }
      return false;
    });

    screen.Loop(event_handler);
    running = false;
    animation_thread.join();
  }
};
;
