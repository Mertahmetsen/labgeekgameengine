#ifndef MERAHM_SCENE
#define MERAHM_SCENE
#include "../fundamental/basic.h"

void changeScene (const Scene* currentScene, const Scene* newScene) {
    if (currentScene && currentScene->onFinish) currentScene->onFinish();
    currentScene = newScene;
    if (currentScene && currentScene->onLoad) currentScene->onLoad();
}

#endif