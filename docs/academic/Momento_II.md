
## ATENEA EL DORADO

Atenea es una de las 12 Diosas del olimpo en la mitologia griega. Es la hija de Zeus y Metis. Atenea se caracteriza por ser estrategica, justa y disciplinada, priorizando la inteligencia y la prudencia sobre la fuerza bruta.

El personaje de atenea en el dorado se va caracterizar por ser estrategica en el momento de atravesar los obstaculos, justa en el momento de encontrar el oro y no tomarlo como posesion, disciplinada para lograr llegar al siguiente nivel.

RESUMEN DEL JUEGO:

NIvel 1: En este nivel atenea empieza su aventura y desafio, Atenea decide aventurarse por un mundo fascinante de la cultura muisca de la actual colombia, donde el cacique se cubria de polvo de oro y ofrecia  tesoros en la laguna de Guatavita. Los conquistadores españoles malinterpretaron este ritual, transformando la figura del gobernante ("El Dorado") en la busqueda de una ciudad o reino fabuloso de inmensas riquezas.

NIvel 1: El recorrido de Atenea comienza en el territorio muisca donde ella se encuentra con obstaculos y objetos de gran valor para el territorio muisca, un obstaculo al que Atenea debe poner atencion en este nivel es a la enredadera aqui ella debe aplicar su estrategia detenerce por 2 segundos y pensar leer el patron, ya que debe agacharse y pasar en el momento justo para no chocar con ella, al finalizar su recorrido y saltar por diferentes bloques de ladrillo  ella podra tomar la llave y pasar al siguiente nivel 2.

Nivel 2: Este recorrido continua en la laguna de Guatvita. Aqui atenea se enfrenta a algo muy diferente y retador, el nivel uno es relativamente sencillo ya que solo debia poner especial cuidado a la enredadera lo otro era mas de salto entre bloques y un recorrido sencillo, aqui ya ella debera enfrentarse al ataque de un agente que le lanzara rocas que es inteligente observa sus movimientos calcula los mismos para el siguiente lanzamiento, si en uno de ellos logra tocarla esto ralentiza sus movimientos por 2 segundos, adicional a esto debe avanzar con precaucion de no caer a la laguna de contiene remolino, despues de superar lo antes mencionado finaliza el juego.

FISICAS:

| Física             | Ecuación                                     | Parámetros      | Clase      | Nivel |
| ------------------ | -------------------------------------------- | --------------- | ---------- | ----- |
| Péndulo (armónico) | `x = x0 + A·sen(ω·t)`                        | `A`, `ω`        | Enredadera | 1     |
| Parabólico         | `x = x0 + vx·t`; `y = y0 + vy·t + ½·g·t²`    | `vx`, `vy`, `g` | Roca       | 2     |
| Circular           | `x = cx + R·cos(ω·t)`; `y = cy + R·sen(ω·t)` | `R`, `ω`        | Remolino   | 2     |

Este juego se compone de dos niveles:

Nivel 1: el territorio muisca
Nivel 2: la laguna de guatavita

En el nivel 1 Atenea:

Caracteristicas de este personaje en este nivel; en este nivel atenea es estrategica para pasar agachada en el momento justo debajo de las enredaderas.

Tiempo: estrategica, se queda quieta 2 segundos frente a las enredaderas "lee" el patron y el momento seguro para pasar, bajo un contador de tiempo quieta.

Fisicas del nivel 1: pendulo (movimiento armonico).

Ecuacion: x = x0 + A·sen(ω·t)

Parametros: amplietud A, frecuencia w.

Donde y que se ve: nivel 1, enredaderas colgantes que oscilan, Atenea debe pasar agachada en el momento justo.

Vistas de este nivel: vista lateral con scroll horizontal.


En el nivel 2 Atenea:

Caracteristicas de este personaje en este nivel:

Tiempo: justa, el oro no se toma como posesion ella lo devuelve: si lo agarra, "pesa" y salta menos durante 5 segundos: Bajo un cambio temporal en la fuerza de salto.

Agente autonomo: Agente de las rocas, este no necesita sprite propio. Es un ente invisible que decide donde y cuando se desprende cada roca de la ladera.
Percepcion: 
Que hace:Observa donde esta Atenea y hacia donde se mueve(izquierda, derecha o quieta).
Como se veria en el codigo: Un metodo que lee get() y la direccion.
Razonamiento:
Que hace: Calcula en cuanto tiempo caera la roca y adivina donde estara Atenea para entonces.
Como se veria en el codigo: Un metodo que devuelve el punto donde debe caer la roca
Accion: 
Lanza la roca con vx, vy y g para que aterrice en ese punto.
Como se veria en el codigo: Un metodo que crea la rocacon esos parametros(aqui esta el parbolico).
Aprendizaje:
Guarda si acerto o fallo y cuanto, y corrige su "adelanto" para el proximo lanzamiento.
Como se veria en el codigo: Un contenedor con los ultimos intentos y un numero adelanto que se ajusta.

¿Como aprende?
Si la roca cae detras de atenea, el agente aprende a lanzar mas adelante. Si cae delante, lanza menos adelante con cada intentoel error se achica, asi que el juego se vuelve mas dificil mientras avanza.

Fisicas 1: Parabolico 

Ecuacion: `x = x0 + vx·t`, `y = y0 + vy·t + ½·g·t²`

Parametros:`vx`, `vy`, `g`

Donde y que se ve: nivel 2, piedras que se desprenden con velocidad horizontal.

Fisica 2: circular

Ecuacion:`x = cx + R·cos(ω·t)`, `y = cy + R·sen(ω·t)`

Parametros: Radio R, Velocidad W.

Donde y que se ve: nivel 2 remolinos.

Vistas de este nivel: vista lateral fija(una sola pantalla, la orilla).

LO QUE PIDE EL ENUNCIADO:

-Herencia propia: Obstaculo con sus hijos Enredadera, Roca y Remolino, y Nivel con Nivel1 y Nivel2.
-Memoria dinamica: Juego crea y destruye a Atenea y a los niveles, y cada nivel es el dueño de sus obstaculos  y objetos. 
-Agente: AgenteRocas esta dividido en percepcion, Razonamiento, Accion y Aprendizaje, cada uno en su propia clase. Aprendizaje guarda un vector de intento.
-Fisicas: Las ecuaciones de pendulo, parabolico y circular estan escritas dentro de enredadera, Roca y Remolino.
-Atenea: conserva todo con los atributos nuevos de estrategia y justa y el metodo Ralentizar.

Nota: aqui me falta un parametro actualizar(dt) en el diagrama que son (los segundos que pasaron) porque Atenea tiene Actualizar() sin parametro.  para las funciones con tiempo hace falta el (dt).


## Enlaces a los sprites

![Sprites nivel 1](assets/sprites/nivel-1/nivel_1_el_territorio_muisca.jpeg)
![Sprites nivel 2](assets/sprites/nivel-2/nivel_2_la_laguna_de_guatavita.jpeg)