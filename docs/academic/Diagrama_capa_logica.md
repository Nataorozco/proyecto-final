# Diagrama de clases — Momento II (capa lógica)

> Solo capa lógica: las reglas del juego, sin Qt. La capa de GUI se agrega en el Momento III. 

## Diagrama

```mermaid
classDiagram
direction TB

class Juego {
  -Atenea* atenea
  -vector~Nivel*~ niveles
  -int nivelActual
  +iniciar()
  +actualizar(float dt)
  +siguienteNivel()
  +~Juego()
}
class Atenea {
  -float x
  -float y
  -float velocidad
  -float velocidadY
  -Estado estado
  -int objetosRecogidos
  -float tiempoQuieta
  -float tiempoOro
  -float tiempoLento
  +mover(Direccion d)
  +saltar()
  +agacharse()
  +levantarse()
  +recogerOro()
  +ralentizar(float seg)
  +actualizar(float dt)
  +getX() float
  +getY() float
  +getEstado() Estado
}
class Nivel {
  <<abstract>>
  #vector~Obstaculo*~ obstaculos
  #vector~Objeto*~ objetos
  #Atenea* atenea
  #bool completado
  +actualizar(float dt)*
  +revisarColisiones()
  +revisarObjetos()
  +estaCompletado() bool
  +~Nivel()
}
class Nivel1 {
  -float scrollX
  -bool llaveTomada
  +actualizar(float dt)
  +avanzarScroll()
}
class Nivel2 {
  -float tiempoRestante
  -AgenteRocas* agente
  +actualizar(float dt)
  +tiempoAgotado() bool
}
class Obstaculo {
  <<abstract>>
  #float x
  #float y
  #float ancho
  #float alto
  +actualizar(float t)*
  +colisionaCon(Atenea& a) bool
  +getX() float
  +getY() float
}
class Enredadera {
  -float x0
  -float amplitud
  -float frecuencia
  +actualizar(float t)
}
class Roca {
  -float x0
  -float y0
  -float vx
  -float vy
  -float g
  -bool impacto
  +actualizar(float t)
  +haImpactado() bool
}
class Remolino {
  -float cx
  -float cy
  -float radio
  -float omega
  +actualizar(float t)
}
class Objeto {
  -float x
  -float y
  -TipoObjeto tipo
  -bool recogido
  +recoger()
  +estaRecogido() bool
  +getTipo() TipoObjeto
}
class AgenteRocas {
  -Percepcion percepcion
  -Razonamiento razonamiento
  -Accion accion
  -Aprendizaje aprendizaje
  +decidir(Atenea& a) Roca*
  +registrarResultado(bool acerto, float xImpacto)
}
class Percepcion {
  +observar(const Atenea& a) Observacion
}
class Razonamiento {
  -float gravedad
  -float alturaLanzamiento
  +calcularObjetivo(Observacion o, float adelanto) float
}
class Accion {
  +lanzar(float xObjetivo) Roca*
}
class Aprendizaje {
  -vector~Intento~ historial
  -float adelanto
  +registrar(Intento i)
  +corregir()
  +getAdelanto() float
}
class Observacion {
  <<struct>>
  float xAtenea
  Direccion direccion
  float velocidad
}
class Intento {
  <<struct>>
  float xObjetivo
  float xImpacto
  bool acerto
}
class Estado {
  <<enumeration>>
  DePie
  Caminando
  Agachada
  Saltando
}
class Direccion {
  <<enumeration>>
  Izquierda
  Derecha
}
class TipoObjeto {
  <<enumeration>>
  Llave
  Oro
}

Juego *-- Atenea
Juego *-- "1..2" Nivel
Nivel *-- "0..*" Obstaculo
Nivel *-- "0..*" Objeto
Nivel --> "1" Atenea : usa
Nivel <|-- Nivel1
Nivel <|-- Nivel2
Obstaculo <|-- Enredadera
Obstaculo <|-- Roca
Obstaculo <|-- Remolino
Nivel2 *-- "1" AgenteRocas
AgenteRocas *-- Percepcion
AgenteRocas *-- Razonamiento
AgenteRocas *-- Accion
AgenteRocas *-- Aprendizaje
Percepcion ..> Atenea : lee
Percepcion ..> Observacion
Accion ..> Roca : crea
Aprendizaje ..> Intento
Razonamiento ..> Observacion
Atenea --> Estado : estado
Atenea ..> Direccion : parámetro de mover
Objeto --> TipoObjeto : tipo
Observacion --> Direccion : direccion
```

Cómo leer las flechas: triángulo vacío = herencia; rombo lleno = composición (el todo es dueño de la parte); flecha simple = asociación (usa, no es dueño); flecha punteada = dependencia (usa de paso).

---

## Relación 

|Relación|Tipo|Se lee así|
|---|---|---|
|Juego → Atenea|Composición|"El juego crea a Atenea y la destruye al terminar."|
|Juego → Nivel (1..2)|Composición|"El juego crea los niveles y los destruye al terminar."|
|Nivel → Atenea|Asociación|"Un nivel usa a Atenea, pero no es su dueño; Atenea pasa de un nivel al otro."|
|Nivel → Obstaculo (0..*)|Composición|"Un nivel es dueño de sus obstáculos: los crea y los destruye."|
|Nivel → Objeto (0..*)|Composición|"Un nivel es dueño de sus objetos para recoger."|
|Nivel1, Nivel2 → Nivel|Herencia|"Nivel1 y Nivel2 son tipos de Nivel; cada uno actualiza a su manera."|
|Enredadera, Roca, Remolino → Obstaculo|Herencia|"Cada uno es un tipo de obstáculo con su propia física en `actualizar(t)`."|
|Nivel2 → AgenteRocas|Composición|"El nivel 2 tiene un agente y lo destruye con él."|
|AgenteRocas → Percepcion, Razonamiento, Accion, Aprendizaje|Composición|"El agente está formado por cuatro partes separadas."|
|Percepcion → Atenea|Dependencia|"La percepción lee a Atenea para observarla."|
|Accion → Roca|Dependencia|"La acción crea las rocas que lanza."|
|Aprendizaje → Intento|Dependencia|"El aprendizaje guarda un historial de intentos."|
|Razonamiento → Observacion|Dependencia|"El razonamiento recibe lo que percibió el agente para decidir."|
|Atenea → Estado|Asociación|"Atenea guarda su estado actual, que es uno de los valores de `Estado`."|
|Atenea → Direccion|Dependencia|"`mover()` recibe una `Direccion` como parámetro."|
|Objeto → TipoObjeto|Asociación|"Cada objeto guarda de qué tipo es: llave u oro."|
|Observacion → Direccion|Asociación|"La observación guarda hacia dónde se mueve Atenea."|

---

## Clases

### Atenea

- **Sabe:** posición `x`, `y`; `velocidad` y `velocidadY`; `estado`; `objetosRecogidos`; `tiempoQuieta` (estratégica); `tiempoOro` (justa); `tiempoLento` (para cuando una roca la golpea).
- **Hace:** `mover`, `saltar`, `agacharse`, `levantarse`, `recogerOro` (suma al marcador `objetosRecogidos` y activa `tiempoOro`), `ralentizar(seg)`, `actualizar(dt)`.
- **Idea clave:** no hereda de nada. Es la misma Atenea en los dos niveles.

### Obstaculo (abstracta) y sus hijos

- **Idea clave:** `actualizar(t)` es abstracta: cada hijo calcula su movimiento con su propia ecuación.
- **Enredadera** (nivel 1): péndulo. **Roca** (nivel 2): parabólico. **Remolino** (nivel 2): circular.

### Objeto

- Llave u oro (el pato). Guarda si ya fue recogido.

### Nivel (abstracta), Nivel1 y Nivel2

- **Nivel:** guarda los obstáculos, los objetos y el puntero a Atenea. Detecta choques y objetos, y Atenea reacciona con sus métodos.
- **Nivel1:** vista lateral con scroll; hay que llegar hasta la llave y tomarla para completar el nivel.
- **Nivel2:** vista lateral fija; contrarreloj con `tiempoRestante`; tiene el agente.

### AgenteRocas y sus cuatro partes

- **Percepcion:** observa a Atenea y devuelve una `Observacion` (posición, dirección, velocidad).
- **Razonamiento:** calcula dónde estará Atenea cuando llegue la roca, usando el `adelanto` aprendido.
- **Accion:** crea la `Roca` con `vx`, `vy` y `g` para que caiga en ese punto.
- **Aprendizaje:** guarda cada `Intento` (a dónde apuntó, dónde cayó, si acertó) y corrige el `adelanto`.

### Juego

- Crea y destruye a Atenea y a los niveles, y decide cuándo pasar al siguiente.

---

## Estructuras de datos y memoria dinámica

|Dato|Dónde|Para qué|Memoria|
|---|---|---|---|
|`vector<Nivel*>`|Juego|Guardar los dos niveles|`new` al crear, `delete` en `~Juego()`|
|`Atenea*`|Juego|Crear una sola Atenea|`new` / `delete` en el juego; los niveles solo la usan|
|`vector<Obstaculo*>`|Nivel|Guardar obstáculos de distinto tipo|`new` al crear; `delete` en `~Nivel()`|
|`vector<Objeto*>`|Nivel|Guardar los objetos|`delete` en `~Nivel()`|
|`AgenteRocas*`|Nivel2|El agente del nivel|`new` / `delete` en Nivel2|
|`vector<Intento>`|Aprendizaje|Historial para aprender|Se maneja solo (guarda copias)|
|`struct Observacion`, `struct Intento`|Agente|Pasar datos entre las partes|Sin memoria dinámica|
|`enum class`|Atenea, Objeto|Estados, direcciones y tipos|Sin memoria dinámica|

El destructor de `Nivel` y el de `Obstaculo` deben ser `virtual`, para que al borrar un obstáculo desde un puntero de la clase base se destruya el hijo correcto.

---

## Físicas

| Física             | Ecuación                                     | Parámetros      | Clase      | Nivel |
| ------------------ | -------------------------------------------- | --------------- | ---------- | ----- |
| Péndulo (armónico) | `x = x0 + A·sen(ω·t)`                        | `A`, `ω`        | Enredadera | 1     |
| Parabólico         | `x = x0 + vx·t`; `y = y0 + vy·t + ½·g·t²`    | `vx`, `vy`, `g` | Roca       | 2     |
| Circular           | `x = cx + R·cos(ω·t)`; `y = cy + R·sen(ω·t)` | `R`, `ω`        | Remolino   | 2     |

---



---

