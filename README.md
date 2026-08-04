# 🎯 ESP Base for CS 1.6

![Made with C++](https://img.shields.io/badge/Made%20with-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![Platform Windows](https://img.shields.io/badge/Platform-Windows-0078D6?style=flat-square&logo=windows&logoColor=white)
![Status](https://img.shields.io/badge/Status-Stable-brightgreen?style=flat-square)
![Game](https://img.shields.io/badge/Game-CS%201.6-orange?style=flat-square)

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&color=00FF88&center=true&vCenter=true&width=500&lines=ESP+Base+for+CS+1.6;Clean+minimal+source+code;Learn+by+reading" alt="Typing SVG" />
</p>

---

## 📑 Меню

- [🤔 О чём тут](#-о-чём-тут)
- [⚡️ Что умеет](#-что-умеет)
- [🗂️ Структура проекта](#-структура-проекта)
- [🚀 Как собрать](#-как-собрать)
- [🎮 Как юзать](#-как-юзать)
- [🧩 Что можно докрутить](#-что-можно-докрутить)
- [🙏 Респект](#-респект)
- [⚠️ Дисклеймер](#-дисклеймер)

---

## 🤔 О чём тут

**ESP Base** — минимальный чистый исходник ESP для Counter-Strike 1.6 на C++ / OpenGL / WinAPI.

Задумывался как **отправная точка для тех кто хочет разобраться** как работают читы для GoldSrc движка. Никаких сторонних библиотек, никакой обфускации — только чистая база чтобы читать код и понимать.

Проект собирается в DLL, инжектится в `hl.exe` любым инжектором, рисует ESP-боксы врагов и своё меню на OpenGL.

---

## ⚡️ Что умеет

| Категория | Функции |
|---|---|
| 🎯 **ESP** | Box, Name, Teammates, Visible Only, Color CT / Color T |
| 🖥️ **GUI** | Своё меню на OpenGL с чекбоксами и цветами, drag-and-drop окна |
| 🧹 **Unload** | Полная выгрузка DLL из процесса по кнопке |
| ⌨️ **Bind** | Открытие/закрытие меню на `INSERT` |
| 🎨 **Render** | OpenGL 1.x fixed pipeline: RectFilled, RectOutline, Text, Cursor |

---

## 🗂️ Структура проекта

```
source/
├── core/
│   ├── hook_manager.h     # Inline и IAT хуки
│   ├── hooks.cpp/h        # Хук wglSwapBuffers и HUD_AddEntity
│   ├── offsets.cpp/h      # Поиск структур движка (pmove, pEngineFunc)
│   └── unload.cpp/h       # Логика выгрузки DLL
├── gui/
│   ├── gui.cpp/h          # Само меню
│   ├── gui_input.h        # Обработка мыши
│   └── gui_render.h       # OpenGL примитивы
├── valve_sdk/             # Стандартный SDK от Valve (HL SDK)
├── visuals/
│   └── esp.cpp/h          # Отрисовка ESP
├── dllmain.cpp            # Точка входа DLL
├── pch.h/cpp              # Precompiled header
```


---

## 🚀 Как собрать

1. Открой `Project-1.sln` в **Visual Studio 2022** (Community подойдёт)
2. Убедись что установлен компонент **Desktop development with C++**
3. Выбери конфигурацию **Release | x86** (или Debug)
4. Нажми **Build → Build Solution** (`Ctrl+Shift+B`)
5. Готовая `.dll` появится в `Release-Files/` или `Debug-Files/`

> [!IMPORTANT]
> Проект **только x86** — CS 1.6 32-битный, x64 работать не будет.

---

## 🎮 Как юзать

1. Запусти Counter-Strike 1.6
2. Запусти любой инжектор
3. Инжектни собранную `.dll` в процесс `hl.exe`
4. Зайди на любую карту / сервер
5. Нажми **INSERT** — откроется меню
6. Включи **ESP Enabled** + **Box** + **Name**
7. Готово. Для выгрузки нажми **UNLOAD** в меню

---

## 🧩 Что можно докрутить

Отличная база для практики. Что можно добавить самому:

- 🎨 **Chams** — просвечивание моделей через стены
- 📏 **Distance** — расстояние до врага в метрах
- ❤️ **Health Bar** — полоска HP над боксом
- 🔊 **Sound ESP** — точки на экране откуда звук
- 📁 **Config System** — сохранение настроек в файл
- 🎨 **Themes** — темы оформления меню

---

## 🙏 Респект

| Кто | За что |
|---|---|
| **Valve** | за HL SDK |
| **CS 1.6 community** | за исследования GoldSrc |

Автор: **exz666**  
Канал: **[t.me/originalHNS](https://t.me/originalHNS)**

---

## ⚠️ Дисклеймер

**Этот проект создан исключительно в образовательных и исследовательских целях.**

**Запрещено:**
1. Использовать на публичных серверах против других игроков
2. Использовать на турнирных / рейтинговых площадках
3. Выдавать за "честную игру"

**Ты соглашаешься, что:**
1. Автор **не несёт ответственности** за баны, потерю аккаунтов, разбитые мониторы и любые последствия
2. Все риски — на тебе
3. Используешь на свой страх и риск

Изучай, разбирайся, кодь

---

## 📸 Скриншоты

<img width="1127" height="580" alt="image" src="https://github.com/user-attachments/assets/d238b8f9-1ed7-4c39-b0a8-cf1ee5c3af39" />
