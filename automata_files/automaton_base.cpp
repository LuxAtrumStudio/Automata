#include "automaton_base.hpp"
#include <pessum.h>
#include <array>
#include <string>
#include <vector>
#include "automata.hpp"

automata::Automaton::Automaton() { name = "automaton"; }

automata::Automaton::Automaton(const Automaton& copy) {
  start_state = copy.start_state;
  name = copy.name;
  language = copy.language;
  accepting_states = copy.accepting_states;
  states = copy.states;
  transitions = copy.transitions;
}

automata::Automaton::~Automaton() {
  language.clear();
  accepting_states.clear();
  states.clear();
  transitions.clear();
}

void automata::Automaton::SetName(std::string in_name) { name = in_name; }

void automata::Automaton::SetStartState(std::string stat) {
  start_state = State(stat);
}

void automata::Automaton::SetStartState(int stat) { start_state = stat; }

void automata::Automaton::SetLanguage(char lang) {
  language.clear();
  language = {lang};
}

void automata::Automaton::SetLanguage(std::vector<char> lang) {
  language.clear();
  language = lang;
}

void automata::Automaton::SetLanguage(std::string lang) {
  language.clear();
  language = std::vector<char>(lang.c_str(), lang.c_str() + lang.length() + 1);
}

void automata::Automaton::AddLanguage(char lang) { language.push_back(lang); }

void automata::Automaton::AddLanguage(std::vector<char> lang) {
  language.insert(language.end(), lang.begin(), lang.end());
}

void automata::Automaton::AddLanguage(std::string lang) {
  std::vector<char> lang_vec(lang.c_str(), lang.c_str() + lang.length() + 1);
  language.insert(language.end(), lang_vec.begin(), lang_vec.end());
}

void automata::Automaton::SetStates(std::string stat) {
  states.clear();
  states = {stat};
}

void automata::Automaton::SetStates(std::vector<std::string> stat) {
  states.clear();
  states = stat;
}

void automata::Automaton::AddStates(std::string stat) {
  states.push_back(stat);
}

void automata::Automaton::AddStates(std::vector<std::string> stat) {
  states.insert(states.end(), stat.begin(), stat.end());
}

void automata::Automaton::SetAccepting(std::string stat) {
  accepting_states.clear();
  int state_index;
  for (state_index = 0; state_index < states.size(); state_index++) {
    if (states[state_index] == stat) {
      break;
    }
  }
  accepting_states = {state_index};
}

void automata::Automaton::SetAccepting(int stat) {
  accepting_states.clear();
  accepting_states = {stat};
}

void automata::Automaton::SetAccepting(std::vector<std::string> stat) {
  accepting_states.clear();
  for (int i = 0; i < stat.size(); i++) {
    int state_index;
    for (state_index = 0; state_index < states.size(); state_index++) {
      if (states[state_index] == stat[i]) {
        break;
      }
    }
    accepting_states.push_back(state_index);
  }
}

void automata::Automaton::SetAccepting(std::vector<int> stat) {
  accepting_states.clear();
  accepting_states = stat;
}

void automata::Automaton::AddAccepting(std::string stat) {
  int state_index;
  for (state_index = 0; state_index < states.size(); state_index++) {
    if (states[state_index] == stat) {
      break;
    }
  }
  accepting_states.push_back(state_index);
}

void automata::Automaton::AddAccepting(int stat) {
  accepting_states.push_back(stat);
}

void automata::Automaton::AddAccepting(std::vector<std::string> stat) {
  for (int i = 0; i < stat.size(); i++) {
    int state_index;
    for (state_index = 0; state_index < states.size(); state_index++) {
      if (states[state_index] == stat[i]) {
        break;
      }
    }
    accepting_states.push_back(state_index);
  }
}

void automata::Automaton::AddAccepting(std::vector<int> stat) {
  accepting_states.insert(accepting_states.end(), stat.begin(), stat.end());
}

bool automata::Automaton::IsAccept(int stat) {
  for (int i = 0; i < accepting_states.size(); i++) {
    if (accepting_states[i] == stat) {
      return (true);
    }
  }
  return (false);
}

void automata::Automaton::SetTransitions(
    std::vector<std::array<int, 3>> trans) {
  transitions.clear();
  transitions = trans;
}

void automata::Automaton::AddTransitions(std::array<int, 3> trans) {
  transitions.push_back(trans);
}

void automata::Automaton::AddTransitions(std::string state_a, char ch,
                                         std::string state_b) {
  if (this->Type() != DFA && this->Type() != NONE) {
    pessum::Log(pessum::WARNING,
                "Transtions for this automaton requier different parameters",
                "automata::Automaton::AddTransitions");
  } else {
    transitions.push_back(
        std::array<int, 3>{State(state_a), Language(ch), State(state_b)});
  }
}

std::vector<std::array<int, 3>> automata::Automaton::GetTransitions(
    std::array<int, 2> match) {
  std::vector<std::array<int, 3>> matched;
  for (int i = 0; i < transitions.size(); i++) {
    if (transitions[i][0] == match[0] && transitions[i][1] == match[1]) {
      matched.push_back(transitions[i]);
    }
  }
  return (matched);
}

int automata::Automaton::State(std::string stat) {
  for (int i = 0; i < states.size(); i++) {
    if (states[i] == stat) {
      return (i);
    }
  }
  pessum::Log(pessum::WARNING, "State %s does not exist",
              "automata::Automaton::State", stat.c_str());
  return (0);
}

int automata::Automaton::Language(char ch) {
  for (int i = 0; i < language.size(); i++) {
    if (language[i] == ch) {
      return (i);
    }
  }
  pessum::Log(pessum::WARNING, "Language does not contain %c",
              "automata::Automaton::Language", ch);
  return (0);
}

int automata::Automaton::Type() { return (NONE); }
