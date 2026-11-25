# Atenea en El Dorado

Videojuego 2D desarrollado en C++ con Qt como proyecto final de Informática II (Universidad de Antioquia). Atenea recorre dos niveles en busca del oro y la llave de El Dorado.

## Estado del proyecto

Proyecto terminado: **Momento III** (entrega final). Dos niveles jugables, un agente inteligente que aprende y tres niveles de dificultad.

## Cómo jugar

**Controles**

| Acción | Tecla |
|--------|-------|
| Caminar a la izquierda | Flecha izquierda |
| Caminar a la derecha | Flecha derecha |
| Saltar | Barra espaciadora |
| Agacharse | Flecha abajo |

En algunos teclados compactos las flechas comparten tecla con *Inicio* (izquierda), *Av Pág* (abajo) y *Fin* (derecha).

**Objetivo**

- Nivel 1: recoger el oro y la llave esquivando la liana que se balancea.
- Nivel 2: recoger la llave antes de que se acabe el tiempo, esquivando el remolino y las rocas que lanza el agente, que aprende dónde estarás.

Al iniciar el juego se elige la dificultad (Fácil, Normal o Difícil), que cambia el comportamiento del agente y del remolino en el Nivel 2.

## Cómo ejecutar (Linux, Ubuntu)

1. Instalar Qt 6: `sudo apt install qt6-base-dev qt6-multimedia-dev`
2. Entrar a la carpeta `ejecutable-linux/`
3. Ejecutar: `./AteneaEnElDorado`

La carpeta `assets/` debe estar junto al ejecutable.

## Cómo compilar desde el código fuente

Requiere Qt 6 (Widgets y Multimedia), CMake y g++.

```bash
cmake -S . -B build
cmake --build build
```

El ejecutable queda en `build/` junto con su carpeta `assets/`.

## Documentación

La documentación del proyecto se gestiona con **Obsidian** dentro de la carpeta `docs/`.

- [Momento I](docs/academic/Momento-I.md)

## Estructura del proyecto

```text
proyecto-final/
├── docs/                  # Documentación y Vault de Obsidian
│   ├── academic/         # Entregas académicas
│   ├── decisions/        # Decisiones del proyecto
│   ├── planning/         # Planificación
│   ├── product/          # Diseño y visión del videojuego
│   └── inbox/            # Ideas pendientes de organizar
│
├── src/                  # Código fuente C++
├── include/              # Archivos de cabecera C++
├── assets/               # Recursos del videojuego (sprites y sonidos)
├── ejecutable-linux/     # Ejecutable para Linux con sus assets
├── CMakeLists.txt        # Configuración de compilación
├── README.md
└── .gitignore
```

## Repositorio

https://github.com/Nataorozco/proyecto-final
