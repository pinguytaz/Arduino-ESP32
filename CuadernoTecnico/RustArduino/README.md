Ejemplos y librerias de Arduino realizados en Rust
=======

Proyectos para ejecutarse en Arduino
## Instrucciones de construcción
1. Instalar: avr-gcc, avr-libc, avrdude.
2. `cargo build` construye el firmware.
3. `cargo run` carga el firmware en la placa 
    `ravedude` despues de cargar el firmware abre una consola serie con la placa
[`avr-hal` README]: https://github.com/Rahix/avr-hal#readme
[`ravedude`]: https://crates.io/crates/ravedude


cargo build --bin 'ejemplo'   Compila el ejemplo indicado  
cargo run --bin 'ejemplo'     Carga y ejecuta consola de ejemplo indicado  
cargo build  Compila todos los ejemplos  


## Ejemplos
1. digitales (uso de entradas y salidas digitales  
2. intexternas (mismo ejemplo anterior pero esperando interupción externas y no en loop  
3. pwm (ejemplo uso PWM con fade de Leds)
4. servomotor (Ejemplo con un servo motor) uso de los Timer-Counter generando PWM 
5. sonar (Ejemplo de uso del HC-SR04) uso de Timer-Counter como contador.
6. motor (Ejemplo simple de motor que funciona al pulsar boton)

   

<br><br>
__Website__: <https://www.pinguytaz.net>
