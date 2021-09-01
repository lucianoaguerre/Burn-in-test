# Proyecto

Burn-in Test

## Descripcion

En este documento se propone un sistema para hacer el burn-in test a fuentes de alimentación de tipo switching de 12V x 2A. El ensayo consiste en verificar que la fuente de alimentación esté funcionando correctamente, monitoreando la salida de 12V en vacío y en carga durante un lapso de tiempo. En dicho lapso la regulación de tensión no debe ser mayor que 10%, o el criterio que se elija. 

![equipo](/Media/vista1.jpg)
![despiece](/Media/vista2.jpg)

### Ciclado de la salida
Para estresar aún más las fuentes de alimentación que se están probando, la salida se enciende y apaga repetidamente. Si un dispositivo está destinado a fallar, generalmente pasa cuando la salida se cicla. Para capturar datos de falla, se mide la tensión de salida de cada fuente de alimentación cuando se enciende la salida. Después de que la salida se cicla de 15 a 20 veces, se deja encendida y se deja seguir envejeciendo la fuente. Mientras que la salida se deja encendida, el voltaje se mide solo ocasionalmente. 

### Ruido ambiente
Medir con exactitud la tensión de salida de una fuente switching es uy difícil en un contexto donde hay varias colocadas y funcionando al mismo tiempo, porque irradian ruido de alta frecuencia. Por lo tanto es importante que el circuito de medición realice promedios de cada muestra y tenga en cuento el efecto de sincronización de la medición de las fuentes.

### Vida útil de los componentes
Para hacer este test con carga, generalmente se utilizan relés, que conectan la resistencia con la salida de la fuente de alimentación. Pero como la fuente está encendida los relés se abren y cierran con voltaje en sus contactos. La activación de un relé de esta manera aumenta la posibilidad de formación de arco, lo que afecta la vida útil del mismo. Por otro lado, las resistencias cerámicas trabajan con una temperatura elevada, haciendo que irradien calor, debe monitorearse que la temperatura del módulo no sea muy elevada, para no reducir la vida útil de las mismas. Finalmente otro elemento que puede desgastarse es el conector de la fuente, de tanto colocar y retirar los enchufes puede dañarse las partes internas del conector y debe ser reemplazado.

### Corriente de carga
Si bien la fuente de alimentación a ensayar es de 2A, se propone que el ensayo con carga se haga al 80% de la corriente máxima, para no disipar tanto calor en los componentes.

### Ciclos
Para reducir el ruido eléctrico provocado por la transición de conexión y desconexión de las resistencias de carga, se propone un esquema de 12 ciclos de 5 segundos y luego se mantiene encendido con carga. El ciclo de la siguiente fuente comienza cuando termina la primera, y así sucesivamente. El ciclo completo de 10 fuentes es de 10 minutos. Por lo general, las recomendaciones para el test de burn-in sugieren probar las fuentes 4hs y si no hay fallas reducir el tiempo a 2hs. En el caso que ese tiempo sea muy largo se puede acortar o reducir los ciclos.


## Autor

Luciano Aguerre
[@luchoaguerre](https://twitter.com/luchoaguerre)
