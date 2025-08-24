#pragma once

#include "../utils/all_solutions.hpp"
#include "../utils/solution_registry.cpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

class Aoi {
  // Your original colored text methods
  inline ftxui::Element a_text(std::string s) {
    return ftxui::text(s) | ftxui::bold | ftxui::color(ftxui::Color::Red);
  }
  inline ftxui::Element o_text(std::string s) {
    return ftxui::text(s) | ftxui::bold | ftxui::color(ftxui::Color::White);
  }
  inline ftxui::Element c_text(std::string s) {
    return ftxui::text(s) | ftxui::bold | ftxui::color(ftxui::Color::Green);
  }

  // Convert showBanner() to return an Element instead of printing
  ftxui::Element getBannerElement() {
    using namespace ftxui;
    return vbox({hbox({a_text(" ________  "), o_text("________  "),
                       c_text("________")}),
                 hbox({a_text("|\\   __  \\"), o_text("|\\   __  \\"),
                       c_text("|\\   ____\\")}),
                 hbox({a_text("\\ \\  \\|\\  \\ "), o_text("\\  \\|\\  \\ "),
                       c_text("\\  \\___|")}),
                 hbox({a_text(" \\ \\   __  \\"), o_text(" \\  \\\\\\  \\"),
                       c_text(" \\  \\")}),
                 hbox({a_text("  \\ \\  \\ \\  \\"), o_text(" \\  \\\\\\  \\"),
                       c_text(" \\  \\____")}),
                 hbox({a_text("   \\ \\__\\ \\__\\"), o_text(" \\_______\\"),
                       c_text(" \\_______\\")}),
                 hbox({a_text("    \\|__|\\|__|"), o_text("\\|_______|"),
                       c_text("\\|_______|")}),
                 separator(),
                 paragraph(
                     "Welcome! I have tried my hand at solving Advent of "
                     "Code problems throughout the years. This interface is "
                     "a way to navigate through my solutions. You can press "
                     "ESC anytime to close this interface.")}) |
           border | size(ftxui::WIDTH, ftxui::EQUAL, 40);
  }

public:
  void run(std::map<int, std::map<int, std::vector<int>>> solutions_map) {
    using namespace ftxui;

    int selected_year = -1, selected_day = -1, selected_part = -1;
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

    auto verify_button = Button("Verify Selection", [&]() {
      if (selected_year != -1 && selected_day != -1 && selected_part != -1) {
        show_result = true;
        int year = std::stoi(years_str[selected_year]);
        int day = std::stoi(days_str[selected_day].substr(4));
        int part = std::stoi(parts_str[selected_part].substr(5));

        auto solution = makeSolution(year, day, part, 0);

        if (solution) {
          std::pair<int, long long> output = solution->run();
          result = output.first;
          time = output.second / 1000.0f;
        }
      }
    });

    auto update_days = [&]() {
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
        {menu_year, maybe_day, maybe_part, verify_button})});

    // Main renderer
    auto renderer = Renderer(main_container, [&]() -> Element {
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
  }
};
;
