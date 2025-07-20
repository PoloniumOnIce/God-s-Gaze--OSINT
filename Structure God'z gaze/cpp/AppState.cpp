#include "AppState.h"

AppState::State AppState::currentState = AppState::ACCUEIL;

void AppState::set(State state) {
    currentState = state;
}

AppState::State AppState::get() {
    return currentState;
}