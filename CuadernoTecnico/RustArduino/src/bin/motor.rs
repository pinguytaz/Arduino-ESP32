/********************************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro                                                                *
 *  WEB: www.pinguytaz.net                                                                              *
 *       https://github.com/pinguytaz                                                                   *
 *                                                                                                      *
 *  Descripción: Ejemplo de desarrollo en Arduino con el lenguage Rust.                                 *
 *               Ejecuta o para un motor al pulsar un boton.                                            *
 *                                                                                                      *
 *  Historico:                                                                                          *
 *      Creación:  0.1.0 Abril 2024  FJRN                                                               *
 *                                                                                                      *
 ********************************************************************************************************/
#![no_std]           // No usa libreria estandard, sino la core al tratarse de embebido
#![no_main]          // No usa la funcion main como inicio

use panic_halt as _;    // Tratamiento de ecepciones


#[arduino_hal::entry]      // Punto de entrada del programa
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

    let mut motor = pins.d12.into_output();  // Salida que activa o desactiva el motor.
    let boton = pins.d2;  // El boton es una entrada por defecto.

    // Configuracion de consola
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);

    // Este loop seria la función loop() de un programa arduino normal.
    loop {
        // Mira Boton
        if boton.is_high()   // El boton se activa a alto
        {
           if motor.is_set_low() {
               _ = ufmt::uwriteln!(serial, "Estaba en Bajo!"); 
               motor.set_high();
           } 
           else {
               _ = ufmt::uwriteln!(serial, "Estaba en Alto!"); 
               motor.set_low();
           }
//           motor.toggle();  // Cambia estado del motor
 //          _ = ufmt::uwriteln!(serial, "Cambio estado del motor!"); 
        }
        arduino_hal::delay_ms(1000);
    }
}
